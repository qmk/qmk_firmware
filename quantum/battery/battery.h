// Copyright 2025 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <stdint.h>

/**
 * \file
 *
 * \defgroup battery Battery API
 *
 * \brief API to query battery status.
 * \{
 */

/**
 * \brief Initialize the battery driver.
 */
void battery_init(void);

/**
 * \brief Perform housekeeping tasks.
 */
void battery_task(void);

/**
 * \brief Sample battery level.
 *
 * \return The battery percentage, in the range 0-100.
 */
uint8_t battery_get_percent(void);

/**
 * \brief user hook called when battery level changed.
 *
 */
void battery_percent_changed_user(uint8_t level);

/**
 * \brief keyboard hook called when battery level changed.
 *
 */
void battery_percent_changed_kb(uint8_t level);

/** \} */
