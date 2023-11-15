
#pragma once
#include "../__init__.h"

bool pre_process_record_user(uint16_t keycode, keyrecord_t *record);
bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record);
uint16_t get_quick_tap_term(uint16_t keycode, keyrecord_t *record);
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record);
