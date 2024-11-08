/* Copyright 2021 Christian C. Berclaz
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

#include "chrisgve.h"

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

   [_GAMING] = LAYOUT(
        QK_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSLS,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
        KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_ENT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, QUT_SFT,
        ADJUST,  TD_ADJ,  KC_LALT, KC_LGUI, LOWER,   KC_SPC,  KC_SPC,  RAISE,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
    ),

   [_QWERTY_MAC] = LAYOUT(
        QK_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSLS,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    CU_BSPC,
        CPS_CTL, A_MOUSE, KC_S,    M_NAV_1, M_F_NAV, KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_ENT,
        SFT_MSE, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, QUT_SFT,
        ADJUST,  TD_ADJ,  KC_LALT, KC_LGUI, LOWER,   SPC_RSE, SPC_RSE, RAISE,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
    ),

    [_MAC_NAV_1] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, M_F_WRD, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, A_SHIFT, S_SHIFT, _______, M_NAV_2, _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, _______,
        _______, _______, _______, _______, _______, M_B_WRD, KC_HOME, KC_END,  _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),

    [_MAC_NAV_2] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END,  _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END
    ),

    [_QWERTY_LINUX] = LAYOUT(
        QK_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSLS,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    CU_BSPC,
        CPS_CTL, A_MOUSE, KC_S,    L_NAV_1, L_F_NAV, KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_ENT,
        SFT_MSE, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, QUT_SFT,
        ADJUST,  TD_ADJ,  KC_LGUI, KC_LALT, LOWER,   SPC_RSE, SPC_RSE, RAISE,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
    ),

    [_LINUX_NAV_1] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, L_F_WRD, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, A_SHIFT, S_SHIFT, _______, L_NAV_2, _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, _______,
        _______, _______, _______, _______, _______, L_B_WRD, KC_HOME, KC_END,  _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),

    [_LINUX_NAV_2] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END,  _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END
    ),

    [_QWERTY_WIN] = LAYOUT(
        QK_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSLS,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    CU_BSPC,
        CPS_CTL, A_MOUSE, KC_S,    W_NAV_1, W_F_NAV, KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_ENT,
        SFT_MSE, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, QUT_SFT,
        ADJUST,  TD_ADJ,  KC_LGUI, KC_LALT, LOWER,   SPC_RSE, SPC_RSE, RAISE,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
    ),

    [_WIN_NAV_1] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, W_F_WRD, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, A_SHIFT, S_SHIFT, _______, W_NAV_2, _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, _______,
        _______, _______, _______, _______, _______, W_B_WRD, KC_HOME, KC_END,  _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),

    [_WIN_NAV_2] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END,  _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END
    ),

    [_LOWER] = LAYOUT(
        KC_GRV,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_LBRC, KC_RBRC, _______,
        KC_CAPS, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_MINS, KC_EQL,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END
    ),

    [_RAISE] = LAYOUT(
        KC_GRV,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_LCBR, KC_RCBR, _______,
        KC_CAPS, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_UNDS, KC_PLUS,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END
    ),

    [_ADJUST] = LAYOUT(
        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
        QK_BOOT, MAC_SWT, _______, WIN_SWT, _______, _______, _______, _______, _______, _______, _______, KC_DEL,
        KC_CAPS, DF_M_P,  DF_L_P,  DF_W_P,  _______, _______, KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT, _______, _______,
        _______, DF_MAC,  DF_LNX,  DF_WIN,  DF_GMG,  _______, _______, KC_MUTE, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, KC_MPLY, KC_MPLY, _______, KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT
    ),

    [_NUM] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, KC_P7,   KC_P8,   KC_P9,   KC_PMNS, _______,
        _______, _______, _______, _______, _______, _______, _______, KC_P4,   KC_P5,   KC_P6,   KC_PPLS, _______,
        _______, _______, _______, _______, _______, _______, _______, KC_P1,   KC_P2,   KC_P3,   KC_PAST, KC_PENT,
        _______, _______, _______, _______, _______, _______, _______, KC_P0,   KC_P0,   KC_PDOT, KC_PSLS, _______,
        _______, TG_NUM,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),

    [_MOUSE] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, KC_ACL2, KC_ACL1, KC_ACL0, KC_BTN2, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, _______, _______,
        _______, _______, _______, _______, _______, _______, KC_WH_U, KC_WH_D, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, KC_BTN1, KC_BTN1, _______, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R
    ),

    [_EX_MOUSE] = LAYOUT(
        TG_MSE,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, KC_ACL2, KC_ACL1, KC_ACL0, KC_BTN2, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, XXXXXXX, XXXXXXX,
        TG_MSE,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_WH_U, KC_WH_D, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_BTN1, KC_BTN1, XXXXXXX, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R
    ),

};
// clang-format on
