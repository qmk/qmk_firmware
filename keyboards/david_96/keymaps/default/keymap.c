/* Copyright 2018 amnesia0287
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H

enum layers {
  _QWERTY,
  _F24_HOTKEY,
  _ADJUST_REST
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_all( \
/* ┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐ */
    KC_ESC,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_INS,   KC_HOME,   KC_PSCR,  KC_PAUS,   TG(2),   TG(1),
/* ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┴─────────┼─────────┼─────────┼─────────┼─────────┤ */
	  KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,            KC_NLCK,  KC_PSLS,  KC_PAST,  KC_PMNS,
/* ├─────────┴────┬────┴────┬────┴────┬────┴────┬────┴────┬────┴────┬────┴────┬────┴────┬────┴────┬────┴────┬────┴────┬────┴────┬────┴────┬──────────────┼─────────┼─────────┼─────────┼─────────┤ */
	  KC_TAB, 	     KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,       KC_P7,    KC_P8,    KC_P9,
/* ├──────────────┴──┬──────┴──┬──────┴──┬──────┴──┬──────┴──┬──────┴──┬──────┴──┬──────┴──┬──────┴──┬──────┴──┬──────┴──┬──────┴──┬──────┴──────────────├─────────├─────────├─────────├         ┤ */
	  KC_CAPS,          KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,  KC_ENT,               KC_P4,    KC_P5,    KC_P6,    KC_PPLS,
/* ├─────────────────┴───┬─────┴───┬─────┴───┬─────┴───┬─────┴───┬─────┴───┬─────┴───┬─────┴───┬─────┴───┬─────┴───┬─────┴───┬─────┴───────────┬─────────┼─────────┼─────────┼─────────┼─────────┤ */
	  KC_LSFT,              KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,          KC_UP,    KC_P1,    KC_P2,    KC_P3,
/* ├───────────┬─────────┴─┬───────┴───┬─────┴─────────┴─────────┴─────────┴─────────┴─────────┴───────┬─┴─────────┴──┬──────┴───────┬─────────┼─────────┼─────────┼─────────┼─────────┼         ┤ */
	  KC_LCTL,    KC_LGUI,      KC_LALT,                       KC_SPC,                              KC_RALT,       KC_RCTL,    KC_RGUI,     KC_LEFT,  KC_DOWN,  KC_RGHT,  KC_P0,   KC_PDOT,  KC_PENT
