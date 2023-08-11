/*
Copyright 2023 Joe Scotto
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include QMK_KEYBOARD_H

#ifdef TAP_DANCE_ENABLE
    #include "tap_dance.h"
#endif

// Assign rows of keycodes to a single def each 
#define __QWERTY1__       KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P
#define __QWERTY2__       KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_BSPC
#define __QWERTY3a_       LSFT_T(KC_Z), KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, RSFT_T(KC_SLSH)
#define __QWERTY3b_       KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH

#define __COLEMAK1__      KC_Q, KC_W, KC_F, KC_P, KC_G, KC_J, KC_L, KC_U, KC_Y, KC_BSPC
#define __COLEMAK2__      KC_A, KC_R, KC_S, KC_T, KC_D, KC_H, KC_N, KC_E, KC_I, KC_O
#define __COLEMAK3a_      LSFT_T(KC_Z), KC_X, KC_C, KC_V, KC_B, KC_K, KC_M, KC_COMM, KC_DOT, RSFT_T(KC_SLSH)
#define __COLEMAK3b_      KC_Z, KC_X, KC_C, KC_V, KC_B, KC_K, KC_M, KC_COMM, KC_DOT, KC_SLSH

#define ______________SYM_MEDIA_NAV1______________      KC_UNDS, KC_MINS, KC_PLUS, KC_EQL,  KC_COLN, KC_GRV, KC_MRWD, KC_MPLY, KC_MFFD, KC_DEL
#define ______________SYM_MEDIA_NAV2______________      KC_LCBR, KC_LPRN, KC_RPRN, KC_RCBR, KC_PIPE, KC_ESC, KC_LEFT, KC_UP, KC_DOWN, KC_RGHT
#define ______________SYM_MEDIA_NAV3______________      LSFT_T(KC_LBRC), KC_QUOT, KC_DQUO, KC_RBRC, KC_SCLN, KC_TILD, KC_VOLD, KC_MUTE, KC_VOLU, RSFT_T(KC_BSLS)

#define _________________NUM_SYM1_________________      KC_EXLM, KC_AT, KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_CAPS, KC_BSPC
#define _________________NUM_SYM2_________________      KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0
#define _________________NUM_SYM3a________________      KC_LSFT, KC_NO, KC_NO, KC_NO, MO(3), KC_NO, KC_NO, KC_COMM, KC_DOT, RSFT_T(KC_SLSH)
#define _________________NUM_SYM3b________________      KC_LSFT, KC_NO, KC_NO, KC_NO, MO(8), KC_NO, KC_NO, KC_COMM, KC_DOT, RSFT_T(KC_SLSH)

#define ________________FUNC_SYS1a________________      KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, TO(5), TO(4)
#define ________________FUNC_SYS1b________________      KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, TO(4), TO(5), TO(0)
#define ________________FUNC_SYS2_________________      KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10
#define ________________FUNC_SYS3_________________      KC_F11, KC_NO, KC_NO, QK_BOOT, KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_F12

#define _______THUMB6_1_______      TD(TD_LCTL_ESC_SPOTLIGHT_EMOJI), KC_LALT, LGUI_T(KC_SPC), LT(1, KC_TAB), LT(2, KC_ENT), TD(TD_LCTL_ESC_SPOTLIGHT_EMOJI)
#define _______THUMB6_4_______      TD(TD_LALT_ESC_WINDOWS_EMOJI), KC_LALT, LCTL_T(KC_SPC), LT(6, KC_TAB), LT(7, KC_ENT), TD(TD_LALT_ESC_WINDOWS_EMOJI)
#define _______THUMB6_5_______      TD(TD_LALT_ESC_WINDOWS_EMOJI), KC_LCTL, KC_SPC, LT(6, KC_TAB), LT(7, KC_ENT), TD(TD_LALT_ESC_WINDOWS_EMOJI)
#define _____THUMB6_TRNS______      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS

#define _______THUMB4_1_______      TD(TD_ESC_LALT_LCTL_SPOTLIGHT_EMOJI), LGUI_T(KC_SPC), LT(1, KC_TAB), LT(2, KC_ENT)
#define _______THUMB4_4_______      TD(TD_ESC_LCTL_LALT_WINDOWS_EMOJI), LCTL_T(KC_SPC), LT(6, KC_TAB), LT(7, KC_ENT)
#define _______THUMB4_5_______      KC_LCTL, KC_SPC, LT(6, KC_TAB), LT(7, KC_ENT)
#define _____THUMB4_TRNS______      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS

// set functional layout
#if defined (KEYMAP_QWERTY)
    #define _________________KEYMAP1__________________ __QWERTY1__
    #define _________________KEYMAP2__________________ __QWERTY2__
    #define _________________KEYMAP3a_________________ __QWERTY3a_
    #define _________________KEYMAP3b_________________ __QWERTY3b_
#else
    #define _________________KEYMAP1__________________ __COLEMAK1__
    #define _________________KEYMAP2__________________ __COLEMAK2__
    #define _________________KEYMAP3a_________________ __COLEMAK3a_
    #define _________________KEYMAP3b_________________ __COLEMAK3b_
#endif
