/* Copyright 2020 pastapojken
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

#include "nack.h"

// Interrupt bools
bool lshift = false, ralt = false;

// Number of items that are saved in prev_kcs
uint8_t prev_indx = 0;
// Used to save the last 6 actual keycodes activated by frankenkeycodes
uint16_t prev_kcs[6] = {0, 0, 0, 0, 0, 0};

/*
Used to add a keycode to a prev_kcs to remember it.
When full the last code gets discarded and replaced by
the new one.
*/
void add_to_prev(uint16_t kc){
  for (int i=0; i<prev_indx; i++){
    if (kc == prev_kcs[i])
      return;
  }
  if (prev_indx == 6){
    for (int i=5; i>0; i--){
      prev_kcs[i] = prev_kcs[i-1];
    }
    prev_kcs[0] = kc;
  } else {
    prev_kcs[prev_indx] = kc;
    prev_indx++;
  }
}

/*
Unregisters all codes saved in prev_kcs and resets prev_indx.
gets called on multiple occasions mainly when shift is released
and when frankenkeycodes are pressed. Prevents output of
wrong characters when really specific key combinations
that would never occur during normal usage are pressed.
*/
void unreg_prev(void){
  if (prev_indx == 0)
    return;
  for (int i=0; i<prev_indx; i++){
    unregister_code(prev_kcs[i]);
  }
  prev_indx = 0;
}

// Interrupts all timers
void timer_timeout(void){
    timer_timeout_keymap();
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case CK_LSFT:
          if(record->event.pressed) {
            unregister_code(KC_LSFT);
            register_code(KC_LSFT);
            lshift = true;
          } else {
            unreg_prev();
            unregister_code(KC_LSFT);
            lshift = false;
          }
          return false;
        case CK_RALT:
          if(record->event.pressed) {
            unregister_code(KC_RALT);
            register_code(KC_RALT);
            ralt = true;
          } else {
            unreg_prev();
            unregister_code(KC_RALT);
            ralt = false;
          }
          return false;
        case CK_BSPC_DEL:
            RALT_NO(KC_BSPC,KC_DEL);
            break;
        case CK_UP_PGUP:
            RALT_NO(KC_UP,KC_PGUP);
            break;
        case CK_DOWN_PGDOWN:
            RALT_NO(KC_DOWN,KC_PGDOWN);
            break;
        case CK_LEFT_HOME:
            RALT_NO(KC_LEFT,KC_HOME);
            break;
        case CK_RIGHT_END:
            RALT_NO(KC_RIGHT,KC_END);
            break;
        default:
          if(record->event.pressed) {
            timer_timeout();
            if (lshift)
              register_code(KC_LSFT);
            else
              unregister_code(KC_LSFT);
            
            if (ralt)
              register_code(KC_ALGR);
            else
              unregister_code(KC_ALGR);
          }
        return process_record_keymap(keycode, record);
    }
    return true;
}

#ifdef RGB_MATRIX_ENABLE
led_config_t g_led_config = { {
  // Key Matrix to LED Index
  {   0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 },
  {  13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25 },
  {  26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38 },
  {  39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51 }
}, {
  // LED Index to Physical Position
  { 0, 0 }, { 19,  0 }, { 38,  0 }, { 57,  0 }, { 76,  0 }, { 95, 0 }, { 114,  0 }, { 133,  0 }, { 152,  0 }, { 171,  0 }, { 190, 0 }, { 209,  0 }, { 223,  0 },
  { 0, 21 }, { 19,  21 }, { 38,  21 }, { 57,  21 }, { 76,  21 }, { 95, 21 }, { 114,  21 }, { 133,  21 }, { 152,  21 }, { 171,  21 }, { 190, 21 }, { 209,  21 }, { 223,  21 },
  { 0, 42 }, { 19,  42 }, { 38,  42 }, { 57,  42 }, { 76,  42 }, { 95, 42 }, { 114,  42 }, { 133,  42 }, { 152,  42 }, { 171,  42 }, { 190, 42 }, { 209,  42 }, { 223,  42 },
  { 0, 63 }, { 19,  63 }, { 38,  63 }, { 57,  63 }, { 76,  63 }, { 95, 63 }, { 114,  63 }, { 133,  63 }, { 152,  63 }, { 171,  63 }, { 190, 63 }, { 209,  63 }, { 223,  63 }
}, {
  // LED Index to Flag
  4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
  4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
  4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
  4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4
} };
#endif

__attribute__((weak))
bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
  return true;
}

__attribute__((weak))
void timer_timeout_keymap(void){
}
