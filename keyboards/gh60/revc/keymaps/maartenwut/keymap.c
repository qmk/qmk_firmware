#include QMK_KEYBOARD_H

#define _MA 0
#define _GA 1
#define _FL 2
#define _AR 3

#define TRNS KC_TRNS
#define trigger_time 400

#define LSHIFT OSM(MOD_LSFT)
#define SPACE LT(_AR, KC_SPC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
// Main Layer
[_MA] = LAYOUT_60_ansi_split_bs_rshift(
  KC_GESC,  KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,  KC_NO,
  KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,
  KC_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,          KC_ENT,
  LSHIFT,         KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,  KC_DEL,
  KC_LCTL,  KC_LGUI,  KC_LALT,                    SPACE,                      KC_NO,    KC_RALT,  MO(_FL),  KC_RCTRL),

//Function Layer
[_FL] = LAYOUT_60_ansi_split_bs_rshift(
  KC_GRV,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   RESET,    KC_NO,
  TRNS,     TRNS,   TRNS,     TRNS,     TRNS,     TRNS,     TRNS,   TRNS,     TRNS,     TRNS,     TRNS,     TRNS,   TRNS,   KC_PSCR,
  TRNS,     KC_MS_L,  KC_MS_D,  KC_MS_R,  TRNS,   TG(_GA),  TRNS,   TRNS,   TRNS,   TRNS,   TRNS,   TRNS,         TRNS,
  TRNS,           TRNS,   TRNS,   TRNS,   TRNS,     TRNS,     TRNS,   TRNS,   KC_VOLD,  KC_VOLU,  KC_MUTE,  TRNS,   KC_MPLY,
  TRNS,     TRNS,     TRNS,                     TRNS,                     TRNS,   TRNS,   TRNS,   TRNS),

//Arrow keys layer (space bar)
[_AR] = LAYOUT_60_ansi_split_bs_rshift(
  KC_GRV,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   TRNS,   KC_NO,
  TRNS,   TRNS,     TRNS,     TRNS,     TRNS,     TRNS,     TRNS,     KC_PGUP,  KC_UP,    KC_PGDN,    TRNS,     TRNS,   TRNS,   TRNS,
  TRNS,   TRNS,     TRNS,     TRNS,     TRNS,     TRNS,     TRNS,     KC_LEFT,  KC_DOWN,    KC_RGHT,    TRNS,     TRNS,           TRNS,
  TRNS,         TRNS,   TRNS,   TRNS,   TRNS,   TRNS,     TRNS,     TRNS,     TRNS,     TRNS,   TRNS,     TRNS,     TRNS,
  TRNS,     TRNS,     TRNS,                     TRNS,                     TRNS,   TRNS,     TRNS,   TRNS),

//Game layer (fn + g)
[_GA] = LAYOUT_60_ansi_split_bs_rshift(
  TRNS,   TRNS,     TRNS,     TRNS,     TRNS,     TRNS,     TRNS,     TRNS,     TRNS,     TRNS,     TRNS,     TRNS,   TRNS,   TRNS,   KC_NO,
  TRNS,   TRNS,     TRNS,     TRNS,     TRNS,     TRNS,     TRNS,     TRNS,     TRNS,     TRNS,     TRNS,     TRNS,   TRNS,   TRNS,
  TRNS,   TRNS,     TRNS,     TRNS,     TRNS,     TRNS,     TRNS,     TRNS,     TRNS,     TRNS,     TRNS,     TRNS,           TRNS,
  KC_LSFT,        TRNS,     TRNS,     TRNS,     TRNS,     TRNS,     TRNS,     TRNS,     TRNS,     TRNS,   TRNS,     TRNS,   TRNS,
  TRNS,     TRNS,     TRNS,                     KC_SPC,                     TRNS,   TRNS,     MO(_FL),  TRNS),

};
