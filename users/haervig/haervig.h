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

#include "quantum.h"
#include "keymap_danish.h"

enum userspace_layers {
  _DEADKEY = 14,            // Change if more than 16 layers are required
  _NAV
};

enum userspace_custom_keycodes {
  //CU_GAME = SAFE_RANGE,     // Toggle game mode on/off
  CU_NAV = SAFE_RANGE,                   // NAV | ESC

  #ifdef DANISH_ENABLE
  CU_LSFT,                  // LSFT | (
  CU_RSFT,                  // LSFT | )
  CU_COMM,                  // , | <
  CU_DOT,                   // . | >
  CU_SLSH,                  // / | ?
  CU_SCLN,                  // ; | :
  CU_QUOT,                  // ' | "
  CU_2,                     // 2 | @
  CU_4,                     // 4 | $
  CU_6,                     // 6 | ^
  CU_7,                     // 7 | &
  CU_8,                     // 8 | *
  CU_9,                     // 9 | (
  CU_0,                     // 0 | )
  CU_MINS,                  // - | _
  CU_EQL,                   // = | +
  CU_BSPC,                  // backspace | delete
  CU_LBRC,                  // [ | {
  CU_RBRC,                  // ] | }
  CU_BSLS,                  // \ | |
  #endif

  NEW_SAFE_RANGE            // Use for keymap specific keycodes
};

#ifdef DANISH_ENABLE
extern bool lshift;
extern bool rshift;
extern bool lshiftp;
extern bool rshiftp;
extern uint16_t lshift_timer;
extern uint16_t rshift_timer;

extern uint8_t prev_indx;
extern uint16_t prev_kcs[6];
void add_to_prev(uint16_t kc);
void unreg_prev(void);

extern bool esct;
#endif

extern bool navesc;
extern uint16_t navesc_timer;

void timer_timeout(void);

void timer_timeout_keymap(void);

bool process_record_keymap(uint16_t keycode, keyrecord_t *record);

#define CTRLX LCTL(KC_X)
#define CTRLC LCTL(KC_C)
#define CTRLV LCTL(KC_V)

#define ALTF4 LALT(KC_F4)

#define GUIU LGUI(KC_UP)
#define GUID LGUI(KC_DOWN)
#define GUIL LGUI(KC_LEFT)
#define GUIR RGUI(KC_RIGHT)

#define CTLENT CTL_T(KC_ENT)

#define EMOJI LWIN(KC_DOT)

/*
Templates for Keys, with custom shifted and non shifted Characters
*/

// Normal shift status
#define SHIFT_NORM(kc1, kc2) \
if (record->event.pressed) { \
  timer_timeout(); \
  if (lshift || rshift) { \
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

// Inverted shift status
#define SHIFT_SWITCH(kc1, kc2) \
if (record->event.pressed) { \
  timer_timeout(); \
  if (lshift || rshift) { \
    unregister_code(KC_LSFT); \
    unregister_code(kc2); \
    register_code(kc2); \
    add_to_prev(kc2); \
  } else { \
    register_code(KC_LSFT); \
    unregister_code(kc1); \
    register_code(kc1); \
    add_to_prev(kc1); \
  } \
} else { \
  unregister_code(kc1); \
  unregister_code(kc2); \
  unreg_prev(); \
  if (lshift || rshift) \
    register_code(KC_LSFT); \
  else \
    unregister_code(KC_LSFT); \
} \
return false;

// Always shifted
#define SHIFT_ALL(kc1, kc2) \
if (record->event.pressed) { \
  timer_timeout(); \
  register_code(KC_LSFT); \
  if (lshift || rshift) { \
    tap_code(kc2); \
    add_to_prev(kc2); \
  } else { \
    tap_code(kc1); \
    add_to_prev(kc1); \
  } \
} else { \
  unregister_code(kc1); \
  unregister_code(kc2); \
  unreg_prev(); \
  if (lshift || rshift) \
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
  if (lshift || rshift) { \
    tap_code(kc2); \
    add_to_prev(kc2); \
  } else { \
    tap_code(kc1); \
  } \
} else { \
  unregister_code(kc1); \
  unregister_code(kc2); \
  unreg_prev(); \
  if (lshift || rshift) \
    register_code(KC_LSFT); \
  else \
    unregister_code(KC_LSFT); \
} \
return false;

// Norm AltGr
#define NORM_ALGR(kc1, kc2) \
if (record->event.pressed) { \
  timer_timeout(); \
  if (lshift || rshift) { \
    register_code(KC_ALGR); \
    unregister_code(KC_LSFT); \
    tap_code(kc2); \
    unregister_code(KC_ALGR); \
  } else { \
    unregister_code(KC_ALGR); \
    unregister_code(KC_LSFT); \
    tap_code(kc1); \
  } \
} else { \
  unregister_code(kc1); \
  unregister_code(kc2); \
} \
return false;

// Norm AltGr shift
#define NORM_ALGRSHIFT(kc1, kc2) \
if (record->event.pressed) { \
  timer_timeout(); \
  register_code(KC_LSFT); \
  register_code(KC_ALGR); \
  if (lshift || rshift) { \
    unregister_code(kc2); \
    tap_code(kc2); \
    unregister_code(KC_LSFT); \
  } else { \
    unregister_code(KC_LSFT); \
    unregister_code(kc1); \
    register_code(kc1); \
  } \
  unregister_code(KC_ALGR); \
} else { \
  unregister_code(kc1); \
  unregister_code(kc2); \
} \
return false;

// Inverted altgr status
#define ALGR_SWITCH(kc1, kc2) \
if (record->event.pressed) { \
  timer_timeout(); \
  register_code(KC_ALGR); \
  if (lshift || rshift) { \
    unregister_code(KC_LSFT); \
    unregister_code(kc2); \
    register_code(kc2); \
    unregister_code(KC_ALGR); \
    add_to_prev(kc2); \
  } else { \
    register_code(KC_LSFT); \
    unregister_code(kc1); \
    register_code(kc1); \
    unregister_code(KC_ALGR); \
    add_to_prev(kc1); \
  } \
} else { \
  unregister_code(kc1); \
  unregister_code(kc2); \
  unreg_prev(); \
  if (lshift || rshift) \
    register_code(KC_LSFT); \
  else \
    unregister_code(KC_LSFT); \
} \
return false;

// Always AltGr
#define SHIFT_ALGR(kc1, kc2) \
if (record->event.pressed) { \
  timer_timeout(); \
  unregister_code(KC_LSFT); \
  register_code(KC_ALGR); \
  if (lshift || rshift) { \
    unregister_code(kc2); \
    tap_code(kc2); \
    register_code(KC_LSFT); \
  } else { \
    unregister_code(kc1); \
    tap_code(kc1); \
  } \
  unregister_code(KC_ALGR); \
} \
return false;

// Different keycode when Ctrl is pressed
#define CTRL(kc1, kc2) \
if(record->event.pressed) { \
  timer_timeout(); \
  if (lshift || rshift) \
    register_code(KC_LSFT); \
  else \
    unregister_code(KC_LSFT); \
  if (keyboard_report->mods & (MOD_BIT(KC_LCTL) | MOD_BIT(KC_RCTL))){ \
    register_code(kc2); \
  } else { \
    register_code(kc1); \
  } \
} else { \
    unregister_code(kc1); \
    unregister_code(kc2); \
} \
return false;
