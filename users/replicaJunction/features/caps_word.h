#pragma once
#include QMK_KEYBOARD_H
#include "rj_keycodes.h"

bool is_caps_word_enabled(void);
void enable_caps_word(void);
void disable_caps_word(void);
void toggle_caps_word(void);

bool process_record_caps_word(uint16_t keycode, const keyrecord_t *record);
