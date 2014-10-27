/*
Copyright 2011,2012,2013 Jun Wako <wakojun@gmail.com>

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
#include <avr/pgmspace.h>
#include "keycode.h"
#include "action.h"
#include "action_macro.h"
#include "report.h"
#include "print.h"
#include "debug.h"
#include "keymap.h"


// 32*8(256) byte array which converts PS/2 code into USB code
extern const uint8_t keymaps[][MATRIX_ROWS][MATRIX_COLS];
extern const uint16_t fn_actions[];


/* 77, 107-key From Ellipse@Deskthority
 * http://deskthority.net/workshop-f7/tmk-keyboard-firmware-collection-t4478-90.html#p190550

 * 77-key
    K00,K18,K19,K1A,K10,K11,K12,K08,K09,K0A,K0F,K1F,K0D,K0C,K0E,    K44,K45,K46, \
    K04,K05,K06,K13,K14,K15,K16,K17,K01,K02,K03,K1B,K1C,K1D,        K54,K55,K56, \
    K20,K21,K22,K23,K24,K25,K26,K27,K28,K29,K2A,K2B,K2C,K2D,        K64,K65,K66, \
    K30,K3E,K32,K33,K34,K35,K36,K37,K38,K39,K3A,K3B,K3C,K3D,        K74,K75,K76, \
    K31,K41,K3F,        K40,                    K42,K2F,            K77,K67,K71 \

 * 107-key
    K00,K18,    K19,K1A,K10,K11,K12,K08,K09,K0A,K0F,K1F,K0D,K0C,K0E,K46,K64,    NO, K6B,K6C,    K47,K48,K49,K4A, \
    K04,K05,    K06,K13,K14,K15,K16,K17,K01,K02,K03,K1B,K1C,K1D,K56,K66,        K6D,K6E,K6F,    K4B,K4C,K4D,K4E, \
    K20,K21,    K22,K23,K24,K25,K26,K27,K28,K29,K2A,K2B,K2C,K2D,K71,K77,        K70,K65,K72,    K50,K51,K52,K53, \
    K30,        K3E,K32,K33,K34,K35,K36,K37,K38,K39,K3A,K3B,K3C,K3D,K44,        K74,K75,K76,    K5E,K58,K59,K5A, \
    K31,K41,    K3F,K40,K42,        K2F,                    K54,K55,            K78,K67,K79,    K5B,K5C,K5D,K57 \

 * IBM4704 scancode 00-79h
    { KC_##K00, KC_##K01, KC_##K02, KC_##K03, KC_##K04, KC_##K05, KC_##K06, KC_NO    }, \
    { KC_##K08, KC_##K09, KC_##K0A, KC_NO,    KC_##K0C, KC_##K0D, KC_##K0E, KC_##K0F }, \
    { KC_##K10, KC_##K11, KC_##K12, KC_##K13, KC_##K14, KC_##K15, KC_##K16, KC_##K17 }, \
    { KC_##K18, KC_##K19, KC_##K1A, KC_##K1B, KC_##K1C, KC_##K1D, KC_NO,    KC_##K1F }, \
    { KC_##K20, KC_##K21, KC_##K22, KC_##K23, KC_##K24, KC_##K25, KC_##K26, KC_##K27 }, \
    { KC_##K28, KC_##K29, KC_##K2A, KC_##K2B, KC_##K2C, KC_##K2D, KC_NO,    KC_##K2F }, \
    { KC_##K30, KC_##K31, KC_##K32, KC_##K33, KC_##K34, KC_##K35, KC_##K36, KC_##K37 }, \
    { KC_##K38, KC_##K39, KC_##K3A, KC_##K3B, KC_##K3C, KC_##K3D, KC_##K3E, KC_##K3F }, \
    { KC_##K40, KC_##K41, KC_##K42, KC_NO,    KC_##K44, KC_NO,    KC_##K46, KC_##K47 }, \
    { KC_##K48, KC_##K49, KC_##K4A, KC_##K4B, KC_##K4C, KC_##K4D, KC_##K4E, KC_NO    }, \
    { KC_##K50, KC_##K51, KC_##K52, KC_##K53, KC_##K54, KC_##K55, KC_##K56, KC_##K57 }, \
    { KC_##K58, KC_##K59, KC_##K5A, KC_##K5B, KC_##K5C, KC_##K5D, KC_##K5E, KC_NO    }, \
    { KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_##K64, KC_##K65, KC_##K66, KC_##K67 }, \
    { KC_NO,    KC_NO,    KC_NO,    KC_##K6B, KC_##K6C, KC_##K6D, KC_##K6E, KC_##K6F }, \
    { KC_##K70, KC_##K71, KC_##K72, KC_NO,    KC_##K74, KC_##K75, KC_##K76, KC_##K77 }, \
    { KC_##K78, KC_##K79, KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO    }, 
*/
/* 62-key */
#define KEYMAP( \
    K00,K18,K19,K1A,K10,K11,K12,K08,K09,K0A,K0F,K1F,K0D,K0C,K0E, \
    K04,K05,K06,K13,K14,K15,K16,K17,K01,K02,K03,K1B,K1C,K1D, \
    K20,K21,K22,K23,K24,K25,K26,K27,K28,K29,K2A,K2B,K2C,K2D, \
    K30,K3E,K32,K33,K34,K35,K36,K37,K38,K39,K3A,K3B,K3C,K3D, \
    K31,K41,K3F,        K40,                    K42,K2F \
) { \
    { KC_##K00, KC_##K01, KC_##K02, KC_##K03, KC_##K04, KC_##K05, KC_##K06, KC_NO }, \
    { KC_##K08, KC_##K09, KC_##K0A, KC_NO,    KC_##K0C, KC_##K0D, KC_##K0E, KC_##K0F }, \
    { KC_##K10, KC_##K11, KC_##K12, KC_##K13, KC_##K14, KC_##K15, KC_##K16, KC_##K17 }, \
    { KC_##K18, KC_##K19, KC_##K1A, KC_##K1B, KC_##K1C, KC_##K1D, KC_NO,    KC_##K1F }, \
    { KC_##K20, KC_##K21, KC_##K22, KC_##K23, KC_##K24, KC_##K25, KC_##K26, KC_##K27 }, \
    { KC_##K28, KC_##K29, KC_##K2A, KC_##K2B, KC_##K2C, KC_##K2D, KC_NO,    KC_##K2F }, \
    { KC_##K30, KC_##K31, KC_##K32, KC_##K33, KC_##K34, KC_##K35, KC_##K36, KC_##K37 }, \
    { KC_##K38, KC_##K39, KC_##K3A, KC_##K3B, KC_##K3C, KC_##K3D, KC_##K3E, KC_##K3F }, \
    { KC_##K40, KC_##K41, KC_##K42, KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO }, \
    { KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO }, \
    { KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO }, \
    { KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO }, \
    { KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO }, \
    { KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO }, \
    { KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO }, \
    { KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO }, \
}

#endif
