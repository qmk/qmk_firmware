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
 * Keymap: Default
 */

#include QMK_KEYBOARD_H

enum protokeeb_keymap_layers {
    LAYER_BASE,
    LAYER_LOWER,
    LAYER_RAISE,
    LAYER_ADJUST,
};

#define LOWER LT(LAYER_LOWER, KC_P0)
#define RAISE LT(LAYER_RAISE, KC_PENT)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [LAYER_BASE] = LAYOUT(/* Base: Numpad without Num Lock*/
                          KC_P7, KC_P8, KC_P9, KC_PSLS, KC_MUTE, KC_P4, KC_P5, KC_P6, KC_PAST, KC_P1, KC_P2, KC_P3, KC_PMNS, LOWER, KC_PDOT, RAISE, KC_PPLS),

    [LAYER_LOWER] = LAYOUT(/* RGB Control */
                           UG_TOGG, UG_NEXT, UG_PREV, DB_TOGG, KC_TRNS, UG_HUEU, UG_HUED, UG_SATU, UG_SATD, UG_VALU, UG_VALD, UG_SPDU, UG_SPDD, KC_TRNS, KC_NO, KC_TRNS, QK_BOOT),

    [LAYER_RAISE] = LAYOUT(/* Media Control and Quick Launch*/
                           KC_MPLY, KC_MPRV, KC_MNXT, KC_MSTP, KC_TRNS, KC_CALC, KC_MYCM, KC_CPNL, KC_PWR, KC_PSCR, KC_HOME, KC_INS, KC_DEL, KC_TRNS, KC_NO, KC_TRNS, QK_RBT),

    [LAYER_ADJUST] = LAYOUT(/* Function Keys */
                            KC_F1, KC_F2, KC_F3, KC_F4, KC_TRNS, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_TRNS, KC_NO, KC_TRNS, KC_NO),
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [LAYER_BASE]   = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [LAYER_LOWER]  = {ENCODER_CCW_CW(KC_BRID, KC_BRIU)},
    [LAYER_RAISE]  = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [LAYER_ADJUST] = {ENCODER_CCW_CW(KC_TRNS, KC_TRNS)},
};
#endif

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, LAYER_LOWER, LAYER_RAISE, LAYER_ADJUST);
}