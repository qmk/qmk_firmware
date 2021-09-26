/* Copyright 2021 Joshua T.
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
#include "replicaJunction.h"

// enum additional_keyboard_layers {
//     L_RGB = _LAYER_SAFE_RANGE
// };

#define BSP_SYM LT(L_SYMBOLS, KC_BSPC)
#define SPC_NAV LT(L_NAVIGATION, KC_SPC)
#define ESC_NUM LT(L_NUMBERS, KC_ESC)
#define MO_FN MO(L_FN)
#define MO_MAC MO(L_MACROS)

#define DF_TYPE DF(L_BASE)
#define DF_GAME DF(L_GAMING)

#define ESC_SFT  LSFT_T(KC_ESC)
#define TAB_SFT  RSFT_T(KC_TAB)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [L_BASE] = LAYOUT_ortho_5x15(
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_MINS, KC_GRV,  KC_EQL,  KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
        KC_EQL,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,    KC_LBRC, KC_BSLS, KC_RBRC, KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_BSLS,
        KC_MINS, KC_A,    KC_R,    KC_S,    KC_T,    KC_G,    SALTTAB, KC_UP,   KC_END,  KC_M,    KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT,
        NUMWORD, KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,    KC_LEFT, KC_DOWN, KC_RGHT, KC_K,    KC_H,    KC_COMM, KC_DOT,  KC_SLSH, CAPWORD,
        KC_LCTL, KC_LGUI, KC_LALT, MO_FN,   ESC_SFT, BSP_SYM, CTL_DEL, KC_ENT,  ALT_ENT, SPC_NAV, TAB_SFT, MO_FN,   KC_RALT, KC_RGUI, KC_RCTL
    ),


    [L_GAMING] = LAYOUT_ortho_5x15(
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_MINS, KC_GRV,  KC_EQL,  KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_LBRC, KC_BSLS, KC_RBRC, KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_QUOT,
        KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_HOME, KC_DEL,  KC_PGUP, KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_ENT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_END,  KC_UP,   KC_PGDN, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
        KC_LCTL, KC_LCTL, KC_LALT, KC_LSFT, KC_SPC,  KC_LALT, KC_LEFT, KC_DOWN, KC_RGHT, KC_BSPC, KC_SPC,  MO_FN,   KC_RALT, KC_RGUI, KC_RCTL
    ),


    // [L_QWERTY] = LAYOUT_ortho_5x15(
    //     KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_MINS, KC_GRV,  KC_EQL,  KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
    //     KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_LBRC, KC_BSLS, KC_RBRC, KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_QUOT,
    //     KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_HOME, KC_DEL,  KC_PGUP, KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_ENT,
    //     KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_END,  KC_UP,   KC_PGDN, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
    //     KC_LCTL, KC_LGUI, KC_LALT, MO(_FN), KC_SPC,  KC_SPC,  KC_LEFT, KC_DOWN, KC_RGHT, KC_SPC,  KC_SPC,  MO(_FN), KC_RALT, KC_RGUI, KC_RCTL
    // ),


    // [L_CURSOR] = LAYOUT_ortho_5x15(
    //     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    //     _______, _______, _______, _______, _______, _______, _______, _______, _______, OS_SALL, OS_COPY, OS_PAST, OS_CUT,  OS_UNDO, _______,
    //     _______, KC_LGUI, KC_LALT, KC_LSFT, KC_LCTL, _______, _______, _______, SEARCH,  SALTTAB, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______,
    //     _______, KC_RGUI, KC_RALT, KC_RSFT, KC_RCTL, _______, _______, _______, _______, OS_FIND, KC_HOME, KC_PGDN, KC_PGUP, KC_END,  _______,
    //     _______, _______, _______, _______, _______, ooooooo, _______, _______, _______, SPC_NAV, _______, _______, _______, _______, _______
    // ),


    [L_NUMBERS] = LAYOUT_ortho_5x15(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_NLCK, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_HASH, KC_P7,   KC_P8,   KC_P9,   KC_PSLS, SFT_TAB,
        _______, KC_LGUI, KC_LALT, KC_LSFT, KC_LCTL, _______, _______, _______, _______, KC_PPLS, KC_P4,   KC_P5,   KC_P6,   KC_PAST, KC_TAB,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_PMNS, KC_P1,   KC_P2,   KC_P3,   KC_BSLS, KC_EQL,
        _______, _______, _______, _______, ooooooo, _______, _______, _______, _______, _______, KC_P0,   KC_P0,   KC_PDOT, KC_PENT, _______
    ),


    [L_SYMBOLS] = LAYOUT_ortho_5x15(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, KC_AT,   KC_LT,   KC_DLR,  KC_GT,   XXXXXXX, _______, _______, _______, XXXXXXX, KC_LBRC, KC_UNDS, KC_RBRC, XXXXXXX, _______,
        _______, KC_BSLS, KC_LPRN, KC_DQUO, KC_RPRN, KC_HASH, _______, _______, _______, KC_PERC, KC_LCBR, KC_EQL,  KC_RCBR, KC_PIPE, _______,
        _______, KC_EXLM, KC_COLN, KC_ASTR, KC_PLUS, XXXXXXX, _______, _______, _______, XXXXXXX, KC_AMPR, KC_CIRC, KC_TILD, KC_GRV,  _______,
        _______, _______, _______, _______, _______, ooooooo, _______, _______, _______, ooooooo, _______, _______, _______, _______, _______
    ),


    [L_NAVIGATION] = LAYOUT_ortho_5x15(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, OS_UNDO, OS_CUT,  OS_PAST, OS_COPY, OS_SALL, _______, _______, _______, KC_PGUP, KC_HOME, KC_UP,   KC_END,  KC_DEL,  _______,
        _______, KC_LGUI, KC_LALT, KC_LSFT, KC_LCTL, _______, _______, _______, _______, KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_BSPC, _______,
        _______, WIN_V,   _______, _______, OS_FIND, SEARCH,  _______, _______, _______, _______, SFT_TAB, KC_TAB,  KC_APP,  KC_PSCR, _______,
        _______, _______, _______, _______, _______, ooooooo, _______, _______, _______, ooooooo, _______, _______, _______, _______, _______
    ),


    [L_FN] = LAYOUT_ortho_5x15(
        DF_TYPE, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   _______, MS_JIGL, _______, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
        DF_GAME, RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, _______, _______, _______, _______, KC_VOLU, _______, _______, _______, _______, KC_F12,
        _______, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, _______, KC_CAPS, RESET,   _______, KC_MUTE, _______, _______, _______, _______, _______,
        _______, RGB_M_P, RGB_M_B, _______, _______, _______, _______, _______, _______, KC_VOLD, K_SECR1, K_SECR2, K_SECR3, K_SECR4, _______,
        _______, _______, _______, ooooooo, _______, _______, _______, _______, _______, _______, _______, ooooooo, _______, _______, _______
    ),


    [L_MACROS] = LAYOUT_ortho_5x15(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, QK_MAKE, _______, DM_REC2, DM_REC1, _______, _______, _______, _______, _______, SHEBANG, _______, _______, _______, _______,
        _______, QK_FLSH, _______, DM_PLY2, DM_PLY1, DM_RSTP, _______, _______, _______, PRG_NE,  PRG_EQ,  PRG_GEQ, PRG_LEQ, PRG_ARR, _______,
        _______, QK_VERS, _______, _______, _______, _______, _______, _______, _______, _______, PS_ITEM, FS_PIPE, _______, FS_ARR,  _______,
        _______, _______, _______, _______, ooooooo, _______, _______, _______, _______, ooooooo, _______, _______, _______, _______, _______
    )

    // [_FN] = LAYOUT_ortho_5x15( /* FUNCTION */
    //     _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_NLCK, KC_SLSH, KC_ASTR, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
    //     KC_MSEL, KC_CALC, KC_MYCM, KC_MAIL, RGB_HUD, RGB_HUI, KC_P7,   KC_P8,   KC_P9,   KC_MINS, _______, _______, KC_PSCR, KC_SLCK, KC_F12,
    //     KC_MPRV, KC_MPLY, KC_MNXT, KC_MSTP, RGB_SAD, RGB_SAI, KC_P4,   KC_P5,   KC_P6,   KC_PLUS, _______, RESET,   _______, _______, _______,
    //     KC_VOLD, KC_MUTE, KC_VOLU, KC_APP,  RGB_VAD, RGB_VAI, KC_P1,   KC_P2,   KC_P3,   KC_PENT, _______, _______, _______, _______, _______,
    //     _______, _______, RGB_TOG, ooooooo, RGB_RMOD,RGB_MOD, KC_P0,   _______, KC_PDOT, KC_PENT, KC_PENT, ooooooo, _______, _______, _______
    // )

    // // Template
    // [_LAYER] = LAYOUT_ortho_5x15(
    //     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    //     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    //     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    //     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    //     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    // ),
};

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, L_SYMBOLS, L_NAVIGATION, L_MACROS);
}
