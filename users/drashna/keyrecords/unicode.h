// Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

enum unicode_typing_modes {
    UCTM_NO_MODE,
    UCTM_WIDE,
    UCTM_SCRIPT,
    UCTM_BLOCKS,
    UCTM_REGIONAL,
    UCTM_AUSSIE,
    UCTM_ZALGO,
    UCTM_SUPER,
    UCTM_COMIC,
    UNCODES_MODE_END,
};

extern uint8_t unicode_typing_mode;
extern const PROGMEM char unicode_mode_str[UNCODES_MODE_END][13];
void set_unicode_input_mode_soft(uint8_t input_mode);
