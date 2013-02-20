/*
Copyright 2013 Jun Wako <wakojun@gmail.com>

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
#include <avr/pgmspace.h>
#include "keymap.h"
#include "report.h"
#include "keycode.h"
#include "layer_switch.h"
#include "action.h"
#include "debug.h"


static action_t keycode_to_action(uint8_t keycode);

#ifdef USE_KEYMAP_V2
/* converts key to action */
action_t action_for_key(uint8_t layer, key_t key)
{
    uint8_t keycode = keymap_key_to_keycode(layer, key);
    switch (keycode) {
        case KC_FN0 ... KC_FN31:
            return keymap_fn_to_action(keycode);
        default:
            return keycode_to_action(keycode);
    }
}

__attribute__ ((weak))
void action_function(keyrecord_t *event, uint8_t id, uint8_t opt)
{
}
#else
/* 
 * legacy keymap support
 */
/* translation for legacy keymap */
action_t action_for_key(uint8_t layer, key_t key)
{
    /* convert from legacy keycode to action */
    /* layer 16-31 indicate 'overlay' but not supported in legacy keymap */
    uint8_t keycode = keymap_get_keycode((layer & OVERLAY_MASK), key.row, key.col);
    action_t action;
    switch (keycode) {
        case KC_FN0 ... KC_FN31:
            {
                uint8_t layer = keymap_fn_layer(FN_INDEX(keycode));
                uint8_t key = keymap_fn_keycode(FN_INDEX(keycode));
                if (key) {
                    action.code = ACTION_KEYMAP_TAP_KEY(layer, key);
                } else {
                    action.code = ACTION_KEYMAP_MOMENTARY(layer);
                }
            }
            return action;
        default:
            return keycode_to_action(keycode);
    }
}
/* not used for legacy keymap */
void action_function(keyrecord_t *event, uint8_t id, uint8_t opt)
{
}
#endif



/* translates keycode to action */
static action_t keycode_to_action(uint8_t keycode)
{
    action_t action;
    switch (keycode) {
        case KC_A ... KC_EXSEL:
            action.code = ACTION_KEY(keycode);
            break;
        case KC_LCTRL ... KC_LGUI:
            action.code = ACTION_LMOD(keycode);
            break;
        case KC_RCTRL ... KC_RGUI:
            action.code = ACTION_RMOD(keycode);
            break;
        case KC_SYSTEM_POWER ... KC_SYSTEM_WAKE:
            action.code = ACTION_USAGE_SYSTEM(KEYCODE2SYSTEM(keycode));
            break;
        case KC_AUDIO_MUTE ... KC_WWW_FAVORITES:
            action.code = ACTION_USAGE_CONSUMER(KEYCODE2CONSUMER(keycode));
            break;
        case KC_MS_UP ... KC_MS_ACCEL2:
            action.code = ACTION_MOUSEKEY(keycode);
            break;
        case KC_TRNS:
            action.code = ACTION_TRANSPARENT;
            break;
        default:
            action.code = ACTION_NO;
            break;
    }
    return action;
}
