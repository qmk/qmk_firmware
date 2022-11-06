/* Copyright 2022
 * GEIST @geigeigeist
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

#include "klor.h"


//#ifdef HAPTIC_ENABLE
//#include "drivers/haptic/DRV2605L.h"
//#endif //HAPTIC ENABLE


#ifdef SWAP_HANDS_ENABLE

__attribute__ ((weak))
const keypos_t PROGMEM hand_swap_config[MATRIX_ROWS][MATRIX_COLS] =
    // The LAYOUT macro could work for this, but it was harder to figure out the
    // identity using it.

    // This is the identity layout.
/*
{ \
 { {1, 0}, {2, 0}, {3, 0}, {4, 0}, {5, 0} }, \
 { {0, 1}, {1, 1}, {2, 1}, {3, 1}, {4, 1}, {5, 1} }, \
 { {0, 2}, {1, 2}, {2, 2}, {3, 2}, {4, 2}, {5, 2} }, \
 { {1, 3}, {2, 3}, {3, 3}, {4, 3}, {5, 3} }, \
    \
 { {1, 5}, {2, 5}, {3, 5}, {4, 5}, {5, 5} }, \
 { {0, 6}, {1, 6}, {2, 6}, {3, 6}, {4, 6}, {5, 6} }, \
 { {0, 7}, {1, 7}, {2, 7}, {3, 7}, {4, 7}, {5, 7} }, \
 { {1, 8}, {2, 8}, {3, 8}, {4, 8}, {5, 8} }, \
};
*/

    // This is the mirror, q <-> p, w <-> o, etc...
{ \
 {         {1, 5}, {2, 5}, {3, 5}, {4, 5}, {5, 5} }, \
 { {0, 6}, {1, 6}, {2, 6}, {3, 6}, {4, 6}, {5, 6} }, \
 { {0, 7}, {1, 7}, {2, 7}, {3, 7}, {4, 7}, {5, 7} }, \
 {         {1, 8}, {2, 8}, {3, 8}, {4, 8}, {5, 8} }, \
                                                     \
 {         {1, 0}, {2, 0}, {3, 0}, {4, 0}, {5, 0} }, \
 { {0, 1}, {1, 1}, {2, 1}, {3, 1}, {4, 1}, {5, 1} }, \
 { {0, 2}, {1, 2}, {2, 2}, {3, 2}, {4, 2}, {5, 2} }, \
 {         {1, 3}, {2, 3}, {3, 3}, {4, 3}, {5, 3} }, \
};

#endif //SWAP_HANDS_ENABLE





#ifdef RGB_MATRIX_ENABLE

// Physical layout ────────────────────────────────────────────────────
//
//    ┌────────────────────┐                 ┌────────────────────┐
//    │ 18  13  12  06  05 │                 │ 26  27  33  34  39 │
//┌───┴────────────────────┤                 ├────────────────────┴───┐
//│ 20  17  14  11  07  04 │                 │ 25  28  32  35  38  40 │
//├────────────────────────┤                 ├────────────────────────┤
//│ 19  16  15  10  08  03 │                 │ 24  29  31  36  37  41 │
//└───────────────┬────────┴───────┐ ┌───────┴────────┬───────────────┘
//                │ 09  02  01  00 │ │ 21  22  23  30 │
//                └────────────────┘ └────────────────┘
//
//
// Electrical layout ───────────────────────────────────────
//
// C  00  01  02  03  04  05    06  07  08  09  10  11    R
//      ┌────────────────────┐┌────────────────────┐
//    X │ 18  13  12  06  05 ││ 26  27  33  34  39 │ X   00
//  ┌───┴────────────────────┤├────────────────────┴───┐
//  │ 20  17  14  11  07  04 ││ 25  28  32  35  38  40 │ 01
//  ├────────────────────────┤├────────────────────────┤ 
//  │ 19  16  15  10  08  03 ││ 24  29  31  36  37  41 │ 02
//  └───┬────────────────┬───┘└───┬────────────────┬───┘
//    X │ 09  02  01  00 │ X    X │ 21  22  23  30 │ X   03
//      └────────────────┘        └────────────────┘


// POLYDACTYL / YUBITSUME 
// use this matrix if you use the polydactyl or yubitsume layout ────────────────────────────────────┐

