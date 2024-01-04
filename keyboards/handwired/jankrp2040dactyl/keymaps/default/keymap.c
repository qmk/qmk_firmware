/* Copyright 2023 Ethan Perry (@wheres-perry)
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
  _BASELAYER,
  _FUNCTIONLAYER,
  _ARROWLAYER,
  _SYMBOLLAYER
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASELAYER] = LAYOUT(
        QK_GESC,KC_1,	  KC_2,   KC_3,   KC_4,   KC_5,         KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_EQUAL,
        KC_BSLS,KC_B,  	KC_Y,   KC_O, 	KC_U,	  KC_QUOT,      KC_SCLN,KC_L,	  KC_D,	  KC_W,	  KC_V,	  KC_Z,
        MO(_FUNCTIONLAYER),   KC_C, 	KC_I,   KC_E,	  KC_A, 	KC_COMM,      KC_DOT,	KC_H, 	KC_T,	  KC_S,	  KC_N,	  KC_Q,
        KC_LSFT,KC_G, 	KC_X,   KC_J,	  KC_K, 	KC_MINS,      KC_SLSH,KC_R,   KC_M,	  KC_F,	  KC_P,	  MO(_ARROWLAYER),

                                  KC_DEL, KC_SPC,KC_BSPC,       KC_ENT, MO(_SYMBOLLAYER), KC_TAB,    
                                  KC_LGUI,KC_LALT,              KC_RCTL,KC_NO                  
                                                                	    
                                                                                   
    ),
    [_ARROWLAYER] = LAYOUT(
        KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,      KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
        KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,      KC_TRNS,KC_TRNS,KC_UP,  KC_TRNS,KC_TRNS,KC_TRNS,
        MO(_FUNCTIONLAYER),  KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,      KC_TRNS,KC_LEFT,KC_DOWN,KC_RGHT,KC_TRNS,KC_TRNS,
        KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,      KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS, KC_TRNS,

                                  KC_DEL, KC_SPC,KC_BSPC,      KC_ENT, MO(_SYMBOLLAYER), KC_TAB,    
                                  KC_LGUI,KC_LALT,             KC_RCTL,KC_NO               
                                                                    
                                                               
    ),
    [_FUNCTIONLAYER] = LAYOUT(
        KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,        KC_F7,  KC_F8,  KC_F9,  KC_F10, KC_F11,  KC_F12,
        KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,      KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
        KC_TRNS,  KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,      KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,  
        KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,      KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,

                                  KC_DEL, KC_SPC,KC_BSPC,      KC_ENT, MO(_SYMBOLLAYER), KC_TAB,    
                                  KC_LGUI,KC_LALT,             KC_RCTL,   KC_NO                 
                                                                	    
                                                                
    ),
    [_SYMBOLLAYER] = LAYOUT(
        KC_TILD,KC_1,	  KC_2,   KC_3,   KC_4,   KC_5,         KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_GRV,
        KC_NO,  KC_PIPE,KC_BSLS,KC_EQL, KC_LT,	KC_GT,        KC_LCBR,KC_RCBR,KC_UNDS,KC_ASTR,KC_PLUS,	KC_NO,
       KC_TRNS,  KC_QUES,KC_QUOT,KC_DQUO,KC_COLN,KC_SCLN,      KC_LPRN,KC_RPRN,KC_COMM,KC_DOT, KC_MINS,KC_NO,
        KC_LSFT,KC_CIRC,KC_PERC,KC_AMPR,KC_HASH,KC_SLSH,      KC_LBRC,KC_RBRC,KC_DLR,	KC_AT,	KC_EXLM,KC_TRNS,
                                  KC_DEL, KC_SPC,KC_BSPC,       KC_ENT, KC_TRNS, KC_TAB,    
                                  KC_LGUI,KC_LALT,             KC_RCTL,KC_NO                 
                                                                	    
                                                                
    )
};
