/* Copyright 2021 @ Keychron (https://www.keychron.com)
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
#include "test.h"

enum layers { _BASE, _FN1, _RESERVED1, _RESERVED2 };

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT_numpad_6x4(
        MO(_FN1), KC_ESC,  KC_BSPACE, KC_TAB,
        KC_NUMLOCK, KC_PSLS, KC_PAST,   KC_PMNS,
        KC_P7,      KC_P8,   KC_P9,
        KC_P4,      KC_P5,   KC_P6,     KC_PPLS,
        KC_P1,      KC_P2,   KC_P3,
        KC_P0,               KC_PDOT,   KC_PENT),

    [_FN1] = LAYOUT_numpad_6x4(
        KC_TRNS,    KC_MUTE, KC_VOLD,   KC_VOLU,
        RGB_MOD,    RGB_VAI, RGB_HUI,   KC_DEL,
        RGB_RMOD,   RGB_VAD, RGB_HUD,
        RGB_SAI,    RGB_SPI, KC_MPRV,   KC_TRNS,
        RGB_SAD,    RGB_SPD, KC_MPLY,
        RGB_TOG,             KC_MNXT,   KC_TRNS),

    [_RESERVED1] = LAYOUT_numpad_6x4(
        KC_TRNS,    KC_TRNS, KC_TRNS,   KC_TRNS,
        KC_TRNS,    KC_TRNS, KC_TRNS,   KC_TRNS,
        KC_TRNS,    KC_TRNS, KC_TRNS,
        KC_TRNS,    KC_TRNS, KC_TRNS,   KC_TRNS,
        KC_TRNS,    KC_TRNS, KC_TRNS,
        KC_TRNS,             KC_TRNS,   KC_TRNS),

    [_RESERVED2] = LAYOUT_numpad_6x4(
        KC_TRNS,    KC_TRNS, KC_TRNS,   KC_TRNS,
        KC_TRNS,    KC_TRNS, KC_TRNS,   KC_TRNS,
        KC_TRNS,    KC_TRNS, KC_TRNS,
        KC_TRNS,    KC_TRNS, KC_TRNS,   KC_TRNS,
        KC_TRNS,    KC_TRNS, KC_TRNS,
        KC_TRNS,             KC_TRNS,   KC_TRNS)
};

void matrix_scan_user(void) {
    /* Set timers for factory reset and backlight test */
    timer_task_start();
}

bool dip_switch_update_user(uint8_t index, bool active) {
    /* Send default layer state to host */
    system_switch_state_report(index, active);
    return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    process_other_record(keycode, record);
    return true;  // Process all other keycodes normally
}
