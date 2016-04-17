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
#include "bootloader.h"

extern keymap_config_t keymap_config;

#include <stdio.h>
#include <inttypes.h>
#ifdef AUDIO_ENABLE
    #include "audio.h"
    #ifndef TONE_GOODBYE
    #define TONE_GOODBYE { \
        {440.0*pow(2.0,(31)/12.0), 8}, \
        {440.0*pow(2.0,(24)/12.0), 8}, \
        {440.0*pow(2.0,(19)/12.0), 12}, \
    } 
    #endif
    float tone_goodbye[][2] = TONE_GOODBYE;
#endif

static action_t keycode_to_action(uint16_t keycode);

/* converts key to action */
action_t action_for_key(uint8_t layer, keypos_t key)
{
	// 16bit keycodes - important
    uint16_t keycode = keymap_key_to_keycode(layer, key);

    switch (keycode) {
        case KC_FN0 ... KC_FN31:
            return keymap_fn_to_action(keycode);
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
        case 0x0100 ... 0x1FFF: ;
            // Has a modifier
            // Split it up
            action.code = ACTION_MODS_KEY(keycode >> 8, keycode & 0xFF); // adds modifier to key
            break;
        case 0x2000 ... 0x2FFF:
            // Is a shortcut for function layer, pull last 12bits
            // This means we have 4,096 FN macros at our disposal
            return keymap_func_to_action(keycode & 0xFFF);
            break;
        case 0x3000 ... 0x3FFF: ;
            // When the code starts with 3, it's an action macro.
            action.code = ACTION_MACRO(keycode & 0xFF);
            break;
    #ifdef BACKLIGHT_ENABLE
        case BL_0 ... BL_15:
            action.code = ACTION_BACKLIGHT_LEVEL(keycode & 0x000F);
            break;
        case BL_DEC:
            action.code = ACTION_BACKLIGHT_DECREASE();
            break;
        case BL_INC:
            action.code = ACTION_BACKLIGHT_INCREASE();
            break;
        case BL_TOGG:
            action.code = ACTION_BACKLIGHT_TOGGLE();
            break;
        case BL_STEP:
            action.code = ACTION_BACKLIGHT_STEP();
            break;
    #endif
        case RESET: ; // RESET is 0x5000, which is why this is here
            clear_keyboard();
            #ifdef AUDIO_ENABLE
                PLAY_NOTE_ARRAY(tone_goodbye, false, 0);
            #endif
            _delay_ms(250);
            #ifdef ATREUS_ASTAR
                *(uint16_t *)0x0800 = 0x7777; // these two are a-star-specific
            #endif
            bootloader_jump();
            break;
        case DEBUG: ; // DEBUG is 0x5001
            print("\nDEBUG: enabled.\n");
            debug_enable = true;
            break;
        case 0x5002 ... 0x50FF:
            // MAGIC actions (BOOTMAGIC without the boot)
            if (!eeconfig_is_enabled()) {
                eeconfig_init();
            }
            /* keymap config */
            keymap_config.raw = eeconfig_read_keymap();
            if (keycode == MAGIC_SWAP_CONTROL_CAPSLOCK) {
                keymap_config.swap_control_capslock = 1;
            } else if (keycode == MAGIC_CAPSLOCK_TO_CONTROL) {
                keymap_config.capslock_to_control = 1;
            } else if (keycode == MAGIC_SWAP_LALT_LGUI) {
                keymap_config.swap_lalt_lgui = 1;
            } else if (keycode == MAGIC_SWAP_RALT_RGUI) {
                keymap_config.swap_ralt_rgui = 1;
            } else if (keycode == MAGIC_NO_GUI) {
                keymap_config.no_gui = 1;
            } else if (keycode == MAGIC_SWAP_GRAVE_ESC) {
                keymap_config.swap_grave_esc = 1;
            } else if (keycode == MAGIC_SWAP_BACKSLASH_BACKSPACE) {
                keymap_config.swap_backslash_backspace = 1;
            } else if (keycode == MAGIC_HOST_NKRO) {
                keymap_config.nkro = 1;
            } else if (keycode == MAGIC_SWAP_ALT_GUI) {
                keymap_config.swap_lalt_lgui = 1;
                keymap_config.swap_ralt_rgui = 1;
            }
            /* UNs */
            else if (keycode == MAGIC_UNSWAP_CONTROL_CAPSLOCK) {
                keymap_config.swap_control_capslock = 0;
            } else if (keycode == MAGIC_UNCAPSLOCK_TO_CONTROL) {
                keymap_config.capslock_to_control = 0;
            } else if (keycode == MAGIC_UNSWAP_LALT_LGUI) {
                keymap_config.swap_lalt_lgui = 0;
            } else if (keycode == MAGIC_UNSWAP_RALT_RGUI) {
                keymap_config.swap_ralt_rgui = 0;
            } else if (keycode == MAGIC_UNNO_GUI) {
                keymap_config.no_gui = 0;
            } else if (keycode == MAGIC_UNSWAP_GRAVE_ESC) {
                keymap_config.swap_grave_esc = 0;
            } else if (keycode == MAGIC_UNSWAP_BACKSLASH_BACKSPACE) {
                keymap_config.swap_backslash_backspace = 0;
            } else if (keycode == MAGIC_UNHOST_NKRO) {
                keymap_config.nkro = 0;
            } else if (keycode == MAGIC_UNSWAP_ALT_GUI) {
                keymap_config.swap_lalt_lgui = 0;
                keymap_config.swap_ralt_rgui = 0;
            }
            eeconfig_write_keymap(keymap_config.raw);
            break;
        case 0x5100 ... 0x5FFF: ;
            // Layer movement shortcuts
            // See .h to see constraints/usage
            int type = (keycode >> 0x8) & 0xF;
            if (type == 0x1) {
                // Layer set "GOTO"
                int when = (keycode >> 0x4) & 0x3;
                int layer = keycode & 0xF;
                action.code = ACTION_LAYER_SET(layer, when);
            } else if (type == 0x2) {
                // Momentary layer
                int layer = keycode & 0xFF;
                action.code = ACTION_LAYER_MOMENTARY(layer);
            } else if (type == 0x3) {
                // Set default layer
                int layer = keycode & 0xFF;
                action.code = ACTION_DEFAULT_LAYER_SET(layer);
            } else if (type == 0x4) {
                // Set default layer
                int layer = keycode & 0xFF;
                action.code = ACTION_LAYER_TOGGLE(layer);
            }
            break;
    #ifdef MIDI_ENABLE
        case 0x6000 ... 0x6FFF:
            action.code =  ACTION_FUNCTION_OPT(keycode & 0xFF, (keycode & 0x0F00) >> 8);
            break;
    #endif
        case 0x7000 ... 0x7FFF:
            action.code = ACTION_MODS_TAP_KEY((keycode >> 0x8) & 0xF, keycode & 0xFF);
            break;
        case 0x8000 ... 0x8FFF:
            action.code = ACTION_LAYER_TAP_KEY((keycode >> 0x8) & 0xF, keycode & 0xFF);
            break;
    #ifdef UNICODE_ENABLE
        case 0x8000000 ... 0x8FFFFFF:
            uint16_t unicode = keycode & ~(0x8000);
            action.code =  ACTION_FUNCTION_OPT(unicode & 0xFF, (unicode & 0xFF00) >> 8);
            break;
    #endif
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

void update_tri_layer(uint8_t layer1, uint8_t layer2, uint8_t layer3) {
  if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2)) {
    layer_on(layer3);
  } else {
    layer_off(layer3);
  }
}
