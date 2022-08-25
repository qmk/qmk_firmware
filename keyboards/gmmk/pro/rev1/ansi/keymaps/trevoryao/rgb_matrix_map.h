/* Copyright 2022 gourdo1 <gourdo1@outlook.com>
   Copyright 2022 Trevor J Yao @trevoryao

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

#include QMK_KEYBOARD_H

// colour layers
// when hit end of the colour layers, go to rainbow effect, and then cycle
static const RGB COLOUR_LAYERS[] = {
    { .r = 0x81, .g = 0xD8, .b = 0xD0 }, // teal
    { .r = 0xFF, .g = 0xFF, .b = 0xFF }, // white
    { .r = 0xFF, .g = 0x00, .b = 0x8C }  // pink
};

void init_colour_layer(void);
void step_colour_layer(void);
void reverse_colour_layer(void);

void indicator_set(int index);

// RGB LED locations
enum led_location_map {
    LED_ESC, // 0, ESC, k13
    LED_GRV, // 1, ~, k16
    LED_TAB, // 2, Tab, k11
    LED_CAPS, // 3, Caps, k21
    LED_LSFT, // 4, L_SFT, k00
    LED_LCTL, // 5, L_CTL, k06
    LED_F1, // 6, F1, k26
    LED_1, // 7, 1, k17
    LED_Q, // 8, Q, k10
    LED_A, // 9, A, k12
    LED_Z, // 10, Z, k14
    LED_LOPT, // 11, L_OPT, k90
    LED_F2, // 12, F2, k36
    LED_2, // 13, 2, k27
    LED_W, // 14, W, k20
    LED_S, // 15, S, k22
    LED_X, // 16, X, k24
    LED_LCMD, // 17, L_CMD, k93
    LED_F3, // 18, F3, k31
    LED_3, // 19, 3, k37
    LED_E, // 20, E, k30
    LED_D, // 21, D, k32
    LED_C, // 22, C, k34
    LED_F4, // 23, F4, k33
    LED_4, // 24, 4, k47
    LED_R, // 25, R, k40
    LED_F, // 26, F, k42
    LED_V, // 27, V, k44
    LED_F5, // 28, F5, k07
    LED_5, // 29, 5, k46
    LED_T, // 30, T, k41
    LED_G, // 31, G, k43
    LED_B, // 32, B, k45
    LED_SPC, // 33, SPACE, k94
    LED_F6, // 34, F6, k63
    LED_6, // 35, 6, k56
    LED_Y, // 36, Y, k51
    LED_H, // 37, H, k53
    LED_N, // 38, N, k55
    LED_F7, // 39, F7, k71
    LED_7, // 40, 7, k57
    LED_U, // 41, U, k50
    LED_J, // 42, J, k52
    LED_M, // 43, M, k54
    LED_F8, // 44, F8, k76
    LED_8, // 45, 8, k67
    LED_I, // 46, I, k60
    LED_K, // 47, K, k62
    LED_COMM, // 48, ,, k64
    LED_FN, // 49, FN, k95
    LED_F9, // 50, F9, ka6
    LED_9, // 51, 9, k77
    LED_O, // 52, O, k70
    LED_L, // 53, L, k72
    LED_DOT, // 54, ., k74
    LED_RCMD, // 55, R_CMD, k92
    LED_F10, // 56, F10, ka7
    LED_0, // 57, 0, k87
    LED_P, // 58, P, k80
    LED_SCLN, // 59, ;, k82
    LED_SLSH, // 60, ?, k85
    LED_F11, // 61, F11, ka3
    LED_MINS, // 62, -, k86
    LED_LBRC, // 63, [, k81
    LED_QUOT, // 64, ", k83
    LED_RCTL, // 65, R_CTL, k04
    LED_F12, // 66, F12, ka5
    LED_L1, // 67, LED, l01
    LED_R1, // 68, LED, l11
    LED_F13, // 69, F13/Print Screen, k97
    LED_L2, // 70, LED, l02
    LED_R2, // 71, LED, l12
    LED_DEL, // 72, Del, k65
    LED_L3, // 73, LED, l03
    LED_R3, // 74, LED, l13
    LED_POWER, // 75, Power, k15
    LED_L4, // 76, LED, l04
    LED_R4, // 77, LED, l14
    LED_EQL, // 78, =, k66
    LED_RIGHT, // 79, Right, k05
    LED_L5, // 80, LED, l05
    LED_R5, // 81, LED, l15
    LED_LNDN, // 82, Line Down, k75
    LED_L6, // 83, LED, l06
    LED_R6, // 84, LED, l16
    LED_BSPC, // 85, BSpc, ka1
    LED_LNUP, // 86, Line Up, k25
    LED_L7, // 87, LED, l07
    LED_R7, // 88, LED, l17
    LED_RBRC, // 89, ], k61
    LED_RSFT, // 90, R_SFT, k91
    LED_L8, // 91, LED, l08
    LED_R8, // 92, LED, l18
    LED_BSLS, // 93, \, ka2
    LED_UP, // 94, Up, k35
    LED_LEFT, // 95, Left, k03
    LED_ENT, // 96, Enter, ka4
    LED_DOWN // 97, Down, k73
};

static const uint8_t LED_LIST_FUNCROW[] = {
    LED_ESC,
    LED_F1,
    LED_F2,
    LED_F3,
    LED_F4,
    LED_F5,
    LED_F6,
    LED_F7,
    LED_F8,
    LED_F9,
    LED_F10,
    LED_F11,
    LED_F12,
    LED_F13
};

static const uint8_t LED_LIST_NUMROW[] = {
    LED_GRV,
    LED_1,
    LED_2,
    LED_3,
    LED_4,
    LED_5,
    LED_6,
    LED_7,
    LED_8,
    LED_9,
    LED_0,
    LED_MINS,
    LED_EQL,
    LED_BSPC,
    LED_DEL
};

static const uint8_t LED_LIST_LETTERS[] = {
    LED_Q,
    LED_W,
    LED_E,
    LED_R,
    LED_T,
    LED_Y,
    LED_U,
    LED_I,
    LED_O,
    LED_P,
    LED_A,
    LED_S,
    LED_D,
    LED_F,
    LED_G,
    LED_H,
    LED_J,
    LED_K,
    LED_L,
    LED_Z,
    LED_X,
    LED_C,
    LED_V,
    LED_B,
    LED_N,
    LED_M
};

static const uint8_t LED_SIDE_LEFT[] = {
    LED_L1,
    LED_L2,
    LED_L3,
    LED_L4,
    LED_L5,
    LED_L6,
    LED_L7,
    LED_L8
};

static const uint8_t LED_SIDE_RIGHT[] = {
    LED_R1,
    LED_R2,
    LED_R3,
    LED_R4,
    LED_R5,
    LED_R6,
    LED_R7,
    LED_R8
};

static const uint8_t LED_SIDE[] = {
    LED_L1,
    LED_L2,
    LED_L3,
    LED_L4,
    LED_L5,
    LED_L6,
    LED_L7,
    LED_L8,
    LED_R1,
    LED_R2,
    LED_R3,
    LED_R4,
    LED_R5,
    LED_R6,
    LED_R7,
    LED_R8
};

static const uint8_t LED_MAIN[] = {
    LED_ESC,
    LED_GRV,
    LED_TAB,
    LED_CAPS,
    LED_LSFT,
    LED_LCTL,
    LED_F1,
    LED_1,
    LED_Q,
    LED_A,
    LED_Z,
    LED_LOPT,
    LED_F2,
    LED_2,
    LED_W,
    LED_S,
    LED_X,
    LED_LCMD,
    LED_F3,
    LED_3,
    LED_E,
    LED_D,
    LED_C,
    LED_F4,
    LED_4,
    LED_R,
    LED_F,
    LED_V,
    LED_F5,
    LED_5,
    LED_T,
    LED_G,
    LED_B,
    LED_SPC,
    LED_F6,
    LED_6,
    LED_Y,
    LED_H,
    LED_N,
    LED_F7,
    LED_7,
    LED_U,
    LED_J,
    LED_M,
    LED_F8,
    LED_8,
    LED_I,
    LED_K,
    LED_COMM,
    LED_FN,
    LED_F9,
    LED_9,
    LED_O,
    LED_L,
    LED_DOT,
    LED_RCMD,
    LED_F10,
    LED_0,
    LED_P,
    LED_SCLN,
    LED_SLSH,
    LED_F11,
    LED_MINS,
    LED_LBRC,
    LED_QUOT,
    LED_RCTL,
    LED_F12,
    LED_F13,
    LED_DEL,
    LED_POWER,
    LED_EQL,
    LED_RIGHT,
    LED_LNDN,
    LED_BSPC,
    LED_LNUP,
    LED_RBRC,
    LED_RSFT,
    LED_BSLS,
    LED_UP,
    LED_LEFT,
    LED_ENT,
    LED_DOWN
};
