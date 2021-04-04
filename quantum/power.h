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

extern bool high_power_state;

#ifdef HAPTIC_ENABLE_PIN_ACTIVE_LOW
#    ifndef HAPTIC_ENABLE_PIN
#        error HAPTIC_ENABLE_PIN not defined
#    endif
#    define HAPTIC_ENABLE_PIN_WRITE_ACTIVE() writePinLow(HAPTIC_ENABLE_PIN)
#    define HAPTIC_ENABLE_PIN_WRITE_INACTIVE() writePinHigh(HAPTIC_ENABLE_PIN)
#else
#    define HAPTIC_ENABLE_PIN_WRITE_ACTIVE() writePinHigh(HAPTIC_ENABLE_PIN)
#    define HAPTIC_ENABLE_PIN_WRITE_INACTIVE() writePinLow(HAPTIC_ENABLE_PIN)
#endif

#ifdef HAPTIC_ENABLE_STATUS_LED_ACTIVE_LOW
#    ifndef HAPTIC_ENABLE_STATUS_LED
#        error HAPTIC_ENABLE_STATUS_LED not defined
#    endif
#    define HAPTIC_ENABLE_STATUS_LED_WRITE_ACTIVE() writePinLow(HAPTIC_ENABLE_STATUS_LED)
#    define HAPTIC_ENABLE_STATUS_LED_WRITE_INACTIVE() writePinHigh(HAPTIC_ENABLE_STATUS_LED)
#else
#    define HAPTIC_ENABLE_STATUS_LED_WRITE_ACTIVE() writePinHigh(HAPTIC_ENABLE_STATUS_LED)
#    define HAPTIC_ENABLE_STATUS_LED_WRITE_INACTIVE() writePinLow(HAPTIC_ENABLE_STATUS_LED)
#endif

#ifndef HAPTIC_OFF_IN_LOW_POWER
#    define HAPTIC_OFF_IN_LOW_POWER 0
#endif
