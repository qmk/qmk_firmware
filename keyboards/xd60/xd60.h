#ifndef XD60_H
#define XD60_H

#include "quantum.h"
#include "led.h"

/* XD60 LEDs
 *   GPIO pads
 *   0 F7 not connected
 *   1 F6 RGB PWM Underglow
 *   2 F5 Backlight LED
 *   3 F4 not connected
 *   B2 Capslock LED
 *   B0 not connected
 */
inline void xd60_caps_led_on(void)    { DDRB |=  (1<<2); PORTB &= ~(1<<2); }
inline void xd60_bl_led_on(void)    	{ DDRF |=  (1<<5); PORTF &= ~(1<<5); }

inline void xd60_caps_led_off(void)   { DDRB &= ~(1<<2); PORTB &= ~(1<<2); }
inline void xd60_bl_led_off(void)   	{ DDRF &= ~(1<<5); PORTF &= ~(1<<5); }

/* XD60 Keymap Definition Macro */
#define KEYMAP( \
      K00,  K01,  K02,  K03,  K04,  K05,  K06,  K07,  K08,  K09,  K0A,  K0B,  K0C,  K0D,  K49, \
      K10,  K11,  K12,  K13,  K14,  K15,  K16,  K17,  K18,  K19,  K1A,  K1B,  K1C,  K1D,       \
      K20,  K21,  K22,  K23,  K24,  K25,  K26,  K27,  K28,  K29,  K2A,  K2B,  K2C,  K2D,       \
      K30,  K31,  K32,  K33,  K34,  K35,  K36,  K37,  K38,  K39,  K3A,  K3B,  K47,  K3D,  K3C, \
      K40,  K41,  K42,              K45,                          K4A,  K4B,  K48,  K4C,  K4D  \
) { \
    { K00,  K01,  K02,  K03,  K04,  K05,  K06,  K07,  K08,  K09,  K0A,  K0B,  K0C,  K0D }, \
    { K10,  K11,  K12,  K13,  K14,  K15,  K16,  K17,  K18,  K19,  K1A,  K1B,  K1C,  K1D }, \
    { K20,  K21,  K22,  K23,  K24,  K25,  K26,  K27,  K28,  K29,  K2A,  K2B,  K2C,  K2D }, \
    { K30,  K31,  K32,  K33,  K34,  K35,  K36,  K37,  K38,  K39,  K3A,  K3B,  K3C,  K3D }, \
    { K40,  K41,  K42,  KC_NO,KC_NO,K45,  KC_NO,K47,  K48,  K49,  K4A,  K4B,  K4C,  K4D }  \
}

/* #define KEYMAP( \ */
/* 	K000, K001, K002, K003, K004, K005, K006, K007, K008, K009, K010, K011, K012, K013, K014, \ */
/* 	K100, K101, K102, K103, K104, K105, K106, K107, K108, K109, K110, K111, K112, K113, \ */
/* 	K200, K201, K202, K203, K204, K205, K206, K207, K208, K209, K210, K211, K212, K213, \ */
/* 	K300, K301, K302, K303, K304, K305, K306, K307, K308, K309, K310, K311, K312, K313, K314, \ */
/* 	K400, K401, K402, K403,             K406,                   K410, K411, K412, K413, K414 \ */
/* ) { \ */
/* 	{ K000,  K001,  K002,  K003,   K004,   K005,  K006,   K007,  K008,  K009,  K010,  K011,  K012,  K013 }, \ */
/* 	{ K100,  K101,  K102,  K103,   K104,   K105,  K106,   K107,  K108,  K109,  K110,  K111,  K112,  K113 }, \ */
/* 	{ K200,  K201,  K202,  K203,   K204,   K205,  K206,   K207,  K208,  K209,  K210,  K211,  K212,  K213 }, \ */
/* 	{ K300,  K301,  K302,  K303,   K304,   K305,  K306,   K307,  K308,  K309,  K310,  K311,  K312,  K313 }, \ */
/* 	{ K400,  K401,  K402,  KC_NO,  KC_NO,  K406,  KC_NO,  K014,  K314,  K410,  K411,  K412,  K413,  K414 } \ */
/* } */

#endif
