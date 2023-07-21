// Copyright 2023 JZ-Skyloong (@JZ-Skyloong)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#ifdef ENCODER_ENABLE
#define ENCODERS_PAD_A {A1, A3, A0, C14}
#define ENCODERS_PAD_B { A2, A4, C13, C15 }
#define ENCODER_RESOLUTIONS { 1, 1, 1, 1 }
#define ENCODER_MAP_KEY_DELAY 20
#endif

#ifdef RGB_MATRIX_ENABLE
#define DRIVER_ADDR_2 0b0100011
#define DRIVER_COUNT 2

#define RGB_MATRIX_LED_COUNT 87
#define CAPS_LOCK_INDEX 44
#define WIN_MOD_INDEX 20
#define MAC_MOD_INDEX 21
#define WIN_LOCK_INDEX 75

/* RGB Matrix Animation modes. Explicitly enabled
 * For full list of effects, see:
 * https://docs.qmk.fm/#/feature_rgb_matrix?id=rgb-matrix-effects
 */

#define RGB_MATRIX_KEYPRESSES
#define RGB_MATRIX_FRAMEBUFFER_EFFECTS

#endif
