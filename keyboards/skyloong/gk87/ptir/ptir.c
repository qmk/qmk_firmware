//  Copyright 2023 JZ-Skyloong (@JZ-Skyloong)
// SPDX-License-Identifier: GPL-2.0-or-later
#include "quantum.h"
int FN_WIN = 0;
int FN_MAC = 0;
int L_WIN = 0;
int L_MAC = 0;

#if defined(RGB_MATRIX_ENABLE)  /*&& defined(CAPS_LOCK_INDEX)*/
const is31_led PROGMEM g_is31_leds[RGB_MATRIX_LED_COUNT] = {
/* Refer to IS31 manual for these locations
 *   driver
 *   |  R location
 *   |  |          G location
 *   |  |          |          B location
 *   |  |          |          | */
    {0, CS1_SW1,   CS2_SW1,   CS3_SW1},
    {0, CS1_SW3,   CS2_SW3,   CS3_SW3},
    {0, CS1_SW4,   CS2_SW4,   CS3_SW4},
    {0, CS1_SW5,   CS2_SW5,   CS3_SW5},
    {0, CS1_SW6,   CS2_SW6,   CS3_SW6},
    {0, CS1_SW7,   CS2_SW7,   CS3_SW7},
    {0, CS1_SW8,   CS2_SW8,   CS3_SW8},
    {0, CS1_SW9,   CS2_SW9,   CS3_SW9},
    {0, CS1_SW10,  CS2_SW10,  CS3_SW10},
    {0, CS1_SW11,  CS2_SW11,  CS3_SW11},
    {0, CS10_SW1,  CS11_SW1,  CS12_SW1},
    {0, CS10_SW2,  CS11_SW2,  CS12_SW2},
    {0, CS10_SW3,  CS11_SW3,  CS12_SW3},
    {0, CS10_SW4,  CS11_SW4,  CS12_SW4},
    {0, CS10_SW5,  CS11_SW5,  CS12_SW5},
    {1, CS10_SW4,  CS11_SW4,  CS12_SW4},

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
    {0, CS13_SW1,  CS14_SW1,  CS15_SW1},
    {0, CS13_SW2,  CS14_SW2,  CS15_SW2},
    {0, CS13_SW3,  CS14_SW3,  CS15_SW3},
    {0, CS13_SW4,  CS14_SW4,  CS15_SW4},
    {0, CS13_SW5,  CS14_SW5,  CS15_SW5},
    {1, CS10_SW5,  CS11_SW5,  CS12_SW5},

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
    {0, CS16_SW1,  CS17_SW1,  CS18_SW1},
    {0, CS16_SW2,  CS17_SW2,  CS18_SW2},
    {0, CS16_SW3,  CS17_SW3,  CS18_SW3},
    {0, CS16_SW4,  CS17_SW4,  CS18_SW4},
    {0, CS16_SW5,  CS17_SW5,  CS18_SW5},
    {1, CS13_SW5,  CS14_SW5,  CS15_SW5},


    {1, CS1_SW1,   CS2_SW1,   CS3_SW1},
    {1, CS1_SW2,   CS2_SW2,   CS3_SW2},
    {1, CS1_SW3,   CS2_SW3,   CS3_SW3},
    {1, CS1_SW4,   CS2_SW4,   CS3_SW4},
    {1, CS1_SW5,   CS2_SW5,   CS3_SW5},
    {1, CS1_SW6,   CS2_SW6,   CS3_SW6},
    {1, CS1_SW7,   CS2_SW7,   CS3_SW7},
    {1, CS1_SW8,   CS2_SW8,   CS3_SW8},
    {1, CS1_SW9,   CS2_SW9,   CS3_SW9},
    {1, CS1_SW10,  CS2_SW10,  CS3_SW10},
    {1, CS1_SW11,  CS2_SW11,  CS3_SW11},
    {1, CS10_SW1,  CS11_SW1,  CS12_SW1},
    {1, CS10_SW2,  CS11_SW2,  CS12_SW2},
    {1, CS10_SW3,  CS11_SW3,  CS12_SW3},

    {1, CS4_SW1,   CS5_SW1,   CS6_SW1},
    {1, CS7_SW4,   CS8_SW4,   CS9_SW4},
    {1, CS4_SW2,   CS5_SW2,   CS6_SW2},
    {1, CS4_SW3,   CS5_SW3,   CS6_SW3},
    {1, CS4_SW4,   CS5_SW4,   CS6_SW4},
    {1, CS4_SW5,   CS5_SW5,   CS6_SW5},
    {1, CS4_SW6,   CS5_SW6,   CS6_SW6},
    {1, CS4_SW7,   CS5_SW7,   CS6_SW7},
    {1, CS4_SW8,   CS5_SW8,   CS6_SW8},
    {1, CS4_SW9,   CS5_SW9,   CS6_SW9},
    {1, CS4_SW10,  CS5_SW10,  CS6_SW10},
    {1, CS4_SW11,  CS5_SW11,  CS6_SW11},
    {1, CS13_SW2,  CS14_SW2,  CS15_SW2},
    {1, CS13_SW4,  CS14_SW4,  CS15_SW4},


    {1, CS7_SW1,   CS8_SW1,   CS9_SW1},
    {1, CS7_SW2,   CS8_SW2,   CS9_SW2},
    {1, CS7_SW3,   CS8_SW3,   CS9_SW3},
    {1, CS7_SW5,   CS8_SW5,   CS9_SW5},
    {1, CS7_SW6,   CS8_SW6,   CS9_SW6},
    {1, CS7_SW8,   CS8_SW8,   CS9_SW8},
    {1, CS7_SW10,  CS8_SW10,  CS9_SW10},
    {1, CS7_SW11,  CS8_SW11,  CS9_SW11},
    {1, CS16_SW1,  CS17_SW1,  CS18_SW1},
    {1, CS16_SW2,  CS17_SW2,  CS18_SW2},
    {1, CS16_SW3,  CS17_SW3,  CS18_SW3},
    {1, CS16_SW4,  CS17_SW4,  CS18_SW4},
    {1, CS16_SW5,  CS17_SW5,  CS18_SW5}
};


