#ifndef z150_blackheart_H
#define z150_blackheart_H

#include "quantum.h"

#define LAYOUT( \
	K000, K001, K002, K003, K004, K005, K006, K007, K008, K009, K010, K011, K012, K013, K014, K015, K016, K017, 	  K019, \
	K100, K101, K102, K103, K104, K105, K106, K107, K108, K109, K110, K111, K112, K113, K114, K115, K116, K117, K118, K119, \
	K200, K201, K202, K203, K204, K205, K206, K207, K208, K209, K210, K211, K212, K213,       K215, K216, K217, K218,       \
	K300, K301, K302, K303, K304, K305, K306, K307, K308, K309, K310, K311, K312, K313, K314, K315, K316, K317, K318,       \
	K400, K401, K402, K403, 			      K407,                          			K414, 	K415, 	K417 \
) { \
	{ K000,  K001,  K002,  K003,  K004,  K005,  K006,  K007,  K008,  K009,  K010,  K011,  K012,  K013,  K014,  K015,  K016,  K017,  KC_NO, K019 }, \
	{ K100,  K101,  K102,  K103,  K104,  K105,  K106,  K107,  K108,  K109,  K110,  K111,  K112,  K113,  K114,  K115,  K116,  K117,  K118,  K119 }, \
	{ K200,  K201,  K202,  K203,  K204,  K205,  K206,  K207,  K208,  K209,  K210,  K211,  K212,  K213,  KC_NO, K215,  K216,  K217,  K218,  KC_NO }, \
	{ K300,  K301,  K302,  K303,  K304,  K305,  K306,  K307,  K308,  K309,  K310,  K311,  K312,  K313,  K314,  K315,  K316,  K317,  K318,  KC_NO }, \
	{ K400,  K401,  K402,  K403,  KC_NO, KC_NO, KC_NO, K407,  KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,  K414,  K415, KC_NO, K417,  KC_NO, KC_NO }  \
}
/* Not sure how to setup dual layout support so for now the code is commented out.
#define Z150_TKL( \
	K000, K001, K002, K003, K004, K005, K006, K007, K008, K009, K010, K011, K012, K013, K014, K015,       K017, K018, K019, \
	K100, K101, K102, K103, K104, K105, K106, K107, K108, K109, K110, K111, K112, K113, K114, K115,       K117, K118, K119, \
	K200, K201, K202, K203, K204, K205, K206, K207, K208, K209, K210, K211, K212, K213, K214,       K216, K217, K218,       \
	K300, K301, K302, K303, K304, K305, K306, K307, K308, K309, K310, K311, K312, K313, K314,       K316, K317, K318,       \
	K400, K401, K402, K403, K404, K405,       K407,                         K412, K413, K414, K415, K416, K417, K418  \
) { \
	{ K000,  K001,  K002,  K003,  K004,  K005,  K006,  K007,  K008,  K009,  K010,  K011,  K012,  K013,  K014,  K015,  KC_NO, K017,  K018,  K019 }, \
	{ K100,  K101,  K102,  K103,  K104,  K105,  K106,  K107,  K108,  K109,  K110,  K111,  K112,  K113,  K114,  K115,  KC_NO, K117,  K118,  K119 }, \
	{ K200,  K201,  K202,  K203,  K204,  K205,  K206,  K207,  K208,  K209,  K210,  K211,  K212,  K213,  K214,  KC_NO, K216,  K217,  K218,  KC_NO }, \
	{ K300,  K301,  K302,  K303,  K304,  K305,  K306,  K307,  K308,  K309,  K310,  K311,  K312,  K313,  K314,  KC_NO, K316,  K317,  K318,  KC_NO }, \
	{ K400,  K401,  K402,  K403,  K404,  K405,  KC_NO, K407,  KC_NO, KC_NO, KC_NO, KC_NO, K412,  K413,  K414,  K415,  K416,  K417,  K418,  KC_NO }  \
}*/

#endif