/* Copyright 2023 @ Keychron (https://www.keychron.com)
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
#include "keychron_common.h"

enum layers { _BASE, _FN1, _RESERVED1, _RESERVED2 };

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT_numpad_6x4(
        MO(_FN1), KC_ESC,  KC_BSPC,   KC_TAB,
        KC_NUM,   KC_PSLS, KC_PAST,   KC_PMNS,
        KC_P7,    KC_P8,   KC_P9,
        KC_P4,    KC_P5,   KC_P6,     KC_PPLS,
        KC_P1,    KC_P2,   KC_P3,
        KC_P0,             KC_PDOT,   KC_PENT),

    [_FN1] = LAYOUT_numpad_6x4(
        _______,    KC_MUTE, KC_VOLD,   KC_VOLU,
        RM_NEXT,    RM_VALU, RM_HUEU,   KC_DEL,
        RM_PREV,    RM_VALD, RM_HUED,
        RM_SATU,    RM_SPDU, KC_MPRV,   _______,
        RM_SATD,    RM_SPDD, KC_MPLY,
        RM_TOGG,             KC_MNXT,   _______),

    [_RESERVED1] = LAYOUT_numpad_6x4(
        _______,    _______, _______,   _______,
        _______,    _______, _______,   _______,
        _______,    _______, _______,
        _______,    _______, _______,   _______,
        _______,    _______, _______,
        _______,             _______,   _______),

    [_RESERVED2] = LAYOUT_numpad_6x4(
        _______,    _______, _______,   _______,
        _______,    _______, _______,   _______,
        _______,    _______, _______,
        _______,    _______, _______,   _______,
        _______,    _______, _______,
        _______,             _______,   _______)
};

void housekeeping_task_user(void) {
    housekeeping_task_keychron();
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_keychron(keycode, record)) {
        return false;
    }
    return true;
}
