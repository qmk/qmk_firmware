#include "lets_split.h"
#include "rekeymap.h"
#include "action_layer.h"
#include "eeconfig.h"

extern keymap_config_t keymap_config;

#define QWERTY_LAYER 0
#define LOWER_LAYER 1
#define UPPER_LAYER 2
#define UNDERGLOW_LAYER 6

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[QWERTY_LAYER] = KEYMAP( \
  KC_ESC,     KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_BSPC, \
  KC_TAB,     KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_ENT, \
  KC_LSFT,    KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_ENT, \
  KC_LCTL,  MO(UNDERGLOW_LAYER),   KC_LALT,  KC_LGUI,  MO(LOWER_LAYER),    F(1),     KC_SPC,     KC_LGUI,  KC_LALT, MO(UPPER_LAYER), KC_MINS,  KC_EQL \
),

[UPPER_LAYER] = KEYMAP( \
  KC_GRV,     KC_1,  KC_2,  KC_3,  KC_4,  KC_5,  KC_6,  KC_7,  KC_8,  KC_9,  KC_0,  _______, \
  KC_TAB,    KC_4,  KC_5,  KC_6,  KC_DOT,   _______,   KC_LEFT,  KC_DOWN,  KC_UP,  KC_RIGHT,  _______,  _______, \
  KC_LSFT,    KC_7,  KC_8,  KC_9,  KC_0,     _______,  _______,  _______,  _______,  KC_MPLY,  KC_MPRV,  KC_MNXT, \
  KC_LCTL,    KC_LCTL,  KC_LALT,  KC_LGUI,   _______,  _______,  _______,  _______,  KC_MUTE,  _______,  KC_VOLD,   KC_VOLU \
),

[LOWER_LAYER] = KEYMAP( \
  KC_GRV,         KC_EXLM,   KC_AT,    KC_HASH,  KC_DLR,   KC_PERC,  KC_CIRC,  KC_AMPR,  KC_ASTR,  KC_LPRN,  KC_RPRN,  KC_MINS, \
  KC_TAB,         KC_F1,     KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_UNDS,  KC_PLUS,  KC_LCBR,  KC_RCBR,  KC_BSLS, \
  KC_LSFT,         KC_F7,     KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   _______,  KC_HOME,  KC_PGDN,  KC_PGUP,  KC_END, \
  KC_LCTL,  KC_LCTL,   KC_LALT,  KC_LGUI,  _______,  _______,  _______,  _______,  KC_LEFT,  KC_DOWN,  KC_UP,  KC_RIGHT \
),

[UNDERGLOW_LAYER] = KEYMAP( \
  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______, \
  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______, \
  _______,  RGB_TOG,  RGB_MOD,  RGB_HUD,  RGB_HUI,  RGB_SAD,  RGB_SAI,  RGB_VAD,  RGB_VAI,  _______,  _______,  _______, \
  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______ \
),
};

const uint16_t PROGMEM fn_actions[] = {
    [0] = ACTION_DEFAULT_LAYER_SET(QWERTY_LAYER),

    // // Tap for backspace, hold for LOWER
    // [1] = ACTION_LAYER_TAP_KEY(LOWER_LAYER, KC_BSPC),
    //
    // Tap for space, hold for RAISE
    [1] = ACTION_LAYER_TAP_KEY(UPPER_LAYER, KC_SPC),
    //
    // Tap for space, hold for SpaceFN
    // [3] = ACTION_LAYER_TAP_KEY(SPACEFN_LAYER, KC_SPC),
};
