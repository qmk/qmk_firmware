// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

#include <stdbool.h>
#include <stdint.h>

/** \brief user hook called when sampled value has changed
 */
bool potentiometer_update_user(uint8_t index, uint16_t value);

/** \brief keyboard hook called when sampled value has changed
 */
bool potentiometer_update_kb(uint8_t index, uint16_t value);

/** \brief Handle various subsystem background tasks
 */
bool potentiometer_task(void);
