/* Copyright 2019 ashlar 2021 peepeetee
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
#include "keymap.h"

#ifdef TAP_DANCE_ENABLE
enum {
    TD_ESC_CAPS,
    TD_A_B,
    TD_1_F1,
    TD_2_F2,
    TD_3_F3,
    TD_4_F4,
    TD_5_F5,
    TD_6_F6,
    TD_7_F7,
    TD_8_F8,
    TD_9_F9,
    TD_0_F10,
    TD_MINS_F11,
    TD_EQL_F12,
};

// Tap Dance definitions
qk_tap_dance_action_t tap_dance_actions[] = {
    // Tap once for Escape, twice for Caps Lock
    [TD_ESC_CAPS] = ACTION_TAP_DANCE_DOUBLE(KC_ESC, KC_CAPS),
    //tap once for a, twice for b
    [TD_A_B] = ACTION_TAP_DANCE_DOUBLE(KC_A, KC_B),
    [TD_1_F1] = ACTION_TAP_DANCE_DOUBLE(KC_1, KC_F1),
    [TD_2_F2] = ACTION_TAP_DANCE_DOUBLE(KC_2, KC_F2),
    [TD_3_F3] = ACTION_TAP_DANCE_DOUBLE(KC_3, KC_F3),
    [TD_4_F4] = ACTION_TAP_DANCE_DOUBLE(KC_4, KC_F4),
    [TD_5_F5] = ACTION_TAP_DANCE_DOUBLE(KC_5, KC_F5),
    [TD_6_F6] = ACTION_TAP_DANCE_DOUBLE(KC_6, KC_F6),
    [TD_7_F7] = ACTION_TAP_DANCE_DOUBLE(KC_7, KC_F7),
    [TD_8_F8] = ACTION_TAP_DANCE_DOUBLE(KC_8, KC_F8),
    [TD_9_F9] = ACTION_TAP_DANCE_DOUBLE(KC_9, KC_F9),
    [TD_0_F10] = ACTION_TAP_DANCE_DOUBLE(KC_0, KC_F10),
    [TD_MINS_F11] = ACTION_TAP_DANCE_DOUBLE(KC_MINS, KC_F11),
    [TD_EQL_F12] = ACTION_TAP_DANCE_DOUBLE(KC_EQL, KC_F12),
};
#endif


// // Defines names for use in layer keycodes and the keymap
 enum  layers {
     _BL,
     _RED_,
     _GREEN_,
     _BLUE_
 };



const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* 0: Main layer, swapped alt and GUI for Mac
   * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┬───┐
   * │GE │1 !│2 "│3 £│4 $│5 %│6 ^│7 &│8 *│9 (│0 )│- _│= +│Bksp   │Del│
   * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┼───┤
   * │Tab  │ Q │ W │ E │ R │ T │ Y │ U │ I │ O │ P │[ {│] }│Enter│HOM│
   * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐    ├───┤
   * │FnCaps│ A │ S │ D │ F │ G │ H │ J │ K │ L │; :│' @│# ~│    │PUp│
   * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴┬───┼───┤
   * │Sft │\ |│ Z │ X │ C │ V │ B │ N │ M │, <│. >│/ ?│Shift │Up │PDn│
   * ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴──┬┴──┬┴──┬───┼───┼───┤
   * │Ctrl│GUI │Alt │Space                   │Alt│Fn │   │Lft│Dwn│Rgt│
   * └────┴────┴────┴────────────────────────┴───┴───┴───┴───┴───┴───┘
   */

  /* 0: ISO qwerty */
  [_BL] = LAYOUT_iso(
    KC_CAPS,   KC_1,    KC_2,    KC_3,    KC_4,    KC_5,   KC_6,    KC_7,    KC_8,    KC_9,   KC_0,   KC_MINS, KC_EQL,  KC_BSPC, KC_DEL,  \
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_ENT, KC_HOME,  \
    KC_ESC, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_NUHS,         KC_PGUP, \
    KC_LSFT, KC_NUBS, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_UP,   KC_PGDN, \
    KC_LCTL, KC_LGUI, KC_LALT,                   KC_SPC,                             KC_RALT, MO(_RED_),         KC_LEFT, KC_DOWN, KC_RGHT  \

  ),


  /* 1: Locking arrow keys to WASD for when you need dedicated arrow keys
   * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┬───┐
   * │   │   │   │   │   │   │   │   │   │   │   │   │   │       │   │
   * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┼───┤
   * │     │   │Up │   │   │   │   │   │   │   │   │   │   │     │   │
   * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐    ├───┤
   * │      │Lft│Dwn│Rgt│   │   │   │   │   │   │   │   │   │    │   │
   * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴┬───┼───┤
   * │    │   │   │   │   │   │   │   │   │   │   │   │      │   │   │
   * ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴──┬┴──┬┴──┬───┼───┼───┤
   * │    │    │    │                        │   │   │   │   │   │   │
   * └────┴────┴────┴────────────────────────┴───┴───┴───┴───┴───┴───┘
   */

  [_RED_] = LAYOUT_iso(
    RESET, KC_F1, KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12, _______, _______, \
    _______, _______, KC_UP,   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  TO(0),  _______, \
    KC_VOLU, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______, _______, _______, _______, RGB_TOG, _______, _______, _______,          _______, \
    KC_VOLD, TO(_GREEN_), TO(_BLUE_), _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
    KC_MPLY, KC_MUTE, _______,                   _______,                            _______, _______,          _______, _______, _______  \
  ),


  /* 2: Fn layer
   * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┬───┐
   * │` ~│F1 │F2 │F3 │F4 │F5 │F6 │F7 │F8 │F9 │F10│F11│F12│       │   │
   * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┼───┤
   * │     │_AL│Up │   │   │   │   │   │PUp│PDn│PSc│SLk│Pau│     │   │
   * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┐    ├───┤
   * │      │Lft│Dwn│Rgt│   │   │Lft│Dwn│Up │Rgt│   │   │   │    │   │
   * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴┬───┼───┤
   * │    │   │_UL│   │   │   │   │   │   │Hm │End│   │      │VUp│   │
   * ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴──┬┴──┬┴──┬───┼───┼───┤
   * │    │    │    │                        │   │   │   │Mut│VDn│Ply│
   * └────┴────┴────┴────────────────────────┴───┴───┴───┴───┴───┴───┘
   */

  [_GREEN_] = LAYOUT_iso(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  \
    _______, KC_MS_ACCEL0, KC_MS_ACCEL1, KC_MS_ACCEL2, _______, _______, _______,  KC_PGUP, KC_PGDN, KC_PSCR,_______, _______, _______, TO(0),   _______, \
    _______, _______, _______, _______, _______, _______, KC_MS_LEFT, KC_MS_DOWN, KC_MS_UP,   KC_MS_RIGHT, KC_MS_BTN1, KC_MS_BTN2, _______,           _______, \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_HOME, KC_END,  _______, _______, _______, _______, \
    _______, _______, _______,                   _______,                            _______, _______,         _______, _______, _______  \
  ),


  /* 3: Locking layer for controlling the underglow
   * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┬───┐
   * │   │   │   │   │   │   │   │   │   │   │   │   │   │       │   │
   * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┼───┤
   * │     │   │   │   │   │   │   │   │   │   │   │   │   │     │   │
   * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┼───┤
   * │      │RTg│RMd│   │   │   │   │   │   │   │   │   │        │   │
   * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┼───┤
   * │    │   │   │RH+│RH-│RS+│RS-│RV+│RV-│   │   │   │      │   │   │
   * ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴──┬┴──┬┴──┬───┼───┼───┤
   * │    │    │    │                        │   │   │   │   │   │   │
   * └────┴────┴────┴────────────────────────┴───┴───┴───┴───┴───┴───┘
   */

  [_BLUE_] = LAYOUT_iso(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,TO(0),    _______,

    _______, RGB_TOG, RGB_MOD, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,           _______, \
    _______, _______, _______, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, _______, _______, _______, _______, _______, _______, \
    _______, _______, _______,                   _______,                            _______, _______,          _______, _______, _______  \
  )

  /*template
    [_UL] = LAYOUT_iso(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,TO(0),    _______,

    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,           _______, \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
    _______, _______, _______,                   _______,                            _______, _______,          _______, _______, _______  \
  )
  */
};

