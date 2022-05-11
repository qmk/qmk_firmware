// Copyright 2022 Kevin Goldberg @kevkevco <hello@kevkev.co>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once
#include QMK_KEYBOARD_H
#include "keycodes.h"
#include "layers.h"

bool is_num_word_enabled(void);
void enable_num_word(void);
void disable_num_word(void);
void toggle_num_word(void);

bool process_record_num_word(uint16_t keycode, const keyrecord_t *record);
