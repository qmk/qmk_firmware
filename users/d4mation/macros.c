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

    case AMENO:  /* ༼ つ ◕_◕ ༽つ */

      if ( record->event.pressed ) {

        process_unicode( ( 0x0F3C|QK_UNICODE ), record );  /* Head */
        tap_code( KC_SPACE );
        process_unicode( ( 0x3064|QK_UNICODE ), record );  /* Hand */
        tap_code( KC_SPACE );
        process_unicode( ( 0x25D5|QK_UNICODE ), record );  /* Eye */
        tap_code16( S( KC_MINS ) );                        /* Mouth */
        process_unicode( ( 0x25D5|QK_UNICODE ), record );  /* Eye */
        tap_code( KC_SPACE );
        process_unicode( ( 0x0F3D|QK_UNICODE ), record );  /* Head */
        process_unicode( ( 0x3064|QK_UNICODE ), record );  /* Hand */

      }

      return false;
      break;

    case MAGIC:  /* (∩ ͡° ͜ʖ ͡°)⊃━☆ﾟ. * */

      if ( record->event.pressed ) {
        
        tap_code16( S( KC_9 ) );                            /* Head */
        process_unicode( ( 0x2229|QK_UNICODE ), record );   /* Hand */
        tap_code( KC_SPC );
        process_unicode( ( 0x0361|QK_UNICODE ), record );   /* Eyebrow */
        process_unicode( ( 0x00B0|QK_UNICODE ), record );   /* Eye */
        tap_code( KC_SPC );
        process_unicode( ( 0x035C|QK_UNICODE ), record );   /* Mouth */
        process_unicode( ( 0x0296|QK_UNICODE ), record );   /* Nose */
        tap_code( KC_SPC );
        process_unicode( ( 0x0361|QK_UNICODE ), record );   /* Eyebrow */
        process_unicode((0x00B0 | QK_UNICODE), record);     /* Eye */
        tap_code16( S( KC_0 ) );                            /* Head */
        process_unicode( ( 0x2283|QK_UNICODE ), record );   /* Hand */
        process_unicode( ( 0x2501|QK_UNICODE ), record );   /* Wand Shaft */
        process_unicode( ( 0x2606|QK_UNICODE ), record );   /* Wand Star */
        unicode_input_start();
        register_hex( 0xFF9F );  /* Magic. If we use process_unicode() here it does a bitwise AND operation on it and changes the character on us */
        unicode_input_finish();
        tap_code( KC_DOT );  /* Magic */
        tap_code( KC_SPACE );
        tap_code16( S( KC_8 ) );  /* Magic */

      }

      return false;
      break;

    case LENNY:  /* ( ͡° ͜ʖ ͡°) */

      if ( record->event.pressed ) {

        tap_code16( S( KC_9 ) );                           /* Head */
        tap_code( KC_SPC );
        process_unicode( ( 0x0361|QK_UNICODE ), record );  /* Eyebrow */
        process_unicode( ( 0x00B0|QK_UNICODE ), record );  /* Eye */
        tap_code( KC_SPC );
        process_unicode( ( 0x035C|QK_UNICODE ), record );  /* Mouth */
        process_unicode( ( 0x0296|QK_UNICODE ), record );  /* Nose */
        tap_code( KC_SPC );
        process_unicode( ( 0x0361|QK_UNICODE ), record );  /* Eyebrow */
        process_unicode( ( 0x00B0|QK_UNICODE ), record );  /* Eye */
        tap_code16( S( KC_0 ) );                           /* Head */

      }

      return false;
      break;

    case DISFACE:  /* ಠ_ಠ */

      if ( record->event.pressed ) {
        process_unicode( ( 0x0CA0|QK_UNICODE ), record );  /* Eye */
        tap_code16( S( KC_MINS ) );
        process_unicode( ( 0x0CA0|QK_UNICODE ), record );  /* Eye */
      }

      return false;
      break;

    case TFLIP:  /* (╯°□°)╯ ︵ ┻━┻ */

      if ( record->event.pressed ) {

        tap_code16( S( KC_9 ) );
        process_unicode( ( 0x256F|QK_UNICODE ), record );  /* Arm */
        process_unicode( ( 0x00B0|QK_UNICODE ), record );  /* Eye */
        process_unicode( ( 0x25A1|QK_UNICODE ), record );  /* Mouth */
        process_unicode( ( 0x00B0|QK_UNICODE ), record );  /* Eye */
        tap_code16( S( KC_0 ) );
        process_unicode( ( 0x256F|QK_UNICODE ), record );  /* Arm */
        tap_code( KC_SPC );
        process_unicode( ( 0x0361|QK_UNICODE ), record );  /* Flippy */
        tap_code( KC_SPC );
        process_unicode( ( 0x253B|QK_UNICODE ), record );  /* Table */
        process_unicode( ( 0x2501|QK_UNICODE ), record );  /* Table */
        process_unicode( ( 0x253B|QK_UNICODE ), record );  /* Table */

      }

      return false;
      break;

    case TPUT:  /* ┬──┬ ノ( ゜-゜ノ) */

      if ( record->event.pressed ) {

        process_unicode( ( 0x252C|QK_UNICODE ), record );  /* Table */
        process_unicode( ( 0x2500|QK_UNICODE ), record );  /* Table */
        process_unicode( ( 0x2500|QK_UNICODE ), record );  /* Table */
        process_unicode( ( 0x252C|QK_UNICODE ), record );  /* Table */
        tap_code( KC_SPC );
        process_unicode( ( 0x30CE|QK_UNICODE ), record );  /* Arm */
        tap_code16( S( KC_9 ) );
        tap_code( KC_SPC );
        process_unicode( ( 0x309C|QK_UNICODE ), record );  /* Eye */
        tap_code( KC_MINS );
        process_unicode( ( 0x309C|QK_UNICODE ), record );  /* Eye */
        process_unicode( ( 0x30CE|QK_UNICODE ), record );  /* Arm */
        tap_code16( S( KC_0 ) );
      }

      return false;
      break;

    case SHRUG:  /* ¯\_(ツ)_/¯ */

      if ( record->event.pressed ) {

        process_unicode( ( 0x00AF|QK_UNICODE ), record );  /* Hand */
        tap_code( KC_BSLS );                               /* Arm */
        tap_code16( S( KC_MINS ) );                        /* Arm */
        tap_code16( S( KC_9 ) );                           /* Head */
        process_unicode( ( 0x30C4|QK_UNICODE ), record );  /* Face */
        tap_code16( S( KC_0 ) );                           /* Head */
        tap_code16( S( KC_MINS ) );                        /* Arm */
        tap_code( KC_SLSH );                               /* Arm */
        process_unicode( ( 0x00AF|QK_UNICODE ), record );  /* Hand */

      }

      return false;
      break;

    case ZALGO:  /* Toggles Zalgo Text mode */

      if ( record->event.pressed ) {
        zalgo_enabled = ! zalgo_enabled;
      }

      return false;
      break;

    default:

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

      break;
  }

  process_record_keymap( keycode, record );
  return true;

};