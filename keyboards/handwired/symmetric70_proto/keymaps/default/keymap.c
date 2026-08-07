/* Copyright 2020 mtei
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

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _BASE,
    _FN
};

#define KC_FUNC MO(_FN)

// clang-format off

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [_BASE] = LAYOUT(
     //_ESC_1_2_3_4_5_NO              _NO_6_7_8_9_0_BSPC
     //_TAB_Q_W_E_R_T_MINS            _EQL_Y_U_I_O_P_BSLS
     //_LCTL_A_S_D_F_G_LBRC           _RBRC_H_J_K_L_SCLN_RCTL
     //_LSFT_Z_X_C_V_B_GRV_NO         _NO_QUOT_N_M_COMM_DOT_SLSH_RSFT
     //_FUNC_CAPS_LALT_LGUI_SPC_BSPC  _ENT_SPC_RGUI_RALT_APP_FUNC
      KC_ESC,  KC_1, KC_2, KC_3, KC_4, KC_5, KC_NO,                 KC_NO,   KC_6, KC_7, KC_8,    KC_9,   KC_0,    KC_BSPC,
       KC_TAB,  KC_Q, KC_W, KC_E, KC_R, KC_T, KC_MINS,             KC_EQL,  KC_Y, KC_U, KC_I,    KC_O,   KC_P,    KC_BSLS,
      KC_LCTL, KC_A, KC_S, KC_D, KC_F, KC_G, KC_LBRC,               KC_RBRC, KC_H, KC_J, KC_K,    KC_L,   KC_SCLN, KC_RCTL,
     KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_GRV, KC_NO,   KC_NO,  KC_QUOT, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT,
     KC_FUNC,    KC_CAPS, KC_LALT, KC_LGUI, KC_SPC, KC_BSPC, KC_ENT,   KC_SPC,  KC_RGUI, KC_RALT,  KC_APP,          KC_FUNC
    ),
    [_FN] = LAYOUT(
     //_NO_F1_F2_F3_F4_F5_NO                   _NO_F6_F7_F8_F9_F10_F11
     //_NO_NO_PAUS_SLCK_NO_NO_NO               _NO_NO_NO_SLCK_PAUS_NO_F12
     //_TRNS_HOME_NO_UP_NO_PGUP_INS            _INS_PGUP_NO_UP_NO_HOME_TRNS
     //_TRNS_END_LEFT_DOWN_RGHT_PGDN_DEL_TRNS  _TRNS_DEL_PGDN_LEFT_DOWN_RGHT_END_TRNS
     //_TRNS_PSCR_TRNS_TRNS_NO_NO              _NO_NO_TRNS_TRNS_PSCR_TRNS
       KC_NO, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_NO,               KC_NO,  KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
       KC_NO, KC_NO,   KC_PAUS, KC_SCRL, KC_NO,   KC_NO,   KC_NO,               KC_NO,  KC_NO,   KC_NO,   KC_SCRL, KC_PAUS, KC_NO,   KC_F12,
     _______, KC_HOME, KC_NO,   KC_UP,   KC_NO,   KC_PGUP, KC_INS,              KC_INS, KC_PGUP, KC_NO,   KC_UP,   KC_NO,   KC_HOME, _______,
     _______, KC_END,  KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, KC_DEL, KC_NO,KC_NO, KC_DEL, KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_END,  _______,
     _______,          KC_PSCR, _______, _______, KC_NO,           KC_NO,KC_NO,         KC_NO,   _______, _______, KC_PSCR,          _______
    )
};
