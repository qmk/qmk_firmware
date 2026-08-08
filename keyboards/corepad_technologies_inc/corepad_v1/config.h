// Copyright 2026 albertphu07
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

/* --------------------------------------------------------------------------
 * I2C (SSD1306 128x32 OLED)
 *
 * XIAO RP2040
 * D4 (SDA) = RP2040 GPIO6
 * D5 (SCL) = RP2040 GPIO7
 *
 * NOTE: I2C_DRIVER can only be set here (config.h) - it is not a valid
 * rules.mk setting or a data-driven keyboard.json key.
 * -------------------------------------------------------------------------- */

#define I2C_DRIVER I2CD1

#define I2C1_SDA_PIN GP6
#define I2C1_SCL_PIN GP7

#define OLED_UPDATE_INTERVAL 20
