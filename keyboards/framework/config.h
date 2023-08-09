// Copyright 2022 Framework Computer
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

// Allow (emulated) EEPROM reset using VIA
#define VIA_EEPROM_ALLOW_RESET

// Increase to 16K for more storage space
// With 64K backing size, this spread the wear level over 4 blocks
#define WEAR_LEVELING_LOGICAL_SIZE (4 * 4096)
// Increase to 64K backing size to allow more wear leveling
#define WEAR_LEVELING_BACKING_SIZE (16 * 4096)
// We use 1MB flash
#define PICO_FLASH_SIZE_BYTES (1 * 1024 * 1024)
#define WEAR_LEVELING_RP2040_FLASH_SIZE PICO_FLASH_SIZE_BYTES
// Keep the last 4K sector free for the serial number
#define WEAR_LEVELING_RP2040_FLASH_BASE ((PICO_FLASH_SIZE_BYTES) - (WEAR_LEVELING_BACKING_SIZE + 4096))

// Prints every second how many matrix scans were done (Frequency in Hz)
// Only during debugging, since it prevents the host from going to sleep
//#define DEBUG_MATRIX_SCAN_RATE

// Prototype for Framework Laptop 16 with Raspberry Pi Pico
// It'll disable column drive because we need to remap some pins to there
// SDB is mapped to GP22
//#define PICO_FL16

#ifdef KEYBOARD_framework_ansi
#    define LED_CAPS_LOCK_PIN GP24
#elif KEYBOARD_framework_iso
#    define LED_CAPS_LOCK_PIN GP24
#elif KEYBOARD_framework_jis
#    define LED_CAPS_LOCK_PIN GP24
#endif

// PWM single one backlight configuration
// GPIO25 maps to PWM channel 4B of the RP2040
// On the Raspberry Pi Pico this is the green LED on the board, good for prototyping
#define BACKLIGHT_PWM_DRIVER PWMD4
#define BACKLIGHT_PWM_CHANNEL RP2040_PWM_CHANNEL_B
#define BACKLIGHT_BREATHING
// Change PWM frequency to 24kHz, the default of 2048Hz causes loud noise
// TODO: Waiting for PR #21717
// #define BACKLIGHT_PWM_PERIOD BACKLIGHT_PWM_COUNTER_FREQUENCY / 24000

// I2C for the RBG controller
#define I2C_DRIVER I2CD1
#define I2C1_SDA_PIN GP26
#define I2C1_SCL_PIN GP27

// RGB config

#define RGB_DISABLE_WHEN_USB_SUSPENDED

// RGB Matrix Animation modes. Explicitly enabled
// For full list of effects, see:
// https://docs.qmk.fm/#/feature_rgb_matrix?id=rgb-matrix-effects
// 0 = Off
// 1 = Solid Color
// 2
#define ENABLE_RGB_MATRIX_ALPHAS_MODS
#define ENABLE_RGB_MATRIX_GRADIENT_UP_DOWN
#define ENABLE_RGB_MATRIX_GRADIENT_LEFT_RIGHT
#define ENABLE_RGB_MATRIX_BREATHING
#define ENABLE_RGB_MATRIX_BAND_SAT
#define ENABLE_RGB_MATRIX_BAND_VAL
#define ENABLE_RGB_MATRIX_BAND_PINWHEEL_SAT
#define ENABLE_RGB_MATRIX_BAND_PINWHEEL_VAL
// 10
#define ENABLE_RGB_MATRIX_BAND_SPIRAL_SAT
#define ENABLE_RGB_MATRIX_BAND_SPIRAL_VAL
#define ENABLE_RGB_MATRIX_CYCLE_ALL
#define ENABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT
#define ENABLE_RGB_MATRIX_CYCLE_UP_DOWN
#define ENABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON
#define ENABLE_RGB_MATRIX_CYCLE_OUT_IN
#define ENABLE_RGB_MATRIX_CYCLE_OUT_IN_DUAL
#define ENABLE_RGB_MATRIX_CYCLE_PINWHEEL
#define ENABLE_RGB_MATRIX_CYCLE_SPIRAL
// 20
#define ENABLE_RGB_MATRIX_DUAL_BEACON
#define ENABLE_RGB_MATRIX_RAINBOW_BEACON
#define ENABLE_RGB_MATRIX_RAINBOW_PINWHEELS
#define ENABLE_RGB_MATRIX_RAINDROPS
#define ENABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS
#define ENABLE_RGB_MATRIX_HUE_BREATHING
#define ENABLE_RGB_MATRIX_HUE_PENDULUM
#define ENABLE_RGB_MATRIX_HUE_WAVE
#define ENABLE_RGB_MATRIX_PIXEL_RAIN
#define ENABLE_RGB_MATRIX_PIXEL_FLOW
// 30
#define ENABLE_RGB_MATRIX_PIXEL_FRACTAL

#define RGB_MATRIX_FRAMEBUFFER_EFFECTS
// enabled only if RGB_MATRIX_FRAMEBUFFER_EFFECTS is defined
#define ENABLE_RGB_MATRIX_TYPING_HEATMAP
#define ENABLE_RGB_MATRIX_DIGITAL_RAIN

#define RGB_MATRIX_KEYPRESSES
// enabled only of RGB_MATRIX_KEYPRESSES or RGB_MATRIX_KEYRELEASES is defined
// 33
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_CROSS
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTICROSS
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS
// 40
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS
#define ENABLE_RGB_MATRIX_SPLASH
#define ENABLE_RGB_MATRIX_MULTISPLASH
#define ENABLE_RGB_MATRIX_SOLID_SPLASH
#define ENABLE_RGB_MATRIX_SOLID_MULTISPLASH

/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

/* disable debug print */
//#define NO_DEBUG

/* disable print */
//#define NO_PRINT

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT
