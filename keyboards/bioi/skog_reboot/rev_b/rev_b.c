/* Copyright 2022 Basic I/O Instruments (Scott Wei)
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

#include "rev_b.h"
#include "quantum.h"

const is31_led g_is31_leds[RGB_MATRIX_LED_COUNT] = {
    // clang-format off
/* Refer to IS31 manual for these locations
 *   driver
 *   |  R location
 *   |  |       G location
 *   |  |       |       B location
 *   |  |       |       | */

//ROW I (A ROW1 1-8, B ROW1 1-9)
//A Row1 1-8
    {0, L_1,    K_1,    J_1},
    {0, L_3,    K_3,    J_3},
    {0, L_4,    K_4,    J_4},
    {0, L_5,    K_5,    J_5},
    {0, L_6,    K_6,    J_6},
    {0, L_7,    K_7,    J_7},
    {0, L_8,    K_8,    J_8},
//B Row1 1-9
    {1, L_1,    K_1,    J_1},
    {1, L_2,    K_2,    J_2},
    {1, L_3,    K_3,    J_3},
    {1, L_4,    K_4,    J_4},
    {1, L_5,    K_5,    J_5},
    {1, L_6,    K_6,    J_6},
    {1, L_7,    K_7,    J_7},
    {1, L_8,    K_8,    J_8},
    {1, L_9,    K_9,    J_9},
//END OF ROW I

//ROW II (A ROW1 9-12, A ROW2, 1-4, B ROW1 10-12, B ROW2 1-6)
//A Row1 9-12
    {0, L_9,    K_9,    J_9},
    {0, L_10,   K_10,   J_10},
    {0, L_11,   K_11,   J_11},
    {0, L_12,   K_12,   J_12},
//A Row 2 1-4
    {0, I_1,    H_1,    G_1},
    {0, I_2,    H_2,    G_2},
    {0, I_3,    H_3,    G_3},
    {0, I_4,    H_4,    G_4},
//B Row1 10-12
    {1, L_10,   K_10,   J_10},
    {1, L_11,   K_11,   J_11},
    {1, L_12,   K_12,   J_12},
//B Row2 1-6
    {1, I_1,    H_1,    G_1},
    {1, I_2,    H_2,    G_2},
    {1, I_3,    H_3,    G_3},
    {1, I_4,    H_4,    G_4},
    {1, I_5,    H_5,    G_5},
    {1, I_6,    H_6,    G_6},
//END OF ROW II

//ROW III (A ROW2 5-12, B ROW2 7-12, B ROW3 1-3)
//A Row 2 5-12
    {0, I_5,    H_5,    G_5},
    {0, I_6,    H_6,    G_6},
    {0, I_7,    H_7,    G_7},
    {0, I_8,    H_8,    G_8},
    {0, I_9,    H_9,    G_9},
    {0, I_10,   H_10,   G_10},
    {0, I_11,   H_11,   G_11},
    {0, I_12,   H_12,   G_12},
//B Row2 7-12
    {1, I_7,    H_7,    G_7},
    {1, I_8,    H_8,    G_8},
    {1, I_9,    H_9,    G_9},
    {1, I_10,   H_10,   G_10},
    {1, I_11,   H_11,   G_11},
    {1, I_12,   H_12,   G_12},
//B Row3 1-3
    {1, F_1,    E_1,    D_1},
    {1, F_2,    E_2,    D_2},
    {1, F_3,    E_3,    D_3},
//END OF ROW III

//ROW IV (A ROW3 1-8, B ROW3 4-10)
//A Row3 1-8
    {0, F_1,    E_1,    D_1},
    {0, F_2,    E_2,    D_2},
    {0, F_3,    E_3,    D_3},
    {0, F_4,    E_4,    D_4},
    {0, F_5,    E_5,    D_5},
    {0, F_6,    E_6,    D_6},
    {0, F_7,    E_7,    D_7},
    {0, F_8,    E_8,    D_8},
//B Row3 4-10
    {1, F_4,    E_4,    D_4},
    {1, F_5,    E_5,    D_5},
    {1, F_6,    E_6,    D_6},
    {1, F_7,    E_7,    D_7},
    {1, F_8,    E_8,    D_8},
    {1, F_9,    E_9,    D_9},
    {1, F_10,   E_10,   D_10},
//END OF ROW IV

//ROW V (A Row3 9-12, A Row4 1-4, B Row3 11-12, B Row4 1-5)
//A Row3 9-12
    {0, F_9,    E_9,    D_9},
    {0, F_10,   E_10,   D_10},
    {0, F_11,   E_11,   D_11},
    {0, F_12,   E_12,   D_12},
//A Row 4 1-4
    {0, C_1,    B_1,    A_1},
    {0, C_2,    B_2,    A_2},
    {0, C_3,    B_3,    A_3},
    {0, C_4,    B_4,    A_4},
