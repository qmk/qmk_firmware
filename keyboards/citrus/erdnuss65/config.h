// Copyright 2023 Citrus Lab
// SPDX-License-Identifier: GPL-2.0
#pragma once

#include "config_common.h"

// The pin connected to the data pin of the LEDs
#define RGBLIGHT_LAYERS//允许您定义可打开或关闭的照明层。非常适合显示当前键盘层或大写锁定状态。
#define RGBLIGHT_LAYERS_OVERRIDE_RGB_OFF//如果已定义，则即使 RGB 光源处于关闭状态，也会显示照明图层。

#define LOCKING_SUPPORT_ENABLE
#define LOCKING_RESYNC_ENABLE//尝试使开关状态与键盘指示灯状态保持一致

