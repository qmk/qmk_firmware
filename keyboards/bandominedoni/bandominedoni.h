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
#define MIS_EIS  LT(_MISC,KC_LNG2)
#define MIS_KAN  LT(_MISC,KC_LNG1)


//  Overriding is_keyboard_left() in qmk_firmware/quantum/split_common/split_util.c to limit the handedness check only once.
//  reason: bandoMIneDonI has no space on right hand side to use "SPLIT_HAND_MATRIX_GRID".
//          However, It enables to decide the handedness by the HW by adding one condition: "not to press any keys (especially r30) dusing startup."
bool is_keyboard_left(void);

