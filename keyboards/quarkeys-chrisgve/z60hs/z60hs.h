#pragma once
#ifndef Z60HS_H
#define Z60HS_H

#include "quantum.h"
#include "config.h"

#define XXXX KC_NO

#define LAYOUT_Z60_VIA( \
	K000, K001, K002, K003, K004, K005, K006, K007, K008, K009, K010, K011, K012, 		K014, 					\
	K100,  		K102, K103, K104, K105, K106, K107, K108, K109, K110, K111, K112, K113, K114,	 				\
	K200, 		K202, K203, K204, K205, K206, K207, K208, K209, K210, K211, K212, K213, 	 					\
		  K301, K302, K303, K304, K305, K306, K307, K308, K309, K310, K311, 	  K313, K314,					\
	K400, 		K402, K403,             	  K407,                   K411, 	  K413, K414					\
)  { \
	{ K000,  K001,  K002,  K003,  K004,  K005,  K006,  K007,  K008,  K009,  K010,  K011,  K012,  XXXX,  K014 }, \
	{ K100,  XXXX,  K102,  K103,  K104,  K105,  K106,  K107,  K108,  K109,  K110,  K111,  K112,  K113,  K114 }, \
	{ K200,  XXXX,  K202,  K203,  K204,  K205,  K206,  K207,  K208,  K209,  K210,  K211,  K212,  K213,  XXXX }, \
	{ XXXX,  K301,  K302,  K303,  K304,  K305,  K306,  K307,  K308,  K309,  K310,  K311,  XXXX,  K313,  K314 }, \
	{ K400,  XXXX,  K402,  K403,  XXXX,  XXXX,  XXXX,  K407,  XXXX,  XXXX,  XXXX,  K411,  XXXX,	 K413,  K414 }  \
}

#endif