// Copyright 2023 Javier Oliver (@joliverMI)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/*Split keyboard configuration*/
// Hardware Settings
#define SPLIT_HAND_PIN GP18 //GP18 at High is for Left
#define SERIAL_PIO_USE_PIO1
#define SERIAL_USART_FULL_DUPLEX
#define SERIAL_USART_TX_PIN GP1
#define SERIAL_USART_RX_PIN GP0
#undef USE_I2C

// Communication Settings
#define FORCED_SYNC_THROTTLE_MS 1000
#define SPLIT_MAX_CONNECTION_ERRORS 5
#define SPLIT_CONNECTION_CHECK_TIMEOUT 2000

// RGB Configuration
#define WS2812_DI_PIN GP17
#define RGBLIGHT_EFFECT_BREATHING
#define WS2812_PIO_USE_PIO1
#define NOP_FUDGE 0.4
#define RGBLIGHT_EFFECT_BREATHE_CENTER 2.0 //1.0 to 2.7

// Tap-Hold Settings
#define TAPPING_TERM 100