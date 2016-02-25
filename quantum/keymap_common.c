/*
Copyright 2012,2013 Jun Wako <wakojun@gmail.com>

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
#include "keycode.h"
#include "action_layer.h"
#include <util/delay.h>
#include "action.h"
#include "action_macro.h"
#include "debug.h"
#include "backlight.h"
#include "keymap_midi.h"

#include <stdio.h>
#include <inttypes.h>
#ifdef AUDIO_ENABLE
    #include "audio.h"

    float goodbye[][2] = {
        {440.0*pow(2.0,(67)/12.0), 400},
        {0, 50},
        {440.0*pow(2.0,(60)/12.0), 400},
        {0, 50},
        {440.0*pow(2.0,(55)/12.0), 600},
    };
#endif

static action_t keycode_to_action(uint16_t keycode);

/* converts key to action */
action_t action_for_key(uint8_t layer, keypos_t key)
{
	// 16bit keycodes - important
    uint16_t keycode = keymap_key_to_keycode(layer, key);

    if (keycode >= 0x0100 && keycode < 0x2000) {
    	// Has a modifier
    	action_t action;
    	// Split it up
    	action.code = ACTION_MODS_KEY(keycode >> 8, keycode & 0xFF); // adds modifier to key
    	return action;
	} else if (keycode >= 0x2000 && keycode < 0x3000) {
        // Is a shortcut for function layer, pull last 12bits
        // This means we have 4,096 FN macros at our disposal
        return keymap_func_to_action(keycode & 0xFFF);
	} else if (keycode >= 0x3000 && keycode < 0x4000) {
      // When the code starts with 3, it's an action macro.
    	action_t action;
    	action.code = ACTION_MACRO(keycode & 0xFF);
    	return action;
#ifdef BACKLIGHT_ENABLE
	} else if (keycode >= BL_0 && keycode <= BL_15) {
        action_t action;
        action.code = ACTION_BACKLIGHT_LEVEL(keycode & 0x000F);
        return action;
    } else if (keycode == BL_DEC) {
        action_t action;
        action.code = ACTION_BACKLIGHT_DECREASE();
        return action;
    } else if (keycode == BL_INC) {
        action_t action;
        action.code = ACTION_BACKLIGHT_INCREASE();
        return action;
    } else if (keycode == BL_TOGG) {
        action_t action;
        action.code = ACTION_BACKLIGHT_TOGGLE();
        return action;
    } else if (keycode == BL_STEP) {
        action_t action;
        action.code = ACTION_BACKLIGHT_STEP();
        return action;
#endif
    } else if (keycode == RESET) { // RESET is 0x5000, which is why this is here
        clear_keyboard();
        #ifdef AUDIO_ENABLE
            play_notes(&goodbye, 5, false);
        #endif
        _delay_ms(250);
        #ifdef ATREUS_ASTAR
            *(uint16_t *)0x0800 = 0x7777; // these two are a-star-specific
        #endif
        bootloader_jump();
        return;
    } else if (keycode == DEBUG) { // DEBUG is 0x5001
      // TODO: Does this actually work?
        print("\nDEBUG: enabled.\n");
        debug_enable = true;
        return;
    } else if (keycode >= 0x5000 && keycode < 0x6000) {
        // Layer movement shortcuts
        // See .h to see constraints/usage
        int type = (keycode >> 0x8) & 0xF;
        if (type == 0x1) {
            // Layer set "GOTO"
            int when = (keycode >> 0x4) & 0x3;
            int layer = keycode & 0xF;
            action_t action;
            action.code = ACTION_LAYER_SET(layer, when);
            return action;
        } else if (type == 0x2) {
            // Momentary layer
            int layer = keycode & 0xFF;
            action_t action;
            action.code = ACTION_LAYER_MOMENTARY(layer);
            return action;
        } else if (type == 0x3) {
            // Set default layer
            int layer = keycode & 0xFF;
            action_t action;
            action.code = ACTION_DEFAULT_LAYER_SET(layer);
            return action;
        } else if (type == 0x4) {
            // Set default layer
            int layer = keycode & 0xFF;
            action_t action;
            action.code = ACTION_LAYER_TOGGLE(layer);
            return action;
        }
#ifdef MIDI_ENABLE
    } else if (keycode >= 0x6000 && keycode < 0x7000) {
        action_t action;
        action.code =  ACTION_FUNCTION_OPT(keycode & 0xFF, (keycode & 0x0F00) >> 8);
        return action;
#endif
    } else if (keycode >= 0x7000 && keycode < 0x8000) {
        action_t action;
        action.code = ACTION_MODS_TAP_KEY((keycode >> 0x8) & 0xF, keycode & 0xFF);
        return action;
    } else if (keycode >= 0x8000 && keycode < 0x9000) {
        action_t action;
        action.code = ACTION_LAYER_TAP_KEY((keycode >> 0x8) & 0xF, keycode & 0xFF);
        return action;
#ifdef UNICODE_ENABLE
    } else if (keycode >= 0x8000000) {
        action_t action;
        uint16_t unicode = keycode & ~(0x8000);
        action.code =  ACTION_FUNCTION_OPT(unicode & 0xFF, (unicode & 0xFF00) >> 8);
        return action;
#endif
    } else {

    }

    switch (keycode) {
        case KC_FN0 ... KC_FN31:
            return keymap_fn_to_action(keycode);
#ifdef BOOTMAGIC_ENABLE
        case KC_CAPSLOCK:
        case KC_LOCKING_CAPS:
            if (keymap_config.swap_control_capslock || keymap_config.capslock_to_control) {
                return keycode_to_action(KC_LCTL);
            }
            return keycode_to_action(keycode);
        case KC_LCTL:
            if (keymap_config.swap_control_capslock) {
                return keycode_to_action(KC_CAPSLOCK);
            }
            return keycode_to_action(KC_LCTL);
        case KC_LALT:
            if (keymap_config.swap_lalt_lgui) {
                if (keymap_config.no_gui) {
                    return keycode_to_action(ACTION_NO);
                }
                return keycode_to_action(KC_LGUI);
            }
            return keycode_to_action(KC_LALT);
        case KC_LGUI:
            if (keymap_config.swap_lalt_lgui) {
                return keycode_to_action(KC_LALT);
            }
            if (keymap_config.no_gui) {
                return keycode_to_action(ACTION_NO);
            }
            return keycode_to_action(KC_LGUI);
        case KC_RALT:
            if (keymap_config.swap_ralt_rgui) {
                if (keymap_config.no_gui) {
                    return keycode_to_action(ACTION_NO);
                }
                return keycode_to_action(KC_RGUI);
            }
            return keycode_to_action(KC_RALT);
        case KC_RGUI:
            if (keymap_config.swap_ralt_rgui) {
                return keycode_to_action(KC_RALT);
            }
            if (keymap_config.no_gui) {
                return keycode_to_action(ACTION_NO);
            }
            return keycode_to_action(KC_RGUI);
        case KC_GRAVE:
            if (keymap_config.swap_grave_esc) {
                return keycode_to_action(KC_ESC);
            }
            return keycode_to_action(KC_GRAVE);
        case KC_ESC:
            if (keymap_config.swap_grave_esc) {
                return keycode_to_action(KC_GRAVE);
            }
            return keycode_to_action(KC_ESC);
        case KC_BSLASH:
            if (keymap_config.swap_backslash_backspace) {
                return keycode_to_action(KC_BSPACE);
            }
            return keycode_to_action(KC_BSLASH);
        case KC_BSPACE:
            if (keymap_config.swap_backslash_backspace) {
                return keycode_to_action(KC_BSLASH);
            }
            return keycode_to_action(KC_BSPACE);
#endif
        default:
            return keycode_to_action(keycode);
    }
}


/* Macro */
__attribute__ ((weak))
const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    return MACRO_NONE;
}

/* Function */
__attribute__ ((weak))
void action_function(keyrecord_t *record, uint8_t id, uint8_t opt)
{
}

/* translates keycode to action */
static action_t keycode_to_action(uint16_t keycode)
{
    action_t action;
    switch (keycode) {
        case KC_A ... KC_EXSEL:
        case KC_LCTRL ... KC_RGUI:
            action.code = ACTION_KEY(keycode);
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


/* translates key to keycode */
uint16_t keymap_key_to_keycode(uint8_t layer, keypos_t key)
{
	// Read entire word (16bits)
    return pgm_read_word(&keymaps[(layer)][(key.row)][(key.col)]);
}

/* translates Fn keycode to action */
action_t keymap_fn_to_action(uint16_t keycode)
{
    return (action_t){ .code = pgm_read_word(&fn_actions[FN_INDEX(keycode)]) };
}

action_t keymap_func_to_action(uint16_t keycode)
{
	// For FUNC without 8bit limit
    return (action_t){ .code = pgm_read_word(&fn_actions[(int)keycode]) };
}
