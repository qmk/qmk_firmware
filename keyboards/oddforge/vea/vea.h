/*
Copyright 2021 MajorKoos <github.com/majorkoos>

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
#include "i2c_master.h"
#include "rgblight.h"
#include "ws2812.h"
#include "led.h"

#define WS2812_ADDRESS 0xb0
#define WS2812_ADDRESS_SPLIT 0xb8
#define WS2812_TIMEOUT 100

void vea_setleds(LED_TYPE *ledarray, uint16_t leds);

/*
LEFT
            .5,0. .5,1. .5,2. .5,3. .5,4. .5,5. .5,6.
.6,1. .7,1. .4,0. .4,1. .4,2. .4,3. .4,4. .4,5. .4,6.
.6,2. .7,2. .3,0. .3,1. .3,2. .3,3. .3,4. .3,5.
.6,3. .7,3. .2,0. .2,1. .2,2. .2,3. .2,4. .2,5.
.6,4. .7,4. .1,0. .1,1. .1,2. .1,3. .1,4. .1,5.
.6,5. .7,5. .0,0. .0,1. .0,2. .7,7. .6,6.

RIGHT
.5,8. .5,9. .5,10. .5,11. .5,12. .5,13. .6,11. .7,11. .6,13.
.4,8. .4,9. .4,10. .4,11. .4,12. .4,13. .4,14. .6,10.
.1,8. .1,9. .1,10. .1,11. .1,12. .1,13. .1,14. .2,14. .7,10.
.2,8. .2,9. .2,10. .2,11. .2,12. .2,13. .3,13. .6,12.
.3,8. .3,9. .3,10. .3,11. .3,12. .3,14. .6,8. .7,12.
.6,14. .0,10. .0,9. .0,8. .7,8. .6,9. .7,9.

*/

#define LAYOUT( \
            K50,  K51,  K52,  K53,  K54,  K55,  K56,              K58,  K59,  K5A,  K5B,  K5C,  K5D,  K6B,  K7B,  K6D, \
K61,  K71,  K40,  K41,  K42,  K43,  K44,  K45,  K46,              K48,  K49,  K4A,  K4B,  K4C,  K4D,  K4E,  K6A,       \
K62,  K72,  K30,  K31,  K32,  K33,  K34,  K35,                    K18,  K19,  K1A,  K1B,  K1C,  K1D,  K1E,  K2E,  K7A, \
K63,  K73,  K20,  K21,  K22,  K23,  K24,  K25,                    K28,  K29,  K2A,  K2B,  K2C,  K2D,  K3D,  K6C,       \
K64,  K74,  K10,  K11,  K12,  K13,  K14,  K15,                    K38,  K39,  K3A,  K3B,  K3C,  K3E,  K68,  K7C,       \
K65,  K75,  K00,  K01,  K02,              K77, K66,               K6E,  K0A,  K09,  K08,  K78,  K69,  K79              \
){ \
{ K00,    K01,    K02,    KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  K08,    K09,    K0A,    KC_NO,  KC_NO,  KC_NO,  KC_NO }, \
{ K10,    K11,    K12,    K13,    K14,    K15,    KC_NO,  KC_NO,  K18,    K19,    K1A,    K1B,    K1C,    K1D,    K1E   }, \
{ K20,    K21,    K22,    K23,    K24,    K25,    KC_NO,  KC_NO,  K28,    K29,    K2A,    K2B,    K2C,    K2D,    K2E   }, \
{ K30,    K31,    K32,    K33,    K34,    K35,    KC_NO,  KC_NO,  K38,    K39,    K3A,    K3B,    K3C,    K3D,    K3E   }, \
{ K40,    K41,    K42,    K43,    K44,    K45,    K46,    KC_NO,  K48,    K49,    K4A,    K4B,    K4C,    K4D,    K4E   }, \
{ K50,    K51,    K52,    K53,    K54,    K55,    K56,    KC_NO,  K58,    K59,    K5A,    K5B,    K5C,    K5D,    KC_NO }, \
{ KC_NO,  K61,    K62,    K63,    K64,    K65,    K66,    KC_NO,  K68,    K69,    K6A,    K6B,    K6C,    K6D,    K6E   }, \
{ KC_NO,  K71,    K72,    K73,    K74,    K75,    KC_NO,  K77,    K78,    K79,    K7A,    K7B,    K7C,    KC_NO,  KC_NO }  \
}
