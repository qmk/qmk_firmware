/* Copyright 2018 MechMerlin

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
#ifndef KIRA75_H
#define KIRA75_H

#include "quantum.h"


// Functions for setting LEDs on toggle keys
inline void caps_led_on(void)     { DDRD |=  (1<<7); PORTD &= ~(1<<7); }
inline void caps_led_off(void)    { DDRD &= ~(1<<7); PORTD &= ~(1<<7); }

inline void num_led_on(void)      { DDRD |=  (1<<6); PORTD &= ~(1<<6); }
inline void num_led_off(void)     { DDRD &= ~(1<<6); PORTD &= ~(1<<6); }

// This a shortcut to help you visually see your layout.
// The following is an example using the Planck MIT layout
// The first section contains all of the arguments
// The second converts the arguments into a two-dimensional array
#define LAYOUT( \
    K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, K0D, K0E, K0F, \
    K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1D,      K1F, \
    K20,      K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2C, K2D, K2E, K2F, \
    K30,      K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B, K3C, K3D,      K3F, \
         K41, K42, K43, K44, K45, K46, K47, K48, K49, K4A, K4B, K4D, K4E,      K4F, \
    K50, K51,      K53,           K56,                K5A, K5B, K5D, K5E,      K5F  \
) \
{ \
    { K00,   K01,   K02,   K03, K04,   K05,   K06, K07,   K08,   K09,   K0A, K0B, K0C,   K0D, K0E,   K0F }, \
    { K10,   K11,   K12,   K13, K14,   K15,   K16, K17,   K18,   K19,   K1A, K1B, K1C,   K1D, KC_NO, K1F }, \
    { K20,   KC_NO, K22,   K23, K24,   K25,   K26, K27,   K28,   K29,   K2A, K2B, K2C,   K2D, K2E,   K2F }, \
    { K30,   KC_NO, K32,   K33, K34,   K35,   K36, K37,   K38,   K39,   K3A, K3B, K3C,   K3D, KC_NO, K3F }, \
    { KC_NO, K41,   K42,   K43, K44,   K45,   K46, K47,   K48,   K49,   K4A, K4B, KC_NO, K4D, K4E,   K4F }, \
    { K50,   K51,   KC_NO, K53, KC_NO, KC_NO, K56, KC_NO, KC_NO, KC_NO, K5A, K5B, KC_NO, K5D, K5E,   K5F }  \
}

#endif
