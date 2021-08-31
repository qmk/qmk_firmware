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
#include QMK_KEYBOARD_H
#include "bbaserdem.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // Base layer
    [_BASE] = LAYOUT_ortho_4x12_wrapper(
        _BL1_5_,_BL1_1_,_BR1_1_,_BR1_5_,
        _BL2_5_,_BL2_1_,_BR2_1_,_BR2_5_,
        _BL3_5_,_BL3_1_,_BR3_1_,_BR3_5_,
        BB_ENC0,KC_DOWN,KC_UP,  _BL4_3_,_BR4_3_,KC_LEFT,KC_RGHT,RGB_TOG
    ),
    // Extra characters overlay
    [_CHAR] = LAYOUT_ortho_4x12_wrapper(
        _CL1_5_,xxx2xxx,_CR1_5_,
        _CL2_5_,xxx2xxx,_CR2_5_,
        _CL3_5_,xxx2xxx,_CR3_5_,
        ___3___,_CL4_3_,_CR4_3_,___3___
    ),
    // Game layer: left_half
    [_GAME] = LAYOUT_ortho_4x12_wrapper(
        _GA1_5_,_GA1_1_,___6___,
        _GA2_5_,_GA2_1_,___6___,
        _GA3_5_,_GA3_1_,___6___,
        ___3___,_GA4_3_,___6___
    ),
    // Media layer: right_half
    [_MEDI] = LAYOUT_ortho_4x12_wrapper(
        ___6___,xxx1xxx,_ME1_5_,
        ___6___,xxx1xxx,_ME2_5_,
        ___6___,xxx1xxx,_ME3_5_,
        ___6___,_ME4_3_,___3___
    ),
    // Navigation layer: right_half
    [_NAVI] = LAYOUT_ortho_4x12_wrapper(
        ___6___,xxx1xxx,_NA1_5_,
        ___6___,xxx1xxx,_NA2_5_,
        ___6___,xxx1xxx,_NA3_5_,
        ___6___,_NA4_3_,___3___
    ),
    // Symbol layer: right_half
    [_SYMB] = LAYOUT_ortho_4x12_wrapper(
        ___6___,xxx1xxx,_SY1_5_,
        ___6___,xxx1xxx,_SY2_5_,
        ___6___,xxx1xxx,_SY3_5_,
        ___6___,_SY4_3_,___3___
    ),
    // Number layer: left_half
    [_NUMB] = LAYOUT_ortho_4x12_wrapper(
        xxx1xxx,_NU1_5_,___6___,
        xxx1xxx,_NU2_5_,___6___,
        xxx1xxx,_NU3_5_,___6___,
        ___3___,_NU4_3_,___6___
    ),
    // Function layer: left_half
    [_FUNC] = LAYOUT_ortho_4x12_wrapper(
        _FU1_5_,xxx1xxx,___6___,
        _FU2_5_,xxx1xxx,___6___,
        _FU3_5_,xxx1xxx,___6___,
        ___3___,_FU4_3_,___6___
    ),
    // Mouse layer: left_half
    [_MOUS] = LAYOUT_ortho_4x12_wrapper(
        _MO1_5_,xxx1xxx,___6___,
        _MO2_5_,xxx1xxx,___6___,
        _MO3_5_,xxx1xxx,___6___,
        ___3___,_MO4_3_,___6___
    ),
    // Music layer: everything
    [_MUSI] = LAYOUT_ortho_4x12_wrapper(
        _MU_12_,_MU_12_,_MU_12_,
        ___1___,_MU_02_,_MUL_3_,_MUR_3_,_MU_02_,___1___)
};

// RGB Matrix configuration
#ifdef RGB_MATRIX_ENABLE

// planck:Light
#if defined(KEYBOARD_planck_light)
/* This is left-right for planck light indicator light
 *  - The LED 42 is for spacebar specifically, leave it out of the matrix
 *  - This is how it looks like
 * ┌──┬──┬──┬──┬──┬──┬──┬──┬──┬──┬──┬──┐
 * │00│01│02│03│04│05│06│07│08│09│10│11│
 * ├──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┤
 * │12│13│14│15│16│17│18│19│20│21│22│23│
 * ├──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┤
 * │24│25│26│27│28│29│30│31│32│33│34│35│
 * ├──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┤
 * │36│37│38│39│40│41│43│44│45│46│47│48│
 * └──┴──┴──┴──┴──┴─042─┴──┴──┴──┴──┴──┘
 */
int board_left[24] = {
     0,  1,  2,  3,  4,  5,
    12, 13, 14, 15, 16, 17,
    24, 25, 26, 27, 28, 29,
    36, 37, 38, 39, 40, 41};
