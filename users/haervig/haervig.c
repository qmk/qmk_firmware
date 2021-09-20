/*
Copyright 2021 Jakob Hærvig <jakob.haervig@gmail.com>

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

#include "haervig.h"

#ifdef DANISH_ENABLE
// These indicate if left and right shift are physically pressed
bool lshift = false;
bool rshift = false;

// Interrupt and times for space cadet shift
bool lshiftp = false;
bool rshiftp = false;
uint16_t lshift_timer = 0;
uint16_t rshift_timer = 0;

// Number of items that are saved in prev_kcs
uint8_t prev_indx = 0;
// Used to save the last 6 actual keycodes activated by frankenkeycodes
uint16_t prev_kcs[6] = {0, 0, 0, 0, 0, 0};

// If true the deadkey characters grave and circonflexe are not automatically escaped
bool esct = false;

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
#endif

// Interrupt and times for Nav/Esc
bool navesc = false;
uint16_t navesc_timer = 0;

// Interrupts all timers
void timer_timeout(void){
  #ifdef DANISH_ENABLE
  lshiftp = false;
  rshiftp = false;
  #endif
  navesc = false;
  timer_timeout_keymap();
}

__attribute__((weak))
void timer_timeout_keymap(void){
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
  case KC_LGUI:
  case KC_RGUI:
    if (record->event.pressed)
      timer_timeout();
    return true;
  case CU_NAV:
    if(record->event.pressed) {
      navesc = true;
      navesc_timer = timer_read();
      layer_on(_NAV);
    } else {
      if (timer_elapsed(navesc_timer) < TAPPING_TERM && navesc) {
        tap_code(KC_ESC);
      }
      layer_off(_NAV);
    }
    return false;

  #ifdef DANISH_ENABLE
  case CU_LSFT:
    if(record->event.pressed) {
      lshiftp = true;
      lshift_timer = timer_read();
      unregister_code(KC_LSFT);
      register_code(KC_LSFT);
      lshift = true;
    } else {
      if (timer_elapsed(lshift_timer) < TAPPING_TERM && lshiftp) {
        register_code(KC_LSFT);
        tap_code(KC_8);
        unregister_code(KC_LSFT);
      }
      unreg_prev();
      if (!rshift)
        unregister_code(KC_LSFT);
      lshift = false;
    }
    return false;
  case CU_RSFT:
    if(record->event.pressed) {
      rshiftp = true;
      rshift_timer = timer_read();
      unregister_code(KC_LSFT);
      register_code(KC_LSFT);
      rshift = true;
    } else {
      if (timer_elapsed(rshift_timer) < TAPPING_TERM && rshiftp) {
        register_code(KC_LSFT);
        tap_code(KC_9);
        unregister_code(KC_LSFT);
      }
      unreg_prev();
      if (!lshift)
        unregister_code(KC_LSFT);
      rshift = false;
    }
    return false;
  case CU_COMM:
    SHIFT_NO(DK_COMM, KC_GRV)
  case CU_DOT:
    SHIFT_NORM(DK_DOT, KC_GRV)
  case CU_SLSH:
    SHIFT_ALL(DK_7, KC_MINS)
  case CU_SCLN:
    SHIFT_ALL(DK_COMM, DK_DOT)
  case CU_QUOT:
    SHIFT_NORM(DK_QUOT, DK_2)
  case CU_2:
    NORM_ALGR(DK_2, KC_NUHS)
  case CU_4:
    if (record->event.pressed) { \
      timer_timeout(); \
      if (lshift || rshift) { \
        register_code(KC_LSFT); \
        register_code(KC_ALGR); \
        unregister_code(KC_3); \
        tap_code(KC_3); \
        unregister_code(KC_3); \
      } else { \
        unregister_code(KC_4); \
        tap_code(KC_4); \
      } \
      unregister_code(KC_ALGR); \
      unregister_code(KC_LSFT); \
    } \
    return false;
  case CU_6:
    SHIFT_NORM(DK_6, KC_RBRC)
  case CU_7:
    SHIFT_NORM(DK_7, DK_6)
  case CU_8:
    SHIFT_NORM(DK_8, KC_NUHS)
  case CU_9:
    SHIFT_NORM(DK_9, DK_8)
  case CU_0:
    SHIFT_NORM(DK_0, DK_9)
  case CU_MINS:
    SHIFT_NORM(KC_SLSH, KC_SLSH)
  case CU_EQL:
    SHIFT_SWITCH(DK_0, DK_PLUS)
  case CU_BSPC:
    SHIFT_NO(KC_BSPC, KC_DEL)
  case CU_LBRC:
    NORM_ALGRSHIFT(DK_8, DK_8)
  case CU_RBRC:
    NORM_ALGRSHIFT(DK_9, DK_9)
  case CU_BSLS:
    ALGR_SWITCH(DK_7, DK_I)
  case KC_LCTL:
  case KC_RCTL:
    if(!record->event.pressed) {
      timer_timeout();
      unregister_code(KC_Z);
      unregister_code(KC_Y);
    }
    return true;
  #endif

  default:
    if(record->event.pressed) {
      timer_timeout();

      #ifdef DANISH_ENABLE
      if (lshift || rshift)
        register_code(KC_LSFT);
      else
        unregister_code(KC_LSFT);
      #endif

    }
    return process_record_keymap(keycode, record);
  }
}

__attribute__((weak))
bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
  return true;
}
