#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2
#define _ADJUST 16

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
};

// Defines for task manager and such
#define CALTDEL LCTL(LALT(KC_DEL))
#define TSKMGR LCTL(LSFT(KC_ESC))
#define DSK_LFT LGUI(LCTL(KC_LEFT))
#define DSK_RT  LGUI(LCTL(KC_RIGHT))

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {


[_QWERTY] = LAYOUT( \
  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                       KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    \
  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                       KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, \
  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                       KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, \
          ALT_T(KC_ENT), LT(_LOWER, KC_TAB), CTL_T(KC_SPC),    SFT_T(KC_BSPC), LT(_RAISE, KC_DEL), KC_LGUI    \
),

[_RAISE] = LAYOUT( \
  KC_EXLM,    KC_AT,    KC_HASH, KC_DLR,  KC_PERC,      KC_PLUS, KC_7,     KC_8,   KC_9, KC_0,    \
  KC_CIRC,    KC_AMPR,  KC_TILD, KC_PIPE, KC_BSLS,      KC_MINUS,  KC_4,     KC_5,   KC_6, KC_EQL, \
  KC_DQT,     KC_QUOT,  KC_UNDS, KC_GRV,  _______,      KC_ASTR,  KC_1,     KC_2,   KC_3, _______, \
                        _______, MO(_ADJUST), _______,      _______,  _______,  _______                    \
),


[_LOWER] = LAYOUT( \
  KC_ESC,   KC_HOME, KC_UP,   KC_END,   _______,     KC_LPRN, KC_RPRN, _______, _______, _______,
  KC_VOLU,  KC_LEFT, KC_DOWN, KC_RIGHT, KC_PGUP,     KC_LBRC, KC_RBRC, _______, _______, _______, \
  KC_VOLD,  KC_MPRV, KC_MPLY, KC_MNXT,  KC_PGDN,     KC_LCBR, KC_RCBR, _______, _______,  _______, \
                    _______, _______, _______,      _______,  MO(_ADJUST), _______                    \
),


[_ADJUST] =  LAYOUT( \
  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,        KC_F6,   KC_F7,    KC_F8,   KC_F9,    KC_F10, \
  _______, DSK_LFT, _______, DSK_RT,  _______,      TSKMGR,  CALTDEL,  _______, KC_F11,   KC_F12, \
  QK_BOOT, _______, _______, _______, _______,      _______, _______,  _______, _______,  _______, \
                    _______, _______, _______,      _______, _______,  _______                    \
)
};

void persistant_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}
