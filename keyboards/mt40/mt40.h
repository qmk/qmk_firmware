/* Copyright 2017 REPLACE_WITH_YOUR_NAME
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
#ifndef MT40_H
#define MT40_H

#include "quantum_keycodes.h"
#include "keycode.h"
#include "action.h"

// This a shortcut to help you visually see your layout.
// The following is an example using the Planck MIT layout
// The first section contains all of the arguments
// The second converts the arguments into a two-dimensional array
#define KEYMAP( \
    K00,  K01,  K02,  K03,  K04,  K05,  K06,  K07,  K08,  K09,  K0A,  K0B, \
    K10,  K11,  K12,  K13,  K14,  K15,  K16,  K17,  K18,  K19,  K1A,  K1B, \
    K20,  K21,  K22,  K23,  K24,  K25,  K26,  K27,  K28,  K29,  K2A,  K2B, \
    K30,  K31,  K32,  K33,  K34,  K35,  K36,  K37,  K38,  K39,  K3A,  K3B \
) { \
    { K31,   K32,   K33,   KC_NO, K34,   K35,   KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, K37,   KC_NO, KC_NO, KC_NO }, \
    { K20,   K21,   K22,   K23,   K24,   K25,   KC_NO, KC_NO, KC_NO, KC_NO, K2A,   KC_NO, KC_NO, KC_NO, KC_NO }, \
    { K30,   K11,   K12,   K13,   K14,   K15,   KC_NO, KC_NO, KC_NO, KC_NO, K1A,   K1B,   KC_NO, KC_NO, KC_NO }, \
    { K10,   K01,   K02,   K03,   K04,   K05,   KC_NO, KC_NO, KC_NO, KC_NO, K0A,   KC_NO, KC_NO, KC_NO, KC_NO }, \
    { K00,   KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, K0B   }, \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
    { KC_NO, KC_NO, K06,   K16,   K26,   K36,   K38,   K3A,   K39,   K3B,   KC_NO, KC_NO, K07,   K17,   K27   }, \
    { KC_NO, KC_NO, K09,   K19,   K29,   KC_NO, K2B,   KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, K08,   K18,   K28   }  \
}

/* #define KC_KEYMAP( \ */
/*     k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, \ */
/*     k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, \ */
/*     k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, \ */
/*     k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b \ */
/* ) \ */
/* { \ */
/*     { KC_##k31, KC_##k32, KC_##k33, KC_NO,    KC_##k34, KC_##k35, KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_##k37, KC_NO,    KC_NO,    KC_NO,    KC_NO    }, \ */
/*     { KC_##k20, KC_##k21, KC_##k22, KC_##k23, KC_##k24, KC_##k25, KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_##k2a, KC_NO,    KC_NO,    KC_NO    }, \ */
/*     { KC_##k30, KC_##k11, KC_##k12, KC_##k13, KC_##k14, KC_##k15, KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_##k1b, KC_##k1a, KC_NO,    KC_NO,    KC_NO    }, \ */
/*     { KC_##k10, KC_##k01, KC_##k02, KC_##k03, KC_##k04, KC_##k05, KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_##k0a, KC_NO,    KC_NO,    KC_NO    }, \ */
/*     { KC_##k00, KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_##k0b }, \ */
/*     { KC_NO,    KC_NO,    KC_##k06, KC_##k16, KC_##k26, KC_##k36, KC_##k38, KC_##k3a, KC_##k17, KC_##k07, KC_NO,    KC_NO,    KC_##k3b, KC_##k39, KC_##k27 }  \ */
/*     { KC_NO,    KC_NO,    KC_##k09, KC_##k19, KC_##k29, KC_NO,    KC_NO,    KC_##k2b, KC_##k18, KC_##k08, KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_##k28 }  \ */
/* } */

/* #define FR_A KC_A */
/* #define FR_B KC_B */
/* #define FR_C KC_C */
/* #define FR_D KC_D */
/* #define FR_E KC_E */
/* #define FR_F KC_F */
/* #define FR_G KC_G */
/* #define FR_H KC_H */
/* #define FR_I KC_I */
/* #define FR_J KC_J */
/* #define FR_K KC_K */
/* #define FR_L KC_L */
/* #define FR_M KC_M */
/* #define FR_N KC_N */
/* #define FR_O KC_O */
/* #define FR_P KC_P */
/* #define FR_Q KC_Q */
/* #define FR_R KC_R */
/* #define FR_S KC_S */
/* #define FR_T KC_T */
/* #define FR_U KC_U */
/* #define FR_V KC_V */
/* #define FR_W KC_W */
/* #define FR_X KC_X */
/* #define FR_Y KC_Y */
/* #define FR_Z KC_Z */


#endif
