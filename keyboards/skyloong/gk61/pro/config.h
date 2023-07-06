// Copyright 2023 linlin012 (@linlin012)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once


#ifdef RGB_MATRIX_ENABLE
#define DRIVER_COUNT 1
#define RGB_MATRIX_LED_COUNT 64
#define CAPS_LOCK_INDEX 28
#define WIN_MOD_INDEX 16
#define MAC_MOD_INDEX 17
#define WIN_LOCK_INDEX 54

/* RGB Matrix Animation modes. Explicitly enabled
 * For full list of effects, see:
 * https://docs.qmk.fm/#/feature_rgb_matrix?id=rgb-matrix-effects
 */

#define RGB_MATRIX_KEYPRESSES
#define RGB_MATRIX_FRAMEBUFFER_EFFECTS

#endif

#ifdef  IS31FL3743A
#define __flash  PROGMEM
#endif
