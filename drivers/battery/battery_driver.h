// Copyright 2025 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <stdint.h>

/**
 * \file
 *
 * \defgroup battery Battery Driver API
 *
 * \brief API to query battery status.
 * \{
 */

/**
 * \brief Initialize the battery driver. This function must be called only once, before any of the below functions can be called.
 */
void battery_driver_init(void);

/**
 * \brief Sample battery level.
 *
 * \return The battery percentage, in the range 0-100.
 */
uint8_t battery_driver_sample_percent(void);

/** \} */
