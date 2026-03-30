// Copyright 2024 Leon Sieber (@lesieber)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

// Raw HID settings for companion app communication
#define RAW_USAGE_PAGE 0xFF60
#define RAW_USAGE_ID 0x61

// Dynamic keymap layers
#define DYNAMIC_KEYMAP_LAYER_COUNT 4

// EEPROM for storing layer names (16 chars per layer x 4 layers = 64 bytes)
#define EECONFIG_USER_DATA_SIZE 64
