/* Copyright 2019 Angelo Gazzola (nglgzz)
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

#define ___ KC_NO
#define LAYOUT( \
  K00, K01, K02, K03, K04, K05,     K06, K07, K08, K09, K0A, K0B, \
  K10, K11, K12, K13, K14, K15,     K16, K17, K18, K19, K1A, K1B, \
  K20, K21, K22, K23, K24, K25,     K26, K27, K28, K29, K2A, K2B, \
                 K33, K34, K35,     K36, K37, K38 \
) { \
  { K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B }, \
  { K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B }, \
  { K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B }, \
  { ___, ___, ___, K33, K34, K35, K36, K37, K38, ___, ___, ___ } \
}

// MOD_KC
#define CTL_ESC MT(MOD_LCTL, KC_ESCAPE)
#define CTL_ENT MT(MOD_LCTL, KC_ENTER)
#define ALT_Z   MT(MOD_LALT, KC_Z)
#define ALT_SLS MT(MOD_LALT, KC_SLASH)
#define SU_QUOT MT(MOD_LGUI, KC_QUOTE)
#define SU_BSLS MT(MOD_LGUI, KC_BSLS)
#define SFT_DEL MT(MOD_LSFT, KC_DELETE)

// LAYER_KC
#define L3_SPC  LT(3, KC_SPC)
#define L2_SPC  LT(2, KC_SPC)
#define L1_LBRC LT(1, KC_LBRC)
#define L1_RBRC LT(1, KC_RBRC)


#define _______ KC_TRNS
#define TAPPING_TERM 100
