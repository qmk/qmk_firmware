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

// Shift / paren setup
#ifndef LSPO_KEY
  #define LSPO_KEY KC_9
#endif
#ifndef RSPC_KEY
  #define RSPC_KEY KC_0
#endif

#ifndef LSPO_MOD
  #define LSPO_MOD KC_LSFT
#endif
#ifndef RSPC_MOD
  #define RSPC_MOD KC_RSFT
#endif

// Control / paren setup
#ifndef LCPO_KEY
  #define LCPO_KEY KC_9
#endif
#ifndef RCPC_KEY
  #define RCPC_KEY KC_0
#endif

#ifndef LCPO_MOD
  #define LCPO_MOD KC_LCTL
#endif
#ifndef RCPC_MOD
  #define RCPC_MOD KC_RCTL
#endif

// Alt / paren setup
#ifndef LAPO_KEY
  #define LAPO_KEY KC_9
#endif
#ifndef RAPC_KEY
  #define RAPC_KEY KC_0
#endif

#ifndef LAPO_MOD
  #define LAPO_MOD KC_LALT
#endif
#ifndef RAPC_MOD
  #define RAPC_MOD KC_RALT
#endif

// Shift / Enter setup
#ifndef SFTENT_KEY
  #define SFTENT_KEY KC_ENT
#endif

static bool space_cadet_interrupted[4] = {0, 0, 0, 0};
static uint16_t space_cadet_timer[4] = {0, 0, 0, 0};

static void do_space_cadet(keyrecord_t *record, uint8_t index, uint8_t normalMod, uint8_t tapMod, uint8_t rolloverMod, uint8_t keycode) {
  if (record->event.pressed) {
    space_cadet_interrupted[index] = false;
    space_cadet_timer[index] = timer_read ();
    register_mods(MOD_BIT(normalMod));
  }
  else {
    #ifdef DISABLE_SPACE_CADET_ROLLOVER
      if (get_mods() & MOD_BIT(rolloverMod)) {
        space_cadet_interrupted[index] = true;
        space_cadet_interrupted[1] = true; // shift esc
      }
    #endif
    if (!space_cadet_interrupted[index] && timer_elapsed(space_cadet_timer[index]) < TAPPING_TERM) {
      #ifdef DISABLE_SPACE_CADET_MODIFIER
        unregister_mods(MOD_BIT(normalMod));
      #else
        if (tapMod != normalMod) {
          unregister_mods(MOD_BIT(normalMod));
          register_mods(MOD_BIT(tapMod));
        }
      #endif

      register_code(keycode);
      unregister_code(keycode);

      #ifndef DISABLE_SPACE_CADET_MODIFIER
        if (tapMod != normalMod) {
          unregister_mods(MOD_BIT(tapMod));
        }
      #endif
    }
    unregister_mods(MOD_BIT(normalMod));
  }
}

bool process_space_cadet(uint16_t keycode, keyrecord_t *record) {
  switch(keycode) {
    case KC_LSPO: {
      do_space_cadet(record, 0, KC_LSFT, LSPO_MOD, RSPC_MOD, LSPO_KEY);
      return false;
    }
    case KC_RSPC: {
      do_space_cadet(record, 0, KC_RSFT, RSPC_MOD, LSPO_MOD, RSPC_KEY);
      return false;
    }
    case KC_LCPO: {
      do_space_cadet(record, 2, KC_LCTL, LCPO_MOD, RCPC_MOD, LCPO_KEY);
      return false;
    }
    case KC_RCPC: {
      do_space_cadet(record, 2, KC_RCTL, RCPC_MOD, LCPO_MOD, RCPC_KEY);
      return false;
    }
    case KC_LAPO: {
      do_space_cadet(record, 3, KC_LALT, LAPO_MOD, RAPC_MOD, LAPO_KEY);
      return false;
    }
    case KC_RAPC: {
      do_space_cadet(record, 3, KC_RALT, RAPC_MOD, LAPO_MOD, RAPC_KEY);
      return false;
    }
    case KC_SFTENT: {
      if (record->event.pressed) {
        space_cadet_interrupted[1] = false;
        space_cadet_timer[1] = timer_read ();
        register_mods(MOD_BIT(KC_RSFT));
      }
      else if (!space_cadet_interrupted[1] && timer_elapsed(space_cadet_timer[1]) < TAPPING_TERM) {
        unregister_mods(MOD_BIT(KC_RSFT));
        register_code(SFTENT_KEY);
        unregister_code(SFTENT_KEY);
      }
      else {
        unregister_mods(MOD_BIT(KC_RSFT));
      }
      return false;
    }
    default: {
      space_cadet_interrupted[0] = true;
      space_cadet_interrupted[1] = true;
      space_cadet_interrupted[2] = true;
      space_cadet_interrupted[3] = true;
      break;
    }
  }
  return true;
}
