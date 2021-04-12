/* Copyright 2021 datafx
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

#define LAYOUT_all( \
	K000, K001, K002, K003, K004, K005, K006, K007, K008, K009, K010, K011, K012, K013, K014, K015, \
	K100, K101, K102, K103, K104, K105, K106, K107, K108, K109, K110, K111, K112, K113, K114, K115, \
	K200, K201, K202, K203, K204, K205, K206, K207, K208, K209, K210, K211, K212, K213, K214, K215, \
	K300, K301, K302, K303, K304, K305, K306, K307, K308, K309, K310, K311, K312, K313,             \
	K400, K401, K402, K403, K404, K405, K406, K407, K408, K409, K410, K411, K412, K413, K414, K415, \
	K500, K501, K502,             K505, K506,             K509, K510, K511, K512, K513, K514, K515  \
) { \
	{ K000,  K001,  K002,  K003,  K004,  K005,  K006,  K007,  K008,  K009,  K010,  K011,  K012,  K013,  K014,  K015 }, \
	{ K100,  K101,  K102,  K103,  K104,  K105,  K106,  K107,  K108,  K109,  K110,  K111,  K112,  K113,  K114,  K115 }, \
	{ K200,  K201,  K202,  K203,  K204,  K205,  K206,  K207,  K208,  K209,  K210,  K211,  K212,  K213,  K214,  K215 }, \
	{ K300,  K301,  K302,  K303,  K304,  K305,  K306,  K307,  K308,  K309,  K310,  K311,  K312,  K313,  KC_NO, KC_NO }, \
	{ K400,  K401,  K402,  K403,  K404,  K405,  K406,  K407,  K408,  K409,  K410,  K411,  K412,  K413,  K414,  K415 }, \
	{ K500,  K501,  K502,  KC_NO, KC_NO, K505,  K506,  KC_NO, KC_NO, K509,  K510,  K511,  K512,  K513,  K514,  K515 }  \
}

#define u8 uint8_t
#define u16 uint16_t

#pragma once

#include "quantum.h"

#define KEYLED_ROWS 6
#define KEYLED_COLS 16

#define XaxisMax 18
#define YaxisMax 6

#define RhythmLedColumMax 18

typedef struct{
	u8 onf;
	u8 hightLevel;
	u8 ColumHeight[RhythmLedColumMax];
}

RhythmLed_;

typedef struct{
	u8 r,g,b;
}

rgb_;
#define colorAGSize 10
#define colorBGSize RGBLED_NUM-10

typedef struct{
	rgb_ colorAG[colorAGSize];
    rgb_ colorBG[RGBLED_NUM-10];
}

backLedRgbG_;

#define Lseg0 E5
#define Lseg1 B4
#define Lseg2 B5
#define Lseg3 F0
#define Lseg4 C6
#define Lseg5 D5

#define Lcom0 C4
#define Lcom1 C2
#define Lcom2 C0
#define Lcom3 E0
#define Lcom4 D4
#define Lcom5 E4
#define Lcom6 B6
#define Lcom7 B2
#define Lcom8 F4
#define Lcom9 A0
#define Lcom10 F2
#define Lcom11 A4
#define Lcom12 F1
#define Lcom13 A7
#define Lcom14 D3
#define Lcom15 A3

extern void keyLedDriver(void);
extern void KeyLedCom(void);
u8 getKeyLedIndexForXY(u8 x,u8 y);

extern void ledCapsSet(bool onf);
extern void ledNumSet(bool onf);
extern void ledSollSet(bool onf);
void reflashLedState(void);
