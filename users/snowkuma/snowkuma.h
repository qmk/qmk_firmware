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

enum layers {
  _COLEMAK = 0,
  _NAV,
  _SYMBOL,
  _NUMBER,
  _ARRANGE
};

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
#define ESC_NUM LT(_NUMBER, KC_ESC)
#define TAB_SFT LSFT_T(KC_TAB)
#define MIN_ARR LT(_ARRANGE, KC_MINS)

// magnet keycodes
#define M_LEFT LCA(KC_LEFT)
#define M_TOP LCA(KC_UP)
#define M_BOTT LCA(KC_DOWN)
#define M_RGHT LCA(KC_RGHT)

#define M_TOPL LCA(KC_U)
#define M_TOPR LCA(KC_I)
#define M_BOTL LCA(KC_J)
#define M_BOTR LCA(KC_K)

#define M_L13 LCA(KC_D)
#define M_L23 LCA(KC_E)
#define M_C13 LCA(KC_F)
#define M_R23 LCA(KC_T)
#define M_R13 LCA(KC_G)

#define M_1_6 LCA(KC_1)
#define M_2_6 LCA(KC_2)
#define M_3_6 LCA(KC_3)
#define M_4_6 LCA(KC_4)
#define M_5_6 LCA(KC_5)
#define M_6_6 LCA(KC_6)
#define M_L_56 LCA(KC_COMM)
#define M_R_56 LCA(KC_DOT)

#define M_NEXT LCAG(KC_RGHT)
#define M_PREV LCAG(KC_LEFT)

#define M_MAX LCA(KC_ENT)
#define M_CEN LCA(KC_C)
#define M_REST LCA(KC_BSPC)

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


#define _________________NUM_L1____________________        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
#define _________________NUM_L2____________________        KC_COLN, KC_HASH, XXXXXXX, XXXXXXX, XXXXXXX
#define _________________NUM_L3____________________        KC_COMM, KC_PLUS, KC_MINS, KC_EQL,  XXXXXXX

#define _________________NUM_R1____________________        KC_SLSH, KC_7,    KC_8,    KC_9,    KC_ASTR
#define _________________NUM_R2____________________        KC_DOT,  KC_4,    KC_5,    KC_6,    KC_MINS
#define _________________NUM_R3____________________        KC_COMM, KC_1,    KC_2,    KC_3,    KC_PLUS
#define ________NUM_R4___________                          KC_BSLS, KC_0,    KC_EQL


#define _________________ARR_L1____________________        M_1_6,   M_2_6,   M_MAX,   M_5_6,   M_6_6
#define _________________ARR_L2____________________        M_L13,   M_L23,   M_C13,   M_R23,   M_R13
#define _________________ARR_L3____________________        M_L_56,  M_3_6,   M_REST,  M_4_6,   M_R_56

#define _________________ARR_R1____________________        XXXXXXX, M_TOPL,  M_TOP,   M_TOPR,  XXXXXXX
#define _________________ARR_R2____________________        M_PREV,  M_LEFT,  M_BOTT,  M_RGHT,  M_NEXT
#define _________________ARR_R3____________________        XXXXXXX, M_BOTL,  M_CEN,   M_BOTR,  XXXXXXX


#define ________MOD_LEFT_________ ESC_NUM, BSP_SYM, TAB_SFT 
#define ________MOD_RIGHT________ MIN_ARR, SPC_NAV, KC_ENT

#define _________MEDIA_1_________ KC_BRIU, KC_MPLY, KC_MUTE
#define _________MEDIA_2_________ KC_BRID, KC_MFFD, KC__VOLUP
#define _________MEDIA_3_________ XXXXXXX, KC_MRWD, KC__VOLDOWN

// Layout wrappers
#define LAYOUT_wrapper(...) LAYOUT(__VA_ARGS__)
#define LAYOUT_ergodox_wrapper(...) LAYOUT_ergodox(__VA_ARGS__)