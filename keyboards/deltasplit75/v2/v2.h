#pragma once

#include "quantum.h"

//matrix is defined in a weird way here; the layout on both sides are asymmetrical, but the "matrix" is symmetrical but with empty gaps
//the last column is defined as a separate row because the firmware currently doesnt support more than 8 columns (this layout has 9 columns per side) K45 and K110 are the Bs on both sides; K53 and K106 are extra keys for ISO
#define LAYOUT_v2( \
	K00,   K01,   K02,   K03,   K04,   K05,   K06,       K70,   K71,   K72,   K73,   K74,   K75,   K76,   K77,   K132, \
	K10,   K11,   K12,   K13,   K14,   K15,   K16,       K80,   K81,   K82,   K83,   K84,   K85,   K86,   K87,   K133, \
	K20,   K21,   K22,   K23,   K24,   K25,              K90,   K91,   K92,   K93,   K94,   K95,   K96,   K97,   K134, \
	K30,   K31,   K32,   K33,   K34,   K35,              K100,  K101,  K102,  K103,  K104,  K105,  K106,  K107,  K135, \
	K40,   K53,   K41,   K42,   K43,   K44,   K45,              K110,  K111,  K112,  K113,  K114,  K115,  K116,  K117,  K136, \
	K50,   K51,   K52,          K54,   K55,              K120,  K121,  K122,  K123,                K126,  K127,  K137 \
	) \
	{ \
		{ K00,   K01,   K02,   K03,   K04,   K05,   K06,   KC_NO}, \
		{ K10,   K11,   K12,   K13,   K14,   K15,   K16,   KC_NO}, \
		{ K20,   K21,   K22,   K23,   K24,   K25,   KC_NO, KC_NO}, \
		{ K30,   K31,   K32,   K33,   K34,   K35,   KC_NO, KC_NO}, \
		{ K40,   K41,   K42,   K43,   K44,   K45,   KC_NO, KC_NO}, \
		{ K50,   K51,   K52,   K53,   K54,   K55,   KC_NO, KC_NO}, \
		{ KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO}, \
		{ K70  , K71,   K72,   K73,   K74,   K75,   K76,   K77}, \
		{ K80,   K81,   K82,   K83,   K84,   K85,   K86,   K87}, \
		{ K90,   K91,   K92,   K93,   K94,   K95,   K96,   K97}, \
		{ K100,  K101,  K102,  K103,  K104,  K105,  K106, K107}, \
		{ K110,  K111,  K112,  K113,  K114,  K115,  K116,  K117}, \
		{ K120,  K121,  K122,  K123,  KC_NO, KC_NO, K126,  K127}, \
		{ KC_NO, KC_NO, K132,  K133,  K134,  K135,  K136,  K137} \
	}

#define LAYOUT_protosplit( \
	K00,   K01,   K02,   K03,   K04,   K05,   K06,       K70,   K71,   K72,   K73,   K74,   K75,   K76,   K77,   K132, \
	K10,   K11,   K12,   K13,   K14,   K15,   K16,       K80,   K81,   K82,   K83,   K84,   K85,   K86,   K87,   K133, \
	K20,   K21,   K22,   K23,   K24,   K25,              K90,   K91,   K92,   K93,   K94,   K95,   K96,   K97,   K134, \
	K30,   K31,   K32,   K33,   K34,   K35,              K100,  K101,  K102,  K103,  K104,  K105,         K107,  K135, \
	K40,   K41,   K42,   K43,   K44,   K45,              K110,  K111,  K112,  K113,  K114,  K115,  K116,  K117,  K136, \
	K50,   K51,   K52,          K54,   K55,              K120,  K121,  K122,  K123,                K126,  K127,  K137 \
	) \
	{ \
		{ K00,   K01,   K02,   K03,   K04,   K05,   K06,   KC_NO}, \
		{ K10,   K11,   K12,   K13,   K14,   K15,   K16,   KC_NO}, \
		{ K20,   K21,   K22,   K23,   K24,   K25,   KC_NO, KC_NO}, \
		{ K30,   K31,   K32,   K33,   K34,   K35,   KC_NO, KC_NO}, \
		{ K40,   K41,   K42,   K43,   K44,   K45,   KC_NO, KC_NO}, \
		{ K50,   K51,   K52,   KC_NO, K54,   K55,   KC_NO, KC_NO}, \
		{ KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO}, \
		{ K70  , K71,   K72,   K73,   K74,   K75,   K76,   K77}, \
		{ K80,   K81,   K82,   K83,   K84,   K85,   K86,   K87}, \
		{ K90,   K91,   K92,   K93,   K94,   K95,   K96,   K97}, \
		{ K100,  K101,  K102,  K103,  K104,  K105,  KC_NO, K107}, \
		{ K110,  K111,  K112,  K113,  K114,  K115,  K116,  K117}, \
		{ K120,  K121,  K122,  K123,  KC_NO, KC_NO, K126,  K127}, \
		{ KC_NO, KC_NO, K132,  K133,  K134,  K135,  K136,  K137} \
	}
