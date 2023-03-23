/* Copyright 2021 @kuriatsu
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

#include "tsubasa.h"

#ifdef ENCODER_ENABLE
bool encoder_update_kb(uint8_t index, bool clockwise) {
    if (!encoder_update_user(index, clockwise)) { return false; }
    if (index == 0) {
        if (clockwise) {
            tap_code_delay(KC_VOLU, 10);
        } else {
            tap_code_delay(KC_VOLD, 10);
        }
    }
    return true;
}
#endif

#ifdef OLED_ENABLE
static void render_scrl(void) {
    static const char PROGMEM raw_scrl[] = {
        128,192,192,224, 96, 48, 48, 48, 48, 48, 48, 48,240,240,240,240,240,112,112, 56, 56, 56, 56, 24, 28, 28, 28,124,248,248,240, 64,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,192,192,224,112, 56, 56, 56, 56,  8,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        7, 15, 28, 24, 24, 24, 12, 12,  0,  0,192,254,255,255,255, 15, 32, 32, 48, 48, 16, 24, 24,  8, 12,140,156,254,255, 51,129,192,192,224,224,224,224,224,192,192,192,224,224,224,  0,  0,  0,  0,192,192,224, 96,  0,  0,  0,240,254,255,255,135,192,224,224,224,224,224,128,  0,  0,128,128,192,224, 96, 96,224,224,224,224,224, 96,  0,  0,  0,128,192,192,224,224,224,224,224, 64,  0,128,128,192,224, 96,224,224,224,224,224,224, 96,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,128,192,252,255,255,127, 15,  1, 16, 24,  8, 12, 12, 12,132,134,198,238,127, 59,131,  0, 30, 63, 63,124,248,240,240,  3,  1,193,253,255,127,  7,  0,  0,128,240,254,255, 63,  7,  0,128,224,254,255,127,  7,  1,  0,  0,192,252,255,127, 63,251,252,255,127,  7,  1,  0,128,192,252,255,255, 31,  1,128,192,192, 30, 63, 63,124,248,240,240,193,224,252,255,255,  7,  1,  0,128,192,252,255,255, 31,  1,128,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        96,112,112, 48, 56, 28, 14, 15,  3,  3,  5,  4,  4,  6,  6,  2,  2,  2,  3,  3,  1,  1,  1,  1,  7,  7, 15, 31, 31, 12, 12, 12,  6,  7,  3,  1,  0,  0, 31, 31, 15, 14,  6,  7,  3, 15, 31, 15, 15,  7,  7,  3, 63, 31, 31, 31, 30, 14, 14,  6,  7,  3,  3,  1,  0,  0, 15, 31, 31, 15,  6,  6,  3, 11, 31, 15, 15,  7,  7,  7, 15, 31, 31, 12, 12, 12,  6,  7,  3,  1,  0, 15, 31, 31, 15,  6,  6,  3, 11, 31, 15, 15,  7,  7,  3,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    };
    oled_write_raw_P(raw_scrl, sizeof(raw_scrl));
}
bool oled_task_kb(void) {
    if (!oled_task_user()) { return false; }
    render_scrl();
    oled_set_cursor(14, 0);
    oled_write_P(PSTR("WPM:"), false);
    oled_write(get_u8_str(get_current_wpm(), ' '), false);
    return false;
}
#endif
