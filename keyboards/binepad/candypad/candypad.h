// Copyright 2023 binepad (@binepad)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "quantum.h"

#ifdef OLED_ENABLE

#    ifndef OLED_SPLASH_TIMEOUT
#        define OLED_SPLASH_TIMEOUT 2500
#    endif

// clang-format off
enum oled_modes {
    OLED_SPLASH,
    OLED_DEFAULT,
    OLED_OFF,
    __NUM_OLED_MODES
} oled_modes_t;
// clang-format on

bool candypad_render_logo_user(void);
bool candypad_render_logo_kb(void);
bool candypad_render_default_user(void);
bool candypad_render_default_kb(void);

// OLED functions
extern uint8_t  oled_mode;
extern bool     oled_repaint_requested;
extern uint32_t oled_splash_timer;

#endif
