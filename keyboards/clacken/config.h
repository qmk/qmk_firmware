// Copyright 2024 Carter Pollan (@Carter Pollan)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define MASTER_LEFT

 /* Serial communication */
#define SERIAL_USART_FULL_DUPLEX

 /* Uncomment when flashing left keyboard */
// #define SERIAL_USART_TX_PIN GP3
// #define SERIAL_USART_RX_PIN GP4

 /* Uncomment when flashing right keyboard */
#define SERIAL_USART_TX_PIN GP6
#define SERIAL_USART_RX_PIN GP29


#define PERMISSIVE_HOLD


/* Right keyboard kin definitions */
#define MATRIX_COL_PINS_RIGHT { F5, F6, F7, B1, B3 }
#define MATRIX_ROW_PINS_RIGHT { C6, D4, D0, B1 }

/* LED definitions */
#define WS2812_DI_PIN GP12
// #define RGBLED_NUM 2
// #define RGBLED_SPLIT {1, 1}
// #define RGBLIGHT_LAYERS
#define SPLIT_LAYER_STATE_ENABLE
#define RGBLIGHT_LAYERS_OVERRIDE_RGB_OFF
// #define SPLIT_TRANSPORT_MIRROR
// #define RGBLIGHT_SPLIT
