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

#include "matrix.h"
#include "quantum.h"

#define  ___ XXXXXXX

#define LAYOUT( \
    KJ6,      KI4, KH4, KH2, KH6, KA7, KE6, KD2, KD4, KB4, KB7, KB6, KB0,   KC7, KC5, KA5, \
    KJ4, KJ7, KI7, KH7, KG7, KG4, KF4, KF7, KE7, KD7, KR7, KR4, KE4, KB2,   KL4, KO4, KQ4, \
    KJ2, KJ5, KI5, KH5, KG5, KG2, KF2, KF5, KE5, KD5, KR5, KR2, KE2, KB3,   KK4, KO7, KQ7, \
    KI2, KJ3, KI3, KH3, KG3, KG6, KF6, KF3, KE3, KD3, KR3, KR6,      KB1,                  \
    KN2, KI6, KJ1, KI1, KH1, KG1, KG0, KF0, KF1, KE1, KD1, KR0,      KN3,        KO6,      \
    KA4, KP2, KC6,                KK6,                KC0, KM3, KD0, KA1,   KO0, KK0, KL0  \
    ) { /*         00-A  01-B  02-C  03-D  04-E  05-F  06-G  07-H  08-I  09-J  10-K  11-L  12-M  13-N  14-O  15-P  16-Q  17-R */ \
        /* 0 */  { ___ , KB0 , KC0 , KD0 , ___ , KF0 , KG0 , ___ , ___ , ___ , KK0 , KL0 , ___ , ___ , KO0 , ___ , ___ , KR0 }, \
        /* 1 */  { KA1 , KB1 , ___ , KD1 , KE1 , KF1 , KG1 , KH1 , KI1 , KJ1 , ___ , ___ , ___ , ___ , ___ , ___ , ___ , ___ }, \
        /* 2 */  { ___ , KB2 , ___ , KD2 , KE2 , KF2 , KG2 , KH2 , KI2 , KJ2 , ___ , ___ , ___ , KN2 , ___ , KP2 , ___ , KR2 }, \
        /* 3 */  { ___ , KB3 , ___ , KD3 , KE3 , KF3 , KG3 , KH3 , KI3 , KJ3 , ___ , ___ , KM3 , KN3 , ___ , ___ , ___ , KR3 }, \
        /* 4 */  { KA4 , KB4 , ___ , KD4 , KE4 , KF4 , KG4 , KH4 , KI4 , KJ4 , KK4 , KL4 , ___ , ___ , KO4 , ___ , KQ4 , KR4 }, \
        /* 5 */  { KA5 , ___ , KC5 , KD5 , KE5 , KF5 , KG5 , KH5 , KI5 , KJ5 , ___ , ___ , ___ , ___ , ___ , ___ , ___ , KR5 }, \
        /* 6 */  { ___ , KB6 , KC6 , ___ , KE6 , KF6 , KG6 , KH6 , KI6 , KJ6 , KK6 , ___ , ___ , ___ , KO6 , ___ , ___ , KR6 }, \
        /* 7 */  { KA7 , KB7 , KC7 , KD7 , KE7 , KF7 , KG7 , KH7 , KI7 , KJ7 , ___ , ___ , ___ , ___ , KO7 , ___ , KQ7 , KR7 }  \
    }

