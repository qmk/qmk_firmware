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
#    include "haptic.h"
#endif

enum power_state power_state;

__attribute__((weak)) void notify_power_state_change_kb(void) {
}

static void notify_power_state_change(void)
{
#if defined(HAPTIC_ENABLE) && HAPTIC_OFF_IN_LOW_POWER
    haptic_notify_power_state_change();
#endif
    notify_power_state_change_kb();
}

void power_set_configuration(bool isConfigured, uint8_t configurationNumber)
{
    power_state = isConfigured ? POWER_STATE_CONFIGURED : POWER_STATE_INIT;
    notify_power_state_change();
}

void power_set_suspend(bool isConfigured, uint8_t configurationNumber)
{
    power_state = POWER_STATE_SUSPEND;
    notify_power_state_change();
}

void power_set_resume(bool isConfigured, uint8_t configurationNumber)
{
    power_state = isConfigured ? POWER_STATE_CONFIGURED : POWER_STATE_INIT;
    notify_power_state_change();
}

void power_set_reset(void)
{
    power_state = POWER_STATE_INIT;
    notify_power_state_change();
}

void power_init(void)
{
    power_state = POWER_STATE_INIT;
    notify_power_state_change();
}
