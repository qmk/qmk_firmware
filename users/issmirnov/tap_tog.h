#pragma once

#include "issmirnov.h"

extern bool tap_tog_layer_other_key_pressed; // set to true if any key pressed while TAP_TOG_LAYER held down
extern bool tap_tog_layer_toggled_on; // will become true if no keys are pressed while TTL held down
extern uint8_t tap_tog_count; // number of presses on TAP_TOG_LAYER button.

// Tap dance analog with momentary toggle when held, switch when tapped
void process_tap_tog(uint8_t layer, keyrecord_t *record);