/* └───────────┴───────────┴───────────┴───────────────────────────────────────────────────────────────┴──────────────┴──────────────┴─────────┴─────────┴─────────┴─────────┴─────────┴─────────┘ */
  ),


  [_F24_HOTKEY] = LAYOUT_all( \
/* ┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐ */
    KC_ESC,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_INS,   KC_HOME,   KC_PSCR,  KC_PAUS,   XXXXXXX,  TG(1),
/* ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┴─────────┼─────────┼─────────┼─────────┼─────────┤ */
	  KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,            KC_NLCK,  KC_PSLS,  KC_PAST,  KC_PMNS,
/* ├─────────┴────┬────┴────┬────┴────┬────┴────┬────┴────┬────┴────┬────┴────┬────┴────┬────┴────┬────┴────┬────┴────┬────┴────┬────┴────┬──────────────┼─────────┼─────────┼─────────┼─────────┤ */
	  KC_TAB, 	     KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,       KC_P7,    KC_P8,    KC_P9,
/* ├──────────────┴──┬──────┴──┬──────┴──┬──────┴──┬──────┴──┬──────┴──┬──────┴──┬──────┴──┬──────┴──┬──────┴──┬──────┴──┬──────┴──┬──────┴──────────────├─────────├─────────├─────────├         ┤ */
	  KC_F20,            KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,  KC_ENT,               KC_P4,    KC_P5,    KC_P6,    KC_PPLS,
/* ├─────────────────┴───┬─────┴───┬─────┴───┬─────┴───┬─────┴───┬─────┴───┬─────┴───┬─────┴───┬─────┴───┬─────┴───┬─────┴───┬─────┴───────────┬─────────┼─────────┼─────────┼─────────┼─────────┤ */
	  KC_INT2,                KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,          KC_UP,    KC_P1,    KC_P2,    KC_P3,
/* ├───────────┬─────────┴─┬───────┴───┬─────┴─────────┴─────────┴─────────┴─────────┴─────────┴───────┬─┴─────────┴──┬──────┴───────┬─────────┼─────────┼─────────┼─────────┼─────────┼         ┤ */
	  KC_LANG2,    KC_LANG1,    KC_INT1,                       KC_SPC,                                      KC_LANG4,       KC_LANG3,    KC_INT4,  KC_LEFT,  KC_DOWN,  KC_RGHT,  KC_P0,   KC_PDOT,  KC_PENT
/* └───────────┴───────────┴───────────┴───────────────────────────────────────────────────────────────┴──────────────┴──────────────┴─────────┴─────────┴─────────┴─────────┴─────────┴─────────┘ */
  ),

  [_ADJUST_REST] = LAYOUT_all( \
/* ┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐ */
    KC_ESC,  RGB_TOG,   RGB_MOD,  RGB_HUI,  RGB_HUI,  RGB_VAI,  RGB_M_P,  RGB_M_T,  _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  RESET,    TG(2),  XXXXXXX,
/* ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┴─────────┼─────────┼─────────┼─────────┼─────────┤ */
	  KC_GRV,   BL_TOGG,  BL_STEP,   BL_ON,   BL_OFF,   BL_INC,   BL_DEC,  BL_BRTG,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,             XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
/* ├─────────┴────┬────┴────┬────┴────┬────┴────┬────┴────┬────┴────┬────┴────┬────┴────┬────┴────┬────┴────┬────┴────┬────┴────┬────┴────┬──────────────┼─────────┼─────────┼─────────┼─────────┤ */
	  KC_TAB, 	      KC_MPLY,  KC_MPRV,  KC_MNXT,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,       XXXXXXX,  XXXXXXX,  XXXXXXX,
/* ├──────────────┴──┬──────┴──┬──────┴──┬──────┴──┬──────┴──┬──────┴──┬──────┴──┬──────┴──┬──────┴──┬──────┴──┬──────┴──┬──────┴──┬──────┴──────────────├─────────├─────────├─────────├         ┤ */
	  KC_CAPS,           XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,    KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,  KC_ENT,               KC_P4,    KC_P5,    KC_P6,    KC_PPLS,
/* ├─────────────────┴───┬─────┴───┬─────┴───┬─────┴───┬─────┴───┬─────┴───┬─────┴───┬─────┴───┬─────┴───┬─────┴───┬─────┴───┬─────┴───────────┬─────────┼─────────┼─────────┼─────────┼─────────┤ */
	  KC_LSFT,              XXXXXXX,   XXXXXXX,  XXXXXXX,  XXXXXXX,  KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_INT3 ,          KC_UP,    KC_P1,    KC_P2,    KC_P3,
/* ├───────────┬─────────┴─┬───────┴───┬─────┴─────────┴─────────┴─────────┴─────────┴─────────┴───────┬─┴─────────┴──┬──────┴───────┬─────────┼─────────┼─────────┼─────────┼─────────┼         ┤ */
	  KC_LCTL,    KC_LGUI,       KC_LALT,                        XXXXXXX,                          KC_RALT,       KC_RCTL,     KC_RGUI,  KC_LEFT,  KC_DOWN,  KC_RGHT,  KC_P0,    KC_PDOT,  KC_PENT
/* └───────────┴───────────┴───────────┴───────────────────────────────────────────────────────────────┴──────────────┴──────────────┴─────────┴─────────┴─────────┴─────────┴─────────┴─────────┘ */
  ),



/*  [1] = LAYOUT_all( \ */
/* ┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐ */
//     RESET,    KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_INS,   KC_DEL,   KC_HOME,  KC_END,   KC_PGUP,  KC_PGDN,
/* ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┴─────────┼─────────┼─────────┼─────────┼─────────┤ */
//	  KC_GRV,   BL_TOGG,   BL_STEP,  BL_ON,    BL_OFF,   BL_INC,   BL_DEC,   BL_BRTG,    KC_8,     KC_9,     KC_0,   KC_MINS,  KC_EQL,      KC_BSPC,         KC_NLCK,  KC_PSLS,  KC_PAST,  KC_PMNS,
/* ├─────────┴────┬────┴────┬────┴────┬────┴────┬────┴────┬────┴────┬────┴────┬────┴────┬────┴────┬────┴────┬────┴────┬────┴────┬────┴────┬──────────────┼─────────┼─────────┼─────────┼─────────┤ */
//	  KC_TAB, 	      RGB_TOG,   RGB_MOD, RGB_HUI  ,RGB_SAI,  RGB_VAI,  RGB_VAD,  _______,  _______,  _______,  _______,  _______,  _______,    _______,     _______,  _______,  _______,
/* ├──────────────┴──┬──────┴──┬──────┴──┬──────┴──┬──────┴──┬──────┴──┬──────┴──┬──────┴──┬──────┴──┬──────┴──┬──────┴──┬──────┴──┬──────┴──────────────├─────────├─────────├─────────├         ┤ */
//	  KC_CAPS,          KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,  KC_ENT,               KC_P4,    KC_P5,    KC_P6,    KC_PPLS,
/* ├─────────────────┴───┬─────┴───┬─────┴───┬─────┴───┬─────┴───┬─────┴───┬─────┴───┬─────┴───┬─────┴───┬─────┴───┬─────┴───┬─────┴───────────┬─────────┼─────────┼─────────┼─────────┼─────────┤ */
//	  KC_LSFT,              KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,          KC_UP,    KC_P1,    KC_P2,    KC_P3,
/* ├───────────┬─────────┴─┬───────┴───┬─────┴─────────┴─────────┴─────────┴─────────┴─────────┴───────┬─┴─────────┴──┬──────┴───────┬─────────┼─────────┼─────────┼─────────┼─────────┼         ┤ */
//	  KC_LCTL,    KC_LGUI,    KC_LALT,                       KC_SPC,                              KC_RALT,       KC_RCTL,    MO(1),     KC_LEFT,  KC_DOWN,  KC_RGHT,  KC_P0,    KC_PDOT,  KC_PENT
/* └───────────┴───────────┴───────────┴───────────────────────────────────────────────────────────────┴──────────────┴──────────────┴─────────┴─────────┴─────────┴─────────┴─────────┴─────────┘ */
//  ),


