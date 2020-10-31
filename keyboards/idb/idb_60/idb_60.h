#pragma once

#include "quantum.h"

void _idb_60_caps_led_on(void);
void _idb_60_fn_led_on(void);
void _idb_60_caps_led_off(void);
void _idb_60_fn_led_off(void);

#define _idb_60_esc_led_on() _idb_60_fn_led_on()
#define _idb_60_esc_led_off() _idb_60_fn_led_off()

#define LAYOUT( \
	K00, K10, K01, K11, K02, K12, K03, K13, K04, K14, K05, K15, K06, K16, K07,\
	K20, K30, K21, K31, K22, K32, K23, K33, K24, K34, K25, K35, K26, K36,\
	K40, K50, K41, K51, K42, K52, K43, K53, K44, K54, K45, K55,      K56,\
	K60, K70, K61, K71, K62, K72, K63, K73, K64, K74, K65, K75, K66, K76,\
	K80, K90, K81,                     K93,                K95, K86, K96\
) { \
	{ K00,   K01,   K02,   K03,   K04,   K05,   K06,   K07 }, \
	{ K10,   K11,   K12,   K13,   K14,   K15,   K16        }, \
	{ K20,   K21,   K22,   K23,   K24,   K25,   K26        }, \
	{ K30,   K31,   K32,   K33,   K34,   K35,   K36        }, \
	{ K40,   K41,   K42,   K43,   K44,   K45,   KC_NO      }, \
	{ K50,   K51,   K52,   K53,   K54,   K55,   K56        }, \
	{ K60,   K61,   K62,   K63,   K64,   K65,   K66        }, \
	{ K70,   K71,   K72,   K73,   K74,   K75,   K76        }, \
	{ K80,   K81,   KC_NO, KC_NO, KC_NO, KC_NO, K86        }, \
	{ K90,   KC_NO, KC_NO, K93,   KC_NO, K95,   K96        } \
}

#define LAYOUT_all LAYOUT

#define LAYOUT_default( \
	K00, K10, K01, K11, K02, K12, K03, K13, K04, K14, K05, K15, K06, K16,\
	K20, K30, K21, K31, K22, K32, K23, K33, K24, K34, K25, K35, K26, K36,\
	K40, K50, K41, K51, K42, K52, K43, K53, K44, K54, K45, K55,      K56,\
	K60,      K61, K71, K62, K72, K63, K73, K64, K74, K65, K75, K66, K76,\
	K80,      K81,                     K93,                K95,      K96\
) { \
	{ K00,   K01,   K02,   K03,   K04,   K05,   K06,	KC_NO }, \
	{ K10,   K11,   K12,   K13,   K14,   K15,   K16        	  }, \
	{ K20,   K21,   K22,   K23,   K24,   K25,   K26           }, \
	{ K30,   K31,   K32,   K33,   K34,   K35,   K36           }, \
	{ K40,   K41,   K42,   K43,   K44,   K45,   KC_NO         }, \
	{ K50,   K51,   K52,   K53,   K54,   K55,   K56           }, \
	{ K60,   K61,   K62,   K63,   K64,   K65,   K66           }, \
	{ KC_NO, K71,   K72,   K73,   K74,   K75,   K76           }, \
	{ K80,   K81,   KC_NO, KC_NO, KC_NO, KC_NO, KC_NO         }, \
	{ KC_NO, KC_NO, KC_NO, K93,   KC_NO, K95,   K96           } \
}
