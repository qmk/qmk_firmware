/* Copyright 2021 Quentin LEBASTARD <qlebastard@gmail.com>
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
// clang-format off

/* based on miryoku */

#define __________________MBO_L1___________________ RESET,   U_NA,    U_NA,    U_NA,    U_NA
#define __________________MBO_L2___________________ KC_LGUI, KC_LALT, KC_LSFT, KC_LCTL, U_NA
#define __________________MBO_L3___________________ KC_BTN3, KC_ALGR, KC_BTN2, KC_BTN1, U_NA
#define __________________MBO_L4___________________ U_NA,    U_NA,    U_NA

#define __________________MBO_R1___________________ U_RDO,   U_PST,   U_CPY,   U_CUT,   U_UND
#define __________________MBO_R2___________________ KC_CAPS, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
#define __________________MBO_R3___________________ KC_INS,  KC_HOME, KC_PGDN, KC_PGUP, KC_END
#define __________________MBO_R4___________________ KC_ENT,  KC_DEL, KC_DEL

#define __________________MEDIA_L1_________________ __________________MBO_L1___________________
#define __________________MEDIA_L2_________________ __________________MBO_L2___________________
#define __________________MEDIA_L3_________________ U_NA,    KC_ALGR, U_NA,    U_NA,    U_NA
#define __________________MEDIA_L4_________________ __________________MBO_L4___________________

#define __________________MEDIA_R1_________________ __________________MBO_R1___________________
#define __________________MEDIA_R2_________________ U_NU,    KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R
#define __________________MEDIA_R3_________________ U_NU,    KC_WH_L, KC_WH_D, KC_WH_U, KC_WH_R
#define __________________MEDIA_R4_________________ KC_BTN1, KC_BTN3, KC_BTN2

#define __________________NAV_L1___________________ __________________MBO_L1___________________
#define __________________NAV_L2___________________ __________________MBO_L2___________________
#define __________________NAV_L3___________________ __________________MEDIA_L3_________________
#define __________________NAV_L4___________________ __________________MBO_L4___________________

#define __________________NAV_R1___________________ RGB_TOG, RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI
#define __________________NAV_R2___________________ U_NU,    KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT
#define __________________NAV_R3___________________ U_NU,    U_NU,    U_NU,    U_NU,    U_NU
#define __________________NAV_R4___________________ KC_MSTP, KC_MPLY, KC_MUTE

#define _________________MOUSE_L1__________________ __________________MBO_R1___________________
#define _________________MOUSE_L2__________________ DPI_CONFIG, DRAG_SCROLL, KC_LSFT, KC_LCTL, KC_TRNS
#define _________________MOUSE_L3__________________ U_RDO,   SNIPER,  U_CPY,   U_CUT,   U_UND
#define _________________MOUSE_L4__________________ KC_BTN2, KC_BTN1, KC_BTN3

#define _________________MOUSE_R1__________________ __________________MBO_R1___________________
#define _________________MOUSE_R2__________________ KC_TRNS, KC_LCTL, KC_LSFT, DRAG_SCROLL, KC_LGUI
#define _________________MOUSE_R3__________________ KC_TRNS, KC_LCTL, KC_LSFT, DRAG_SCROLL, KC_LGUI
#define _________________MOUSE_R4__________________ KC_BTN1, KC_BTN3, KC_BTN2

#define _________________SYM_L1____________________ KC_LBRC, KC_7,    KC_8,    KC_9,    KC_RBRC
#define _________________SYM_L2____________________ KC_SCLN, KC_4,    KC_5,    KC_6,    KC_EQL
#define _________________SYM_L3____________________ KC_GRV,  KC_1,    KC_2,    KC_3,    KC_BSLS
#define _________________SYM_L4____________________ KC_DOT,  KC_0,    KC_MINS

#define _________________SYM_R1____________________ U_NA,    U_NA,    U_NA,    U_NA,    RESET
#define _________________SYM_R2____________________ U_NA,    KC_LCTL, KC_LSFT, KC_LALT, KC_LGUI
#define _________________SYM_R3____________________ U_NA,    U_NA,    U_NA,    KC_ALGR, U_NA
#define _________________SYM_R4____________________ U_NA,    U_NA,    U_NA

