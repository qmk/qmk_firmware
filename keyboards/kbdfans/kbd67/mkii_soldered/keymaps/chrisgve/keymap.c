/* Copyright 2019 Ryota Goto
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

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY_MAC] = LAYOUT_65_ansi_blocker_split_bs( 
	KC_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSLS, KC_DEL,  KC_HOME,
	KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,          KC_BSPC, KC_PGUP,
	CPS_CTL, KC_A,    KC_S,    M_NAV_1, KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,           KC_PGDN,
	SFT_MSE,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, R_SHIFT,          KC_UP,   END_F_M,
	KC_LCTL, KC_LALT, KC_LGUI,                            SPC_RSE,                            KC_RGUI, KC_RALT,          KC_LEFT, KC_DOWN, KC_RGHT
  ),

  [_MAC_NAV_1] = LAYOUT_65_ansi_blocker_split_bs( 
	_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
	_______, _______, M_F_WRD, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______,
	_______, A_SHIFT, S_SHIFT, _______, M_NAV_2, _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, _______,          _______,          _______,
	_______,          _______, _______, _______, M_B_WRD, KC_HOME, KC_END,  _______, _______, _______, _______, _______,          _______, _______,
	_______, _______, _______,                            _______,                            _______, _______,          _______, _______, _______
  ),

  [_MAC_NAV_2] = LAYOUT_65_ansi_blocker_split_bs( 
	_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
	_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______,
	_______, _______, _______, _______, _______, _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END,  _______, _______,          _______,          _______,
	_______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______,
	_______, _______, _______,                            _______,                            _______, _______,          _______, _______, _______
  ),

  [_QWERTY_LINUX] = LAYOUT_65_ansi_blocker_split_bs( 
	KC_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSLS, KC_DEL,  KC_HOME,
	KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,          KC_BSPC, KC_PGUP,
	CPS_CTL, KC_A,    KC_S,    L_NAV_1, KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,           KC_PGDN,
	SFT_MSE,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, R_SHIFT,          KC_UP,   END_F_L,
	KC_LCTL, KC_LGUI, KC_LALT,                            SPC_RSE,                            KC_RALT, KC_RGUI,          KC_LEFT, KC_DOWN, KC_RGHT
  ),

  [_LINUX_NAV_1] = LAYOUT_65_ansi_blocker_split_bs( 
	_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
	_______, _______, L_F_WRD, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______,
	_______, A_SHIFT, S_SHIFT, _______, L_NAV_2, _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, _______,          _______,          _______,
	_______,          _______, _______, _______, L_B_WRD, KC_HOME, KC_END,  _______, _______, _______, _______, _______,          _______, _______,
	_______, _______, _______,                            _______,                            _______, _______,          _______, _______, _______
  ),

  [_LINUX_NAV_2] = LAYOUT_65_ansi_blocker_split_bs( 
	_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
	_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______,
	_______, _______, _______, _______, _______, _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END,  _______, _______,          _______,          _______,
	_______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______,
	_______, _______, _______,                            _______,                            _______, _______,          _______, _______, _______
  ),

  [_QWERTY_WIN] = LAYOUT_65_ansi_blocker_split_bs( 
	KC_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSLS, KC_DEL,  KC_HOME,
	KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,          KC_BSPC, KC_PGUP,
	CPS_CTL, KC_A,    KC_S,    W_NAV_1, KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,           KC_PGDN,
	SFT_MSE,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, R_SHIFT,          KC_UP,   END_F_W,
	KC_LCTL, KC_LGUI, KC_LALT,                            SPC_RSE,                            KC_RALT, KC_RGUI,          KC_LEFT, KC_DOWN, KC_RGHT
  ),

  [_WIN_NAV_1] = LAYOUT_65_ansi_blocker_split_bs( 
	_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, W_F_WRD, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______,
    _______, A_SHIFT, S_SHIFT, _______, W_NAV_2, _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, _______,          _______,          _______,
	_______,          _______, _______, _______, W_B_WRD, KC_HOME, KC_END,  _______, _______, _______, _______, _______,          _______, _______,
	_______, _______, _______,                            _______,                            _______, _______,          _______, _______, _______
  ),

  [_WIN_NAV_2] = LAYOUT_65_ansi_blocker_split_bs( 
	_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
	_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______,
	_______, _______, _______, _______, _______, _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END,  _______, _______,          _______,          _______,
	_______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______,
	_______, _______, _______,                            _______,                            _______, _______,          _______, _______, _______
  ),

  [_RAISE] = LAYOUT_65_ansi_blocker_split_bs( 
	_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
	_______, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_UNDS, KC_PLUS,          _______, _______,
	KC_CAPS, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,          KC_EQL,           _______,
	_______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______,
	_______, _______, _______,                            _______,                            _______, _______,          _______, _______, _______
  ),

  [_ADJUST_MAC] = LAYOUT_65_ansi_blocker_split_bs( 
	KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, _______, _______,
	RESET,   MAC_SWT, _______, WIN_SWT, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______,
	_______, DF_M_P,  DF_L_P,  DF_W_P,  _______, _______, KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT, _______, _______,          _______,          _______,
	_______,          DF_MAC,  DF_LNX,  DF_WIN,  _______, _______, _______, KC_MUTE, _______, _______, _______, KC_APFN,          KC_VOLU, _______,
	_______, _______, _______,                            KC_MPLY,                            _______, _______,          KC_MPRV, KC_VOLD, KC_MNXT
  ),

  [_ADJUST_LINUX] = LAYOUT_65_ansi_blocker_split_bs( 
	KC_GRV,  KC_WF1,  KC_WF2,  KC_WF3,  KC_WF4,  KC_WF5,  KC_WF6,  KC_WF7,  KC_WF8,  KC_WF9,  KC_WF10, KC_WF11, KC_WF12, _______, _______, _______,
	RESET,   MAC_SWT, _______, WIN_SWT, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______,
	_______, DF_M_P,  DF_L_P,  DF_W_P,  _______, _______, KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT, _______, _______,          _______,          _______,
	_______,          DF_MAC,  DF_LNX,  DF_WIN,  _______, _______, _______, KC_MUTE, _______, _______, _______, INV_AFN,          KC_VOLU, _______,
	_______, _______, _______,                            KC_MPLY,                            _______, _______,          KC_MPRV, KC_VOLD, KC_MNXT
  ),

  [_ADJUST_WIN] = LAYOUT_65_ansi_blocker_split_bs( 
	KC_GRV,  KC_WF1,  KC_WF2,  KC_WF3,  KC_WF4,  KC_WF5,  KC_WF6,  KC_WF7,  KC_WF8,  KC_WF9,  KC_WF10, KC_WF11, KC_WF12, _______, _______, _______,
	RESET,   MAC_SWT, _______, WIN_SWT, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______,
	_______, DF_M_P,  DF_L_P,  DF_W_P,  _______, _______, KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT, _______, _______,          _______,          _______,
	_______,          DF_MAC,  DF_LNX,  DF_WIN,  _______, _______, _______, KC_MUTE, _______, _______, _______, INV_AFN,          KC_VOLU, _______,
	_______, _______, _______,                            KC_MPLY,                            _______, _______,          KC_MPRV, KC_VOLD, KC_MNXT
  ),

  [_MOUSE] = LAYOUT_65_ansi_blocker_split_bs( 
	TG_MSE,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
	_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______,
	_______, _______, KC_ACL2, KC_ACL1, KC_ACL0, KC_BTN2, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, _______, _______,          _______,          _______,
	TG_MSE,           _______, _______, _______, _______, KC_WH_U, KC_WH_D, _______, _______, _______, _______, _______,          _______, _______,
	_______, _______, _______,                            KC_BTN1,                            _______, _______,          _______, _______, _______
  ),

};
