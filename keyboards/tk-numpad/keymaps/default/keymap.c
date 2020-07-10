/*
Copyright 2020
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


//OLED EXAMPLE CODE
//TODO: Change layer stuff
//Stolen from https://beta.docs.qmk.fm/using-qmk/hardware-features/displays/feature_oled_driver


// ENCODER STUFF
// TODO make sure everything else works before this one is added


//Example from https://beta.docs.qmk.fm/using-qmk/hardware-features/feature_encoders

/* void encoder_update_user(uint8_t index, bool clockwise) { */
/*     if (index == 0) { /\* First encoder *\/ */
/*         if (clockwise) { */
/*             tap_code(KC_PGDN); */
/*         } else { */
/*             tap_code(KC_PGUP); */
/*         } */
/*     } else if (index == 1) { /\* Second encoder *\/ */
/*         if (clockwise) { */
/*             tap_code(KC_DOWN); */
/*         } else { */
/*             tap_code(KC_UP); */
/*         } */
/*     } */
/* } */



#include QMK_KEYBOARD_H


//TODO: Change this stuff

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_NLCK, KC_PSLS, KC_PAST, KC_PMNS,
        KC_P7,   KC_P8,   KC_P9,   KC_PPLS,
        KC_P4,   KC_P5,   KC_P6,   KC_PPLS,
        KC_P1,   KC_P2,   KC_P3,   KC_ENT,
        KC_P0,   KC_P0,   KC_PDOT, KC_ENT
    )

    // [1] = LAYOUT(
    //     _______, BL_STEP, RGB_M_SW, RESET,
    //     RGB_TOG, RGB_MOD, RGB_M_P,  RGB_M_SN,
    //     RGB_HUI, RGB_SAI, RGB_VAI,  RGB_M_K,
    //     RGB_HUD, RGB_SAD, RGB_VAD,  RGB_M_X,
    //     _______, WK_RED,  WK_GREEN, WK_BLUE
    // )
};


