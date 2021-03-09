/* Copyright 2020 e3w2q
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

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
  SEND_00 = SAFE_RANGE,
  SEND_000
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* Default Layer
   *  Master Side (USB Cable Connected Side)
   *  ,-------------------------------
   *  |  Esc    Q    W    E    R    T 
   *  |  Tab    A    S    D    F    G 
   *  | Caps    Z    X    C    V    B 
   *  | Shft Ctrl  Alt  GUI MO(1)Spce 
   *  | XXXX XXXX XXXX XXXX XXXX XXXX 
   *  | XXXX XXXX XXXX XXXX XXXX XXXX 
   *  | XXXX XXXX XXXX XXXX XXXX XXXX 
   *  | XXXX XXXX XXXX XXXX XXXX XXXX 
   *  `-------------------------------
   *  Slave Side (USB Cable Not Connected Side)
   *  ,-------------------------------
   *  |    Y    U    I    O    P   BS 
   *  |    H    J    K    L    ;    " 
   *  |    N    M    ,    .    / Entr 
   *  | Spce MO(2)Left Down   Up Rght 
   *  | XXXX XXXX XXXX XXXX XXXX XXXX 
   *  | XXXX XXXX XXXX XXXX XXXX XXXX 
   *  | XXXX XXXX XXXX XXXX XXXX XXXX 
   *  | XXXX XXXX XXXX XXXX XXXX XXXX 
   *  `-------------------------------
   */

  [0] = LAYOUT( /* Base */ 
    KC_ESC,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     
    KC_TAB,   KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     
    KC_CAPS,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     
    KC_LSFT,  KC_LCTL,  KC_LALT,  KC_LGUI,  MO(1),    KC_SPC,   
    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  
    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  
    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  
    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  

    KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_BSPC,  
    KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,  
    KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_ENT,   
    KC_SPC,   MO(2),    KC_LEFT,  KC_DOWN,  KC_UP,    KC_RGHT   
    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  
    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  
    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  
    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX   
  ),

  /* Lower Layer
   *  Master Side (USB Cable Connected Side)
   *  ,-------------------------------
   *  |    ~    !    @    #    $    % 
   *  |   F1   F2   F3   F4   F5   F6 
   *  |   F7   F8   F9  F10  F11  F12 
   *  | ____ ____ ____ ____ ____ ____ 
   *  | XXXX XXXX XXXX XXXX XXXX XXXX 
   *  | XXXX XXXX XXXX XXXX XXXX XXXX 
   *  | XXXX XXXX XXXX XXXX XXXX XXXX 
   *  | XXXX XXXX XXXX XXXX XXXX XXXX 
   *  `-------------------------------
   *  Slave Side (USB Cable Not Connected Side)
   *  ,-------------------------------
   *  |    ^    &    *    (    )  Del 
   *  | XXXX    _    +    {    }    | 
   *  | XXXX XXXX XXXX XXXX XXXX XXXX 
   *  | ____ MO(3)____ ____ ____ ____ 
   *  | XXXX XXXX XXXX XXXX XXXX XXXX 
   *  | XXXX XXXX XXXX XXXX XXXX XXXX 
   *  | XXXX XXXX XXXX XXXX XXXX XXXX 
   *  | XXXX XXXX XXXX XXXX XXXX XXXX 
   *  `-------------------------------
   */

  [1] = LAYOUT(
    KC_TILD,  KC_EXLM,  KC_AT,    KC_HASH,  KC_DLR,   KC_PERC,  
    KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    
    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   
    _______,  _______,  _______,  _______,  _______,  _______,  
    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  
    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  
    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  
    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  

    KC_CIRC,  KC_AMPR,  KC_ASTR,  KC_LPRN,  KC_RPRN,  KC_DEL,   
    XXXXXXX,  KC_UNDS,  KC_PLUS,  KC_LCBR,  KC_RCBR,  KC_PIPE,  
    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  
    _______,  MO(3),    _______,  _______,  _______,  _______,  
    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  
    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  
    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  
    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX   
  ),

  /* Raise Layer
   *  Master Side (USB Cable Connected Side)
   *  ,-------------------------------
   *  |    `    1    2    3    4    5 
   *  |   F1   F2   F3   F4   F5   F6 
   *  |   F7   F8   F9  F10  F11  F12 
   *  | ____ ____ ____ ____ ____ ____ 
   *  | XXXX XXXX XXXX XXXX XXXX XXXX 
   *  | XXXX XXXX XXXX XXXX XXXX XXXX 
   *  | XXXX XXXX XXXX XXXX XXXX XXXX 
   *  | XXXX XXXX XXXX XXXX XXXX XXXX 
   *  `-------------------------------
   *  Slave Side (USB Cable Not Connected Side)
   *  ,-------------------------------
   *  |    6    7    8    9    0  Del 
   *  | XXXX    -    =    [    ]    \ 
   *  | XXXX XXXX XXXX XXXX XXXX XXXX 
   *  | ____ ____ ____ ____ ____ ____ 
   *  | XXXX XXXX XXXX XXXX XXXX XXXX 
   *  | XXXX XXXX XXXX XXXX XXXX XXXX 
   *  | XXXX XXXX XXXX XXXX XXXX XXXX 
   *  | XXXX XXXX XXXX XXXX XXXX XXXX 
   *  `-------------------------------
   */

  [2] = LAYOUT(
    KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     
    KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    
    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   
    _______,  _______,  _______,  _______,  _______,  _______,  
    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  
    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  
    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  
    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  

    KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_DEL,   
    XXXXXXX,  KC_MINS,  KC_EQL,   KC_LBRC,  KC_RBRC,  KC_BSLS,  
    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  
    _______,  _______,  _______,  _______,  _______,  _______,  
    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  
    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  
    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  
    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX   
  ),

  [3] = LAYOUT(
    RGB_TOG,  RGB_MOD,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  
    RGB_HUI,  RGB_SAI,  RGB_VAI,  XXXXXXX,  XXXXXXX,  XXXXXXX,  
    RGB_HUD,  RGB_SAD,  RGB_VAD,  XXXXXXX,  XXXXXXX,  XXXXXXX,  
    _______,  _______,  _______,  _______,  _______,  _______,  
    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  
    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  
    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  
    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  

    EEP_RST,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  
    RESET,    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  
    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  
    _______,  _______,  _______,  _______,  _______,  _______,  
    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  
    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  
    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  
    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX   
  ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case SEND_00:
      if (record->event.pressed) {
        // when keycode SEND_00 is pressed
        SEND_STRING("00");
      } else {
        // when keycode SEND_00 is released
      }
      break;
    case SEND_000:
      if (record->event.pressed) {
        // when keycode SEND_000 is pressed
        //SEND_STRING("000" SS_TAP(X_ENTER));
        SEND_STRING("000");
      } else {
        // when keycode SEND_000 is released
      }
      break;
  }
  return true;
}

void matrix_init_user(void) {

}

void matrix_scan_user(void) {

}

void led_set_user(uint8_t usb_led) {

}
