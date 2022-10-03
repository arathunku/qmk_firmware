#include QMK_KEYBOARD_H
#include "version.h"
#include "keymap_german.h"
#include "keymap_bepo.h"
#include "keymap_contributions.h"
#include "oneshot.h"

#define KC_MAC_UNDO LGUI(KC_Z)
#define KC_MAC_CUT LGUI(KC_X)
#define KC_MAC_COPY LGUI(KC_C)
#define KC_MAC_PASTE LGUI(KC_V)
#define KC_PC_UNDO LCTL(KC_Z)
#define KC_PC_CUT LCTL(KC_X)
#define KC_PC_COPY LCTL(KC_C)
#define KC_PC_PASTE LCTL(KC_V)
#define ES_LESS_MAC KC_GRAVE
#define ES_GRTR_MAC LSFT(KC_GRAVE)
#define ES_BSLS_MAC ALGR(KC_6)
#define NO_PIPE_ALT KC_GRAVE
#define NO_BSLS_ALT KC_EQUAL
#define LSA_T(kc) MT(MOD_LSFT | MOD_LALT, kc)
#define BP_NDSH_MAC ALGR(KC_8)
#define SE_SECT_MAC ALGR(KC_6)
#define MOON_LED_LEVEL LED_LEVEL

#define KC_OCTL ONESHOT_CTL
#define KC_OALT ONESHOT_ALT
#define KC_OMETA ONESHOT_META
#define KC_OSHIFT ONESHOT_SHIFT
#define KC_OSCTL ONESHOT_SHIFT_CTL
// THIS SHOULD MATCH ORYX
#define NORM 0
#define DVO 1
#define QRT 2
#define SYM 3
#define NAV 4
#define VIS 5
#define FUN 6
#define NUM 7
#define KC_SYM MO(SYM)
#define KC_NAV MO(NAV)
#define KC_NUML MO(NUM)

enum custom_keycodes {
  RGB_SLD = ML_SAFE_RANGE,
  ST_MACRO_0,
  /* added */
  ONESHOT_SHIFT,
  ONESHOT_META,
  ONESHOT_ALT,
  ONESHOT_CTL,
  ONESHOT_SHIFT_CTL
  /* /added */
};

static struct oneshot shift_state = {
    .state = ONESHOT_DISABLED,
    .timer = 0,
    .modifier = KC_LSHIFT,
};

static struct oneshot ctl_state = {
    .state = ONESHOT_DISABLED,
    .timer = 0,
    .modifier = KC_LCTL,
};

static struct oneshot meta_state = {
    .state = ONESHOT_DISABLED,
    .timer = 0,
    .modifier = KC_LGUI,
};

static struct oneshot alt_state = {
    .state = ONESHOT_DISABLED,
    .timer = 0,
    .modifier = KC_LALT,
};

