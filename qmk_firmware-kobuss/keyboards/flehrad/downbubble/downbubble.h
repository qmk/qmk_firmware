/* Copyright 2018 REPLACE_WITH_YOUR_NAME
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

/* This a shortcut to help you visually see your layout.
 *
 * The first section contains all of the arguments representing the physical
 * layout of the board and position of the keys.
 *
 * The second converts the arguments into a two-dimensional array which
 * represents the switch matrix.
 */
#define LAYOUT_standard( \
    K00,  K01,  K02,  K03,  K04,  K05,  K06,                                       K010,  K011,  K012,  K013,  K014,  K015,  K016,  K017,  K018,  K019,\
    K10,  K11,  K12,  K13,  K14,  K15,  K16,              K17,  K18,  K19,         K110,  K111,  K112,  K113,  K114,  K115,         K116,  K118,  K119,\
    K20,  K21,  K22,  K23,  K24,  K25,              K26,  K27,  K28,               K210,  K211,  K212,  K213,  K214,  K215,  K216,  K217,  K218,  K219,\
    K30,  K31,  K32,  K33,  K34,  K35,              K36,  K37,  K38,  K29,         K310,  K311,  K312,  K313,  K314,  K315,         K317,              \
    K40,        K41,  K42,  K43,  K44,  K45,        K46,  K47,  K48,               K410,  K411,  K412,  K413,  K414,         K416,         K418,       \
    K50,  K51,  K52,  K53,        K54,              K56,        K58,  K49,         K510,         K512,  K513,  K514,  K516,         K517,  K518, K519  \
) \
{ \
    { K00,  K01,  K02,  K03,  K04,  K05,    K06,  KC_NO,  KC_NO,  KC_NO,  K010,  K011,   K012,  K013,  K014,  K015,   K016,   K017,   K018,   K019  }, \
    { K10,  K11,  K12,  K13,  K14,  K15,    K16,  K17,    K18,    K19,    K110,  K111,   K112,  K113,  K114,  K115,   K116,   KC_NO,  K118,   K119  }, \
    { K20,  K21,  K22,  K23,  K24,  K25,    K26,  K27,    K28,    K29,    K210,  K211,   K212,  K213,  K214,  K215,   K216,   K217,   K218,   K219  }, \
    { K30,  K31,  K32,  K33,  K34,  K35,    K36,  K37,    K38,    KC_NO,  K310,  K311,   K312,  K313,  K314,  K315,   KC_NO,  K317,   KC_NO,  KC_NO }, \
    { K40,  K41,  K42,  K43,  K44,  K45,    K46,  K47,    K48,    K49,    K410,  K411,   K412,  K413,  K414,  KC_NO,  K416,   KC_NO,  K418,   KC_NO }, \
    { K50,  K51,  K52,  K53,  K54,  KC_NO,  K56,  KC_NO,  K58,    KC_NO,  K510,  KC_NO,  K512,  K513,  K514,  KC_NO,  K516,   K517,   K518,   K519  }, \
         }

#define LAYOUT_split_bs( \
    K00,  K01,  K02,  K03,  K04,  K05,  K06,                                       K010,  K011,  K012,  K013,  K014,  K015,  K016,  K017,  K018,  K019,\
    K10,  K11,  K12,  K13,  K14,  K15,  K16,              K17,  K18,  K19,         K110,  K111,  K112,  K113,  K114,  K115,  K116,  K117,  K118,  K119,\
    K20,  K21,  K22,  K23,  K24,  K25,              K26,  K27,  K28,               K210,  K211,  K212,  K213,  K214,  K215,  K216,  K217,  K218,  K219,\
    K30,  K31,  K32,  K33,  K34,  K35,              K36,  K37,  K38,  K29,         K310,  K311,  K312,  K313,  K314,  K315,         K317,              \
    K40,        K41,  K42,  K43,  K44,  K45,        K46,  K47,  K48,               K410,  K411,  K412,  K413,  K414,         K416,         K418,       \
    K50,  K51,  K52,  K53,        K54,              K56,        K58,  K49,         K510,         K512,  K513,  K514,  K516,         K517,  K518,  K519 \
) \
{ \
    { K00,  K01,  K02,  K03,  K04,  K05,    K06,  KC_NO,  KC_NO,  KC_NO,  K010,  K011,   K012,  K013,  K014,  K015,   K016,   K017,   K018,   K019  }, \
    { K10,  K11,  K12,  K13,  K14,  K15,    K16,  K17,    K18,    K19,    K110,  K111,   K112,  K113,  K114,  K115,   K116,   K117,   K118,   K119  }, \
    { K20,  K21,  K22,  K23,  K24,  K25,    K26,  K27,    K28,    K29,    K210,  K211,   K212,  K213,  K214,  K215,   K216,   K217,   K218,   K219  }, \
    { K30,  K31,  K32,  K33,  K34,  K35,    K36,  K37,    K38,    KC_NO,  K310,  K311,   K312,  K313,  K314,  K315,   KC_NO,  K317,   KC_NO,  KC_NO }, \
    { K40,  K41,  K42,  K43,  K44,  K45,    K46,  K47,    K48,    K49,    K410,  K411,   K412,  K413,  K414,  KC_NO,  K416,   KC_NO,  K418,   KC_NO }, \
    { K50,  K51,  K52,  K53,  K54,  KC_NO,  K56,  KC_NO,  K58,    KC_NO,  K510,  KC_NO,  K512,  K513,  K514,  KC_NO,  K516,   K517,   K518,   K519  }, \
         }

