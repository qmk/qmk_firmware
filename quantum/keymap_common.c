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
#if defined(__AVR__)
#include <util/delay.h>
#include <stdio.h>
#endif
#include "action.h"
#include "action_macro.h"
#include "debug.h"
#include "backlight.h"
#include "quantum.h"

#ifdef SPLIT_KEYBOARD
    #include "split_flags.h"
#endif

#ifdef MIDI_ENABLE
	#include "process_midi.h"
#endif

#ifdef CUSTOM_MODIFIED_VALUES_ENABLE
  #include "custom_modified_values.h"
#endif

extern keymap_config_t keymap_config;

#include <inttypes.h>

/* converts key to action */
action_t action_for_key(uint8_t layer, keypos_t key)
{
    // 16bit keycodes - important
    uint16_t keycode = keymap_key_to_keycode(layer, key);

    // keycode remapping
    keycode = keycode_config(keycode);

    action_t action;
    uint8_t action_layer, when, mod;

    switch (keycode) {
        case KC_FN0 ... KC_FN31:
            action.code = keymap_function_id_to_action(FN_INDEX(keycode));
            break;
        case KC_A ... KC_EXSEL:
        case KC_LCTRL ... KC_RGUI:
            action.code = ACTION_KEY(keycode);
            break;
        case KC_SYSTEM_POWER ... KC_SYSTEM_WAKE:
            action.code = ACTION_USAGE_SYSTEM(KEYCODE2SYSTEM(keycode));
            break;
        case KC_AUDIO_MUTE ... KC_MEDIA_REWIND:
            action.code = ACTION_USAGE_CONSUMER(KEYCODE2CONSUMER(keycode));
            break;
        case KC_MS_UP ... KC_MS_ACCEL2:
            action.code = ACTION_MOUSEKEY(keycode);
            break;
        case KC_TRNS:
            action.code = ACTION_TRANSPARENT;
            break;
        case QK_MODS ... QK_MODS_MAX: ;
            // Has a modifier
            // Split it up
            action.code = ACTION_MODS_KEY(keycode >> 8, keycode & 0xFF); // adds modifier to key
            break;
        case QK_FUNCTION ... QK_FUNCTION_MAX: ;
            // Is a shortcut for function action_layer, pull last 12bits
            // This means we have 4,096 FN macros at our disposal
            action.code = keymap_function_id_to_action( (int)keycode & 0xFFF );
            break;
        case QK_MACRO ... QK_MACRO_MAX:
            if (keycode & 0x800) // tap macros have upper bit set
                action.code = ACTION_MACRO_TAP(keycode & 0xFF);
            else
                action.code = ACTION_MACRO(keycode & 0xFF);
            break;
        case QK_LAYER_TAP ... QK_LAYER_TAP_MAX:
            action.code = ACTION_LAYER_TAP_KEY((keycode >> 0x8) & 0xF, keycode & 0xFF);
            break;
        case QK_TO ... QK_TO_MAX: ;
            // Layer set "GOTO"
            when = (keycode >> 0x4) & 0x3;
            action_layer = keycode & 0xF;
            action.code = ACTION_LAYER_SET(action_layer, when);
            break;
        case QK_MOMENTARY ... QK_MOMENTARY_MAX: ;
            // Momentary action_layer
            action_layer = keycode & 0xFF;
            action.code = ACTION_LAYER_MOMENTARY(action_layer);
            break;
        case QK_DEF_LAYER ... QK_DEF_LAYER_MAX: ;
            // Set default action_layer
            action_layer = keycode & 0xFF;
            action.code = ACTION_DEFAULT_LAYER_SET(action_layer);
            break;
        case QK_TOGGLE_LAYER ... QK_TOGGLE_LAYER_MAX: ;
            // Set toggle
            action_layer = keycode & 0xFF;
            action.code = ACTION_LAYER_TOGGLE(action_layer);
            break;
        case QK_ONE_SHOT_LAYER ... QK_ONE_SHOT_LAYER_MAX: ;
            // OSL(action_layer) - One-shot action_layer
            action_layer = keycode & 0xFF;
            action.code = ACTION_LAYER_ONESHOT(action_layer);
            break;
        case QK_ONE_SHOT_MOD ... QK_ONE_SHOT_MOD_MAX: ;
            // OSM(mod) - One-shot mod
            mod = keycode & 0xFF;
            action.code = ACTION_MODS_ONESHOT(mod);
            break;
        case QK_LAYER_TAP_TOGGLE ... QK_LAYER_TAP_TOGGLE_MAX:
            action.code = ACTION_LAYER_TAP_TOGGLE(keycode & 0xFF);
            break;
        case QK_LAYER_MOD ... QK_LAYER_MOD_MAX:
            mod = keycode & 0xF;
            action_layer = (keycode >> 4) & 0xF;
            action.code = ACTION_LAYER_MODS(action_layer, mod);
            break;
        case QK_MOD_TAP ... QK_MOD_TAP_MAX:
            mod = mod_config((keycode >> 0x8) & 0x1F);
            action.code = ACTION_MODS_TAP_KEY(mod, keycode & 0xFF);
            break;
    #ifdef BACKLIGHT_ENABLE
        case BL_ON:
            action.code = ACTION_BACKLIGHT_ON();
            #ifdef SPLIT_KEYBOARD
                BACKLIT_DIRTY = true;
            #endif
            break;
        case BL_OFF:
            action.code = ACTION_BACKLIGHT_OFF();
            #ifdef SPLIT_KEYBOARD
                BACKLIT_DIRTY = true;
            #endif
            break;
        case BL_DEC:
            action.code = ACTION_BACKLIGHT_DECREASE();
            #ifdef SPLIT_KEYBOARD
                BACKLIT_DIRTY = true;
            #endif
            break;
        case BL_INC:
            action.code = ACTION_BACKLIGHT_INCREASE();
            #ifdef SPLIT_KEYBOARD
                BACKLIT_DIRTY = true;
            #endif
            break;
        case BL_TOGG:
            action.code = ACTION_BACKLIGHT_TOGGLE();
            #ifdef SPLIT_KEYBOARD
                BACKLIT_DIRTY = true;
            #endif
            break;
        case BL_STEP:
            action.code = ACTION_BACKLIGHT_STEP();
            #ifdef SPLIT_KEYBOARD
                BACKLIT_DIRTY = true;
            #endif
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

__attribute__ ((weak))
const uint16_t PROGMEM fn_actions[] = {

};

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

#ifdef CUSTOM_MODIFIED_VALUES_ENABLE
static uint16_t cmv_buffer[4] = {0,0,0,0};

bool set_cmv_buffer(uint16_t kc_default, uint16_t kc_shifted, uint16_t kc_altgred, uint16_t kc_sftralt) {
  cmv_buffer[0] = kc_default;
  cmv_buffer[1] = kc_shifted;
  cmv_buffer[2] = kc_altgred;
  cmv_buffer[3] = kc_sftralt;
  return false;
}

__attribute__ ((weak))
bool keycodes_for_key(uint16_t default_kc, uint8_t layer, keypos_t key) {
  return true;
}

static uint16_t* get_custom_modified_values_for_key(uint16_t default_kc, uint8_t layer, keypos_t key) {
  if(keycodes_for_key(default_kc, layer, key)) {
    set_cmv_buffer(default_kc, 0, 0, 0);
  }
  return cmv_buffer;
}

static uint8_t get_kcid(uint16_t* kcs) {
  if(are_there_non_charmods()) return 0;
  else if(are_there_shifts() && are_there_ralts() && kcs[3]) return 3;
  else if(are_there_shifts() && kcs[1]) return 1;
  else if(are_there_ralts() && kcs[2]) return 2;
  return 0;
}

static uint16_t keymap_key_to_keycode_cmv(uint8_t layer, keypos_t key) {
  uint8_t kcid = get_kcid(get_custom_modified_values_for_key(pgm_read_word(&keymaps[layer][key.row][key.col]), layer, key));
  if (kcid) {
    set_mods_blocker(true);
  } else {
    set_mods_blocker(false);
  }
  return cmv_buffer[kcid];
}
#endif

// translates key to keycode
__attribute__ ((weak))
uint16_t keymap_key_to_keycode(uint8_t layer, keypos_t key)
{
#if defined(CUSTOM_MODIFIED_VALUES_ENABLE)
    return keymap_key_to_keycode_cmv(layer, key);
#else
    // Read entire word (16bits)
    return pgm_read_word(&keymaps[(layer)][(key.row)][(key.col)]);
#endif
}

// translates function id to action
__attribute__ ((weak))
uint16_t keymap_function_id_to_action( uint16_t function_id )
{
    // The compiler sees the empty (weak) fn_actions and generates a warning
    // This function should not be called in that case, so the warning is too strict
    // If this function is called however, the keymap should have overridden fn_actions, and then the compile
    // is comparing against the wrong array
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Warray-bounds"
	return pgm_read_word(&fn_actions[function_id]);
    #pragma GCC diagnostic pop
}
