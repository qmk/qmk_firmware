#pragma once

#include "quantum.h"

#define LAYOUT_all( \
	K000, K001, K002, K003, K004, K005, K006, K007, K008, K009, K010, K011, K012, K013, K014, \
	K100,       K102, K103, K104, K105, K106, K107, K108, K109, K110, K111, K112, K113, K114, \
	K200,       K202, K203, K204, K205, K206, K207, K208, K209, K210, K211, K212, K213, K214, \
	K300, K301, K302, K303, K304, K305, K306, K307, K308, K309, K310, K311,       K313, K314, \
	K400, K401,       K403,             K406,                   K410, K411,       K413, K414  \
) { \
	{ K000,  K001,  K002,  K003,  K004,  K005,  K006,  K007,  K008,  K009,  K010,  K011,  K012,  K013,  K014 }, \
	{ K100,  KC_NO, K102,  K103,  K104,  K105,  K106,  K107,  K108,  K109,  K110,  K111,  K112,  K113,  K114 }, \
	{ K200,  KC_NO, K202,  K203,  K204,  K205,  K206,  K207,  K208,  K209,  K210,  K211,  K212,  K213,  K214 }, \
	{ K300,  K301,  K302,  K303,  K304,  K305,  K306,  K307,  K308,  K309,  K310,  K311,  KC_NO, K313,  K314 }, \
	{ K400,  K401,  KC_NO, K403,  KC_NO, KC_NO, K406,  KC_NO, KC_NO, KC_NO, K410,  K411,  KC_NO, K413,  K414 }  \
}


/* ANSI variant. No extra keys for ISO */
#define LAYOUT_60_ansi( \
	K000, K001, K002, K003, K004, K005, K006, K007, K008, K009, K010, K011, K012,       K013, \
	K100,       K102, K103, K104, K105, K106, K107, K108, K109, K110, K111, K112, K113, K114, \
	K200,       K202, K203, K204, K205, K206, K207, K208, K209, K210, K211, K212,       K214, \
	K300,       K302, K303, K304, K305, K306, K307, K308, K309, K310, K311,             K313, \
	K400, K401,       K403,             K406,                   K410, K411,       K413, K414  \
) LAYOUT_all( \
	K000, K001, K002, K003, K004, K005, K006, K007, K008, K009, K010, K011, K012, K013, K013,\
	K100,       K102, K103, K104, K105, K106, K107, K108, K109, K110, K111, K112, K113, K114, \
	K200,       K202, K203, K204, K205, K206, K207, K208, K209, K210, K211, K212, K214, K214, \
	K300, KC_NO,K302, K303, K304, K305, K306, K307, K308, K309, K310, K311,       K313, KC_NO,\
	K400, K401,       K403,             K406,                   K410, K411,       K413, K414  \
)

/* ISO variant. Remove useless ANSI keys */
#define LAYOUT_60_iso( \
	K000, K001, K002, K003, K004, K005, K006, K007, K008, K009, K010, K011, K012,       K013, \
	K100,       K102, K103, K104, K105, K106, K107, K108, K109, K110, K111, K112, K113,       \
	K200,       K202, K203, K204, K205, K206, K207, K208, K209, K210, K211, K212, K213, K214, \
	K300, K301, K302, K303, K304, K305, K306, K307, K308, K309, K310, K311,             K313, \
	K400, K401,       K403,             K406,                   K410, K411,       K413, K414  \
) LAYOUT_all( \
	K000, K001, K002, K003, K004, K005, K006, K007, K008, K009, K010, K011, K012, K013, K013,\
	K100,       K102, K103, K104, K105, K106, K107, K108, K109, K110, K111, K112, K113, K214, \
	K200,       K202, K203, K204, K205, K206, K207, K208, K209, K210, K211, K212, K213, K214, \
	K300, K301, K302, K303, K304, K305, K306, K307, K308, K309, K310, K311,       K313, KC_NO,\
	K400, K401,       K403,             K406,                   K410, K411,       K413, K414  \
)

/* HHKB Variant */
#define LAYOUT_60_ansi_split_bs_rshift( \
	K000, K001, K002, K003, K004, K005, K006, K007, K008, K009, K010, K011, K012, K013, K014, \
	K100,       K102, K103, K104, K105, K106, K107, K108, K109, K110, K111, K112, K113, K114, \
	K200,       K202, K203, K204, K205, K206, K207, K208, K209, K210, K211, K212,       K214, \
	K300,       K302, K303, K304, K305, K306, K307, K308, K309, K310, K311,       K313, K314, \
	K400, K401,       K403,             K406,                   K410, K411,       K413, K414  \
) LAYOUT_all( \
	K000, K001, K002, K003, K004, K005, K006, K007, K008, K009, K010, K011, K012, K013, K014,\
	K100,       K102, K103, K104, K105, K106, K107, K108, K109, K110, K111, K112, K113, K114, \
	K200,       K202, K203, K204, K205, K206, K207, K208, K209, K210, K211, K212, K214, K214, \
	K300, KC_NO,K302, K303, K304, K305, K306, K307, K308, K309, K310, K311,       K313, K314,\
	K400, K401,       K403,             K406,                   K410, K411,       K413, K414  \
)

/* HHKB Variant */
#define LAYOUT_60_hhkb( \
	K000, K001, K002, K003, K004, K005, K006, K007, K008, K009, K010, K011, K012, K013, K014, \
	K100,       K102, K103, K104, K105, K106, K107, K108, K109, K110, K111, K112, K113, K114, \
	K200,       K202, K203, K204, K205, K206, K207, K208, K209, K210, K211, K212,       K214, \
	K300,       K302, K303, K304, K305, K306, K307, K308, K309, K310, K311,       K313, K314, \
	            K401, K403,             K406,                   K411, K413                    \
) LAYOUT_all( \
	K000, K001, K002, K003, K004, K005, K006, K007, K008, K009, K010, K011, K012, K013, K014, \
	K100,       K102, K103, K104, K105, K106, K107, K108, K109, K110, K111, K112, K113, K114, \
	K200,       K202, K203, K204, K205, K206, K207, K208, K209, K210, K211, K212, K214, K214, \
	K300, KC_NO,K302, K303, K304, K305, K306, K307, K308, K309, K310, K311,       K313, K314, \
	KC_NO,K401,       K403,             K406,                   KC_NO,K411,       K413, KC_NO \
)
