// Copyright 2023 FxStudio <FXS@fx-studio.cn>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define SPLIT_USB_DETECT
#define SPLIT_WATCHDOG_ENABLE           //监视程序
//#define SPLIT_MAX_CONNECTION_ERRORS 20

#define SPLIT_TRANSPORT_MIRROR
#define SPLIT_ACTIVITY_ENABLE

#ifdef SPLIT_KEYBOARD
    #define FORCED_SYNC_THROTTLE_MS 100
    #define SPLIT_HAND_PIN C13
    #define SERIAL_USART_SPEED 137000
    #define SELECT_SOFT_SERIAL_SPEED 1
    #define SERIAL_USART_DRIVER SD1
    #define SERIAL_USART_TX_PAL_MODE 7
#endif

#define WS2812_PWM_COMPLEMENTARY_OUTPUT
#define WS2812_PWM_DRIVER PWMD1
#define WS2812_PWM_CHANNEL 1
#define WS2812_PWM_PAL_MODE 1
#define WS2812_DMA_STREAM STM32_DMA2_STREAM5
#define WS2812_DMA_CHANNEL 6

/* Disable RGB lighting when PC is in suspend */
#define RGB_DISABLE_WHEN_USB_SUSPENDED

#ifdef RGB_MATRIX_ENABLE
    #define RGB_MATRIX_STARTUP_VAL 60
    #define RGB_DISABLE_WHEN_USB_SUSPENDED  // turn off effects when suspended
    #define RGB_MATRIX_STARTUP_MODE RGB_MATRIX_CYCLE_LEFT_RIGHT
#endif


