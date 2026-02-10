/* Copyright 2023 @ Keychron (https://www.keychron.com)
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

#include "quantum.h"

#ifdef LED_MATRIX_ENABLE
// clang-format off
const snled27351_led_t PROGMEM g_snled27351_leds[LED_MATRIX_LED_COUNT] = {
/* Refer to SNLED27351 manual for these locations
 *   driver
 *   |  LED address
 *   |  |   */
    {0, CB6_CA1 },
    {0, CB6_CA2 },
    {0, CB6_CA3 },
    {0, CB6_CA4 },
    {0, CB6_CA5 },
    {0, CB6_CA6 },
    {0, CB5_CA1 },
    {0, CB5_CA2 },
    {0, CB5_CA3 },
    {0, CB5_CA4 },
    {0, CB5_CA5 },
    {0, CB5_CA6 },
    {0, CB5_CA7 },
    {0, CB4_CA1 },
    {0, CB4_CA2 },
    {0, CB4_CA3 },
    {0, CB4_CA4 },
    {0, CB4_CA5 },
    {0, CB4_CA6 },
    {0, CB3_CA1 },
    {0, CB3_CA2 },
    {0, CB3_CA3 },
    {0, CB3_CA4 },
    {0, CB3_CA5 },
    {0, CB3_CA6 },
    {0, CB2_CA1 },
    {0, CB2_CA3 },
    {0, CB2_CA4 },
    {0, CB2_CA5 },
    {0, CB2_CA6 },
    {0, CB1_CA1 },
    {0, CB1_CA3 },
    {0, CB1_CA4 },
    {0, CB1_CA5 },
};
#endif
