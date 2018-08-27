/*
Copyright 2017 Luiz Ribeiro <luizribeiro@gmail.com>

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

#ifndef KEYMAP_COMMON_H
#define KEYMAP_COMMON_H

#include "quantum.h"
#include "quantum_keycodes.h"
#include "keycode.h"
#include "action.h"

void matrix_init_user(void);  // TODO port this to other PS2AVRGB boards

#define KEYMAP_GRID( \
    K01, K02, K03, K04, K05, K06, K07, K08, K09, K010, K011, K012, \
    K11, K12, K13, K14, K15, K16, K17, K18, K19, K110, K111, K112, \
    K21, K22, K23, K24, K25, K26, K27, K28, K29, K210, K211, K212, \
    K31, K32, K33, K34, K35, K36, K37, K38, K39, K310, K311, K312  \
) \
{ \
  { K012, K011, K010, K09, K05, K06, K07, K08, K04, K03, K02, K01 }, \
  { K112, K111, K110, K19, K15, K16, K17, K18, K14, K13, K12, K11 }, \
  { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
  { K212, K211, K210, K29, K25, K26, K27, K28, K24, K23, K22, K21 }, \
  { K312, K311, K310, K39, K35, K36, K37, K38, K34, K33, K32, K31 }  \
}

#define KEYMAP_MIT( \
    K01, K02, K03, K04, K05, K06, K07, K08, K09, K010, K011, K012, \
    K11, K12, K13, K14, K15, K16, K17, K18, K19, K110, K111, K112, \
    K21, K22, K23, K24, K25, K26, K27, K28, K29, K210, K211, K212, \
    K31, K32, K33, K34, K35,    K3X,   K38, K39, K310, K311, K312  \
) \
{ \
  { K012, K011, K010, K09, K05, K06, K07,   K08, K04, K03, K02, K01 }, \
  { K112, K111, K110, K19, K15, K16, K17,   K18, K14, K13, K12, K11 }, \
  { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
  { K212, K211, K210, K29, K25, K26, K27,   K28, K24, K23, K22, K21 }, \
  { K312, K311, K310, K39, K35, K3X, KC_NO, K38, K34, K33, K32, K31 }  \
}

#define KEYMAP_OFFSET( \
    K01, K02, K03, K04, K05, K06, K07, K08, K09, K010, K011, K012, \
    K11, K12, K13, K14, K15, K16, K17, K18, K19, K110, K111, K112, \
    K21, K22, K23, K24, K25, K26, K27, K28, K29, K210, K211, K212, \
    K31, K32, K33, K34, K35, K36,    K3X,   K39, K310, K311, K312  \
) \
{ \
  { K012, K011, K010, K09, K05, K06, K07,   K08, K04, K03, K02, K01 }, \
  { K112, K111, K110, K19, K15, K16, K17,   K18, K14, K13, K12, K11 }, \
  { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
  { K212, K211, K210, K29, K25, K26, K27,   K28, K24, K23, K22, K21 }, \
  { K312, K311, K310, K39, K35, K36, K3X, KC_NO, K34, K33, K32, K31 }  \
}

#define KC_KEYMAP( \
	k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, \
	k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, \
	k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, \
	k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b \
	) \
	KEYMAP_GRID( \
		KC_##k00, KC_##k01, KC_##k02, KC_##k03, KC_##k04, KC_##k05, KC_##k06, KC_##k07, KC_##k08, KC_##k09, KC_##k0a, KC_##k0b, \
		KC_##k10, KC_##k11, KC_##k12, KC_##k13, KC_##k14, KC_##k15, KC_##k16, KC_##k17, KC_##k18, KC_##k19, KC_##k1a, KC_##k1b, \
		KC_##k20, KC_##k21, KC_##k22, KC_##k23, KC_##k24, KC_##k25, KC_##k26, KC_##k27, KC_##k28, KC_##k29, KC_##k2a, KC_##k2b, \
		KC_##k30, KC_##k31, KC_##k32, KC_##k33, KC_##k34, KC_##k35, KC_##k36, KC_##k37, KC_##k38, KC_##k39, KC_##k3a, KC_##k3b \
    )


#define KEYMAP KEYMAP_MIT

#define LAYOUT_ortho_4x12 KEYMAP_GRID

#define LAYOUT_2U_space KEYMAP_MIT
#define LAYOUT_planck_mit KEYMAP_MIT

#define KC_LAYOUT_ortho_4x12 KC_KEYMAP
#define LAYOUT_kc_ortho_4x12 KC_KEYMAP

#endif
