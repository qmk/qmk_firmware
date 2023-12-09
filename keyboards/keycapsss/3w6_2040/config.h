// Copyright 2022 Conor Burns (@Conor-Burns)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

#define SERIAL_USART_FULL_DUPLEX  // Enable full duplex operation mode.
#define SERIAL_USART_TX_PIN GP0   // USART TX pin
#define SERIAL_USART_RX_PIN GP1   // USART RX pin
#define SERIAL_USART_PIN_SWAP     // Swap TX and RX pins if keyboard is master halve.
#define SERIAL_USART_SPEED 921600 // Sped :)
#define USB_VBUS_PIN GP19         // for rp2040 | When USB_VBUS_PIN is not defined, SPLIT_USB_DETECT is used.
#define EE_HANDS                  // Split handedness via eeprom
#define SPLIT_LED_STATE_ENABLE    // Sync host leds (caps lock, ...)
#define SPLIT_LAYER_STATE_ENABLE  // Enables syncing of the layer state between both halves
#define SPLIT_POINTING_ENABLE     // Transmitting the pointing device status to the master side
#define POINTING_DEVICE_RIGHT     // Pointing device on the right side (Required - pick one only)
//#define POINTING_DEVICE_LEFT    // Pointing device on the left side (Required - pick one only)

#define RGBLIGHT_DEFAULT_MODE RGBLIGHT_EFFECT_BREATHING + 2
#define RGBLIGHT_DEFAULT_HUE 152
#define RGBLIGHT_DEFAULT_SAT 232
#define RGBLIGHT_DEFAULT_VAR 255
#define RGBLIGHT_DEFAULT_SPD 2

#define DYNAMIC_KEYMAP_LAYER_COUNT 9
