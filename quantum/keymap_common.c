/*
Copyright 2012-2017 Jun Wako <wakojun@gmail.com>

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
#include "action_layer.h"
#include "action.h"
#include "action_macro.h"
#include "debug.h"
#include "quantum.h"

#ifdef BACKLIGHT_ENABLE
#    include "backlight.h"
#endif

#ifdef MIDI_ENABLE
#    include "process_midi.h"
#endif

extern keymap_config_t keymap_config;

#include <inttypes.h>

/* converts key to action */
action_t action_for_key(uint8_t layer, keypos_t key) {
    // 16bit keycodes - important
    uint16_t keycode = keymap_key_to_keycode(layer, key);
    return action_for_keycode(keycode);
};

action_t action_for_keycode(uint16_t keycode) {
    // keycode remapping
    keycode = keycode_config(keycode);

    action_t action = {};
    uint8_t  action_layer, when, mod;

    (void)action_layer;
    (void)when;
    (void)mod;

    switch (keycode) {
        case KC_A ... KC_EXSEL:
        case KC_LCTRL ... KC_RGUI:
            action.code = ACTION_KEY(keycode);
            break;
#ifdef EXTRAKEY_ENABLE
        case KC_SYSTEM_POWER ... KC_SYSTEM_WAKE:
            action.code = ACTION_USAGE_SYSTEM(KEYCODE2SYSTEM(keycode));
            break;
        case KC_AUDIO_MUTE ... KC_BRIGHTNESS_DOWN:
            action.code = ACTION_USAGE_CONSUMER(KEYCODE2CONSUMER(keycode));
            break;
#endif
#ifdef MOUSEKEY_ENABLE
        case KC_MS_UP ... KC_MS_ACCEL2:
            action.code = ACTION_MOUSEKEY(keycode);
            break;
#endif
        case KC_TRNS:
            action.code = ACTION_TRANSPARENT;
            break;
        case QK_MODS ... QK_MODS_MAX:;
            // Has a modifier
            // Split it up
            action.code = ACTION_MODS_KEY(keycode >> 8, keycode & 0xFF);  // adds modifier to key
            break;
#ifndef NO_ACTION_FUNCTION
        case KC_FN0 ... KC_FN31:
            action.code = keymap_function_id_to_action(FN_INDEX(keycode));
            break;
        case QK_FUNCTION ... QK_FUNCTION_MAX:;
            // Is a shortcut for function action_layer, pull last 12bits
            // This means we have 4,096 FN macros at our disposal
            action.code = keymap_function_id_to_action((int)keycode & 0xFFF);
            break;
#endif
#ifndef NO_ACTION_MACRO
        case QK_MACRO ... QK_MACRO_MAX:
            if (keycode & 0x800)  // tap macros have upper bit set
                action.code = ACTION_MACRO_TAP(keycode & 0xFF);
            else
                action.code = ACTION_MACRO(keycode & 0xFF);
            break;
#endif
#ifndef NO_ACTION_LAYER
        case QK_LAYER_TAP ... QK_LAYER_TAP_MAX:
            action.code = ACTION_LAYER_TAP_KEY((keycode >> 0x8) & 0xF, keycode & 0xFF);
            break;
        case QK_TO ... QK_TO_MAX:;
            // Layer set "GOTO"
            when         = (keycode >> 0x4) & 0x3;
            action_layer = keycode & 0xF;
            action.code  = ACTION_LAYER_SET(action_layer, when);
            break;
        case QK_MOMENTARY ... QK_MOMENTARY_MAX:;
            // Momentary action_layer
            action_layer = keycode & 0xFF;
            action.code  = ACTION_LAYER_MOMENTARY(action_layer);
            break;
        case QK_DEF_LAYER ... QK_DEF_LAYER_MAX:;
            // Set default action_layer
            action_layer = keycode & 0xFF;
            action.code  = ACTION_DEFAULT_LAYER_SET(action_layer);
            break;
        case QK_TOGGLE_LAYER ... QK_TOGGLE_LAYER_MAX:;
            // Set toggle
            action_layer = keycode & 0xFF;
            action.code  = ACTION_LAYER_TOGGLE(action_layer);
            break;
#endif
#ifndef NO_ACTION_ONESHOT
        case QK_ONE_SHOT_LAYER ... QK_ONE_SHOT_LAYER_MAX:;
            // OSL(action_layer) - One-shot action_layer
            action_layer = keycode & 0xFF;
            action.code  = ACTION_LAYER_ONESHOT(action_layer);
            break;
        case QK_ONE_SHOT_MOD ... QK_ONE_SHOT_MOD_MAX:;
            // OSM(mod) - One-shot mod
            mod         = mod_config(keycode & 0xFF);
            action.code = ACTION_MODS_ONESHOT(mod);
            break;
#endif
#ifndef NO_ACTION_LAYER
        case QK_LAYER_TAP_TOGGLE ... QK_LAYER_TAP_TOGGLE_MAX:
            action.code = ACTION_LAYER_TAP_TOGGLE(keycode & 0xFF);
            break;
        case QK_LAYER_MOD ... QK_LAYER_MOD_MAX:
            mod          = mod_config(keycode & 0xF);
            action_layer = (keycode >> 4) & 0xF;
            action.code  = ACTION_LAYER_MODS(action_layer, mod);
            break;
#endif
#ifndef NO_ACTION_TAPPING
        case QK_MOD_TAP ... QK_MOD_TAP_MAX:
            mod         = mod_config((keycode >> 0x8) & 0x1F);
            action.code = ACTION_MODS_TAP_KEY(mod, keycode & 0xFF);
            break;
#endif
#ifdef SWAP_HANDS_ENABLE
        case QK_SWAP_HANDS ... QK_SWAP_HANDS_MAX:
            action.code = ACTION(ACT_SWAP_HANDS, keycode & 0xff);
            break;
#endif

        default:
            action.code = ACTION_NO;
            break;
    }
    return action;
}

__attribute__((weak)) const uint16_t PROGMEM fn_actions[] = {

};

/* Macro */
__attribute__((weak)) const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) { return MACRO_NONE; }

/* Function */
__attribute__((weak)) void action_function(keyrecord_t *record, uint8_t id, uint8_t opt) {}

// translates key to keycode
__attribute__((weak)) uint16_t keymap_key_to_keycode(uint8_t layer, keypos_t key) {
    // Read entire word (16bits)
    return pgm_read_word(&keymaps[(layer)][(key.row)][(key.col)]);
}

// translates function id to action
__attribute__((weak)) uint16_t keymap_function_id_to_action(uint16_t function_id) {
// The compiler sees the empty (weak) fn_actions and generates a warning
// This function should not be called in that case, so the warning is too strict
// If this function is called however, the keymap should have overridden fn_actions, and then the compile
// is comparing against the wrong array
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Warray-bounds"
    return pgm_read_word(&fn_actions[function_id]);
#pragma GCC diagnostic pop
}
