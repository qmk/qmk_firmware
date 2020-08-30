#pragma once

#include "quantum.h"
#include "led.h"

/* Shawn65 LEDs
 *   GPIO pads
 *   0 F7 Capslock LED
 */
inline void shawn65_caps_led_on(void)      { setPinOutput(F7); writePinLow(F7); }

inline void shawn65_caps_led_off(void)     { setPinInput(F7); }

/* Shawn65 Keymap Definitions */
#define LAYOUT_all( \
    K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, K0D, K0E, \
    K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1D, K1E, \
    K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2C,      K2E, \
    K30, K31, K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B,      K3D, K3E, \
    K40, K41, K42,      K44,                     K49, K4A,      K4C, K4D, K4E, \
) { \
    { K00, K01, K02, K03,   K04,   K05,   K06,   K07,   K08,   K09, K0A, K0B,   K0C,   K0D,   K0E }, \
    { K10, K11, K12, K13,   K14,   K15,   K16,   K17,   K18,   K19, K1A, K1B,   K1C,   K1D,   K1E }, \
    { K20, K21, K22, K23,   K24,   K25,   K26,   K27,   K28,   K29, K2A, K2B,   K2C,   KC_NO, K2E }, \
    { K30, K31, K32, K33,   K34,   K35,   K36,   K37,   K38,   K39, K3A, K3B,   KC_NO, K3D,   K3E }, \
    { K40, K41, K42, KC_NO, K44,   KC_NO, KC_NO, KC_NO, KC_NO, K49, K4A, KC_NO, K4C,   K4D,   K4E }  \
}

