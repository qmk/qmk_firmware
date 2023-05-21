// Copyright 2023 Thong (@thong-phn)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

//----------------------------------------------------------------
// RGB Underglow settings
#define RGBLED_NUM 22
#define RGBLIGHT_LED_MAP {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21}
#define RGBLIGHT_LAYERS
// PWM Configuration 
#define WS2812_PWM_DRIVER PWMD2 
#define WS2812_PWM_CHANNEL 1  
#define WS2812_DMA_STREAM STM32_DMA1_STREAM2