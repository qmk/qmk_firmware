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

// Shift / Enter setup
#ifndef SFTENT_KEY
  #define SFTENT_KEY KC_ENT
#endif

/*
static bool     shift_interrupted[2] = {0, 0};
static uint16_t scs_timer        [2] = {0, 0};
*/

static bool     shift_pressed[ 2 ] = { false, false };
static uint16_t scs_time     [ 2 ] = { 0, 0 };

static const uint8_t SCS_LEFT  = 0, SCS_RIGHT = 1;






static void stop_SCS( const uint8_t pos ){ 

  shift_pressed[ pos ] = false;
//  scs_time     [ pos ] = UINT16_C( 0 ); // + 120 bytes

  return;
}


static void start_SCS( const uint8_t pos, const uint16_t time ){

  shift_pressed[ pos ] = true;
  scs_time     [ pos ] = time;

  return;
}






static bool is_while_tap( const uint8_t pos ){ 
  return timer_elapsed( scs_time[ pos ] ) < TAPPING_TERM;
}

static bool is_pressed( const uint8_t pos ){ 
  return shift_pressed[ pos ];
}

# ifdef DISABLE_SPACE_CADET_ROLLOVER
static bool is_tap_enable( const uint8_t pos ){
  return is_pressed( pos ) && is_while_tap( pos );
}

# endif




static void pressed_SCS ( const uint16_t time, const uint8_t pos, const uint8_t brother, const uint8_t shift ){

  register_mods( MOD_BIT( shift ) );
 
# ifdef DISABLE_SPACE_CADET_ROLLOVER
    if( is_tap_enable( brother ) ) {
      stop_SCS ( brother );
      return;
    }
# endif

  start_SCS( pos, time );

  return;
}


static void released_SCS ( const uint8_t pos, const uint8_t shift, const uint8_t mod, const uint16_t key, const bool is_sftent ){

  if( ! is_pressed( pos ) ) {
    unregister_mods( MOD_BIT( shift ) );
    return;
  }

  bool mod_changed = false;

    if( is_sftent ){                          // is this shift enter ?
      unregister_mods( MOD_BIT( shift ) );
    }
  /* -------------------- ↑ Shift Enter ↓ Shift Parenthesis -------------- */
#   ifdef DISABLE_SPACE_CADET_MODIFIER
    else {
      unregister_mods( MOD_BIT( shift ) );
#   else
    else if( mod != shift ) {
      unregister_mods( MOD_BIT( shift ) );
        register_mods( MOD_BIT( mod   ) );
      mod_changed = true;
#   endif
    }


  if( is_while_tap( pos ) ) {
      register_code( key );
    unregister_code( key );
  }

  stop_SCS ( pos );


  unregister_mods(
      ( mod_changed ) ? MOD_BIT( mod   ) :      // Shift Parenthesis and Mod changed
      ( ! is_sftent ) ? MOD_BIT( shift ) : 0    // Shift Parenthesis not Mod changed, or other, nothing happen
  );
  return;
}






bool process_space_cadet( const uint16_t keycode, keyrecord_t *record ){ 

  switch( keycode ) {

    case KC_LSPO : {
      if( record -> event.pressed ) { 
        pressed_SCS( record -> event.time, SCS_LEFT, SCS_RIGHT, KC_LSFT );
        return false;
      }

      // key released process
      released_SCS( SCS_LEFT, KC_LSFT, LSPO_MOD, LSPO_KEY, false );
      return false;
    } 
    break;

    case KC_RSPC : {
      if( record -> event.pressed ) {
        pressed_SCS( record -> event.time, SCS_RIGHT, SCS_LEFT, KC_RSFT );
        return false; 
      }

      // key released process
      released_SCS( SCS_RIGHT, KC_RSFT, RSPC_MOD, RSPC_KEY, false );
      return false;
    }
    break;

    case KC_SFTENT : {
      if( record -> event.pressed ) {
        pressed_SCS( record -> event.time, SCS_RIGHT, SCS_LEFT, KC_RSFT );
        return false;
      }

      // key released process
      released_SCS( SCS_RIGHT, KC_RSFT, RSPC_MOD, SFTENT_KEY, true );
      return false;
    }
    break;

    default: {
/*
      shift_interrupted[0] = true;
      shift_interrupted[1] = true;
*/
      stop_SCS( SCS_LEFT );
      stop_SCS( SCS_RIGHT );

    }
    break;


/*
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
*/


  }


  return true;
}
