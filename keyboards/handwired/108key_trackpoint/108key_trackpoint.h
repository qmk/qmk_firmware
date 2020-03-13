#pragma once

#include "quantum.h"

#define LAYOUT( \
  K000,       K002, K003, K004, K005,       K007, K008, K009, K010, K011, K012, K013, K014, K015, K016, K017,       K019, K020, K021, K022, \
	                                                                                                                                          \
  K200, K201, K202, K203, K204, K205, K206, K207, K208, K209, K210, K211, K212,       K214, K215, K216, K217,       K219, K220, K221, K222, \
  K300,       K302, K303, K304, K305, K306, K307, K308, K309, K310, K311, K312, K313, K314, K315, K316, K317,       K319, K320, K321,       \
  K400,       K402, K403, K404, K405, K406, K407, K408, K409, K410, K411, K412, K413,                               K419, K420, K421, K422, \
  K501, K502, K503, K504, K505, K506, K507, K508, K509, K510, K511,       K513,             K516,             K519, K520, K521,       \
	K600, K601,       K603,             K606,                   K610, K611,       K613, K614, K615, K616, K617,       K619,       K621, K622, \
                             K705, K706, K707  \
) { \
  { K000,  KC_NO, K002,  K003,  K004,  K005,  KC_NO, K007,  K008,  K009,  K010,  K011,  K012,  K013,  K014,  K015,  K016,  K017,  KC_NO, K019,  K020,  K021,  K022 }, \
  { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }, \
  { K200,  K201,  K202,  K203,  K204,  K205,  K206,  K207,  K208,  K209,  K210,  K211,  K212,  KC_NO, K214,  K215,  K216,  K217,  KC_NO, K219,  K220,  K221,  K222 }, \
  { K300,  KC_NO, K302,  K303,  K304,  K305,  K306,  K307,  K308,  K309,  K310,  K311,  K312,  K313,  K314,  K315,  K316,  K317,  KC_NO, K319,  K320,  K321,  KC_NO }, \
  { K400,  KC_NO, K402,  K403,  K404,  K405,  K406,  K407,  K408,  K409,  K410,  K411,  K412,  K413,  KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, K419,  K420,  K421,  K422 }, \
  { KC_NO, K501,  K502,  K503,  K504,  K505,  K506,  K507,  K508,  K509,  K510,  K511,  KC_NO, K513,  KC_NO, KC_NO, K516,  KC_NO, KC_NO, K519,  K520,  K521,  KC_NO }, \
  { K600,  K601,  KC_NO, K603,  KC_NO, KC_NO, K606,  KC_NO, KC_NO, KC_NO, K610,  K611,  KC_NO, K613,  K614,  K615,  K616,  K617,  KC_NO, K619,  KC_NO, K621,  K622 }, \
  { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, K705,  K706,  K707,  KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO }  \
}
