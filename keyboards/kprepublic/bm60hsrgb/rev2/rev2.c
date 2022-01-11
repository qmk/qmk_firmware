/* Copyright 2021 bdtc123
 * Copyright 2021 sigprof
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
#include "rev2.h"

#ifdef RGB_MATRIX_ENABLE

#    include "i2c_master.h"
#    include "is31fl3733.h"
#    include "ws2812.h"

const is31_led PROGMEM g_is31_leds[DRIVER_LED_TOTAL] = {
    { 0, B_1, A_1, C_1 },
    { 0, B_2, A_2, C_2 },
    { 0, B_3, A_3, C_3 },
    { 0, B_4, A_4, C_4 },
    { 0, B_5, A_5, C_5 },
    { 0, B_6, A_6, C_6 },
    { 0, B_7, A_7, C_7 },
    { 0, B_8, A_8, C_8 },
    { 0, B_9, A_9, C_9 },
    { 0, B_10, A_10, C_10 },
    { 0, B_11, A_11, C_11 },
    { 0, B_12, A_12, C_12 },
    { 0, B_13, A_13, C_13 },
    { 0, B_14, A_14, C_14 },

    { 0, E_1,  D_1,  F_1 },
    { 0, E_2,  D_2,  F_2 },
    { 0, E_3,  D_3,  F_3 },
    { 0, E_4,  D_4,  F_4 },
    { 0, E_5,  D_5,  F_5 },
    { 0, E_6,  D_6,  F_6 },
    { 0, E_7,  D_7,  F_7 },
    { 0, E_8,  D_8,  F_8 },
    { 0, E_9,  D_9,  F_9 },
    { 0, E_10, D_10, F_10 },
    { 0, E_11, D_11, F_11 },
    { 0, E_12, D_12, F_12 },
    { 0, E_13, D_13, F_13 },
    { 0, E_14, D_14, F_14 },

    { 0, H_1,  G_1,  I_1 },
    { 0, H_2,  G_2,  I_2 },
    { 0, H_3,  G_3,  I_3 },
    { 0, H_4,  G_4,  I_4 },
    { 0, H_5,  G_5,  I_5 },
    { 0, H_6,  G_6,  I_6 },
    { 0, H_7,  G_7,  I_7 },
    { 0, H_8,  G_8,  I_8 },
    { 0, H_9,  G_9,  I_9 },
    { 0, H_10, G_10, I_10 },
    { 0, H_11, G_11, I_11 },
    { 0, H_12, G_12, I_12 },
    { 0, H_14, G_14, I_14 },

    { 0, K_1,  J_1,  L_1 },
    { 0, K_2,  J_2,  L_2 },
    { 0, K_3,  J_3,  L_3 },
    { 0, K_4,  J_4,  L_4 },
    { 0, K_5,  J_5,  L_5 },
    { 0, K_6,  J_6,  L_6 },
    { 0, K_7,  J_7,  L_7 },
    { 0, K_8,  J_8,  L_8 },
    { 0, K_9,  J_9,  L_9 },
    { 0, K_10, J_10, L_10 },
    { 0, K_12, J_12, L_12 },
    { 0, K_13, J_13, L_13 },
    { 0, K_14, J_14, L_14 },

    { 0, H_16, G_16, I_16 },
    { 0, H_15, G_15, I_15 },
    { 0, H_13, G_13, I_13 },
    { 0, E_15, D_15, F_15 },
    { 0, K_15, J_15, L_15 },
    { 0, K_11, J_11, L_11 },
    { 0, K_16, J_16, L_16 },
    { 0, B_16, A_16, C_16 },
    { 0, E_16, D_16, F_16 }
};

led_config_t g_led_config = {
    {
        { 0,      1,      2,      3,      4,      5,      6,      7,      8,      9,      10,     11,     12,     13 },
        { 14,     15,     16,     17,     18,     19,     20,     21,     22,     23,     24,     25,     26,     27 },
        { 28,     29,     30,     31,     32,     33,     34,     35,     36,     37,     38,     39, NO_LED,     40 },
        { 41,     42,     43,     44,     45,     46,     47,     48,     49,     50, NO_LED,     51,     52,     53 },
        { 54,     55,     56,     NO_LED, NO_LED, 57, NO_LED,   NO_LED,   NO_LED, 58,     59,     60,     61,     62 }
    }, {
    // Esc, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, -, =, Backspace
    {   0,   0 }, {  15,   0 }, {  30,   0 }, {  45,   0 }, {  60,   0 }, {  75,   0 }, {  90,   0 }, { 105,   0 }, { 120,   0 }, { 135,   0 }, { 150,   0 }, { 165,   0 }, { 180,   0 }, { 202,   0 },
    // Tab, Q, W, E, R, T, Y, U, I, O, P, [, ],  ,
    {   7,  16 }, {  22,  16 }, {  37,  16 }, {  52,  16 }, {  67,  16 }, {  82,  16 }, {  97,  16 }, { 112,  16 }, { 127,  16 }, { 142,  16 }, { 157,  16 }, { 172,  16 }, { 187,  16 }, { 206,  16 },
    // Capslock, A, S, D, F, G, H, A, K, L, ;, ', Enter
    {  11,  32 }, {  26,  32 }, {  41,  32 }, {  56,  32 }, {  71,  32 }, {  86,  32 }, { 101,  32 }, { 116,  32 }, { 131,  32 }, { 146,  32 }, { 161,  32 }, { 176,  32 }, { 198,  32 },
    // LShift, Z, X, C, V, B, N, M, ,, ., /, Shift, Up,
    {  18,  48 }, {  30,  48 }, {  45,  48 }, {  60,  48 }, {  75,  48 }, {  90,  48 }, { 105,  48 }, { 120,  48 }, { 135,  48 }, { 150,  48 }, { 165,  48 }, { 191,  48 }, { 210,  48 },
    // Ctrl, GUI, Alt, Space, RAlt, FN, Left, Down, Right
    {   3,  64 }, {  22,  64 }, {  33,  64 }, { 101,  64 }, { 135,  64 }, { 153,  64 }, { 195,  64 }, { 210,  64 }, { 225,  64 }
#    if WS2812_LED_TOTAL > 0
        ,{ 28, 40}, { 62, 40}, { 96, 40}, {130, 40}, {164, 40}, {198, 40}
#    endif
}, {
    // Esc, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, -, =, Backspace
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,
    // Tab, Q, W, E, R, T, Y, U, I, O, P, [, ],
    1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    // Capslock, A, S, D, F, G, H, A, K, L, ;, ', Enter
    9, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,
    // LShift, Z, X, C, V, B, N, M, ,, ., /, Shift, Up, ?
    1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 1, 4,
    // Ctrl, GUI, Alt, Space, RAlt, FN, Left, Down, Right
    1, 1, 1, 4, 1, 1, 1, 1, 1
#    if WS2812_LED_TOTAL > 0
        ,2, 2, 2, 2, 2, 2
#    endif
    }
};

__attribute__ ((weak))
void rgb_matrix_indicators_user(void) {
    if (host_keyboard_led_state().caps_lock) {
        rgb_matrix_set_color(28, 0xFF, 0xFF, 0xFF);
    }
}


// clang-format on

// ==========================================================================
// Custom RGB Matrix driver that combines IS31FL3733 and WS2812
// ==========================================================================

#    if WS2812_LED_TOTAL > 0
LED_TYPE rgb_matrix_ws2812_array[WS2812_LED_TOTAL];
#    endif

static void rgb_matrix_driver_init(void) {
    i2c_init();
    IS31FL3733_init(DRIVER_ADDR_1, 0);
    for (uint8_t index = 0; index < ISSI_LED_TOTAL; index++) {
        bool enabled = true;
        IS31FL3733_set_led_control_register(index, enabled, enabled, enabled);
    }
    IS31FL3733_update_led_control_registers(DRIVER_ADDR_1, 0);
}

static void rgb_matrix_driver_flush(void) {
    IS31FL3733_update_pwm_buffers(DRIVER_ADDR_1, 0);
#    if WS2812_LED_TOTAL > 0
    ws2812_setleds(rgb_matrix_ws2812_array, WS2812_LED_TOTAL);
#    endif
}

static void rgb_matrix_driver_set_color(int index, uint8_t red, uint8_t green, uint8_t blue) {
    if (index < ISSI_LED_TOTAL) {
        IS31FL3733_set_color(index, red, green, blue);
    } else {
#    if WS2812_LED_TOTAL > 0
        rgb_matrix_ws2812_array[index - ISSI_LED_TOTAL].r = red;
        rgb_matrix_ws2812_array[index - ISSI_LED_TOTAL].g = green;
        rgb_matrix_ws2812_array[index - ISSI_LED_TOTAL].b = blue;
#    endif
    }
}

static void rgb_matrix_driver_set_color_all(uint8_t red, uint8_t green, uint8_t blue) {
    IS31FL3733_set_color_all(red, green, blue);
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
