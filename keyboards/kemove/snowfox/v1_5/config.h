// Copyright 2026 Michael Loukeris (@milouk)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

// Room for eight dynamic keymap layers and VIA macros.
#define LPC11UXX_EEPROM_SIZE 2048

// Keyboard settings (4 bytes) and the lighting of each of the five profiles (8 bytes each).
#define EECONFIG_KB_DATA_SIZE (4 + 5 * 8)

// VIA sends one request and waits for the answer, so small USB queues are enough.
#define RAW_IN_CAPACITY 2
#define RAW_OUT_CAPACITY 2
#define SHARED_IN_CAPACITY 2
