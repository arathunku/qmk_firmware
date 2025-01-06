#include "oneshot.h"

bool oneshot_timer_expired(struct oneshot *state) {
    return state->timer > 0 && (timer_elapsed(state->timer) > ONESHOT_MOD_TIMEOUT);
}

void oneshot_modifier(struct oneshot *state, keyrecord_t *record) {
    if (!record->event.pressed) {
        if (state->state == ONESHOT_HOLDING) {
            state->state = ONESHOT_TRIGGER;
        }
        else if (state->state == ONESHOT_RELEASE_AFTER_HOLD) {
            state->state = ONESHOT_DISABLED;

            unregister_code(state->modifier);
        }

        return;
    }

    if (state->state != ONESHOT_DISABLED) {
        state->state = ONESHOT_DISABLED;
        state->timer = 0;

        return;
    }

    state->state = ONESHOT_HOLDING;
    state->timer = timer_read();
}

void handle_oneshot_modifier(struct oneshot *state, keyrecord_t *record) {
    bool is_press = record->event.pressed;

    switch (state->state) {
        case ONESHOT_HOLDING:
            // This state means the one-shot mod key itself is still physically held.
            // If another key is pressed (is_press == true) during this hold,
            // the modifier should become active.
            if (is_press) {
                state->timer = 0; // Cancel timeout for tap behavior of the OS key
                state->state = ONESHOT_RELEASE_AFTER_HOLD;
                register_code(state->modifier);
            }
            break;

        case ONESHOT_TRIGGER:
            // One-shot mod key was tapped and released, waiting for the next key press.
            if (oneshot_timer_expired(state)) {
                state->timer = 0;
                state->state = ONESHOT_DISABLED;
                return;
            }

            if (is_press) {
                state->state = ONESHOT_RELEASE; // Modifier will be active for this key
                register_code(state->modifier);
            }
            // If !is_press, and state is ONESHOT_TRIGGER, do nothing.
            // Let it be consumed by a subsequent press or time out.
            break;

        case ONESHOT_RELEASE:
            // Modifier was active for a key press.
            // If that key is released, deactivate the modifier.
            if (!is_press) {
                state->state = ONESHOT_DISABLED;

                unregister_code(state->modifier);
            }
            // If is_press is true here, it means another key is pressed while the
            // modifier is already active from a previous key. The modifier remains active.
            break;

        case ONESHOT_DISABLED:
        case ONESHOT_RELEASE_AFTER_HOLD: // This state is managed by oneshot_modifier() upon OS key release.
            // Nothing to do in handle_oneshot_modifier for these states.
            break;
    }
}

