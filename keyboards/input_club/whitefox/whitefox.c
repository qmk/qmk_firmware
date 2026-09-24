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
const is31fl3731_led_t PROGMEM g_is31fl3731_leds[IS31FL3731_LED_COUNT] = {
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

void matrix_init_kb(void) {
    /*
     * Since K20x is stuck with a 32 byte EEPROM (see tmk_core/common/chibios/eeprom_teensy.c),
     * and neither led_matrix_eeconfig.speed or .flags fit in this boundary, just force their values to default on boot.
     */
    led_matrix_set_speed(LED_MATRIX_DEFAULT_SPD),
    led_matrix_set_flags(LED_FLAG_ALL);

    matrix_init_user();
}
#endif
