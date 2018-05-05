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
            break;
        case BL_OFF:
            action.code = ACTION_BACKLIGHT_OFF();
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
#define CHAR_MODS_SET 0b01100010

typedef struct {
  uint16_t kc;
  uint8_t row;
  uint8_t col;
  uint8_t layer   :5;
  bool transp_res :1;
  bool is_pressed :1;
  bool not_from_q :1;
} cached_key_t;

struct {
  uint8_t lsft :2;
  uint8_t rsft :2;
  uint8_t ralt :2;
  bool other   :1;
} mods_state;

typedef struct {
  keypos_t k;
  uint8_t i :2;
  uint16_t kc[4];
} heldkey_t;

struct heldkeys {
  int8_t i :4;
#ifdef CMV_COMPLETE_VERSION
  bool dakpe   :1; // Dynamic Active Key Processing Enabled
#ifndef CMV_NO_DELAY_AFTER_MODIFIER_RELEASE
  bool damre   :1; // Delay After Modifier Release Enabled
#endif
#endif
  heldkey_t all[CMV_NUMBER_OF_HELD_KEYS];
};

static struct heldkeys held_keys = {.i = -1};
static cached_key_t cached_key = {.row = 255, .col = 255};
static uint16_t cmv_buffer[4] = {0,0,0,0};


bool set_cmv_buffer(uint16_t kc_default, uint16_t kc_shifted, uint16_t kc_altgred, uint16_t kc_sftralt) {
  cmv_buffer[0] = kc_default;
  cmv_buffer[1] = kc_shifted;
  cmv_buffer[2] = kc_altgred;
  cmv_buffer[3] = kc_sftralt;
  return false;
}

__attribute__ ((weak))
bool keycodes_for_key(uint16_t default_kc, uint8_t layer, uint8_t row, uint8_t col) {
  return true;
}

static uint16_t* get_modified_values_for_key(uint16_t default_kc, uint8_t layer, uint8_t row, uint8_t col) {
  if(keycodes_for_key(default_kc, layer, row, col)) {
    set_cmv_buffer(default_kc, 0, 0, 0);
  }
  return cmv_buffer;
}

#ifdef CMV_COMPLETE_VERSION
bool get_dynamic_active_key_processing(void) {
  return held_keys.dakpe;
}

bool set_dynamic_active_key_processing(bool new_state) {
  return (held_keys.dakpe = new_state);
}

#ifndef CMV_NO_DELAY_AFTER_MODIFIER_RELEASE
bool get_delay_after_modifier_release(void) {
  return held_keys.damre;
}

bool set_delay_after_modifier_release(bool new_state) {
  return (held_keys.damre = new_state);
}
#endif

static void add_to_q_release_and_press(
  heldkey_t* active_held_key,
  uint8_t new_kcid
#ifndef CMV_NO_DELAY_AFTER_MODIFIER_RELEASE
  , uint32_t additional_time
#endif
) {
  // print("add_to_q_release_and_press.\n");
  keyevent_describer_t ke_descr = {
    .row = active_held_key->k.row,
    .col = active_held_key->k.col,
    .p = false,
    .kcid = active_held_key->i
#ifndef CMV_NO_DELAY_AFTER_MODIFIER_RELEASE
    , .time = timer_read32()
#endif
  };
  push_key_to_q(ke_descr);
  ke_descr.p = true;
  ke_descr.kcid = new_kcid;
#ifndef CMV_NO_DELAY_AFTER_MODIFIER_RELEASE
  ke_descr.time = timer_read32() + additional_time;
#endif
  push_key_to_q(ke_descr);
}
#endif

static heldkey_t* get_active_held_key(bool only_non_modifier) {
  if(held_keys.i == -1) return NULL;
  if(!only_non_modifier) return &(held_keys.all[held_keys.i]);
  int8_t i = held_keys.i;
  for(; i >= 0; i--) {
    heldkey_t* key = &(held_keys.all[i]);
    if(!IS_MOD(key->kc[key->i])) return key;
  }
  return NULL;
}

static bool add_held_key(heldkey_t new_key) {
  if(held_keys.i == CMV_NUMBER_OF_HELD_KEYS - 1) return false;
  held_keys.all[++(held_keys.i)] = new_key;
  return true;
}

static heldkey_t* remove_held_key(uint8_t id) {
  // print("Removing a held key from the array.\n");
  uint8_t i = 0;
  for(; i <= held_keys.i; i++) {
    if(i > id) {
      held_keys.all[i - 1] = held_keys.all[i];
    }
  }
  held_keys.i = i-2;
  return get_active_held_key(true);
}

