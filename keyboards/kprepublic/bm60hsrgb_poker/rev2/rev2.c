// Copyright 2021 bdtc123
// SPDX-License-Identifier: GPL-2.0-or-later
#include "quantum.h"

#if defined(RGB_MATRIX_ENABLE) && defined(RGBLIGHT_ENABLE)
#    error "RGBLight must not be enabled due to this keyboard's custom RGB Matrix driver"
#endif

#ifdef RGB_MATRIX_ENABLE

#    include "i2c_master.h"
#    include "is31fl3733.h"
#    include "ws2812.h"

// clang-format off
const is31fl3733_led_t PROGMEM g_is31fl3733_leds[IS31FL3733_LED_COUNT] = {
    { 0, SW2_CS1, SW1_CS1, SW3_CS1 },
    { 0, SW2_CS2, SW1_CS2, SW3_CS2 },
    { 0, SW2_CS3, SW1_CS3, SW3_CS3 },
    { 0, SW2_CS4, SW1_CS4, SW3_CS4 },
    { 0, SW2_CS5, SW1_CS5, SW3_CS5 },
    { 0, SW2_CS6, SW1_CS6, SW3_CS6 },
    { 0, SW2_CS7, SW1_CS7, SW3_CS7 },
    { 0, SW2_CS8, SW1_CS8, SW3_CS8 },
    { 0, SW2_CS9, SW1_CS9, SW3_CS9 },
    { 0, SW2_CS10, SW1_CS10, SW3_CS10 },
    { 0, SW2_CS11, SW1_CS11, SW3_CS11 },
    { 0, SW2_CS12, SW1_CS12, SW3_CS12 },
    { 0, SW2_CS13, SW1_CS13, SW3_CS13 },
    { 0, SW2_CS14, SW1_CS14, SW3_CS14 },

    { 0, SW5_CS1,  SW4_CS1,  SW6_CS1 },
    { 0, SW5_CS2,  SW4_CS2,  SW6_CS2 },
    { 0, SW5_CS3,  SW4_CS3,  SW6_CS3 },
    { 0, SW5_CS4,  SW4_CS4,  SW6_CS4 },
    { 0, SW5_CS5,  SW4_CS5,  SW6_CS5 },
    { 0, SW5_CS6,  SW4_CS6,  SW6_CS6 },
    { 0, SW5_CS7,  SW4_CS7,  SW6_CS7 },
    { 0, SW5_CS8,  SW4_CS8,  SW6_CS8 },
    { 0, SW5_CS9,  SW4_CS9,  SW6_CS9 },
    { 0, SW5_CS10, SW4_CS10, SW6_CS10 },
    { 0, SW5_CS11, SW4_CS11, SW6_CS11 },
    { 0, SW5_CS12, SW4_CS12, SW6_CS12 },
    { 0, SW5_CS13, SW4_CS13, SW6_CS13 },
    { 0, SW5_CS14, SW4_CS14, SW6_CS14 },

    { 0, SW8_CS1,  SW7_CS1,  SW9_CS1 },
    { 0, SW8_CS2,  SW7_CS2,  SW9_CS2 },
    { 0, SW8_CS3,  SW7_CS3,  SW9_CS3 },
    { 0, SW8_CS4,  SW7_CS4,  SW9_CS4 },
    { 0, SW8_CS5,  SW7_CS5,  SW9_CS5 },
    { 0, SW8_CS6,  SW7_CS6,  SW9_CS6 },
    { 0, SW8_CS7,  SW7_CS7,  SW9_CS7 },
    { 0, SW8_CS8,  SW7_CS8,  SW9_CS8 },
    { 0, SW8_CS9,  SW7_CS9,  SW9_CS9 },
    { 0, SW8_CS10, SW7_CS10, SW9_CS10 },
    { 0, SW8_CS11, SW7_CS11, SW9_CS11 },
    { 0, SW8_CS12, SW7_CS12, SW9_CS12 },
    { 0, SW8_CS14, SW7_CS14, SW9_CS14 },

    { 0, SW11_CS1,  SW10_CS1,  SW12_CS1 },
    { 0, SW11_CS2,  SW10_CS2,  SW12_CS2 },
    { 0, SW11_CS3,  SW10_CS3,  SW12_CS3 },
    { 0, SW11_CS4,  SW10_CS4,  SW12_CS4 },
    { 0, SW11_CS5,  SW10_CS5,  SW12_CS5 },
    { 0, SW11_CS6,  SW10_CS6,  SW12_CS6 },
    { 0, SW11_CS7,  SW10_CS7,  SW12_CS7 },
    { 0, SW11_CS8,  SW10_CS8,  SW12_CS8 },
    { 0, SW11_CS9,  SW10_CS9,  SW12_CS9 },
    { 0, SW11_CS10, SW10_CS10, SW12_CS10 },
    { 0, SW11_CS11, SW10_CS11, SW12_CS11 },
    { 0, SW11_CS13, SW10_CS13, SW12_CS13 },

    { 0, SW8_CS16, SW7_CS16, SW9_CS16 },
    { 0, SW8_CS15, SW7_CS15, SW9_CS15 },
    { 0, SW8_CS13, SW7_CS13, SW9_CS13 },
    { 0, SW5_CS15, SW4_CS15, SW6_CS15 },
    { 0, SW11_CS15, SW10_CS15, SW12_CS15 },
    { 0, SW11_CS16, SW10_CS16, SW12_CS16 },
    { 0, SW11_CS12, SW10_CS12, SW12_CS12 },
    { 0, SW5_CS16, SW4_CS16, SW6_CS16 }
};
// clang-format on

bool rgb_matrix_indicators_kb(void) {
    if (!rgb_matrix_indicators_user()) {
        return false;
    }
    if (host_keyboard_led_state().caps_lock) {
        rgb_matrix_set_color(28, 0xFF, 0xFF, 0xFF);
    }
    return true;
}

// ==========================================================================
// Custom RGB Matrix driver that combines IS31FL3733 and WS2812
// ==========================================================================

static void rgb_matrix_driver_init(void) {
    i2c_init();
    is31fl3733_init(0);
    ws2812_init();
    for (uint8_t index = 0; index < IS31FL3733_LED_COUNT; index++) {
        bool enabled = true;
        is31fl3733_set_led_control_register(index, enabled, enabled, enabled);
    }
    is31fl3733_update_led_control_registers(0);
}

static void rgb_matrix_driver_flush(void) {
    is31fl3733_update_pwm_buffers(0);
    ws2812_flush();
}

static void rgb_matrix_driver_set_color(int index, uint8_t red, uint8_t green, uint8_t blue) {
    if (index < IS31FL3733_LED_COUNT) {
        is31fl3733_set_color(index, red, green, blue);
    } else {
        ws2812_set_color(index - IS31FL3733_LED_COUNT, red, green, blue);
    }
}

static void rgb_matrix_driver_set_color_all(uint8_t red, uint8_t green, uint8_t blue) {
    is31fl3733_set_color_all(red, green, blue);
    ws2812_set_color_all(red, green, blue);
}

// clang-format off
const rgb_matrix_driver_t rgb_matrix_driver = {
    .init          = rgb_matrix_driver_init,
    .flush         = rgb_matrix_driver_flush,
    .set_color     = rgb_matrix_driver_set_color,
    .set_color_all = rgb_matrix_driver_set_color_all,
};
// clang-format on

#endif /* RGB_MATRIX_ENABLE */
