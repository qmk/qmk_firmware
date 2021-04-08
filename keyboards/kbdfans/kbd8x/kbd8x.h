/* Copyright 2017 MechMerlin
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#pragma once

#include "quantum.h"
#include "led.h"

// Functions for setting LEDs on toggle keys
inline void caps_led_on(void)     { writePinHigh(LED_CAPS_LOCK_PIN); }
inline void caps_led_off(void)    { writePinLow(LED_CAPS_LOCK_PIN); }

inline void num_led_on(void)      { writePinHigh(LED_NUM_LOCK_PIN); }
inline void num_led_off(void)     { writePinLow(LED_NUM_LOCK_PIN); }

inline void scroll_led_on(void)   { writePinHigh(LED_SCROLL_LOCK_PIN); }
inline void scroll_led_off(void)  { writePinLow(LED_SCROLL_LOCK_PIN); }

// LAYOUT depicting all possible switch positions.
// LAYOUT_all supports ISO, split backspace and split left/right shift.
#define LAYOUT_all( \
    K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, K0D, K0E, K3D,           \
    K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1D, K1E, K5B, K5C, K3E, \
    K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2C, K2D, K2E, K5D, K5E,      \
    K30, K31, K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B, K3C,                          \
    K40, K41, K42, K43, K44, K45, K46, K47, K48, K49, K4A, K4B, K4C, K4D, K4E,                \
    K50, K51, K52, K53, K54, K55, K56, K57, K58, K59, K5A                                     \
) \
{ \
    { K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, K0D, K0E }, \
    { K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1D, K1E }, \
    { K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2C, K2D, K2E }, \
    { K30, K31, K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B, K3C, K3D, K3E }, \
    { K40, K41, K42, K43, K44, K45, K46, K47, K48, K49, K4A, K4B, K4C, K4D, K4E }, \
    { K50, K51, K52, K53, K54, K55, K56, K57, K58, K59, K5A, K5B, K5C, K5D, K5E }  \
}

// LAYOUT depicting only switch positions for a standard TKL ANSI keyboard.
// TODO: Double check location of backspace key for 2u layout (It's either K1D or K1C).
#define LAYOUT_tkl_ansi( \
    K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, K0D, K0E, K3D,      \
    K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1E, K5B, K5C, K3E, \
    K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2C, K2D, K2E, K5D, K5E, \
    K30, K31, K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B, K3C,                     \
    K40,      K42, K43, K44, K45, K46, K47, K48, K49, K4A, K4B, K4C, K4E,                \
    K50, K51, K52, K53, K54, K55, K56, K57, K58, K59, K5A                                \
) \
{ \
    { K00, K01,   K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, K0D,   K0E }, \
    { K10, K11,   K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, KC_NO, K1E }, \
    { K20, K21,   K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2C, K2D,   K2E }, \
    { K30, K31,   K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B, K3C, K3D,   K3E }, \
    { K40, KC_NO, K42, K43, K44, K45, K46, K47, K48, K49, K4A, K4B, K4C, KC_NO, K4E }, \
    { K50, K51,   K52, K53, K54, K55, K56, K57, K58, K59, K5A, K5B, K5C, K5D,   K5E }  \
}

