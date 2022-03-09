/* Copyright 2021 Yiancar
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

#include "nebula68b.h"
#include <lib/lib8tion/lib8tion.h>

#ifndef KEYBOARD_spaceholdings_nebula68b_hs
#ifdef RGB_MATRIX_ENABLE
// clang-format off
led_config_t g_led_config = { {
    {  0,      1,  2,      4,      5,      6,  7,      9,     10, 11, 13, 14, 15, 18, 19 },
    { 36,     35, 34,     33,     32,     31, 30,     29,     28, 27, 26, 25, 24, 16, 22 },
    { 38,     39, 40,     41,     42,     43, 44,     45,     46, 47, 48, 49, 23, 50, 20 },
    { 64, NO_LED, 63,     62,     61,     60, 59,     58,     57, 56, 55, 54, 53, 52, 21 },
    { 65,     66, 68, NO_LED, NO_LED, NO_LED, 70, NO_LED, NO_LED, 72, 73, 74, 76, 77, 78 }
}, {
    {  6, 10}, { 19, 10}, { 32, 10}, { 44, 13}, { 45, 10}, { 58, 10}, { 71, 10}, { 84, 10}, { 88, 13}, { 97, 10}, {110, 10}, {123, 10}, {132, 13}, {136, 10}, {149, 10}, {162, 10},
    {175, 10}, {179, 13}, {188, 10}, {205, 10}, {218, 10}, {218, 23}, {205, 23}, {185, 23}, {169, 23}, {156, 23}, {143, 23}, {130, 23}, {117, 23}, {104, 23}, { 91, 23}, { 78, 23},
    { 65, 23}, { 52, 23}, { 39, 23}, { 26, 23}, { 10, 23}, {  4, 26}, { 11, 35}, { 29, 35}, { 42, 35}, { 55, 35}, { 68, 35}, { 81, 35}, { 94, 35}, {107, 35}, {120, 35}, {133, 35},
    {146, 35}, {159, 35}, {180, 35}, {220, 32}, {205, 48}, {177, 48}, {153, 48}, {140, 48}, {127, 48}, {114, 48}, {101, 48}, { 88, 48}, { 75, 48}, { 62, 48}, { 49, 48}, { 36, 48},
    { 15, 48}, {  8, 61}, { 24, 61}, { 32, 52}, { 41, 61}, { 82, 56}, { 89, 61}, {132, 53}, {138, 61}, {154, 61}, {170, 61}, {179, 53}, {192, 61}, {205, 61}, {218, 61}
}, {
    1, 4, 4, 2, 4, 4, 4, 4, 2, 4, 4, 4, 2, 4, 4, 4, 4, 2, 1, 1, 1,
    1, 1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 2,
    1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 2,
    1, 1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,
    1, 1, 2, 1, 2, 4, 2, 1, 1, 1, 2, 1, 1, 1
} };
// clang-format on
#endif
#endif

#if defined(RGB_MATRIX_ENABLE) && defined(VIA_ENABLE)
void raw_hid_receive_kb(uint8_t *data, uint8_t length) {
    uint8_t *command_id = &(data[0]);
    uint8_t *command_data = &(data[1]);
    switch (*command_id) {
        case id_lighting_set_value: {
            uint8_t *value_id   = &(command_data[0]);
            uint8_t *value_data = &(command_data[1]);
            switch (*value_id) {
                case id_qmk_rgblight_brightness: {
                    rgb_matrix_sethsv_noeeprom(rgb_matrix_get_hue(), rgb_matrix_get_sat(), scale8(value_data[0], RGB_MATRIX_MAXIMUM_BRIGHTNESS));
                    break;
                }
                case id_qmk_rgblight_effect: {
                    rgb_matrix_mode_noeeprom(value_data[0]);
                    if (value_data[0] == 0) {
                        rgb_matrix_disable_noeeprom();
                    } else {
                        rgb_matrix_enable_noeeprom();
                    }
                    break;
                }
                case id_qmk_rgblight_effect_speed: {
                    rgb_matrix_set_speed_noeeprom(value_data[0] * 85);
                    break;
                }
                case id_qmk_rgblight_color: {
                    rgb_matrix_sethsv_noeeprom(value_data[0], value_data[1], rgb_matrix_get_val());
                    break;
                }
            }
            break;
        }
        case id_lighting_get_value: {
            uint8_t *value_id   = &(command_data[0]);
            uint8_t *value_data = &(command_data[1]);
            switch (*value_id) {
                case id_qmk_rgblight_brightness: {
                    value_data[0] = ((uint16_t)rgb_matrix_get_val() * 255) / RGB_MATRIX_MAXIMUM_BRIGHTNESS;
                    break;
                }
                case id_qmk_rgblight_effect: {
                    value_data[0] = rgb_matrix_get_mode();
                    break;
                }
                case id_qmk_rgblight_effect_speed: {
                    value_data[0] = rgb_matrix_get_speed() / 85;
                    break;
                }
                case id_qmk_rgblight_color: {
                    value_data[0] = rgb_matrix_get_hue();
                    value_data[1] = rgb_matrix_get_sat();
                    break;
                }
            }
            break;
        }
        case id_lighting_save: {
            eeconfig_update_rgb_matrix();
            break;
        }
        default: {
            *command_id         = id_unhandled;
            break;
        }
    }
}
#endif
