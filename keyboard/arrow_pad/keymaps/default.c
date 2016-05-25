// This is the canonical layout file for the Quantum project. If you want to add another keyboard,
// this is the style you want to emulate.

#include "arrow_pad.h"

#define LAYER_BASE                      0
#define LAYER_EDIT                      1
#define LAYER_FUNCTION                  2


#define SC_UNDO             LCTL(KC_Z)
#define SC_REDO             LCTL(KC_Y)
#define SC_CUT              LCTL(KC_X)
#define SC_COPY             LCTL(KC_C)
#define SC_PSTE             LCTL(KC_V)
#define SC_SELA             LCTL(KC_A)
#define SC_SAVE             LCTL(KC_S)
#define SC_OPEN             LCTL(KC_O)
#define SC_ACLS             LALT(KC_F4)
#define SC_CCLS             LCTL(KC_F4)

#define _______             KC_TRNS
#define XXXXXXX             KC_NO


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[LAYER_BASE] = { // BASE
  {  KC_ESC,  KC_TAB,  KC_DEL,  KC_FN0,   },
  {  KC_NLCK, KC_PEQL, KC_PSLS, KC_PAST,  },
  {  KC_P7,   KC_P8,   KC_P9,   KC_PMNS,  },
  {  KC_P4,   KC_P5,   KC_P6,   KC_PPLS,  },
  {  KC_P1,   KC_P2,   KC_P3,   XXXXXXX,  },
  {  KC_P0,   KC_PCMM, KC_PDOT, KC_PENT,  },
 },

[LAYER_EDIT] = { // EDIT
  {  KC_ESC,  KC_TAB,  KC_DEL,  _______,  },
  {  KC_FN1,  SC_PSTE, KC_PSLS, SC_REDO,  },
  {  KC_HOME, KC_UP,   KC_PGUP, SC_UNDO,  },
  {  KC_LEFT, KC_FN5,  KC_RGHT, KC_LCTL,  },
  {  KC_END,  KC_DOWN, KC_PGDN, XXXXXXX,  },
  {  KC_ENT,  KC_BSPC, KC_DEL,  KC_FN6,  },
 },

[LAYER_FUNCTION] = { // FUNCTION
  {  KC_FN2,  KC_FN3,  KC_FN4,  _______,  },
  {  KC_FN1,  _______, _______, _______,  },
  {  _______, _______, _______, _______,  },
  {  _______, _______, _______, _______,  },
  {  _______, _______, _______, _______,  },
  {  RESET,   _______, _______, _______,  },
 },

};


const uint16_t PROGMEM fn_actions[] = {
	[0] = ACTION_LAYER_MOMENTARY(LAYER_FUNCTION),
	[1] = ACTION_LAYER_TOGGLE(LAYER_EDIT),
	[2] = ACTION_BACKLIGHT_TOGGLE(),
	[3] = ACTION_BACKLIGHT_INCREASE(),
	[4] = ACTION_BACKLIGHT_DECREASE(),
	[5] = ACTION_MACRO_TAP(0),
    [6] = ACTION_MACRO_TAP(1),
};


void action_function(keyrecord_t *record, uint8_t id, uint8_t opt)
{
}


const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
    switch (id) {
    case 0:
        if (record->event.pressed) {
            register_code(KC_LCTL);
            if (record->tap.count == 1) {
                register_code(KC_C);
                unregister_code(KC_C);
            }
            else if (record->tap.count == 2) {
                register_code(KC_X);
                unregister_code(KC_X);
            }
            unregister_code(KC_LCTL);
        }
        break;
    case 1:
        if (record->event.pressed) {
            if (record->tap.count <= 2) register_mods(MOD_BIT(KC_LSFT));
            if (record->tap.count == 2) register_mods(MOD_BIT(KC_LCTL));
        }
        else {
            unregister_mods(MOD_BIT(KC_LSFT) | MOD_BIT(KC_LCTL));
        }
        break;
    }
    return MACRO_NONE;
};