#define LAYOUT_tkl_ansi( \
    KJ6,      KI4, KH4, KH2, KH6, KA7, KE6, KD2, KD4, KB4, KB7, KB6, KB0,   KC7, KC5, KA5, \
    KJ4, KJ7, KI7, KH7, KG7, KG4, KF4, KF7, KE7, KD7, KR7, KR4, KE4, KB2,   KL4, KO4, KQ4, \
    KJ2, KJ5, KI5, KH5, KG5, KG2, KF2, KF5, KE5, KD5, KR5, KR2, KE2, KB3,   KK4, KO7, KQ7, \
    KI2, KJ3, KI3, KH3, KG3, KG6, KF6, KF3, KE3, KD3, KR3, KR6,      KB1,                  \
    KN2,      KJ1, KI1, KH1, KG1, KG0, KF0, KF1, KE1, KD1, KR0,      KN3,        KO6,      \
    KA4, KP2, KC6,                KK6,                KC0, KM3, KD0, KA1,   KO0, KK0, KL0  \
    ) { /*         00-A  01-B  02-C  03-D  04-E  05-F  06-G  07-H  08-I  09-J  10-K  11-L  12-M  13-N  14-O  15-P  16-Q  17-R */ \
        /* 0 */  { ___ , KB0 , KC0 , KD0 , ___ , KF0 , KG0 , ___ , ___ , ___ , KK0 , KL0 , ___ , ___ , KO0 , ___ , ___ , KR0 }, \
        /* 1 */  { KA1 , KB1 , ___ , KD1 , KE1 , KF1 , KG1 , KH1 , KI1 , KJ1 , ___ , ___ , ___ , ___ , ___ , ___ , ___ , ___ }, \
        /* 2 */  { ___ , KB2 , ___ , KD2 , KE2 , KF2 , KG2 , KH2 , KI2 , KJ2 , ___ , ___ , ___ , KN2 , ___ , KP2 , ___ , KR2 }, \
        /* 3 */  { ___ , KB3 , ___ , KD3 , KE3 , KF3 , KG3 , KH3 , KI3 , KJ3 , ___ , ___ , KM3 , KN3 , ___ , ___ , ___ , KR3 }, \
        /* 4 */  { KA4 , KB4 , ___ , KD4 , KE4 , KF4 , KG4 , KH4 , KI4 , KJ4 , KK4 , KL4 , ___ , ___ , KO4 , ___ , KQ4 , KR4 }, \
        /* 5 */  { KA5 , ___ , KC5 , KD5 , KE5 , KF5 , KG5 , KH5 , KI5 , KJ5 , ___ , ___ , ___ , ___ , ___ , ___ , ___ , KR5 }, \
        /* 6 */  { ___ , KB6 , KC6 , ___ , KE6 , KF6 , KG6 , KH6 , ___ , KJ6 , KK6 , ___ , ___ , ___ , KO6 , ___ , ___ , KR6 }, \
        /* 7 */  { KA7 , KB7 , KC7 , KD7 , KE7 , KF7 , KG7 , KH7 , KI7 , KJ7 , ___ , ___ , ___ , ___ , KO7 , ___ , KQ7 , KR7 }  \
    }

#define LAYOUT_tkl_iso( \
    KJ6,      KI4, KH4, KH2, KH6, KA7, KE6, KD2, KD4, KB4, KB7, KB6, KB0,   KC7, KC5, KA5, \
    KJ4, KJ7, KI7, KH7, KG7, KG4, KF4, KF7, KE7, KD7, KR7, KR4, KE4, KB2,   KL4, KO4, KQ4, \
    KJ2, KJ5, KI5, KH5, KG5, KG2, KF2, KF5, KE5, KD5, KR5, KR2, KE2,        KK4, KO7, KQ7, \
    KI2, KJ3, KI3, KH3, KG3, KG6, KF6, KF3, KE3, KD3, KR3, KR6, KB3, KB1,                  \
    KN2, KI6, KJ1, KI1, KH1, KG1, KG0, KF0, KF1, KE1, KD1, KR0,      KN3,        KO6,      \
    KA4, KP2, KC6,                KK6,                KC0, KM3, KD0, KA1,   KO0, KK0, KL0  \
    ) { /*         00-A  01-B  02-C  03-D  04-E  05-F  06-G  07-H  08-I  09-J  10-K  11-L  12-M  13-N  14-O  15-P  16-Q  17-R */ \
        /* 0 */  { ___ , KB0 , KC0 , KD0 , ___ , KF0 , KG0 , ___ , ___ , ___ , KK0 , KL0 , ___ , ___ , KO0 , ___ , ___ , KR0 }, \
        /* 1 */  { KA1 , KB1 , ___ , KD1 , KE1 , KF1 , KG1 , KH1 , KI1 , KJ1 , ___ , ___ , ___ , ___ , ___ , ___ , ___ , ___ }, \
        /* 2 */  { ___ , KB2 , ___ , KD2 , KE2 , KF2 , KG2 , KH2 , KI2 , KJ2 , ___ , ___ , ___ , KN2 , ___ , KP2 , ___ , KR2 }, \
        /* 3 */  { ___ , KB3 , ___ , KD3 , KE3 , KF3 , KG3 , KH3 , KI3 , KJ3 , ___ , ___ , KM3 , KN3 , ___ , ___ , ___ , KR3 }, \
        /* 4 */  { KA4 , KB4 , ___ , KD4 , KE4 , KF4 , KG4 , KH4 , KI4 , KJ4 , KK4 , KL4 , ___ , ___ , KO4 , ___ , KQ4 , KR4 }, \
        /* 5 */  { KA5 , ___ , KC5 , KD5 , KE5 , KF5 , KG5 , KH5 , KI5 , KJ5 , ___ , ___ , ___ , ___ , ___ , ___ , ___ , KR5 }, \
        /* 6 */  { ___ , KB6 , KC6 , ___ , KE6 , KF6 , KG6 , KH6 , KI6 , KJ6 , KK6 , ___ , ___ , ___ , KO6 , ___ , ___ , KR6 }, \
        /* 7 */  { KA7 , KB7 , KC7 , KD7 , KE7 , KF7 , KG7 , KH7 , KI7 , KJ7 , ___ , ___ , ___ , ___ , KO7 , ___ , KQ7 , KR7 }  \
    }