led_config_t g_led_config = { {
//COL   00     01   02   03   04   05       ROW 
    { NO_LED,  18,  13,  12,   6,   5    },//00
    {  19,     17,  14,  11,   7,   4    },//01
    {  20,     16,  15,  10,   8,   3    },//02
    { NO_LED,   9,   2,   1,   0, NO_LED },//03
    { NO_LED,  37,  34,  33,  27,  26    },//00
    {  40,     38,  35,  32,  28,  25    },//01
    {  41,     39,  36,  31,  29,  24    },//02
    { NO_LED,  30,  23,  22,  21, NO_LED } //03
}, {
   //LEFT
   //thumb1 ▼      thumb2 ▼     thumb3 ▼       C0 R3 ▼       C0 R2 ▼       C0 R1 ▼       C1 R1 ▼
    { 102,  63 }, {  89,  54 }, {  74,  49 }, {  75,  34 }, {  75,  21 }, {  75,   8 }, {  60,   6 },
   //C1 R2 ▼       C1 R3 ▼       thumb4 ▼      C2 R3 ▼       C2 R2 ▼       C2 R1 ▼       C3 R1 ▼
    {  60,  19 }, {  60,  32 }, {  58,  48 }, {  46,  25 }, {  46,  12 }, {  46,   0 }, {  29,   7 },
   //C3 R2 ▼       C3 R3 ▼       C4 R3 ▼       C4 R2 ▼       C4 R1 ▼       C5 R2 ▼       C5 R3 ▼
    {  30,  20 }, {  31,  33 }, {  17,  42 }, {  15,  30 }, {  13,  17 }, {   0,  28 }, {   3,  41 }, 
    //RIGHT
   //thumb1 ▼      thumb2 ▼     thumb3 ▼       C0 R3 ▼       C0 R2 ▼       C0 R1 ▼       C1 R1 ▼
    { 122,  63 }, { 135,  54 }, { 150,  49 }, { 149,  34 }, { 149,  21 }, { 149,   8 }, { 163,   6 },
   //C1 R2 ▼       C1 R3 ▼       thumb4 ▼      C2 R3 ▼       C2 R2 ▼       C2 R1 ▼       C3 R1 ▼
    { 163,  19 }, { 163,  32 }, { 166,  48 }, { 178,  25 }, { 178,  12 }, { 178,   0 }, { 195,   7 },
   //C3 R2 ▼       C3 R3 ▼       C4 R3 ▼       C4 R2 ▼       C4 R1 ▼       C5 R2 ▼       C5 R3 ▼
    { 194,  20 }, { 193,  33 }, { 206,  42 }, { 209,  30 }, { 211,  17 }, { 224,  28 }, { 221,  41 }
}, {       
    //LEFT               
    1, 1, 1, 4, 4, 4, 4,
    4, 4, 1, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 1, 1,
    //RIGHT
    1, 1, 1, 4, 4, 4, 4,
    4, 4, 1, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 1, 1
} };
// ────────────────────────────────────────────────────────────────────────────────────────────────────┘


/*
// KONRAD / SAEGEWERK
// use this matrix if you use the konrad or saegewerk layout ──────────────────────────────────────────┐

led_config_t g_led_config = { {
//COL   00     01   02   03   04   05          ROW 
    { NO_LED,  17,  12,  11,   5,   4       },//00
    {  18,     16,  13,  10,   6,   3       },//01
    {  19,     15,  14,   9,   7,   2       },//02
    { NO_LED,   8,   1,   0, NO_LED, NO_LED },//03
    { NO_LED,  38,  33,  32,  26,  25       },//00
    {  39,     37,  34,  31,  27,  24       },//01
    {  40,     36,  35,  30,  28,  23       },//02
    { NO_LED,  29,  22,  21,  20,  NO_LED   } //03
}, {
   //LEFT
   //thumb1 ▼      thumb2 ▼     thumb3 ▼       C0 R3 ▼       C0 R2 ▼       C0 R1 ▼       C1 R1 ▼
                  {  89,  54 }, {  74,  49 }, {  75,  34 }, {  75,  21 }, {  75,   8 }, {  60,   6 },
   //C1 R2 ▼       C1 R3 ▼       thumb4 ▼      C2 R3 ▼       C2 R2 ▼       C2 R1 ▼       C3 R1 ▼
    {  60,  19 }, {  60,  32 }, {  58,  48 }, {  46,  25 }, {  46,  12 }, {  46,   0 }, {  29,   7 },
   //C3 R2 ▼       C3 R3 ▼       C4 R3 ▼       C4 R2 ▼       C4 R1 ▼       C5 R2 ▼       C5 R3 ▼
    {  30,  20 }, {  31,  33 }, {  17,  42 }, {  15,  30 }, {  13,  17 }, {   0,  28 }, {   3,  41 }, 
    //RIGHT
   //thumb1 ▼      thumb2 ▼     thumb3 ▼       C0 R3 ▼       C0 R2 ▼       C0 R1 ▼       C1 R1 ▼
    { 122,  63 }, { 135,  54 }, { 150,  49 }, { 149,  34 }, { 149,  21 }, { 149,   8 }, { 163,   6 },
   //C1 R2 ▼       C1 R3 ▼       thumb4 ▼      C2 R3 ▼       C2 R2 ▼       C2 R1 ▼       C3 R1 ▼
    { 163,  19 }, { 163,  32 }, { 166,  48 }, { 178,  25 }, { 178,  12 }, { 178,   0 }, { 195,   7 },
   //C3 R2 ▼       C3 R3 ▼       C4 R3 ▼       C4 R2 ▼       C4 R1 ▼       C5 R2 ▼       C5 R3 ▼
    { 194,  20 }, { 193,  33 }, { 206,  42 }, { 209,  30 }, { 211,  17 }, { 224,  28 }, { 221,  41 }
}, {       
    //LEFT               
    1, 1, 4, 4, 4, 4,
    4, 4, 1, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 1, 1,
    //RIGHT
    1, 1, 1, 4, 4, 4, 4,
    4, 4, 1, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 1, 1
} };

// ────────────────────────────────────────────────────────────────────────────────────────────────────┘
*/


void suspend_power_down_kb(void) {
    rgb_matrix_set_suspend_state(true);
    suspend_power_down_user();
}

void suspend_wakeup_init_kb(void) {
    rgb_matrix_set_suspend_state(false);
    suspend_wakeup_init_user();
}
#endif //RGB_MATRIX_ENABLE


