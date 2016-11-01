#include "gh60.h"
#include "action_layer.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* 0: qwerty */
    KEYMAP(
	ESC, 1,   2,   3,   4,   5,   6,   7,   8,   9,   0,   LBRC,RBRC,BSPC, \
        TAB, QUOT,COMM,DOT, P,   Y,   F,   G,   C,   R,   L,   SLSH,EQL, BSLS, \
        FN0, A,   O,   E,   U,   I,   D,   H,   T,   N,   S,   MINS,NO,  ENT,  \
        LSFT,NO,  SCLN,Q,   J,   K,   X,   B,   M,   W,   V,   Z,   NO,  RSFT, \
        LCTL,LALT,LGUI,          SPC,                NO,  RGUI,RALT,RCTL,FN0),
    /* 1: fn */
	KEYMAP(
        ESC, F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12, DEL,  \
        TRNS,TRNS,UP,  TRNS,TRNS,TRNS,TRNS,PGUP,UP,  PGDN,PSCR,SLCK,PAUS,TRNS, \
        TRNS,LEFT,DOWN,RGHT,TRNS,TRNS,HOME,LEFT,DOWN,RGHT,INS, DEL, TRNS,TRNS, \
        CAPS,TRNS,TRNS,TRNS,TRNS,TRNS,END, TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS, \
        TRNS,TRNS,TRNS,          TRNS,               TRNS,TRNS,TRNS,TRNS,TRNS),
};

const uint16_t PROGMEM fn_actions[] = {
    [0] = ACTION_LAYER_MOMENTARY(1),  // to Fn overlay
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
      switch(id) {
        case 0:
          if (record->event.pressed) {
            register_code(KC_RSFT);
          } else {
            unregister_code(KC_RSFT);
          }
        break;
      }
    return MACRO_NONE;
};

void matrix_scan_user(void) {

//Layer LED indicators
    uint32_t layer = layer_state;
	
    if (layer & (1<<1)) {
        gh60_wasd_leds_on();
        gh60_fn_led_on();
    } else {
        gh60_wasd_leds_off();
        gh60_fn_led_off();
    }
	
    if (layer & (1<<2)) {
        gh60_poker_leds_on();
        gh60_esc_led_on();
    } else {
        gh60_poker_leds_off();
        gh60_esc_led_off();
    }
	
};
