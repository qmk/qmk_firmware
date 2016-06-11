/*
Copyright 2012, 2013 Jun Wako <wakojun@gmail.com>

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
#include "keymap_common.h"
#include "report.h"
#include "action_layer.h"
#include "action.h"
#ifdef BOOTMAGIC_ENABLE
#   include "bootmagic.h"
#else
#   include "magic.h"
#endif

static void apply_keymap_config(action_t *target);

/* gets the action associated with a key */
action_t action_for_key(uint8_t layer, keypos_t key) {
    action_t action;
    action.code = keymap_key_to_keycode(layer, key);
    apply_keymap_config(&action);
    switch (action.code) {
    case KC_FN0 ... KC_FN31:
        action.code = keymap_fn_to_keycode(action.code);
        break;
    case KC_SYSTEM_POWER ... KC_SYSTEM_WAKE:
        action.code = ACTION_USAGE_SYSTEM(KEYCODE2SYSTEM(action.code));
        break;
    case KC_AUDIO_MUTE ... KC_WWW_FAVORITES:
        action.code = ACTION_USAGE_CONSUMER(KEYCODE2CONSUMER(action.code));
        break;
    case KC_MS_UP ... KC_MS_ACCEL2:
        action.code = ACTION_MOUSEKEY(action.code);
        break;
    }
    return action;
}

static void apply_keymap_config(action_t *target) {
    switch (target->code) {
    case KC_CAPSLOCK:
    case KC_LOCKING_CAPS:
        if (keymap_config.swap_control_capslock_or_capslock_to_control) {
            target->code = KC_LCTL;
        }
        break;
    case KC_LCTL:
        if (keymap_config.swap_control_capslock) {
            target->code = KC_CAPSLOCK;
            break;
        }
        break;
    case KC_LALT:
        if (keymap_config.swap_lalt_lgui) {
            if (keymap_config.no_gui) {
                target->code = ACTION_NO;
                break;
            }
            target->code = KC_LGUI;
        }
        break;
    case KC_LGUI:
        if (keymap_config.swap_lalt_lgui) {
            target->code = KC_LALT;
        }
        if (keymap_config.no_gui) {
            target->code = ACTION_NO;
        }
        break;
    case KC_RALT:
        if (keymap_config.swap_ralt_rgui) {
            if (keymap_config.no_gui) {
                target->code = ACTION_NO;
                break;
            }
            target->code = KC_RGUI;
        }
        break;
    case KC_RGUI:
        if (keymap_config.swap_ralt_rgui) {
            target->code = KC_RALT;
        }
        if (keymap_config.no_gui) {
            target->code = ACTION_NO;
        }
        break;
    case KC_GRAVE:
        if (keymap_config.swap_grave_esc) {
            target->code = KC_ESC;
        }
        break;
    case KC_ESC:
        if (keymap_config.swap_grave_esc) {
            target->code = KC_GRAVE;
        }
        break;
    case KC_BSLASH:
        if (keymap_config.swap_backslash_backspace) {
            target->code = KC_BSPACE;
        }
        break;
    case KC_BSPACE:
        if (keymap_config.swap_backslash_backspace) {
            target->code = KC_BSLASH;
        }
        break;
    }
}

/* returns macros */
__attribute__ ((weak))
const macro_t * action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
    return MACRO_NONE;
}

/* executes custom code */
__attribute__ ((weak))
void action_function(keyrecord_t *record, uint8_t id, uint8_t opt) {
}

/* fetches a keycode */
uint16_t keymap_key_to_keycode(uint8_t layer, keypos_t key) {
    // Read entire word (16bits)
    return pgm_read_word(&keymaps[layer][key.row][key.col]);
}

/* fetches a keycode */
uint16_t keymap_fn_to_keycode(uint8_t keycode) {
    return pgm_read_word(&fn_actions[FN_INDEX(keycode)]);
}

void update_tri_layer(uint8_t layer1, uint8_t layer2, uint8_t layer3) {
    if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2)) {
        layer_on(layer3);
    }
    else {
        layer_off(layer3);
    }
}
