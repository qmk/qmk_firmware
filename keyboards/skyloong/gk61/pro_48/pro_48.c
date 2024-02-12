// Copyright 2023 linlin012 (@linlin012)
// SPDX-License-Identifier: GPL-2.0-or-later
#include "quantum.h"
_Bool FN_WIN = 0;
_Bool FN_MAC = 0;
_Bool L_WIN = 0;
_Bool L_MAC = 0;

#if defined(RGB_MATRIX_ENABLE)  /*&& defined(CAPS_LOCK_INDEX)*/
const is31fl3743a_led_t PROGMEM g_is31fl3743a_leds[IS31FL3743A_LED_COUNT] = {
/* Refer to IS31 manual for these locations
 *   driver
 *   |  R location
 *   |  |          G location
 *   |  |          |          B location
 *   |  |          |          | */
    {0, CS1_SW1,   CS2_SW1,   CS3_SW1},
    {0, CS1_SW2,   CS2_SW2,   CS3_SW2},
    {0, CS1_SW3,   CS2_SW3,   CS3_SW3},
    {0, CS1_SW4,   CS2_SW4,   CS3_SW4},
    {0, CS1_SW5,   CS2_SW5,   CS3_SW5},
    {0, CS1_SW6,   CS2_SW6,   CS3_SW6},
    {0, CS1_SW7,   CS2_SW7,   CS3_SW7},
    {0, CS1_SW8,   CS2_SW8,   CS3_SW8},
    {0, CS1_SW9,   CS2_SW9,   CS3_SW9},
    {0, CS1_SW10,  CS2_SW10,  CS3_SW10},
    {0, CS1_SW11,  CS2_SW11,  CS3_SW11},
    {0, CS16_SW1,  CS17_SW1,  CS18_SW1},
    {0, CS16_SW2,  CS17_SW2,  CS18_SW2},
    {0, CS16_SW3,  CS17_SW3,  CS18_SW3},

    {0, CS4_SW1,   CS5_SW1,   CS6_SW1},
    {0, CS4_SW2,   CS5_SW2,   CS6_SW2},
    {0, CS4_SW3,   CS5_SW3,   CS6_SW3},
    {0, CS4_SW4,   CS5_SW4,   CS6_SW4},
    {0, CS4_SW5,   CS5_SW5,   CS6_SW5},
    {0, CS4_SW6,   CS5_SW6,   CS6_SW6},
    {0, CS4_SW7,   CS5_SW7,   CS6_SW7},
    {0, CS4_SW8,   CS5_SW8,   CS6_SW8},
    {0, CS4_SW9,   CS5_SW9,   CS6_SW9},
    {0, CS4_SW10,  CS5_SW10,  CS6_SW10},
    {0, CS4_SW11,  CS5_SW11,  CS6_SW11},
    {0, CS16_SW4,  CS17_SW4,  CS18_SW4},
    {0, CS16_SW5,  CS17_SW5,  CS18_SW5},
    {0, CS16_SW6,  CS17_SW6,  CS18_SW6},

    {0, CS7_SW1,   CS8_SW1,   CS9_SW1},
    {0, CS7_SW2,   CS8_SW2,   CS9_SW2},
    {0, CS7_SW3,   CS8_SW3,   CS9_SW3},
    {0, CS7_SW4,   CS8_SW4,   CS9_SW4},
    {0, CS7_SW5,   CS8_SW5,   CS9_SW5},
    {0, CS7_SW6,   CS8_SW6,   CS9_SW6},
    {0, CS7_SW7,   CS8_SW7,   CS9_SW7},
    {0, CS7_SW8,   CS8_SW8,   CS9_SW8},
    {0, CS7_SW9,   CS8_SW9,   CS9_SW9},
    {0, CS7_SW10,  CS8_SW10,  CS9_SW10},
    {0, CS7_SW11,  CS8_SW11,  CS9_SW11},
    {0, CS16_SW7,  CS17_SW7,  CS18_SW7},
    {0, CS16_SW8,  CS17_SW8,  CS18_SW8},

    {0, CS10_SW1,  CS11_SW1,  CS12_SW1},
    {0, CS10_SW2,  CS11_SW2,  CS12_SW2},
    {0, CS10_SW3,  CS11_SW3,  CS12_SW3},
    {0, CS10_SW4,  CS11_SW4,  CS12_SW4},
    {0, CS10_SW5,  CS11_SW5,  CS12_SW5},
    {0, CS10_SW6,  CS11_SW6,  CS12_SW6},
    {0, CS10_SW7,  CS11_SW7,  CS12_SW7},
    {0, CS10_SW8,  CS11_SW8,  CS12_SW8},
    {0, CS10_SW9,  CS11_SW9,  CS12_SW9},
    {0, CS10_SW10, CS11_SW10, CS12_SW10},
    {0, CS10_SW11, CS11_SW11, CS12_SW11},
    {0, CS16_SW9,  CS17_SW9,  CS18_SW9},

    {0, CS13_SW1,  CS14_SW1,  CS15_SW1},
    {0, CS13_SW2,  CS14_SW2,  CS15_SW2},
    {0, CS13_SW3,  CS14_SW3,  CS15_SW3},
    {0, CS13_SW4,  CS14_SW4,  CS15_SW4},
    {0, CS13_SW5,  CS14_SW5,  CS15_SW5},
    {0, CS13_SW5,  CS14_SW5,  CS15_SW5},
    {0, CS13_SW6,  CS14_SW6,  CS15_SW6},
    {0, CS13_SW7,  CS14_SW7,  CS15_SW7},
    {0, CS13_SW8,  CS14_SW8,  CS15_SW8},
    {0, CS13_SW9,  CS14_SW9,  CS15_SW9},
    {0, CS13_SW10, CS14_SW10, CS15_SW10}
};