#ifdef _______
#undef _______
#define _______ {0, 0, 0}

const uint8_t PROGMEM ledmap[][DRIVER_LED_TOTAL][3] = {
    [_BL] = {
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______, \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,           _______, \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
    _______, _______, _______,                   _______,                            _______, _______,          _______, _______, _______  \
    },
    [_RED_] = {
    RED, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______, \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,           _______, \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
    _______, _______, _______,                   RED,                            _______, _______,          _______, _______, _______  \
    
    //    PURPLE, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______,   _______,
    //    GREEN,   BLUE, {0, 0, 255}, PURPLE, AZURE, _______, {0, 0, 255}, {0, 0, 255}, {0, 0, 255}, _______, _______, _______, _______,  _______, _______,
    //    RED,    BLUE, {0, 0, 1}, PURPLE, AZURE, _______, {0, 0, 255}, {0, 0, 255}, {0, 0, 255}, _______, _______, _______,              _______,  _______,
    //    _______,      _______, _______, _______, _______, RED, {0, 0, 255}, {0, 0, 255}, {0, 0, 255}, _______, _______,     _______,   _______,  _______,
    //    _______,   _______,   _______,                    _______,                         _______, _______,              _______, _______,  _______
    },
        [_GREEN_] = {
    GREEN, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
      _______,  _______, \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,           _______, \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
    _______, _______, _______,                  GREEN,                            _______, _______,          _______, _______, _______  \
    },
    [_BLUE_] = {
    BLUE, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
      _______,  _______, \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,           _______, \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
    _______, _______, _______,                  BLUE,                            _______, _______,          _______, _______, _______  \
    },




};