#define _________________NUM_L1____________________ KC_LCBR, KC_AMPR, KC_ASTR, KC_LPRN, KC_RCBR
#define _________________NUM_L2____________________ KC_COLN, KC_DLR,  KC_PERC, KC_CIRC, KC_PLUS
#define _________________NUM_L3____________________ KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_PIPE
#define _________________NUM_L4____________________ KC_LPRN, KC_RPRN, KC_UNDS

#define _________________NUM_R1____________________ _________________SYM_R1____________________
#define _________________NUM_R2____________________ _________________SYM_R2____________________
#define _________________NUM_R3____________________ _________________SYM_R3____________________
#define _________________NUM_R4____________________ _________________SYM_R4____________________

#define _________________FUN_L1____________________ KC_F12,  KC_F7,   KC_F8,   KC_F9,   KC_PSCR
#define _________________FUN_L2____________________ KC_F11,  KC_F4,   KC_F5,   KC_F6,   KC_SLCK
#define _________________FUN_L3____________________ KC_F10,  KC_F1,   KC_F2,   KC_F3,   KC_PAUS
#define _________________FUN_L4____________________ KC_APP,  KC_SPC,  KC_TAB

#define _________________FUN_R1____________________ U_NA,    U_NA,    U_NA,    U_NA,    RESET
#define _________________FUN_R2____________________ U_NA,    KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI
#define _________________FUN_R3____________________ U_NA,    U_NA,    U_NA,    KC_ALGR, U_NA
#define _________________FUN_R4____________________ U_NA,    U_NA,    U_NA

#define _MBO \
	__________________MBO_L1___________________, __________________MBO_R1___________________, \
	__________________MBO_L2___________________, __________________MBO_R2___________________, \
	__________________MBO_L3___________________, __________________MBO_R3___________________, \
	__________________MBO_L4___________________, __________________MBO_R4___________________

#define _MEDIA \
    __________________MEDIA_L1_________________, __________________MEDIA_R1_________________, \
    __________________MEDIA_L2_________________, __________________MEDIA_R2_________________, \
    __________________MEDIA_L3_________________, __________________MEDIA_R3_________________, \
    __________________MEDIA_L4_________________, __________________MEDIA_R4_________________
    
#define _NAV  \
    __________________NAV_L1___________________, __________________NAV_R1___________________, \
    __________________NAV_L2___________________, __________________NAV_R2___________________, \
    __________________NAV_L3___________________, __________________NAV_R3___________________, \
    __________________NAV_L4___________________, __________________NAV_R4___________________

#define _MOUSE \
    _________________MOUSE_L1__________________, _________________MOUSE_R1__________________, \
    _________________MOUSE_L2__________________, _________________MOUSE_R2__________________, \
    _________________MOUSE_L3__________________, _________________MOUSE_R3__________________, \
    _________________MOUSE_L4__________________, _________________MOUSE_R4__________________

#define _SYM \
    _________________SYM_L1____________________, _________________SYM_R1____________________, \
    _________________SYM_L2____________________, _________________SYM_R2____________________, \
    _________________SYM_L3____________________, _________________SYM_R3____________________, \
    _________________SYM_L4____________________, _________________SYM_R4____________________

#define _NUM \
    _________________NUM_L1____________________, _________________NUM_R1____________________, \
    _________________NUM_L2____________________, _________________NUM_R2____________________, \
    _________________NUM_L3____________________, _________________NUM_R3____________________, \
    _________________NUM_L4____________________, _________________NUM_R4____________________

#define _FUN  \
    _________________FUN_L1____________________, _________________FUN_R1____________________, \
    _________________FUN_L2____________________, _________________FUN_R2____________________, \
    _________________FUN_L3____________________, _________________FUN_R3____________________, \
    _________________FUN_L4____________________, _________________FUN_R4____________________

// clang-format on