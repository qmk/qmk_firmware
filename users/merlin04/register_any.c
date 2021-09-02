/* Copyright 2021 Benjamin Smith (@Merlin04)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
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

#include "register_any.h"
#include "action.h"
#include QMK_KEYBOARD_H

// Taken from part of the action_for_key function of tmk_core/common/action.c
// action_for_key takes in a keypos_t with row and column and the layer number and gets the corresponding keycode, then converts that to an action, but I only need the converting part
action_t keycodeToAction(uint16_t keycode) {
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

void register_any(uint16_t keycode, bool pressed) {
    keyrecord_t record = {
        .event = {
            .key = {
                // Position doesn't matter
                .col = 99,
                .row = 99
            },
            .pressed = pressed,
            .time = (timer_read() | 1)
        },
        .tap = {
            .interrupted = true,
            // All of the reserved things are not used I think, it is just to make the data structure the correct size
            .reserved2 = false,
            .reserved1 = false,
            .reserved0 = false,
            .count = 1
        }
    };
    action_t action = keycodeToAction(keycode);

    process_action(&record, action);
}

void tap_any(uint16_t code) {
    register_any(code, true);
#if TAP_CODE_DELAY > 0
    wait_ms(TAP_CODE_DELAY);
#endif
    register_any(code, false);
}