#define LAYOUT_split_rshift( \
    K00,  K01,  K02,  K03,  K04,  K05,  K06,                                       K010,  K011,  K012,  K013,  K014,  K015,  K016,  K017,  K018,  K019,\
    K10,  K11,  K12,  K13,  K14,  K15,  K16,              K17,  K18,  K19,         K110,  K111,  K112,  K113,  K114,  K115,         K116,  K118,  K119,\
    K20,  K21,  K22,  K23,  K24,  K25,              K26,  K27,  K28,               K210,  K211,  K212,  K213,  K214,  K215,  K216,  K217,  K218,  K219,\
    K30,  K31,  K32,  K33,  K34,  K35,              K36,  K37,  K38,  K29,         K310,  K311,  K312,  K313,  K314,  K315,         K317,              \
    K40,        K41,  K42,  K43,  K44,  K45,        K46,  K47,  K48,               K410,  K411,  K412,  K413,  K414,         K416,  K417,  K418,       \
    K50,  K51,  K52,  K53,        K54,              K56,        K58,  K49,         K510,         K512,  K513,  K514,  K516,         K517,  K518,  K519 \
) \
{ \
    { K00,  K01,  K02,  K03,  K04,  K05,    K06,  KC_NO,  KC_NO,  KC_NO,  K010,  K011,   K012,  K013,  K014,  K015,   K016,   K017,   K018,   K019  }, \
    { K10,  K11,  K12,  K13,  K14,  K15,    K16,  K17,    K18,    K19,    K110,  K111,   K112,  K113,  K114,  K115,   K116,   KC_NO,  K118,   K119  }, \
    { K20,  K21,  K22,  K23,  K24,  K25,    K26,  K27,    K28,    K29,    K210,  K211,   K212,  K213,  K214,  K215,   K216,   K217,   K218,   K219  }, \
    { K30,  K31,  K32,  K33,  K34,  K35,    K36,  K37,    K38,    KC_NO,  K310,  K311,   K312,  K313,  K314,  K315,   KC_NO,  K317,   KC_NO,  KC_NO }, \
    { K40,  K41,  K42,  K43,  K44,  K45,    K46,  K47,    K48,    K49,    K410,  K411,   K412,  K413,  K414,  KC_NO,  K416,   K417,   K418,   KC_NO }, \
    { K50,  K51,  K52,  K53,  K54,  KC_NO,  K56,  KC_NO,  K58,    KC_NO,  K510,  KC_NO,  K512,  K513,  K514,  KC_NO,  K516,   K517,   K518,   K519  }, \
         }

