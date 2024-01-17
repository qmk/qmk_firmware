// Copyright 2023 customMK
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

// With 8k FRAM, max out dynamic keymap layers and macros
// 7x6 matrix (84 bytes) and three encoders (12 bytes) consume 96 bytes per layer
// 32 layers consumes 3072 bytes
#define DYNAMIC_KEYMAP_LAYER_COUNT 32

// Most of the remaining space can be used for macros
// QMK Macro keycode range allows up to 128 macros
#define DYNAMIC_KEYMAP_MACRO_COUNT 128
