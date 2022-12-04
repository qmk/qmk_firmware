// Copyright 2022 David Kristoffersen (@davidkristoffersen)
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include "davidkristoffersen.h"

// Default layer if none is specified
#define LAYER_DEFAULT -1

// Check if layer is an active default layer
#define IS_DEFAULT_ON(layer) is_default_on(layer)
// Check if layer is an inactive default layer
#define IS_DEFAULT_OFF(layer) !is_default_on(layer)

// Return false if test equal false
#define HANDLE_FALSE(bool) if (!bool) return false;
// Generic array lenght define
#define ARR_LEN(arr) (sizeof(arr) / sizeof(arr)[0])
// Printf-like functionality for send_string
#define SEND_VAR(str, ...) \
    do { \
        char var[128]; \
        sprintf(var, str, __VA_ARGS__); \
        send_string(var); \
    } while(0)

// Get special shifted code
uint16_t get_special_shifted_code(uint16_t keycode);

// Get language specific code
uint16_t get_norwegian_code(uint16_t keycode);
