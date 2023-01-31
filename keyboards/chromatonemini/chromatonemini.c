/* Copyright 2021 3araht
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

#include "chromatonemini.h"

#ifdef RGB_MATRIX_ENABLE
#    define NO_LED 255

led_config_t g_led_config = {
    {
#if 0
        // register bottom two rows
        { 0,   4,  3,  2,  1, 41,  5, NO_LED },
        { 40,  6, 39,  7, 38,  8, 37, NO_LED },
        {  9, 36, 10, 35, 11, 34, 12, NO_LED },
        { 33, 13, 32, 14, 31, 15, 30, NO_LED },
        { 16, 29, 17, 28, 18, 27, 19, NO_LED },
        { 26, 20, 25, 21, 24, 22, 23, NO_LED }

        // register middle two rows
        { 0,   4,  3,  2,  1, 78, 42, NO_LED },
        { 77, 43, 76, 44, 75, 45, 74, NO_LED },
        { 46, 73, 47, 72, 48, 71, 49, NO_LED },
        { 70, 50, 69, 51, 68, 52, 67, NO_LED },
        { 53, 66, 54, 65, 55, 64, 56, NO_LED },
        { 63, 57, 62, 58, 61, 59, 60, NO_LED }

        // register top and bottom rows
        { 0,     4,   3,   2,   1, 115,   5, NO_LED },
        { 114,   6, 113,   7, 112,   8, 111, NO_LED },
        { 9,   110,  10, 109,  11, 108,  12, NO_LED },
        { 107,  13, 106,  14, 105,  15, 104, NO_LED },
        {  16, 103,  17, 102,  18, 101,  19, NO_LED },
        { 100,  20,  99,  21,  98,  22,  97, NO_LED }
#else
        // register top two rows
        { 0,     4,   3,   2,   1, 115,  79, NO_LED },
        { 114,  80, 113,  81, 112,  82, 111, NO_LED },
        { 83,  110,  84, 109,  85, 108,  86, NO_LED },
        { 107,  87, 106,  88, 105,  89, 104, NO_LED },
        {  90, 103,  91, 102,  92, 101,  93, NO_LED },
        { 100,  94,  99,  95,  98,  96,  97, NO_LED }
#endif
    },  {
        { 14,  12 },
        { 14,  36 },
        { 19,  48 }, { 9, 48 },
        { 14,  60 },
        { 39,  60 }, { 49,  60 }, {  59, 60 }, {  69, 60 }, {  79, 60 }, {  89, 60 }, {  99, 60 }, { 109, 60 }, { 119, 60 }, { 129, 60 }, { 139, 60 }, { 149, 60 }, { 159, 60 }, { 169, 60 }, { 179, 60 }, { 189, 60 }, { 199, 60 }, { 209, 60 },
        { 214, 48 }, { 204, 48 }, { 194, 48 }, { 184, 48 }, { 174, 48 }, { 164, 48 }, { 154, 48 }, { 144, 48 }, { 134, 48 }, { 124, 48 }, { 114, 48 }, { 104, 48 }, {  94, 48 }, {  84, 48 }, {  74, 48 }, {  64, 48 }, {  54, 48 }, {  44, 48 }, { 34, 48 },
        { 39,  36 }, { 49,  36 }, {  59, 36 }, {  69, 36 }, {  79, 36 }, {  89, 36 }, {  99, 36 }, { 109, 36 }, { 119, 36 }, { 129, 36 }, { 139, 36 }, { 149, 36 }, { 159, 36 }, { 169, 36 }, { 179, 36 }, { 189, 36 }, { 199, 36 }, { 209, 36 },
        { 214, 24 }, { 204, 24 }, { 194, 24 }, { 184, 24 }, { 174, 24 }, { 164, 24 }, { 154, 24 }, { 144, 24 }, { 134, 24 }, { 124, 24 }, { 114, 24 }, { 104, 24 }, {  94, 24 }, {  84, 24 }, {  74, 24 }, {  64, 24 }, {  54, 24 }, {  44, 24 }, { 34, 24 },
        { 39,  12 }, { 49,  12 }, {  59, 12 }, {  69, 12 }, {  79, 12 }, {  89, 12 }, {  99, 12 }, { 109, 12 }, { 119, 12 }, { 129, 12 }, { 139, 12 }, { 149, 12 }, { 159, 12 }, { 169, 12 }, { 179, 12 }, { 189, 12 }, { 199, 12 }, { 209, 12 },
        { 214,  0 }, { 204,  0 }, { 194,  0 }, { 184,  0 }, { 174,  0 }, { 164,  0 }, { 154,  0 }, { 144,  0 }, { 134,  0 }, { 124,  0 }, { 114,  0 }, { 104,  0 }, {  94,  0 }, {  84,  0 }, {  74,  0 }, {  64,  0} , {  54,  0 }, {  44,  0 }, { 34,  0 }
    },  {
        1,
        4,
        4, 4,
        4,
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4
    }
};

// indicator
const uint8_t led_scale_indicator[12][12] = {
  {23, 29, 35, 41, 60, 66,  72,  78,  97, 103,    109,    115},     //  C
  { 5, 11, 17, 42, 48, 54,  79,  85,  91, NO_LED, NO_LED, NO_LED},  //  C#
  {28, 34, 40, 65, 71, 77, 102, 108, 114, NO_LED, NO_LED, NO_LED},  //  D
  { 6, 12, 18, 43, 49, 55,  80,  86,  92, NO_LED, NO_LED, NO_LED},  //  D#
  {27, 33, 39, 64, 70, 76, 101, 107, 113, NO_LED, NO_LED, NO_LED},  //  E
  { 7, 13, 19, 44, 50, 56,  81,  87,  93, NO_LED, NO_LED, NO_LED},  //  F
  {26, 32, 38, 63, 69, 75, 100, 106, 112, NO_LED, NO_LED, NO_LED},  //  F#
  { 8, 14, 20, 45, 51, 57,  82,  88,  94, NO_LED, NO_LED, NO_LED},  //  G
  {25, 31, 37, 62, 68, 74,  99, 105, 111, NO_LED, NO_LED, NO_LED},  //  G#
  { 9, 15, 21, 46, 52, 58,  83,  89,  95, NO_LED, NO_LED, NO_LED},  //  A
  {24, 30, 36, 61, 67, 73,  98, 104, 110, NO_LED, NO_LED, NO_LED},  //  A#
  {10, 16, 22, 47, 53, 59,  84,  90,  96, NO_LED, NO_LED, NO_LED}   //  B
};

const uint8_t led_single_col_indicator[37][3] = {
  {41, 78, 115},  //  K01  = C1
  { 5, 42,  79},  //  K02  = C#1
  {40, 77, 114},  //  K03  = D1
  { 6, 43,  80},  //  K04  = D#1
  {39, 76, 113},  //  K05  = E1
  { 7, 44,  81},  //  K06  = F1
  {38, 75, 112},  //  K07  = F#1
  { 8, 45,  82},  //  K08  = G1
  {37, 74, 111},  //  K09  = G#1
  { 9, 46,  83},  //  K10  = A1
  {36, 73, 110},  //  K11  = A#1
  {10, 47,  84},  //  K12  = B1
  {35, 72, 109},  //  K13  = C2
  {11, 48,  85},  //  K14  = C#2
  {34, 71, 108},  //  K15  = D2
  {12, 49,  86},  //  K16  = D#2
  {33, 70, 107},  //  K17  = E2
  {13, 50,  87},  //  K18  = F2
  {32, 69, 106},  //  K19  = F#2
  {14, 51,  88},  //  K20  = G2
  {31, 68, 105},  //  K21  = G#2
  {15, 52,  89},  //  K22  = A2
  {30, 67, 104},  //  K23  = A#2
  {16, 53,  90},  //  K24  = B2
  {29, 66, 103},  //  K25  = C3
  {17, 54,  91},  //  K26  = C#3
  {28, 65, 102},  //  K27  = D3
  {18, 55,  92},  //  K28  = D#3
  {27, 64, 101},  //  K29  = E3
  {19, 56,  93},  //  K30  = F3
  {26, 63, 100},  //  K31  = F#3
  {20, 57,  94},  //  K32  = G3
  {25, 62,  99},  //  K33  = G#3
  {21, 58,  95},  //  K34  = A3
  {24, 61,  98},  //  K35  = A#3
  {22, 59,  96},  //  K36  = B3
  {23, 60,  97}   //  K37  = C4
};

#endif  //  RGB_MATRIX_ENABLE

uint8_t shift_led_indicator_left(uint8_t scale_indicator_col){
    if (scale_indicator_col > 0) {
        scale_indicator_col--;
    } else {
        scale_indicator_col = 11;
    }
    return scale_indicator_col;
}

uint8_t shift_led_indicator_right(uint8_t scale_indicator_col){
    if (scale_indicator_col < 11) {
        scale_indicator_col++;
    } else {
        scale_indicator_col = 0;
    }
    return scale_indicator_col;
}

#ifdef ENCODER_ENABLE
#   ifdef ENCODERS
static uint8_t  encoder_state[ENCODERS] = {0};
static keypos_t encoder_cw[ENCODERS]    = ENCODERS_CW_KEY;
static keypos_t encoder_ccw[ENCODERS]   = ENCODERS_CCW_KEY;
#   endif

void encoder_action_unregister(void) {
#   ifdef ENCODERS
    for (int index = 0; index < ENCODERS; ++index) {
        if (encoder_state[index]) {
            keyevent_t encoder_event = (keyevent_t) {
                .key = encoder_state[index] >> 1 ? encoder_cw[index] : encoder_ccw[index],
                .pressed = false,
                .time = (timer_read() | 1)
            };
            encoder_state[index] = 0;
            action_exec(encoder_event);
        }
    }
#   endif
}

void encoder_action_register(uint8_t index, bool clockwise) {
#   ifdef ENCODERS
    keyevent_t encoder_event = (keyevent_t) {
        .key = clockwise ? encoder_cw[index] : encoder_ccw[index],
        .pressed = true,
        .time = (timer_read() | 1)
    };
    encoder_state[index] = (clockwise ^ 1) | (clockwise << 1);
#       ifdef CONSOLE_ENABLE
    uprintf("encoder_action_register index = %u, clockwise = %u, row = %u, col = %u\n", index, clockwise, encoder_event.key.row, encoder_event.key.col);
#       endif
    action_exec(encoder_event);
#   endif
}

void matrix_scan_kb(void) {
    encoder_action_unregister();
    matrix_scan_user();
}

bool encoder_update_kb(uint8_t index, bool clockwise) {
    encoder_action_register(index, clockwise);
    // don't return user actions, because they are in the keymap
    // encoder_update_user(index, clockwise);
    return true;
};

#endif
