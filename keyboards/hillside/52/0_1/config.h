// Copyright 2022 Michael McCoyd (@mmccoyd)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once


/* Split */
#define SPLIT_HAND_MATRIX_GRID B5, F6
#define SPLIT_HAND_MATRIX_GRID_LOW_IS_LEFT
#define MATRIX_MASKED

/* Haptic hardware */
// The Pimoroni is the likely hardware, for which these settings work
#define DRV2605L_FB_ERM_LRA 1
#define DRV2605L_FB_BRAKEFACTOR 3 /* 1x:0, 2x:1, 3x:2, 4x:3, 6:4, 8:5, 16:6, Disable:7 */
#define DRV2605L_FB_LOOPGAIN 1 /* For  Low:0, Medium:1, High:2, Very High:3 */
/* Please refer to your datasheet for optimal setting for your specific motor.*/
#define DRV2605L_RATED_VOLTAGE 2
#define DRV2605L_V_PEAK 2.8
#define DRV2605L_V_RMS 2.0
#define DRV2605L_F_LRA 205 /* resonance freq */

/* Haptic waveforms */
// Two mild waveforms
#define DRV2605L_GREETING DRV2605L_EFFECT_750_MS_ALERT_100
#define DRV2605L_DEFAULT_MODE DRV2605L_EFFECT_SHARP_TICK_3_60
