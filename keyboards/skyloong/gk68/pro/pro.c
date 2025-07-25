// Copyright 2023 NaturalZh (@NaturalZh)
// SPDX-License-Identifier: GPL-2.0-or-later
#include "quantum.h"

#if defined(RGB_MATRIX_ENABLE)  /*&& defined(CAPS_LOCK_INDEX)*/
const aw20216s_led_t PROGMEM g_aw20216s_leds[AW20216S_LED_COUNT] = {
/* Refer to aw20216 manual for these locations
 *   driver
 *   |  R location
 *   |  |          G location
 *   |  |          |          B location
 *   |  |          |          | */
    {0, SW1_CS1,   SW1_CS2,   SW1_CS3},
    {0, SW2_CS1,   SW2_CS2,   SW2_CS3},
    {0, SW3_CS1,   SW3_CS2,   SW3_CS3},
    {0, SW4_CS1,   SW4_CS2,   SW4_CS3},
    {0, SW5_CS1,   SW5_CS2,   SW5_CS3},
    {0, SW6_CS1,   SW6_CS2,   SW6_CS3},
    {0, SW7_CS1,   SW7_CS2,   SW7_CS3},
    {0, SW8_CS1,   SW8_CS2,   SW8_CS3},
    {0, SW9_CS1,   SW9_CS2,   SW9_CS3},
    {0, SW10_CS1,  SW10_CS2,  SW10_CS3},
    {0, SW11_CS1,  SW11_CS2,  SW11_CS3},
    {0, SW12_CS1,  SW12_CS2,  SW12_CS3},
    {0, SW1_CS18,  SW1_CS17,  SW1_CS16},
    {0, SW2_CS18,  SW2_CS17,  SW2_CS16},
    {0, SW3_CS18,  SW3_CS17,  SW3_CS16},

    {0, SW1_CS4,   SW1_CS5,   SW1_CS6},
    {0, SW2_CS4,   SW2_CS5,   SW2_CS6},
    {0, SW3_CS4,   SW3_CS5,   SW3_CS6},
    {0, SW4_CS4,   SW4_CS5,   SW4_CS6},
    {0, SW5_CS4,   SW5_CS5,   SW5_CS6},
    {0, SW6_CS4,   SW6_CS5,   SW6_CS6},
    {0, SW7_CS4,   SW7_CS5,   SW7_CS6},
    {0, SW8_CS4,   SW8_CS5,   SW8_CS6},
    {0, SW9_CS4,   SW9_CS5,   SW9_CS6},
    {0, SW10_CS4,  SW10_CS5,  SW10_CS6},
    {0, SW11_CS4,  SW11_CS5,  SW11_CS6},
    {0, SW12_CS4,  SW12_CS5,  SW12_CS6},
    {0, SW4_CS18,  SW4_CS17,  SW4_CS16},
    {0, SW5_CS18,  SW5_CS17,  SW5_CS16},
    {0, SW6_CS18,  SW6_CS17,  SW6_CS16},

    {0, SW1_CS7,   SW1_CS8,   SW1_CS9},
    {0, SW2_CS7,   SW2_CS8,   SW2_CS9},
    {0, SW3_CS7,   SW3_CS8,   SW3_CS9},
    {0, SW4_CS7,   SW4_CS8,   SW4_CS9},
    {0, SW5_CS7,   SW5_CS8,   SW5_CS9},
    {0, SW6_CS7,   SW6_CS8,   SW6_CS9},
    {0, SW7_CS7,   SW7_CS8,   SW7_CS9},
    {0, SW8_CS7,   SW8_CS8,   SW8_CS9},
    {0, SW9_CS7,   SW9_CS8,   SW9_CS9},
    {0, SW10_CS7,  SW10_CS8,  SW10_CS9},
    {0, SW11_CS7,  SW11_CS8,  SW11_CS9},
    {0, SW12_CS7,  SW12_CS8,  SW12_CS9},
    {0, SW7_CS18,  SW7_CS17,  SW7_CS16},
    {0, SW8_CS18,  SW8_CS17,  SW8_CS16},

    {0, SW1_CS10,  SW1_CS11,  SW1_CS12},
    {0, SW2_CS10,  SW2_CS11,  SW2_CS12},
    {0, SW3_CS10,  SW3_CS11,  SW3_CS12},
    {0, SW4_CS10,  SW4_CS11,  SW4_CS12},
    {0, SW5_CS10,  SW5_CS11,  SW5_CS12},
    {0, SW6_CS10,  SW6_CS11,  SW6_CS12},
    {0, SW7_CS10,  SW7_CS11,  SW7_CS12},
    {0, SW8_CS10,  SW8_CS11,  SW8_CS12},
    {0, SW9_CS10,  SW9_CS11,  SW9_CS12},
    {0, SW10_CS10, SW10_CS11, SW10_CS12},
    {0, SW11_CS10, SW11_CS11, SW11_CS12},
    {0, SW12_CS10, SW12_CS11, SW12_CS12},
    {0, SW9_CS18,  SW9_CS17,  SW9_CS16},
    {0, SW10_CS18,  SW10_CS17,  SW10_CS16},

    {0, SW1_CS13,  SW1_CS14,  SW1_CS15},
    {0, SW2_CS13,  SW2_CS14,  SW2_CS15},
    {0, SW3_CS13,  SW3_CS14,  SW3_CS15},
    {0, SW5_CS13,  SW5_CS14,  SW5_CS15},
    {0, SW6_CS13,  SW6_CS14,  SW6_CS15},
    {0, SW8_CS13,  SW8_CS14,  SW8_CS15},
    {0, SW9_CS13,  SW9_CS14,  SW9_CS15},
    {0, SW10_CS13, SW10_CS14, SW10_CS15},
    {0, SW11_CS13, SW11_CS14, SW11_CS15},
    {0, SW12_CS13, SW12_CS14, SW12_CS15},
    {0, SW11_CS18,  SW11_CS17,  SW11_CS16},
    {0, SW12_CS18,  SW12_CS17,  SW12_CS16}
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
    return true;
}
#endif

void suspend_power_down_kb(void) {
    gpio_write_pin_low(AW20216S_EN_PIN);
    suspend_power_down_user();
}

void suspend_wakeup_init_kb(void) {
    gpio_write_pin_high(AW20216S_EN_PIN);
    suspend_wakeup_init_user();
}
bool shutdown_kb(bool jump_to_bootloader) {
    gpio_write_pin_low(AW20216S_EN_PIN);
    return true;
}



void board_init(void) {
    // JTAG-DP Disabled and SW-DP Disabled
    AFIO->MAPR = (AFIO->MAPR & ~AFIO_MAPR_SWJ_CFG_Msk) | AFIO_MAPR_SWJ_CFG_DISABLE;
}
