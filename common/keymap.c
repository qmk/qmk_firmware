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
#include "keymap.h"
#include "report.h"
#include "keycode.h"
#include "action.h"


/* layer */
uint8_t default_layer = 0;
uint8_t current_layer = 0;


action_t keymap_keycode_to_action(uint8_t keycode)
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

#ifndef NO_LEGACY_KEYMAP_SUPPORT
/* legacy support with weak reference */
__attribute__ ((weak))
action_t keymap_get_action(uint8_t layer, uint8_t row, uint8_t col)
{
    /* convert from legacy keycode to action */
    uint8_t keycode = keymap_get_keycode(layer, row, col);
    action_t action;
    switch (keycode) {
        case KC_FN0 ... KC_FN31:
            {
                uint8_t layer = keymap_fn_layer(FN_INDEX(keycode));
                uint8_t key = keymap_fn_keycode(FN_INDEX(keycode));
                if (key) {
                    action.code = ACTION_LAYER_SET_TAP_KEY(layer, key);
                } else {
                    action.code = ACTION_LAYER_SET_MOMENTARY(layer);
                }
            }
            return action;
        default:
            return keymap_keycode_to_action(keycode);
    }
}
#endif

__attribute__ ((weak))
void keymap_call_function(keyrecord_t *event, uint8_t id, uint8_t opt)
{
}
