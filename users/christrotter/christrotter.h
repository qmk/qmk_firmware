// Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once
#include QMK_KEYBOARD_H
#include "keyrecords/process_records.h"
#include "callbacks.h"

#if defined(RGB_MATRIX_ENABLE)
#    include "rgb/rgb_matrix_stuff.h"
#endif
#ifdef SPLIT_KEYBOARD
#    include "split/transport_sync.h"
#endif
#ifdef POINTING_DEVICE_ENABLE
#    include "pointing/pointing.h"
#endif

enum userspace_layers {
    _QWERTY             = 0,
    FIRST_DEFAULT_LAYER = 0,
    _SYMBOLS,
    _MOUSE,
    _NAV,
};

#define _MACROS _MOUSE

// clang-format off
// this is used in the custom transport sync
typedef union {
    uint32_t raw;
    struct {
        bool    rgb_layer_change     :1;
    };
} userspace_config_t;
// clang-format on

extern userspace_config_t userspace_config;
