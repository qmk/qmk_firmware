/* Copyright 2019 @ninjonas
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
#include "quantum.h"
#include "version.h"
#include "eeprom.h"
#include "process_records.h"

#ifdef TAP_DANCE_ENABLE
  #include "tap_dances.h"
#endif
#if defined(KEYBOARD_lily58_rev1) & defined(PROTOCOL_LUFA)
  #include "lufa.h"
  #include "split_util.h"
#endif

#define _QWERTY 0
#define _DVORAK 1
#define _COLEMAK 2
#define _LOWER 3
#define _RAISE 4
#define _ADJUST 5

// Shortcut Keys
#define K_LOCK LGUI(LCTL(KC_Q)) // Locks screen on MacOS
#define K_CSCN LGUI(LCTL(LSFT(KC_4))) // Copy a portion of the screen to the clipboard
#define K_MDSH LSFT(LALT(KC_MINS))
#define K_LAPP SGUI(KC_TAB) //  + Shift + Tab
#define K_RAPP LGUI(KC_TAB) //  + Tab

// Layer Keys
#define LM_LOW MO(_LOWER)
#define LM_RAI MO(_RAISE)
#define LT_LOW LT(_LOWER, KC_ENT)
#define LT_RAI LT(_RAISE, KC_SPC)

// Layout blocks
#define _____________________QWERTY_L1______________________ T_TAB, T_Q, T_W, KC_E, KC_R, KC_T
#define _____________________QWERTY_L2______________________ T_ESC, KC_A, KC_S, KC_D, KC_F, KC_G
#define _____________________QWERTY_L3______________________ KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B

#define _____________________QWERTY_R1______________________ KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSLS
#define _____________________QWERTY_R2______________________ KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT
#define _____________________QWERTY_R3______________________ KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_EQL

#define _____________________DVORAK_L1______________________ T_TAB, KC_QUOT, KC_COMM, KC_DOT, KC_P, KC_Y
#define _____________________DVORAK_L2______________________ T_ESC, KC_A, KC_O, KC_E, KC_U, KC_I
#define _____________________DVORAK_L3______________________ KC_LSFT, KC_SCLN, T_Q, KC_J, KC_K, KC_X

#define _____________________DVORAK_R1______________________ KC_F, KC_G, KC_C, KC_R, KC_L, KC_BSLS
#define _____________________DVORAK_R2______________________ KC_D, KC_H, KC_T, KC_N, KC_S, KC_SLSH
#define _____________________DVORAK_R3______________________ KC_B, KC_M, T_W, KC_V, KC_Z, KC_EQL

#define _____________________COLEMAK_L1_____________________ T_TAB, T_Q, T_W, KC_F, KC_P, KC_G
#define _____________________COLEMAK_L2_____________________ T_ESC, KC_A, KC_R, KC_S, KC_T, KC_D
#define _____________________COLEMAK_L3_____________________ KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B

#define _____________________COLEMAK_R1_____________________ KC_J, KC_L, KC_U, KC_Y, KC_SCLN, KC_BSLS
#define _____________________COLEMAK_R2_____________________ KC_H, KC_N, KC_E, KC_I, KC_O, KC_QUOT
#define _____________________COLEMAK_R3_____________________ KC_K, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_EQL

#define _____________________NUM_LEFT_______________________ T_GRV, KC_1, KC_2, KC_3, KC_4, KC_5
#define _____________________NUM_RIGHT______________________ KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS

#define _____________________FUNC_LEFT______________________ KC_F11, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5
#define _____________________FUNC_RIGHT_____________________ KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F12

#define _____________________SYM_LEFT_______________________ KC_TILD, KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC
#define _____________________SYM_RIGHT______________________ KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_UNDS

#define ____________________________________________________ _______, _______, _______, _______, _______, _______
#define _____________________XXXXXXX________________________ XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX

#define _______________NAV_1______________ KC_PGUP, KC_HOME, KC_UP, KC_END
#define _______________NAV_2______________ KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT

#define _____________MOUSE_1______________ KC_BTN1, KC_MS_U, KC_BTN2, KC_WH_D
#define _____________MOUSE_2______________ KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_U

#define __________________________________ _______, _______, _______, _______
#define _____________XXXXXXX______________ XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX

#define _________MEDIA_1_________ KC_BRIU, KC_MPLY, KC_MUTE
#define _________MEDIA_2_________ KC_BRID, KC_MFFD, KC__VOLUP
#define _________MEDIA_3_________ XXXXXXX, KC_MRWD, KC__VOLDOWN

#define ________MOD_LEFT_________ KC_LALT, T_GUI, KC_LCTL
#define ________MOD_RIGHT________ KC_BSPC, KC_DEL, LM_LOW

// Layout wrappers
#define LAYOUT_wrapper(...) LAYOUT(__VA_ARGS__)
#define LAYOUT_ergodox_wrapper(...) LAYOUT_ergodox(__VA_ARGS__)