/* Copyright 2021 klackygears
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
#include "ein_60.h"

#ifdef RGB_MATRIX_ENABLE

  // Logical Layout
  // Columns
  //  0  1  2  3  4  5  6  7  8  9 10 11 12 13
  //                                            ROWS
  // 37  0  1  2  3  4  5  6  7  8  9 10 11 12   0
  // 36                                     13   1
  // 35                                     14   2
  // 34                                     15   3
  // 33                                     16   3
  // 32                                     17   4
  // 31 30 29 28 27 26 25 24 23 22 21 20 19 18   5

led_config_t g_led_config = { {
    {   36,      1,      2,      3,      4,      5,      5,      6,      7,      8,      9,     10,     13   },
    {   34,      1,      2,      3,      4,      5, NO_LED,      6,      7,      8,      9,     10,     15   },
    {   33,     30,     29,     28,     27,     26, NO_LED,     23,     22,     21,     20,     19,     16   },
    {   32,     30,     29,     28,     27,     26,     24,     23,     22,     21,     20,     19,     17   }
}, {
    {  30,  0 }, {  45,  0 }, {  60,  0 }, {  75,  0 }, {  90,  0 }, { 105,  0 }, { 119,  0 }, { 134,  0 }, { 149,  0 }, { 164,  0 }, { 179,  0 }, { 194,  0 }, { 209,  0 }, { 224, 11 },
    { 224, 21 }, { 224, 32 }, { 224, 43 }, { 224, 53 }, { 209, 64 }, { 194, 64 }, { 179, 64 }, { 164, 64 }, { 149, 64 }, { 134, 64 }, { 119, 64 }, { 105, 64 }, {  90, 64 },
    {  75, 64 }, {  60, 64 }, {  45, 64 }, {  30, 64 }, {  15, 64 }, {   0, 53 }, {   0, 43 }, {   0, 32 }, {   0, 21 }, {   0, 11 }, {  15,  0 },
}, {
     2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
     2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
     1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
     1, 2,
} };
#endif

#ifdef AUDIO_ENABLE
const uint8_t music_map[MATRIX_ROWS][MATRIX_COLS] = LAYOUT(
   30, 31, 32, 33, 34, 35, 35, 36, 37, 38, 39, 40, 41,
   18,  9, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29,
    6,  7,  8,  9, 10, 11, 12, 13, 14, 15, 16, 17,
    1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1
);
#endif

#ifdef OLED_ENABLE
__attribute__((weak)) void oled_task_user(void) {
    // Host Keyboard Layer Status
    oled_write_P(PSTR("Layer: "), false);
    switch (get_highest_layer(layer_state)) {
        case 0:
            oled_write_P(PSTR("Default\n"), false);
            break;
        case 1:
            oled_write_P(PSTR("Lower\n"), false);
            break;
        case 2:
            oled_write_P(PSTR("Raise\n"), false);
            break;
        case 3:
            oled_write_P(PSTR("Adjust\n"), false);
            break;
        case 4:
            oled_write_P(PSTR("FN\n"), false);
            break;
        default:
            // Or use the write_ln shortcut over adding '\n' to the end of your string
            oled_write_ln_P(PSTR("Undefined"), false);
    }


    // Host Keyboard LED Status
    led_t led_state = host_keyboard_led_state();
    oled_write_P(led_state.num_lock ? PSTR("NUM ") : PSTR("    "), false);
    oled_write_P(led_state.caps_lock ? PSTR("CAP ") : PSTR("    "), false);
    oled_write_P(led_state.scroll_lock ? PSTR("SCR ") : PSTR("    "), false);

    oled_set_cursor(1,2);
    oled_advance_page(true);
    static const char PROGMEM ein60_logo[] = {
            0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,255,255, 11,251,139,139,139,139,139,139,139,139,139,139,139, 11, 15,  0,240,240, 16,240,  0,240,240, 16,240,224,192,128,  0,  0,  0,  0,240, 16,240,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,254,255, 11,251,139,139,139,139,139,139,139,139,139,139,139,143,128,  0,  0,  0,  0,254,255, 11,251, 11, 11, 11, 11,139,203,235,123,187,219,235,251,255,  7,252,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,255,255,  4,253,197,197,197,197,197,197,197,197,197,197,199,192,192,  0,255,255,  0,255,  0,255,255,  0,254, 13, 27, 55,111,222,188,120,255,  0,255,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,255,255,  0,255,197,197,197,197,197,197,197,197,197,197,253,253,255,131,254,  0,  0,255,255,  0,255,184,220,238,247,219,205,198,195,193,192,255,255,255,128,255,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  3,  3,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  3,  0,  3,  3,  2,  3,  0,  3,  3,  2,  3,  0,  0,  0,  0,  0,  1,  3,  2,  2,  3,  0,  8, 28, 20, 20, 20, 20, 20, 28,  8,  0,  1,  3,  3,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  3,  0,  0,  0,  1,  3,  3,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        };
    oled_write_raw_P(ein60_logo, sizeof(ein60_logo));
}
#endif

#ifdef ENCODER_ENABLE
bool encoder_update_kb(uint8_t index, bool clockwise) {
    if (!encoder_update_user(index, clockwise)) { return false; }
    if (index == 0) { /* First encoder */
        if (clockwise) {
            tap_code_delay(KC_VOLU, 10);
        } else {
            tap_code_delay(KC_VOLD, 10);
        }
    } else if (index == 1) { /* Second encoder */
        if (clockwise) {
            tap_code(KC_DOWN);
        } else {
            tap_code(KC_UP);
        }
    }
    return true;
}
#endif
