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

    // Pressing the key again disables it.
    if (state->state != ONESHOT_DISABLED) {
        state->state = ONESHOT_DISABLED;
        state->timer = 0;

        return;
    }

    state->state = ONESHOT_HOLDING;
    state->timer = timer_read();
}

void handle_oneshot_modifier(struct oneshot *state) {
    if (state->state == ONESHOT_HOLDING) {
        // We pressed a key while the modifier is still being held. In this case
        // we'll unregister the modifier when the modifier key is released.
        state->timer = 0;
        state->state = ONESHOT_RELEASE_AFTER_HOLD;

        register_code(state->modifier);
        return;
    }

    if (state->state == ONESHOT_TRIGGER) {
        // The modifier key was released before another key was pressed. In this
        // case we'll apply (if still valid) the modifier to the next key.
        if (oneshot_timer_expired(state)) {
            state->timer = 0;
            state->state = ONESHOT_DISABLED;

            return;
        }

        state->state = ONESHOT_RELEASE;

        register_code(state->modifier);
        return;
    }

    if (state->state == ONESHOT_RELEASE) {
        state->state = ONESHOT_DISABLED;

        unregister_code(state->modifier);
    }
}

