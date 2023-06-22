// Copyright 2021 Michael McCoyd (@mmccoyd)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

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
