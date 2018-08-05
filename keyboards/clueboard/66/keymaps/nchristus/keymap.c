#include "66.h"
#include "action_layer.h"
#include "eeconfig.h"

extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define LOWER F(1)
#define RAISE F(2)
#define _FN 3
#define _CL 4

// Useful defines
#define _______ KC_TRNS
#define XXXXXXX KC_NO

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Keymap _QWERTY: Base Layer (Default Layer) */
[0] = LAYOUT (
  KC_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSLS, KC_GRV,           KC_MUTE, \
  KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSPC,                   _______, \
  KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, XXXXXXX, KC_ENT,                             \
  KC_LSPO, XXXXXXX, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_SLSH, KC_RSPC,          KC_UP,            \
  MO(_FN), MO(_CL), KC_LALT, KC_LGUI,          RAISE,   LOWER,                              KC_RGUI, KC_RALT, MO(_FN), KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
),

/* Keymap LOWER: Lower Layer */
[1] = LAYOUT (
  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______, _______, _______, _______,          _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                   _______, \
  _______, _______, _______, _______, _______, _______, _______, KC_MINS, KC_PLUS, KC_LBRC, KC_RBRC, KC_BSLS, _______, _______,                            \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,          \
  _______, _______, _______, _______,          _______, _______,                            _______, _______, _______, _______, _______, _______, _______
),

/* Keymap RAISE: Raise Layer */
[2] = LAYOUT (
  KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______, _______, _______, _______,          _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                   _______, \
  _______, _______, _______, _______, _______, _______, _______, KC_UNDS, KC_EQL,  KC_LCBR, KC_RCBR, KC_PIPE, _______, _______,                            \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,          \
  _______, _______, _______, _______,          _______, _______,                            _______, _______, _______, _______, _______, _______, _______
),

/* Keymap _FL: Function Layer */
[_FN] = LAYOUT (
  _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, _______,          BL_STEP, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                   BL_TOGG, \
  _______, _______, _______, _______, _______, _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, _______, _______, _______,                            \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          KC_VOLU,          \
  _______, _______, _______, _______,          _______, _______,                            _______, _______, _______, _______, KC_MRWD, KC_VOLD, KC_MPLY
),

/* Keymap _CL: Control layer */
[_CL] = LAYOUT (
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RGB_TOG,          RGB_VAI, \
  _______, _______, _______, _______, RESET,   _______, _______, _______, _______, _______, _______, _______, _______, _______,                   RGB_VAD, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                            \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          RGB_SAI,          \
  _______, _______, _______, _______,          RGB_MOD, RGB_MOD,                            _______, _______, _______, _______, RGB_HUD, RGB_SAD, RGB_HUI
)
};

const uint16_t PROGMEM fn_actions[] = {
 [1] = ACTION_LAYER_TAP_KEY(1, KC_SPC),
 [2] = ACTION_LAYER_TAP_KEY(2, KC_ENT)
};
