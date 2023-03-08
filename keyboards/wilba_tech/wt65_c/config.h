// Copyright 2023 Jason Williams (@wilba)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

// Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap
#define LOCKING_SUPPORT_ENABLE

// Locking resynchronize hack
#define LOCKING_RESYNC_ENABLE

// IS31FL3731 driver
#define DRIVER_COUNT 2
#define RGB_MATRIX_LED_COUNT 72

// Enable WT RGB backlight
#define RGB_BACKLIGHT_ENABLED 1

// This conditionally compiles the backlight code for WT65-C specifics
#define RGB_BACKLIGHT_WT65_C

// enable/disable LEDs based on layout
#define RGB_BACKLIGHT_USE_SPLIT_BACKSPACE 1
#define RGB_BACKLIGHT_USE_SPLIT_LEFT_SHIFT 0
#define RGB_BACKLIGHT_USE_SPLIT_RIGHT_SHIFT 0
#define RGB_BACKLIGHT_USE_7U_SPACEBAR 1
#define RGB_BACKLIGHT_USE_ISO_ENTER 0
#define RGB_BACKLIGHT_DISABLE_HHKB_BLOCKER_LEDS 0

// disable backlight when USB suspended (PC sleep/hibernate/shutdown)
#define RGB_BACKLIGHT_DISABLE_WHEN_USB_SUSPENDED 0

// disable backlight after timeout in minutes, 0 = no timeout
#define RGB_BACKLIGHT_DISABLE_AFTER_TIMEOUT 0

// the default brightness
#define RGB_BACKLIGHT_BRIGHTNESS 255

// the default effect (RGB test)
#define RGB_BACKLIGHT_EFFECT 255

// the default effect speed (0-3)
#define RGB_BACKLIGHT_EFFECT_SPEED 0

// the default color1 and color2
#define RGB_BACKLIGHT_COLOR_1 \
    { .h = 0, .s = 255 }
#define RGB_BACKLIGHT_COLOR_2 \
    { .h = 127, .s = 255 }

// These define which keys in the matrix are alphas/mods
// Used for backlight effects so colors are different for
// alphas vs. mods
// Each value is for a row, bit 0 is column 0
// Alpha=0 Mod=1
#define RGB_BACKLIGHT_ALPHAS_MODS_ROW_0 0b0110000000000001
#define RGB_BACKLIGHT_ALPHAS_MODS_ROW_1 0b0110000000000001
#define RGB_BACKLIGHT_ALPHAS_MODS_ROW_2 0b0111000000000001
#define RGB_BACKLIGHT_ALPHAS_MODS_ROW_3 0b0111000000000001
#define RGB_BACKLIGHT_ALPHAS_MODS_ROW_4 0b0111100000000111

#define RGB_BACKLIGHT_CAPS_LOCK_INDICATOR \
    { .color = {.h = 0, .s = 0}, .index = 255 }
#define RGB_BACKLIGHT_LAYER_1_INDICATOR \
    { .color = {.h = 0, .s = 0}, .index = 255 }
#define RGB_BACKLIGHT_LAYER_2_INDICATOR \
    { .color = {.h = 0, .s = 0}, .index = 255 }
#define RGB_BACKLIGHT_LAYER_3_INDICATOR \
    { .color = {.h = 0, .s = 0}, .index = 255 }

// Backlight config starts after VIA's EEPROM usage,
// dynamic keymaps start after this.
#define VIA_EEPROM_CUSTOM_CONFIG_SIZE 31

// VIA lighting is handled by the keyboard-level code
#define VIA_CUSTOM_LIGHTING_ENABLE
