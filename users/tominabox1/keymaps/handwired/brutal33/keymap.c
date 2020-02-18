
#include QMK_KEYBOARD_H
#include "quantum.h"
#include "tominabox1.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_brutal_wrap(
	KC_Q, KC_W, KC_F, KC_P, KC_G, KC_J, KC_L, KC_U, KC_Y, KC_QUOTE,
	_______________HOMEROW_MOD_________________,
	_______________COLEMAK3____________________,
    KC_NAV_ENT, KC_NUM_SPC, KC_NAV_ENT
  ),

  [_NUM_SYM] = LAYOUT_brutal_wrap(
	__________________NUM_1____________________,
	__________________NUM_2____________________,
	KC_BSLS, __________________NUM_3____________________, KC_DOT, KC_GRV,
    KC_TRNS,   KC_TRNS,  KC_TRNS
  ),

  [_NAV] = LAYOUT_brutal(
    RESET,  KC_NO,  KC_NO, KC_NO, KC_NO,  KC_NO,  KC_PGDN,    KC_UP,  KC_PGUP,    KC_SCLN,
    SPONGEBOB,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_HOME,  KC_LEFT,  KC_DOWN,  KC_RGHT,   KC_END,
    AESTHETIC,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,    KC_NO,  KC_COMM,   KC_DOT,  KC_BSLS,
    KC_TRNS,   KC_TRNS,  KC_TRNS
  ),
};
