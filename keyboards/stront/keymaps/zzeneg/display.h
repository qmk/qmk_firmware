// Copyright 2023 zzeneg (@zzeneg)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"

bool display_init(void);
void display_process_raw_hid_data(uint8_t *data, uint8_t length);
void display_process_record(uint16_t keycode, keyrecord_t *record);
void display_process_layer_state(uint8_t layer);
void display_process_caps(bool active);
void display_process_caps_word(bool active);
void display_refresh_data(void);
