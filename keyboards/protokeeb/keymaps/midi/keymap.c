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
 * Keymap: MIDI
 */

#include QMK_KEYBOARD_H

enum protokeeb_keymap_layers {
    LAYER_NOTES_SET_1,
    LAYER_NOTES_SET_2,
    LAYER_NOTES_SET_3,
    LAYER_RGB_CONTROL,
};

#define NOTES_SET_1 TG(LAYER_NOTES_SET_1)
#define NOTES_SET_2 TG(LAYER_NOTES_SET_2)
#define NOTES_SET_3 TG(LAYER_NOTES_SET_3)
#define RGB_CTRL MO(LAYER_RGB_CONTROL)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [LAYER_NOTES_SET_1] = LAYOUT(/* Notes Set-1 */
                                 MI_C, MI_Cs, MI_D, MI_Ds, KC_MUTE, MI_E, MI_F, MI_Fs, MI_G, MI_Gs, MI_A, MI_As, MI_B, RGB_CTRL, NOTES_SET_2, NOTES_SET_3, MI_TOGG),

    [LAYER_NOTES_SET_2] = LAYOUT(/* Notes Set-2 */
                                 MI_C1, MI_Cs1, MI_D1, MI_Ds1, KC_MUTE, MI_E1, MI_F1, MI_Fs1, MI_G1, MI_Gs1, MI_A1, MI_As1, MI_B1, NOTES_SET_1, KC_TRNS, NOTES_SET_3, KC_TRNS),

    [LAYER_NOTES_SET_3] = LAYOUT(/* Notes Set-3 */
                                 MI_C2, MI_Cs2, MI_D2, MI_Ds2, KC_MUTE, MI_E2, MI_F2, MI_Fs2, MI_G2, MI_Gs2, MI_A2, MI_As2, MI_B2, NOTES_SET_1, NOTES_SET_2, KC_TRNS, KC_TRNS),

    [LAYER_RGB_CONTROL] = LAYOUT(/* RGB Control */
                                 UG_TOGG, UG_NEXT, UG_PREV, DB_TOGG, KC_MUTE, UG_HUEU, UG_HUED, UG_SATU, UG_SATD, UG_VALU, UG_VALD, UG_SPDU, UG_SPDD, KC_TRNS, KC_NO, KC_NO, QK_BOOT),
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [LAYER_NOTES_SET_1] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [LAYER_NOTES_SET_2] = {ENCODER_CCW_CW(MI_OCTD, MI_OCTU)},
    [LAYER_NOTES_SET_3] = {ENCODER_CCW_CW(MI_TRSD, MI_TRSU)},
    [LAYER_RGB_CONTROL] = {ENCODER_CCW_CW(UG_HUED, UG_HUEU)},
};
#endif