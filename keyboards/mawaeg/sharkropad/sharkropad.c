/* Copyright 2025 @mawaeg
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
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
#include <ctype.h>
#include <lib/lib8tion/lib8tion.h>
#include <rgb_matrix.h>

static uint8_t effect_name_len = 0;

const char *rgb_matrix_get_effect_name(void) {
    static char buf[32] = {0};

    snprintf(buf, sizeof(buf), "%s", rgb_matrix_get_mode_name(rgb_matrix_get_mode()));
    for (uint8_t i = 1; i < sizeof(buf); ++i) {
        if (buf[i] == 0) {
            effect_name_len = i;
            break;
        } else if (buf[i] == '_')
            buf[i] = ' ';
        else if (buf[i - 1] == ' ')
            buf[i] = toupper(buf[i]);
        else if (buf[i - 1] != ' ')
            buf[i] = tolower(buf[i]);
    }
    return buf;
}

bool oled_task_kb(void) {
    if (!oled_task_user()) {
        return false;
    }

    static uint8_t  last_effect = 0;
    static uint8_t  last_speed  = 0;
    static uint16_t key_timer   = 0;
    static uint8_t  start_index = 0;

    uint8_t speedPercentage  = scale8(rgb_matrix_get_speed(), 100);
    bool    is_timer_elapsed = timer_elapsed(key_timer) > 200;

    if (last_effect != rgb_matrix_get_mode() || last_speed != speedPercentage || is_timer_elapsed) {
        last_effect = rgb_matrix_get_mode();
        last_speed  = speedPercentage;

        oled_write_ln_P(PSTR("Mode: "), false);
        const char *name = rgb_matrix_get_effect_name();
        if (effect_name_len > 21) {
            if (!is_timer_elapsed && start_index != 0) {
                start_index -= 1;
            } else {
                key_timer = timer_read();
            }
            if (start_index > effect_name_len) {
                start_index = 0;
            }
            for (uint8_t char_index = 0; char_index < 21; char_index++) {
                if ((start_index + char_index) % effect_name_len == 0 && char_index != 0) {
                    oled_write_char(' ', false);
                } else {
                    oled_write_char(name[(start_index + char_index) % (effect_name_len + 1)], false);
                }
            }
            start_index += 1;
        } else {
            oled_write_ln(name, false);
            start_index = 0;
        }

        oled_set_cursor(0, 2);
        oled_write_ln_P(PSTR("RGB Speed: "), false);
        oled_write(get_u8_str(speedPercentage, ' '), false);
        oled_write("%", false);
    }

    return true;
}