#undef _______
#define _______ KC_TRNS
#endif



void keyboard_post_init_user(void) {
  // Call the post init code.
    //dfa_state = 0; // ENGLISH
    //debug_enable=true;
    //debug_matrix=true;
    //rgblight_disable_noeeprom();
}


/*bool process_record_user(uint16_t keycode, keyrecord_t *record) {
#ifdef CONSOLE_ENABLE
    uprintf("KL: kc: 0x%04X, col: %u, row: %u, pressed: %b, time: %u, interrupt: %b, count: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed, record->event.time, record->tap.interrupted, record->tap.count);
#endif
  switch (keycode) {
  
    case KC_DELETE:
      if (record->event.pressed) {
                dfa_state = 0;
    } else {
        // Do something else when release
      }
      return false; // Skip all further processing of this key
    case KC_SPC:
      if (record->event.pressed) {
          if ((get_mods() & MOD_BIT(KC_LGUI)) == MOD_BIT(KC_LGUI)){
              if(dfa_state == 3){
                  dfa_state = 0;
              } else {
                  dfa_state = dfa_state + 1;
              }
          }
    } else {
        // Do something else when release
      }
      return true; // Continue execution


    case KC_HOME:
      if (record->event.pressed) {
          switch(dfa_state){
            case 0 :{
                return false;
            }
            case 1 :{
                tap_code16(G(KC_SPC));
                wait_ms(100);
                tap_code16(G(KC_SPC));
                wait_ms(100);
                tap_code16(G(KC_SPC));
                dfa_state = 0;
                return false;
            }
            case 2 :{
                tap_code16(G(KC_SPC));
                wait_ms(100);
                tap_code16(G(KC_SPC));
                dfa_state = 0;
                return false;
            }
            case 3 :{
                tap_code16(G(KC_SPC));
                dfa_state = 0;
                return false;
            }
          }

        // Do something when pressed
      } else {
        // Do something else when release
      }
      return false; // Skip all further processing of this key
      */
    // case KC_PGUP:
    //   if (record->event.pressed) {
    //       switch(dfa_state){
    //         case 0 :{
    //             tap_code16(G(KC_SPC));
    //             dfa_state = 1;
    //             return false;
    //         }
    //         case 1 :{
    //             return false;
    //         }
    //         case 2 :{
    //             tap_code16(G(KC_SPC));
    //             wait_ms(100);
    //             tap_code16(G(KC_SPC));
    //             wait_ms(100);
    //             tap_code16(G(KC_SPC));
    //             dfa_state = 1;
    //             return false;
    //         }
    //         case 3 :{
    //             tap_code16(G(KC_SPC));
    //             wait_ms(100);
    //             tap_code16(G(KC_SPC));
    //             dfa_state = 1;
    //             return false;
    //         }
    //       }
    //     // Do something when pressed
    //   } else {
    //     // Do something else when release
    //   }
    //   return false; // Skip all further processing of this key
    // case KC_PGDOWN:
    //   if (record->event.pressed) {
    //       switch(dfa_state){
    //         case 0 :{
    //             tap_code16(G(KC_SPC));
    //             wait_ms(100);
    //             tap_code16(G(KC_SPC));
    //             dfa_state = 2;
    //             return false;
    //         }
    //         case 1 :{
    //             tap_code16(G(KC_SPC));
    //             dfa_state = 2;
    //             return false;
    //         }
    //         case 2 :{
    //             return false;
    //         }
    //         case 3 :{
    //             tap_code16(G(KC_SPC));
    //             wait_ms(100);
    //             tap_code16(G(KC_SPC));
    //             wait_ms(100);
    //             tap_code16(G(KC_SPC));
    //             dfa_state = 2;
    //             return false;
    //         }
    //       }
    //     // Do something when pressed
    //   } else {
    //     // Do something else when release
    //   }
    //   return false; // Skip all further processing of this key
    // case KC_END:
    //   if (record->event.pressed) {
    //       switch(dfa_state){
    //         case 0 :{
    //             tap_code16(G(KC_SPC));
    //             wait_ms(100);
    //             tap_code16(G(KC_SPC));
    //             wait_ms(100);
    //             tap_code16(G(KC_SPC));
    //             dfa_state = 3;
    //             return false;
    //         }
    //         case 1 :{
    //             tap_code16(G(KC_SPC));
    //             wait_ms(100);
    //             tap_code16(G(KC_SPC));
    //             dfa_state = 3;
    //             return false;
    //         }
    //         case 2 :{
    //             tap_code16(G(KC_SPC));
    //             dfa_state = 3;
    //             return false;
    //         }
    //         case 3 :{
    //             return false;
    //         }
    //       }
    //     // Do something when pressed
    //   } else {
    //     // Do something else when release
    //   }
    //   return false; // Skip all further processing of this key
            //case RGB_TOG:
            /*if (record->event.pressed) {
              switch (rgb_matrix_get_flags()) {
                case LED_FLAG_ALL: {
                    rgb_matrix_set_flags(LED_FLAG_KEYLIGHT | LED_FLAG_MODIFIER | LED_FLAG_INDICATOR);
                    rgb_matrix_set_color_all(0, 0, 0);
                  }
                  break;
                case (LED_FLAG_KEYLIGHT | LED_FLAG_MODIFIER | LED_FLAG_INDICATOR): {
                    rgb_matrix_set_flags(LED_FLAG_UNDERGLOW);
                    rgb_matrix_set_color_all(0, 0, 0);
                  }
                  break;
                case LED_FLAG_UNDERGLOW: {
                    rgb_matrix_set_flags(LED_FLAG_NONE);
                    rgb_matrix_disable_noeeprom();
                  }
                  break;
                default: {
                    rgb_matrix_set_flags(LED_FLAG_ALL);
                    rgb_matrix_enable_noeeprom();
                  }
                  break;
              }
            }
            return false;
    default:
      return true; // Process all other keycodes normally
  }
}*/
/*
void set_layer_color(int layer) {
    //if (layer == 0) { return; }
    for (int i = 0; i < DRIVER_LED_TOTAL; i++) {
        HSV hsv = {
            .h = pgm_read_byte(&ledmap[layer][i][0]),
            .s = pgm_read_byte(&ledmap[layer][i][1]),
            .v = pgm_read_byte(&ledmap[layer][i][2]),
        };
        if (hsv.h || hsv.s || hsv.v) {
            RGB rgb = hsv_to_rgb(hsv);
            float f = (float)rgb_matrix_config.hsv.v / UINT8_MAX;
            rgb_matrix_set_color(i, f * rgb.r, f * rgb.g, f * rgb.b);
        } else if (layer == 0) {
            // Only deactivate non-defined key LEDs at layers other than FN. Because at FN we have RGB adjustments and need to see them live.
            // If the values are all false then it's a transparent key and deactivate LED at this layer
            if(i==30) continue;//ignore if  key=capslock
            rgb_matrix_set_color(i, 0, 0, 0);
        }
    }

void rgb_matrix_indicators_user(void) {

    led_t host_leds = host_keyboard_led_state();
    if (host_leds.caps_lock) {
        rgb_matrix_set_color(30, 0xFF, 0xFF, 0xFF);
        //rgb_matrix_set_color(30, 0x0, 0x0, 0x0);

    } else {
        rgb_matrix_set_color(30, 0x0, 0x0, 0x0);
    }
        set_layer_color(get_highest_layer(layer_state));

}*/

