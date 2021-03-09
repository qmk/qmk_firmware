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
   *  ,-------------------------------------------
   *  | XXXX XXXX Ctrl/Esc Q    W    E    R     T 
   *  | XXXX XXXX Shft/Tab A    S    D    F     G 
   *  | XXXX XXXX XXXX     Z    X    C    V     B 
   *  | XXXX XXXX XXXX  XXXX XXXX XXXX XXXX  XXXX 
   *  | XXXX XXXX XXXX  XXXX XXXX XXXX MO(1) Spce 
   *  | XXXX XXXX XXXX  XXXX XXXX XXXX XXXX  XXXX 
   *  `-------------------------------------------
   *  Slave Side (USB Cable Not Connected Side)
   *  ,---------------------------------------------
   *  |    Y    U     I    O    P GUI/Del XXXX XXXX 
   *  |    H    J     K    L    - Alt/BS  XXXX XXXX 
   *  |    N    M     ,    .    / XXXX    XXXX XXXX 
   *  | XXXX XXXX  XXXX XXXX XXXX XXXX    XXXX XXXX 
   *  | Entr MO(2) XXXX XXXX XXXX XXXX    XXXX XXXX 
   *  | XXXX XXXX  XXXX XXXX XXXX XXXX    XXXX XXXX 
   *  `---------------------------------------------
   */

  [0] = LAYOUT( /* Base */ 
    XXXXXXX,  XXXXXXX,  MT(MOD_LCTL, KC_ESC), KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     
    XXXXXXX,  XXXXXXX,  MT(MOD_LSFT, KC_TAB), KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     
    XXXXXXX,  XXXXXXX,  XXXXXXX,              KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     
    XXXXXXX,  XXXXXXX,  XXXXXXX,              XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  
    XXXXXXX,  XXXXXXX,  XXXXXXX,              XXXXXXX,  XXXXXXX,  XXXXXXX,  MO(1),    KC_SPC,   
    XXXXXXX,  XXXXXXX,  XXXXXXX,              XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  

    KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     MT(MOD_LGUI, KC_DEL),  XXXXXXX,  XXXXXXX,  
    KC_H,     KC_J,     KC_K,     KC_L,     KC_MINS,  MT(MOD_LALT, KC_BSPC), XXXXXXX,  XXXXXXX,  
    KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  XXXXXXX,               XXXXXXX,  XXXXXXX,  
    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,               XXXXXXX,  XXXXXXX,  
    KC_ENT,   MO(2),    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,               XXXXXXX,  XXXXXXX,  
    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,               XXXXXXX,  XXXXXXX   
  ),

  /* Lower Layer
   *  Master Side (USB Cable Connected Side)
   *  ,-----------------------------------------
   *  | XXXX XXXX ____    !    @    #    $    % 
   *  | XXXX XXXX ____ XXXX    _    +    |    ~ 
   *  | XXXX XXXX XXXX XXXX    -    =    \    ` 
   *  | XXXX XXXX XXXX XXXX XXXX XXXX XXXX XXXX 
   *  | XXXX XXXX XXXX XXXX XXXX XXXX ____ ____ 
   *  | XXXX XXXX XXXX XXXX XXXX XXXX XXXX XXXX 
   *  `-----------------------------------------
   *  Slave Side (USB Cable Not Connected Side)
   *  ,-----------------------------------------
   *  |    ^    &    *    (    ) ____ XXXX XXXX 
   *  |    :    "    >    {    } ____ XXXX XXXX 
   *  |    ;    '    <    [    ] XXXX XXXX XXXX 
   *  | XXXX XXXX XXXX XXXX XXXX XXXX XXXX XXXX 
   *  | ____ MO(3)XXXX XXXX XXXX XXXX XXXX XXXX 
   *  | XXXX XXXX XXXX XXXX XXXX XXXX XXXX XXXX 
   *  `-----------------------------------------
   */

  [1] = LAYOUT(
    XXXXXXX,  XXXXXXX,  _______,  KC_EXLM,  KC_AT,    KC_HASH,  KC_DLR,   KC_PERC,  
    XXXXXXX,  XXXXXXX,  _______,  XXXXXXX,  KC_UNDS,  KC_PLUS,  KC_PIPE,  KC_TILD,  
    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  KC_MINS,  KC_EQL,   KC_BSLS,  KC_GRV,   
    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  
    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  _______,  _______,  
    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  

    KC_CIRC,  KC_AMPR,  KC_ASTR,  KC_LPRN,  KC_RPRN,  _______,  XXXXXXX,  XXXXXXX,  
    KC_COLN,  KC_DQUO,  KC_GT,    KC_LCBR,  KC_RCBR,  _______,  XXXXXXX,  XXXXXXX,  
    KC_SCLN,  KC_QUOT,  KC_LT,    KC_LBRC,  KC_RBRC,  XXXXXXX,  XXXXXXX,  XXXXXXX,  
    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  
    _______,  MO(3),    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  
    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX   
  ),

  /* Raise Layer
   *  Master Side (USB Cable Connected Side)
   *  ,-----------------------------------------
   *  | XXXX XXXX PgUp   F1   F2   F3   F4   F5 
   *  | XXXX XXXX PgDn    1    2    3    4    5 
   *  | XXXX XXXX XXXX  F11  F12 XXXX XXXX XXXX 
   *  | XXXX XXXX XXXX XXXX XXXX XXXX XXXX XXXX 
   *  | XXXX XXXX XXXX XXXX XXXX XXXX ____ ____ 
   *  | XXXX XXXX XXXX XXXX XXXX XXXX XXXX XXXX 
   *  `-----------------------------------------
   *  Slave Side (USB Cable Not Connected Side)
   *  ,-----------------------------------------
   *  |   F6   F7   F8   F9  F10 ____ XXXX XXXX 
   *  |    6    7    8    9    0 ____ XXXX XXXX 
   *  | XXXX Left Down   Up Rght XXXX XXXX XXXX 
   *  | XXXX XXXX XXXX XXXX XXXX XXXX XXXX XXXX 
   *  | ____ ____ XXXX XXXX XXXX XXXX XXXX XXXX 
   *  | XXXX XXXX XXXX XXXX XXXX XXXX XXXX XXXX 
   *  `-----------------------------------------
   */

  [2] = LAYOUT(
    XXXXXXX,  XXXXXXX,  KC_PGUP,  KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    
    XXXXXXX,  XXXXXXX,  KC_PGDN,  KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     
    XXXXXXX,  XXXXXXX,  XXXXXXX,  KC_F11,   KC_F12,   XXXXXXX,  XXXXXXX,  XXXXXXX,  
    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  
    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  _______,  _______,  
    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  

    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   _______,  XXXXXXX,  XXXXXXX,  
    KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     _______,  XXXXXXX,  XXXXXXX,  
    XXXXXXX,  KC_LEFT,  KC_DOWN,  KC_UP,    KC_RGHT,  XXXXXXX,  XXXXXXX,  XXXXXXX,  
    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  
    _______,  _______,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  
    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX   
  ),

  [3] = LAYOUT(
    XXXXXXX,  XXXXXXX,  XXXXXXX,  RGB_TOG,  RGB_MOD,  XXXXXXX,  XXXXXXX,  EEP_RST,  
    XXXXXXX,  XXXXXXX,  XXXXXXX,  RGB_HUI,  RGB_SAI,  RGB_VAI,  XXXXXXX,  RESET,    
    XXXXXXX,  XXXXXXX,  XXXXXXX,  RGB_HUD,  RGB_SAD,  RGB_VAD,  XXXXXXX,  XXXXXXX,  
    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  
    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  
    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  

    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  
    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  
    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  
    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  
    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  
    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX   
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