/* 
  [0] = LAYOUT_all( \
    KC_ESC,  KC_F1,   KC_F2,  KC_F3,  KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_PSCR, KC_SLCK, KC_DEL,  \
    KC_GRV,  KC_1,    KC_2,   KC_3,   KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_HOME, \
    KC_TAB,  KC_Q,    KC_W,   KC_E,   KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_PGUP, \
    KC_LCTL, KC_A,    KC_S,   KC_D,   KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,  KC_PGDN, \
    KC_LSFT, KC_Z,    KC_X,   KC_C,   KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_UP,   LT(1, KC_END), \
    KC_LGUI, KC_LALT, KC_SPC, MO(1),  KC_LEFT, KC_DOWN, KC_RGHT \
  ),
*/

/*
  [1] = LAYOUT_all(
    RESET,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, \
    KC_TRNS, KC_TRNS, KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,   KC_F11, KC_F12,  KC_DEL,  KC_TRNS, \
    KC_CAPS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, \
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, \
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, \
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS \
  )
*/

};

//wrap every key with F24 

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    static uint8_t f24_tracker;
    /*
    uprintf("KL: kc: %u, col: %u, row: %u, pressed: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed);    
    if (layer_state_is(0)){
      print("this is layer 0\n");
    }    
    if (layer_state_is(1)){
      print("this is layer 1\n");
    }    
    if (layer_state_is(2)){
      print("this is layer 2\n");
    }
    if (layer_state_is(3)){
      print("this is layer 3\n");
    }
    */
   
    switch (keycode) {
    case KC_A ... KC_F23: //notice how it skips over F24
    case KC_EXECUTE ... KC_EXSEL: //exsel is the last one before the modifier keys
        if (record->event.pressed) {
          if(layer_state_is(_F24_HOTKEY)){
            register_code(KC_F24); //this means to send F24 down
            f24_tracker++;
          }
            register_code(keycode);
        } else {
            unregister_code(keycode);
            if(layer_state_is(_F24_HOTKEY)){
              f24_tracker--;
              if (!f24_tracker) {
                  unregister_code(KC_F24); //this means to send F24 up
              }
            }
            //real key is released HERE
        }
        return false;
        break;
    }
    return true;
}



// RGB Modes
// 1 = Static
// 2-5 = Breathing
// 6-8 = Rainbow
// 9-14 = Swirl
// 15-20 = Snake
// 21-24 = Nightrider
// 25 = Christmas
// 26-30 = Static Gradient
// uint8_t RGBLED_RAINBOW_SWIRL_INTERVALS[] PROGMEM = {100, 50, 10}; // Set the last one to 10ms for some speedy swirls

/*
void matrix_init_user() {
	rgblight_mode(5);
}
*/


uint32_t layer_state_set_user(uint32_t state) {
  uint8_t layer = biton32(state);
  switch (layer) {

  	case _ADJUST_REST:      	  
			rgblight_mode_noeeprom(RGBLIGHT_MODE_RGB_TEST);
      print("this is layer 2\n");
		  break;
		
    case _F24_HOTKEY:	  
			rgblight_mode_noeeprom(RGBLIGHT_MODE_KNIGHT);
      print("this is layer 1\n");
		  break;

   		case _QWERTY:
		  rgblight_mode_noeeprom(RGBLIGHT_MODE_RAINBOW_SWIRL);
      print("this is layer 0\n");	
		  break;   
  }

  return state;
}


/*  for debug show scan matix */
/*
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  // If console is enabled, it will print the matrix position and status of each key pressed
    uprintf("KL: kc: %u, col: %u, row: %u, pressed: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed);
    
    if (layer_state_is(0)){
      print("this is layer 0\n");
    }
    
    if (layer_state_is(1)){
      print("this is layer 1\n");
    }
    
    if (layer_state_is(2)){
      print("this is layer 2\n");
    }

    if (layer_state_is(3)){
      print("this is layer 3\n");
    }

  return true;
}
*/

