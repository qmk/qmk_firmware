// This is the canonical layout file for the Quantum project. If you want to add another keyboard,
// this is the style you want to emulate.

#include "retro_refit.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[0] =
	KEYMAP( ESC,    F1,   F2,   F3,   F4,   F5,   F6,   F7,   F8,  F9,  F10, NLCK, SLCK, PSCR, PAUS, \
			GRV,     1,    2,    3,    4,    5,    6,    7,    8,   9,    0, MINS,  EQL, BSPC, HOME, \
			TAB,     Q,    W,    E,    R,    T,    Y,    U,    I,   O,    P, LBRC, RBRC,       PGUP, \
			BSLS,    A,    S,    D,    F,    G,    H,    J,    K,   L, SCLN, QUOT,        ENT, PGDN, \
			LSFT,          Z,    X,    C,    V,    B,    N,    M, COMM, DOT, SLSH, RSFT,   UP,  END, \
			LCTL, LGUI, LALT,        SPC,                               INS,  DEL, LEFT, DOWN, RGHT),
};

const uint16_t PROGMEM fn_actions[] = {

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
