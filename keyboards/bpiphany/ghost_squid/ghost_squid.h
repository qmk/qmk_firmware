/*
Copyright 2016 Daniel Svensson <dsvensson@gmail.com>

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

#include "quantum.h"

#define fn_led_on() writePinLow(D0)
#define fn_led_off() writePinHigh(D0)

#define  ___ KC_NO

/*
 *              ┌───┐   ┌───┬───┬───┬───┐ ┌───┬───┬───┬───┐ ┌───┬───┬───┬───┐ ┌───┬───┬───┐
 *              │J6 │   │I4 │H4 │H2 │H6 │ │A7 │E6 │D2 │D4 │ │B4 │B7 │B6 │B0 │ │C7 │C5 │A5 │
 *              └───┘   └───┴───┴───┴───┘ └───┴───┴───┴───┘ └───┴───┴───┴───┘ └───┴───┴───┘
 *              ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐ ┌───┬───┬───┐ ┌───┬───┬───┬───┐
 *              │J4 │J7 │I7 │H7 │G7 │G4 │F4 │F7 │E7 │D7 │R7 │R4 │E4 │B2     │ │L4 │O4 │Q4 │ │K1 │L1 │Q1 │Q0 │
 *              ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤ ├───┼───┼───┤ ├───┼───┼───┼───┤      ┌─────┐
 *              │J2   │J5 │I5 │H5 │G5 │G2 │F2 │F5 │E5 │D5 │R5 │R2 │E2 │B3   │ │K4 │O7 │Q7 │ │K5 │L5 │Q5 │O5 │      │     │
 *  2.25u       ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤ └───┴───┴───┘ ├───┼───┼───┤   │   ┌──┴┐B1  │ ISO Enter
 *  LShift      │I2    │J3 │I3 │H3 │G3 │G6 │F6 │F3 │E3 │D3 │R3 │R6 │B1      │               │K2 │L2 │Q2 │   │   │B3 │    │
 * ┌────────┐   ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────────┤     ┌───┐     ├───┼───┼───┼───┤   └───┴────┘
 * │N2      │   │N2  │I6 │J1 │I1 │H1 │G1 │G0 │F0 │F1 │E1 │D1 │R0 │N3        │     │O6 │     │K3 │L3 │Q3 │O3 │
 * └────────┘   ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤ ┌───┼───┼───┐ ├───┴───┼───┤   │
 *              │A4  │P2  │C6  │K6                      │C0  │M3  │D0  │A1  │ │O0 │K0 │L0 │ │L6     │Q6 │   │
 *              └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘ └───┴───┴───┘ └───────┴───┴───┘
 */

#define LAYOUT_fullsize_ansi( \
    KJ6,      KI4, KH4, KH2, KH6, KA7, KE6, KD2, KD4, KB4, KB7, KB6, KB0,   KC7, KC5, KA5,                       \
    KJ4, KJ7, KI7, KH7, KG7, KG4, KF4, KF7, KE7, KD7, KR7, KR4, KE4, KB2,   KL4, KO4, KQ4,   KK1, KL1, KQ1, KQ0, \
    KJ2, KJ5, KI5, KH5, KG5, KG2, KF2, KF5, KE5, KD5, KR5, KR2, KE2, KB3,   KK4, KO7, KQ7,   KK5, KL5, KQ5, KO5, \
    KI2, KJ3, KI3, KH3, KG3, KG6, KF6, KF3, KE3, KD3, KR3, KR6,      KB1,                    KK2, KL2, KQ2,      \
    KN2,      KJ1, KI1, KH1, KG1, KG0, KF0, KF1, KE1, KD1, KR0,      KN3,        KO6,        KK3, KL3, KQ3, KO3, \
    KA4, KP2, KC6,                KK6,                KC0, KM3, KD0, KA1,   KO0, KK0, KL0,   KL6,      KQ6       \
    ) { /*        00-A  01-B  02-C  03-D  04-E  05-F  06-G  07-H  08-I  09-J  10-K  11-L  12-M  13-N  14-O  15-P  16-Q  17-R */ \
        /* 0 */  { ___ , KB0 , KC0 , KD0 , ___ , KF0 , KG0 , ___ , ___ , ___ , KK0 , KL0 , ___ , ___ , KO0 , ___ , KQ0 , KR0 }, \
        /* 1 */  { KA1 , KB1 , ___ , KD1 , KE1 , KF1 , KG1 , KH1 , KI1 , KJ1 , KK1 , KL1 , ___ , ___ , ___ , ___ , KQ1 , ___ }, \
        /* 2 */  { ___ , KB2 , ___ , KD2 , KE2 , KF2 , KG2 , KH2 , KI2 , KJ2 , KK2 , KL2 , ___ , KN2 , ___ , KP2 , KQ2 , KR2 }, \
        /* 3 */  { ___ , KB3 , ___ , KD3 , KE3 , KF3 , KG3 , KH3 , KI3 , KJ3 , KK3 , KL3 , KM3 , KN3 , KO3 , ___ , KQ3 , KR3 }, \
        /* 4 */  { KA4 , KB4 , ___ , KD4 , KE4 , KF4 , KG4 , KH4 , KI4 , KJ4 , KK4 , KL4 , ___ , ___ , KO4 , ___ , KQ4 , KR4 }, \
        /* 5 */  { KA5 , ___ , KC5 , KD5 , KE5 , KF5 , KG5 , KH5 , KI5 , KJ5 , KK5 , KL5 , ___ , ___ , KO5 , ___ , KQ5 , KR5 }, \
        /* 6 */  { ___ , KB6 , KC6 , ___ , KE6 , KF6 , KG6 , KH6 , ___ , KJ6 , KK6 , KL6 , ___ , ___ , KO6 , ___ , KQ6 , KR6 }, \
        /* 7 */  { KA7 , KB7 , KC7 , KD7 , KE7 , KF7 , KG7 , KH7 , KI7 , KJ7 , ___ , ___ , ___ , ___ , KO7 , ___ , KQ7 , KR7 }  \
    }

