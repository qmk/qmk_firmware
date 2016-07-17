#ifndef RETRO_REFIT_H
#define RETRO_REFIT_H

#include "quantum.h"

// This macro is an example of using a non-standard row-column matrix. The 
// keyboard in question had 11 rows and 8 columns, but the rows were not all 
// horizontal, and the columns were not all vertical. For example, row 2 
// contained "Print Screen", "N", "M", ",", ".", "/", "Right Shift", and
// "Left Alt". Column 0 contained "F6", "7", "O", "'", "Q", "D", "B", 
// "Left Alt", "Up Arrow", and "Down Arrow".
//
// The macro makes programming the keys easier and in a more straight-forward
// manner because it realigns the keys into a 6x15 sensible keyboard layout 
// instead of the obtuse 11x8 matrix.

#define KEYMAP( \
	K77, K05, K04, K03, K02, K01, K00, KA7, KA6, KA5, KA4, KA3, KA2, K11, K94, \
	K27, K76, K75, K74, K73, K72, K71, K70, K67, K66, K65, K64, K63, K62, KA1, \
	K61, K60, K57, K56, K55, K54, K53, K52, K51, K50, K47, K46, K45,      K97, \
	K43, K42, K41, K40, K37, K36, K35, K34, K33, K32, K31, K30,      K44, K87, \
	K26,      K24, K23, K22, K21, K20, K17, K16, K15, K14, K13, K12, KA0, K91, \
	K10, K06, K25,                K07,                K86, K85, K95, K90, K93  \
) { \
{	KC_##K00,	KC_##K01,	KC_##K02,	KC_##K03,	KC_##K04,	KC_##K05,	KC_##K06,	KC_##K07,	}, \
{	KC_##K10,	KC_##K11,	KC_##K12,	KC_##K13,	KC_##K14,	KC_##K15,	KC_##K16,	KC_##K17,	}, \
{	KC_##K20,	KC_##K21,	KC_##K22,	KC_##K23,	KC_##K24,	KC_##K25,	KC_##K26,	KC_##K27,	}, \
{	KC_##K30,	KC_##K31,	KC_##K32,	KC_##K33,	KC_##K34,	KC_##K35,	KC_##K36,	KC_##K37,	}, \
{	KC_##K40,	KC_##K41,	KC_##K42,	KC_##K43,	KC_##K44,	KC_##K45,	KC_##K46,	KC_##K47,	}, \
{	KC_##K50,	KC_##K51,	KC_##K52,	KC_##K53,	KC_##K54,	KC_##K55,	KC_##K56,	KC_##K57,	}, \
{	KC_##K60,	KC_##K61,	KC_##K62,	KC_##K63,	KC_##K64,	KC_##K65,	KC_##K66,	KC_##K67,	}, \
{	KC_##K70,	KC_##K71,	KC_##K72,	KC_##K73,	KC_##K74,	KC_##K75,	KC_##K76,	KC_##K77,	}, \
{	KC_NO,		KC_NO,		KC_NO,		KC_NO,		KC_NO,		KC_##K85,	KC_##K86,	KC_##K87,	}, \
{	KC_##K90,	KC_##K91,	KC_NO,		KC_##K93,	KC_##K94,	KC_##K95,	KC_NO,		KC_##K97,	}, \
{	KC_##KA0,	KC_##KA1,	KC_##KA2,	KC_##KA3,	KC_##KA4,	KC_##KA5,	KC_##KA6,	KC_##KA7,	} \
}

#endif