/*
Copyright 2020 <contact@vwolf.be>
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.
*/
#include "fave84h.h"

#ifdef RGB_MATRIX_ENABLE
    led_config_t g_led_config = {
    {
        // Key Matrix to LED Index
        { 47, NO_LED, 48,     49,     50, 51,     52,     53,     54,     55, 56,     57,     58,     59,     60,     61,     62 },
        { 46,     45, 44,     43,     42, 41,     40,     39,     38,     37, 36,     35,     34,     33,     32,     31,     30 },
        { 13,     14, 15,     16,     17, 18,     19,     20,     21,     22, 23,     24,     25,     26,     27,     28,     29 },
        { 12,     11, 10,      9,      8,  7,      6,      5,      4,      3,  2,      1, NO_LED,      0, NO_LED, NO_LED, NO_LED },
        { 73,     74, 75,     76,     77, 78,     79,     80,     81,     82, 83, NO_LED,     84, NO_LED, NO_LED,     85, NO_LED },
        { 72,     71, 70, NO_LED, NO_LED, 69, NO_LED, NO_LED, NO_LED, NO_LED, 68, NO_LED,     67,     66,     65,     64,     63 },
    }, {
        // LED Index to Physical Position
        {0, 0}, {28, 0}, {42, 0}, {57, 0}, {71, 0}, {92, 0}, {106, 0}, {120, 0}, {134, 0}, {156, 0}, 
        {170, 0}, {184, 0}, {198, 0}, {216, 0}, {230, 0}, {244, 0}, {0, 15}, {14, 15}, {28, 15}, {42, 15}, 
        {57, 15}, {71, 15}, {85, 15}, {99, 15}, {113, 15}, {127, 15}, {141, 15}, {156, 15}, {170, 15}, {191, 17}, 
        {216, 15}, {230, 15}, {244, 15}, {4, 27}, {21, 27}, {35, 27}, {50, 27}, {64, 27}, {78, 27}, {92, 27}, 
        {106, 27}, {120, 27}, {134, 27}, {149, 27}, {163, 27}, {177, 27}, {194, 27}, {216, 27}, {230, 27}, {244, 27}, 
        {10, 40}, {25, 40}, {39, 40}, {53, 40}, {67, 40}, {81, 40}, {95, 40}, {110, 40}, {124, 40}, {138, 40}, 
        {152, 40}, {166, 40}, {189, 40}, {9, 52}, {32, 52}, {46, 52}, {60, 52}, {74, 52}, {88, 52}, {103, 52}, 
        {117, 52}, {131, 52}, {145, 52}, {159, 52}, {186, 52}, {230, 52}, {4, 64}, {21, 64}, {39, 64}, {99, 64}, 
        {159, 64}, {177, 64}, {194, 64}, {216, 64}, {230, 64}, {244, 64}
    }, {
        // LED Index to Flag
        1,    4, 4, 4, 4, 1, 1, 1, 1, 4, 4, 4, 4,    1, 1, 1, 
        1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,    1, 1, 1, 
        1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,    1, 1, 1, 
        8, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,    1,    
        1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,    1,          1,
        1, 1, 1,       4,             1,    1, 1,    1, 1, 1,

        2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
        2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2
    }
};
#endif

#if defined(VIA_ENABLE) && defined(VIA_CUSTOM_LIGHTING_ENABLE)

// VIA supports only 4 discrete values for effect speed; map these to some
// useful speed values for RGB Matrix.
enum speed_values {
    RGBLIGHT_SPEED_0 = UINT8_MAX / 16, // not 0 to avoid really slow effects
    RGBLIGHT_SPEED_1 = UINT8_MAX / 4,
    RGBLIGHT_SPEED_2 = UINT8_MAX / 2,     // matches the default value
    RGBLIGHT_SPEED_3 = UINT8_MAX / 4 * 3, // UINT8_MAX is really fast
};

static uint8_t speed_from_rgblight(uint8_t rgblight_speed) {
    switch (rgblight_speed) {
        case 0:
            return RGBLIGHT_SPEED_0;
        case 1:
            return RGBLIGHT_SPEED_1;
        case 2:
        default:
            return RGBLIGHT_SPEED_2;
        case 3:
            return RGBLIGHT_SPEED_3;
    }
}

static uint8_t speed_to_rgblight(uint8_t rgb_matrix_speed) {
    if (rgb_matrix_speed < ((RGBLIGHT_SPEED_0 + RGBLIGHT_SPEED_1) / 2)) {
        return 0;
    } else if (rgb_matrix_speed < ((RGBLIGHT_SPEED_1 + RGBLIGHT_SPEED_2) / 2)) {
        return 1;
    } else if (rgb_matrix_speed < ((RGBLIGHT_SPEED_2 + RGBLIGHT_SPEED_3) / 2)) {
        return 2;
    } else {
        return 3;
    }
}

void raw_hid_receive_kb(uint8_t *data, uint8_t length) {
    switch (data[0]) {
        case id_lighting_get_value:
            if (data[1] == id_qmk_rgblight_effect_speed) {
                data[2] = speed_to_rgblight(rgb_matrix_get_speed());
            }
            break;
        case id_lighting_set_value:
            if (data[1] == id_qmk_rgblight_effect_speed) {
                rgb_matrix_set_speed_noeeprom(speed_from_rgblight(data[2]));
            }
            break;
    }
}

#endif // defined(VIA_ENABLE) && defined(VIA_CUSTOM_LIGHTING_ENABLE)
