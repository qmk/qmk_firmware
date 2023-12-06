/* Copyright 2017 Wunder
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

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_ortho_5x15(
        KC_GRV,        KC_1,          KC_2,          KC_3,          KC_4,          KC_5,          LGUI(KC_MINS), LGUI(KC_EQL),  KC_6,          KC_7,          KC_8,          KC_9,          KC_0,          LGUI(KC_0),    KC_BSPC,
        KC_TAB,        KC_Q,          KC_W,          KC_E,          KC_R,          KC_T,          LGUI(KC_LCBR), LGUI(KC_RCBR), KC_Y,          KC_U,          KC_I,          KC_O,          KC_P,          KC_LBRC,       KC_BSLS,
        KC_ESC,        KC_A,          KC_S,          KC_D,          KC_F,          KC_G,          LGUI(KC_LBRC), LGUI(KC_RBRC), KC_H,          KC_J,          KC_K,          KC_L,          KC_SCLN,       KC_QUOT,       KC_ENT,
        KC_LSFT,       KC_Z,          KC_X,          KC_C,          KC_V,          KC_B,          LGUI(KC_QUES), LGUI(KC_SLSH), KC_N,          KC_M,          KC_COMM,       KC_DOT,        KC_SLSH,       KC_UP,         KC_RSFT,
        MO(2),         KC_LCTL,       KC_LALT,       KC_LGUI,       LT(1,KC_SPC),  KC_SPC,        LGUI(KC_SPC),  LGUI(KC_SPC),  KC_SPC,        LT(1,KC_SPC),  KC_RGUI,       KC_RALT,       KC_LEFT,       KC_DOWN,       KC_RGHT
    ),

    [1] = LAYOUT_ortho_5x15(
        KC_TILD,       KC_F1,         KC_F2,         KC_F3,         KC_F4,         KC_NO,         KC_MINS,       KC_EQL,        KC_NO,         KC_NO,         KC_NO,         KC_NO,         KC_NO,         LGUI(KC_1),    KC_DEL,
        KC_NO,         KC_F5,         KC_F6,         KC_F7,         KC_F8,         KC_NO,         KC_LCBR,       KC_RCBR,       KC_NO,         KC_LCBR,       KC_RCBR,       KC_DQUO,       KC_QUOT,       KC_NO,         KC_SLSH,
        KC_NO,         KC_F9,         KC_F10,        KC_F11,        KC_F12,        KC_NO,         KC_LBRC,       KC_RBRC,       KC_NO,         KC_LBRC,       KC_RBRC,       KC_LT,         KC_GT,         KC_NO,         KC_PENT,
        KC_TRNS,       KC_UNDS,       KC_PLUS,       KC_MINS,       KC_EQL,        KC_NO,         KC_QUES,       KC_SLSH,       KC_NO,         KC_QUES,       KC_SLSH,       KC_QUES,       KC_SLSH,       LCAG(KC_UP),   KC_TRNS,
        MO(15),        KC_TRNS,       KC_TRNS,       KC_TRNS,       KC_TRNS,       LGUI(KC_SPC),  HYPR(KC_J),    KC_TRNS,       LGUI(KC_SPC),  KC_TRNS,       KC_TRNS,       KC_TRNS,       LGUI(KC_LBRC), LCAG(KC_DOWN), LGUI(KC_RBRC)
    ),

    [2] = LAYOUT_ortho_5x15(
        DB_TOGG,       KC_F1,         KC_F2,         KC_F3,         KC_F4,         KC_F5,         KC_NO,         KC_NO,         KC_F6,         KC_F7,         KC_F8,         KC_F9,         KC_F10,        KC_NO,         KC_DEL,
        RGB_TOG,       KC_F11,        KC_F12,        KC_F13,        KC_F14,        KC_F15,        KC_NO,         KC_NO,         KC_F16,        KC_F17,        KC_F18,        KC_F19,        KC_F20,        KC_NO,         KC_NO,
        HYPR(KC_H),    KC_MUTE,       KC_VOLD,       KC_VOLU,       KC_NO,         KC_NO,         KC_NO,         KC_NO,         KC_F21,        KC_F22,        KC_F23,        KC_F24,        KC_NO,         KC_NO,         KC_NO,
        KC_TRNS,       KC_MPRV,       KC_MPLY,       KC_MNXT,       KC_NO,         KC_NO,         KC_NO,         KC_NO,         KC_NO,         KC_NO,         KC_NO,         KC_NO,         KC_NO,         KC_PGUP,       KC_TRNS,
        KC_TRNS,       KC_TRNS,       KC_TRNS,       KC_TRNS,       MO(15),        HYPR(KC_K),    KC_NO,         KC_NO,         KC_TRNS,       MO(15),        KC_TRNS,       KC_TRNS,       KC_HOME,       KC_PGDN,       KC_END

    ),

    // Musical keys

    [3] = LAYOUT_ortho_5x15(
        // Chromatic Scale       Vertical  Typing 60
        KC_ESC,        MI_C,          MI_E,          MI_Gs,          MI_C1,         MI_E1,        KC_NO,         KC_NO,          MI_Gs1,        MI_C2,         MI_E2,         MI_Gs2,        MI_C3,         MI_E3,        MI_TR0,
        KC_TAB,        MI_Cs,         MI_F,          MI_A,           MI_Cs1,        MI_F1,        KC_NO,         KC_NO,          MI_A1,         MI_Cs2,        MI_F2,         MI_A2,         MI_Cs3,        MI_F3,        MI_TRSU,
        KC_SPC,        MI_D,          MI_Fs,         MI_As,          MI_D1,         MI_Fs1,       KC_NO,         KC_NO,          MI_As1,        MI_D2,         MI_Fs2,        MI_As2,        MI_D3,         MI_Fs3,       MI_TRSD,
        MI_SUST,        MI_Ds,         MI_G,          MI_B,           MI_Ds1,        MI_G1,        KC_NO,         KC_NO,          MI_B1,         MI_Ds2,        MI_G2,         MI_B2,         MI_Ds3,        MI_G3,        MI_OCTU,
        MO(15),        KC_LCTL,       KC_LALT,       KC_LGUI,       MI_BNDD,      MI_SUST,        MI_SUST,        MI_SUST,        MI_SUST,        MI_BNDU,      KC_NO,         KC_NO,         MI_MODD,      MI_MODU,      MI_OCTD

    ),

    [4] = LAYOUT_ortho_5x15(
        // Pocket Operator Scale Vertical  Typing 60
        KC_ESC,        MI_C,          MI_G,           MI_C1,         MI_G1,         MI_C2,        KC_NO,         KC_NO,          MI_G2,         MI_C3,         MI_G3,         MI_C4,         MI_G4,         MI_C5,        MI_TR0,
        KC_TAB,        MI_D,          MI_Gs,          MI_D1,         MI_Gs1,        MI_D2,        KC_NO,         KC_NO,          MI_Gs2,        MI_D3,         MI_Gs3,        MI_D4,         MI_Gs4,        MI_D5,        MI_TRSU,
        KC_SPC,        MI_Ds,         MI_As,          MI_Ds1,        MI_As1,        MI_Ds2,       KC_NO,         KC_NO,          MI_As2,        MI_Ds3,        MI_As3,        MI_Ds4,        MI_As4,        MI_Ds5,       MI_TRSD,
        MI_SUST,        MI_F,          MI_B,           MI_F1,         MI_B1,         MI_F2,        KC_NO,         KC_NO,          MI_B2,         MI_F3,         MI_B3,         MI_F4,         MI_B4,         MI_F5,        MI_OCTU,
        MO(15),        KC_LCTL,       KC_LALT,       KC_LGUI,       MI_BNDD,      MI_SUST,        MI_SUST,        MI_SUST,        MI_SUST,        MI_BNDU,      KC_NO,         KC_NO,         MI_MODD,      MI_MODU,      MI_OCTD

    ),

    [5] = LAYOUT_ortho_5x15(
        // Major scale           Vertical  Typing 60
        KC_ESC,        MI_C,          MI_G,           MI_D1,         MI_A1,         MI_E2,        KC_NO,         KC_NO,          MI_B2,         MI_F3,         MI_C4,         MI_G4,         MI_D5,         MI_A5,        MI_TR0,
        KC_TAB,        MI_D,          MI_A,           MI_E1,         MI_B1,         MI_F2,        KC_NO,         KC_NO,          MI_C3,         MI_G3,         MI_D4,         MI_A4,         MI_E5,         MI_B5,        MI_TRSU,
        KC_SPC,        MI_E,          MI_B,           MI_F1,         MI_C2,         MI_G2,        KC_NO,         KC_NO,          MI_D3,         MI_A3,         MI_E4,         MI_B4,         MI_F5,        KC_NO,         MI_TRSD,
        MI_SUST,        MI_F,           MI_C1,         MI_G1,         MI_D2,         MI_A2,        KC_NO,         KC_NO,          MI_E3,         MI_B3,         MI_F4,         MI_C5,         MI_G5,        KC_NO,         MI_OCTU,
        MO(15),        KC_LCTL,       KC_LALT,       KC_LGUI,       MI_BNDD,      MI_SUST,        MI_SUST,        MI_SUST,        MI_SUST,        MI_BNDU,      KC_NO,         KC_NO,         MI_MODD,      MI_MODU,      MI_OCTD

    ),

    [6] = LAYOUT_ortho_5x15(
        // Black Keys            Vertical  Typing 60
        KC_ESC,        MI_C,          MI_A,           MI_G1,         MI_F2,         MI_D3,        KC_NO,         KC_NO,          MI_C4,         MI_A4,         MI_G5,        KC_NO,         KC_NO,         KC_NO,         MI_TR0,
        KC_TAB,        MI_D,           MI_C1,         MI_A1,         MI_G2,         MI_F3,        KC_NO,         KC_NO,          MI_D4,         MI_C5,         MI_A5,        KC_NO,         KC_NO,         KC_NO,         MI_TRSU,
        KC_SPC,        MI_F,           MI_D1,         MI_C2,         MI_A2,         MI_G3,        KC_NO,         KC_NO,          MI_F4,         MI_D5,        KC_NO,         KC_NO,         KC_NO,         KC_NO,         MI_TRSD,
        MI_SUST,        MI_G,           MI_F1,         MI_D2,         MI_C3,         MI_A3,        KC_NO,         KC_NO,          MI_G4,         MI_F5,        KC_NO,         KC_NO,         KC_NO,         KC_NO,         MI_OCTU,
        MO(15),        KC_LCTL,       KC_LALT,       KC_LGUI,       MI_BNDD,      MI_SUST,        MI_SUST,        MI_SUST,        MI_SUST,        MI_BNDU,      KC_NO,         KC_NO,         MI_MODD,      MI_MODU,      MI_OCTD

    ),

    [7] = LAYOUT_ortho_5x15(
        // Chromatic Scale       Vertical
        KC_ESC,        MI_C,          MI_E,          MI_Gs,          MI_C1,         MI_E1,         MI_Gs1,        MI_C2,         MI_E2,         MI_Gs2,        MI_C3,         MI_E3,         MI_Gs3,       KC_NO,         MI_TR0,
        KC_TAB,        MI_Cs,         MI_F,          MI_A,           MI_Cs1,        MI_F1,         MI_A1,         MI_Cs2,        MI_F2,         MI_A2,         MI_Cs3,        MI_F3,         MI_A3,        KC_NO,         MI_TRSU,
        KC_SPC,        MI_D,          MI_Fs,         MI_As,          MI_D1,         MI_Fs1,        MI_As1,        MI_D2,         MI_Fs2,        MI_As2,        MI_D3,         MI_Fs3,        MI_As3,       KC_NO,         MI_TRSD,
        MI_SUST,        MI_Ds,         MI_G,          MI_B,           MI_Ds1,        MI_G1,         MI_B1,         MI_Ds2,        MI_G2,         MI_B2,         MI_Ds3,        MI_G3,         MI_B3,        KC_NO,         MI_OCTU,
        MO(15),        KC_LCTL,       KC_LALT,       KC_LGUI,       MI_BNDD,      MI_SUST,        MI_SUST,        MI_SUST,        MI_SUST,        MI_BNDU,      KC_NO,         KC_NO,         MI_MODD,      MI_MODU,      MI_OCTD

    ),

    [8] = LAYOUT_ortho_5x15(
        // Pocket Operator Scale Vertical
        KC_ESC,        MI_C,          MI_G,           MI_C1,         MI_G1,         MI_C2,         MI_G2,         MI_C3,         MI_G3,         MI_C4,         MI_G4,         MI_C5,         MI_G5,        KC_NO,         MI_TR0,
        KC_TAB,        MI_D,          MI_Gs,          MI_D1,         MI_Gs1,        MI_D2,         MI_Gs2,        MI_D3,         MI_Gs3,        MI_D4,         MI_Gs4,        MI_D5,         MI_Gs5,       KC_NO,         MI_TRSU,
        KC_SPC,        MI_Ds,         MI_As,          MI_Ds1,        MI_As1,        MI_Ds2,        MI_As2,        MI_Ds3,        MI_As3,        MI_Ds4,        MI_As4,        MI_Ds5,        MI_As5,       KC_NO,         MI_TRSD,
        MI_SUST,        MI_F,          MI_B,           MI_F1,         MI_B1,         MI_F2,         MI_B2,         MI_F3,         MI_B3,         MI_F4,         MI_B4,         MI_F5,         MI_B5,        KC_NO,         MI_OCTU,
        MO(15),        KC_LCTL,       KC_LALT,       KC_LGUI,       MI_BNDD,      MI_SUST,        MI_SUST,        MI_SUST,        MI_SUST,        MI_BNDU,      KC_NO,         KC_NO,         MI_MODD,      MI_MODU,      MI_OCTD

    ),

    [9] = LAYOUT_ortho_5x15(
        // Major scale           Vertical
        KC_ESC,        MI_C,          MI_G,           MI_D1,         MI_A1,         MI_E2,         MI_B2,         MI_F3,         MI_C4,         MI_G4,         MI_D5,         MI_A5,        KC_NO,         KC_NO,         MI_TR0,
        KC_TAB,        MI_D,          MI_A,           MI_E1,         MI_B1,         MI_F2,         MI_C3,         MI_G3,         MI_D4,         MI_A4,         MI_E5,         MI_B5,        KC_NO,         KC_NO,         MI_TRSU,
        KC_SPC,        MI_E,          MI_B,           MI_F1,         MI_C2,         MI_G2,         MI_D3,         MI_A3,         MI_E4,         MI_B4,         MI_F5,        KC_NO,         KC_NO,         KC_NO,         MI_TRSD,
        MI_SUST,        MI_F,           MI_C1,         MI_G1,         MI_D2,         MI_A2,         MI_E3,         MI_B3,         MI_F4,         MI_C5,         MI_G5,        KC_NO,         KC_NO,         KC_NO,         MI_OCTU,
        MO(15),        KC_LCTL,       KC_LALT,       KC_LGUI,       MI_BNDD,      MI_SUST,        MI_SUST,        MI_SUST,        MI_SUST,        MI_BNDU,      KC_NO,         KC_NO,         MI_MODD,      MI_MODU,      MI_OCTD

    ),

    [10] = LAYOUT_ortho_5x15(
        // Black Keys            Vertical
        KC_ESC,        MI_C,          MI_A,           MI_G1,         MI_F2,         MI_D3,         MI_C4,         MI_A4,         MI_G5,        KC_NO,         KC_NO,         KC_NO,         KC_NO,         KC_NO,         MI_TR0,
        KC_TAB,        MI_D,           MI_C1,         MI_A1,         MI_G2,         MI_F3,         MI_D4,         MI_C5,         MI_A5,        KC_NO,         KC_NO,         KC_NO,         KC_NO,         KC_NO,         MI_TRSU,
        KC_SPC,        MI_F,           MI_D1,         MI_C2,         MI_A2,         MI_G3,         MI_F4,         MI_D5,        KC_NO,         KC_NO,         KC_NO,         KC_NO,         KC_NO,         KC_NO,         MI_TRSD,
        MI_SUST,        MI_G,           MI_F1,         MI_D2,         MI_C3,         MI_A3,         MI_G4,         MI_F5,        KC_NO,         KC_NO,         KC_NO,         KC_NO,         KC_NO,         KC_NO,         MI_OCTU,
        MO(15),        KC_LCTL,       KC_LALT,       KC_LGUI,       MI_BNDD,      MI_SUST,        MI_SUST,        MI_SUST,        MI_SUST,        MI_BNDU,      KC_NO,         KC_NO,         MI_MODD,      MI_MODU,      MI_OCTD

    ),

    [11] = LAYOUT_ortho_5x15(
        // Chromatic Scale       Horizontal
        KC_ESC,        MI_C,          MI_Cs,         MI_D,          MI_Ds,         MI_E,          MI_F,          MI_Fs,         MI_G,          MI_Gs,         MI_A,          MI_As,         MI_B,          KC_NO,         MI_TR0,
        KC_TAB,         MI_C1,         MI_Cs1,        MI_D1,         MI_Ds1,        MI_E1,         MI_F1,         MI_Fs1,        MI_G1,         MI_Gs1,        MI_A1,         MI_As1,        MI_B1,        KC_NO,         MI_TRSU,
        KC_SPC,         MI_C2,         MI_Cs2,        MI_D2,         MI_Ds2,        MI_E2,         MI_F2,         MI_Fs2,        MI_G2,         MI_Gs2,        MI_A2,         MI_As2,        MI_B2,        KC_NO,         MI_TRSD,
        MI_SUST,         MI_C3,         MI_Cs3,        MI_D3,         MI_Ds3,        MI_E3,         MI_F3,         MI_Fs3,        MI_G3,         MI_Gs3,        MI_A3,         MI_As3,        MI_B3,        KC_NO,         MI_OCTU,
        MO(15),        KC_LCTL,       KC_LALT,       KC_LGUI,       MI_BNDD,      MI_SUST,        MI_SUST,        MI_SUST,        MI_SUST,        MI_BNDU,      KC_NO,         KC_NO,         MI_MODD,      MI_MODU,      MI_OCTD

    ),
    [12] = LAYOUT_ortho_5x15(
        // Pocket Operator Scale Horizontal
        KC_ESC,        MI_C,          MI_D,          MI_Ds,         MI_F,          MI_G,          MI_Gs,         MI_As,         MI_B,           MI_C1,         MI_D1,         MI_Ds1,        MI_F1,        KC_NO,         MI_TR0,
        KC_TAB,         MI_G1,         MI_Gs1,        MI_As1,        MI_B1,         MI_C2,         MI_D2,         MI_Ds2,        MI_F2,         MI_G2,         MI_Gs2,        MI_As2,        MI_B2,        KC_NO,         MI_TRSU,
        KC_SPC,         MI_C3,         MI_D3,         MI_Ds3,        MI_F3,         MI_G3,         MI_Gs3,        MI_As3,        MI_B3,         MI_C4,         MI_D4,         MI_Ds4,        MI_F4,        KC_NO,         MI_TRSD,
        MI_SUST,         MI_G4,         MI_Gs4,        MI_As4,        MI_B4,         MI_C5,         MI_D5,         MI_Ds5,        MI_F5,         MI_G5,         MI_Gs5,        MI_As5,        MI_B5,        KC_NO,         MI_OCTU,
        MO(15),        KC_LCTL,       KC_LALT,       KC_LGUI,       MI_BNDD,      MI_SUST,        MI_SUST,        MI_SUST,        MI_SUST,        MI_BNDU,      KC_NO,         KC_NO,         MI_MODD,      MI_MODU,      MI_OCTD

    ),

    [13] = LAYOUT_ortho_5x15(
        // Major scale           Horizontal
        KC_ESC,        MI_C,          MI_D,          MI_E,          MI_F,          MI_G,          MI_A,          MI_B,           MI_C1,         MI_D1,         MI_E1,         MI_F1,         MI_G1,        KC_NO,         MI_TR0,
        KC_TAB,         MI_A1,         MI_B1,         MI_C2,         MI_D2,         MI_E2,         MI_F2,         MI_G2,         MI_A2,         MI_B2,         MI_C3,         MI_D3,         MI_E3,        KC_NO,         MI_TRSU,
        KC_SPC,         MI_F3,         MI_G3,         MI_A3,         MI_B3,         MI_C4,         MI_D4,         MI_E4,         MI_F4,         MI_G4,         MI_A4,         MI_B4,         MI_C5,        KC_NO,         MI_TRSD,
        MI_SUST,         MI_D5,         MI_E5,         MI_F5,         MI_G5,         MI_A5,         MI_B5,        KC_NO,         KC_NO,         KC_NO,         KC_NO,         KC_NO,         KC_NO,         KC_NO,         MI_OCTU,
        MO(15),        KC_LCTL,       KC_LALT,       KC_LGUI,       MI_BNDD,      MI_SUST,        MI_SUST,        MI_SUST,        MI_SUST,        MI_BNDU,      KC_NO,         KC_NO,         MI_MODD,      MI_MODU,      MI_OCTD

    ),
    [14] = LAYOUT_ortho_5x15(
        // Black Keys            Horizontal
        KC_ESC,        MI_C,          MI_D,          MI_F,          MI_G,          MI_A,           MI_C1,         MI_D1,         MI_F1,         MI_G1,         MI_A1,         MI_C2,         MI_D2,        KC_NO,         MI_TR0,
        KC_TAB,         MI_F2,         MI_G2,         MI_A2,         MI_C3,         MI_D3,         MI_F3,         MI_G3,         MI_A3,         MI_C4,         MI_D4,         MI_F4,         MI_G4,        KC_NO,         MI_TRSU,
        KC_SPC,         MI_A4,        MI_C,          MI_D,          MI_F,          MI_G,          MI_A,          KC_NO,         KC_NO,         KC_NO,         KC_NO,         KC_NO,         KC_NO,         KC_NO,         MI_TRSD,
        MI_SUST,        KC_NO,         KC_NO,         KC_NO,         KC_NO,         KC_NO,         KC_NO,         KC_NO,         KC_NO,         KC_NO,         KC_NO,         KC_NO,         KC_NO,         KC_NO,         MI_OCTU,
        MO(15),        KC_LCTL,       KC_LALT,       KC_LGUI,       MI_BNDD,      MI_SUST,        MI_SUST,        MI_SUST,        MI_SUST,        MI_BNDU,      KC_NO,         KC_NO,         MI_MODD,      MI_MODU,      MI_OCTD

    ),

    [15] = LAYOUT_ortho_5x15(
        // Settings
        DB_TOGG,       MI_CH1,        MI_CH2,        MI_CH3,        MI_CH4,        MI_CH5,        KC_NO,         KC_NO,         MI_CH6,        MI_CH7,        MI_CH8,        AU_TOGG,        KC_NO,         KC_NO,         QK_BOOT,
        KC_NO,         KC_NO,         KC_NO,         KC_NO,         KC_NO,         KC_NO,         KC_NO,         KC_NO,         DF(3),         DF(4),         DF(5),         DF(6),         KC_NO,         KC_NO,         KC_NO,
        RGB_MOD,       RGB_HUI,       RGB_SAI,       RGB_VAI,       RGB_SPI,       KC_NO,         KC_NO,         KC_NO,         DF(11),        DF(12),        DF(13),        DF(14),        KC_NO,         KC_NO,         DB_TOGG,
        RGB_RMOD,      RGB_HUD,       RGB_SAD,       RGB_VAD,       RGB_SPD,       KC_NO,         KC_NO,         KC_NO,         DF(7),         DF(8),         DF(9),         DF(10),        KC_NO,         KC_NO,         KC_NO,
        KC_TRNS,       KC_NO,         KC_NO,         KC_NO,         KC_TRNS,       DF(0),         DF(0),         DF(0),         DF(0),         KC_TRNS,       KC_NO,         KC_TRNS,       KC_NO,         KC_NO,         KC_NO
    )
};

