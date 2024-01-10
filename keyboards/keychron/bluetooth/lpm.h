/* Copyright 2022 @ lokher (https://www.keychron.com)
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

#ifndef RUN_MODE_PROCESS_TIME
#    define RUN_MODE_PROCESS_TIME 1000
#endif

typedef enum { PM_RUN, PM_LOW_POWER_RUN, PM_SLEEP, PM_LOW_POWER_SLEEP, PM_STOP0, PM_STOP1, PM_STOP2, PM_STANDBY_WITH_RAM, PM_STANDBY, PM_SHUTDOWN } pm_t;

void lpm_init(void);
void lpm_timer_reset(void);
void lpm_timer_stop(void);
bool usb_power_connected(void);
void enter_power_mode(pm_t mode);
void lpm_task(void);
