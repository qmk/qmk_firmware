/* Copyright 2020 joshajohnson 2021 peepeetee
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

#include "hub20.h"


#ifdef RGB_MATRIX_ENABLE
led_config_t g_led_config = { {
    // Key Matrix to LED Index
    {NO_LED,NO_LED,NO_LED,NO_LED},
    { 7,      8,      9,     10},
    { 11,    12,     13,     14},
    { 15,    16,     17,     18},
    { 19,    20,     21,     22},
    { 23,    24,     25,     26}
    //todo: assign leds to keys differently for the different layouts
}, {
    // LED Index to Physical Position
    { 190, 50}, { 111, 50}, { 35, 50}, {38, 0}, {38, 35}, {186, 35}, {186, 0}, // UNDERGLOW
    //todo: underglow location needs to be recalculated. The top row is above row 4, and for now they have the same y value 0
    {  0,  0}, {75,  0}, {150,  0}, {225,  0}, // row 4
    {  0, 16}, {75, 16}, {150, 16}, {225, 16}, // row 3
    {  0, 32}, {75, 32}, {150, 32}, {225, 32}, // row 2
    {  0, 48}, {75, 48}, {150, 48}, {225, 48}, // row 1
    {  0, 64}, {75, 64}, {150, 64}, {225, 64}  // row 0

}, {
    // LED Index to Flag
    LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW,  // UNDERGLOW
    LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,           // row 4
    LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,           // row 3
    LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,           // row 2
    LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,           // row 1
    LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT            // row 0

} };
#endif



// #if LED_MERGE_NUMPAD_LEFT_HANDED_ENTER && LED_MERGE_NUMPAD_RIGHT_HANDED_ZERO
// #error lower left enter conflicts with lower left zero
// #endif

// #if LED_MERGE_NUMPAD_RIGHT_HANDED_ENTER && LED_MERGE_NUMPAD_LEFT_HANDED_ZERO
// #error lower right enter conflicts with lower right zero
// #endif

//     /* LAYOUT_left_handed


//      *     ┌───┬───┐
//      *     │01 │02 │
//      * ┌───┼───┼───┼───┐
//      * │10 │11 │12 │13 │
//      * ├───┼───┼───┼───┤
//      * │   │21 │22 │23 │
//      * │20 ├───┼───┼───┤
//      * │   │31 │32 │33 │
//      * ├───┼───┼───┼───┤
//      * │   │41 │42 │43 │
//      * │40 ├───┼───┴───┤
//      * │   │51 │  52   │
//      * └───┴───┴───────┘
//      */

// #ifndef LED_MERGE_NUMPAD_LEFT_HANDED_PLUS //key 20
// #define LED_MERGE_NUMPAD_LEFT_HANDED_PLUS FALSE
// #endif // LED_MERGE_NUMPAD_LEFT_HANDED_PLUS

// #ifndef LED_MERGE_NUMPAD_LEFT_HANDED_ENTER //key 40
// #define LED_MERGE_NUMPAD_LEFT_HANDED_ENTER FALSE
// #endif // LED_MERGE_NUMPAD_LEFT_HANDED_ENTER

// #ifndef LED_MERGE_NUMPAD_LEFT_HANDED_ZERO //key 52
// #define LED_MERGE_NUMPAD_LEFT_HANDED_ZERO FALSE
// #endif // LED_MERGE_NUMPAD_LEFT_HANDED_ZERO


//     /* LAYOUT_right_handed


//      *     ┌───┬───┐
//      *     │01 │02 │
//      * ┌───┼───┼───┼───┐
//      * │10 │11 │12 │13 │
//      * ├───┼───┼───┼───┤
//      * │20 │21 │22 │   │
//      * ├───┼───┼───┤23 │
//      * │30 │31 │32 │   │
//      * ├───┼───┼───┼───┤
//      * │40 │41 │42 │   │
//      * ├───┴───┼───┤43 │
//      * │  50   │52 │   │
//      * └───────┴───┴───┘
//      */
//         //LOCATION OF bottom row 0 NOT TESTED, WAITING ENDORSEMENT FROM MANUFACTURER

// #ifndef LED_MERGE_NUMPAD_RIGHT_HANDED_PLUS // key 23
// #define LED_MERGE_NUMPAD_RIGHT_HANDED_PLUS FALSE
// #endif // LED_MERGE_NUMPAD_RIGHT_HANDED_PLUS

// #ifndef LED_MERGE_NUMPAD_RIGHT_HANDED_ENTER // key 43
// #define LED_MERGE_NUMPAD_RIGHT_HANDED_ENTER FALSE
// #endif // LED_MERGE_NUMPAD_RIGHT_HANDED_ENTER

// #ifndef LED_MERGE_NUMPAD_RIGHT_HANDED_ZERO // key 50 (confirm with manufacturer)
// #define LED_MERGE_NUMPAD_RIGHT_HANDED_ZERO FALSE
// #endif // LED_MERGE_NUMPAD_RIGHT_HANDED_ZERO

// uint8_t rgb_matrix_map_row_column_to_led_kb(uint8_t row, uint8_t column, uint8_t *led_i) {
// // Keys here have 2 leds. Here we add the led that is not bound to the key
// // and the default led would be added
// // by the default code that runs after this in rgb_matrix_map_row_column_to_led

// uint8_t counter = 0;

// #if LED_MERGE_NUMPAD_LEFT_HANDED_PLUS //key 20, leds 7 and 11, 7 already bound

//     if (row == 2 && column == 0) {
//         led_i[counter] = 11;
//         counter ++;
//     }
// #endif
// #if LED_MERGE_NUMPAD_LEFT_HANDED_ENTER //key 40, leds 19 and 23, 23 already bound
//     if (row == 4 && column == 0) {
//         led_i[counter] = 23;
//         counter ++;
//     }
// #endif
// #if LED_MERGE_NUMPAD_LEFT_HANDED_ZERO //key 52, leds 25 and 26, 26 already bound
//     if (row == 5 && column == 2) {
//         led_i[counter] = 26;
//         counter ++;
//     }
// #endif

// #if LED_MERGE_NUMPAD_RIGHT_HANDED_PLUS // key 23, led 14 and 18, 14 already bound
//     if (row == 2 && column == 3) {
//         led_i[counter] = 18;
//         counter ++;
//     }
// #endif
// #if LED_MERGE_NUMPAD_RIGHT_HANDED_ENTER // key 43, led 22 and 26, 22 already bound
//     if (row == 4 && column == 3) {
//         led_i[counter] = 26;
//         counter ++;
//     }
// #endif
// #if LED_MERGE_NUMPAD_RIGHT_HANDED_ZERO  // key 50 (confirm with manufacturer)
// // LED 23 and 24, 23(?) already bound
//     if (row == 5 && column == 0) {
//         led_i[counter] = 24;
//         counter ++;
//     }
// #endif
//     return counter;
// }
