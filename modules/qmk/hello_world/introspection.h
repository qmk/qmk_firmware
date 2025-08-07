// Copyright 2025 Nick Brassel (@tzarc)
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H

typedef struct hello_world_introspection_t {
    int16_t total_size;
    int16_t layer_count;
} hello_world_introspection_t;

hello_world_introspection_t hello_world_introspection(void);
