// Copyright 2026 Scramble Tools
// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

// Piezo buzzer, only used when AUDIO_ENABLE is set in a keymap
#ifdef AUDIO_ENABLE
#    define AUDIO_PIN B5
#endif

// 0.96" SSD1306 module on I2C (D1/D0), one per half
#ifdef OLED_ENABLE
#    define OLED_DISPLAY_128X64
#endif

// Give the split link a moment to settle before the primary decides it is alone
#define SPLIT_USB_TIMEOUT 2000

// One PCB serves both halves, so nothing electrical tells them apart. Each
// half keeps its side in EEPROM, written by a left or right firmware image
#define EE_HANDS
