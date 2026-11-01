// Copyright 2026 Andreas Hirschauer
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "quantum.h"

// Layer indices shared by the default keymap and OLED lighting legend.
enum reform4_layers {
    R4_LAYER_BASE,
    R4_LAYER_HYPER,
    R4_LAYER_CIRCLE,
};

typedef enum {
    R4_OLED_NONE,
    R4_OLED_SPLASH,
    R4_OLED_RGB,
} reform4_oled_page_t;

#ifdef OLED_ENABLE
void reform4_oled_show(reform4_oled_page_t page, uint32_t duration_ms);
#else
static inline void reform4_oled_show(reform4_oled_page_t page, uint32_t duration_ms) {}
#endif
