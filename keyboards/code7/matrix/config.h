// Copyright 2023 Chris H <chris@zoid.com.au>
// SPDX-License-Identifier: GPL-3.0-only

#pragma once

#define RGB_MATRIX_SLEEP

#define WEAR_LEVELING_LOGICAL_SIZE 16384
#define WEAR_LEVELING_BACKING_SIZE (WEAR_LEVELING_LOGICAL_SIZE * 4)

#define VIA_EEPROM_CUSTOM_CONFIG_SIZE (1 + RGB_MATRIX_LED_COUNT * 2)
