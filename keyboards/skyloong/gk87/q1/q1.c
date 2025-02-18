//  Copyright 2023 NaturalZh (@NaturalZh)
// SPDX-License-Identifier: GPL-2.0-or-later
#include "quantum.h"
#include "led_hc595.h"

uint8_t IND = 0;  //buffer of LED Display

int FN_ON = 0;
_Bool WIN_LOCK = 0;

#if defined(RGB_MATRIX_ENABLE)  /*&& defined(CAPS_LOCK_INDEX)*/
const aw20216s_led_t PROGMEM g_aw20216s_leds[AW20216S_LED_COUNT] = {
/* Each AW20216 channel is controlled by a register at some offset between 0x00
 * and 0xD7 inclusive.
 * See drivers/awinic/aw20216.h for the mapping between register offsets and
 * driver pin locations.
 *   driver
 *   |  R location
 *   |  |          G location
 *   |  |          |          B location
 *   |  |          |          | */
    {0, CS1_SW1,   CS2_SW1,   CS3_SW1},  //ESC
    {0, CS1_SW3,   CS2_SW3,   CS3_SW3},  //F1
    {0, CS1_SW4,   CS2_SW4,   CS3_SW4},
    {0, CS1_SW5,   CS2_SW5,   CS3_SW5},  //F3
    {0, CS1_SW6,   CS2_SW6,   CS3_SW6},
    {0, CS1_SW7,   CS2_SW7,   CS3_SW7},  //F5
    {0, CS1_SW8,   CS2_SW8,   CS3_SW8},
    {0, CS1_SW9,   CS2_SW9,   CS3_SW9},  //F7
    {0, CS1_SW10,  CS2_SW10,  CS3_SW10},
    {0, CS1_SW11,  CS2_SW11,  CS3_SW11},  //F9
    {0, CS1_SW12,  CS2_SW12,  CS3_SW12},  //F10
    {0, CS10_SW2,  CS11_SW2,  CS12_SW2},
    {0, CS10_SW3,  CS11_SW3,  CS12_SW3},  //F12
    //encoder no led

    {0, CS4_SW1,   CS5_SW1,   CS6_SW1},   //`~
    {0, CS4_SW2,   CS5_SW2,   CS6_SW2},   //1
    {0, CS4_SW3,   CS5_SW3,   CS6_SW3},   //2
    {0, CS4_SW4,   CS5_SW4,   CS6_SW4},
    {0, CS4_SW5,   CS5_SW5,   CS6_SW5},   //4
    {0, CS4_SW6,   CS5_SW6,   CS6_SW6},
    {0, CS4_SW7,   CS5_SW7,   CS6_SW7},   //6
    {0, CS4_SW8,   CS5_SW8,   CS6_SW8},
    {0, CS4_SW9,   CS5_SW9,   CS6_SW9},   //8
    {0, CS4_SW10,  CS5_SW10,  CS6_SW10},
    {0, CS4_SW11,  CS5_SW11,  CS6_SW11},  //0
    {0, CS4_SW12,  CS5_SW12,  CS6_SW12},  //-_
    {0, CS13_SW2,  CS14_SW2,  CS15_SW2},  //=+
    {0, CS13_SW3,  CS14_SW3,  CS15_SW3},  //BS
    {0, CS13_SW4,  CS14_SW4,  CS15_SW4},  //INS
    {0, CS13_SW5,  CS14_SW5,  CS15_SW5},  //Home
    {0, CS13_SW6,  CS14_SW6,  CS15_SW6},  //PgUp

    {0, CS7_SW1,   CS8_SW1,   CS9_SW1},   //Tab
    {0, CS7_SW2,   CS8_SW2,   CS9_SW2},   //Q
    {0, CS7_SW3,   CS8_SW3,   CS9_SW3},   //W
    {0, CS7_SW4,   CS8_SW4,   CS9_SW4},   //E
    {0, CS7_SW5,   CS8_SW5,   CS9_SW5},   //R
    {0, CS7_SW6,   CS8_SW6,   CS9_SW6},   //T
    {0, CS7_SW7,   CS8_SW7,   CS9_SW7},   //Y
    {0, CS7_SW8,   CS8_SW8,   CS9_SW8},   //U
    {0, CS7_SW9,   CS8_SW9,   CS9_SW9},   //I
    {0, CS7_SW10,  CS8_SW10,  CS9_SW10},   //O
    {0, CS7_SW11,  CS8_SW11,  CS9_SW11},   //P
    {0, CS7_SW12,  CS8_SW12,  CS9_SW12},   //[
    {0, CS16_SW2,  CS17_SW2,  CS18_SW2},   //]
    {0, CS16_SW3,  CS17_SW3,  CS18_SW3},   //|
    {0, CS16_SW4,  CS17_SW4,  CS18_SW4},   //DEL
    {0, CS16_SW5,  CS17_SW5,  CS18_SW5},   //END
    {0, CS16_SW6,  CS17_SW6,  CS18_SW6},   //PgDn

    {1, CS1_SW1,   CS2_SW1,   CS3_SW1},   //Cap
    {1, CS1_SW2,   CS2_SW2,   CS3_SW2},   //A
    {1, CS1_SW3,   CS2_SW3,   CS3_SW3},   //S
    {1, CS1_SW4,   CS2_SW4,   CS3_SW4},   //D
    {1, CS1_SW5,   CS2_SW5,   CS3_SW5},   //F
    {1, CS1_SW6,   CS2_SW6,   CS3_SW6},   //G
    {1, CS1_SW7,   CS2_SW7,   CS3_SW7},   //H
    {1, CS1_SW8,   CS2_SW8,   CS3_SW8},   //J
    {1, CS1_SW9,   CS2_SW9,   CS3_SW9},   //K
    {1, CS1_SW10,  CS2_SW10,  CS3_SW10},   //L
    {1, CS1_SW11,  CS2_SW11,  CS3_SW11},   //;
    {1, CS1_SW12,  CS2_SW12,  CS3_SW12},   //.
    {1, CS10_SW2,  CS11_SW2,  CS12_SW2},   //Ent

    {1, CS4_SW1,   CS5_SW1,   CS6_SW1},   //Shift
    {1, CS4_SW2,   CS5_SW2,   CS6_SW2},   //Z
    {1, CS4_SW3,   CS5_SW3,   CS6_SW3},   //X
    {1, CS4_SW4,   CS5_SW4,   CS6_SW4},   //C
    {1, CS4_SW5,   CS5_SW5,   CS6_SW5},   //V
    {1, CS4_SW6,   CS5_SW6,   CS6_SW6},   //B
    {1, CS4_SW7,   CS5_SW7,   CS6_SW7},   //N
    {1, CS4_SW8,   CS5_SW8,   CS6_SW8},   //M
    {1, CS4_SW9,   CS5_SW9,   CS6_SW9},   //,
    {1, CS4_SW10,  CS5_SW10,  CS6_SW10},   //.
    {1, CS4_SW11,  CS5_SW11,  CS6_SW11},   //?
    {1, CS10_SW3,  CS11_SW3,  CS12_SW3},   //Shift
    {1, CS13_SW4,  CS14_SW4,  CS15_SW4},   //Up

    {1, CS7_SW1,   CS8_SW1,   CS9_SW1},   //Ctrl
    {1, CS7_SW2,   CS8_SW2,   CS9_SW2},   //Com
    {1, CS7_SW3,   CS8_SW3,   CS9_SW3},   //Alt
    {1, CS7_SW4,   CS8_SW4,   CS9_SW4},   //SPAC1
    {1, CS7_SW6,   CS8_SW6,   CS9_SW6},   //SPAC
    {1, CS7_SW8,   CS8_SW8,   CS9_SW8},   //SPAC2
    {1, CS7_SW10,  CS8_SW10,  CS9_SW10},   //Alt
    {1, CS7_SW11,  CS8_SW11,  CS9_SW11},   //Fn
    {1, CS7_SW12,  CS8_SW12,  CS9_SW12},   //Menu
    {1, CS16_SW2,  CS17_SW2,  CS18_SW2},   //Ctrl
    {1, CS16_SW3,  CS17_SW3,  CS18_SW3},   //Left
    {1, CS16_SW4,  CS17_SW4,  CS18_SW4},   //Down
    {1, CS16_SW5,  CS17_SW5,  CS18_SW5},   //Right
};
#endif


bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_user(keycode, record)) {
        return false;
    }
    switch (keycode) {
#  ifdef RGB_MATRIX_ENABLE
    case RM_TOGG:
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
    case RM_VALU:
       rgb_matrix_set_flags(LED_FLAG_ALL);
       return true;
#    endif

    case MO(1):
      if (record->event.pressed) {
       FN_ON = 1;
      } else {
       FN_ON = 0;
      }
      return true;

    case MO(2):
      if (record->event.pressed) {
       FN_ON = 1;
      } else {
       FN_ON = 0;
      }
      return true;

    case MO(3):
      if (record->event.pressed) {
       FN_ON = 1;
      } else {
       FN_ON = 0;
      }
      return true;

    case KC_LGUI:
      if (FN_ON){
          if ( record->event.pressed){
             WIN_LOCK = !WIN_LOCK ; //change win lock state
            }
          if (!WIN_LOCK) {
             IND = IND & (~WINLK_ON);   //Close win lock display
             s_serial_to_parallel(IND);
             gpio_write_pin_high(WIN_LOCK_PIN);
             return false; //windows key locked do nothing
            }
          s_serial_to_parallel(IND);
        }
      if (WIN_LOCK) {
             IND = IND | WINLK_ON;   //Open win lock display
             s_serial_to_parallel(IND);
             gpio_write_pin_low(WIN_LOCK_PIN);
             return false; //windows key locked do nothing
            }
      return true;  // continue all further processing of this key

    default:
      return true;
    }
   s_serial_to_parallel(IND);
}

