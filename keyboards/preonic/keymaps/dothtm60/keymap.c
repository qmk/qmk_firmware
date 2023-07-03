/* Copyright 2015-2021 Jack Humbert
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 7 of the License, or
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
    // [0] = LAYOUT_ortho_5x12(
    [0] = LAYOUT_ortho_5x12(
        KC_GRV,     KC_1,       KC_2,       KC_3,       KC_4,          KC_5,         KC_6,      KC_7,         KC_8,       KC_9,          KC_0,          KC_BSPC,
        KC_TAB,     KC_Q,       KC_W,       KC_E,       KC_R,          KC_T,         KC_Y,      KC_U,         KC_I,       KC_O,          KC_P,          KC_QUOT,
        KC_ESC,     KC_A,       KC_S,       KC_D,       KC_F,          KC_G,         KC_H,      KC_J,         KC_K,       KC_L,          KC_SCLN,       KC_ENT,
        KC_LSFT,    KC_Z,       KC_X,       KC_C,       KC_V,          KC_B,         KC_N,      KC_M,         KC_COMM,    KC_DOT,        KC_UP,         KC_RSFT,
        MO(2),      KC_LCTL,    KC_LALT,    KC_LGUI,    LT(1,KC_SPC),  KC_SPC,       KC_SPC,    LT(1,KC_SPC), KC_RGUI,    KC_LEFT,       KC_DOWN,       KC_RGHT
    ),

    [1] = LAYOUT_ortho_5x12(
        KC_TILD,    KC_F1,      KC_F2,      KC_F3,      KC_F4,         LGUI(KC_MINS), LGUI(KC_EQL),  KC_NO,        KC_NO,      KC_NO,         KC_NO,         KC_DEL,
        KC_NO,      KC_F5,      KC_F6,      KC_F7,      KC_F8,         LGUI(KC_LCBR), LGUI(KC_RCBR), KC_LCBR,      KC_RCBR,    KC_DQUO,       KC_QUOT,       KC_BSLS,
        KC_NO,      KC_F9,      KC_F10,     KC_F11,     KC_F12,        LGUI(KC_LBRC), LGUI(KC_RBRC), KC_LBRC,      KC_RBRC,    KC_LT,         KC_GT,         KC_PENT,
        KC_TRNS,    KC_UNDS,    KC_PLUS,    KC_MINS,    KC_EQL,        LGUI(KC_QUES), LGUI(KC_SLSH), KC_QUES,      KC_SLSH,    KC_QUES,       LCAG(KC_UP),   KC_TRNS,
        MO(15),     KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,       LGUI(KC_SPC),  LGUI(KC_SPC),   KC_TRNS,      KC_TRNS,    LGUI(KC_LBRC), LCAG(KC_DOWN), LGUI(KC_RBRC)
    ),

    [2] = LAYOUT_ortho_5x12(
        DB_TOGG,    KC_F1,      KC_F2,      KC_F3,      KC_F4,         KC_F5,       KC_F6,      KC_F7,        KC_F8,      KC_F9,         KC_F10,        KC_DEL,
        RGB_TOG,    KC_F11,     KC_F12,     KC_F13,     KC_F14,        KC_F15,      KC_F16,     KC_F17,       KC_F18,     KC_F19,        KC_F20,        KC_NO,
        HYPR(KC_H), KC_MUTE,    KC_VOLD,    KC_VOLU,    KC_NO,         KC_NO,       KC_F21,     KC_F22,       KC_F23,     KC_F24,        KC_NO,         KC_NO,
        KC_TRNS,    KC_MPRV,    KC_MPLY,    KC_MNXT,    KC_NO,         KC_NO,       KC_NO,      KC_NO,        KC_NO,      KC_NO,         KC_PGUP,       KC_TRNS,
        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    MO(15),        KC_NO,       KC_NO,      MO(15),       KC_TRNS,    KC_HOME,       KC_PGDN,       KC_END
    ),




    // Musical keys

    [7] = LAYOUT_ortho_5x12(

        // Chromatic Scale       Vertical
        //      1,        2,        3,        4,        5,        6,        7,        8,        9,        10,       11,       12,
        KC_ESC,     MI_C,       MI_E,       MI_Gs,      MI_C_1,        MI_E_1,      MI_Gs_1,    MI_C_2,       MI_E_2,     MI_Gs_2,       MI_C_3,        MI_TRNS_0,
        KC_TAB,     MI_Cs,      MI_F,       MI_A,       MI_Cs_1,       MI_F_1,      MI_A_1,     MI_Cs_2,      MI_F_2,     MI_A_2,        MI_Cs_3,       MI_TRNSU,
        KC_SPC,     MI_D,       MI_Fs,      MI_As,      MI_D_1,        MI_Fs_1,     MI_As_1,    MI_D_2,       MI_Fs_2,    MI_As_2,       MI_D_3,        MI_TRNSD,
        MI_SUS,     MI_Ds,      MI_G,       MI_B,       MI_Ds_1,       MI_G_1,      MI_B_1,     MI_Ds_2,      MI_G_2,     MI_B_2,        MI_Ds_3,       MI_OCTU,
        MO(15),     KC_LCTL,    KC_LALT,    KC_LGUI,    MI_BENDD,      MI_SUS,      MI_SUS,     MI_BENDU,     KC_NO,      MI_MODSD,      MI_MODSU,      MI_OCTD
    ),


    [8] = LAYOUT_ortho_5x12(
        // Pocket Operator Scale Vertical
        //1,    2,       3,       4,        5,        6,        7,        8,        9,        10,       11,        12,
        KC_ESC,     MI_C,       MI_G,       MI_C_1,     MI_G_1,        MI_C_2,      MI_G_2,     MI_C_3,       MI_G_3,     MI_C_4,        MI_G_4,        MI_TRNS_0,
        KC_TAB,     MI_D,       MI_Gs,      MI_D_1,     MI_Gs_1,       MI_D_2,      MI_Gs_2,    MI_D_3,       MI_Gs_3,    MI_D_4,        MI_Gs_4,       MI_TRNSU,
        KC_SPC,     MI_Ds,      MI_As,      MI_Ds_1,    MI_As_1,       MI_Ds_2,     MI_As_2,    MI_Ds_3,      MI_As_3,    MI_Ds_4,       MI_As_4,       MI_TRNSD,
        MI_SUS,     MI_F,       MI_B,       MI_F_1,     MI_B_1,        MI_F_2,      MI_B_2,     MI_F_3,       MI_B_3,     MI_F_4,        MI_B_4,        MI_OCTU,
        MO(15),     KC_LCTL,    KC_LALT,    KC_LGUI,    MI_BENDD,      MI_SUS,      MI_SUS,     MI_BENDU,     KC_NO,      MI_MODSD,      MI_MODSU,      MI_OCTD
    ),

    [9] = LAYOUT_ortho_5x12(
        // Major scale           Vertical
        //      1,       2,       3,       4,        5,       6,       7,       8,       9,        10,       11,     12,
        KC_ESC,     MI_C,       MI_G,       MI_D_1,     MI_A_1,        MI_E_2,      MI_B_2,     MI_F_3,       MI_C_4,     MI_G_4,        MI_D_5,        MI_TRNS_0,
        KC_TAB,     MI_D,       MI_A,       MI_E_1,     MI_B_1,        MI_F_2,      MI_C_3,     MI_G_3,       MI_D_4,     MI_A_4,        MI_E_5,        MI_TRNSU,
        KC_SPC,     MI_E,       MI_B,       MI_F_1,     MI_C_2,        MI_G_2,      MI_D_3,     MI_A_3,       MI_E_4,     MI_B_4,        MI_F_5,        MI_TRNSD,
        MI_SUS,     MI_F,       MI_C_1,     MI_G_1,     MI_D_2,        MI_A_2,      MI_E_3,     MI_B_3,       MI_F_4,     MI_C_5,        MI_G_5,        MI_OCTU,
        MO(15),     KC_LCTL,    KC_LALT,    KC_LGUI,    MI_BENDD,      MI_SUS,      MI_SUS,     MI_BENDU,     KC_NO,      MI_MODSD,      MI_MODSU,      MI_OCTD
    ),

    [10] = LAYOUT_ortho_5x12(
        // Black Keys            Vertical
        //      1,       2,        3,        4,        5,        6,        7,        8,        9,        10,       11,     12,
        KC_ESC,     MI_C,       MI_A,       MI_G_1,     MI_F_2,        MI_D_3,      MI_C_4,     MI_A_4,       MI_G_5,     KC_NO,         KC_NO,         MI_TRNS_0,
        KC_TAB,     MI_D,       MI_C_1,     MI_A_1,     MI_G_2,        MI_F_3,      MI_D_4,     MI_C_5,       MI_A_5,     KC_NO,         KC_NO,         MI_TRNSU,
        KC_SPC,     MI_F,       MI_D_1,     MI_C_2,     MI_A_2,        MI_G_3,      MI_F_4,     MI_D_5,       KC_NO,      KC_NO,         KC_NO,         MI_TRNSD,
        MI_SUS,     MI_G,       MI_F_1,     MI_D_2,     MI_C_3,        MI_A_3,      MI_G_4,     MI_F_5,       KC_NO,      KC_NO,         KC_NO,         MI_OCTU,
        MO(15),     KC_LCTL,    KC_LALT,    KC_LGUI,    MI_BENDD,      MI_SUS,      MI_SUS,     MI_BENDU,     KC_NO,      MI_MODSD,      MI_MODSU,      MI_OCTD
    ),


    [11] = LAYOUT_ortho_5x12(
        // Chromatic Scale       Horizontal
        //1,    2,        3,        4,        5,        6,        7,        8,        9,        10,
        KC_ESC,     MI_C,       MI_Cs,      MI_D,       MI_Ds,         MI_E,        MI_F,       MI_Fs,        MI_G,       MI_Gs,         MI_A,          MI_TRNS_0,
        KC_TAB,     MI_As,      MI_B,       MI_C_1,     MI_Cs_1,       MI_D_1,      MI_Ds_1,    MI_E_1,       MI_F_1,     MI_Fs_1,       MI_G_1,        MI_TRNSU,
        KC_SPC,     MI_Gs_1,    MI_A_1,     MI_As_1,    MI_B_1,        MI_C_2,      MI_Cs_2,    MI_D_2,       MI_Ds_2,    MI_E_2,        MI_F_2,        MI_TRNSD,
        MI_SUS,     MI_Fs_2,    MI_G_2,     MI_Gs_2,    MI_A_2,        MI_As_2,     MI_B_2,     MI_C_3,       MI_Cs_3,    MI_D_3,        MI_Ds_3,       MI_OCTU,
        MO(15),     KC_LCTL,    KC_LALT,    KC_LGUI,    MI_BENDD,      MI_SUS,      MI_SUS,     MI_BENDU,     KC_NO,      MI_MODSD,      MI_MODSU,      MI_OCTD

    ),
    [12] = LAYOUT_ortho_5x12(
        // Pocket Operator Scale Horizontal
        //1,    2,        3,        4,        5,         6,         7,         8,         9,         10,
        KC_ESC,     MI_C,       MI_D,       MI_Ds,      MI_F,          MI_G,        MI_Gs,      MI_As,        MI_B,       MI_C_1,        MI_D_1,        MI_TRNS_0,
        KC_TAB,     MI_Ds_1,    MI_F_1,     MI_G_1,     MI_Gs_1,       MI_As_1,     MI_B_1,     MI_C_2,       MI_D_2,     MI_Ds_2,       MI_F_2,        MI_TRNSU,
        KC_SPC,     MI_G_2,     MI_Gs_2,    MI_As_2,    MI_B_2,        MI_C_3,      MI_D_3,     MI_Ds_3,      MI_F_3,     MI_G_3,        MI_Gs_3,       MI_TRNSD,
        MI_SUS,     MI_As_3,    MI_B_3,     MI_C_4,     MI_D_4,        MI_Ds_4,     MI_F_4,     MI_G_4,       MI_Gs_4,    MI_As_4,       MI_B_4,        MI_OCTU,
        MO(15),     KC_LCTL,    KC_LALT,    KC_LGUI,    MI_BENDD,      MI_SUS,      MI_SUS,     MI_BENDU,     KC_NO,      MI_MODSD,      MI_MODSU,      MI_OCTD



    ),


    [13] = LAYOUT_ortho_5x12(
        // Major scale           Horizontal
        //1,      2,          3,          4,        5,        6,          7,         8,        9,        10,
        KC_ESC,     MI_C,       MI_D,       MI_E,       MI_F,          MI_G,        MI_A,       MI_B,         MI_C_1,     MI_D_1,        MI_E_1,        MI_TRNS_0,
        KC_TAB,     MI_F_1,     MI_G_1,     MI_A_1,     MI_B_1,        MI_C_2,      MI_D_2,     MI_E_2,       MI_F_2,     MI_G_2,        MI_A_2,        MI_TRNSU,
        KC_SPC,     MI_B_2,     MI_C_3,     MI_D_3,     MI_E_3,        MI_F_3,      MI_G_3,     MI_A_3,       MI_B_3,     MI_C_4,        MI_D_4,        MI_TRNSD,
        MI_SUS,     MI_E_4,     MI_F_4,     MI_G_4,     MI_A_4,        MI_B_4,      MI_C_5,     MI_D_5,       MI_E_5,     MI_F_5,        MI_G_5,        MI_OCTU,
        MO(15),     KC_LCTL,    KC_LALT,    KC_LGUI,    MI_BENDD,      MI_SUS,      MI_SUS,     MI_BENDU,     KC_NO,      MI_MODSD,      MI_MODSU,      MI_OCTD


    ),
    [14] = LAYOUT_ortho_5x12(
        // Black Keys            Horizontal
        //1,        2,         3,         4,          5,        6,          7,         8,        9,        10,
        KC_ESC,     MI_C,       MI_D,       MI_F,       MI_G,          MI_A,        MI_C_1,     MI_D_1,       MI_F_1,     MI_G_1,        MI_A_1,        MI_TRNS_0,
        KC_TAB,     MI_C_2,     MI_D_2,     MI_F_2,     MI_G_2,        MI_A_2,      MI_C_3,     MI_D_3,       MI_F_3,     MI_G_3,        MI_A_3,        MI_TRNSU,
        KC_SPC,     MI_C_4,     MI_D_4,     MI_F_4,     MI_G_4,        MI_A_4,      MI_C,       MI_D,         MI_F,       MI_G,          MI_A,          MI_TRNSD,
        MI_SUS,     KC_NO,      KC_NO,      KC_NO,      KC_NO,         KC_NO,       KC_NO,      KC_NO,        KC_NO,      KC_NO,         KC_NO,         MI_OCTU,
        MO(15),     KC_LCTL,    KC_LALT,    KC_LGUI,    MI_BENDD,      MI_SUS,      MI_SUS,     MI_BENDU,     KC_NO,      MI_MODSD,      MI_MODSU,      MI_OCTD

    ),







    // Settings
    [15] = LAYOUT_ortho_5x12(
        DB_TOGG,    MI_CH1,     MI_CH2,     MI_CH3,     MI_CH4,        MI_CH5,      MI_CH6,     MI_CH7,       MI_CH8,     AU_TOG,        KC_NO,         QK_BOOT,
        KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_NO,         KC_NO,       KC_NO,      KC_NO,        KC_NO,      KC_NO,         KC_NO,         KC_NO,
        RGB_MOD,    RGB_HUI,    RGB_SAI,    RGB_VAI,    RGB_SPI,       KC_NO,       DF(11),     DF(12),       DF(13),     DF(14),        KC_NO,         DEBUG,
        RGB_RMOD,   RGB_HUD,    RGB_SAD,    RGB_VAD,    RGB_SPD,       KC_NO,       DF(7),      DF(8),        DF(9),      DF(10),        KC_NO,         KC_NO,
        KC_TRNS,    KC_NO,      KC_NO,      KC_NO,      KC_TRNS,       DF(0),       DF(0),      KC_TRNS,      KC_TRNS,    KC_NO,         KC_NO,         KC_NO
    )


};

