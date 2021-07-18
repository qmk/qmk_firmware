/*
Copyright 2017 Damien Broqua <contact@darkou.fr>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include "quantum.h"

inline void dk60_caps_led_on(void) { writePinHigh(E6); }
inline void dk60_esc_led_on(void) { writePinHigh(F0); }

inline void dk60_caps_led_off(void) { writePinLow(E6); }
inline void dk60_esc_led_off(void) { writePinLow(F0); }

inline void dk60_led_all_on(void) {
    dk60_caps_led_on();
    dk60_esc_led_on();
}

inline void dk60_led_all_off(void) {
    dk60_caps_led_off();
    dk60_esc_led_off();
}

#define XXX KC_NO

#define LAYOUT( \
    K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, K4B, K4A, \
    K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K4C, \
    K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B,      K2C, \
    K30,      K31, K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B, K3C, \
         K41, K42,                K45,                K48, K49  \
) { \
    { K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C }, \
    { K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C }, \
    { K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2C }, \
    { K30, K31, K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B, K3C }, \
    { XXX, K41, K42, XXX, XXX, K45, XXX, XXX, K48, K49, K4A, K4B, K4C } \
}
