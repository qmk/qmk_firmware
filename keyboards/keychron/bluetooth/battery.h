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

enum {
    BAT_NOT_CHARGING = 0,
    BAT_CHARGING,
    BAT_CHARGING_FINISHED,
};

#ifndef FULL_VOLTAGE_VALUE
#    define FULL_VOLTAGE_VALUE 4100
#endif

#ifndef EMPTY_VOLTAGE_VALUE
#    define EMPTY_VOLTAGE_VALUE 3500
#endif

#ifndef SHUTDOWN_VOLTAGE_VALUE
#    define SHUTDOWN_VOLTAGE_VALUE 3300
#endif

#ifndef VOLTAGE_MEASURE_INTERVAL
#    define VOLTAGE_MEASURE_INTERVAL 3000
#endif

void battery_init(void);
void battery_measure(void);
void     battery_calculte_voltage(uint16_t value);
void     battery_set_voltage(uint16_t value);
uint16_t battery_get_voltage(void);
uint8_t battery_get_percentage(void);
void indicator_battery_low_enable(bool enable);
bool battery_is_empty(void);
bool battery_is_critical_low(void);

void battery_task(void);
