// Copyright 2025 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "compiler_support.h"

#include "eeconfig.h"

typedef union autocorrect_config_t {
    uint8_t raw;
    struct {
        bool enabled : 1;
        uint8_t current_dict : 3;
    };
} autocorrect_config_t;

STATIC_ASSERT(sizeof(autocorrect_config_t) == sizeof(uint8_t), "Keycode (magic) EECONFIG out of spec.");

extern autocorrect_config_t autocorrect_config;

bool autocorrect_is_enabled(void);
void autocorrect_enable(void);
void autocorrect_disable(void);
void autocorrect_toggle(void);

void autocorrect_dict_cycle(bool forward);
void autocorrect_init(void);

bool apply_autocorrect(uint8_t backspaces, const char *str, char *typo, char *correct);