#define LAYOUT_tkl_jis( \
    KJ6,      KI4, KH4, KH2, KH6, KA7, KE6, KD2, KD4, KB4, KB7, KB6, KB0,        KC7, KC5, KA5, \
    KJ4, KJ7, KI7, KH7, KG7, KG4, KF4, KF7, KE7, KD7, KR7, KR4, KE4, KB5, KB2,   KL4, KO4, KQ4, \
    KJ2, KJ5, KI5, KH5, KG5, KG2, KF2, KF5, KE5, KD5, KR5, KR2, KE2,             KK4, KO7, KQ7, \
    KI2, KJ3, KI3, KH3, KG3, KG6, KF6, KF3, KE3, KD3, KR3, KR6, KB3, KB1,                       \
    KN2,      KJ1, KI1, KH1, KG1, KG0, KF0, KF1, KE1, KD1, KR0, KE0, KN3,             KO6,      \
    KA4, KP2, KC6, KJ0,           KK6,           KI0, KH0, KC0, KD0, KA1,        KO0, KK0, KL0  \
    ) { /*         00-A  01-B  02-C  03-D  04-E  05-F  06-G  07-H  08-I  09-J  10-K  11-L  12-M  13-N  14-O  15-P  16-Q  17-R */ \
        /* 0 */  { ___ , KB0 , KC0 , KD0 , KE0 , KF0 , KG0 , KH0 , KI0 , KJ0 , KK0 , KL0 , ___ , ___ , KO0 , ___ , ___ , KR0 }, \
        /* 1 */  { KA1 , KB1 , ___ , KD1 , KE1 , KF1 , KG1 , KH1 , KI1 , KJ1 , ___ , ___ , ___ , ___ , ___ , ___ , ___ ,     }, \
        /* 2 */  { ___ , KB2 , ___ , KD2 , KE2 , KF2 , KG2 , KH2 , KI2 , KJ2 , ___ , ___ , ___ , KN2 , ___ , KP2 , ___ , KR2 }, \
        /* 3 */  { ___ , KB3 , ___ , KD3 , KE3 , KF3 , KG3 , KH3 , KI3 , KJ3 , ___ , ___ , ___ , KN3 , ___ , ___ , ___ , KR3 }, \
        /* 4 */  { KA4 , KB4 , ___ , KD4 , KE4 , KF4 , KG4 , KH4 , KI4 , KJ4 , KK4 , KL4 , ___ , ___ , KO4 , ___ , KQ4 , KR4 }, \
        /* 5 */  { KA5 , KB5 , KC5 , KD5 , KE5 , KF5 , KG5 , KH5 , KI5 , KJ5 , ___ , ___ , ___ , ___ , ___ , ___ , ___ , KR5 }, \
        /* 6 */  { ___ , KB6 , KC6 , ___ , KE6 , KF6 , KG6 , KH6 , ___ , KJ6 , KK6 , ___ , ___ , ___ , KO6 , ___ , ___ , KR6 }, \
        /* 7 */  { KA7 , KB7 , KC7 , KD7 , KE7 , KF7 , KG7 , KH7 , KI7 , KJ7 , ___ , ___ , ___ , ___ , KO7 , ___ , KQ7 , KR7 }  \
}

inline void ph_caps_led_on(void)  { DDRC |=  (1<<6); PORTC &= ~(1<<6); }
inline void ph_caps_led_off(void) { DDRC &= ~(1<<6); PORTC &= ~(1<<6); }

inline void ph_sclk_led_on(void)  { DDRC |=  (1<<5); PORTC &= ~(1<<5); }
inline void ph_sclk_led_off(void) { DDRC &= ~(1<<5); PORTC &= ~(1<<5); }

