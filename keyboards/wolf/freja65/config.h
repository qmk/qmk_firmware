// Copyright 2023 contact@vwolf.be
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET

#define WS2812_PIO_USE_PIO1

#define RGB_MATRIX_LED_COUNT 102
#define RGB_MATRIX_KEYPRESSES 
#define RGB_MATRIX_FRAMEBUFFER_EFFECTS
#define RGB_DISABLE_WHEN_USB_SUSPENDED // turn off effects when suspended

#define RGB_MATRIX_DEFAULT_MODE RGB_MATRIX_CYCLE_ALL

#define EECONFIG_KB_DATA_SIZE 5

#define CAPS_INDICATOR_INDEX 0