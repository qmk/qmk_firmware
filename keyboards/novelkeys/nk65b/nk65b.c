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

#include "nk65b.h"
#include <lib/lib8tion/lib8tion.h>

void led_init_ports(void) {
    // Set our LED pins as open drain outputs
    palSetLineMode(LED_CAPS_LOCK_PIN, PAL_MODE_OUTPUT_OPENDRAIN);
    palSetLineMode(A15, PAL_MODE_OUTPUT_OPENDRAIN);
    palSetLineMode(B3, PAL_MODE_OUTPUT_OPENDRAIN);
}

layer_state_t layer_state_set_kb(layer_state_t state) {
    writePin(A15, !layer_state_cmp(state, 1));
    writePin(B3, !layer_state_cmp(state, 2));
    return layer_state_set_user(state);
}

#ifdef RGB_MATRIX_ENABLE
// clang-format off
led_config_t g_led_config = { {
    {  0,      1,  2,      3,      4,      5,  6,      7,     8,   9, 10, 11, 12,     13, 14 },
    { 29,     28, 27,     26,     25,     24, 23,     22,     21, 20, 19, 18, 17, NO_LED, 15 },
    { 30,     31, 32,     33,     34,     35, 36,     37,     38, 39, 40, 41, 42,     16, 43 },
    { 57, NO_LED, 56,     55,     54,     53, 52,     51,     50, 49, 48, 47, 46,     45, 44 },
    { 58,     59, 60, NO_LED, NO_LED, NO_LED, 61, NO_LED, NO_LED, 61, 62, 63, 64,     65, 66 }
}, {
    {  0,0  }, { 15,0  }, { 30,0  }, { 45,0  }, { 60,0  }, { 75,0  }, { 90,0  }, {105,0  }, {120,0  }, {135,0  }, {150,0  }, {165,0  }, {180,0  }, {203,0  }, 
    {225,0  }, {225,16 }, {206,16 }, {188,16 }, {173,16 }, {158,16 }, {143,16 }, {128,16 }, {113,16 }, { 98,16 }, { 83,16 }, { 68,16 }, { 53,16 }, { 38,16 }, 
    { 23,16 }, {  4,16 }, {  6,32 }, { 26,32 }, { 41,32 }, { 56,32 }, { 71,32 }, { 86,32 }, {101,32 }, {116,32 }, {131,32 }, {146,32 }, {161,32 }, {176,32 }, 
    {201,32 }, {225,32 }, {225,48 }, {210,48 }, {189,48 }, {169,48 }, {154,48 }, {139,48 }, {124,48 }, {109,48 }, { 94,48 }, { 79,48 }, { 64,48 }, { 49,48 }, 
    { 34,48 }, {  9,48 }, {  2,64 }, { 21,64 }, { 39,64 }, { 96,64 }, {150,64 }, {165,64 }, {180,64 }, {195,64 }, {210,64 }, {225,64 }
}, {
    1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 1,
    1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,
    1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 1,
    1, 1, 1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,
    1, 1, 1, 4, 1, 1, 1, 1, 1, 1
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
