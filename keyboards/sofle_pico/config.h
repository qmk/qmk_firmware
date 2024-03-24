// Copyright 2024 Ryan Neff (@JellyTitan)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/* Split Keyboard Stuff */
#define EE_HANDS
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

#ifdef OLED_ENABLE
#    define OLED_DISPLAY_128X64
#    define OLED_TIMEOUT 30000
#endif

/* Encoder settings */
#ifdef ENCODER_MAP_ENABLE
#    define ENCODER_MAP_KEY_DELAY 10
#endif

/* Mouse settings */
#define MOUSEKEY_MOVE_DELTA 8
#define MOUSEKEY_WHEEL_MAX_SPEED 42
#define MOUSEKEY_WHEEL_TIME_TO_MAX 15
#define POINTING_DEVICE_ROTATION_90
#define SPLIT_POINTING_ENABLE
#define POINTING_DEVICE_RIGHT
#define POINTING_DEVICE_TASK_THROTTLE_MS 8

#ifdef RGB_MATRIX_ENABLE
#    define RGB_MATRIX_TYPING_HEATMAP_DECREASE_DELAY_MS 50
/* If you're setting colors per key, this is required */
#    define SPLIT_LAYER_STATE_ENABLE
/* Turns off RGB effects when there is no longer a USB connection */
#    define RGB_DISABLE_WHEN_USB_SUSPENDED
#endif

/* Allows for more than the default 4 layers in VIA. */
#ifndef DYNAMIC_KEYMAP_LAYER_COUNT
#    define DYNAMIC_KEYMAP_LAYER_COUNT 5
#endif
