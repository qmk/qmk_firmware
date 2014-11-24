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

/* Map physical keyboard layout to matrix array */
#define KEYMAP( \
            K5A, K5B, K5C, K5D, \
            K4A, K4B, K4C, K4D, \
            K3A, K3B, K3C, K3D, \
            K2A, K2B, K2C,      \
            K1A, K1B, K1C, K1D, \
            K0A, K0B, K0C       \
) { \
/*             0         1         2         3    */ \
/* 5 */   { KC_##K5A, KC_##K5B, KC_##K5C, KC_##K5D}, \
/* 4 */   { KC_##K4A, KC_##K4B, KC_##K4C, KC_##K4D}, \
/* 3 */   { KC_##K3A, KC_##K3B, KC_##K3C, KC_##K3D}, \
/* 2 */   { KC_##K2A, KC_##K2B, KC_##K2C, KC_NO},    \
/* 1 */   { KC_##K1A, KC_##K1B, KC_##K1C, KC_##K1D}, \
/* 0 */   { KC_##K0A, KC_##K0B, KC_##K0C, KC_NO,  }  \
}

#include "keymap_lightpad.h"

#define KEYMAPS_SIZE    (sizeof(keymaps) / sizeof(keymaps[0]))
#define FN_ACTIONS_SIZE (sizeof(fn_actions) / sizeof(fn_actions[0]))

/* translates key to keycode */
uint8_t keymap_key_to_keycode(uint8_t layer, keypos_t key)
{
    if (layer < KEYMAPS_SIZE) {
        return pgm_read_byte(&keymaps[(layer)][(key.row)][(key.col)]);
    } else {
        // fall back to layer 0
        return pgm_read_byte(&keymaps[0][(key.row)][(key.col)]);
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
