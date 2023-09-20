// Copyright 2023 David Hoelscher (@customMK)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

// With 8k FRAM, max out dynamic keymap layers and macros
// 5x16 matrix (160 bytes) and one encoder (4 bytes) consume 164 bytes per layer
// 32 layers consumes 5248 bytes
#define DYNAMIC_KEYMAP_LAYER_COUNT 32

// Most of the remaining space can be used for macros
// QMK Macro keycode range allows up to 128 macros
#define DYNAMIC_KEYMAP_MACRO_COUNT 128
