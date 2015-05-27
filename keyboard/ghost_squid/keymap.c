/*
Copyright 2014 Ralf Schmitt <ralf@bunkertor.net>

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

#include <stdint.h>
#include <stdbool.h>
#include <avr/pgmspace.h>
#include "keycode.h"
#include "action.h"
#include "action_macro.h"
#include "report.h"
#include "host.h"
#include "debug.h"
#include "keymap.h"

/*
 Matrix col/row mapping

 ,----.    ,-------------------. ,-------------------. ,-------------------. ,--------------.
 |06/6|    |07/4|08/4|08/2|08/6| |15/5|11/6|12/2|12/4| |14/4|14/5|14/6|14/0| |13/5|13/7|15/7|
 `----'    `-------------------' `-------------------' `-------------------' `--------------'
 ,-------------------------------------------------------------------------. ,--------------. ,-------------------.
 |06/4|06/5|07/5|08/5|09/5|09/4|10/4|10/5|11/5|12/5|05/5|05/4|11/4|    14/2| |17/4|02/4|04/4| |16/1|17/1|04/1|04/0|
 |-------------------------------------------------------------------------| |--------------| |-------------------|
 |06/2  |06/7|07/7|08/7|09/7|09/2|10/2|10/7|11/7|12/7|05/7|05/2|11/2|  14/3| |16/4|02/5|04/5| |16/7|17/7|04/7|    |
 |-------------------------------------------------------------------------| '--------------' |-------------- 02/7|
 |02/7   |06/3|07/3|08/3|09/3|09/6|10/6|10/3|11/3|12/3|05/3|05/6|      14/1|                  |16/2|17/2|04/2|    |
 |-------------------------------------------------------------------------|      ,----.      |-------------------|
 |01/2     |06/1|07/1|08/1|09/1|09/0|10/0|10/1|11/1|12/1|05/0|         01/3|      |02/6|      |16/3|17/3|04/3|    |
 |-------------------------------------------------------------------------| ,--------------. |-------------- 02/3|
 |15/4|03/2|13/6|                 16/6                  |13/0|0/3|12/0|15/1| |02/0|16/0|17/0| | 17/6    |04/6|    |
 `-------------------------------------------------------------------------' `--------------' `-------------------'
*/

#define KEYMAP( \
    KG6,      KH4, KI4, KI2, KI6, KP5, KL6, KM2, KM4, KO4, KO5, KO6, KO0,   KN5, KN7, KP7,                       \
    KG4, KG5, KH5, KI5, KJ5, KJ4, KK4, KK5, KL5, KM5, KF5, KF4, KL4, KO2,   KR4, KC4, KE4,   KQ1, KR1, KE1, KE0, \
    KG2, KG7, KH7, KI7, KJ7, KJ2, KK2, KK7, KL7, KM7, KF7, KF2, KL2, KO3,   KQ4, KC5, KE5,   KQ7, KR7, KE7, KC7, \
    KH2, KG3, KH3, KI3, KJ3, KJ6, KK6, KK3, KL3, KM3, KF3, KF6,      KO1,                    KQ2, KR2, KE2,      \
    KB2, KH6, KG1, KH1, KI1, KJ1, KJ0, KK0, KK1, KL1, KM1, KF0,      KB3,        KC6,        KQ3, KR3, KE3, KC3, \
    KP4, KD2, KN6,                KQ6,                KN0, KA3, KM0, KP1,   KC0, KQ0, KR0,   KR6,      KE6       \
) { \
/*            0         1         2         3         4         5         6         7   */  \
/* A  0 */ {KC_NO,    KC_NO,    KC_NO,    KC_##KA3, KC_NO,    KC_NO,    KC_NO,    KC_NO   },\
/* B  1 */ {KC_NO,    KC_NO,    KC_##KB2, KC_##KB3, KC_NO,    KC_NO,    KC_NO,    KC_NO   },\
/* C  2 */ {KC_##KC0, KC_NO,    KC_NO,    KC_##KC3, KC_##KC4, KC_##KC5, KC_##KC6, KC_##KC7},\
/* D  3 */ {KC_NO,    KC_NO,    KC_##KD2, KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO   },\
/* E  4 */ {KC_##KE0, KC_##KE1, KC_##KE2, KC_##KE3, KC_##KE4, KC_##KE5, KC_##KE6, KC_##KE7},\
/* F  5 */ {KC_##KF0, KC_NO,    KC_##KF2, KC_##KF3, KC_##KF4, KC_##KF5, KC_##KF6, KC_##KF7},\
/* G  6 */ {KC_NO,    KC_##KG1, KC_##KG2, KC_##KG3, KC_##KG4, KC_##KG5, KC_##KG6, KC_##KG7},\
/* H  7 */ {KC_NO,    KC_##KH1, KC_##KH2, KC_##KH3, KC_##KH4, KC_##KH5, KC_##KH6, KC_##KH7},\
/* I  8 */ {KC_NO,    KC_##KI1, KC_##KI2, KC_##KI3, KC_##KI4, KC_##KI5, KC_##KI6, KC_##KI7},\
/* J  9 */ {KC_##KJ0, KC_##KJ1, KC_##KJ2, KC_##KJ3, KC_##KJ4, KC_##KJ5, KC_##KJ6, KC_##KJ7},\
/* K 10 */ {KC_##KK0, KC_##KK1, KC_##KK2, KC_##KK3, KC_##KK4, KC_##KK5, KC_##KK6, KC_##KK7},\
/* L 11 */ {KC_NO,    KC_##KL1, KC_##KL2, KC_##KL3, KC_##KL4, KC_##KL5, KC_##KL6, KC_##KL7},\
/* M 12 */ {KC_##KM0, KC_##KM1, KC_##KM2, KC_##KM3, KC_##KM4, KC_##KM5, KC_NO,    KC_##KM7},\
/* N 13 */ {KC_##KN0, KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_##KN5, KC_##KN6, KC_##KN7},\
/* O 14 */ {KC_##KO0, KC_##KO1, KC_##KO2, KC_##KO3, KC_##KO4, KC_##KO5, KC_##KO6, KC_NO   },\
/* P 15 */ {KC_NO,    KC_##KP1, KC_NO,    KC_NO,    KC_##KP4, KC_##KP5, KC_NO,    KC_##KP7},\
/* Q 16 */ {KC_##KQ0, KC_##KQ1, KC_##KQ2, KC_##KQ3, KC_##KQ4, KC_NO,    KC_##KQ6, KC_##KQ7},\
/* R 17 */ {KC_##KR0, KC_##KR1, KC_##KR2, KC_##KR3, KC_##KR4, KC_NO,    KC_##KR6, KC_##KR7} \
}

#include "keymap_ansi.h"

#define KEYMAPS_SIZE    (sizeof(keymaps) / sizeof(keymaps[0]))
#define FN_ACTIONS_SIZE (sizeof(fn_actions) / sizeof(fn_actions[0]))

/* translates key to keycode */
uint8_t keymap_key_to_keycode(uint8_t layer, keypos_t key)
{
    if (layer < KEYMAPS_SIZE) {
        return pgm_read_byte(&keymaps[(layer)][(key.col)][(key.row)]);
    } else {
        return pgm_read_byte(&keymaps[0][(key.col)][(key.row)]);
    }
}

/* translates Fn keycode to action */
action_t keymap_fn_to_action(uint8_t keycode)
{
    action_t action;
    if (FN_INDEX(keycode) < FN_ACTIONS_SIZE) {
        action.code = pgm_read_word(&fn_actions[FN_INDEX(keycode)]);
    } else {
        action.code = ACTION_NO;
    }
    return action;
}
