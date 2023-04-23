#pragma once
/*
  Copyright 2018 Eric Gebhart <e.a.gebhart@gmail.com>

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


// Kyria
#ifdef KEYBOARD_splitkb_kyria
#define BASE Base_2x6_8_5
#define BASEt6 Base_2x6_8_5t6
#define TRANS Transient_2x6_8_5
#define BASE_COLS_IN_OUT 5_6 // 5, 5_6, 6
#endif

// Corne
#ifdef KEYBOARD_crkbd
#define BASE Base_3x6_3
#define BASEt6 Base_3x6_3t6
#define TRANS Transient_3x6_3
#define BASE_COLS_IN_OUT 5_6 // 5, 5_6, 6
#endif

// Ergodox ez.
#ifdef KEYBOARD_ergodox_ez
#define BASE Base_dox
#define BASEt6 Base_doxt6
#define TRANS Transient_dox
#define BASE_COLS_IN_OUT 5_6 // 5, 5_6, 6
// tell the keymap we want to specify number rows.
// 4x10 input instead 3x10.
#define BASE_NUMBER_ROW    // turn on 4 row base templates.
#endif

// XD75
#ifdef KEYBOARD_xiudi_xd75
#define BASE Base_5x15
#define BASEt6 Base_5x15t6
#define TRANS Transient_5x15
#define BASE_COLS_IN_OUT 5_6 // 5, 5_6, 6

// tell the keymap we want to specify number rows.
// 4x10 input instead 3x10.
#define BASE_NUMBER_ROW    // turn on 4 row base templates.
#endif

// Viterbi
#ifdef KEYBOARD_keebio_viterbi
#define BASE Base_5x14
#define BASEt6 Base_5x14t6
#define TRANS Transient_5x14
#define BASE_COLS_IN_OUT 5_6 // 5, 5_6, 6

// tell the keymap we want to specify number rows.
// 4x10 input instead 3x10.
#define BASE_NUMBER_ROW    // turn on 4 row base templates.
#endif

// Rebound
#ifdef KEYBOARD_montsinger_rebound
#define BASE Base_rebound
#define BASEt6 Base_reboundt6
#define TRANS Rebound_transient
#define BASE_COLS_IN_OUT 5_6 // 5, 5_6, 6
#endif

// Kinesis
#if defined(KEYBOARD_kinesis_alvicstep)         \
  || defined(KEYBOARD_kinesis_stapelberg)       \
  || defined(KEYBOARD_kinesis_kint2pp)          \
  || defined(KEYBOARD_kinesis_nguyenvietyen)    \
  || defined(KEYBOARD_kinesis_kint36)           \
  || defined(KEYBOARD_kinesis_kint41)           \
  || defined(KEYBOARD_kinesis_kintlc)

#undef LAYOUT_PVARG
#define LAYOUT_PVARG(...)     LAYOUT_pretty(__VA_ARGS__)
// Base layers 4x10, so numbers are enabled, and a 3x10 for the keymap.
// Transient function layers are all 3x10.
#define BASE Base_4x6_4_6
#define BASEt6 Base_4x6_4_6t6
#define TRANS Transient_4x6_4_6
#define BASE_COLS_IN_OUT 5_6 // 5, 5_6, 6

// tell the keymap we want to specify number rows.
// 4x10 input instead 3x10.
#define BASE_NUMBER_ROW    // turn on 4 row base templates.
#endif

// My Morpho Dactyl
#ifdef KEYBOARD_gebhart_morpho
#undef LAYOUT_PVARG
#define LAYOUT_PVARG(...)  LAYOUT_split_4x6_5_8(__VA_ARGS__)

#define BASE Base_4x6_5_8
#define BASEt6 Base_4x6_5_8t6
#define TRANS Transient_4x6_5_8
#define BASE_COLS_IN_OUT 5_6 // 5, 5_6, 6

// tell the keymap we want to specify number rows.
// 4x10 input instead 3x10.
#define BASE_NUMBER_ROW    // turn on 4 row base templates.
#endif