#define LAYOUT_split_numpad( \
    K00,  K01,  K02,  K03,  K04,  K05,  K06,                                       K010,  K011,  K012,  K013,  K014,  K015,  K016,  K017,  K018,  K019,\
    K10,  K11,  K12,  K13,  K14,  K15,  K16,              K17,  K18,  K19,         K110,  K111,  K112,  K113,  K114,  K115,         K116,  K118,  K119,\
    K20,  K21,  K22,  K23,  K24,  K25,              K26,  K27,  K28,  K29,         K210,  K211,  K212,  K213,  K214,  K215,  K216,  K217,  K218,  K219,\
    K30,  K31,  K32,  K33,  K34,  K35,              K36,  K37,  K38,  K39,         K310,  K311,  K312,  K313,  K314,  K315,         K317,              \
    K40,        K41,  K42,  K43,  K44,  K45,        K46,  K47,  K48,  K49,         K410,  K411,  K412,  K413,  K414,         K416,         K418,       \
    K50,  K51,  K52,  K53,        K54,              K56,  K57,  K58,  K59,         K510,         K512,  K513,  K514,  K516,         K517,  K518,  K519 \
) \
{ \
    { K00,  K01,  K02,  K03,  K04,  K05,    K06,  KC_NO,  KC_NO,  KC_NO,  K010,  K011,   K012,  K013,  K014,  K015,   K016,   K017,   K018,   K019  }, \
    { K10,  K11,  K12,  K13,  K14,  K15,    K16,  K17,    K18,    K19,    K110,  K111,   K112,  K113,  K114,  K115,   K116,   KC_NO,  K118,   K119  }, \
    { K20,  K21,  K22,  K23,  K24,  K25,    K26,  K27,    K28,    K29,    K210,  K211,   K212,  K213,  K214,  K215,   K216,   K217,   K218,   K219  }, \
    { K30,  K31,  K32,  K33,  K34,  K35,    K36,  K37,    K38,    K39,    K310,  K311,   K312,  K313,  K314,  K315,   KC_NO,  K317,   KC_NO,  KC_NO }, \
    { K40,  K41,  K42,  K43,  K44,  K45,    K46,  K47,    K48,    K49,    K410,  K411,   K412,  K413,  K414,  KC_NO,  K416,   KC_NO,  K418,   KC_NO }, \
    { K50,  K51,  K52,  K53,  K54,  KC_NO,  K56,  K57,    K58,    K59,    K510,  KC_NO,  K512,  K513,  K514,  KC_NO,  K516,   K517,   K518,   K519  }, \
         }

#define LAYOUT_all( \
    K00,  K01,  K02,  K03,  K04,  K05,  K06,                                       K010,  K011,  K012,  K013,  K014,  K015,  K016,  K017,  K018,  K019,\
    K10,  K11,  K12,  K13,  K14,  K15,  K16,              K17,  K18,  K19,         K110,  K111,  K112,  K113,  K114,  K115,  K116,  K117,  K118,  K119,\
    K20,  K21,  K22,  K23,  K24,  K25,              K26,  K27,  K28,  K29,         K210,  K211,  K212,  K213,  K214,  K215,  K216,  K217,  K218,  K219,\
    K30,  K31,  K32,  K33,  K34,  K35,              K36,  K37,  K38,  K39,         K310,  K311,  K312,  K313,  K314,  K315,         K317,              \
    K40,        K41,  K42,  K43,  K44,  K45,        K46,  K47,  K48,  K49,         K410,  K411,  K412,  K413,  K414,         K416,  K417,  K418,       \
    K50,  K51,  K52,  K53,        K54,              K56,  K57,  K58,  K59,         K510,         K512,  K513,  K514,  K516,         K517,  K518,  K519 \
) \
{ \
    { K00,  K01,  K02,  K03,  K04,  K05,    K06,  KC_NO,  KC_NO,  KC_NO,  K010,  K011,   K012,  K013,  K014,  K015,   K016,   K017,  K018,   K019  }, \
    { K10,  K11,  K12,  K13,  K14,  K15,    K16,  K17,    K18,    K19,    K110,  K111,   K112,  K113,  K114,  K115,   K116,   K117,  K118,   K119  }, \
    { K20,  K21,  K22,  K23,  K24,  K25,    K26,  K27,    K28,    K29,    K210,  K211,   K212,  K213,  K214,  K215,   K216,   K217,  K218,   K219  }, \
    { K30,  K31,  K32,  K33,  K34,  K35,    K36,  K37,    K38,    K39,    K310,  K311,   K312,  K313,  K314,  K315,   KC_NO,  K317,  KC_NO,  KC_NO }, \
    { K40,  K41,  K42,  K43,  K44,  K45,    K46,  K47,    K48,    K49,    K410,  K411,   K412,  K413,  K414,  KC_NO,  K416,   K417,  K418,   KC_NO }, \
    { K50,  K51,  K52,  K53,  K54,  KC_NO,  K56,  K57,    K58,    K59,    K510,  KC_NO,  K512,  K513,  K514,  KC_NO,  K516,   K517,  K518,   K519  }, \
         }
