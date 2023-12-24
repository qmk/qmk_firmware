// Copyright 2023 FxStudio <FXS@fx-studio.cn>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define SPLIT_WATCHDOG_ENABLE
#define SPLIT_HAND_PIN C13
#define SERIAL_USART_DRIVER SD1
#define SERIAL_USART_TX_PAL_MODE 7

#define WS2812_PWM_COMPLEMENTARY_OUTPUT
#define WS2812_PWM_DRIVER PWMD1
#define WS2812_PWM_CHANNEL 1
#define WS2812_PWM_PAL_MODE 1
#define WS2812_DMA_STREAM STM32_DMA2_STREAM5
#define WS2812_DMA_CHANNEL 6

#define RGB_DISABLE_WHEN_USB_SUSPENDED  // turn off effects when suspended