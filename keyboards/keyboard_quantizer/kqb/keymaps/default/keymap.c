/* Copyright 2020 sekigon-gonnoc
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
#include "keycode.h"
#include QMK_KEYBOARD_H
#include "bmp.h"
#include "bmp_custom_keycode.h"
#include "keycode_str_converter.h"

#include "pointing_device.h"
#include "report_parser.h"

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
    CUSTOM_KEYCODE_START = BMP_SAFE_RANGE,
};

const key_string_map_t custom_keys_user = {.start_kc    = CUSTOM_KEYCODE_START,
                                           .end_kc      = CUSTOM_KEYCODE_START,
                                           .key_strings = "\0"};

const uint16_t keymaps[][MATRIX_ROWS][MATRIX_COLS] = {{{KC_NO}}};

uint32_t keymaps_len() { return 70; }

typedef enum {
    GESTURE_NONE = 0,
    GESTURE_DOWN_RIGHT,
    GESTURE_DOWN_LEFT,
    GESTURE_UP_LEFT,
    GESTURE_UP_RIGHT,
} gesture_id_t;

extern bool          matrix_has_changed;
extern matrix_row_t* matrix_mouse_dest;
extern bool          mouse_send_flag;

static uint8_t spd_rate_num       = 1;
static uint8_t spd_rate_den       = 1;
static int16_t gesture_move_x     = 0;
static int16_t gesture_move_y     = 0;
static bool    gesture_wait       = false;
static uint8_t kc_no_to_kc_offset = 0;
static uint8_t btn_release_flag   = 0;
static int16_t wheel_move_v       = 0;
static int16_t wheel_move_h       = 0;

static uint8_t get_gesture_threshold() {
    return BMPAPI->app.get_config()->reserved[5];
}

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    bool continue_process = process_record_user_bmp(keycode, record);
    if (continue_process == false) {
        return false;
    }

    switch (keycode) {
        case KC_BTN1 ... KC_BTN5:
            mouse_send_flag = true;
            return true;
            break;

        case KC_MS_WH_UP ... KC_MS_WH_DOWN: {
            if (wheel_move_v != 0) {
                report_mouse_t report = pointing_device_get_report();
                report.v = keycode == KC_MS_WH_UP ? abs(wheel_move_v)
                                                  : -abs(wheel_move_v);
                pointing_device_set_report(report);
                mouse_send_flag = true;
                return false;
            } else {
                return true;
            }
        } break;

        case KC_MS_WH_LEFT ... KC_MS_WH_RIGHT: {
            if (wheel_move_h != 0) {
                report_mouse_t report = pointing_device_get_report();
                report.h = keycode == KC_MS_WH_LEFT ? abs(wheel_move_h)
                                                    : -abs(wheel_move_h);
                pointing_device_set_report(report);
                mouse_send_flag = true;
                return false;
            } else {
                return true;
            }
        } break;

        default:
            break;
    }

    // Enable layer tap with KC_BTNx
    if (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX) {
        uint8_t kc = keycode & 0xFF;
        if (kc == KC_NO) {
            kc = kc_no_to_kc_offset;
            dprintf("KC:%d, tap:%d\n", kc, record->tap.count);
            if (record->tap.count > 0 && !record->tap.interrupted) {
                // set mouse button bit
                report_mouse_t mouse = pointing_device_get_report();
                mouse.buttons |= (1 << (kc - KC_BTN1));
                pointing_device_set_report(mouse);
                mouse_send_flag = true;
                btn_release_flag |= (1 << (kc - KC_BTN1));
            }
        }
    }

    return true;
}

gesture_id_t recognize_gesture(int16_t x, int16_t y) {
    gesture_id_t gesture_id = 0;

    if (abs(x) + abs(y) < get_gesture_threshold()) {
        gesture_id = GESTURE_NONE;
    } else if (x >= 0 && y >= 0) {
        gesture_id = GESTURE_DOWN_RIGHT;
    } else if (x < 0 && y >= 0) {
        gesture_id = GESTURE_DOWN_LEFT;
    } else if (x < 0 && y < 0) {
        gesture_id = GESTURE_UP_LEFT;
    } else if (x >= 0 && y < 0) {
        gesture_id = GESTURE_UP_RIGHT;
    }

    return gesture_id;
}

void process_gesture(uint8_t layer, gesture_id_t gesture_id) {
    switch (gesture_id) {
        case GESTURE_DOWN_RIGHT ... GESTURE_UP_RIGHT: {
            keypos_t keypos  = {.row = MATRIX_MSGES_ROW, .col = gesture_id - 1};
            uint16_t keycode = keymap_key_to_keycode(layer, keypos);
            tap_code16(keycode);
        } break;
        default:
            break;
    }
}

// Start gesture recognition
static void gesture_start(void) {
    dprint("Gesture start\n");
    gesture_wait   = true;
    gesture_move_x = 0;
    gesture_move_y = 0;
}

uint16_t keymap_key_to_keycode_bmp(uint8_t layer, keypos_t key) {
    uint16_t keycode =
        BMPAPI->app.keymap_key_to_keycode(layer, (bmp_api_keypos_t*)&key);

    // To use LT with mouse button, replace keycode and save offset
    if (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX) {
        uint8_t kc = keycode & 0xFF;
        if (kc >= KC_BTN1 && kc <= KC_BTN5) {
            kc_no_to_kc_offset = kc;

            // Gesture recognition trick
            // Start gesture when LT key is pressed
            if (matrix_is_on(key.row, key.col) && gesture_wait == false) {
                gesture_start();
            }

            return keycode & 0xFF00;
        } else {
            kc_no_to_kc_offset = 0;
        }
    }

    return keycode;
}

void matrix_scan_user(void) {
    if (btn_release_flag) {
        report_mouse_t mouse = pointing_device_get_report();
        mouse.buttons &= ~btn_release_flag;
        btn_release_flag = 0;
        pointing_device_set_report(mouse);
        mouse_send_flag = true;
    }
}

void post_process_record_user(uint16_t keycode, keyrecord_t* record) {
    if (keycode >= QK_MOMENTARY && keycode <= QK_MOMENTARY_MAX) {
        if (record->event.pressed && gesture_wait == false) {
            gesture_start();
        }
    }

    if ((keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX) ||
        (keycode >= QK_MOMENTARY && keycode <= QK_MOMENTARY_MAX)) {
        if (gesture_wait == true && (!record->event.pressed)) {
            gesture_wait = false;
            gesture_id_t gesture_id =
                recognize_gesture(gesture_move_x, gesture_move_y);

            uint8_t layer = 0;
            if ((keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX)) {
                layer = (keycode >> 8) & 0x0F;
            } else {
                layer = keycode & 0xFF;
            }

            process_gesture(layer, gesture_id);
            dprintf("id:%d x:%d,y:%d\n", gesture_id, gesture_move_x,
                    gesture_move_y);
        }
    }
}

void mouse_report_hook(mouse_parse_result_t const* report) {
    if (debug_enable) {
        xprintf("Mouse report\n");
        xprintf("b:%d ", report->button);
        xprintf("x:%d ", report->x);
        xprintf("y:%d ", report->y);
        xprintf("v:%d ", report->v);
        xprintf("h:%d ", report->h);
        xprintf("undef:%u\n", report->undefined);
    }

    //
    // Assign buttons to matrix
    // 8 button mouse is assumed
    //
    uint8_t button_prev    = matrix_mouse_dest[0];
    uint8_t button_current = report->button;

    if (button_current != button_prev) {
        matrix_has_changed = true;
    }
    matrix_mouse_dest[0] = button_current;

    //
    // Assign wheel to key action
    //
    if (report->v != 0) {
        keypos_t key;
        wheel_move_v = report->v;
        key.row      = MATRIX_MSWHEEL_ROW;
        key.col = report->v > 0 ? MATRIX_MSWHEEL_COL : MATRIX_MSWHEEL_COL + 1;
        action_exec((keyevent_t){
            .key = key, .pressed = true, .time = (timer_read() | 1)});
        action_exec((keyevent_t){
            .key = key, .pressed = false, .time = (timer_read() | 1)});
    }

    if (report->h != 0) {
        keypos_t key;
        wheel_move_h = report->h;
        key.row      = MATRIX_MSWHEEL_ROW;
        key.col =
            report->h > 0 ? MATRIX_MSWHEEL_COL + 2 : MATRIX_MSWHEEL_COL + 3;
        action_exec((keyevent_t){
            .key = key, .pressed = true, .time = (timer_read() | 1)});
        action_exec((keyevent_t){
            .key = key, .pressed = false, .time = (timer_read() | 1)});
    }

    //
    // Assign mouse movement
    //
    mouse_send_flag      = true;
    report_mouse_t mouse = pointing_device_get_report();

    if (layer_state != 0) {
        mouse.buttons = 0;
    }

    static int16_t x_rem;
    static int16_t y_rem;

    int16_t x = (x_rem + report->x) * spd_rate_num / spd_rate_den;
    int16_t y = (y_rem + report->y) * spd_rate_num / spd_rate_den;

    if (spd_rate_den - spd_rate_num > 0) {
        x_rem = (x_rem + report->x) - (x * spd_rate_den);
        y_rem = (y_rem + report->y) - (y * spd_rate_den);
    } else {
        x_rem = 0;
        y_rem = 0;
    }

    mouse.x += x;
    mouse.y += y;

    pointing_device_set_report(mouse);

    //
    // Save movement to recognize gesture
    //
    if (gesture_wait) {
        gesture_move_x += report->x;
        gesture_move_y += report->y;
    }
}
