/* Copyright 2019 zk-phi
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

#include "joystick.h"
#include "pointing_device.h"

enum layers {
    DEFAULT,
    RAISE,
    LOWER
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [DEFAULT] = LAYOUT(
        KC_7, KC_8, KC_9,
        KC_4, KC_5, KC_6,
        LT(LOWER, KC_1), KC_2, LT(RAISE, KC_3)
    ),
    [RAISE] = LAYOUT(
        RGB_HUI, RGB_SAI, RGB_VAI,
        RGB_HUD, RGB_SAD, RGB_VAD,
        RGB_SPI, RGB_SPD, KC_NO
    ),
    [LOWER] = LAYOUT(
        KC_NO, KC_NO,   KC_NO,
        KC_NO, RGB_MOD, RGB_TOG,
        KC_NO, KC_NO,   KC_NO
    )
};

void keyboard_post_init_user (void) {
    rgb_matrix_enable_noeeprom();
}

void matrix_scan_user (void) {
    joystick_report_t joy = joystick_get_report();
    report_mouse_t r = pointing_device_get_report();

    r.x = joy.x * 30;
    r.y = joy.y * 30;

    pointing_device_set_report(r);
    pointing_device_send();
}
