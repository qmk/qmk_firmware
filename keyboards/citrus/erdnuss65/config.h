// Copyright 2023 Citrus Lab
// SPDX-License-Identifier: GPL-2.0
#pragma once

#include "config_common.h"

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 15

#define MATRIX_ROW_PINS { B10, B1, B0, A7, A6 }
#define MATRIX_COL_PINS { B12, B14, B15, A8, B13, B7, B8, B9, A1, A2, A0, A3, A4, A5, B11 }

/* COL2ROW, ROW2COL*/
#define DIODE_DIRECTION COL2ROW

// The pin connected to the data pin of the LEDs
#define RGB_DI_PIN A15
#define RGBLIGHT_LAYERS//允许您定义可打开或关闭的照明层。非常适合显示当前键盘层或大写锁定状态。
#define RGBLIGHT_LAYERS_OVERRIDE_RGB_OFF//如果已定义，则即使 RGB 光源处于关闭状态，也会显示照明图层。
#ifdef RGB_DI_PIN 
// The number of LEDs connected
#define RGBLED_NUM 1
#define RGBLIGHT_HUE_STEP 8
#define RGBLIGHT_SAT_STEP 8
#define RGBLIGHT_VAL_STEP 8
#define RGBLIGHT_LIMIT_VAL 200

#endif

#define FORCE_NKRO

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

#define LOCKING_SUPPORT_ENABLE
#define LOCKING_RESYNC_ENABLE//尝试使开关状态与键盘指示灯状态保持一致

