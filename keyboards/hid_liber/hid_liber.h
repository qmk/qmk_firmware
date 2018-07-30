/* Copyright 2011 Jun Wako <wakojun@gmail.com>: Original TMK layout
 * Copyright 2018 bakageta <amo@bakageta.com>
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
#ifndef HID_LIBER_H
#define HID_LIBER_H

#include "quantum.h"

#define  ___ KC_NO

/* Tenkeyless keyboard default layout, ISO & ANSI (ISO is between Left Shift
 * and Z, and the ANSI \ key above Return/Enter is used for the additional ISO
 * switch in the ASD row next to enter.  Use NUBS as keycode for the first and
 * NUHS as the keycode for the second.
 *
 * ,---.   ,---------------. ,---------------. ,---------------. ,-----------.
 * |Esc|   |F1 |F2 |F3 |F4 | |F5 |F6 |F7 |F8 | |F9 |F10|F11|F12| |PrS|ScL|Pau|
 * `---'   `---------------' `---------------' `---------------' `-----------'
 * ,-----------------------------------------------------------. ,-----------.
 * |~  |  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|Backsp | |Ins|Hom|PgU|
 * |-----------------------------------------------------------| |-----------|
 * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|    \| |Del|End|PgD|
 * |-----------------------------------------------------------| `-----------'
 * |Caps  |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Return  |              
 * |-----------------------------------------------------------|     ,---.    
 * |Shft|ISO|  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shift     |     |Up |    
 * |-----------------------------------------------------------| ,-----------.
 * |Ctl|Gui|Alt|          Space                |Alt|Gui|App|Ctl| |Lef|Dow|Rig|
 * `-----------------------------------------------------------' `-----------'
 */
#define LAYOUT( \
    KG1,      KH7, KJ7, KJ6, KJ1, KO5, KL1, KA6, KA7, KD7, KD5, KD1, KD2,      KB5, KB3, KO3, \
    KG7, KG5, KH5, KJ5, KI5, KI7, KK7, KK5, KL5, KA5, KC5, KC7, KL7, KD6,      KQ7, KN7, KM7, \
    KG6, KG3, KH3, KJ3, KI3, KI6, KK6, KK3, KL3, KA3, KC3, KC6, KL6, KD4,      KP7, KN5, KM5, \
    KH6, KG4, KH4, KJ4, KI4, KI1, KK1, KK4, KL4, KA4, KC4, KC1,      KD0,                     \
    KF6, KH1, KG0, KH0, KJ0, KI0, KI2, KK2, KK0, KL0, KA0, KC2,      KF4,           KN1,      \
    KO7, KE6, KB1,           KP1,                     KB2, KR4, KA2, KO0,      KN2, KP2, KQ2  \
) { \
/*           0     1     2     3     4     5     6     7  */ \
/* A */   { KA0 , ___ , KA2 , KA3 , KA4 , KA5 , KA6 , KA7 }, \
/* B */   { ___ , KB1 , KB2 , KB3 , ___ , KB5 , ___ , ___ }, \
/* C */   { ___ , KC1 , KC2 , KC3 , KC4 , KC5 , KC6 , KC7 }, \
/* D */   { KD0 , KD1 , KD2 , ___ , KD4 , KD5 , KD6 , KD7 }, \
/* E */   { ___ , ___ , ___ , ___ , ___ , ___ , KE6 , ___ }, \
/* F */   { ___ , ___ , ___ , ___ , KF4 , ___ , KF6 , ___ }, \
/* G */   { KG0 , KG1 , ___ , KG3 , KG4 , KG5 , KG6 , KG7 }, \
/* H */   { KH0 , KH1 , ___ , KH3 , KH4 , KH5 , KH6 , KH7 }, \
/* I */   { KI0 , KI1 , KI2 , KI3 , KI4 , KI5 , KI6 , KI7 }, \
/* J */   { KJ0 , KJ1 , ___ , KJ3 , KJ4 , KJ5 , KJ6 , KJ7 }, \
/* K */   { KK0 , KK1 , KK2 , KK3 , KK4 , KK5 , KK6 , KK7 }, \
/* L */   { KL0 , KL1 , ___ , KL3 , KL4 , KL5 , KL6 , KL7 }, \
/* M */   { ___ , ___ , ___ , ___ , ___ , KM5 , ___ , KM7 }, \
/* N */   { ___ , KN1 , KN2 , ___ , ___ , KN5 , ___ , KN7 }, \
/* O */   { KO0 , ___ , ___ , KO3 , ___ , KO5 , ___ , KO7 }, \
/* P */   { ___ , KP1 , KP2 , ___ , ___ , ___ , ___ , KP7 }, \
/* Q */   { ___ , ___ , KQ2 , ___ , ___ , ___ , ___ , KQ7 }, \
/* R */   { ___ , ___ , ___ , ___ , KR4 , ___ , ___ , ___ }  \
}



#endif
