#ifndef DO60_H
#define DO60_H

#include "quantum.h"
#include "led.h"

/* DO60 LEDs
 *   GPIO pads
 *   0 F7 not connected
 *   1 F6 not connected
 *   2 F5 RGB PWM Underglow
 *   3 F4 Backlight LED
 *   B2 Capslock LED
 *   B0 not connected
 */

/*
inline void do60_caps_led_on(void)    { DDRB |=  (1<<2); PORTB &= ~(1<<2); }
inline void do60_bl_led_on(void)    	{ DDRF |=  (1<<4); PORTF &= ~(1<<4); }

inline void do60_caps_led_off(void)   { DDRB &= ~(1<<2); PORTB &= ~(1<<2); }
inline void do60_bl_led_off(void)   	{ DDRF &= ~(1<<4); PORTF &= ~(1<<4); }
*/

inline void setdefaultrgb(void){ rgblight_sethsv(100,100,100); }

/* Do60 Keymap Definition Macro */
#define LAYOUT_all( \
      K00,  K01,  K02,  K03,  K04,  K05,  K06,  K07,  K08,  K09,  K0A,  K0B,  K0C,  K0D,  K0E, \
      K10,  K11,  K12,  K13,  K14,  K15,  K16,  K17,  K18,  K19,  K1A,  K1B,  K1C,        K1E, \
      K20,  K21,  K22,  K23,  K24,  K25,  K26,  K27,  K28,  K29,  K2A,  K2B,  K2C,        K2E, \
      K30,  K31,  K32,  K33,  K34,  K35,  K36,  K37,  K38,  K39,  K3A,  K3B,  K3C,  K3D,  K3E, \
      K40,  K41,  K42,              K45,  K46,  K47,              K4A,  K4B,  K4C,  K4D,  K4E  \
) { \
    { K00,  K01,  K02,  K03,  K04,  K05,  K06,  K07,  K08,  K09,  K0A,  K0B,  K0C,  K0D,   K0E }, \
    { K10,  K11,  K12,  K13,  K14,  K15,  K16,  K17,  K18,  K19,  K1A,  K1B,  K1C,  KC_NO, K1E }, \
    { K20,  K21,  K22,  K23,  K24,  K25,  K26,  K27,  K28,  K29,  K2A,  K2B,  K2C,  KC_NO, K2E }, \
    { K30,  K31,  K32,  K33,  K34,  K35,  K36,  K37,  K38,  K39,  K3A,  K3B,  K3C,  K3D,   K3E }, \
    { K40,  K41,  K42,  KC_NO,KC_NO,K45,  K46,  K47,  KC_NO,KC_NO,K4A,  K4B,  K4C,  K4D,   K4E }  \
}

#define LAYOUT_60_ansi( \
      K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C,      K0E, \
      K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C,      K1E, \
      K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B,           K2E, \
      K30,      K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B,      K3D,      \
      K40, K41, K42,                K46,                K4A, K4B, K4C,      K4E  \
) { \
    { K00, K01,   K02, K03,   K04,   K05,   K06, K07,   K08,   K09,   K0A, K0B, K0C,   KC_NO, K0E },   \
    { K10, K11,   K12, K13,   K14,   K15,   K16, K17,   K18,   K19,   K1A, K1B, K1C,   KC_NO, K1E },   \
    { K20, K21,   K22, K23,   K24,   K25,   K26, K27,   K28,   K29,   K2A, K2B, KC_NO, KC_NO, K2E },   \
    { K30, KC_NO, K32, K33,   K34,   K35,   K36, K37,   K38,   K39,   K3A, K3B, KC_NO, K3D,   KC_NO }, \
    { K40, K41,   K42, KC_NO, KC_NO, KC_NO, K46, KC_NO, KC_NO, KC_NO, K4A, K4B, K4C,   KC_NO, K4E }    \
}

#define LAYOUT_60_ansi_split_bs_rshift( \
      K00,  K01,  K02,  K03,  K04,  K05,  K06,  K07,  K08,  K09,  K0A,  K0B,  K0C,  K0D,  K0E, \
      K10,  K11,  K12,  K13,  K14,  K15,  K16,  K17,  K18,  K19,  K1A,  K1B,  K1C,        K1E, \
      K20,  K21,  K22,  K23,  K24,  K25,  K26,  K27,  K28,  K29,  K2A,  K2B,              K2E, \
      K30,        K32,  K33,  K34,  K35,  K36,  K37,  K38,  K39,  K3A,  K3B,        K3D,  K3E, \
      K40,  K41,  K42,                    K46,                    K4A,  K4B,  K4C,        K4E  \
) { \
    { K00,  K01,   K02,  K03,   K04,   K05,   K06, K07,   K08,   K09,   K0A,  K0B,  K0C,   K0D,   K0E }, \
    { K10,  K11,   K12,  K13,   K14,   K15,   K16, K17,   K18,   K19,   K1A,  K1B,  K1C,   KC_NO, K1E }, \
    { K20,  K21,   K22,  K23,   K24,   K25,   K26, K27,   K28,   K29,   K2A,  K2B,  KC_NO, KC_NO, K2E }, \
    { K30,  KC_NO, K32,  K33,   K34,   K35,   K36, K37,   K38,   K39,   K3A,  K3B,  KC_NO, K3D,   K3E }, \
    { K40,  K41,   K42,  KC_NO, KC_NO, KC_NO, K46, KC_NO, KC_NO, KC_NO, K4A,  K4B,  K4C,   KC_NO, K4E }  \
}

#define LAYOUT_chiwi60_default( \
      K00,  K01,  K02,  K03,  K04,  K05,  K06,  K07,  K08,  K09,  K0A,  K0B,  K0C,  K0D,  K0E, \
      K10,  K11,  K12,  K13,  K14,  K15,  K16,  K17,  K18,  K19,  K1A,  K1B,  K1C,        K1E, \
      K20,  K21,  K22,  K23,  K24,  K25,  K26,  K27,  K28,  K29,  K2A,  K2B,              K2E, \
      K30,        K32,  K33,  K34,  K35,  K36,  K37,  K38,  K39,  K3A,  K3B,        K3D,  K3E, \
      K40,  K41,  K42,              K45,        K47,              K4A,  K4B,  K4C,  K4D,  K4E  \
) { \
    { K00, K01,   K02, K03,   K04,   K05, K06,   K07, K08,   K09,   K0A, K0B, K0C,   K0D,   K0E }, \
    { K10, K11,   K12, K13,   K14,   K15, K16,   K17, K18,   K19,   K1A, K1B, K1C,   KC_NO, K1E }, \
    { K20, K21,   K22, K23,   K24,   K25, K26,   K27, K28,   K29,   K2A, K2B, KC_NO, KC_NO, K2E }, \
    { K30, KC_NO, K32, K33,   K34,   K35, K36,   K37, K38,   K39,   K3A, K3B, KC_NO, K3D,   K3E }, \
    { K40, K41,   K42, KC_NO, KC_NO, K45, KC_NO, K47, KC_NO, KC_NO, K4A, K4B, K4C,   K4D,   K4E }  \
}
#endif
