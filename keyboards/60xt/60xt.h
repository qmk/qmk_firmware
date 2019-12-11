#ifndef _60XT_H
#define _60XT_H

#include "quantum.h"
#include "led.h"

inline void _60xt_caps_led_on(void)      { DDRD |=  (1<<4); PORTD &= ~(1<<4); }
inline void _60xt_fn_led_on(void)    	{ DDRD |=  (1<<7); PORTD &= ~(1<<7); }

inline void _60xt_caps_led_off(void)     { DDRD &= ~(1<<4); PORTD &= ~(1<<4); }
inline void _60xt_fn_led_off(void)   	{ DDRD &= ~(1<<7); PORTD &= ~(1<<7); }

#define LAYOUT( \
    K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, K0D, K0E, K0F,\
    K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1D, K1E, K1F, \
    K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2C, K2D, K2E, K2F, \
    K30, K31, K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B, K3C, K3D, K3E, K3F, \
    K40, K41, K42, K43, K44,           K45,                          K49, K4A, K4B \
) { \
    { K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, K0D, K0E, K0F }, \
    { K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1D, K1E, K1F }, \
    { K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2C, K2D, K2E, K2F }, \
    { K30, K31, K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B, K3C, K3D, K3E, K3F }, \
    { K40, K41, K42, K43, K44, KC_NO, KC_NO, KC_NO, K45, KC_NO, KC_NO, KC_NO, KC_NO, K49, K4A, K4B }  \
}


#endif
