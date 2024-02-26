// Copyright 2024 Carter Pollan (@Carter Pollan)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

 /* Serial communication */
#define SERIAL_USART_FULL_DUPLEX

 /* Uncomment when flashing left keyboard */
#define SERIAL_USART_TX_PIN GP3
#define SERIAL_USART_RX_PIN GP4

 /* Uncomment when flashing right keyboard */
// #define SERIAL_USART_TX_PIN GP6
// #define SERIAL_USART_RX_PIN GP29

/* Right keyboard kin definitions */
#define MATRIX_COL_PINS_RIGHT { GP4, GP3, GP28, GP27, GP26 }
#define MATRIX_ROW_PINS_RIGHT { GP2, GP1, GP0, GP7 }

/* LED definitions */
#define WS2812_DI_PIN GP12
#define RGBLED_NUM 2
#define RGBLED_SPLIT {1, 1}
#define RGBLIGHT_LAYERS
#define SPLIT_TRANSPORT_MIRROR
#define SPLIT_LAYER_STATE_ENABLE
#define RGBLIGHT_SPLIT
#define RGBLIGHT_LAYERS_OVERRIDE_RGB_OFF