#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2
#define _TB 3

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT( /* Qwerty */ \
    KC_ESC,          KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,     \
    LT(_TB, KC_TAB), KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_QUOT,              \
    KC_LSFT,         KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  MT(MOD_RSFT, KC_ENT), \
    KC_LCTL,         KC_LGUI, KC_LALT,        LT(_RAISE, KC_SPC), LT(_LOWER, KC_SPC),        KC_RALT, KC_APP,  KC_RCTL      \
  ),

  [_RAISE] = LAYOUT( \
    KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC, \
    _______, _______, _______, KC_PAUS, _______, _______, _______, KC_UNDS, KC_PLUS, KC_LCBR, KC_PIPE,          \
    _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_ENT,           \
    _______, _______, _______,                   _______, _______,                   KC_MNXT, KC_MUTE, KC_MPLY  \
  ),

  [_LOWER] = LAYOUT( \
    KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL,  \
    _______, _______, _______, _______, _______, _______, _______, KC_MINS, KC_EQL,  KC_LBRC, KC_BSLS,          \
    _______, KC_F11,  KC_F12,  KC_F13,  KC_F14,  KC_F15,  KC_F16,  KC_F17,  KC_F18,  KC_PGUP, KC_ENT,           \
    _______, _______, _______,                   _______, _______,                   KC_HOME, KC_PGDN, KC_END   \
  ),

  [_TB] = LAYOUT( /* Tab */ \
    KC_ESC,  KC_CALC, KC_WHOM, KC_MAIL, KC_MYCM, _______, _______, _______, _______, _______, KC_PSCR, _______, \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          \
    _______, RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, KC_UP,   KC_ENT,           \
    BL_STEP, _______, _______,                   _______, _______,                   KC_LEFT, KC_DOWN, KC_RGHT  \
  )

};
