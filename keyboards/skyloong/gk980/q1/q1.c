//  Copyright 2023 JZ-Skyloong (@JZ-Skyloong)
// SPDX-License-Identifier: GPL-2.0-or-later
#include "quantum.h"

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
    {0, CS1_SW12,  CS2_SW12,  CS3_SW12},
    {0, CS10_SW2,  CS11_SW2,  CS12_SW2},
    {0, CS10_SW3,  CS11_SW3,  CS12_SW3},
      //encoder no led
    {0, CS10_SW5,  CS11_SW5,  CS12_SW5},
    {0, CS10_SW6,  CS11_SW6,  CS12_SW6},
    {0, CS10_SW7,  CS11_SW7,  CS12_SW7},
    {0, CS10_SW8,  CS11_SW8,  CS12_SW8},

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
    {0, CS4_SW12,  CS5_SW12,  CS6_SW12},
    {0, CS13_SW2,  CS14_SW2,  CS15_SW2},
    {0, CS13_SW3,  CS14_SW3,  CS15_SW3},
    {0, CS13_SW4,  CS14_SW4,  CS15_SW4},
    {0, CS13_SW5,  CS14_SW5,  CS15_SW5},
    {0, CS13_SW6,  CS14_SW6,  CS15_SW6},
    {0, CS13_SW7,  CS14_SW7,  CS15_SW7},

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
    {0, CS7_SW12,  CS8_SW12,  CS9_SW12},
    {0, CS16_SW2,  CS17_SW2,  CS18_SW2},
    {0, CS16_SW3,  CS17_SW3,  CS18_SW3},
    {0, CS16_SW4,  CS17_SW4,  CS18_SW4},
    {0, CS16_SW5,  CS17_SW5,  CS18_SW5},
    {0, CS16_SW6,  CS17_SW6,  CS18_SW6},
    {0, CS16_SW7,  CS17_SW7,  CS18_SW7},


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
    {1, CS1_SW12,  CS2_SW12,  CS3_SW12},
    {1, CS10_SW3,  CS11_SW3,  CS12_SW3},
    {1, CS10_SW4,  CS11_SW4,  CS12_SW4},
    {1, CS10_SW5,  CS11_SW5,  CS12_SW5},
    {1, CS10_SW6,  CS11_SW6,  CS12_SW6},

    {1, CS4_SW1,   CS5_SW1,   CS6_SW1},
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
    {1, CS13_SW3,  CS14_SW3,  CS15_SW3},
    {1, CS13_SW4,  CS14_SW4,  CS15_SW4},
    {1, CS13_SW5,  CS14_SW5,  CS15_SW5},
    {1, CS13_SW6,  CS14_SW6,  CS15_SW6},
    {1, CS13_SW7,  CS14_SW7,  CS15_SW7},


    {1, CS7_SW1,   CS8_SW1,   CS9_SW1},
    {1, CS7_SW2,   CS8_SW2,   CS9_SW2},
    {1, CS7_SW3,   CS8_SW3,   CS9_SW3},
    {1, CS7_SW5,   CS8_SW5,   CS9_SW5},
    {1, CS7_SW6,   CS8_SW6,   CS9_SW6},
    {1, CS7_SW8,   CS8_SW8,   CS9_SW8},
    {1, CS7_SW10,  CS8_SW10,  CS9_SW10},
    {1, CS7_SW11,  CS8_SW11,  CS9_SW11},
    {1, CS7_SW12,  CS8_SW12,  CS9_SW12},
    {1, CS16_SW2,  CS17_SW2,  CS18_SW2},
    {1, CS16_SW3,  CS17_SW3,  CS18_SW3},
    {1, CS16_SW4,  CS17_SW4,  CS18_SW4},
    {1, CS16_SW5,  CS17_SW5,  CS18_SW5},
    {1, CS16_SW6,  CS17_SW6,  CS18_SW6}
};

#endif

void suspend_power_down_kb() {
#    ifdef RGB_MATRIX_ENABLE
    writePinLow(SDB);
#    endif
    writePinLow(MAC_PIN);
    suspend_power_down_user();
}

void suspend_wakeup_init_kb() {
#    ifdef RGB_MATRIX_ENABLE
    writePinHigh(SDB);
#    endif
    suspend_wakeup_init_user();
}

bool shutdown_kb(bool jump_to_bootloader) {
    writePinLow(SDB);
    return shutdown_user(jump_to_bootloader);
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
#   ifdef RGB_MATRIX_ENABLE
    setPinOutput(SDB);
    writePinHigh(SDB);
#   endif
    setPinOutput(MAC_PIN);
    writePinHigh(MAC_PIN);
}
