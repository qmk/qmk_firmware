/*
Copyright 2012,2013 Jun Wako <wakojun@gmail.com>

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

#include "quantum.h"

#ifdef LED_MATRIX_ENABLE
const is31_led PROGMEM g_is31_leds[LED_MATRIX_LED_COUNT] = {
// The numbers in the comments are the led numbers DXX on the PCB
/* Refer to IS31 manual for these locations
 *  driver
 *  |   LED address
 *  |   | */
//     1            2            3            4            5            6            7            8            9            10           11           12           13           14           15           16
  { 0, C1_1 }, { 0, C1_2 }, { 0, C1_3 }, { 0, C1_4 }, { 0, C1_5 }, { 0, C1_6 }, { 0, C1_7 }, { 0, C1_8 }, { 0, C2_1 }, { 0, C2_2 }, { 0, C2_3 }, { 0, C2_4 }, { 0, C2_5 }, { 0, C2_6 }, { 0, C2_7 }, { 0, C2_8 },
//     17           18           19           20           21           22           23           24           25           26           27           28           29           30           31
  { 0, C3_1 }, { 0, C3_2 }, { 0, C3_3 }, { 0, C3_4 }, { 0, C3_5 }, { 0, C3_6 }, { 0, C3_7 }, { 0, C3_8 }, { 0, C4_1 }, { 0, C4_2 }, { 0, C4_3 }, { 0, C4_4 }, { 0, C4_5 }, { 0, C4_6 }, { 0, C4_7 },
//     32           33           34           35           36           37           38           39           40           41           42           43           44           45           46
  { 0, C4_8 }, { 0, C5_1 }, { 0, C5_2 }, { 0, C5_3 }, { 0, C5_4 }, { 0, C5_5 }, { 0, C5_6 }, { 0, C5_7 }, { 0, C5_8 }, { 0, C6_1 }, { 0, C6_2 }, { 0, C6_3 }, { 0, C6_4 }, { 0, C6_5 }, { 0, C6_6 },
//     47           48           49           50           51           52           53           54           55           56           57           58           59           60           61
  { 0, C6_7 }, { 0, C6_8 }, { 0, C7_1 }, { 0, C7_2 }, { 0, C7_3 }, { 0, C7_4 }, { 0, C7_5 }, { 0, C7_6 }, { 0, C7_7 }, { 0, C7_8 }, { 0, C8_1 }, { 0, C8_2 }, { 0, C8_3 }, { 0, C8_4 }, { 0, C8_5 },
//     62           63           64                                                  65                                     66           67           68           69           70           71
  { 0, C8_6 }, { 0, C8_7 }, { 0, C8_8 },                                        { 0, C9_1 },                           { 0, C9_2 }, { 0, C9_3 }, { 0, C9_4 }, { 0, C9_5 }, { 0, C9_6 }, { 0, C9_7 },
};

led_config_t g_led_config = {
    {
      // Key Matrix to LED Index
      {      0,      1,      2,      3,      4,      5,      6,      7,      8 },
      {      9,     10,     11,     12,     13,     14,     15,     16,     17 },
      {     18,     19,     20,     21,     22,     23,     24,     25,     26 },
      {     27,     28,     29,     30,     31,     32,     33,     34,     35 },
      {     36,     37,     38,     39,     40,     41,     42,     43,     44 },
      {     45,     46,     47,     48,     49,     50,     51,     52,     53 },
      {     54,     55,     56,     57,     58,     59,     60,     61,     62 },
      {     63,     64,     65,     66,     67,     68,     69,     70, NO_LED },
    }, {
      // LED Index to Physical Position
      {   0,  0 }, {  15,  0 }, {  30,  0 }, {  45,  0 }, {  60,  0 }, {  75,  0 }, {  90,  0 }, { 105,  0 }, { 119,  0 }, { 134,  0 }, { 149,  0 }, { 164,  0 }, { 179,  0 }, { 194,  0 }, { 209,  0 }, { 224,  0 },
      {   4, 16 }, {  22, 16 }, {  37, 16 }, {  52, 16 }, {  67, 16 }, {  82, 16 }, {  97, 16 }, { 112, 16 }, { 127, 16 }, { 142, 16 }, { 157, 16 }, { 172, 16 }, { 187, 16 }, { 205, 16 }, { 224, 16 },
      {   6, 32 }, {  26, 32 }, {  41, 32 }, {  56, 32 }, {  71, 32 }, {  86, 32 }, { 101, 32 }, { 116, 32 }, { 131, 32 }, { 146, 32 }, { 161, 32 }, { 175, 32 }, { 190, 32 }, { 207, 32 }, { 224, 32 },
      {   2, 48 }, {  19, 48 }, {  34, 48 }, {  49, 48 }, {  63, 48 }, {  78, 48 }, {  93, 48 }, { 108, 48 }, { 123, 48 }, { 138, 48 }, { 153, 48 }, { 168, 48 }, { 189, 48 }, { 209, 48 }, { 224, 48 },
      {   2, 64 }, {  21, 64 }, {  39, 64 },                                        {  95, 64 },                           { 149, 64 }, { 164, 64 }, { 179, 64 }, { 194, 64 }, { 209, 64 }, { 224, 64 }
    }, {
      // LED Index to Flag
      1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,
      1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 1,
      1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 1,
      1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 1, 1,
      1, 1, 1,          1,       1, 1, 1, 1, 1, 1,
    }
};
#endif

void keyboard_pre_init_kb(void) {
#ifdef LED_MATRIX_ENABLE
    // Turn on LED controller
    setPinOutput(B16);
    writePinHigh(B16);
#endif
    keyboard_pre_init_user();
}

void matrix_init_kb(void) {
    // put your keyboard start-up code here
    // runs once when the firmware starts up

#ifdef LED_MATRIX_ENABLE
    /*
     * Since K20x is stuck with a 32 byte EEPROM (see tmk_core/common/chibios/eeprom_teensy.c),
     * and neither led_matrix_eeconfig.speed or .flags fit in this boundary, just force their values to default on boot.
     */
    led_matrix_set_speed(LED_MATRIX_DEFAULT_SPD),
    led_matrix_set_flags(LED_FLAG_ALL);
#endif

    matrix_init_user();
}