static int8_t get_held_key_id(uint8_t row, uint8_t col) {
  uint8_t i = 0;
  for(; i <= held_keys.i; i++) {
    heldkey_t* key = &(held_keys.all[i]);
    if(key->k.row == row && key->k.col == col) {
      return i;
    }
  }
  return -1;
}

static void add_modifiers(bool sft, bool ralt) {
  if(sft && mods_state.lsft) add_mods(MOD_BIT(KC_LSFT));
  if(sft && mods_state.rsft) add_mods(MOD_BIT(KC_RSFT));
  if(ralt && mods_state.ralt) add_mods(MOD_BIT(KC_RALT));
}

static uint8_t get_kcid(uint16_t* kcs) {
  if(mods_state.other) return 0;
  else if((mods_state.lsft || mods_state.rsft) && mods_state.ralt && kcs[3]) return 3;
  else if((mods_state.lsft || mods_state.rsft) && kcs[1]) return 1;
  else if(mods_state.ralt && kcs[2]) return 2;
  return 0;
}

static uint16_t keymap_key_to_keycode_cmv(uint8_t layer, keypos_t key) {
  bool is_pressed = get_current_record()->event.pressed;
  if(
    is_pressed == cached_key.is_pressed
    && key.row == cached_key.row && key.col == cached_key.col
    && (layer == cached_key.layer || (cached_key.transp_res && cached_key.kc != KC_TRANSPARENT))
#ifdef CMV_COMPLETE_VERSION
    && cached_key.not_from_q == (get_key_q()->c == -1)
#endif
  ) {
    // print("Returning cached keycode.\n");
    return cached_key.kc;
  }
  if(cached_key.transp_res && cached_key.kc != KC_TRANSPARENT) cached_key.transp_res = false;
  // print("+++ New key event being processed +++\n");
  cached_key.is_pressed = is_pressed;
  cached_key.layer = layer;
  cached_key.row = key.row;
  cached_key.col = key.col;
#ifdef CMV_COMPLETE_VERSION
  cached_key.not_from_q = (get_key_q()->c == -1);
#endif
  if(is_pressed) {
    // print("User pressed a key.\n");
    cached_key.kc = pgm_read_word(&keymaps[layer][key.row][key.col]);
    if(cached_key.transp_res) {
      // print("---It is actually a transparency resolution.\n");
      heldkey_t* active_held_key = get_active_held_key(false);
      if((cached_key.kc = get_modified_values_for_key(cached_key.kc, layer, key.row, key.col)[active_held_key->i]) == KC_TRANSPARENT) {
        return KC_TRANSPARENT;
      }
      active_held_key->kc[active_held_key->i] = cached_key.kc;
    }
    uint8_t kcid;
    if(IS_MOD(cached_key.kc)) {
      // print("---Pressed key is a modifier.\n");
      if(cached_key.kc == KC_LSFT && mods_state.lsft != 3) mods_state.lsft++;
      else if(cached_key.kc == KC_RSFT && mods_state.rsft != 3) mods_state.rsft++;
      else if(cached_key.kc == KC_RALT && mods_state.ralt != 3) mods_state.ralt++;
      else mods_state.other = true;
#ifdef CMV_COMPLETE_VERSION
      heldkey_t* active_key = get_active_held_key(true);
      if(held_keys.dakpe && active_key != NULL && active_key->i != (kcid = get_kcid(active_key->kc))) {
        // print("------Adding new key press and release events to the key queue for the new active key.\n");
        add_to_q_release_and_press(
          active_key, kcid
#ifndef CMV_NO_DELAY_AFTER_MODIFIER_RELEASE
          , 0
#endif
        );
      }
#endif
      kcid = 0;
      set_cmv_buffer(cached_key.kc,0,0,0);
    } else {
      // print("---Pressed key is NOT a modifier.\n");
#ifdef CMV_COMPLETE_VERSION
      if(cached_key.not_from_q) {
        // print("------NOT executed from the key queue.\n");
#endif
        kcid = get_kcid(get_modified_values_for_key(cached_key.kc, layer, key.row, key.col));
#ifdef CMV_COMPLETE_VERSION
      } else {
        // print("------Executed from the key queue.\n");
        held_keys.all[get_held_key_id(key.row, key.col)].i = (kcid = get_key_q()->q[get_key_q()->c].kcid);
        get_modified_values_for_key(cached_key.kc, layer, key.row, key.col);
      }
#endif
      if(kcid) {
        if(mods_state.lsft) del_mods(MOD_BIT(KC_LSFT));
        if(mods_state.rsft) del_mods(MOD_BIT(KC_RSFT));
        if(mods_state.ralt) del_mods(MOD_BIT(KC_RALT));
      } else {
        if(mods_state.lsft) add_mods(MOD_BIT(KC_LSFT));
        if(mods_state.rsft) add_mods(MOD_BIT(KC_RSFT));
        if(mods_state.ralt) add_mods(MOD_BIT(KC_RALT));
      }
    }
    if(!cached_key.transp_res) {
#ifdef CMV_COMPLETE_VERSION
      if(cached_key.not_from_q) {
#endif
        // print("---Adding a new held key to the array.\n");
        add_held_key((heldkey_t){
          .k = (keypos_t){.row = key.row, .col = key.col},
          .i = kcid,
          .kc = {cmv_buffer[0],cmv_buffer[1],cmv_buffer[2],cmv_buffer[3]}
        });
#ifdef CMV_COMPLETE_VERSION
      }
#endif
      if((cached_key.kc = cmv_buffer[kcid]) == KC_TRANSPARENT) {
        // print("------Transparency resolution required.\n");
        cached_key.transp_res = true;
      }
    }
  } else {
    cached_key.kc = KC_NO;
#ifdef CMV_COMPLETE_VERSION
    if(cached_key.not_from_q) {
#endif
      // print("Processing user releasing key event.\n");
      if(held_keys.i == -1) return cached_key.kc;
      int8_t released_held_key_id = get_held_key_id(key.row, key.col);
      if(released_held_key_id == -1) return cached_key.kc;
#ifdef CMV_COMPLETE_VERSION
      bool process_new_held_key = true;
#endif
      heldkey_t* released_held_key = &held_keys.all[released_held_key_id];
      if(IS_MOD(released_held_key->kc[0])) {
        // print("---Key released is a modifier.\n");
        cached_key.kc = released_held_key->kc[0];
        if(cached_key.kc == KC_LSFT && mods_state.lsft != 0) mods_state.lsft--;
        else if(cached_key.kc == KC_RSFT && mods_state.rsft != 0) mods_state.rsft--;
        else if(cached_key.kc == KC_RALT && mods_state.ralt != 0) mods_state.ralt--;
        else if((keyboard_report->mods & ~(CHAR_MODS_SET | MOD_BIT(cached_key.kc))) == 0) mods_state.other = false;
      } else {
        // print("---Key released is not a modifier.\n");
        cached_key.kc = released_held_key->kc[released_held_key->i];
#ifdef CMV_COMPLETE_VERSION
        uint8_t i;
        keyevent_describer_t* key_q = get_key_q()->q;
        for(i = 0; i < get_key_q()->c_max; i++) {
          if(key_q[i].row == key.row && key_q[i].col == key.col) {
            // print("------Removing key from the additionnal key queue.\n");
            delete_key_from_q(i);
            break;
          }
        }
        if(released_held_key != get_active_held_key(true)) process_new_held_key = false;
#endif
      }
      released_held_key = remove_held_key(released_held_key_id);
#ifndef CMV_COMPLETE_VERSION
      if(released_held_key == NULL || !get_kcid(released_held_key->kc)) {
        if(mods_state.other) {
          add_modifiers(true,true);
        } else if((mods_state.lsft || mods_state.rsft) && mods_state.ralt) {
          add_modifiers(true,true);
        } else if(mods_state.lsft || mods_state.rsft) {
          add_modifiers(true,false);
        } else if(mods_state.ralt) {
          add_modifiers(false,true);
        }
      }
#else
      if(process_new_held_key) {
        if(released_held_key == NULL || (!held_keys.dakpe && !get_kcid(released_held_key->kc))) {
          if(mods_state.other) {
            add_modifiers(true,true);
          } else if((mods_state.lsft || mods_state.rsft) && mods_state.ralt) {
            add_modifiers(true,true);
          } else if(mods_state.lsft || mods_state.rsft) {
            add_modifiers(true,false);
          } else if(mods_state.ralt) {
            add_modifiers(false,true);
          }
        } else {
          // print("---Adding a release and press event for the new active key.\n");
          if(held_keys.dakpe) {
            add_to_q_release_and_press(
              released_held_key, get_kcid(released_held_key->kc)
#ifndef CMV_NO_DELAY_AFTER_MODIFIER_RELEASE
              ,(IS_MOD(cached_key.kc) ? (held_keys.damre ? CMV_TIME_AFTER_MODIFIER_RELEASE : 0) : 0)
#endif
            );
          }
        }
      }
    } else {
      // print("Processing the releasing event of a key executed from the 'additional keys' queue.\n");
      int8_t key_id = get_held_key_id(key.row, key.col);
      if(key_id != -1) {
        cached_key.kc = held_keys.all[key_id].kc[(get_key_q()->q[get_key_q()->c].kcid)];
      }
    }
#endif
  }
  return cached_key.kc;
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
