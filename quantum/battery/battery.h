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

typedef enum {
    BATTERY_CHARGING_UNKNOWN = 0,
    BATTERY_NOT_CHARGING,
    BATTERY_CHARGING,
    BATTERY_FULL,
} battery_charging_state_t;

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
 * \brief Read current charging state.
 *
 * Returns BATTERY_CHARGING_UNKNOWN when no charger driver is configured.
 *
 * \return The current charging state.
 */
battery_charging_state_t battery_get_charging_state(void);

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

/**
 * \brief user hook called when charging state changed.
 *
 */
void battery_charging_state_changed_user(battery_charging_state_t state);

/**
 * \brief keyboard hook called when charging state changed.
 *
 */
void battery_charging_state_changed_kb(battery_charging_state_t state);

/** \} */
