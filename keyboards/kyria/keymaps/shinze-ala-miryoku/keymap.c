/* Copyright 2020 Gaëtan Ark <gaetan.ark@gmail.com>
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
#include "keymap_bepo.h"

#define U_RDO SCMD(KC_Z)
#define U_PST LCMD(KC_V)
#define U_CPY LCMD(KC_C)
#define U_CUT LCMD(KC_X)
#define U_UND LCMD(KC_Z)

// Row 1
// Left
#define S00 KC_NO
#define S01 BP_B
#define S02 BP_E_ACUTE
#define S03 BP_P
#define S04 BP_O
#define S05 BP_E_GRAVE
// Right
#define S06 BP_DCRC
#define S07 BP_V
#define S08 BP_D
#define S09 BP_L
#define S10 BP_J
#define S11 BP_Z

// Row 2
// Left
#define S12 BP_W                     // TODO : See how I can insert FN_T(BP_W) ? Need it ?
#define S13 LCTL_T(BP_A)
#define S14 LALT_T(BP_U)
#define S15 GUI_T(BP_I)
#define S16 LSFT(BP_E)
#define S17 BP_COMMA
// Right
#define S18 BP_C
#define S19 RSFT(BP_T)
#define S20 GUI_T(BP_S)
#define S21 RALT_T(BP_R)
#define S22 RCTL_T(BP_N)
#define S23 BP_M

// Row 3
#define S24 KC_NO
#define S25 BP_A_GRAVE
#define S26 BP_Y                     // NOTE : LCTL_T(BP_Y) in Original layout
#define S27 BP_X
#define S28 BP_DOT
#define S29 BP_K
#define S30 KC_NO                      // Top outer key
#define S31 KC_NO                      // Top outer key
#define S32 KC_NO                      // Top outer key
#define S33 KC_NO                      // Top outer key
#define S34 BP_APOSTROPHE
#define S35 BP_Q
#define S36 BP_G
#define S37 BP_H
#define S38 BP_F
#define S39 BP_CCED

// Row 4
#define B00 KC_NO
#define B01 LT(MEDR, KC_ESC)
#define B02 LT(NAVR, KC_SPC)
#define B03 LT(MOUR, KC_TAB)
#define B04 KC_NO
#define B05 KC_NO
#define B06 LT(NSSL, KC_ENT)
#define B07 LT(NSL, KC_BSPC)
#define B08 LT(FUNL, KC_DEL)
#define B09 KC_NO

// NAVR
// Row1
// Left
#define T00 KC_NO
#define T01 RSFT
#define T02 KC_NO
#define T03 KC_NO
#define T04 KC_NO
#define T05 KC_NO

// Right
#define T06 U_RDO
#define T07 U_PST
#define T08 U_CPY
#define T09 U_CUT
#define T10 U_UND
#define T11 KC_NO

// Row 2
// Left
#define T12 KC_NO
#define T13 KC_LCTL
#define T14 KC_LALT
#define T15 KC_LGUI
#define T16 LSFT
#define T17 KC_NO

// Right
#define T18 KC_LEFT
#define T19 KC_DOWN
#define T20 KC_UP
#define T21 KC_RGHT
#define T22 KC_CAPS
#define T23 KC_NO

// Row 3
// Left
#define T24 KC_NO
#define T25 KC_LALT
#define T26 KC_NO
#define T28 KC_NO
#define T29 KC_NO
#define T30 KC_NO
// Right
#define T31 KC_NO
#define T32 KC_NO
#define T33 KC_HOME
#define T34 KC_PGDN
#define T35 KC_PGUP
#define T36 KC_END
#define T37 KC_INS
#define T38 KC_NO

// Row 4
#define C00 KC_NO
#define C01 KC_NO
#define C02 KC_NO
#define C03 KC_NO
#define C04 KC_NO
#define C05 KC_NO
#define C06 KC_ENT
#define C07 KC_BSPC
#define C08 KC_DEL
#define C09 KC_NO


enum layers { BASE, MBO, MEDR, NAVR, MOUR, NSSL, NSL, FUNL };

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [BASE] = LAYOUT(
      S00, S01, S02, S03, S04, S05,                         S06, S07, S08, S09, S10, S11,
      S12, S13, S14, S15, S16, S17,                         S18, S19, S20, S21, S22, S23,
      S24, S25, S26, S27, S28, S29, S30, S31,     S32, S33, S34, S35, S36, S37, S38, S39,
                     B00, B01, B02, B03, B04,     B05, B06, B07, B08, B09
    ),

    [NAVR] = LAYOUT(
      T00, T01, T02, T03, T04, T05,                         T06, T07, T08, T09, T10, T11,
      T12, T13, T14, T15, T16, T17,                         T18, T19, T20, T21, T22, T23,
      T24, T25, T26, T27, T28, T29, T30, T31,     T32, T33, T34, T35, T36, T37, T38, T39,
                     C00, C01, C02, C03, C04,     C05, C06, C07, C08, C09
    ),

    [MOUR] = LAYOUT(
      S00, S01, S02, S03, S04, S05,                         S06, S07, S08, S09, S10, S11,
      S12, S13, S14, S15, S16, S17,                         S18, S19, S20, S21, S22, S23,
      S24, S25, S26, S27, S28, S29, S30, S31,     S32, S33, S34, S35, S36, S37, S38, S39,
                     B00, B01, B02, B03, B04,     B05, B06, B07, B08, B09
    ),

    [MBO] = LAYOUT(
      S00, S01, S02, S03, S04, S05,                         S06, S07, S08, S09, S10, S11,
      S12, S13, S14, S15, S16, S17,                         S18, S19, S20, S21, S22, S23,
      S24, S25, S26, S27, S28, S29, S30, S31,     S32, S33, S34, S35, S36, S37, S38, S39,
                     B00, B01, B02, B03, B04,     B05, B06, B07, B08, B09
    ),

    [MEDR] = LAYOUT(
      S00, S01, S02, S03, S04, S05,                         S06, S07, S08, S09, S10, S11,
      S12, S13, S14, S15, S16, S17,                         S18, S19, S20, S21, S22, S23,
      S24, S25, S26, S27, S28, S29, S30, S31,     S32, S33, S34, S35, S36, S37, S38, S39,
                     B00, B01, B02, B03, B04,     B05, B06, B07, B08, B09
    ),

    [NSSL] = LAYOUT(
      S00, S01, S02, S03, S04, S05,                         S06, S07, S08, S09, S10, S11,
      S12, S13, S14, S15, S16, S17,                         S18, S19, S20, S21, S22, S23,
      S24, S25, S26, S27, S28, S29, S30, S31,     S32, S33, S34, S35, S36, S37, S38, S39,
                     B00, B01, B02, B03, B04,     B05, B06, B07, B08, B09
    ),

    [NSL] = LAYOUT(
      S00, S01, S02, S03, S04, S05,                         S06, S07, S08, S09, S10, S11,
      S12, S13, S14, S15, S16, S17,                         S18, S19, S20, S21, S22, S23,
      S24, S25, S26, S27, S28, S29, S30, S31,     S32, S33, S34, S35, S36, S37, S38, S39,
                     B00, B01, B02, B03, B04,     B05, B06, B07, B08, B09
    ),

    [FUNL] = LAYOUT(
      S00, S01, S02, S03, S04, S05,                         S06, S07, S08, S09, S10, S11,
      S12, S13, S14, S15, S16, S17,                         S18, S19, S20, S21, S22, S23,
      S24, S25, S26, S27, S28, S29, S30, S31,     S32, S33, S34, S35, S36, S37, S38, S39,
                     B00, B01, B02, B03, B04,     B05, B06, B07, B08, B09
    ),
};
