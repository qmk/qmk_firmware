// Copyright 2023 JZ-Skyloong (@JZ-Skyloong)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define ENCODER_MAP_KEY_DELAY 10

#define IS31FL3743A_I2C_ADDRESS_1 IS31FL3743A_I2C_ADDRESS_GND_GND
#define IS31FL3743A_I2C_ADDRESS_2 IS31FL3743A_I2C_ADDRESS_GND_VCC
#define IS31FL3743A_SDB_PIN B12

#define CAPS_LOCK_INDEX 44
#define WIN_MOD_INDEX 20
#define MAC_MOD_INDEX 21
#define WIN_LOCK_INDEX 75

/* RGB Matrix Animation modes. Explicitly enabled
 * For full list of effects, see:
 * https://docs.qmk.fm/#/feature_rgb_matrix?id=rgb-matrix-effects
 */
#define RGB_MATRIX_DEFAULT_MODE RGB_MATRIX_CUSTOM_solid_green
