/* Copyright (C) 2022 jonylee@hfd
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

#include "mk47.h"

#ifdef RGB_MATRIX_ENABLE
const is31_led PROGMEM g_is31_leds[DRIVER_LED_TOTAL] = {
/* Refer to IS31 manual for these locations
 *   driver
 *   |  R location
 *   |  |       G location
 *   |  |       |       B location
 *   |  |       |       | */
    {0, D_1,   E_1,   F_1},
    {0, D_2,   E_2,   F_2},
    {0, D_3,   E_3,   F_3},
    {0, D_4,   E_4,   F_4},
    {0, D_5,   E_5,   F_5},
    {0, D_6,   E_6,   F_6},
    {0, D_7,   E_7,   F_7},
    {0, D_8,   E_8,   F_8},
    {0, D_9,   E_9,   F_9},
    {0, D_10,  E_10,  F_10},
    {0, D_11,  E_11,  F_11},
    {0, D_12,  E_12,  F_12},

    {0, G_1,   H_1,   I_1},
    {0, G_2,   H_2,   I_2},
    {0, G_3,   H_3,   I_3},
    {0, G_4,   H_4,   I_4},
    {0, G_5,   H_5,   I_5},
    {0, G_6,   H_6,   I_6},
    {0, G_7,   H_7,   I_7},
    {0, G_8,   H_8,   I_8},
    {0, G_9,   H_9,   I_9},
    {0, G_10,  H_10,  I_10},
    {0, G_11,  H_11,  I_11},
    {0, G_12,  H_12,  I_12},

    {0, J_1,   K_1,   L_1},
    {0, J_2,   K_2,   L_2},
    {0, J_3,   K_3,   L_3},
    {0, J_4,   K_4,   L_4},
    {0, J_5,   K_5,   L_5},
    {0, J_6,   K_6,   L_6},
    {0, J_7,   K_7,   L_7},
    {0, J_8,   K_8,   L_8},
    {0, J_9,   K_9,   L_9},
    {0, J_10,  K_10,  L_10},
    {0, J_11,  K_11,  L_11},
    {0, J_12,  K_12,  L_12},

    {0, J_13,  K_13,  L_13},
    {0, J_14,  K_14,  L_14},
    {0, J_15,  K_15,  L_15},
    {0, J_16,  K_16,  L_16},
    {0, D_13,  E_13,  F_13},
    {0, D_14,  E_14,  F_14},
    {0, D_15,  E_15,  F_15},
    {0, G_13,  H_13,  I_13},
    {0, G_14,  H_14,  I_14},
    {0, G_15,  H_15,  I_15},
    {0, G_16,  H_16,  I_16},
};

led_config_t g_led_config = {
    {
        {  0,       1,      2,      3,      4,      5,      6,      7,      8,      9,      10,     11},
        {  12,     13,     14,     15,      16,     17,     18,     19,     20,     21,     22,     23},
        {  24,     25,     26,     27,      28,     29,     30,     31,     32,     33,     34,     35},
        {  36,     37,     38,     39,      40,     41,     NO_LED, 42,     43,     44,     45,     46}
    },
    {
    {  0,  0}, //  0
    { 20,  0}, //  1
    { 40,  0}, //  2
    { 61,  0}, //  3
    { 81,  0}, //  4
    { 101, 0}, //  5
    { 122, 0}, //  6
    {142,  0}, //  7
    {162,  0}, //  8
    {183,  0}, //  9
    {203,  0}, // 10
    {224,  0}, // 11

    {  0,  21}, //  12
    { 20,  21}, //  13
    { 40,  21}, //  14
    { 61,  21}, //  15
    { 81,  21}, //  16
    { 101, 21}, //  17
    { 122, 21}, //  18
    {142,  21}, //  19
    {162,  21}, //  20
    {183,  21}, //  21
    {203,  21}, // 22
    {224,  21}, // 23

    {  0,  42}, //  24
    { 20,  42}, //  25
    { 40,  42}, //  26
    { 61,  42}, //  27
    { 81,  42}, //  28
    { 101, 42}, //  29
    { 122, 42}, //  30
    {142,  42}, //  31
    {162,  42}, //  32
    {183,  42}, //  33
    {203,  42}, // 34
    {224,  42}, // 35

    {  0,  64}, //  36
    { 20,  64}, //  37
    { 40,  64}, //  38
    { 61,  64}, //  39
    { 81,  64}, //  40
    { 111, 64}, //  41
    {142,  64}, //  42
    {162,  64}, //  43
    {183,  64}, //  44
    {203,  64}, // 45
    {224,  64}  // 46
    },
    {
        4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,   4,  4,      4,  4,  4,
        4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,   4,  4,  4,  4,  4,  4,
        4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,   4,  4,  4
    }
};

#endif

#ifdef VIA_ENABLE
enum custom_keycodes {
    KC_RESET = USER00,   
};
#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
#ifdef VIA_ENABLE
        case KC_RESET: {
        if (record->event.pressed) {

        #include "via.h"
        via_eeprom_set_valid(false);
        eeconfig_init_via();
        }
            return false;
        }
#endif
        default:
            return true;  // Process all other keycodes normally
    }
}

#ifdef RGB_MATRIX_ENABLE
bool rgb_matrix_indicators_advanced_kb(uint8_t led_min, uint8_t led_max) {
    if (!rgb_matrix_indicators_advanced_user(led_min, led_max)) {
        return false;
    }
    // caps lock cyan
    if (host_keyboard_led_state().caps_lock) {
        RGB_MATRIX_INDICATOR_SET_COLOR(12, 255, 255, 255);
    }
    return true;
}
#endif
