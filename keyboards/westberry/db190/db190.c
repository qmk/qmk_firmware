/* Copyright (C) 2023 Westberry Technology Corp., Ltd
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

#include QMK_KEYBOARD_H
#include "wb32_driver.h"

#ifdef RGB_MATRIX_ENABLE

const wbrgb_led g_wbrgb_leds[RGB_MATRIX_LED_COUNT] = {
   { RS_ROW1, RS_COL0 }, //  0 ESC
   { RS_ROW2, RS_COL0 }, //  1 F1
   { RS_ROW3, RS_COL0 }, //  2 F2
   { RS_ROW4, RS_COL0 }, //  3 F3
   { RS_ROW5, RS_COL0 }, //  4 F4
   { RS_ROW6, RS_COL0 }, //  5 F5
   { RS_ROW7, RS_COL0 }, //  6 F6
   { RS_ROW8, RS_COL0 }, //  7 F7
   { RS_ROW9, RS_COL0 }, //  8 F8
   {RS_ROW10, RS_COL0 }, //  9 F9
   {RS_ROW11, RS_COL0 }, // 10 F10
   {RS_ROW12, RS_COL0 }, // 11 F11
   {RS_ROW13, RS_COL0 }, // 12 F12
   {RS_ROW14, RS_COL0 }, // 13 DEL

   { RS_ROW0, RS_COL0 }, // 14 ~
   { RS_ROW1, RS_COL1 }, // 15 1
   { RS_ROW2, RS_COL1 }, // 16 2
   { RS_ROW3, RS_COL1 }, // 17 3
   { RS_ROW4, RS_COL1 }, // 18 4
   { RS_ROW5, RS_COL1 }, // 19 5
   { RS_ROW6, RS_COL1 }, // 20 6
   { RS_ROW7, RS_COL1 }, // 21 7
   { RS_ROW8, RS_COL1 }, // 22 8
   { RS_ROW9, RS_COL1 }, // 23 9
   {RS_ROW10, RS_COL1 }, // 24 0
   {RS_ROW11, RS_COL1 }, // 25 -
   {RS_ROW12, RS_COL1 }, // 26 =
   {RS_ROW15, RS_COL0 }, // 27 Backspace
   {RS_ROW16, RS_COL0 }, // 28 PGUP

   { RS_ROW0, RS_COL1 }, // 29 tab
   { RS_ROW1, RS_COL2 }, // 30 Q
   { RS_ROW2, RS_COL2 }, // 31 W
   { RS_ROW3, RS_COL2 }, // 32 E
   { RS_ROW4, RS_COL2 }, // 33 R
   { RS_ROW5, RS_COL2 }, // 34 T
   { RS_ROW6, RS_COL2 }, // 35 Y
   { RS_ROW7, RS_COL2 }, // 36 U
   { RS_ROW8, RS_COL2 }, // 37 I
   { RS_ROW9, RS_COL2 }, // 38 O
   {RS_ROW10, RS_COL2 }, // 39 P
   {RS_ROW11, RS_COL2 }, // 40 [
   {RS_ROW13, RS_COL1 }, // 41 ]
   {RS_ROW14, RS_COL1 }, // 42 KC_BSLS
   {RS_ROW15, RS_COL1 }, // 43 PGDN

   { RS_ROW0, RS_COL2 }, // 44 Caps Lock
   { RS_ROW1, RS_COL3 }, // 45 A
   { RS_ROW2, RS_COL3 }, // 46 S
   { RS_ROW3, RS_COL3 }, // 47 D
   { RS_ROW4, RS_COL3 }, // 48 F
   { RS_ROW5, RS_COL3 }, // 49 G
   { RS_ROW6, RS_COL3 }, // 50 H
   { RS_ROW7, RS_COL3 }, // 51 J
   { RS_ROW8, RS_COL3 }, // 52 K
   { RS_ROW9, RS_COL3 }, // 53 L
   {RS_ROW10, RS_COL3 }, // 54 ;
   {RS_ROW12, RS_COL2 }, // 55 '
   {RS_ROW13, RS_COL2 }, // 56 Enter
   {RS_ROW16, RS_COL1 }, // 57 HOME

   { RS_ROW0, RS_COL3 }, // 58 L_Shift
   { RS_ROW3, RS_COL4 }, // 59 Z
   { RS_ROW4, RS_COL4 }, // 60 X
   { RS_ROW5, RS_COL4 }, // 61 C
   { RS_ROW6, RS_COL4 }, // 62 V
   { RS_ROW7, RS_COL4 }, // 63 B
   { RS_ROW9, RS_COL4 }, // 64 N
   {RS_ROW10, RS_COL4 }, // 65 M
   {RS_ROW11, RS_COL4 }, // 66 ,
   {RS_ROW12, RS_COL4 }, // 67 .
   {RS_ROW11, RS_COL3 }, // 68 /
   {RS_ROW14, RS_COL2 }, // 69 R_Shift
   {RS_ROW15, RS_COL2 }, // 70 UP

   { RS_ROW0, RS_COL4 }, // 71 L_Ctrl
   { RS_ROW1, RS_COL4 }, // 72 Opt
   { RS_ROW2, RS_COL4 }, // 73 L_WIN
   { RS_ROW8, RS_COL4 }, // 74 Space
   {RS_ROW13, RS_COL4 }, // 75 R_WIN
   {RS_ROW14, RS_COL4 }, // 76 FN
   {RS_ROW12, RS_COL3 }, // 77 R_Ctrl
   {RS_ROW13, RS_COL3 }, // 78 LEFT
   {RS_ROW14, RS_COL3 }, // 79 DOWN
   {RS_ROW16, RS_COL2 }  // 80 RIGHT
};

// clang-format on
#endif

void matrix_init_kb(void) {
#ifdef BOOTMAGIC_LITE
    rgb_driver_init();
#endif
    matrix_init_user();
}
