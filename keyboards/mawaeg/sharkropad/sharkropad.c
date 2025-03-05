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
#include <rgb_matrix.h>

#if defined(RGB_MATRIX_EFFECT)
#    undef RGB_MATRIX_EFFECT
#endif // defined(RGB_MATRIX_EFFECT)

#define RGB_MATRIX_EFFECT(x) RGB_MATRIX_EFFECT_##x,
enum {
    RGB_MATRIX_EFFECT_NONE,
#include "rgb_matrix_effects.inc"
#ifdef RGB_MATRIX_CUSTOM_KB
#    include "rgb_matrix_kb.inc"
#endif // RGB_MATRIX_CUSTOM_KB
#ifdef RGB_MATRIX_CUSTOM_USER
#    include "rgb_matrix_user.inc"
#endif // RGB_MATRIX_CUSTOM_USER
#undef RGB_MATRIX_EFFECT
};

#define RGB_MATRIX_EFFECT(x)    \
    case RGB_MATRIX_EFFECT_##x: \
        return #x;
const char *rgb_matrix_name(uint8_t effect) {
    switch (effect) {
        case RGB_MATRIX_EFFECT_NONE:
            return "NONE";
#include "rgb_matrix_effects.inc"
#ifdef RGB_MATRIX_CUSTOM_KB
#    include "rgb_matrix_kb.inc"
#endif // RGB_MATRIX_CUSTOM_KB
#ifdef RGB_MATRIX_CUSTOM_USER
#    include "rgb_matrix_user.inc"
#endif // RGB_MATRIX_CUSTOM_USER
#undef RGB_MATRIX_EFFECT
        default:
            return "UNKNOWN";
    }
}

static uint8_t effect_name_len = 0;

const char *rgb_matrix_get_effect_name(void) {
    static char buf[32] = {0};

    snprintf(buf, sizeof(buf), "%s", rgb_matrix_name(rgb_matrix_get_mode()));
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

bool oled_task_user(void) {
    static uint8_t  last_effect = 0;
    static uint8_t  last_speed  = 0;
    static uint16_t key_timer   = 0;
    static uint8_t  start_index = 0;

    uint8_t speedPercentage = (uint8_t)(((float)rgb_matrix_get_speed() / 255.0) * 100.0);

    if (last_effect != rgb_matrix_get_mode() || last_speed != speedPercentage || timer_elapsed(key_timer) > 200) {
        last_effect = rgb_matrix_get_mode();
        last_speed  = speedPercentage;
        key_timer   = timer_read();

        oled_write_ln_P(PSTR("Mode: "), false);
        const char *name = rgb_matrix_get_effect_name();
        if (effect_name_len > 21) {
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
        char speedBuffer[4];
        sprintf(speedBuffer, "%d", speedPercentage);
        oled_write(speedBuffer, false);
        oled_write("%  ", false);
    }

    return false;
}
