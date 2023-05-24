#include QMK_KEYBOARD_H
#include "koy_keys_on_quertz_de_latin1.h"
// Layer shorthand
#define _1 0
#define _3 1
#define _4 2
#define _7 3


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_1] = LAYOUT(
    KC_ESC,  KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                        KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
    KC_TAB,  KC_K,   KC_DOT,  KC_O,    KC_COMM, N_Y,                         KC_V,    KC_G,    KC_C,    KC_L,    N_SS,    N_Z,
    MO(_3),  KC_H,   KC_A,    KC_E,    KC_I,    KC_U,                        KC_D,    KC_T,    KC_R,    KC_N,    KC_S,    KC_F,
    KC_LSFT, KC_X,   KC_Q,    N_AE,    N_UE,    N_OE,                        KC_B,    KC_P,    KC_W,    KC_M,    KC_J,    KC_RSFT,
    KC_LCTL, N_COPY, N_PASTE, KC_LGUI, KC_LALT, KC_SPC, KC_ENTER,   KC_RCTL, MO(_3),  MO(_4),  KC_TRNS, KC_TRNS, KC_CAPS, TT(_7)
  ),

  [_3] = LAYOUT(
    KC_ESC,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                      KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_BSPC,
    KC_TAB,   N_DOTS,  N_USC,   N_LSQBR, N_RSQBR, N_CIRC,                     N_EXKL,  N_LT,    N_GT,    N_EQ,    N_AMP,   N_ACUT,
    KC_TRNS,  N_BSLS,  N_SLSH,  N_LCUBR, N_RCUBR, N_ASTR,                     N_QUES,  N_LPARN, N_RPARN, N_MINS,  N_COLN,  N_AT,
    KC_LSFT,  N_HASH,  N_DLR,   N_PIPE,  N_TILD,  N_GRAVE,                    N_PLUS,  N_PERC,  N_QUOT,  N_SING,  N_SEMI,  KC_RSFT,
    KC_LCTL,  N_COPY,  N_PASTE, KC_LGUI, KC_LALT, KC_SPC,  KC_ENTER, KC_TRNS, KC_TRNS, KC_RCTL, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
  ),

  [_4] = LAYOUT(
    KC_ESC,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,                    KC_TRNS,        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,     KC_BSPC,
    KC_TAB,  KC_PGUP, KC_BSPC, KC_UP,   KC_DEL,   KC_PGDN,                    KC_KP_SLASH,    KC_7,    KC_8,    KC_9,    KC_KP_MINUS, KC_TRNS,
    KC_TRNS, KC_HOME, KC_LEFT, KC_DOWN, KC_RIGHT, KC_END,                     KC_KP_ASTERISK, KC_4,    KC_5,    KC_6,    KC_KP_PLUS,  KC_TRNS,
    KC_LSFT, KC_ESC,  KC_TAB,  KC_INS,  KC_ENTER, N_UNDO,                     KC_KP_ENTER,    KC_1,    KC_2,    KC_3,    KC_KP_DOT,   KC_RSFT,
    KC_LCTL, N_COPY,  N_PASTE, KC_LGUI, KC_LALT,  KC_0,    KC_ENTER, KC_0,    KC_TRNS,        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,     KC_TRNS
  ),

  [_7] = LAYOUT(
    KC_ESC,  KC_TRNS,      KC_TRNS,    KC_MS_BTN3, KC_TRNS,     KC_TRNS,                          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, RESET,
    KC_TAB,  KC_MS_WH_UP,  KC_MS_BTN2, KC_MS_UP,   KC_MS_BTN1,  KC_MS_WH_DOWN,                    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_MS_ACCEL0, KC_MS_LEFT, KC_MS_DOWN, KC_MS_RIGHT, KC_TRNS,                          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_LSFT, KC_MS_ACCEL1, KC_TRNS,    KC_TRNS,    KC_TRNS,     KC_TRNS,                          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_LCTL, KC_MS_ACCEL2, KC_TRNS,    KC_LALT,    KC_TRNS,     KC_TRNS,        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
  )
};
