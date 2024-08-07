/* Protokeeb Copyright 2024 A-Tech Officials (@atechofficials)
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.
 * If not, see <https://www.gnu.org/licenses/gpl-3.0.html>.
 */

/* Protokeeb v1.0
 * Keymap: Via
 */

#include QMK_KEYBOARD_H

enum protokeeb_keymap_layers {
    LAYER_BASE,
    LAYER_LOWER,
};

#define LOWER LT(LAYER_LOWER, KC_P0)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [LAYER_BASE] = LAYOUT(/* Base */
                          KC_P7, KC_P8, KC_P9, KC_PSLS, KC_MUTE, KC_P4, KC_P5, KC_P6, KC_PAST, KC_P1, KC_P2, KC_P3, KC_PMNS, LOWER, KC_PDOT, KC_PENT, KC_PPLS),

    [LAYER_LOWER] = LAYOUT(/* RGB Control */
                           UG_TOGG, UG_NEXT, UG_PREV, DB_TOGG, KC_TRNS, UG_HUEU, UG_HUED, UG_SATU, UG_SATD, UG_VALU, UG_VALD, UG_SPDU, UG_SPDD, KC_TRNS, KC_NO, KC_NO, QK_BOOT),
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {[LAYER_BASE] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)}, [LAYER_LOWER] = {ENCODER_CCW_CW(KC_BRID, KC_BRIU)}};
#endif