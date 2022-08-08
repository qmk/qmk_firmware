// Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once
// because layouts seem to not be respecting config.h order atm

//#ifdef RGB_MATRIX_ENABLE
//#    define RGB_MATRIX_STARTUP_MODE RGB_MATRIX_SOLID_COLOR
//#endif

#ifndef QMK_KEYS_PER_SCAN
#    define QMK_KEYS_PER_SCAN 8
#endif

//#ifdef MOUSEKEY_ENABLE
//// mouse movement config
//#    ifdef MK_3_SPEED
//#        undef MK_3_SPEED
//#    endif
//#    define MK_KINETIC_SPEED
//#    ifdef MK_KINETIC_SPEED
//#        ifndef MOUSEKEY_DELAY
//#            define MOUSEKEY_DELAY 8
//#        endif
//#        ifndef MOUSEKEY_INTERVAL
//#            define MOUSEKEY_INTERVAL 20
//#        endif
//#        ifndef MOUSEKEY_MOVE_DELTA
//#            define MOUSEKEY_MOVE_DELTA 25
//#        endif
//#    else
//#        ifndef MOUSEKEY_DELAY
//#            define MOUSEKEY_DELAY 300
//#        endif
//#        ifndef MOUSEKEY_INTERVAL
//#            define MOUSEKEY_INTERVAL 50
//#        endif
//#        ifndef MOUSEKEY_MOVE_DELTA
//#            define MOUSEKEY_MOVE_DELTA 5
//#        endif
//#    endif
//#    ifndef MOUSEKEY_MAX_SPEED
//#        define MOUSEKEY_MAX_SPEED 7
//#    endif
//#    ifndef MOUSEKEY_TIME_TO_MAX
//#        define MOUSEKEY_TIME_TO_MAX 60
//#    endif
//#    ifndef MOUSEKEY_INITIAL_SPEED
//#        define MOUSEKEY_INITIAL_SPEED 100
//#    endif
//#    ifndef MOUSEKEY_BASE_SPEED
//#        define MOUSEKEY_BASE_SPEED 1000
//#    endif
//#    ifndef MOUSEKEY_DECELERATED_SPEED
//#        define MOUSEKEY_DECELERATED_SPEED 400
//#    endif
//#    ifndef MOUSEKEY_ACCELERATED_SPEED
//#        define MOUSEKEY_ACCELERATED_SPEED 3000
//#    endif
//// mouse scroll config
//#    ifndef MOUSEKEY_WHEEL_DELAY
//#        define MOUSEKEY_WHEEL_DELAY 15
//#    endif
//#    ifndef MOUSEKEY_WHEEL_DELTA
//#        define MOUSEKEY_WHEEL_DELTA 1
//#    endif
//#    ifndef MOUSEKEY_WHEEL_INTERVAL
//#        define MOUSEKEY_WHEEL_INTERVAL 50
//#    endif
//#    ifndef MOUSEKEY_WHEEL_MAX_SPEED
//#        define MOUSEKEY_WHEEL_MAX_SPEED 8
//#    endif
//#    ifndef MOUSEKEY_WHEEL_TIME_TO_MAX
//#        define MOUSEKEY_WHEEL_TIME_TO_MAX 80
//#    endif
//// mouse scroll kinetic config
//#    ifndef MOUSEKEY_WHEEL_INITIAL_MOVEMENTS
//#        define MOUSEKEY_WHEEL_INITIAL_MOVEMENTS 8
//#    endif
//#    ifndef MOUSEKEY_WHEEL_BASE_MOVEMENTS
//#        define MOUSEKEY_WHEEL_BASE_MOVEMENTS 48
//#    endif
//#    ifndef MOUSEKEY_WHEEL_ACCELERATED_MOVEMENTS
//#        define MOUSEKEY_WHEEL_ACCELERATED_MOVEMENTS 48
//#    endif
//#    ifndef MOUSEKEY_WHEEL_DECELERATED_MOVEMENTS
//#        define MOUSEKEY_WHEEL_DECELERATED_MOVEMENTS 8
//#    endif
//#endif  // MOUSEKEY_ENABLE

#if !defined(LAYER_STATE_16BIT) && !defined(LAYER_STATE_8BIT) && !defined(LAYER_STATE_32BIT)
#    define LAYER_STATE_16BIT
#endif
// #ifndef DYNAMIC_KEYMAP_LAYER_COUNT
// #    define DYNAMIC_KEYMAP_LAYER_COUNT 1
// #endif