int board_right[24] = {
     6,  7,  8,  9, 10, 11,
    18, 19, 20, 21, 22, 23,
    30, 31, 32, 33, 34, 35,
    43, 44, 45, 46, 47, 48};
// Sided color-setting
void keylight_set_left(uint8_t red, uint8_t green, uint8_t blue) {
    for (int i = 0; i < 24; i++) {
        rgb_matrix_set_color(board_left[i], red, green, blue);
    }
}
void keylight_set_right(uint8_t red, uint8_t green, uint8_t blue) {
    for (int i = 0; i < 24; i++) {
        rgb_matrix_set_color(board_right[i], red, green, blue);
    }
}

// planck:rev6
#elif defined(KEYBOARD_planck_rev6)
/* Rev6 has RGB matrix to the bottom LED footprints
 * Breakdown of the daughter board layout that I'm planning to use
 * ┌──┬──┬──┬──┬──┬──┬──┬──┬──┬──┬──┬──┐
 * │35│36│37│38│39│40│41│42│43│44│45│46│
 * ├──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┤
 * │23│24│25│26│27│28│29│30│31│32│33│34│
 * ├──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┤
 * │12│13│14│15│16│17│18│19│20│21│22│47│
 * ├──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┼──┤
 * │00│01│02│03│04│05│06│07│08│09│10│11│
 * └──┴──┴──┴──┴──┴──┴──┴──┴──┴──┴──┴──┘
 */
led_config_t g_led_config = {
    {   // Key Matrix to LED Index
        {35, 36, 37, 38, 39, 40}, // R1: Left
        {23, 24, 25, 26, 27, 28}, // R2: Left
        {12, 13, 14, 15, 16, 17}, // R3: Left
        { 0,  1,  2,  9, 10, 11}, // R4: 1-3, 10-12
        {41, 42, 43, 44, 45, 46}, // R1: Right
        {29, 30, 31, 32, 33, 34}, // R2: Right
        {18, 19, 20, 21, 22, 47}, // R3: Right
        { 6,  7,  8,  3,  4,  5}, // R4: 7-9, 4-6
    }, {// LED Index to Physical Position
        // R4: 12 leds
        {  0, 64}, { 20, 64}, { 41, 64}, { 61, 64}, { 81, 64}, {102, 64},
        {122, 64}, {143, 64}, {163, 64}, {183, 64}, {204, 64}, {224, 64},
        // R3: 11 leds (last one in this row is the last LED)
        {  0, 43}, { 20, 43}, { 41, 43}, { 61, 43}, { 81, 43}, {102, 43},
        {122, 43}, {143, 43}, {163, 43}, {183, 43}, {204, 43},
        // R2: 12 leds
        {  0, 21}, { 20, 21}, { 41, 21}, { 61, 21}, { 81, 21}, {102, 21},
        {122, 21}, {143, 21}, {163, 21}, {183, 21}, {204, 21}, {224, 21},
        // R1: 12 leds
        {  0,  0}, { 20,  0}, { 41,  0}, { 61,  0}, { 81,  0}, {102,  0},
        { 122, 0}, {143,  0}, {163,  0}, {183,  0}, {204,  0}, {224,  0},
        // Last led: right most R3
        {224, 43}
    }, {// LED Index to Flag (4: regular key, 1: modifier)
        4, 4, 4, 1, 1, 1, 1, 1, 1, 4, 4, 4,
        4, 4, 4, 4, 4, 1, 1, 4, 4, 4, 4,
        4, 4, 4, 4, 4, 1, 1, 4, 4, 4, 4, 4,
        4, 4, 4, 4, 4, 1, 1, 4, 4, 4, 4, 4, 4
    }
};
int board_left[24] = {
     0,  1,  2,  3,  4,  5,
    12, 13, 14, 15, 16, 17,
    23, 24, 25, 26, 27, 28,
    35, 36, 37, 38, 39, 40};
int board_right[24] = {
     6,  7,  8,  9, 10, 11,
    18, 19, 20, 21, 22, 47,
    29, 30, 31, 32, 33, 34,
    41, 42, 43, 44, 45, 46};
// Sided color-setting
void keylight_set_left(uint8_t red, uint8_t green, uint8_t blue) {
    for (int i = 0; i < 24; i++) {
        rgb_matrix_set_color(board_left[i], red, green, blue);
    }
}
void keylight_set_right(uint8_t red, uint8_t green, uint8_t blue) {
    for (int i = 0; i < 24; i++) {
        rgb_matrix_set_color(board_right[i], red, green, blue);
    }
}
// End of differentiations
#endif

// End of code for the RGB_MATRIX setup
#endif
