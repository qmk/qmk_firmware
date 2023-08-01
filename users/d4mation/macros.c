#include "d4mation.h"
#include "tap-hold.h"
#include "zalgo.h"
#include "macros.h"

bool zalgo_enabled = false;

bool process_record_user( uint16_t keycode, keyrecord_t *record ) {

  switch ( keycode ) {

    case _GRAVE_ESC:

      /* Send ` on Tap, Esc on Hold */
      tap_or_hold( record, KC_GRAVE, KC_ESC );

      return false;
      break;

    case PHPOPEN:

      if ( record->event.pressed ) {

        tap_code16( S( KC_COMMA ) );
        tap_code16( S( KC_SLASH ) );

        tap_code( KC_P );
        tap_code( KC_H );
        tap_code( KC_P );

      }

      return false;
      break;

    case PHPCLSE:

      if ( record->event.pressed ) {
        tap_code16( S( KC_SLASH ) );
        tap_code16( S( KC_DOT ) );
      }

      return false;
      break;

    #ifdef UNICODE_ENABLE

      case AMENO:

        if ( record->event.pressed ) {

          send_unicode_string( "༼ つ ◕_◕ ༽つ" );

        }

        return false;
        break;

      case MAGIC:

        if ( record->event.pressed ) {

          send_unicode_string( "(∩ ͡° ͜ʖ ͡°)⊃━☆ﾟ. *" );

        }

        return false;
        break;

      case LENNY:

        if ( record->event.pressed ) {

          send_unicode_string( "( ͡° ͜ʖ ͡°)" );

        }

        return false;
        break;

      case DISFACE:

        if ( record->event.pressed ) {
          send_unicode_string( "ಠ_ಠ" );
        }

        return false;
        break;

      case TFLIP:

        if ( record->event.pressed ) {

          send_unicode_string( "(╯°□°)╯︵┻━┻" );

        }

        return false;
        break;

      case TPUT:

        if ( record->event.pressed ) {

          send_unicode_string( "┬──┬ ノ( ゜-゜ノ)" );

        }

        return false;
        break;

      case SHRUG:

        if ( record->event.pressed ) {

          send_unicode_string( "¯\\_(ツ)_/¯" );

        }

        return false;
        break;

      case ZALGO:  /* Toggles Zalgo Text mode */

        if ( record->event.pressed ) {
          zalgo_enabled = ! zalgo_enabled;
        }

        return false;
        break;

    #endif

    default:

      #ifdef UNICODE_ENABLE

        if ( zalgo_enabled ) {

          if ( keycode < KC_A || ( keycode > KC_0 && keycode < KC_MINUS ) || keycode > KC_SLASH ) {
            process_record_keymap( keycode, record );
            return true;
          }

          if ( record->event.pressed ) {
            zalgo_text( keycode );
          }

          return false;
        }

      #endif

      break;
  }

  process_record_keymap( keycode, record );
  return true;

};