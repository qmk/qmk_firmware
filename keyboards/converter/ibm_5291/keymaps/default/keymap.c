/*
Copyright 2018 listofoptions <listofoptions@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H
/*
enum xt_keycodes
    { XT_PAST = SAFE_RANGE // XT pad asterisk / print screen
    , XT_SLCK              // XT scroll lock / break
    , XT_F6                // F6 / app key
    , XT_F5                // F5 / gui
    , XT_F9                // F9 / F11
    , XT_F10               // F10 / F12
    } ;
    
static bool shift_pressed   = false ,
            alt_pressed     = false ,
            ctrl_pressed    = false ,
            xt_pscr_pressed = false ,
            xt_brk_pressed  = false ,
            xt_app_pressed  = false ,
            xt_gui_pressed  = false ,
            xt_lout_pressed = false ,
            xt_f11_pressed  = false ,
            xt_f12_pressed  = false ;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case KC_LSFT:
    case KC_RSFT:
        if (record->event.pressed) {
            shift_pressed = true ;
        } else {
            shift_pressed = false ;
        }
        return true;
        break;
        
    case KC_LALT:
        if (record->event.pressed) {
            alt_pressed = true ;
        } else {
            alt_pressed = false ;
        }
        return true;
        break;
        
    case KC_LCTL:
        if (record->event.pressed) {
            ctrl_pressed = true ;
        } else {
            ctrl_pressed = false ;
        }
        return true;
        break;
    
    case XT_PAST:
        if (record->event.pressed) {
            if (shift_pressed) {
                xt_pscr_pressed = true ;
                register_code(KC_PSCR);
            } else {
                register_code(KC_PAST);
            }
        } else {
            if (xt_pscr_pressed) {
                xt_pscr_pressed = false ;
                unregister_code(KC_PSCR);
            } else {
                unregister_code(KC_PAST);
            }
        }
        return false;
        break;
      
    case XT_SLCK:
        if (record->event.pressed) {
            if (ctrl_pressed) {
                xt_brk_pressed  = true ;
                register_code(KC_BRK);
            } else {
                register_code(KC_SLCK);
            }
        } else {
            if (xt_brk_pressed) {
                xt_brk_pressed  = false ;
                unregister_code(KC_BRK);
            } else {
                unregister_code(KC_SLCK);
            }
        }
        return false;
        break;
    
    case XT_F6:
        if (record->event.pressed) {
            if (shift_pressed) {
                xt_app_pressed = true ;
                register_code(KC_APP);
            } else {
                register_code(KC_F6);
            }
        } else {
            if (xt_app_pressed) {
                xt_app_pressed = false ;
                unregister_code(KC_APP);
            } else {
                unregister_code(KC_F6);
            }
        }
        return false;
        break;
    
    case XT_F5:
        if (record->event.pressed) {
            if (shift_pressed) {
                xt_gui_pressed = true ;
                register_code(KC_LGUI);
            } else if (ctrl_pressed) {
                xt_lout_pressed = true ;
                register_code (KC_LGUI) ;
                register_code (KC_L)    ;
            } else {
                register_code(KC_F5);
            }
        } else {
            if (xt_gui_pressed) {
                xt_gui_pressed = false ;
                unregister_code(KC_LGUI);
            } else if (xt_lout_pressed) {
                xt_lout_pressed = false ;
                unregister_code (KC_LGUI) ;
                unregister_code (KC_L)    ;
            } else {
                unregister_code(KC_F5);
            }
        }
        return false;
        break;
    
    case XT_F9:
        if (record->event.pressed) {
            if (shift_pressed) {
                xt_f11_pressed = true ;
                register_code(KC_F11);
            } else {
                register_code(KC_F9);
            }
        } else {
            if (xt_f11_pressed) {
                xt_f11_pressed = false ;
                unregister_code(KC_F11);
            } else {
                unregister_code(KC_F9);
            }
        }
        return false;
        break;
    
    case XT_F10:
        if (record->event.pressed) {
            if (shift_pressed) {
                xt_f12_pressed = true ;
                register_code(KC_F12);
            } else {
                register_code(KC_F10);
            }
        } else {
            if (xt_f12_pressed) {
                xt_f12_pressed = false ;
                unregister_code(KC_F12);
            } else {
                unregister_code(KC_F10);
            }
        }
        return false;
        break;
    
    default:
        return true;
        break;
  }
  
  return true;
}
*/
    
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
// default layout is the standard XT layout
/*
 * ,-------.  ,--------------------------------------------------------------------------.
 * | F1| F2|  |Esc|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|  BS  |NumLck |ScrLck |
 * |-------|  |--------------------------------------------------------------------------|
 * | F3| F4|  | Tab |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ] |   |  7|  8|  9|  -|
 * |-------|  |------------------------------------------------------|Ent|---------------|
 * | F5| F6|  | Ctrl |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|  `|   |  4|  5|  6|   |
 * |-------|  |----------------------------------------------------------------------|   |
 * | F7| F8|  |Shif|  \|  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shift|  *|  1|  2|  3|  +|
 * |-------|  |----------------------------------------------------------------------|   |
 * | F9|F10|  |  Alt  |               Space                  |CapsLck|   0   |   .   |   |
 * `-------'  `--------------------------------------------------------------------------'
*/
/*
    [0] = LAYOUT (
        KC_F1,KC_F2, KC_ESC, KC_1,   KC_2,KC_3,KC_4,KC_5,KC_6,KC_7,KC_8,KC_9,   KC_0,   KC_MINS,KC_EQL, KC_BSPC,      KC_NLCK,       XT_SLCK,
        KC_F3,KC_F4, KC_TAB, KC_Q,   KC_W,KC_E,KC_R,KC_T,KC_Y,KC_U,KC_I,KC_O,   KC_P,   KC_LBRC,KC_RBRC,        KC_P7,KC_P8,  KC_P9, KC_PMNS, 
        XT_F5,XT_F6, KC_LCTL,KC_A,   KC_S,KC_D,KC_F,KC_G,KC_H,KC_J,KC_K,KC_L,   KC_SCLN,KC_QUOT,KC_GRV, KC_ENT, KC_P4,KC_P5,  KC_P6,           
        KC_F7,KC_F8, KC_LSFT,KC_BSLS,KC_Z,KC_X,KC_C,KC_V,KC_B,KC_N,KC_M,KC_COMM,KC_DOT, KC_SLSH,KC_RSFT,XT_PAST,KC_P1,KC_P2,  KC_P3, KC_PPLS, 
        XT_F9,XT_F10,KC_LALT,                              KC_SPACE,                                    KC_CAPS,      KC_P0,  KC_PDOT           
    )
*/
    [0] = LAYOUT (
        KC_F1,KC_F2, KC_ESC, KC_1,   KC_2,KC_3,KC_4,KC_5,KC_6,KC_7,KC_8,KC_9,   KC_0,   KC_MINS,KC_EQL, KC_BSPC,      KC_NLCK,       KC_SLCK,
        KC_F3,KC_F4, KC_TAB, KC_Q,   KC_W,KC_E,KC_R,KC_T,KC_Y,KC_U,KC_I,KC_O,   KC_P,   KC_LBRC,KC_RBRC,        KC_P7,KC_P8,  KC_P9, KC_PMNS, 
        KC_F5,KC_F6, KC_LCTL,KC_A,   KC_S,KC_D,KC_F,KC_G,KC_H,KC_J,KC_K,KC_L,   KC_SCLN,KC_QUOT,KC_GRV, KC_ENT, KC_P4,KC_P5,  KC_P6,           
        KC_F7,KC_F8, KC_LSFT,KC_BSLS,KC_Z,KC_X,KC_C,KC_V,KC_B,KC_N,KC_M,KC_COMM,KC_DOT, KC_SLSH,KC_RSFT,KC_PAST,KC_P1,KC_P2,  KC_P3, KC_PPLS, 
        KC_F9,KC_F10,KC_LALT,                              KC_SPACE,                                    KC_CAPS,      KC_P0,  KC_PDOT           
    )
} ;