bool arath_process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case ONESHOT_SHIFT:
        oneshot_modifier(&shift_state, record);
        break;
    case ONESHOT_META:
        oneshot_modifier(&meta_state, record);
        break;
    case ONESHOT_ALT:
        oneshot_modifier(&alt_state, record);
        break;
    case ONESHOT_CTL:
        oneshot_modifier(&ctl_state, record);
        break;
    case ONESHOT_SHIFT_CTL:
        oneshot_modifier(&shift_state, record);
        oneshot_modifier(&ctl_state, record);
        break;
    case KC_NAV:
    case KC_NUML:
    case KC_SYM:
        break;
    default:
      handle_oneshot_modifier(&shift_state);
      handle_oneshot_modifier(&ctl_state);
      handle_oneshot_modifier(&meta_state);
      handle_oneshot_modifier(&alt_state);
  }

  return true;
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_moonlander(
    KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,                                          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,
    KC_NO,          KC_Q,           KC_W,           KC_F,           KC_P,           KC_B,           KC_NO,                                          KC_NO,          KC_J,           KC_L,           KC_U,           KC_Y,           KC_QUOTE,       KC_NO,
    KC_NO,          KC_A,           KC_R,           KC_S,           KC_T,           KC_G,           KC_NO,                                                                          KC_NO,          KC_M,           KC_N,           KC_E,           KC_I,           KC_O,           KC_NO,
    KC_NO,          KC_Z,           KC_X,           KC_C,           KC_D,           KC_V,                                           KC_K,           KC_H,           KC_COMMA,       KC_DOT,         KC_SCOLON,      KC_NO,
    KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NUML,        KC_NO,                                                                                                          KC_NO,          KC_RALT,        KC_NO,          KC_NO,          KC_NO,          KC_NO,
    KC_NAV,         OSM(MOD_LCTL),  KC_NO,                          KC_NO,          OSM(MOD_LSFT),  LT(SYM,KC_SPACE)
  ),
  [1] = LAYOUT_moonlander(
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, KC_SCOLON,      KC_COMMA,       KC_TRANSPARENT, KC_P,           KC_Y,           KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_F,           KC_G,           KC_C,           KC_R,           KC_L,           KC_TRANSPARENT,
    KC_TRANSPARENT, KC_A,           KC_O,           KC_E,           KC_U,           KC_I,           KC_TRANSPARENT,                                                                 KC_TRANSPARENT, KC_D,           KC_H,           KC_T,           KC_N,           KC_S,           KC_TRANSPARENT,
    KC_TRANSPARENT, KC_QUOTE,       KC_Q,           KC_J,           KC_K,           KC_X,                                           KC_B,           KC_M,           KC_W,           KC_V,           KC_Z,           KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                                                                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT
  ),
  [2] = LAYOUT_moonlander(
    KC_ESCAPE,      KC_1,           KC_2,           KC_3,           KC_4,           KC_5,           KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_6,           KC_7,           KC_8,           KC_9,           KC_0,           KC_BSPACE,
    KC_TAB,         KC_Q,           KC_TRANSPARENT, KC_E,           KC_R,           KC_T,           KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_Y,           KC_U,           KC_I,           KC_O,           KC_P,           KC_BSLASH,
    KC_LCTRL,       KC_A,           KC_S,           KC_D,           KC_F,           KC_G,           KC_TRANSPARENT,                                                                 KC_TRANSPARENT, KC_H,           KC_J,           KC_K,           KC_L,           KC_SCOLON,      KC_ENTER,
    KC_LSHIFT,      KC_Z,           KC_X,           KC_C,           KC_V,           KC_B,                                           KC_N,           KC_M,           KC_COMMA,       KC_DOT,         KC_SLASH,       KC_MINUS,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_LGUI,        KC_TRANSPARENT, KC_TRANSPARENT,                                                                                                 KC_TRANSPARENT, KC_RALT,        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_EQUAL,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT
  ),
  [SYM] = LAYOUT_moonlander(
    KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_TRANSPARENT,
    KC_NO,          KC_CIRC,        KC_LBRACKET,    KC_LCBR,        KC_LPRN,        KC_LABK,        KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_RABK,        KC_RPRN,        KC_RCBR,        KC_RBRACKET,    KC_GRAVE,       KC_TRANSPARENT,
    KC_NO,          KC_MINUS,       KC_ASTR,        KC_EQUAL,       KC_UNDS,        KC_DLR,         KC_TRANSPARENT,                                                                 KC_TRANSPARENT, LSFT(KC_SCOLON),KC_RCTRL,       KC_RALT,        KC_TILD,        KC_BSPACE,      KC_TRANSPARENT,
    KC_NO,          KC_PLUS,        KC_PIPE,        KC_AT,          KC_SLASH,       KC_PERC,                                        KC_HASH,        KC_BSLASH,      KC_AMPR,        KC_QUES,        KC_EXLM,        KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_NO,          KC_NO,                                                                                                          KC_NO,          KC_NO,          KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_NO,          KC_NO,          KC_NO,                          KC_NO,          KC_NO,          KC_NO
  ),
  [NAV] = LAYOUT_moonlander(
    KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,                                          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,
    KC_NO,          TO(0),          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,                                          KC_NO,          KC_NO,          KC_HOME,        KC_UP,          KC_END,         KC_DELETE,      KC_NO,
    KC_NO,          KC_OSHIFT,      KC_OMETA,       KC_OALT,        KC_OCTL,        KC_TAB,         KC_NO,                                                                          KC_NO,          KC_NO,          KC_LEFT,        KC_DOWN,        KC_RIGHT,       KC_BSPACE,      KC_NO,
    KC_NO,          KC_PSCREEN,     TT(5),          KC_SPACE,       KC_ESCAPE,      LSFT(KC_TAB),                                   KC_NO,          KC_PGUP,        KC_PGDOWN,      KC_NO,          KC_ENTER,       KC_NO,
    KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,                                                                                                          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,
    KC_NO,          KC_NO,          KC_NO,                          KC_NO,          MO(FUN),        KC_NO
  ),
  [5] = LAYOUT_moonlander(
    KC_TRANSPARENT, KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_TRANSPARENT,                                 KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,
    KC_TRANSPARENT, RGB_VAD,        RGB_VAI,        TOGGLE_LAYER_COLOR,ST_MACRO_0,     RESET,          KC_TRANSPARENT,                                 KC_NO,          KC_NO,          KC_MS_BTN1,     KC_MS_UP,       KC_MS_BTN2,     KC_NO,          KC_TRANSPARENT,
    KC_TRANSPARENT, KC_NO,          RGB_HUD,        RGB_HUI,        KC_NO,          KC_NO,          KC_TRANSPARENT,                                                                 KC_NO,          KC_NO,          KC_MS_LEFT,     KC_MS_DOWN,     KC_MS_RIGHT,    KC_NO,          KC_NO,
    KC_TRANSPARENT, MOON_LED_LEVEL, TO(0),          KC_NO,          KC_NO,          KC_NO,                                          KC_NO,          KC_MS_WH_DOWN,  KC_MS_WH_UP,    KC_MS_BTN3,     KC_NO,          KC_TRANSPARENT,
    KC_NO,          KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_NO,          KC_TRANSPARENT,                                                                                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_NO,          KC_NO,          KC_NO,                          KC_TRANSPARENT, KC_NO,          KC_NO
  ),
  [6] = LAYOUT_moonlander(
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, KC_NO,          TO(2),          TO(1),          KC_NO,          KC_NO,          KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_NO,          KC_F7,          KC_F8,          KC_F9,          KC_F10,         KC_TRANSPARENT,
    KC_TRANSPARENT, KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_TRANSPARENT,                                                                 KC_TRANSPARENT, KC_NO,          KC_F4,          KC_F5,          KC_F6,          KC_F11,         KC_TRANSPARENT,
    KC_TRANSPARENT, KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,                                          KC_NO,          KC_F1,          KC_F2,          KC_F3,          KC_F12,         KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                                                                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT
  ),
  [7] = LAYOUT_moonlander(
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_NO,                                          KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,          KC_NO,                                          KC_TRANSPARENT, KC_NO,          KC_7,           KC_8,           KC_9,           KC_DELETE,      KC_TRANSPARENT,
    KC_TRANSPARENT, LGUI(KC_4),     LGUI(KC_3),     LGUI(KC_2),     LGUI(KC_1),     LCTL(KC_A),     KC_TRANSPARENT,                                                                 KC_TRANSPARENT, KC_0,           KC_4,           KC_5,           KC_6,           KC_BSPACE,      KC_TRANSPARENT,
    KC_TRANSPARENT, LGUI(KC_9),     LGUI(KC_0),     KC_NO,          KC_NO,          KC_NO,                                          KC_NO,          KC_1,           KC_2,           KC_3,           KC_ENTER,       KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_NO,                                                                                                          KC_NO,          KC_NO,          KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, KC_NO,          KC_TRANSPARENT,                 KC_TRANSPARENT, KC_TRANSPARENT, KC_SPACE
  ),
};

