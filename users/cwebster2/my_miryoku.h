/* Copyright 2020 Casey Webster <casey@e1337.dev>
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
#pragma once

#define _______QWERTY_L1______        KC_T,         KC_Q,         KC_W,         KC_E,         KC_R
#define _______QWERTY_L2______        KC_G,         KC_A,         KC_S,         KC_D,         KC_F
#define _______QWERTY_L3______        KC_B,         KC_Z,         KC_X,         KC_C,         KC_V
#define _______QWERTY_R1______        KC_Y,         KC_U,         KC_I,         KC_O,         KC_P
#define _______QWERTY_R2______        KC_H,         KC_J,         KC_K,         KC_L,         KC_SCLN
#define _______QWERTY_R3______        KC_N,         KC_M,         KC_COMM,      KC_DOT,       KC_SLSH

#define _______COLEMAK_L1_____        KC_Q,         KC_W,         KC_F,         KC_P,         KC_B
#define _______COLEMAK_L2_____ LGUI_T(KC_A), LALT_T(KC_R), LCTL_T(KC_S), LSFT_T(KC_T),        KC_G
#define _______COLEMAK_L3_____        KC_Z,         KC_X,         KC_C,         KC_D,         KC_V
#define _______COLEMAK_R1_____        KC_J,         KC_L,         KC_U,         KC_Y,         KC_QUOT
#define _______COLEMAK_R2_____        KC_M,  LSFT_T(KC_N), LCTL_T(KC_E), LALT_T(KC_I), LGUI_T(KC_O)
#define _______COLEMAK_R3_____        KC_K,         KC_H,         KC_COMM,      KC_DOT,       KC_SLSH

#define _______THUMBS_L_______ LT(_MOUSE,KC_ESC), LT(_NAV,KC_SPC),  LT(_MEDIA,  KC_TAB)
#define _______THUMBS_R_______ LT(_FN,   KC_ENT), LT(_NUM,KC_BSPC), LT(_SYMBOLS,KC_DEL)

#define _______NAKED_R___T____ KC_ENT,   KC_BSPC,  KC_DEL
#define _______NAKED_L___T____ KC_ESC,   KC_SPC,   KC_TAB

#define _______INACTIVE_R1____ KC_LOCK,  KC_TRNS,  KC_TRNS,  KC_TRNS,  RESET
#define _______INACTIVE_R2____ KC_TRNS,  KC_LSFT,  KC_LCTL,  KC_LALT,  KC_LGUI
#define _______INACTIVE_R3____ KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_RALT,  KC_TRNS

#define _______INACTIVE_L1____ KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_LOCK
#define _______INACTIVE_L2____ KC_LGUI,  KC_LALT,  KC_LCTL,  KC_LSFT,  KC_TRNS
#define _______INACTIVE_L3____ KC_TRNS,  KC_RALT,  KC_LEFT,  KC_RGHT,  KC_TRNS

#define _______INACTIVE__T____ KC_TRNS,  KC_TRNS,  KC_TRNS


#define _______SYM______L1____ KC_RCBR,  KC_AMPR,  KC_ASTR,  KC_LPRN,  KC_LCBR
#define _______SYM______L2____ KC_COLN,  KC_DLR,   KC_PERC,  KC_CIRC,  KC_PLUS
#define _______SYM______L3____ KC_TILD,  KC_EXLM,  KC_AT,    KC_HASH,  KC_PIPE
#define _______SYM_______T____ KC_LPRN,  KC_RPRN,  KC_UNDS

#define _______NUM______L1____ KC_RBRC,  KC_7,  KC_8,  KC_9,  KC_LBRC
#define _______NUM______L2____ KC_SCLN,  KC_4,  KC_5,  KC_6,  KC_EQL
#define _______NUM______L3____ KC_GRV,   KC_1,  KC_2,  KC_3,  KC_BSLS
#define _______NUM_______T____ KC_DOT,   KC_0,  KC_MINS

#define _______FN_______L1____ KC_F12,   KC_F7,   KC_F8,  KC_F9,  KC_SYSREQ
#define _______FN_______L2____ KC_F11,   KC_F4,   KC_F5,  KC_F6,  KC_TRNS
#define _______FN_______L3____ KC_F10,   KC_F1,   KC_F2,  KC_F3,  KC_PAUSE
#define _______FN________T____ KC_MENU,  KC_SPC,  KC_TAB

#define _______NAV______R1____ KC_UNDO,  KC_CUT,   KC_COPY,  KC_PSTE,  KC_AGIN
#define _______NAV______R2____ KC_LEFT,  KC_DOWN,  KC_UP,    KC_RGHT,  KC_CAPS
#define _______NAV______R3____ KC_HOME,  KC_PGDN,  KC_PGUP,  KC_END,  KC_INS
#define _______NAV_______T____ KC_ENT,   KC_BSPC,  KC_DEL

#define _______MEDIA____R1____ RGB_TOG,  RGB_MOD,  RGB_HUI,  RGB_SAI,  RGB_VAI
#define _______MEDIA____R2____ KC_MPRV,  KC_VOLD,  KC_VOLU,  KC_MNXT,  KC_TRNS
#define _______MEDIA____R3____ KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS
#define _______MEDIA_____T____ KC_MSTP,  KC_MPLY,  KC_MUTE

#define _______MOUSE____R1____ KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS
#define _______MOUSE____R2____ KC_MS_L,  KC_MS_D,  KC_MS_U,  KC_MS_R,  KC_TRNS
#define _______MOUSE____R3____ KC_WH_L,  KC_WH_D,  KC_WH_U,  KC_WH_R,  KC_TRNS
#define _______MOUSE_____T____ KC_BTN1,  KC_BTN3,  KC_BTN2
