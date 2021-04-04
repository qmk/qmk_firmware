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

#include "power.h"
#if defined(HAPTIC_ENABLE)
#include "haptic.h"
extern haptic_config_t haptic_config;
#endif

bool high_power_state;

static void update_haptic_config_enable_and_status_pins(void)
{
#if defined(HAPTIC_ENABLE)
    if (haptic_config.enable && ((HAPTIC_OFF_IN_LOW_POWER != 0) || high_power_state)) {
#    if defined(HAPTIC_ENABLE_PIN)
        HAPTIC_ENABLE_PIN_WRITE_ACTIVE();
#    endif
#    if defined(HAPTIC_ENABLE_STATUS_LED)
        HAPTIC_ENABLE_STATUS_LED_WRITE_ACTIVE();
#    endif
    } else {
#    if defined(HAPTIC_ENABLE_PIN)
        HAPTIC_ENABLE_PIN_WRITE_INACTIVE();
#    endif
#    if defined(HAPTIC_ENABLE_STATUS_LED)
        HAPTIC_ENABLE_STATUS_LED_WRITE_INACTIVE();
#    endif
    }
#endif
}

void power_set_configuration(bool isConfigured, uint8_t configurationNumber)
{
    high_power_state = isConfigured;
    update_haptic_config_enable_and_status_pins();
}

void power_set_suspend(bool isConfigured, uint8_t configurationNumber)
{
    high_power_state = false;
    update_haptic_config_enable_and_status_pins();
}

void power_set_resume(bool isConfigured, uint8_t configurationNumber)
{
    high_power_state = isConfigured;
    update_haptic_config_enable_and_status_pins();
}

void power_set_reset(void)
{
    high_power_state = false;
    update_haptic_config_enable_and_status_pins();
}

void power_init(void)
{
    high_power_state = false;
    update_haptic_config_enable_and_status_pins();
#if defined(HAPTIC_ENABLE_PIN)
    setPinOutput(HAPTIC_ENABLE_PIN);
#endif
#if defined(HAPTIC_ENABLE_STATUS_LED)
    setPinOutput(HAPTIC_ENABLE_STATUS_LED);
#endif
}
