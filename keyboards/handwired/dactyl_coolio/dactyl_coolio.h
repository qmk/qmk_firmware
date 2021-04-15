#pragma once
#include "quantum.h"

#ifdef USE_I2C
#include <stddef.h>
#ifdef __AVR__
    #include <avr/io.h>
    #include <avr/interrupt.h>
#endif
#endif

#define LAYOUT( \
    L00, L01, L02, L03, L04, L05,                     R06, R07, R08, R09, R10, R11, \
    L12, L13, L14, L15, L16, L17,                     R18, R19, R20, R21, R22, R23, \
    L24, L25, L26, L27, L28, L29,                     R30, R31, R32, R33, R34, R35, \
         L36, L37, L38, L39, L40,                     R41, R42, R43, R44, R45,      \
	                    L46, L47,                     R48, R49                      \
) \
{ \
    { L05,   L04,  L03,  L02,  L01,  L00, }, \
    { L17,   L16,  L15,  L14,  L13,  L12, }, \
    { L29,   L28,  L27,  L26,  L25,  L24, }, \
    { L40, L39,  L38,  L37,  L36,  KC_NO, }, \
	{ L47, L46,  KC_NO, KC_NO, KC_NO, KC_NO }, \
    { R06,   R07,   R08,   R09,   R10,   R11   }, \
    { R18,   R19,   R20,   R21,   R22,   R23   }, \
    { R30,   R31,   R32,   R33,   R34,   R35   }, \
    { R41,   R42,   R43,   R44,   R45,   KC_NO }, \
	{ R48,   R49, KC_NO, KC_NO, KC_NO,   KC_NO }, \
}
