/*
Copyright 2023 Joe Scotto

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H

const uint16_t PROGMEM scroll_down[] = {KC_MS_BTN1, KC_MS_BTN2, KC_MS_DOWN, COMBO_END};
const uint16_t PROGMEM scroll_up[] = {KC_MS_BTN1, KC_MS_BTN2, KC_MS_UP, COMBO_END};
const uint16_t PROGMEM middle_click[] = {KC_MS_BTN1, KC_MS_BTN2, COMBO_END};
combo_t key_combos[] = {
    COMBO(scroll_down, KC_MS_WH_DOWN),
    COMBO(scroll_up, KC_MS_WH_UP),
    COMBO(middle_click, KC_MS_BTN3)
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_MS_BTN1, KC_MS_BTN2, KC_MS_LEFT, KC_MS_UP,  KC_MS_DOWN, KC_MS_RIGHT
    )
};