// Copyright 2023 Binepad (@binepad)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once


/*
 * Wear Leveling EEPROM Emulation
 */

#define WEAR_LEVELING_LOGICAL_SIZE 2048                              // Number of bytes "exposed" to the rest of QMK and denotes the size of the usable EEPROM.
#define WEAR_LEVELING_BACKING_SIZE (WEAR_LEVELING_LOGICAL_SIZE * 2)  // Number of bytes used by the wear-leveling algorithm for its underlying storage, and needs to be a multiple of the logical size.
