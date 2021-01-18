 /* Copyright 2020 King Wang Wong
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


enum layer_names {
    _ML,
    _FL,
    _NL,
    _SL,
    _RL
};


#define SPC_FUN LT(_FL, KC_SPC)
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

      /* 0: Main Layer
   * ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────────┐
   * │ ESC │  Q  │  W  │  E  │  R  │  T  │  Y  │  U  │  I  │  O  │  P  │BKSPC    │  
   * ├─────┴┬────┴┬────┴┬────┴┬────┴┬────┴┬────┴┬────┴┬────┴┬────┴┬────┴┬────────┤
   * │ TAB  │  A  │  S  │  D  │  F  │  G  │  H  │  J  │  K  │  L  │ ;   │ENTER   │
   * ├──────┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬─────┤
   * │ LSHFT   │  Z  │  X  │  C  │  V  │  B  │  N  │  M  │  ,  │  .  │  /  │'    │
   * ├────────┬┴─────┴─┬───┴─┬───┴─────┴──┬──┴─────┴─────┴─┬───┴─┬───┴─┬───┴─────┤
   * │LCTRL   │   LGUI │ LALT│SPACE(_NL)  │MO(_NL)         │MO_SL│     │MO(RL    │
   * └────────┴────────┴─────┴────────────┴────────────────┴─────┴─────┴─────────┘
   */
    [_ML] = LAYOUT(
        KC_ESC,  KC_Q,    KC_W,    KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,    KC_O,     KC_P,     KC_BSPC,  
        KC_TAB,  KC_A,    KC_S,    KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,    KC_L,     KC_SCLN,  KC_ENT,         
        KC_LSFT, KC_Z,    KC_X,    KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM, KC_DOT,   KC_SLSH,  KC_QUOT,     
        KC_LCTL, KC_LGUI, KC_LALT,         SPC_FUN,        MO(_NL),        MO(_SL), XXXXXXX,  MO(_RL)
    ),


      /* 1: Function Layer
   * ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────────┐
   * │     │     │HOME │ UP  │END  │PGUP │     │ F1  │ F2  │ F3  │ F4  │         │
   * ├─────┴┬────┴┬────┴┬────┴┬────┴┬────┴┬────┴┬────┴┬────┴┬────┴┬────┴┬────────┤
   * │ CAPS │     │LEFT │DOWN │RIGHT│PGDN │     │ F5  │ F6  │ F7  │ F8  │ QUOT   │
   * ├──────┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬─────┤
   * │         │     │     │ DEL │ INS │     │     │ F9  │ F10 │ F11 │ F12 │     │
   * ├────────┬┴─────┴─┬───┴─┬───┴─────┴──┬──┴─────┴─────┴─┬───┴─┬───┴─┬───┴─────┤
   * │        │        │     │            │                │     │     │         │
   * └────────┴────────┴─────┴────────────┴────────────────┴─────┴─────┴─────────┘
   */
    [_FL] = LAYOUT(
        _______,   XXXXXXX, KC_HOME, KC_UP,   KC_END,  KC_PGUP, XXXXXXX, KC_F1, KC_F2,   KC_F3,    KC_F4,   _______,  
        KC_CAPS,   XXXXXXX, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, XXXXXXX, KC_F5, KC_F6,   KC_F7,    KC_F8,   KC_QUOT,        
        _______,   XXXXXXX, XXXXXXX, KC_DEL,  KC_INS,  XXXXXXX, XXXXXXX, KC_F9, KC_F10,  KC_F11,   KC_F12,  _______,        
        _______,   _______,  _______,         _______,          _______,        _______, _______,  _______
    ),



      /* 2: Number Layer
   * ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────────┐
   * │  ~  │  !  │  @  │  #  │  $  │  %  │  ^  │  &  │  *  │  (  │  )  │         │
   * ├─────┴┬────┴┬────┴┬────┴┬────┴┬────┴┬────┴┬────┴┬────┴┬────┴┬────┴┬────────┤
   * │   `  │  1  │  2  │  3  │  4  │  5  │  6  │  7  │  8  │  8  │ 0   │        │
   * ├──────┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬─────┤
   * │         │     │     │     │     │     │     │     │     │     │     │     │
   * ├────────┬┴─────┴─┬───┴─┬───┴─────┴──┬──┴─────┴─────┴─┬───┴─┬───┴─┬───┴─────┤
   * │        │        │     │            │                │     │     │         │
   * └────────┴────────┴─────┴────────────┴────────────────┴─────┴─────┴─────────┘
   */
    [_NL] = LAYOUT(
        KC_TILD,  KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN,  _______,  
        KC_GRV,   KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,     _______,         
        _______,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX,           
        _______,  _______,   _______,        _______,          _______,          _______, _______, _______
    ),

      /* 3: Symbol Layer
   * ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────────┐
   * │     │  _  │  +  │  {  │  }  │  |  │     │     │     │     │     │         │
   * ├─────┴┬────┴┬────┴┬────┴┬────┴┬────┴┬────┴┬────┴┬────┴┬────┴┬────┴┬────────┤
   * │      │  -  │  =  │  [  │  ]  │  \  │     │ DEL │ INS │     │     │        │
   * ├──────┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬─────┤
   * │         │     │     │     │     │     │     │     │     │     │     │     │
   * ├────────┬┴─────┴─┬───┴─┬───┴─────┴──┬──┴─────┴─────┴─┬───┴─┬───┴─┬───┴─────┤
   * │        │        │     │            │                │     │     │         │
   * └────────┴────────┴─────┴────────────┴────────────────┴─────┴─────┴─────────┘
   */
    [_SL] = LAYOUT(
        _______,  KC_UNDS, KC_PLUS,  KC_LCBR, KC_RCBR,  KC_PIPE, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  
        _______,  KC_MINS, KC_EQL,   KC_LBRC, KC_RBRC,  KC_BSLS, XXXXXXX, KC_DEL,  KC_INS,  XXXXXXX, XXXXXXX, XXXXXXX,           
        _______,  XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,           
        _______,  _______,  _______,          _______,           _______,          _______, _______, _______
    ),

        /* 4: Reset Layer
   * ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────────┐
   * │RESET│     │     │     │     │     │     │     │     │     │     │         │
   * ├─────┴┬────┴┬────┴┬────┴┬────┴┬────┴┬────┴┬────┴┬────┴┬────┴┬────┴┬────────┤
   * │      │     │     │     │     │     │     │     │     │     │     │        │
   * ├──────┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬──┴──┬─────┤
   * │         │     │     │     │     │     │     │     │     │     │     │     │
   * ├────────┬┴─────┴─┬───┴─┬───┴─────┴──┬──┴─────┴─────┴─┬───┴─┬───┴─┬───┴─────┤
   * │        │        │     │            │                │     │     │         │
   * └────────┴────────┴─────┴────────────┴────────────────┴─────┴─────┴─────────┘
   */
    [_RL] = LAYOUT(
        RESET,   XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   
        XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,           
        XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,           
        XXXXXXX, XXXXXXX, XXXXXXX,           XXXXXXX,           XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX
    )
};  
