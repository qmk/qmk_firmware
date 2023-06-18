/* Copyright 2021 3araht
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

//  Uncomment below if a pedal used for Open/Close is normally-on type (such as Yamaha's.)
// #define PEDAL_NORMALLY_CLOSED

#ifdef PEDAL_NORMALLY_CLOSED
#   define MO_SWAP  MO(_OPEN)
#   define DF_SWAP  DF(_CLOSE)
#   define TG_SWAP  TG(_OPEN)
#else
#   define MO_SWAP  MO(_CLOSE)
#   define DF_SWAP  DF(_OPEN)
#   define TG_SWAP  TG(_CLOSE)
#endif

// Long press: go to _FN layer, tap: MUTE
#define FN_MUTE  LT(_FN, KC_MUTE)
#define DF_QWER  DF(_QWERTY)
#define DF_COLE  DF(_COLEMAK)
#define MIS_EIS  LT(_MISC,KC_LNG2)
#define MIS_KAN  LT(_MISC,KC_LNG1)

#define _________________QWERTY_L1_________________ KC_Q,    KC_W,    KC_E,    KC_R,    KC_T
#define _________________QWERTY_L2_________________ KC_A,    KC_S,    KC_D,    KC_F,    KC_G
#define _________________QWERTY_L3_________________ KC_Z,    KC_X,    KC_C,    KC_V,    KC_B

#define _________________QWERTY_R1_________________ KC_Y,    KC_U,    KC_I,    KC_O,    KC_P
#define _________________QWERTY_R2_________________ KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN
#define _________________QWERTY_R3_________________ KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH

#define _________________COLEMAK_L1________________ KC_Q,    KC_W,    KC_F,    KC_P,    KC_G
#define _________________COLEMAK_L2________________ KC_A,    KC_R,    KC_S,    KC_T,    KC_D
#define _________________COLEMAK_L3________________ KC_Z,    KC_X,    KC_C,    KC_V,    KC_B

#define _________________COLEMAK_R1________________ KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN
#define _________________COLEMAK_R2________________ KC_H,    KC_N,    KC_E,    KC_I,    KC_O
#define _________________COLEMAK_R3________________ KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH

#define _________________NUMBER_L__________________ KC_1,    KC_2,    KC_3,    KC_4,    KC_5
// #define _________________NUMBER_R__________________ KC_6,    KC_7,    KC_8,    KC_9,    KC_0

#define _________________FUNC__L___________________ KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5
// #define _________________FUNC__R___________________ KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10

//  define which MIDI ch to use.
//  Note that (actual MIDI ch# - 1) -> 0 .. 15 is used for coding.
//  ch1
#define DEFAULT_SUB_CH_NUMBER  0
//  ch2
#define ALT_SUB_CH_NUMBER      1

enum custom_keycodes {
    VERSION = QK_KB,
    TGLCHGR,  //  ToGgLe CH GRoup

   // MY tone to distinguish the notes to avoid sustain effect, etc.
   // Since the # of codes exceeds the limit of QK_KB range (=64), these are stated here.
    MY_TONE_MIN  = QK_USER,

    MY_C = MY_TONE_MIN,
    MY_Cs,
    MY_Db = MY_Cs,
    MY_D,
    MY_Ds,
    MY_Eb = MY_Ds,
    MY_E,
    MY_F,
    MY_Fs,
    MY_Gb = MY_Fs,
    MY_G,
    MY_Gs,
    MY_Ab = MY_Gs,
    MY_A,
    MY_As,
    MY_Bb = MY_As,
    MY_B,

    MY_C1,
    MY_Cs1,
    MY_Db1 = MY_Cs1,
    MY_D1,
    MY_Ds1,
    MY_Eb1 = MY_Ds1,
    MY_E1,
    MY_F1,
    MY_Fs1,
    MY_Gb1 = MY_Fs1,
    MY_G1,
    MY_Gs1,
    MY_Ab1 = MY_Gs1,
    MY_A1,
    MY_As1,
    MY_Bb1 = MY_As1,
    MY_B1,

    MY_C2,
    MY_Cs2,
    MY_Db2 = MY_Cs2,
    MY_D2,
    MY_Ds2,
    MY_Eb2 = MY_Ds2,
    MY_E2,
    MY_F2,
    MY_Fs2,
    MY_Gb2 = MY_Fs2,
    MY_G2,
    MY_Gs2,
    MY_Ab2 = MY_Gs2,
    MY_A2,
    MY_As2,
    MY_Bb2 = MY_As2,
    MY_B2,

    MY_C3,
    MY_Cs3,
    MY_Db3 = MY_Cs3,
    MY_D3,
    MY_Ds3,
    MY_Eb3 = MY_Ds3,
    MY_E3,
    MY_F3,
    MY_Fs3,
    MY_Gb3 = MY_Fs3,
    MY_G3,
    MY_Gs3,
    MY_Ab3 = MY_Gs3,
    MY_A3,
    MY_As3,
    MY_Bb3 = MY_As3,
    MY_B3,

    MY_C4,
    MY_Cs4,
    MY_Db4 = MY_Cs4,
    MY_D4,
    MY_Ds4,
    MY_Eb4 = MY_Ds4,
    MY_E4,
    MY_F4,
    MY_Fs4,
    MY_Gb4 = MY_Fs4,
    MY_G4,
    MY_Gs4,
    MY_Ab4 = MY_Gs4,
    MY_A4,
    MY_As4,
    MY_Bb4 = MY_As4,
    MY_B4,

    MY_C5,
    MY_Cs5,
    MY_Db5 = MY_Cs5,
    MY_D5,
    MY_Ds5,
    MY_Eb5 = MY_Ds5,
    MY_E5,
    MY_F5,
    MY_Fs5,
    MY_Gb5 = MY_Fs5,
    MY_G5,
    MY_Gs5,
    MY_Ab5 = MY_Gs5,
    MY_A5,
    MY_As5,
    MY_Bb5 = MY_As5,
    MY_B5,

    MY_C6,
    MY_TONE_MAX = MY_C6
};

#define MY_TONE_COUNT (MY_TONE_MAX - MY_TONE_MIN + 1)

void my_process_midi4single_note(uint8_t channel, uint16_t keycode, keyrecord_t *record, uint8_t *my_tone_status);

//  Overriding is_keyboard_left() in qmk_firmware/quantum/split_common/split_util.c to limit the handedness check only once.
//  reason: bandoMIneDonI has no space on right hand side to use "SPLIT_HAND_MATRIX_GRID".
//          However, It enables to decide the handedness by the HW by adding one condition: "not to press any keys (especially r30) dusing startup."
bool is_keyboard_left(void);

#ifdef MIDI_ENABLE
extern MidiDevice midi_device;
#endif  //  MIDI_ENABLE
