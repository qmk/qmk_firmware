#pragma once

#define ___ KC_NO

#include "quantum.h"

#define LAYOUT( \
	K000, K001, K002, K003, K004, K005,                                     K012, K013, \
	K100, K101, K102, K103, K104, K105, K106, K107, K108, K109, K110, K111, K112, K113, \ 
	K200,       K202, K203, K204, K205, K206, K207, K208, K209, K210, K211, K212, K213, \
	K300,       K302, K303, K304, K305, K306, K307, K308, K309, K310, K311, K312, K313, \
	K400, K401, K402,       K404,       K406,       K408,       K410, K411, K412, K413, \	                                                                                    
) { \
	K000,  K001,  K002,  K003,  K004,  K005,  KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, K012,  K013 , \
	K100,  K101,  K102,  K103,  K104,  K105,  K106,  K107,  K108,  K109,  K110,  K111,  K112,  K113 , \
	K200,  KC_NO, K202,  K203,  K204,  K205,  K206,  K207,  K208,  K209,  K210,  K211,  K212,  K213 , \
	K300,  KC_NO, K302,  K303,  K304,  K305,  K306,  K307,  K308,  K309,  K310,  K311,  K312,  K313 , \
	K400,  K401,  K402,  KC_NO, K404,  KC_NO, K406,  KC_NO, K408,  KC_NO, K410,  K411,  K412,  K413 , \
	KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO \ 
};
