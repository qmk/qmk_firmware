// Copyright 2022 Michael McCoyd (@mmccoyd)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "config_common.h"

/* key matrix size */
// Rows are doubled-up
#define MATRIX_ROWS 10
#define MATRIX_COLS 6

/* Split */
#define SPLIT_HAND_MATRIX_GRID B5, F6
#define MATRIX_MASKED

/* Encoder */
#define ENCODERS_PAD_A { F5 }
#define ENCODERS_PAD_B { F4 }
#define ENCODERS_PAD_A_RIGHT { F4 }
#define ENCODERS_PAD_B_RIGHT { F5 }

#define RGBLIGHT_SLEEP

/* Haptic hardware */
// The Pimoroni is the likely hardware, for which these settings work
#define FB_ERM_LRA 1
#define FB_BRAKEFACTOR 3 /* 1x:0, 2x:1, 3x:2, 4x:3, 6:4, 8:5, 16:6, Disable:7 */
#define FB_LOOPGAIN 1 /* For  Low:0, Medium:1, High:2, Very High:3 */
/* Please refer to your datasheet for optimal setting for your specific motor.*/
#define RATED_VOLTAGE 2
#define V_PEAK 2.8
#define V_RMS 2.0
#define F_LRA 205 /* resonance freq */

/* Haptic waveforms */
// Two mild waveforms
#define DRV_GREETING alert_750ms
#define DRV_MODE_DEFAULT sharp_tick3_60