extern rgb_config_t rgb_matrix_config;

void keyboard_post_init_user(void) {
  rgb_matrix_enable();
}

const uint8_t PROGMEM ledmap[][DRIVER_LED_TOTAL][3] = {
    [0] = { {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {152,255,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {188,255,255}, {0,0,0}, {0,0,0}, {0,0,0} },

    [1] = { {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {91,218,204}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {91,218,204}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {91,218,204}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {91,218,204}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0} },

    [2] = { {98,161,216}, {98,161,216}, {98,161,216}, {98,161,216}, {98,161,216}, {98,161,216}, {98,161,216}, {98,161,216}, {98,161,216}, {98,161,216}, {98,161,216}, {98,161,216}, {98,161,216}, {98,161,216}, {98,161,216}, {98,161,216}, {98,161,216}, {98,161,216}, {98,161,216}, {98,161,216}, {98,161,216}, {98,161,216}, {98,161,216}, {98,161,216}, {98,161,216}, {98,161,216}, {98,161,216}, {98,161,216}, {98,161,216}, {98,161,216}, {98,161,216}, {98,161,216}, {98,161,216}, {98,161,216}, {98,161,216}, {98,161,216}, {98,161,216}, {98,161,216}, {98,161,216}, {98,161,216}, {98,161,216}, {98,161,216}, {98,161,216}, {98,161,216}, {98,161,216}, {98,161,216}, {98,161,216}, {98,161,216}, {98,161,216}, {98,161,216}, {98,161,216}, {98,161,216}, {98,161,216}, {98,161,216}, {98,161,216}, {98,161,216}, {98,161,216}, {98,161,216}, {98,161,216}, {98,161,216}, {98,161,216}, {98,161,216}, {98,161,216}, {98,161,216}, {98,161,216}, {98,161,216}, {98,161,216}, {98,161,216}, {98,161,216}, {98,161,216}, {98,161,216}, {98,161,216} },

    [3] = { {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,205,155}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0} },

    [4] = { {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {154,86,255}, {0,0,0}, {0,0,0}, {0,0,0}, {154,86,255}, {154,86,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {154,86,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0} },

    [5] = { {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,183,238}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {32,255,234}, {32,255,234}, {0,0,0}, {0,0,0}, {0,0,0}, {32,255,234}, {32,255,234}, {0,0,0}, {0,0,0}, {0,0,0}, {32,255,234}, {32,255,234}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0} },

    [6] = { {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {50,153,244}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {152,255,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0} },

    [7] = { {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {91,218,204}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0} },

};

void set_layer_color(int layer) {
  for (int i = 0; i < DRIVER_LED_TOTAL; i++) {
    HSV hsv = {
      .h = pgm_read_byte(&ledmap[layer][i][0]),
      .s = pgm_read_byte(&ledmap[layer][i][1]),
      .v = pgm_read_byte(&ledmap[layer][i][2]),
    };
    if (!hsv.h && !hsv.s && !hsv.v) {
        rgb_matrix_set_color( i, 0, 0, 0 );
    } else {
        RGB rgb = hsv_to_rgb( hsv );
        float f = (float)rgb_matrix_config.hsv.v / UINT8_MAX;
        rgb_matrix_set_color( i, f * rgb.r, f * rgb.g, f * rgb.b );
    }
  }
}

void rgb_matrix_indicators_user(void) {
  if (keyboard_config.disable_layer_led) { return; }

  switch (biton32(layer_state)) {
    case 0:
      set_layer_color(0);
      break;
    case 1:
      set_layer_color(1);
      break;
    case 2:
      set_layer_color(2);
      break;
    case 3:
      set_layer_color(3);
      break;
    case 4:
      set_layer_color(4);
      break;
    case 5:
      set_layer_color(5);
      break;
    case 6:
      set_layer_color(6);
      break;
    case 7:
      set_layer_color(7);
      break;
   default:
    if (rgb_matrix_get_flags() == LED_FLAG_NONE)
      rgb_matrix_set_color_all(0, 0, 0);
    break;
  }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  arath_process_record_user(keycode, record);

  switch (keycode) {
    case ST_MACRO_0:
    if (record->event.pressed) {
      SEND_STRING(SS_LALT(SS_TAP(X_SPACE)) SS_DELAY(100) SS_TAP(X_W) SS_DELAY(100) SS_TAP(X_A) SS_DELAY(100) SS_TAP(X_L) SS_DELAY(100) SS_TAP(X_Y)  SS_DELAY(100) SS_TAP(X_ENTER));

    }
    break;
    case RGB_SLD:
      if (record->event.pressed) {
        rgblight_mode(1);
      }
      return false;
  }

  return true;
}
