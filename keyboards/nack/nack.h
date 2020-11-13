/* Copyright 2020 pastapojken <pastapojken@gmail.com>
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

#pragma once

#include "quantum.h"

#define LAYOUT( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k10, k11, k12,\
    k13, k14, k15, k16, k17, k18, k19, k20, k21, k22, k23, k24, k25,\
    k26, k27, k28, k29, k30, k31, k32, k33, k34, k35, k36, k37, k38,\
    k39, k40, k41, k42, k43, k44, k45, k46, k47, k48, k49, k50, k51\
) \
{ \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k10, k11, k12 },\
    { k13, k14, k15, k16, k17, k18, k19, k20, k21, k22, k23, k24, k25 },\
    { k26, k27, k28, k29, k30, k31, k32, k33, k34, k35, k36, k37, k38 },\
    { k39, k40, k41, k42, k43, k44, k45, k46, k47, k48, k49, k50, k51 },\
}

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
    CK_LSFT = SAFE_RANGE,   // Shift
    CK_RALT,                // AltGr
    CK_BSPC_DEL,            // Backspace or Del (if pressed with CK_LSFT or CK_RALT)
    CK_UP_PGUP,             // Up or PgUp (if pressed with CK_LSFT or CK_RALT)
    CK_DOWN_PGDOWN,         // Down or PgDown (if pressed with CK_LSFT or CK_RALT)
    CK_LEFT_HOME,           // Left or Home (if pressed with CK_LSFT or CK_RALT)
    CK_RIGHT_END,           // Right or End (if pressed with CK_LSFT or CK_RALT)
    
    NEW_SAFE_RANGE
};

extern bool lshift, ralt;
void add_to_prev(uint16_t kc);
void unreg_prev(void);

void timer_timeout(void);
void timer_timeout_keymap(void);
bool process_record_keymap(uint16_t keycode, keyrecord_t *record);
bool process_record_user(uint16_t keycode, keyrecord_t *record);

/*
Templates for Keys, with custom shifted and non shifted Characters
Heavily based off of SpacebarRacecar's userspace
*/

// Normal shift status
#define SHIFT_NORM(kc1, kc2) \
if (record->event.pressed) { \
  timer_timeout(); \
  if (lshift) { \
    register_code(KC_LSFT); \
    unregister_code(kc2); \
    register_code(kc2); \
    add_to_prev(kc2); \
  } else { \
    unregister_code(KC_LSFT); \
    unregister_code(kc1); \
    register_code(kc1); \
  } \
} else { \
  unregister_code(kc1); \
  unregister_code(kc2); \
} \
return false;

// Always shifted
#define SHIFT_ALL(kc1, kc2) \
if (record->event.pressed) { \
  timer_timeout(); \
  register_code(KC_LSFT); \
  if (lshift) { \
    unregister_code(kc2); \
    register_code(kc2); \
    add_to_prev(kc2); \
  } else { \
    unregister_code(kc1); \
    register_code(kc1); \
    add_to_prev(kc1); \
  } \
} else { \
  unregister_code(kc1); \
  unregister_code(kc2); \
  unreg_prev(); \
  if (lshift) \
    register_code(KC_LSFT); \
  else \
    unregister_code(KC_LSFT); \
} \
return false;

// Never shifted
#define SHIFT_NO(kc1, kc2) \
if (record->event.pressed) { \
  timer_timeout(); \
  unregister_code(KC_LSFT); \
  if (lshift) { \
    unregister_code(kc2); \
    register_code(kc2); \
    add_to_prev(kc2); \
  } else { \
    unregister_code(kc1); \
    register_code(kc1); \
  } \
} else { \
  unregister_code(kc1); \
  unregister_code(kc2); \
  unreg_prev(); \
  if (lshift) \
    register_code(KC_LSFT); \
  else \
    unregister_code(KC_LSFT); \
} \
return false;

//Never RALT
#define RALT_NO(kc1, kc2) \
if (record->event.pressed) { \
  timer_timeout(); \
  unregister_code(KC_RALT); \
  if (ralt) { \
    unregister_code(kc2); \
    register_code(kc2); \
    add_to_prev(kc2); \
  } else { \
    unregister_code(kc1); \
    register_code(kc1); \
  } \
} else { \
  unregister_code(kc1); \
  unregister_code(kc2); \
  unreg_prev(); \
  if (ralt) \
    register_code(KC_RALT); \
  else \
    unregister_code(KC_RALT); \
} \
return false;

