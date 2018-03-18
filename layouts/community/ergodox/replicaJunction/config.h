/*
Config file - Ergodox QMK with replicaJunction layout

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

#ifndef KEYBOARDS_ERGODOX_CONFIG_H_
#define KEYBOARDS_ERGODOX_CONFIG_H_

#include QMK_KEYBOARD_CONFIG_H


#undef MOUSEKEY_DELAY          
#undef MOUSEKEY_INTERVAL       
#undef MOUSEKEY_MAX_SPEED      
#undef MOUSEKEY_TIME_TO_MAX    

#define MOUSEKEY_DELAY          100
#define MOUSEKEY_INTERVAL       20
#define MOUSEKEY_MAX_SPEED      3
#define MOUSEKEY_TIME_TO_MAX    10

#define TAPPING_TOGGLE  1

/* define if matrix has ghost */
//#define MATRIX_HAS_GHOST

// MS the button needs to be held before a tap becomes a hold (default: 200)
#define TAPPING_TERM    200

#define IGNORE_MOD_TAP_INTERRUPT // this makes it possible to do rolling combos (zx) with keys that convert to other keys on hold (z becomes ctrl when you hold it, and when this option isn't enabled, z rapidly followed by x actually sends Ctrl-x. That's bad.)

// I don't have any locking keys, so I don't need these features


/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */

//#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
//#define LOCKING_RESYNC_ENABLE

/* Prevent modifiers from sticking when switching layers */
/* Uses 5 bytes of memory per 8 keys, but makes sure modifiers don't get "stuck" switching layers */
#define PREVENT_STUCK_MODIFIERS

/* key combination for command */
#define IS_COMMAND() ( \
    keyboard_report->mods == (MOD_BIT(KC_LCTL) | MOD_BIT(KC_RCTL)) || \
    keyboard_report->mods == (MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT)) \
)


#endif /* KEYBOARDS_ERGODOX_CONFIG_H_ */
