// Copyright 2024 Hyojin Bak (@eerraa)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "quantum.h"

enum my_keycodes {
  BR_UP = QK_KB_0,
  BR_DOWN,
  BK_OUT,
  BK_IN,
  BK_UP,
  BK_DOWN
};

typedef union {
    uint32_t raw;
    struct {
        uint8_t    breathing_period :4;
        uint8_t    blink_value      :2;
        uint8_t    blink_speed      :4;
        
    };
} my_config_t;

extern my_config_t g_my_config;