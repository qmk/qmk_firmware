
#include "atreus.h"

// layers
#define BASE      0
#define KEYNAV    1
#define KEYSEL    2
#define MOUSE     3
#define COMBINED  4

// macros
#define MOUSE_TOGGLE 1
#define MOUSE_LOCK 2

static bool mouse_lock = false;

// building instructions:
// make atreus-dvorak_42_key

// flashing instructions:
// avrdude -p atmega32u4 -c avr109 -U flash:w:atreus_dvorak_42_key.hex  -P COM7

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	
[BASE] = { 
  {KC_QUOTE,      KC_COMMA,      KC_DOT,    KC_P,       KC_Y,         KC_TRNS,    KC_F,  KC_G,  KC_C,   KC_R,   KC_L, },
  {KC_A,          KC_O,          KC_E,      KC_U,       KC_I,         KC_TRNS,    KC_D,  KC_H,  KC_T,   KC_N,   KC_S, },
  {KC_SCOLON,     KC_Q,          KC_J,      KC_K,       KC_X,         MO(KEYNAV), KC_B,  KC_M,  KC_W,   KC_V,   KC_Z, },
  {OSM(MOD_LSFT), OSM(MOD_LCTL), M(MOUSE_TOGGLE), MO(KEYSEL), MO(COMBINED), KC_ENTER,   KC_SPACE,  KC_BSPC, RCTL(KC_BSPC), KC_CAPSLOCK, OSM(MOD_LSFT), }
},	

[KEYNAV] = { 
  {KC_ESC,    MEH(KC_A), RCTL(KC_Z),   RCTL(KC_S), MEH(KC_B), KC_TRNS,    KC_TRNS,       KC_HOME,    KC_UP,           KC_END,     KC_PGUP, },
  {MEH(KC_C), MEH(KC_D), RSFT(KC_TAB), KC_TAB,     MEH(KC_E), KC_TRNS,    LCTL(KC_LEFT), KC_LEFT,    KC_DOWN,         KC_RIGHT,   LCTL(KC_RIGHT), },
  {MEH(KC_F), MEH(KC_G), MEH(KC_H),    MEH(KC_I),  MEH(KC_J), KC_TRNS,    KC_TRNS,       RCTL(KC_C), RCTL(KC_X),      RCTL(KC_V), KC_PGDOWN, },
  {KC_TRNS, KC_TRNS,   KC_TRNS,      KC_TRNS,    KC_TRNS,   KC_ENTER,   KC_SPACE,      KC_BSPC,   RCTL(KC_BSPC),    KC_DELETE,  LCTL(KC_DELETE), }
},	

[KEYSEL] = { 
  {KC_TRNS, KC_TRNS, RCTL(KC_Z),   RCTL(KC_S), KC_TRNS, KC_TRNS,    KC_TRNS,             RSFT(KC_HOME), RSFT(KC_UP),  RSFT(KC_END), RSFT(KC_PGUP), },
  {KC_TRNS, KC_TRNS, RSFT(KC_TAB), KC_TAB,     KC_TRNS, KC_TRNS,    RSFT(RCTL(KC_LEFT)), RSFT(KC_LEFT), RSFT(KC_DOWN), RSFT(KC_RIGHT), RSFT(RCTL(KC_RIGHT)), },
  {KC_TRNS, KC_TRNS, KC_TRNS,      KC_TRNS,    KC_TRNS, KC_TRNS,    KC_TRNS,             RCTL(KC_C),RCTL(KC_X),     RCTL(KC_V), RSFT(KC_PGDN), },
  {RESET,   KC_TRNS, KC_TRNS,      KC_TRNS,    KC_TRNS, KC_ENTER,   KC_SPACE,            KC_BSPC,   RCTL(KC_BSPC),  KC_DELETE,  LCTL(KC_DELETE), }
},	

[COMBINED] = { 
  {KC_ESC,  KC_LABK, KC_RABK,     KC_DQUO,     KC_GRAVE, KC_TRNS,    KC_PLUS,     KC_7,    KC_8,    KC_9,    KC_ASTR, },
  {KC_LPRN, KC_RPRN, KC_LBRACKET, KC_RBRACKET, KC_UNDS,  KC_TRNS,    KC_MINS,     KC_4,    KC_5,    KC_6,    KC_SLSH, },
  {KC_LCBR, KC_RCBR, KC_BSLS,     KC_PIPE,     KC_TILD,  KC_TRNS,    KC_EQUAL,    KC_1,    KC_2,    KC_3,    KC_QUES, },
  {KC_TRNS, KC_TRNS, KC_TRNS,     KC_TRNS,     KC_TRNS,  KC_TRNS,    KC_TRNS,     KC_0,  KC_DOT,  KC_TRNS, KC_TRNS, }
},	

[MOUSE] = { 
  {KC_TRNS,      KC_PGUP, KC_MS_WH_UP,   KC_UP,        KC_TRNS, KC_TRNS, KC_UP,     KC_HOME,   KC_MS_U,   KC_END,  KC_MS_WH_UP,  },
  {KC_MS_ACCEL0, KC_PGDN, KC_MS_WH_DOWN, KC_DOWN,      KC_TRNS, KC_TRNS, KC_DOWN,   KC_MS_L,   KC_MS_D,   KC_MS_R, KC_MS_WH_DOWN, },
  {KC_TRNS,      KC_TRNS, KC_TRNS,       KC_TRNS,      KC_TRNS, KC_BTN3, MEH(KC_X), MEH(KC_Y), MEH(KC_Z), KC_F5,   RCTL(KC_W), },
  {KC_TRNS, M(MOUSE_LOCK), KC_TRNS, KC_MS_ACCEL0, KC_TRNS, KC_BTN1, KC_BTN2, RSFT(RCTL(KC_TAB)), RCTL(KC_TAB), RCTL(KC_T), LALT(KC_LEFT), }
},	


};

const uint16_t PROGMEM fn_actions[] = {

};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
      switch(id) {
		case MOUSE_TOGGLE:
            if (record->event.pressed) {
				layer_on(MOUSE);
            } else {
				if(!mouse_lock)
					layer_off(MOUSE);
			}
			break;
		case MOUSE_LOCK:
			if (record->event.pressed)
			{
				if(mouse_lock)
				{
					mouse_lock = false;
					layer_off(MOUSE);
				}
				else
					mouse_lock = true;
			}
			break;		  
      }
    return MACRO_NONE;
};
