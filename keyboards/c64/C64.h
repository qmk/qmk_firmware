#ifndef C64_H
#define C64_H

#pragma once

#include "quantum.h"

// This a shortcut to help you visually see your layout.
// The following is an example using the Planck MIT layout
// The first section contains all of the arguements
// The second converts the arguments into a two-dimensional array


// Enable this for ProMicro built-in LEDS
//#define tx_led B0
//#define rx_led D5
 

#define LAYOUT_C64Mini( \
    K00, K01, K02, K03, K04, K05, K06, K07, K08,                                                                 \
    K10, K11, K12, K13, K14, K15, K16, K17, K18,                                                                \
    K20, K21, K22, K23, K24, K25, K26, K27, K28,                                                                \
    K30, K31, K32, K33, K34, K35, K36, K37, K38,                                                            \
    K40, K41, K42, K43, K44, K45, K46, K47, K48,                                                            \
    K50, K51, K52, K53, K54, K55, K56, K57,                                                             \
    K60, K61, K62, K63, K64, K65, K66, K67,                                                             \
    K70, K71, K72, K73, K74, K75, K76, K77,                                                             \
    K80, K81, K82, K83, K84, K85                                                                           \
) { \
    { K00,   K01,   K02,   K03,   K04,   K05,   K06,   K07,   KC_NO         },   \
    { K10,   K11,   K12,   K13,   K14,   K15,   K16,   K17,   KC_NO         },   \
    { K20,   K21,   K22,   K23,   K24,   K25,   K26,   K27,   KC_NO         },   \
    { K30,   K31,   K32,   K33,   K34,   K35,   K36,   K37,   K38           },   \
    { K40,   K41,   K42,   K43,   K44,   K45,   K46,   K47,   K48           },   \
    { K50,   K51,   K52,   K53,   K54,   K55,   K56,   K57,   K58           },   \
    { K60,   K61,   K62,   K63,   K64,   K65,   K66,   K67,   K68           },   \
    { K70,   K71,   K72,   K73,   K74,   K75,   K76,   K77,   K78           },   \
    { K80,   K81,   K82,   K83,   K84,   K85,   KC_NO, KC_NO, KC_NO         }    \
}
#endif
/* QWERTY
*|	1		|	3		|	5	|	7	|	9	|	+	|	£		|	DEL		|			|																			
*|	LEFT	|	W		|	R	|	Y	|	I	|	P	|	*		|	ENT		|			|																		
*|	CTRL	|	A		|	D	|	G	|	J	|	L	|	;		|	RIGHT	|			|																			
*|	PAUSE	|	LSFT	|	X	|	V	|	N	|	,	|	/		|	DOWN	|			|																			
*|	SPACE	|	Z		|	C	|	B	|	M	|	.	|	RSFT	|	F1		|			|																			
*|	WIN		|	S		|	F	|	H	|	K	|	:	|	=		|	F3		|			|																			
*|	Q		|	E		|	T	|	U	|	O	|	@	|	^		|	F5		|			|																			
*|	2		|	4		|	6	|	8	|	0	|	-	|	HOME	|	F7		|			|																			
*|			|			|		|		|		|		|			|			|	RESTO?	|
*/ 