bool rgb_matrix_indicators_advanced_kb(uint8_t led_min, uint8_t led_max) {
    if (!rgb_matrix_indicators_advanced_user(led_min, led_max)) {
        return false;
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

#endif

bool led_update_kb(led_t led_state) {
    bool res = led_update_user(led_state);
    if(res) {
        writePin(CAPS_PIN, led_state.caps_lock);
        writePin(SCR_PIN, led_state.scroll_lock);
    }
    return res;
}

void suspend_power_down_kb() {
#    ifdef RGB_MATRIX_ENABLE
    rgb_matrix_set_flags(LED_FLAG_NONE);
    rgb_matrix_set_color_all(0, 0, 0);
    writePinLow(SDB);
#    endif
    writePinLow(SCR_PIN);
    writePinLow(CAPS_PIN);
    writePinLow(MAC_PIN);
}

void suspend_wakeup_init_kb() {
#    ifdef RGB_MATRIX_ENABLE
    writePinHigh(SDB);
    rgb_matrix_set_flags(LED_FLAG_ALL);
#    endif
}

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

layer_state_t default_layer_state_set_kb(layer_state_t state) {
    switch (get_highest_layer(state)) {
    case 0:
        writePinLow(MAC_PIN);
        break;
    case 1:
        writePinHigh(MAC_PIN);
        break;
    }
  return state;
}

void board_init(void) {
    // JTAG-DP Disabled and SW-DP Disabled
    AFIO->MAPR = (AFIO->MAPR & ~AFIO_MAPR_SWJ_CFG_Msk) | AFIO_MAPR_SWJ_CFG_DISABLE;
    setPinOutput(SDB);
    writePinHigh(SDB);
    setPinOutput(CAPS_PIN);
    writePinHigh(CAPS_PIN);
    setPinOutput(SCR_PIN);
    writePinHigh(SCR_PIN);
    setPinOutput(MAC_PIN);
    writePinLow(MAC_PIN);
}
