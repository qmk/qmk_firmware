// Copyright 2024 QMK
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

// Debounce: press registers immediately, 5ms defer on release only
#define DEBOUNCE 5

// No delay on tap-hold tap output (eager debounce makes this safe)
// keyboard.json defines this as 10 — override it here
#undef TAP_CODE_DELAY
#define TAP_CODE_DELAY 0

// Always-on NKRO (safe for direct USB on Windows)
#define NKRO_DEFAULT_ON true

// RGB Matrix: full brightness allowed, current limited at driver level
#define RGB_MATRIX_MAXIMUM_BRIGHTNESS 255
#define AW20216S_GLOBAL_CURRENT_MAX   150

// Default: solid red
#define RGB_MATRIX_DEFAULT_MODE RGB_MATRIX_SOLID_COLOR
#define RGB_MATRIX_DEFAULT_HUE  0
#define RGB_MATRIX_DEFAULT_SAT  255
#define RGB_MATRIX_DEFAULT_VAL  255
#define RGB_MATRIX_DEFAULT_SPD  128

// Turn off LEDs after 5 minutes idle, and when PC suspends USB
#define RGB_MATRIX_TIMEOUT 300000
#define RGB_MATRIX_SLEEP

// Physical dimensions of the GMMK Pro Rev1 ANSI (75% keyboard) in micrometers
// Used by the LampArray feature for Windows Dynamic Lighting
// Width: ~356mm, Height: ~133mm, Depth: 30mm
#define ESTIMATED_KEYBOARD_WIDTH  356000
#define ESTIMATED_KEYBOARD_HEIGHT 133000
#define LAMPARRAY_DEPTH           30000
