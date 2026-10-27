#pragma once

#include QMK_KEYBOARD_H
#include "config.h"

// The time (in milliseconds) after which a mod-tap modifier is disabled.
static const uint16_t ONESHOT_MOD_TIMEOUT = ONESHOT_TIMEOUT;

// The time (in milliseconds) within which a second tap dispatches the modifier key press.
#ifndef ONESHOT_DOUBLE_TAP_TIMEOUT
#    define ONESHOT_DOUBLE_TAP_TIMEOUT (TAPPING_TERM * 2)
#endif

// The time (in milliseconds) after which holding a oneshot modifier activates it until release.
#ifndef ONESHOT_HOLD_TIMEOUT
#    define ONESHOT_HOLD_TIMEOUT 800
#endif

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
    deferred_token hold_token;
};

bool oneshot_timer_expired(struct oneshot *state);
void oneshot_modifier(struct oneshot *state, keyrecord_t *record);
void handle_oneshot_modifier(struct oneshot *state, keyrecord_t *record);
