#pragma once

#include QMK_KEYBOARD_H
#include "jugemu.h"

bool tap_hold_enabled(void);
void set_tap_hold(bool enabled);
void toggle_tap_hold(void);
void init_tap_hold(void);
bool process_tap_hold_record(uint16_t keycode, keyrecord_t *record);
