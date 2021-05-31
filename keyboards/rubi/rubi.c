/* Copyright 2021 gregorio
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
#include "rubi.h"

uint8_t oled_mode = OLED_MODE_DEFAULT;

char calc_result_display[CALC_DIGITS+1] = "";
char calc_operator_display = ' ';
char calc_status_display[CALC_DIGITS+1] = "";
uint8_t calc_display_lines = 2;

const char keycode_to_ascii_lut[58] = {0, 0, 0, 0, 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', 0, 0, 0, '\t', ' ', '-', '=', '[', ']', '\\', 0, ';', '\'', '`', ',', '.', '/'};

uint8_t encoder_mode = ENC_MODE_VOLUME;

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    if (keycode < 58 && keycode != KC_TAB) {
        if (record->event.pressed) {
            calcInput(keycode_to_ascii_lut[(uint8_t)keycode]);
        }
        return false;
    }
    switch (keycode) {
        case ENC_PRESS:
            if (record->event.pressed) {
                uint16_t mapped_code = handle_encoder_press();
                if (mapped_code != 0) {
                    tap_code16(mapped_code);
                }
            }
            return false;
        case CL_PLUS:
            if (record->event.pressed) {
                calcInput('+');
            }
            return false;
        case CL_STAR:
            if (record->event.pressed) {
                calcInput('*');
            }
            return false;
        case CL_TYPE:
            if (record->event.pressed) {
                send_string(calc_result_display);
            }
            return false;
        default:
            break;
    }

    return process_record_user_oled(keycode, record);
}


bool led_update_kb(led_t led_state) {
    bool res = led_update_user(led_state);
    if (res) {
        writePin(C6, led_state.num_lock);
    }
    return true;
}

__attribute__ ((weak)) void encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        if (get_highest_layer(layer_state) == 0) {
            uint16_t mapped_code = 0;
            if (clockwise) {
                mapped_code = handle_encoder_cw();
            } else {
                mapped_code = handle_encoder_ccw();
            }
            if (mapped_code != 0) {
                tap_code16(mapped_code);
            }
        } else {
            if (clockwise) {
                if (oled_mode == OLED_MODE_CALC) {
                    handle_encoder_cw();
                } else if (oled_mode == OLED_MODE_DEFAULT) {
                    change_encoder_mode(false);
                }
            } else {
                if (oled_mode == OLED_MODE_CALC) {
                    handle_encoder_ccw();
                } else if (oled_mode == OLED_MODE_DEFAULT) {
                    change_encoder_mode(true);
                }
            }
        }
    }
}

void encoder_update_kb(uint8_t index, bool clockwise) {
    encoder_update_user(index, clockwise);
}