void suspend_power_down_kb() {
    gpio_write_pin_low(AW20216S_EN_PIN);
    gpio_write_pin_high(WIN_LOCK_PIN);
    s_serial_to_parallel(0);
    suspend_power_down_user();
}

void suspend_wakeup_init_kb() {
    gpio_write_pin_high(AW20216S_EN_PIN);
    gpio_write_pin(WIN_LOCK_PIN,!WIN_LOCK);
    s_serial_to_parallel(IND);
    suspend_wakeup_init_user();
}

bool shutdown_kb(bool jump_to_bootloader) {
    gpio_write_pin_high(WIN_LOCK_PIN);
    s_serial_to_parallel(0);
    return true;
}

layer_state_t default_layer_state_set_kb(layer_state_t state) {
    switch (get_highest_layer(state)) {
    case 0:
        //switch to win layer display
        IND = IND & (~MAC_ON);
        IND = IND | WIN_ON;
        break;
    case 1:
        //switch to mac layer display
        IND = IND & (~WIN_ON);
        IND = IND | MAC_ON;
        break;
    }
    s_serial_to_parallel(IND);
  return default_layer_state_set_user(state);
}

bool rgb_matrix_indicators_advanced_kb(uint8_t led_min, uint8_t led_max) {
    if (!rgb_matrix_indicators_advanced_user(led_min, led_max)) {
        return false;
    }

    //caps lock display
    if (host_keyboard_led_state().caps_lock) {
       // RGB_MATRIX_INDICATOR_SET_COLOR(CAPS_LOCK_INDEX, 255, 255, 255);
        IND = IND | CAPS_ON;
    } else {

        IND = IND & (~CAPS_ON);
    }
    //number lock display
    if (host_keyboard_led_state().num_lock) {
       // RGB_MATRIX_INDICATOR_SET_COLOR(NUM_LOCK_INDEX, 255, 255, 255);
        IND = IND | NUM_ON;
    } else {

        IND = IND & (~NUM_ON);
    }
    //scroll lock display
    if (host_keyboard_led_state().scroll_lock) {
       // RGB_MATRIX_INDICATOR_SET_COLOR(SCR_LOCK_INDEX, 255, 255, 255);
        IND = IND | SCR_ON;
    } else {

        IND = IND & (~SCR_ON);
    }

    s_serial_to_parallel(IND);
    return true;
}

void board_init(void) {
    // JTAG-DP Disabled and SW-DP Disabled
    AFIO->MAPR = (AFIO->MAPR & ~AFIO_MAPR_SWJ_CFG_Msk) | AFIO_MAPR_SWJ_CFG_DISABLE;
    gpio_set_pin_output(WIN_LOCK_PIN);
    gpio_write_pin_high(WIN_LOCK_PIN);
    s_serial_to_parallel(0xFF);
    IND = SKYLOONG;
}

