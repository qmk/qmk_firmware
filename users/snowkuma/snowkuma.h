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

#define _COLEMAK 0
#define _NAV 1
#define _SYMBOL 2

// Shortcut Keys
#define K_LOCK LGUI(LCTL(KC_Q)) // Locks screen on MacOS
#define K_CSCN LGUI(LCTL(LSFT(KC_4))) // Copy a portion of the screen to the clipboard
#define K_CPRF LGUI(LSFT(KC_M)) //   + Shift + M. Used for switching Google Chrome profiles
#define K_MDSH LSFT(LALT(KC_MINS))
#define K_LAPP SGUI(KC_TAB) //  + Shift + Tab
#define K_RAPP LGUI(KC_TAB) //  + Tab

// Layer Keys
#define SPC_NAV LT(_NAV, KC_SPC)
#define BSP_SYM LT(_SYMBOL, KC_BSPC)
#define DEL_SYM LT(_SYMBOL, KC_DEL)

// Mod-Tap Keys
#define MT_DEL MT(MOD_LGUI | MOD_LALT | MOD_LSFT, KC_DEL)
#define MT_EQL MT(MOD_LALT | MOD_LSFT, KC_EQL)

// Layout blocks
#define _________________COLEMAK_L1________________        KC_Q,    KC_W,    KC_F,    KC_P,    KC_G
#define _________________COLEMAK_L2________________        KC_A,    KC_R,    KC_S,    KC_T,    KC_D
#define _________________COLEMAK_L3________________        KC_Z,    KC_X,    KC_C,    KC_V,    KC_B

#define _________________COLEMAK_R1________________        KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN
#define _________________COLEMAK_R2________________        KC_H,    KC_N,    KC_E,    KC_I,    KC_O
#define _________________COLEMAK_R3________________        KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_QUOT

#define _________________NAV_L1____________________        KC_LCTL, KC_LALT, KC_LGUI, XXXXXXX, XXXXXXX
#define _________________NAV_L2____________________        XXXXXXX, XXXXXXX, XXXXXXX, KC_LSFT, XXXXXXX
#define _________________NAV_L3____________________        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX

#define _________________NAV_R1____________________        XXXXXXX, KC_HOME, KC_UP,   KC_END,  KC_PGUP
#define _________________NAV_R2____________________        XXXXXXX, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN
#define _________________NAV_R3____________________        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX


#define _________________SYM_L1____________________        KC_EXLM, KC_AT,   KC_ASTR, KC_AMPR, KC_PIPE
#define _________________SYM_L2____________________        KC_TILD, KC_LT,   KC_PERC, KC_GT,   XXXXXXX
#define _________________SYM_L3____________________        KC_GRV,  KC_PLUS, KC_MINS, KC_EQL,  XXXXXXX

#define _________________SYM_R1____________________        XXXXXXX, KC_LBRC, KC_CIRC, KC_RBRC, KC_COLN
#define _________________SYM_R2____________________        KC_QUES, KC_LPRN, KC_DLR,  KC_RPRN, KC_SLSH
#define _________________SYM_R3____________________        KC_PIPE, KC_LCBR, KC_HASH, KC_RCBR, KC_BSLS


#define ________MOD_LEFT_________ KC_ESC,  BSP_SYM, KC_LSFT
#define ________MOD_RIGHT________ KC_MINS, SPC_NAV, KC_ENT

#define _________MEDIA_1_________ KC_BRIU, KC_MPLY, KC_MUTE
#define _________MEDIA_2_________ KC_BRID, KC_MFFD, KC__VOLUP
#define _________MEDIA_3_________ XXXXXXX, KC_MRWD, KC__VOLDOWN

// Layout wrappers
#define LAYOUT_wrapper(...) LAYOUT(__VA_ARGS__)
#define LAYOUT_ergodox_wrapper(...) LAYOUT_ergodox(__VA_ARGS__)