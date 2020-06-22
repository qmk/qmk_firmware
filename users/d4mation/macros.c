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

      case AMENO:  /* ༼ つ ◕_◕ ༽つ */

        if ( record->event.pressed ) {

          send_unicode_hex_string( "0F3C 0020 3064 0020 25D5 005F 25D5 0020 0F3D 3064" );

        }

        return false;
        break;

      case MAGIC:  /* (∩ ͡° ͜ʖ ͡°)⊃━☆ﾟ. * */

        if ( record->event.pressed ) {

          send_unicode_hex_string( "0028 2229 0020 0361 00B0 0020 035C 0296 0020 0361 00B0 0029 2283 2501 2606 FF9F 002E 0020 002A" );

        }

        return false;
        break;

      case LENNY:  /* ( ͡° ͜ʖ ͡°) */

        if ( record->event.pressed ) {

          send_unicode_hex_string( "0028 0020 0361 00B0 0020 035C 0296 0020 0361 00b0 0029" );

        }

        return false;
        break;

      case DISFACE:  /* ಠ_ಠ */

        if ( record->event.pressed ) {
          send_unicode_hex_string( "0CA0 005F 0CA0" );
        }

        return false;
        break;

      case TFLIP:  /* (╯°□°)╯ ︵ ┻━┻ */

        if ( record->event.pressed ) {

          send_unicode_hex_string( "0028 256F 00b0 25A1 00B0 0029 256F FE35 253B 2501 253B" );

        }

        return false;
        break;

      case TPUT:  /* ┬──┬ ノ( ゜-゜ノ) */

        if ( record->event.pressed ) {

          send_unicode_hex_string( "252C 2500 2500 252C 0020 30CE 0028 0020 309C 002D 309C 30CE 0029" );

        }

        return false;
        break;

      case SHRUG:  /* ¯\_(ツ)_/¯ */

        if ( record->event.pressed ) {

          send_unicode_hex_string( "00AF 005C 005F 0028 30C4 0029 005F 002F 00AF" );

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