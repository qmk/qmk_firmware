// Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

enum unicode_typing_mode {
    UCTM_NO_MODE,
    UCTM_WIDE,
    UCTM_SCRIPT,
    UCTM_BLOCKS,
    UCTM_REGIONAL,
    UCTM_AUSSIE,
    UCTM_ZALGO,
    UCTM_SUPER,
};

extern uint8_t typing_mode;
