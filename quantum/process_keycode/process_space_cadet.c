/* Copyright 2018 leico
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

#include "quantum.h"

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

// Shift / Enter setup
#ifndef SFTENT_KEY
  #define SFTENT_KEY KC_ENT
#endif

static bool     shift_interrupted[2] = {0, 0};
static uint16_t scs_timer        [2] = {0, 0};



bool process_space_cadet( uint16_t keycode, keyrecord_t *record ){ 

  switch( keycode ) { 
  
    case KC_LSPO: {
      if (record->event.pressed) {
        shift_interrupted[0] = false;
        scs_timer[0] = timer_read ();
        register_mods(MOD_BIT(KC_LSFT));
      }
      else {
        #ifdef DISABLE_SPACE_CADET_ROLLOVER
          if (get_mods() & MOD_BIT(RSPC_MOD)) {
            shift_interrupted[0] = true;
            shift_interrupted[1] = true;
          }
        #endif
        if (!shift_interrupted[0] && timer_elapsed(scs_timer[0]) < TAPPING_TERM) {
          #ifdef DISABLE_SPACE_CADET_MODIFIER
            unregister_mods(MOD_BIT(KC_LSFT));
          #else
            if( LSPO_MOD != KC_LSFT ){
              unregister_mods(MOD_BIT(KC_LSFT));
              register_mods(MOD_BIT(LSPO_MOD));
            }
          #endif
          register_code(LSPO_KEY);
          unregister_code(LSPO_KEY);
          #ifndef DISABLE_SPACE_CADET_MODIFIER
            if( LSPO_MOD != KC_LSFT ){
              unregister_mods(MOD_BIT(LSPO_MOD));
            }
          #endif
        }
        unregister_mods(MOD_BIT(KC_LSFT));
      }
      return false;
    }

    case KC_RSPC: {
      if (record->event.pressed) {
        shift_interrupted[1] = false;
        scs_timer[1] = timer_read ();
        register_mods(MOD_BIT(KC_RSFT));
      }
      else {
        #ifdef DISABLE_SPACE_CADET_ROLLOVER
          if (get_mods() & MOD_BIT(LSPO_MOD)) {
            shift_interrupted[0] = true;
            shift_interrupted[1] = true;
          }
        #endif
        if (!shift_interrupted[1] && timer_elapsed(scs_timer[1]) < TAPPING_TERM) {
          #ifdef DISABLE_SPACE_CADET_MODIFIER
            unregister_mods(MOD_BIT(KC_RSFT));
          #else
            if( RSPC_MOD != KC_RSFT ){
              unregister_mods(MOD_BIT(KC_RSFT));
              register_mods(MOD_BIT(RSPC_MOD));
            }
          #endif
          register_code(RSPC_KEY);
          unregister_code(RSPC_KEY);
          #ifndef DISABLE_SPACE_CADET_MODIFIER
            if ( RSPC_MOD != KC_RSFT ){
              unregister_mods(MOD_BIT(RSPC_MOD));
            }
          #endif
        }
        unregister_mods(MOD_BIT(KC_RSFT));
      }
      return false;
    }

    case KC_SFTENT: {
      if (record->event.pressed) {
        shift_interrupted[1] = false;
        scs_timer[1] = timer_read ();
        register_mods(MOD_BIT(KC_RSFT));
      }
      else if (!shift_interrupted[1] && timer_elapsed(scs_timer[1]) < TAPPING_TERM) {
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
      shift_interrupted[0] = true;
      shift_interrupted[1] = true;
      break;
    }


  }


  return true;
}
