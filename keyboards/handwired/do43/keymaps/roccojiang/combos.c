/* Copyright 2021 Rocco Jiang
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

enum combos {
    BSP,
    SCLN,
    MINS,
    EQL
};

const uint16_t PROGMEM bsp_combo[] = {KC_J, KC_K, COMBO_END};
const uint16_t PROGMEM scln_combo[] = {KC_L, KC_ENT, COMBO_END};
const uint16_t PROGMEM mins_combo[] = {KC_O, KC_P, COMBO_END};
const uint16_t PROGMEM eql_combo[] = {KC_P, KC_QUOT, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
    [BSP]  = COMBO(bsp_combo, KC_BSPC),
    [SCLN] = COMBO(scln_combo, KC_SCLN),
    [MINS] = COMBO(mins_combo, KC_MINS),
    [EQL]  = COMBO(eql_combo, KC_EQL)
};
