/* Copyright 2021 bdtc123
 * Copyright 2021 sigprof
 * Copyright 2021 peepeetee
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "quantum.h"

#ifdef RGB_MATRIX_ENABLE

#    include "i2c_master.h"
#    include "is31fl3733.h"
#    include "ws2812.h"


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
    { 0, SW8_CS13, SW7_CS13, SW9_CS13 },

    { 0, SW11_CS1,  SW10_CS1,  SW12_CS1 },
    { 0, SW11_CS11, SW10_CS11, SW12_CS11 },
    { 0, SW11_CS2,  SW10_CS2,  SW12_CS2 },
    { 0, SW11_CS3,  SW10_CS3,  SW12_CS3 },
    { 0, SW11_CS4,  SW10_CS4,  SW12_CS4 },
    { 0, SW11_CS5,  SW10_CS5,  SW12_CS5 },
    { 0, SW11_CS6,  SW10_CS6,  SW12_CS6 },
    { 0, SW11_CS7,  SW10_CS7,  SW12_CS7 },
    { 0, SW11_CS8,  SW10_CS8,  SW12_CS8 },
    { 0, SW11_CS9,  SW10_CS9,  SW12_CS9 },
    { 0, SW11_CS10, SW10_CS10, SW12_CS10 },
    { 0, SW11_CS12, SW10_CS12, SW12_CS12 },
    { 0, SW11_CS13, SW10_CS13, SW12_CS13 },
    { 0, SW11_CS14, SW10_CS14, SW12_CS14 },

    { 0, SW8_CS16, SW7_CS16, SW9_CS16 },
    { 0, SW8_CS14, SW7_CS14, SW9_CS14 },
    { 0, SW8_CS15, SW7_CS15, SW9_CS15 },
    { 0, SW5_CS15, SW4_CS15, SW6_CS15 },
    { 0, SW11_CS15, SW10_CS15, SW12_CS15 },
    { 0, SW11_CS16, SW10_CS16, SW12_CS16 },
    { 0, SW2_CS16, SW1_CS16, SW3_CS16 },
    { 0, SW2_CS15, SW1_CS15, SW3_CS15 },
    { 0, SW5_CS16, SW4_CS16, SW6_CS16 }
};

led_config_t g_led_config = { {
  {   0,   1,   2,     3,     4,     5,     6,     7,     8,   9,  10,  11,  12,  13 },
  {  14,  15,  16,    17,    18,    19,    20,    21,    22,  23,  24,  25,  26,  27 },
  {  28,  29,  30,    31,    32,    33,    34,    35,    36,  37,  38,  39,  40,NO_LED},
  {  41,  58,  42,    43,    44,    45,    46,    47,    48,  49,  51,  52,  53,  54 },
  {  55,  56,  57,NO_LED,NO_LED,    58,NO_LED,NO_LED,NO_LED,  59,  60,  61,  62,  63 }
}, {
    // Esc, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, -, =, Backspace
    {   0,   0 }, {  15,   0 }, {  30,   0 }, {  45,   0 }, {  60,   0 }, {  75,   0 }, {  90,   0 }, { 105,   0 }, { 120,   0 }, { 135,   0 }, { 150,   0 }, { 165,   0 }, { 180,   0 }, { 202,   0 },
    // Tab, Q, W, E, R, T, Y, U, I, O, P, [, ],  ,
    {   7,  16 }, {  22,  16 }, {  37,  16 }, {  52,  16 }, {  67,  16 }, {  82,  16 }, {  97,  16 }, { 112,  16 }, { 127,  16 }, { 142,  16 }, { 157,  16 }, { 172,  16 }, { 187,  16 }, { 206,  16 },
    // Capslock, A, S, D, F, G, H, J, K, L, ;, ', Enter
    {  11,  32 }, {  26,  32 }, {  41,  32 }, {  56,  32 }, {  71,  32 }, {  86,  32 }, { 101,  32 }, { 116,  32 }, { 131,  32 }, { 146,  32 }, { 161,  32 }, { 176,  32 }, { 198,  32 },
    // LShift, <, Z, X, C, V, B, N, M, ,, ., /, Shift, Up,
    {   3,  48 }, {  22,  48 }, {  33,  48 }, {  48,  48 }, {  63,  48 }, {  78,  48 }, {  93,  48 }, { 108,  48 }, { 123,  48 }, { 138,  48 }, { 153,  48 }, { 168,  48 }, { 194,  48 }, { 213,  48 },
    // Ctrl, GUI, Alt, Space, RAlt, FN, Left, Down, Right
    {   3,  64 }, {  22,  64 }, {  33,  64 }, { 101,  64 }, { 135,  64 }, { 153,  64 }, { 195,  64 }, { 210,  64 }, { 225,  64 }
#    if WS2812_LED_TOTAL > 0
        ,{ 28, 40}, { 62, 40}, { 96, 40}, {130, 40}, {164, 40}, {198, 40}
#    endif
}, {
    // Esc, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, -, =, Backspace
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,
    // Tab, Q, W, E, R, T, Y, U, I, O, P, [, ], Enter
    1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,
    // Capslock, A, S, D, F, G, H, J, K, L, ;, ',#
    9, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    // LShift,backslash, Z, X, C, V, B, N, M, ,, ., Shift, Up, /
    1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 1, 4,
    // Ctrl, GUI, Alt, Space, RAlt, FN, Left, Down, Right
    1, 1, 1, 4, 1, 1, 1, 1, 1
#    if WS2812_LED_TOTAL > 0
        ,2, 2, 2, 2, 2, 2
#    endif
} };

bool rgb_matrix_indicators_kb(void) {
    if (!rgb_matrix_indicators_user()) {
        return false;
    }
    if (host_keyboard_led_state().caps_lock) {
        rgb_matrix_set_color(28, 0xFF, 0xFF, 0xFF);
    }
    return true;
}

// clang-format on

// ==========================================================================
// Custom RGB Matrix driver that combines IS31FL3733 and WS2812
// ==========================================================================

#    if WS2812_LED_TOTAL > 0
rgb_led_t rgb_matrix_ws2812_array[WS2812_LED_TOTAL];
#    endif

static void rgb_matrix_driver_init(void) {
    i2c_init();
    is31fl3733_init(0);
    for (uint8_t index = 0; index < IS31FL3733_LED_COUNT; index++) {
        bool enabled = true;
        is31fl3733_set_led_control_register(index, enabled, enabled, enabled);
    }
    is31fl3733_update_led_control_registers(0);
}

static void rgb_matrix_driver_flush(void) {
    is31fl3733_update_pwm_buffers(0);
#    if WS2812_LED_TOTAL > 0
    ws2812_setleds(rgb_matrix_ws2812_array, WS2812_LED_TOTAL);
#    endif
}

static void rgb_matrix_driver_set_color(int index, uint8_t red, uint8_t green, uint8_t blue) {
    if (index < IS31FL3733_LED_COUNT) {
        is31fl3733_set_color(index, red, green, blue);
    } else {
#    if WS2812_LED_TOTAL > 0
        rgb_matrix_ws2812_array[index - IS31FL3733_LED_COUNT].r = red;
        rgb_matrix_ws2812_array[index - IS31FL3733_LED_COUNT].g = green;
        rgb_matrix_ws2812_array[index - IS31FL3733_LED_COUNT].b = blue;
#    endif
    }
}

static void rgb_matrix_driver_set_color_all(uint8_t red, uint8_t green, uint8_t blue) {
    is31fl3733_set_color_all(red, green, blue);
#    if WS2812_LED_TOTAL > 0
    for (uint8_t i = 0; i < WS2812_LED_TOTAL; i++) {
        rgb_matrix_ws2812_array[i].r = red;
        rgb_matrix_ws2812_array[i].g = green;
        rgb_matrix_ws2812_array[i].b = blue;
    }
#    endif
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
