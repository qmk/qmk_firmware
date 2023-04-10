#pragma once
#include "T4CORUN.h"

bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record);
uint16_t get_quick_tap_term(uint16_t keycode, keyrecord_t *record);
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record);