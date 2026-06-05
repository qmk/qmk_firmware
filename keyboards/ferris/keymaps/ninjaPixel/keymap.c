// Copyright 2025 ninjaPixel
// SPDX-License-Identifier: GPL-2.0-or-later
//
// Ferris Sweep keymap — thin wrapper.
//
// All layers, configuration, and shared code live in the userspace at
// users/ninjaPixel-ferris/ (mirroring how the Sofle keymap lives in
// users/ninjaPixel/). This file only pulls in the shared keymap-data header,
// which defines the `keymaps` array. QMK's introspection needs that array to be
// visible inside the keymap compilation unit, which is why it is included here
// rather than compiled as part of the userspace .c file.
//
// Build / flash:  see keyboards/ferris/keymaps/ninjaPixel/readme.md
#include "ninjaPixel_ferris_keymap.h"
