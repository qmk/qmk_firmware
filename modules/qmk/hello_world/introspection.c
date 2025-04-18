// Copyright 2025 Nick Brassel (@tzarc)
// SPDX-License-Identifier: GPL-2.0-or-later

hello_world_introspection_t hello_world_introspection(void) {
    hello_world_introspection_t introspection = {
        .total_size  = sizeof(keymaps),
        .layer_count = sizeof(keymaps) / sizeof(keymaps[0]),
    };
    return introspection;
}
