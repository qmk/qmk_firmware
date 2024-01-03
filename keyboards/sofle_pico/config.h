// Copyright 2023 Ryan Neff (@JellyTitan)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

// Split Keyboard Stuff
#define EE_HANDS                 // Sets the keyboard’s handedness using EEPROM
#define SERIAL_USART_FULL_DUPLEX // Use full duplex communication (TRRS)
#define SERIAL_USART_TX_PIN GP16 // USART TX pin
#define SERIAL_USART_RX_PIN GP17  // USART RX pin
#define SERIAL_USART_PIN_SWAP  // Swap TX and RX pins if keyboard is master halve. (Only available on some MCUs)

// I2C for OLEDs        
#define I2C_DRIVER I2CD1
#define I2C1_SDA_PIN GP6
#define I2C1_SCL_PIN GP7

#ifdef OLED_ENABLE
  #define OLED_DISPLAY_128X64
  #define OLED_TIMEOUT 30000
#endif

/* - Encoder settings - */
#ifdef ENCODER_MAP_ENABLE
// Key delay for encoders (necessary for some keycodes)
#    define ENCODER_MAP_KEY_DELAY 10
#endif

/* Allows for the setting of constant mouse speed levels. */
/* Not all mouse wheel config settings are currently supported in .json config.*/
/* https://github.com/qmk/qmk_firmware/blob/master/docs/reference_info_json.md */
/* Step size */
#define MOUSEKEY_MOVE_DELTA 8
/* Maximum number of scroll steps per scroll action */
#define MOUSEKEY_WHEEL_MAX_SPEED 42
/* Time until maximum scroll speed is reached */
#define MOUSEKEY_WHEEL_TIME_TO_MAX 15

#define POINTING_DEVICE_ROTATION_90
#define SPLIT_POINTING_ENABLE
#define POINTING_DEVICE_RIGHT
#define POINTING_DEVICE_TASK_THROTTLE_MS 8
/*
    - RGB Stuff -
    All effects can be found in the QMK docs:
    https://docs.qmk.fm/#/feature_rgb_matrix?id=rgb-matrix-effects
*/
#ifdef RGB_MATRIX_ENABLE

// Decrease decay of heatmap rgb effect
#    define RGB_MATRIX_TYPING_HEATMAP_DECREASE_DELAY_MS 50
// If you're setting colors per key, this is required.
#    define SPLIT_LAYER_STATE_ENABLE

// Turns off RGB effects when there is no longer a USB connection
#    define RGB_DISABLE_WHEN_USB_SUSPENDED

#endif

// Allows for more than the default 4 layers in VIA.
#define DYNAMIC_KEYMAP_LAYER_COUNT 5
