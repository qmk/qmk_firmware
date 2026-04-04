// Copyright 2024 QMK
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

// Debounce: press registers immediately, 5ms defer on release only
#define DEBOUNCE 5

// Physical dimensions of the GMMK Pro Rev1 ANSI (75% keyboard) in micrometers
// Used by the LampArray feature for Windows Dynamic Lighting
// Width: ~356mm, Height: ~133mm, Depth: 30mm
#define ESTIMATED_KEYBOARD_WIDTH  356000
#define ESTIMATED_KEYBOARD_HEIGHT 133000
#define LAMPARRAY_DEPTH           30000
