// Copyright 2021 Julian Turner (@JulianTurner)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#undef MANUFACTURER
#define MANUFACTURER Trner

/* Select hand configuration */
#define MASTER_LEFT

// Configure the global tapping term (default: 200ms)
#define TAPPING_TERM 500

// Prevent normal rollover on alphas from accidentally triggering mods.
#define IGNORE_MOD_TAP_INTERRUPT

// Enable rapid switch from tap to hold, disables double tap hold auto-repeat.
#define TAPPING_FORCE_HOLD

//#define OLED_FONT_H "keyboards/crkbd/lib/glcdfont.c"
