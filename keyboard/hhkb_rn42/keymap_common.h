/*
Copyright 2012,2013 Jun Wako <wakojun@gmail.com>

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

#include <stdint.h>
#include <stdbool.h>
#include "keycode.h"
#include "action.h"
#include "action_code.h"
#include "action_layer.h"
#include "action_macro.h"
#include "action_util.h"
#include "report.h"
#include "host.h"
#include "print.h"
#include "debug.h"
#include "keymap.h"


extern const uint8_t keymaps[][MATRIX_ROWS][MATRIX_COLS];
extern const uint16_t fn_actions[];


#define KEYMAP( \
    K31, K30, K00, K10, K11, K20, K21, K40, K41, K60, K61, K70, K71, K50, K51, \
    K32, K01, K02, K13, K12, K23, K22, K42, K43, K62, K63, K73, K72, K52, \
    K33, K04, K03, K14, K15, K24, K25, K45, K44, K65, K64, K74, K53, \
    K34, K05, K06, K07, K16, K17, K26, K46, K66, K76, K75, K55, K54, \
         K35, K36,           K37,                K57, K56 \
) \
{ \
    { KC_##K00, KC_##K01, KC_##K02, KC_##K03, KC_##K04, KC_##K05, KC_##K06, KC_##K07 }, \
    { KC_##K10, KC_##K11, KC_##K12, KC_##K13, KC_##K14, KC_##K15, KC_##K16, KC_##K17 }, \
    { KC_##K20, KC_##K21, KC_##K22, KC_##K23, KC_##K24, KC_##K25, KC_##K26, KC_NO    }, \
    { KC_##K30, KC_##K31, KC_##K32, KC_##K33, KC_##K34, KC_##K35, KC_##K36, KC_##K37 }, \
    { KC_##K40, KC_##K41, KC_##K42, KC_##K43, KC_##K44, KC_##K45, KC_##K46, KC_NO    }, \
    { KC_##K50, KC_##K51, KC_##K52, KC_##K53, KC_##K54, KC_##K55, KC_##K56, KC_##K57 }, \
    { KC_##K60, KC_##K61, KC_##K62, KC_##K63, KC_##K64, KC_##K65, KC_##K66, KC_NO    }, \
    { KC_##K70, KC_##K71, KC_##K72, KC_##K73, KC_##K74, KC_##K75, KC_##K76, KC_NO    } \
}


#define KEYMAP_JP( \
    K02, K32, K62, K22, K12, K52, K72, KA2, K92, K82, KB2, KE2, KF2, KD2, KC2, \
    K03, K63, K23, K13, K53, K73, KA3, K93, K83, KB3, KE3, KF3, KD3, \
    K06, K66, K26, K16, K56, K76, KA6, K96, K86, KB6, KE6, KF6, KD6, KC6, \
    K05, K65, K25, K15, K55, K75, KA5, K95, K85, KB5, KE5, KF5, KD5, KC5, \
    K04, K34, K64, K24, K14,      K74,      K94, K84, KB4, KE4, KF4, KD4, KC4 \
) \
{ \
    { KC_NO,    KC_NO,    KC_##K02, KC_##K03, KC_##K04, KC_##K05, KC_##K06, KC_NO    }, \
    { KC_NO,    KC_NO,    KC_##K12, KC_##K13, KC_##K14, KC_##K15, KC_##K16, KC_NO    }, \
    { KC_NO,    KC_NO,    KC_##K22, KC_##K23, KC_##K24, KC_##K25, KC_##K26, KC_NO    }, \
    { KC_NO,    KC_NO,    KC_##K32, KC_NO,    KC_##K34, KC_NO,    KC_NO,    KC_NO    }, \
    { KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO    }, \
    { KC_NO,    KC_NO,    KC_##K52, KC_##K53, KC_NO,    KC_##K55, KC_##K56, KC_NO    }, \
    { KC_NO,    KC_NO,    KC_##K62, KC_##K63, KC_##K64, KC_##K65, KC_##K66, KC_NO    }, \
    { KC_NO,    KC_NO,    KC_##K72, KC_##K73, KC_##K74, KC_##K75, KC_##K76, KC_NO    }, \
    { KC_NO,    KC_NO,    KC_##K82, KC_##K83, KC_##K84, KC_##K85, KC_##K86, KC_NO    }, \
    { KC_NO,    KC_NO,    KC_##K92, KC_##K93, KC_##K94, KC_##K95, KC_##K96, KC_NO    }, \
    { KC_NO,    KC_NO,    KC_##KA2, KC_##KA3, KC_NO,    KC_##KA5, KC_##KA6, KC_NO    }, \
    { KC_NO,    KC_NO,    KC_##KB2, KC_##KB3, KC_##KB4, KC_##KB5, KC_##KB6, KC_NO    }, \
    { KC_NO,    KC_NO,    KC_##KC2, KC_NO,    KC_##KC4, KC_##KC5, KC_##KC6, KC_NO    }, \
    { KC_NO,    KC_NO,    KC_##KD2, KC_##KD3, KC_##KD4, KC_##KD5, KC_##KD6, KC_NO    }, \
    { KC_NO,    KC_NO,    KC_##KE2, KC_##KE3, KC_##KE4, KC_##KE5, KC_##KE6, KC_NO    }, \
    { KC_NO,    KC_NO,    KC_##KF2, KC_##KF3, KC_##KF4, KC_##KF5, KC_##KF6, KC_NO    }  \
}

#endif
