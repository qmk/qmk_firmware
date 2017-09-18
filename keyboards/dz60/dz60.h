#ifndef DZ60_H
#define DZ60_H

#include "quantum.h"
#include "led.h"

/* DZ60 LEDs
 *   GPIO pads
 *   1 E2 RGB PWM Underglow
 *   2 B6 Backlight LED
 *   B2 Capslock LED
 */
inline void dz60_caps_led_on(void)    { DDRB |=  (1<<2); PORTB &= ~(1<<2); }
inline void dz60_bl_led_on(void)    	{ DDRF |=  (1<<5); PORTF &= ~(1<<5); }

inline void dz60_caps_led_off(void)   { DDRB &= ~(1<<2); PORTB &= ~(1<<2); }
inline void dz60_bl_led_off(void)   	{ DDRF &= ~(1<<5); PORTF &= ~(1<<5); }

/* XD60 Keymap Definition Macro */
#define KEYMAP( \
      K00,  K01,  K02,  K03,  K04,  K05,  K06,  K07,  K08,  K09,  K0A,  K0B,  K0C,  K0D,  K0E, \
      K10,        K12,  K13,  K14,  K15,  K16,  K17,  K18,  K19,  K1A,  K1B,  K1C,  K1D,  K1E, \
      K20,        K22,  K23,  K24,  K25,  K26,  K27,  K28,  K29,  K2A,  K2B,  K2C,  K2D,       \
      K30,  K31,  K32,  K33,  K34,  K35,  K36,  K37,  K38,  K39,  K3A,        K3C,  K3D,  K3E, \
      K40,  K41,        K43,  K44,        K46,        K48,        K4A,  K4B,  K4C,  K4D,  K4E  \
) { \
    { K00,  K01,   K02,   K03,  K04,  K05,   K06,  K07,   K08,  K09,   K0A,  K0B,   K0C,  K0D,  K0E }, \
    { K10,  KC_NO, K12,   K13,  K14,  K15,   K16,  K17,   K18,  K19,   K1A,  K1B,   K1C,  K1D,  K1E }, \
    { K20,  KC_NO, K22,   K23,  K24,  K25,   K26,  K27,   K28,  K29,   K2A,  K2B,   K2C,  K2D }, \
    { K30,  K31,   K32,   K33,  K34,  K35,   K36,  K37,   K38,  K39,   K3A,  KC_NO, K3C,  K3D,  K3E }, \
    { K40,  K41,   KC_NO, K43,  K44,  KC_NO, K46,  KC_NO, K48,  KC_NO, K4A,  K4B,   K4C,  K4D,  K4E }  \
}

#endif