//B Row3 11-12
    {1, F_11,   E_11,   D_11},
    {1, F_12,   E_12,   D_12},
//B Row4 1-5
    {1, C_1,    B_1,    A_1},
    {1, C_2,    B_2,    A_2},
    {1, C_3,    B_3,    A_3},
    {1, C_4,    B_4,    A_4},
    {1, C_5,    B_5,    A_5},
//END OF ROW V

//ROW VI
    {0, C_5,    B_5,    A_5},
    {0, C_6,    B_6,    A_6},
    {0, C_7,    B_7,    A_7},
    {0, C_11,   B_11,   A_11},
    {0, C_12,   B_12,   A_12},
//B Row4 6-12
    {1, C_6,    B_6,    A_6},
    {1, C_7,    B_7,    A_7},
    {1, C_8,    B_8,    A_8},
    {1, C_9,    B_9,    A_9},
    {1, C_10,   B_10,   A_10},
    {1, C_11,   B_11,   A_11},
    {1, C_12,   B_12,   A_12}
//END OF ROW VI
    // clang-format on
};

led_config_t g_led_config = {{
                                 // clang-format off
    { 0, NO_LED, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 },
    { 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32 },
    { 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49 },
    { 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, NO_LED, NO_LED },
    { 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 65, NO_LED, 79, NO_LED },
    { 80, 81, 82, NO_LED, NO_LED, NO_LED, 84, NO_LED, NO_LED, NO_LED, 85, 86, 87, 88, 89, 91, 90 }
                                 // clang-format on
                             },
                             {
                                 // clang-format off
    // LED Index to Physical Position
    {0, 0},            {28, 0}, {42, 0}, {56, 0}, {70, 0}, {84, 0}, {98, 0}, {112, 0}, {126, 0}, {140, 0}, {154, 0}, {168, 0}, {182, 0}, {196, 0}, {210, 0}, {224, 0},
    {0, 13}, {14, 13}, {28, 13}, {42, 13}, {56, 13}, {70, 13}, {84, 13}, {98, 13}, {112, 13}, {126, 13}, {140, 13}, {154, 13}, {168, 13}, {182, 13}, {196, 13}, {210, 13}, {224, 13},
    {0, 26}, {14, 26}, {28, 26}, {42, 26}, {56, 26}, {70, 26}, {84, 26}, {98, 26}, {112, 26}, {126, 26}, {140, 26}, {154, 26}, {168, 26}, {182, 26}, {196, 26}, {210, 26}, {224, 26},
    {0, 38}, {14, 38}, {28, 38}, {42, 38}, {56, 38}, {70, 38}, {84, 38}, {98, 38}, {112, 38}, {126, 38}, {140, 38}, {154, 38}, {168, 38}, {182, 38}, {196, 38},
    {0, 51}, {7, 51}, {14, 51}, {42, 51}, {56, 51}, {70, 51}, {84, 51}, {98, 51}, {112, 51}, {126, 51}, {140, 51}, {154, 51}, {168, 51}, {182, 51},             {210, 51},
    {0, 64}, {14, 64}, {28, 64},                               {84, 64}, {98, 64},                        {140, 64}, {154, 64}, {168, 64}, {182, 64}, {196, 64}, {210, 64}, {224, 64}
                                 // clang-format on
                             },
                             {
                                 // clang-format off
    // LED Index to Flag
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 1, 1, 1,
    1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 1, 1, 1,
    1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 1,
    1, 1, 1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
                                 // clang-format on
                             }};

bool rgb_matrix_indicators_kb(void) {
    if (host_keyboard_led_state().caps_lock) {
        rgb_matrix_set_color(50, 255, 255, 255);
    }
    return rgb_matrix_indicators_user();
}

void keyboard_pre_init_kb(void) {
    setPinOutput(RGB_BL_CONTROL_PIN); // IS31FL3737 SDB pin
    setPinOutput(RGB_UG_CONTROL_PIN);

    writePinHigh(RGB_BL_CONTROL_PIN);
    writePinLow(RGB_UG_CONTROL_PIN);

    keyboard_pre_init_user();
}

bool encoder_update_kb(uint8_t index, bool clockwise) {
    if (clockwise) {
        action_exec((keyevent_t){.key = (keypos_t){.row = 4, .col = 14}, .pressed = 1, .time = 5});
        action_exec((keyevent_t){.key = (keypos_t){.row = 4, .col = 14}, .pressed = 0, .time = 1});
    } else {
        action_exec((keyevent_t){.key = (keypos_t){.row = 4, .col = 16}, .pressed = 1, .time = 5});
        action_exec((keyevent_t){.key = (keypos_t){.row = 4, .col = 16}, .pressed = 0, .time = 1});
    }
    return encoder_update_user(index, clockwise);
}