#include "gamenum.h"
#include "action_layer.h"
#include "eeconfig.h"


#define _______ KC_TRNS

#define DEF 0
#define HDN 1
#define OSY 2

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[DEF] = KEYMAP(
  KC_FN0,   KC_SLSH, KC_ASTR, KC_MINS, \
  KC_7,      KC_8,       KC_9,       KC_PLUS, \
  KC_4,      KC_5,       KC_6, \
  KC_1,      KC_2,       KC_3, \
  KC_0,      KC_DOT,  KC_ENT \
),
[HDN] = KEYMAP(
  KC_FN1,   KC_1,  	KC_2,   	KC_3,  \
  KC_Q,      KC_W, 	KC_E,   	KC_R, \
  KC_A,      KC_S,  	KC_D, \
  KC_Z,      KC_X,  	KC_C, \
  KC_LSFT, KC_LALT,  KC_SPC \
),
[OSY] = KEYMAP(
  KC_A,    	KC_Q, 	KC_1, 	KC_FN2, \
  KC_S,    	KC_W, 	KC_2, 	KC_LALT, \
  KC_D,    	KC_E, 	KC_3, \
  KC_F,   	KC_R, 	KC_4, \
  KC_SPC, KC_T, 	KC_TAB \
)
};


const uint16_t PROGMEM fn_actions[] = {
		[0] = ACTION_LAYER_SET(HDN, ON_PRESS),
		[1] = ACTION_LAYER_SET(OSY, ON_PRESS),
		[2] = ACTION_LAYER_SET(DEF, ON_PRESS),
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
  return MACRO_NONE;
};


bool process_record_user (uint16_t keycode, keyrecord_t *record) {
  switch(keycode) {
  case KC_FN0:
      if (record->event.pressed) {
        PORTC |= (1 << 6); // PC6 goes high 
     }
     break;
  case KC_FN1:
      if (record->event.pressed) {
        PORTC &= ~(1 << 6); // PC6 goes high 
		PORTD |= (1<<4);
     }
     break;
  case KC_FN2:
      if (record->event.pressed) {
        PORTD &= ~(1 << 4); // PC6 goes high 
     }
     break;
  }
  return true;
}