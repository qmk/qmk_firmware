/* Copyright 2019 Jack Humbert
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
#include "process_space_cadet.h"

#ifndef TAPPING_TERM
  #define TAPPING_TERM 200
#endif

// Basic SC_KEY define
#define SC_KEY(mod, tapMod, keycode) mod, tapMod, keycode

// Shift / paren setup
#ifndef KC_LSPO_KEYS
  #define KC_LSPO_KEYS SC_KEY(KC_LSFT, KC_LSFT, KC_9)
#endif
#ifndef KC_RSPC_KEYS
  #define KC_RSPC_KEYS SC_KEY(KC_RSFT, KC_RSFT, KC_0)
#endif

// Control / paren setup
#ifndef KC_LCPO_KEYS
  #define KC_LCPO_KEYS SC_KEY(KC_LCTL, KC_LCTL, KC_9)
#endif
#ifndef KC_RCPO_KEYS
  #define KC_RCPO_KEYS SC_KEY(KC_RCTL, KC_RCTL, KC_0)
#endif

// Alt / paren setup
#ifndef KC_LAPO_KEYS
  #define KC_LAPO_KEYS SC_KEY(KC_LALT, KC_LALT, KC_9)
#endif
#ifndef KC_RAPO_KEYS
  #define KC_RAPO_KEYS SC_KEY(KC_RALT, KC_RALT, KC_0)
#endif

// Shift / Enter setup
#ifndef KC_SFTENT_KEYS
  #define KC_SFTENT_KEYS SC_KEY(KC_RSFT, KC_TRNS, KC_ENT)
#endif

static uint8_t sc_last = 0;
static uint16_t sc_timer = 0;

static void do_space_cadet_simple(keyrecord_t *record, uint8_t normalMod, uint8_t tapMod, uint8_t keycode) {
  if (record->event.pressed) {
    sc_last = normalMod;
    sc_timer = timer_read ();
    register_mods(MOD_BIT(normalMod));
  }
  else {
    unregister_mods(MOD_BIT(normalMod));

    if (sc_last == normalMod && timer_elapsed(sc_timer) < TAPPING_TERM) {
      if (IS_MOD(tapMod)) {
        register_mods(MOD_BIT(tapMod));
      }
      tap_code(keycode);
      if (IS_MOD(tapMod)) {
        unregister_mods(MOD_BIT(tapMod));
      }
    }
  }
}

bool process_space_cadet_simple(uint16_t keycode, keyrecord_t *record) {
  switch(keycode) {
    case KC_LSPO: {
      do_space_cadet_simple(record, KC_LSPO_KEYS);
      return false;
    }
    case KC_RSPC: {
      do_space_cadet_simple(record, KC_RSPC_KEYS);
      return false;
    }
    case KC_LCPO: {
      do_space_cadet_simple(record, KC_LCPO_KEYS);
      return false;
    }
    case KC_RCPC: {
      do_space_cadet_simple(record, KC_RCPO_KEYS);
      return false;
    }
    case KC_LAPO: {
      do_space_cadet_simple(record, KC_LAPO_KEYS);
      return false;
    }
    case KC_RAPC: {
      do_space_cadet_simple(record, KC_RAPO_KEYS);
      return false;
    }
    case KC_SFTENT: {
      do_space_cadet_simple(record, KC_SFTENT_KEYS);
      return false;
    }
    default: {
      sc_last = 0;
      break;
    }
  }
  return true;
}