bool rgb_matrix_indicators_advanced_kb(uint8_t led_min, uint8_t led_max) {
    if (!rgb_matrix_indicators_advanced_user(led_min, led_max)) {
        return false;
    }

    if (host_keyboard_led_state().caps_lock) {
        RGB_MATRIX_INDICATOR_SET_COLOR(CAPS_LOCK_INDEX, 255, 255, 255);
    } else {
        if (!rgb_matrix_get_flags()) {
            RGB_MATRIX_INDICATOR_SET_COLOR(CAPS_LOCK_INDEX, 0, 0, 0);
        }
    }

   switch (get_highest_layer(layer_state)) {
      case 2:{
        RGB_MATRIX_INDICATOR_SET_COLOR(WIN_MOD_INDEX, 255, 255, 255);
        if (!rgb_matrix_get_flags()) {
            RGB_MATRIX_INDICATOR_SET_COLOR(MAC_MOD_INDEX, 0, 0, 0);
         }
      } break;
      case 3:{
        RGB_MATRIX_INDICATOR_SET_COLOR(MAC_MOD_INDEX, 255, 255, 255);
        if (!rgb_matrix_get_flags()) {
            RGB_MATRIX_INDICATOR_SET_COLOR(WIN_MOD_INDEX, 0, 0, 0);
         }
      } break;

      case 0:{
       if (L_WIN) {
            RGB_MATRIX_INDICATOR_SET_COLOR(WIN_MOD_INDEX, 255, 255, 255);
            if (!rgb_matrix_get_flags()) {
               RGB_MATRIX_INDICATOR_SET_COLOR(MAC_MOD_INDEX, 0, 0, 0);
            }
            }else{
                if (!rgb_matrix_get_flags()) {
                   RGB_MATRIX_INDICATOR_SET_COLOR(WIN_MOD_INDEX, 0, 0, 0);
                 }
              }
         } break;

     case 1:{
       if (L_MAC) {
            RGB_MATRIX_INDICATOR_SET_COLOR(MAC_MOD_INDEX, 255, 255, 255);
            if (!rgb_matrix_get_flags()) {
               RGB_MATRIX_INDICATOR_SET_COLOR(WIN_MOD_INDEX, 0, 0, 0);
            }
            }else{
                if (!rgb_matrix_get_flags()) {
                   RGB_MATRIX_INDICATOR_SET_COLOR(MAC_MOD_INDEX, 0, 0, 0);
                 }
              }
         } break;

      default:{
         if (!rgb_matrix_get_flags()) {
            RGB_MATRIX_INDICATOR_SET_COLOR(WIN_MOD_INDEX, 0, 0, 0);
            RGB_MATRIX_INDICATOR_SET_COLOR(MAC_MOD_INDEX, 0, 0, 0);
         }
      }
    }
    return false;
}


void suspend_power_down_kb(void) {
    writePinLow(IS31FL3743A_SDB_PIN);
    suspend_power_down_user();
}

void suspend_wakeup_init_kb(void) {
    writePinHigh(IS31FL3743A_SDB_PIN);
    suspend_wakeup_init_user();
}
#endif

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_user(keycode, record)) {
        return false;
    }
    switch (keycode) {
#    ifdef RGB_MATRIX_ENABLE
        case RGB_TOG:
            if (record->event.pressed) {
                switch (rgb_matrix_get_flags()) {
                    case LED_FLAG_ALL: {
                        rgb_matrix_set_flags(LED_FLAG_NONE);
                        rgb_matrix_set_color_all(0, 0, 0);
                    } break;
                    default: {
                        rgb_matrix_set_flags(LED_FLAG_ALL);
                    } break;
                }
            }
         return false;
#    endif
     case TO(0):
      if (record->event.pressed) {
       L_WIN = 1;
       set_single_persistent_default_layer(0); // Save default layer 0 to eeprom
      } else {
       L_WIN = 0;
      }
      return true; // continue all further processing of this key

     case MO(2):
      if (record->event.pressed) {
       FN_WIN = 1;
      } else {
       FN_WIN = 0;
      }
      return true; // continue all further processing of this key

     case TO(1):
      if (record->event.pressed) {
       L_MAC = 1;
       set_single_persistent_default_layer(1);  //Save default layer 1 to eeprom
      } else {
       L_MAC = 0;
      }
      return true; // continue all further processing of this key

     case MO(3):
      if (record->event.pressed) {
       FN_MAC = 1;
      } else {
       FN_MAC = 0;
      }
      return true; // continue all further processing of this key
    default:
      return true;
    }
}

void board_init(void) {
    // JTAG-DP Disabled and SW-DP Disabled
    AFIO->MAPR = (AFIO->MAPR & ~AFIO_MAPR_SWJ_CFG_Msk) | AFIO_MAPR_SWJ_CFG_DISABLE;
}
