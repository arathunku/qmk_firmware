#pragma once

#include QMK_KEYBOARD_H
#include "config.h"

// The time (in milliseconds) after which a mod-tap modifier is disabled.
const static uint16_t ONESHOT_MOD_TIMEOUT = ONESHOT_TIMEOUT;

enum oneshot_state {
    ONESHOT_DISABLED,
    ONESHOT_TRIGGER,
    ONESHOT_HOLDING,
    ONESHOT_RELEASE_AFTER_HOLD,
    ONESHOT_RELEASE,
};

struct oneshot {
    enum oneshot_state state;
    uint16_t timer;
    uint16_t modifier;
};

bool oneshot_timer_expired(struct oneshot *state);
void oneshot_modifier(struct oneshot *state, keyrecord_t *record);
void handle_oneshot_modifier(struct oneshot *state);
