/*
 * Copyright 2021 Andrei Purdea <andrei@purdea.ro>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include "quantum.h"

void power_set_configuration(bool isConfigured, uint8_t configurationNumber);
void power_set_suspend(bool isConfigured, uint8_t configurationNumber);
void power_set_resume(bool isConfigured, uint8_t configurationNumber);
void power_set_reset(void);
void power_init(void);

enum power_state {
    POWER_STATE_INIT = 0,       // Can consume up to 100mA
    POWER_STATE_CONFIGURED = 1, // Can consume up to what is specified in configuration descriptor, typically 500mA
    POWER_STATE_SUSPEND = 2     // Can consume only suspend current
};

extern enum power_state power_state;

void notify_power_state_change_kb(void);
