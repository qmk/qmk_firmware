/*
Copyright 2019 Batuhan Başerdem <baserdem.batuhan@gmail.com> @bbaserdem
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

// Code pertaining to planck rev6
#if defined(KEYBOARD_planck_rev6)
    // Encoder I use;
    #ifdef RGB_DI_PIN
    #undef ENCODER_RESOLUTION
    #endif
    #define ENCODER_RESOLUTION 2
    // Daughter board related utilities
    #ifdef RGB_MATRIX_ENABLE
        // Reconfigure the RGB DI Pin
        #ifdef RGB_DI_PIN
        #undef RGB_DI_PIN
        #endif
        // Change this later
        #define RGB_DI_PIN A1
        // Reconfigure number of LEDS
        #ifdef DRIVER_LED_TOTAL
        #undef DRIVER_LED_TOTAL
        #endif
        #define DRIVER_LED_TOTAL 48
    #elif RGBLIGHT_ENABLE
        // RGB Underglow with on-board SMD footprints
        // This is for original planck led locations
        // ┌────────────┐
        // │ 6  5  4  3 │
        // │            │
        // │     0      │
        // │ 7  8  1  2 │
        // └────────────┘
        #ifdef RGBLIGHT_RIGHT_BEG
        #undef RGBLIGHT_RIGHT_BEG
        #endif
        #define RGBLIGHT_RIGHT_BEG 1

        #ifdef RGBLIGHT_RIGHT_NUM
        #undef RGBLIGHT_RIGHT_NUM
        #endif
        #define RGBLIGHT_RIGHT_NUM 4

        #ifdef RGBLIGHT_LEFT_BEG
        #undef RGBLIGHT_LEFT_BEG
        #endif
        #define RGBLIGHT_LEFT_BEG 5

        #ifdef RGBLIGHT_LEFT_NUM
        #undef RGBLIGHT_LEFT_NUM
        #endif
        #define RGBLIGHT_LEFT_NUM 4
    #endif
#endif

// Let's Split Eh! specific
#ifdef KEYBOARD_lets_split_eh_eh
    #ifdef RGBLIGHT_LEFT_BEG
    #undef RGBLIGHT_LEFT_BEG
    #endif
    #define RGBLIGHT_LEFT_BEG 0

    #ifdef RGBLIGHT_LEFT_NUM
    #undef RGBLIGHT_LEFT_NUM
    #endif
    #define RGBLIGHT_LEFT_NUM 6

    #ifdef RGBLIGHT_RIGHT_BEG
    #undef RGBLIGHT_RIGHT_BEG
    #endif
    #define RGBLIGHT_RIGHT_BEG 6

    #ifdef RGBLIGHT_RIGHT_NUM
    #undef RGBLIGHT_RIGHT_NUM
    #endif
    #define RGBLIGHT_RIGHT_NUM 6
#endif

// JJ40 specific
#ifdef KEYBOARD_jj40
    #ifdef RGBLIGHT_LEFT_BEG
    #undef RGBLIGHT_LEFT_BEG
    #endif
    #define RGBLIGHT_LEFT_BEG 0

    #ifdef RGBLIGHT_LEFT_NUM
    #undef RGBLIGHT_LEFT_NUM
    #endif
    #define RGBLIGHT_LEFT_NUM 2

    #ifdef RGBLIGHT_RIGHT_BEG
    #undef RGBLIGHT_RIGHT_BEG
    #endif
    #define RGBLIGHT_RIGHT_BEG 3

    #ifdef RGBLIGHT_RIGHT_NUM
    #undef RGBLIGHT_RIGHT_NUM
    #endif
    #define RGBLIGHT_RIGHT_NUM 2
#endif
