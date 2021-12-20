/* Copyright 2021 Jay Greco
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

#include QMK_KEYBOARD_H

typedef struct PACKED {
    uint8_t r;
    uint8_t c;
} encodermap_t;

// Map encoders to their respective virtual matrix entry
// Allows for encoder control using VIA
const encodermap_t encoder_map[4][2] = {
    {{1, 0}, {1, 1}},  // Encoder 1 matrix location
    {{2, 0}, {2, 1}},  // Encoder 2 matrix location
    {{3, 0}, {3, 1}},  // Encoder 3 matrix location
    {{4, 0}, {4, 1}},  // Encoder 4 matrix location
};

static void process_encoder_matrix(encodermap_t pos) {
    action_exec((keyevent_t){
        .key = (keypos_t){.row = pos.r, .col = pos.c}, .pressed = true, .time = (timer_read() | 1) /* time should not be 0 */
    });
#if TAP_CODE_DELAY > 0
    wait_ms(TAP_CODE_DELAY);
#endif
    action_exec((keyevent_t){
        .key = (keypos_t){.row = pos.r, .col = pos.c}, .pressed = false, .time = (timer_read() | 1) /* time should not be 0 */
    });
}

bool encoder_update_kb(uint8_t index, bool clockwise) {
    if (!encoder_update_user(index, clockwise)) return false;
    process_encoder_matrix(encoder_map[index][clockwise ? 0 : 1]);
    return false;
}

// Use Bit-C LED to show NUM LOCK status
bool led_update_kb(led_t led_state) {
    bool res = led_update_user(led_state);
    if (res) {
        set_bitc_LED(led_state.num_lock ? LED_DIM : LED_OFF);
    }
    return res;
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    process_record_remote_kb(keycode, record);
    return true;
}

void matrix_init_kb(void) {
    matrix_init_remote_kb();
    set_bitc_LED(LED_OFF);
}

void matrix_scan_kb(void) {
    matrix_scan_remote_kb();
}