#define LAYOUT_fullsize_iso( \
    KJ6,      KI4, KH4, KH2, KH6, KA7, KE6, KD2, KD4, KB4, KB7, KB6, KB0,   KC7, KC5, KA5,                       \
    KJ4, KJ7, KI7, KH7, KG7, KG4, KF4, KF7, KE7, KD7, KR7, KR4, KE4, KB2,   KL4, KO4, KQ4,   KK1, KL1, KQ1, KQ0, \
    KJ2, KJ5, KI5, KH5, KG5, KG2, KF2, KF5, KE5, KD5, KR5, KR2, KE2,        KK4, KO7, KQ7,   KK5, KL5, KQ5, KO5, \
    KI2, KJ3, KI3, KH3, KG3, KG6, KF6, KF3, KE3, KD3, KR3, KR6, KB3, KB1,                    KK2, KL2, KQ2,      \
    KN2, KI6, KJ1, KI1, KH1, KG1, KG0, KF0, KF1, KE1, KD1, KR0,      KN3,        KO6,        KK3, KL3, KQ3, KO3, \
    KA4, KP2, KC6,                KK6,                KC0, KM3, KD0, KA1,   KO0, KK0, KL0,   KL6,      KQ6       \
    ) { /*        00-A  01-B  02-C  03-D  04-E  05-F  06-G  07-H  08-I  09-J  10-K  11-L  12-M  13-N  14-O  15-P  16-Q  17-R */ \
        /* 0 */  { ___ , KB0 , KC0 , KD0 , ___ , KF0 , KG0 , ___ , ___ , ___ , KK0 , KL0 , ___ , ___ , KO0 , ___ , KQ0 , KR0 }, \
        /* 1 */  { KA1 , KB1 , ___ , KD1 , KE1 , KF1 , KG1 , KH1 , KI1 , KJ1 , KK1 , KL1 , ___ , ___ , ___ , ___ , KQ1 , ___ }, \
        /* 2 */  { ___ , KB2 , ___ , KD2 , KE2 , KF2 , KG2 , KH2 , KI2 , KJ2 , KK2 , KL2 , ___ , KN2 , ___ , KP2 , KQ2 , KR2 }, \
        /* 3 */  { ___ , KB3 , ___ , KD3 , KE3 , KF3 , KG3 , KH3 , KI3 , KJ3 , KK3 , KL3 , KM3 , KN3 , KO3 , ___ , KQ3 , KR3 }, \
        /* 4 */  { KA4 , KB4 , ___ , KD4 , KE4 , KF4 , KG4 , KH4 , KI4 , KJ4 , KK4 , KL4 , ___ , ___ , KO4 , ___ , KQ4 , KR4 }, \
        /* 5 */  { KA5 , ___ , KC5 , KD5 , KE5 , KF5 , KG5 , KH5 , KI5 , KJ5 , KK5 , KL5 , ___ , ___ , KO5 , ___ , KQ5 , KR5 }, \
        /* 6 */  { ___ , KB6 , KC6 , ___ , KE6 , KF6 , KG6 , KH6 , KI6 , KJ6 , KK6 , KL6 , ___ , ___ , KO6 , ___ , KQ6 , KR6 }, \
        /* 7 */  { KA7 , KB7 , KC7 , KD7 , KE7 , KF7 , KG7 , KH7 , KI7 , KJ7 , ___ , ___ , ___ , ___ , KO7 , ___ , KQ7 , KR7 }  \
    }

