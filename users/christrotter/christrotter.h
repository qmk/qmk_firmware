// Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once
#include QMK_KEYBOARD_H
#include "keyrecords/process_records.h"
#include "callbacks.h"

#ifdef TAP_DANCE_ENABLE
#    include "keyrecords/tap_dances.h"
#endif  // TAP_DANCE_ENABLE
#if defined(RGB_MATRIX_ENABLE)
#    include "rgb/rgb_matrix_stuff.h"
#endif
#ifdef SPLIT_KEYBOARD
#    include "split/transport_sync.h"
#endif
#ifdef POINTING_DEVICE_ENABLE
#    include "pointing/pointing.h"
#endif

//Define layer names 
// the layers are broken after moving them here...why?
enum userspace_layers {
    _QWERTY             = 0,
    FIRST_DEFAULT_LAYER = 0,
    _SYMBOLS,
    _MOUSE,
};

// this is definitely used by the mouse layer trigger stuff...just wrapping our mouse layer name under _MACROS
// but where???? maybe something in QMK? not in the kb or userspace...
#define _MACROS _MOUSE

// clang-format off
// this is used in the custom transport sync
typedef union {
    uint32_t raw;
    struct {
        bool    rgb_layer_change     :1;
        bool    is_overwatch         :1;
//        bool    nuke_switch          :1;
        bool    swapped_numbers      :1;
//        bool    rgb_matrix_idle_anim :1;
//        bool    autocorrection       :1;
    };
} userspace_config_t;
// clang-format on

extern userspace_config_t userspace_config;
