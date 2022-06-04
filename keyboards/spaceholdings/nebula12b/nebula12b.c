/* Copyright 2022 Yiancar
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

#include "nebula12b.h"
#include <lib/lib8tion/lib8tion.h>

#ifdef RGB_MATRIX_ENABLE
// clang-format off
led_config_t g_led_config = { {
    { 13, 15,  1 }, 
    {  4,  3,  2 }, 
    {  5,  6,  7 }, 
    { 11, 10,  9 }, 
}, {
    {224,  0 }, {224,  9 }, {224, 27 }, {112, 27 }, {  0,27 }, 
    {  0, 46 }, {112, 46 }, {224, 46 }, {224, 55 }, {224,64 }, 
    {112, 64 }, {  0, 64 }, {  0, 55 }, {  0,  9 }, {  0, 0 }, {112, 9 }
}, {
    2,
    4, 4, 4, 4, 4, 4, 4,
    2,
    4, 4, 4,
    2,
    4,
    2,
    4
} };
// clang-format on
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
