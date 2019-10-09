#pragma once
#include "quantum.h"
#include "version.h"
// #include "eeprom.h"
#include "wrappers.h"
#include "process_records.h"

/* Define layer names */
enum userspace_layers {
    _QWERTY  = 0,
    _NUMLOCK = 0,
    _COLEMAK,
    _DVORAK,
    _WORKMAN,
    _MODS, /* layer 8 */
    _MACROS,
    _MEDIA,
    _LOWER,
    _RAISE,
    _ADJUST,
};

bool          mod_key_press_timer(uint16_t code, uint16_t mod_code, bool pressed);
bool          mod_key_press(uint16_t code, uint16_t mod_code, bool pressed, uint16_t this_timer);
layer_state_t layer_state_set_keymap(layer_state_t state);
layer_state_t default_layer_state_set_keymap(layer_state_t state);
