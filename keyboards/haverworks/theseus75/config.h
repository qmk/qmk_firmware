// Copyright 2023 Moritz Plattner (@ebastler), Alex Havermale (@haversnail)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/* Defines for configuring the serial driver for split comms (see https://docs.qmk.fm/drivers/serial) */
#define SERIAL_USART_DRIVER SD3    // USART 3

/* Defines for required pins */
#define ID_PIN A13
#define USBSW_PIN A14     // Switches the hub input/output with the MUXes
#define PSW_PIN A15       // Turns the power routing to the USB-C port on/off
#define BUS_B_PIN C13     // Tells the hub to be bus-powered or self-powered (which in turn tells the clients to use 100 mA or 500 mA)
#define USB_VBUS_PIN C15  // Only the master side will have VBUS present at power-up (used to determine master/slave)
#define USBPD_1_PIN F0
#define USBPD_2_PIN F1

/* Additional defines for managing power and state scross split */
#define DISABLE_BUS_POWER_MODE TRUE
#define KB_STATE_SYNC_INTERVAL 500
#define USBPD_ALLOWANCE_CHECK_INTERVAL 100
#define SPLIT_TRANSACTION_IDS_KB RPC_ID_KB_STATE

/* Defines for the RGB matrix */
#define INDICATOR_MAX_BRIGHTNESS 255
#define CAPS_LOCK_LED_INDEX 0 // LED1 on PCB
#define WS2812_EXTERNAL_PULLUP
#define WS2812_PWM_DRIVER PWMD3
#define WS2812_PWM_CHANNEL 4
#define WS2812_PWM_PAL_MODE 10
#define WS2812_DMA_STREAM STM32_DMA1_STREAM2
#define WS2812_DMA_CHANNEL 2
#define WS2812_DMAMUX_ID STM32_DMAMUX1_TIM3_UP
