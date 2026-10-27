#include "oneshot.h"

static uint16_t nonzero_timer_read(void) {
    uint16_t now = timer_read();
    return now ? now : 0xFFFF;
}

static void cancel_oneshot_timer(struct oneshot *state) {
    if (state->hold_token != INVALID_DEFERRED_TOKEN) {
        cancel_deferred_exec(state->hold_token);
        state->hold_token = INVALID_DEFERRED_TOKEN;
    }
}

static uint32_t oneshot_timer_callback(uint32_t trigger_time, void *cb_arg) {
    (void)trigger_time;
    struct oneshot *state = (struct oneshot *)cb_arg;
    state->hold_token = INVALID_DEFERRED_TOKEN;

    if (state->state == ONESHOT_HOLDING) {
        state->timer = 0;
        state->state = ONESHOT_RELEASE_AFTER_HOLD;
        register_code(state->modifier);
    } else if (state->state == ONESHOT_TRIGGER) {
        state->timer = 0;
        state->state = ONESHOT_DISABLED;
    }

    return 0;
}

bool oneshot_timer_expired(struct oneshot *state) {
    return state->timer > 0 && (timer_elapsed(state->timer) > ONESHOT_MOD_TIMEOUT);
}

void oneshot_modifier(struct oneshot *state, keyrecord_t *record) {
    if (!record->event.pressed) {
        cancel_oneshot_timer(state);

        if (state->state == ONESHOT_HOLDING) {
            state->state = ONESHOT_TRIGGER;
            state->timer = nonzero_timer_read();
            state->hold_token = defer_exec(ONESHOT_MOD_TIMEOUT, oneshot_timer_callback, state);
        }
        else if (state->state == ONESHOT_RELEASE_AFTER_HOLD) {
            state->state = ONESHOT_DISABLED;
            state->timer = 0;

            unregister_code(state->modifier);
        }

        return;
    }

    if (state->state == ONESHOT_TRIGGER) {
        cancel_oneshot_timer(state);
        if (!oneshot_timer_expired(state)) {
            if (state->timer > 0 && timer_elapsed(state->timer) <= ONESHOT_DOUBLE_TAP_TIMEOUT) {
                state->state = ONESHOT_RELEASE_AFTER_HOLD;
                state->timer = 0;
                register_code(state->modifier);
            } else {
                state->state = ONESHOT_DISABLED;
                state->timer = 0;
            }
            return;
        }
        state->state = ONESHOT_DISABLED;
        state->timer = 0;
    }

    if (state->state == ONESHOT_RELEASE) {
        cancel_oneshot_timer(state);
        unregister_code(state->modifier);
        state->state = ONESHOT_DISABLED;
        state->timer = 0;
    } else if (state->state != ONESHOT_DISABLED) {
        cancel_oneshot_timer(state);
        if (state->state == ONESHOT_RELEASE_AFTER_HOLD) {
            unregister_code(state->modifier);
        }
        state->state = ONESHOT_DISABLED;
        state->timer = 0;

        return;
    }

    state->state = ONESHOT_HOLDING;
    state->timer = nonzero_timer_read();
    state->hold_token = defer_exec(ONESHOT_HOLD_TIMEOUT, oneshot_timer_callback, state);
}

void handle_oneshot_modifier(struct oneshot *state, keyrecord_t *record) {
    bool is_press = record->event.pressed;

    switch (state->state) {
        case ONESHOT_HOLDING:
            // This state means the one-shot mod key itself is still physically held.
            // If another key is pressed (is_press == true) during this hold,
            // the modifier should become active.
            if (is_press) {
                cancel_oneshot_timer(state);
                state->timer = 0; // Cancel timeout for tap behavior of the OS key
                state->state = ONESHOT_RELEASE_AFTER_HOLD;
                register_code(state->modifier);
#ifdef REPEAT_KEY_ENABLE
                set_last_mods(get_last_mods() | MOD_BIT(state->modifier));
#endif
            }
            break;

        case ONESHOT_TRIGGER:
            // One-shot mod key was tapped and released, waiting for the next key press.
            if (oneshot_timer_expired(state)) {
                cancel_oneshot_timer(state);
                state->timer = 0;
                state->state = ONESHOT_DISABLED;
                return;
            }

            if (is_press) {
                cancel_oneshot_timer(state);
                state->timer = 0;
                state->state = ONESHOT_RELEASE; // Modifier will be active for this key
                register_code(state->modifier);
#ifdef REPEAT_KEY_ENABLE
                set_last_mods(get_last_mods() | MOD_BIT(state->modifier));
#endif
            }
            // If !is_press, and state is ONESHOT_TRIGGER, do nothing.
            // Let it be consumed by a subsequent press or time out.
            break;

        case ONESHOT_RELEASE:
            // Modifier was active for a single key press.
            // Deactivate when that key is released, or before a rolled second key press.
            state->state = ONESHOT_DISABLED;
            state->timer = 0;

            unregister_code(state->modifier);
            break;

        case ONESHOT_DISABLED:
        case ONESHOT_RELEASE_AFTER_HOLD: // This state is managed by oneshot_modifier() upon OS key release.
            // Nothing to do in handle_oneshot_modifier for these states.
            break;
    }
}

