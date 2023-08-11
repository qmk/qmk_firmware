// Copyright 2023 zzeneg (@zzeneg)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"

typedef enum {
    _QWERTY = 0,
    _GAME,
    _EU,
    _NAV,
    _NUMBER,
    _SYMBOL,
    _FUNC,
    _SYS,
} layer_number;

typedef enum {
    _TIME = 0,
    _VOLUME,
    _LAYOUT,
    _MEDIA_ARTIST,
    _MEDIA_TITLE,
} hid_data_type;

void display_process_raw_hid_data(uint8_t *data, uint8_t length);
void display_process_layer_state(uint8_t layer);
void display_process_caps_word(bool active);
