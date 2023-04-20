// Copyright 2023 @miketronic -- Mike B <mxb540@gmail.com>
// SPDX-License-Identifier: GPL-2.0+

#include "miketronic.h"
#include "process_records.h"

__attribute__ ((weak))
bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
  return true;
}

__attribute__ ((weak))
bool process_record_secrets(uint16_t keycode, keyrecord_t *record) {
  return true;
}


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
#ifdef CONSOLE_ENABLE
  uprintf("KL: kc: %u, col: %u, row: %u, pressed: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed);
#endif


  switch(keycode) {

    case VERSION:
      if (!record->event.pressed) {
        send_string_with_delay_P(PSTR(QMK_KEYBOARD ":" QMK_KEYMAP "\nVersion:" QMK_VERSION ", built: " QMK_BUILDDATE "\n"), MACRO_TIMER);
      }
      break;

    case MAKE:  // Compiles the firmware, and adds the flash command based on keyboard bootloader
            if (!record->event.pressed) {
            uint8_t temp_mod = get_mods();
            uint8_t temp_osm = get_oneshot_mods();
            clear_mods(); clear_oneshot_mods();
            SEND_STRING("make " QMK_KEYBOARD ":" QMK_KEYMAP);
    #ifndef FLASH_BOOTLOADER
            if ((temp_mod | temp_osm) & MOD_MASK_SHIFT)
    #endif
            {
                SEND_STRING(":flash");
            }
            if ((temp_mod | temp_osm) & MOD_MASK_CTRL) {
                SEND_STRING(" -j8 --output-sync");
            }
            tap_code(KC_ENT);
            set_mods(temp_mod);
        }
        break;


   case M01: 
        if (record->event.pressed) {
            SEND_STRING("//a11");
        }
	      break;
    
   case M02: 
        if (record->event.pressed) {
            SEND_STRING("//a12");
        }
	      break;

    case M03: 
        if (record->event.pressed) {
            SEND_STRING("//a08");
        }         
	      break;

    case M04: 
        if (record->event.pressed) {
            SEND_STRING("//a09");
        }
	      break;
    
    case M05: 
        if (record->event.pressed) {
            SEND_STRING("//th");
       }
	     break;
  
    case M06: 
        if (record->event.pressed) {
            SEND_STRING("//re");
      }
	    break;
    
    case M07: 
        if (record->event.pressed) {
	          SEND_STRING("//yw");
        }
	      break;
    
    case M08: 
        if (record->event.pressed) {
            tap_random_base64();
        }
	      break;

#if defined(KEYBOARD_1upkeyboards_pi40_v1_0) && defined(RGBLIGHT_ENABLE)        
    case WM:
        if (record->event.pressed) {
           set_single_persistent_default_layer(_WM);
	         rgblight_sethsv_noeeprom(HSV_WHITE);
        } 
      break;

     case QW:
       if (record->event.pressed) {
           set_single_persistent_default_layer(_QW);
	         rgblight_sethsv_noeeprom(HSV_MAGENTA);
      }
      break;

     case RGB1:
       if (record->event.pressed) {
	         rgblight_sethsv_noeeprom(HSV_BLUE);
      }
      break;

     case RGB2:
       if (record->event.pressed) {
	         rgblight_sethsv_noeeprom(HSV_RED);
      }
      break;

     case RGB3:
       if (record->event.pressed) {
	         rgblight_sethsv_noeeprom(HSV_ORANGE);
      }
      break; 

     case RGB4:
       if (record->event.pressed) {
	         rgblight_sethsv_noeeprom(HSV_YELLOW);
      }
      break;

     case RGB5:
       if (record->event.pressed) {
	         rgblight_sethsv_noeeprom(HSV_GREEN);
      }
      break;
#endif

  }
  return process_record_keymap(keycode, record) &&
    process_record_secrets(keycode, record);
}

