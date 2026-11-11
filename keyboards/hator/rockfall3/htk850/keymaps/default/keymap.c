/* Copyright (C) 2024 koosikus
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

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

<<<<<<< Updated upstream
    [0] = LAYOUT_ansi( /* Base */
=======
    [0] = LAYOUT_all( /* Base */
>>>>>>> Stashed changes
		KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,           KC_PSCR, KC_SCRL, KC_PAUS,
		KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_INS,  KC_HOME, KC_PGUP,
		KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_DEL,  KC_END,  KC_PGDN,
		KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_NUHS, KC_ENT,
		KC_LSFT, KC_NUBS, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT,          KC_UP,
		KC_LCTL, KC_LGUI, KC_LALT,                   KC_SPC,                             KC_RALT, MO(1),   MO(4),           KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT),

<<<<<<< Updated upstream
    [1] = LAYOUT_ansi( /* FN1 */
	    EE_CLR,  KC_BRID, KC_BRIU, KC_MAIL, KC_WSCH, KC_CALC, KC_MSEL, KC_MPRV, KC_MPLY, KC_MNXT, KC_MUTE, KC_VOLD, KC_VOLU,          _______, _______, _______,
		NK_TOGG, KC_BT1,  KC_BT2,  KC_BT3,  KC_2G4,  _______, _______, _______, _______, _______, _______, _______, _______, RGB_MOD, _______, _______, RGB_HUI,
		TO(2),   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RGB_HUD,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,          RGB_VAI,
		_______, GU_TOGG, _______,                   _______,                            _______, _______, _______,          _______, RGB_SPD, RGB_VAD, RGB_SPI),

    [2] = LAYOUT_ansi( /* Base */
=======
    [1] = LAYOUT_all( /* FN1 */
	    EE_CLR,  KC_BRID, KC_BRIU, KC_MAIL, KC_WSCH, KC_CALC, KC_MSEL, KC_MPRV, KC_MPLY, KC_MNXT, KC_MUTE, KC_VOLD, KC_VOLU,          _______, _______, _______,
		NK_TOGG, KC_BT1,  KC_BT2,  KC_BT3,  KC_2G4,  _______, _______, _______, _______, _______, _______, _______, _______, RM_NEXT, _______, _______, RM_HUEU,
		PDF(2),   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RM_HUED,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,          RM_VALU,
		_______, GU_TOGG, KC_BATQ,                   _______,                            _______, _______, _______,          _______, RM_SPDD, RM_VALD, RM_SPDU),

    [2] = LAYOUT_all( /* Base */
>>>>>>> Stashed changes
		KC_ESC,KC_BRID,KC_BRIU,C(KC_UP),C(S(KC_DOWN)),KC_F5,  KC_F6,   KC_MPRV, KC_MPLY, KC_MNXT, KC_MUTE, KC_VOLD, KC_VOLU,          KC_PSCR, KC_SCRL, KC_PAUS,
		KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_INS,  KC_HOME, KC_PGUP,
		KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_DEL,  KC_END,  KC_PGDN,
		KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_NUHS, KC_ENT,
		KC_LSFT, KC_NUBS, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT,          KC_UP,
		KC_LCTL, KC_LALT, KC_LGUI,                   KC_SPC,                             KC_RGUI, MO(3),   MO(4),            KC_RCTL, KC_LEFT, KC_DOWN,   KC_RGHT),

<<<<<<< Updated upstream
    [3] = LAYOUT_ansi( /* FN1 */
		EE_CLR,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   _______, _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,           _______, _______, _______,
		NK_TOGG, KC_BT1,  KC_BT2,  KC_BT3,  KC_2G4,  _______, _______, _______, _______, _______, _______, _______, _______, RGB_MOD, _______, _______, RGB_HUI,
		TO(0),   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RGB_HUD,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,          RGB_VAI,
		_______, _______, _______,                   _______,                            _______, _______, _______,          _______, RGB_SPD, RGB_VAD, RGB_SPI),

    [4] = LAYOUT_ansi( /* FN2 */
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RGB_MOD, _______, _______, RGB_HUI,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RGB_HUD,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,          RGB_VAI,
		_______, _______, _______,                   _______,                            _______, _______, _______,          _______, RGB_SPD, RGB_VAD, RGB_SPI),

    [5] = LAYOUT_ansi( /* FNx */
=======
    [3] = LAYOUT_all( /* FN1 */
		EE_CLR,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   _______, _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,           _______, _______, _______,
		NK_TOGG, KC_BT1,  KC_BT2,  KC_BT3,  KC_2G4,  _______, _______, _______, _______, _______, _______, _______, _______, RM_NEXT, _______, _______, RM_HUEU,
		PDF(0),   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RM_HUED,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,          RM_VALU,
		_______, KC_BATQ, _______,                   _______,                            _______, _______, _______,          _______, RM_SPDD, RM_VALD, RM_SPDU),

    [4] = LAYOUT_all( /* FN2 */
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RM_NEXT, _______, _______, RM_HUEU,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RM_HUED,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,          RM_VALU,
		_______, _______, _______,                   _______,                            _______, _______, _______,          _______, RM_SPDD, RM_VALD, RM_SPDU),

    [5] = LAYOUT_all( /* FNx */
>>>>>>> Stashed changes
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,          _______,
		_______, _______, _______,                   _______,                            _______, _______, _______,          _______, _______, _______, _______)
};
