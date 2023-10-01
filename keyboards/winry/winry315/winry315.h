// Copyright 2022 Sergey Vlasov (@sigprof)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "quantum.h"

// Supported orientations of the board.  The enum values must match the layout
// option values used by VIA.
enum winry315_orientation {
    WINRY315_ORIENTATION_TOP,   // Encoders at the top side (default)
    WINRY315_ORIENTATION_LEFT,  // Encoders at the left side
    WINRY315_ORIENTATION_RIGHT, // Encoders at the right side
    WINRY315_ORIENTATION_BOTTOM // Encoders at the bottom side
};

// Set the orientation of the board (changes the RGB Matrix effect behavior to
// match the new orientation).
//
// This function is intended to be used in the `via` keymap, where the board
// orientation is configured dynamically using a VIA layout option.  If you are
// making a custom keymap for one specific orientation, it is better to set the
// orientation in config.h (e.g., `#define WINRY315_DEFAULT_ORIENTATION
// WINRY315_ORIENTATION_LEFT`) instead of adding custom code that calls this
// function.
void winry315_set_orientation(uint8_t orientation);
