// Copyright 2024 Ryan Neff (@JellyTitan)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/* Use full duplex communication (TRRS) */
#define SERIAL_USART_FULL_DUPLEX
#define SERIAL_USART_TX_PIN GP16
#define SERIAL_USART_RX_PIN GP17
/* Swap TX and RX pins if keyboard is master half. Only available on some MCU's. This _is_ available on the RP2040 */
#define SERIAL_USART_PIN_SWAP

/* I2C for OLEDs */
#define I2C_DRIVER I2CD1
#define I2C1_SDA_PIN GP6
#define I2C1_SCL_PIN GP7

#define OLED_DISPLAY_128X64
#define OLED_TIMEOUT 30000

#define ENCODER_MAP_KEY_DELAY 10

#define RGB_MATRIX_TYPING_HEATMAP_DECREASE_DELAY_MS 50
