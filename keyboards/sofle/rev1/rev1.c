/* Copyright 2021 Carlos Martins
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

#include "sofle.h"

#ifdef RGB_MATRIX_ENABLE
#define RLO 36
#define LLI(x) (x)
#define LLP(x,y) {(x),(y)}
#define RLI(x) (RLO+(x))
#define RLP(x,y) {(224-(x)),((y))}
  // Physical Layout
  // Columns
  // 0  1  2  3  4  5  6  7  8  9  10 11 12 13
  //                                           ROWS
  // 12 13 22 23 32 33       33 32 23 22 13 12  0
  //    02    03    04       04    03    02
  // 11 14 21 24 31 34       34 31 24 21 14 11  1
  //                01       01
  // 10 15 20 25 30 35       35 30 25 20 15 10  2
  //
  // 09 16 19 26 29 36       36 29 26 19 16 09  3
  //
  //     08 17 18 27 28     28 27 18 17 08      4
  //    07    06    05       05    06    07

led_config_t g_led_config = {
    {
        {  LLI(11),  LLI(12),  LLI(21),  LLI(22),  LLI(31),  LLI(32) },
        {  LLI(10),  LLI(13),  LLI(20),  LLI(23),  LLI(30),  LLI(33) },
        {  LLI(9),  LLI(14),  LLI(19),  LLI(24),  LLI(29),  LLI(34)},
        {  LLI(8),  LLI(15),  LLI(18),  LLI(25),  LLI(28),  LLI(35)},
        {  LLI(7),  LLI(16),  LLI(17),  LLI(26),  LLI(27),  NO_LED },
        {  RLI(11),  RLI(12),  RLI(21),  RLI(22),  RLI(31),  RLI(32)},
        {  RLI(10),  RLI(13),  RLI(20),  RLI(23),  RLI(30),  RLI(33)},
        {  RLI(9),  RLI(14),  RLI(19),  RLI(24),  RLI(29),  RLI(34)},
        {  RLI(8),  RLI(15),  RLI(18),  RLI(25),  RLI(28),  RLI(35)},
        {  RLI(7),  RLI(16),  RLI(17),  RLI(26),  RLI(27), NO_LED }
    },
    {
        // Left side underglow
        LLP(96, 40), LLP(16, 20), LLP(48, 10), LLP(80, 18), LLP(88, 60), LLP(56, 57), LLP(24,60),
        // Left side Matrix
        LLP(32, 57), LLP( 0, 48), LLP( 0, 36), LLP( 0, 24), LLP( 0, 12),
        LLP(16, 12), LLP(16, 24), LLP(16, 36), LLP(16, 48), LLP(48, 55),
        LLP(64, 57), LLP(32, 45), LLP(32, 33), LLP(32, 21), LLP(32,  9),
        LLP(48,  7), LLP(48, 19), LLP(48, 31), LLP(48, 43), LLP(80, 59),
        LLP(96, 64), LLP(64, 45), LLP(64, 33), LLP(64, 21), LLP(64,  9),
        LLP(80, 10), LLP(80, 22), LLP(80, 34), LLP(80, 47),


        // Right side underglow
        RLP(96, 40), RLP(16, 20), RLP(48, 10), RLP(80, 18), RLP(88, 60), RLP(56, 57), RLP(24,60),
        // Right side Matrix
        RLP(32, 57), RLP( 0, 48), RLP( 0, 36), RLP( 0, 24), RLP( 0, 12),
        RLP(16, 12), RLP(16, 24), RLP(16, 36), RLP(16, 48), RLP(48, 55),
        RLP(64, 57), RLP(32, 45), RLP(32, 33), RLP(32, 21), RLP(32,  9),
        RLP(48,  7), RLP(48, 19), RLP(48, 31), RLP(48, 43), RLP(80, 59),
        RLP(96, 64), RLP(64, 45), RLP(64, 33), RLP(64, 21), RLP(64,  9),
        RLP(80, 10), RLP(80, 22), RLP(80, 34), RLP(80, 47),
    },
    {
        LED_FLAG_NONE, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW,
        LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
        LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
        LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
        LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
        LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
        LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
        LED_FLAG_NONE, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW,
        LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
        LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
        LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
        LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
        LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
        LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT
    }
};
#endif
