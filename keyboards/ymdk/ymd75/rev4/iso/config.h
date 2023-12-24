// Copyright 2023 zvecr<git@zvecr.com>
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

#define RGB_DISABLE_WHEN_USB_SUSPENDED

#define WS2812_PWM_DRIVER PWMD4
#define WS2812_PWM_CHANNEL 4
#define WS2812_PWM_PAL_MODE 2
#define WS2812_DMA_STREAM STM32_DMA1_STREAM7
#define WS2812_DMA_CHANNEL 7
