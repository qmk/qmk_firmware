/*
 * Copyright 2024 João Silva @https://github.com/Ghost-Spot
 *
 * This is an adaptation of several pieces of code
 * I found online, starting from a copy of a sofle,
 * as it as the same layout (minus 2 thumb keys),
 * an OLED and an encoder, on each half.
 *
 * Use this at your own discretion!
 *
 */

#pragma once

#define SPLIT_TRANSPORT_MIRROR
#define SPLIT_LAYER_STATE_ENABLE
#define SPLIT_MODS_ENABLE
#define SPLIT_WPM_ENABLE
#define BOTH_SHIFTS_TURNS_ON_CAPS_WORD

#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 1000U

#define SERIAL_USART_FULL_DUPLEX
#define SERIAL_USART_TX_PIN GP3
#define SERIAL_USART_RX_PIN GP16

#define ONESHOT_TAP_TOGGLE 2  /* Tapping this number of times holds the key until tapped once again. */
#define ONESHOT_TIMEOUT 5000  /* Time (in ms) before the one shot key is released */

#define SPLIT_OLED_ENABLE
#define OLED_DISPLAY_128X64
#define OLED_DISPLAY_ADDRESS 0x3C
#define I2C_DRIVER I2CD1
#define I2C1_SDA_PIN GP4
#define I2C1_SCL_PIN GP5

// Force master side determination by USB voltage detect (VBUS sensing) method instead of the default USB data detect method.
// RP2040 microcontrollers like Splinky and Sea Picro have working VBUS detect on GP19 pin. For Pi Pico it's GP24 pin.
#undef SPLIT_USB_DETECT
#define USB_VBUS_PIN GP24
