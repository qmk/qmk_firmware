// Copyright 2022 Nick Brassel (@tzarc)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

#include <stdint.h>

// Get the number of layers defined in the keymap
uint8_t keymap_layer_count(void);

#if defined(ENCODER_ENABLE) && defined(ENCODER_MAP_ENABLE)

// Get the number of layers defined in the encoder map
uint8_t encodermap_layer_count(void);

#endif // defined(ENCODER_ENABLE) && defined(ENCODER_MAP_ENABLE)
