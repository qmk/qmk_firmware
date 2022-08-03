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

#include "quantum.h"
#include "bluetooth.h"
#include "battery.h"
#include "transport.h"
#include "ckbt51.h"
#include "lpm.h"

#define BATTERY_EMPTY_COUNT 10
#define CRITICAL_LOW_COUNT 20

static uint32_t bat_monitor_timer_buffer = 0;
static uint16_t voltage                  = FULL_VOLTAGE_VALUE;
static uint8_t  bat_empty                = 0;
static uint8_t  critical_low             = 0;
static uint8_t  bat_state;

void battery_init(void) {
    bat_monitor_timer_buffer = 0;
    bat_state                = BAT_NOT_CHARGING;
}
__attribute__((weak)) void battery_measure(void) {}

/* Calculate the voltage */
__attribute__((weak)) void battery_calculate_voltage(uint16_t value) {}

void battery_set_voltage(uint16_t value) {
    voltage = value;
}

uint16_t battery_get_voltage(void) {
    return voltage;
}

uint8_t battery_get_percentage(void) {
    if (voltage > FULL_VOLTAGE_VALUE) return 100;

    if (voltage > EMPTY_VOLTAGE_VALUE) {
        return ((uint32_t)voltage - EMPTY_VOLTAGE_VALUE) * 80 / (FULL_VOLTAGE_VALUE - EMPTY_VOLTAGE_VALUE) + 20;
    }

    if (voltage > SHUTDOWN_VOLTAGE_VALUE) {
        return ((uint32_t)voltage - SHUTDOWN_VOLTAGE_VALUE) * 20 / (EMPTY_VOLTAGE_VALUE - SHUTDOWN_VOLTAGE_VALUE);
    } else
        return 0;
}

bool battery_is_empty(void) {
    return bat_empty > BATTERY_EMPTY_COUNT;
}

bool battery_is_critical_low(void) {
    return critical_low > CRITICAL_LOW_COUNT;
}

void battery_check_empty(void) {
    if (voltage < EMPTY_VOLTAGE_VALUE) {
        if (bat_empty <= BATTERY_EMPTY_COUNT) {
            if (++bat_empty > BATTERY_EMPTY_COUNT) indicator_battery_low_enable(true);
        }
    } else if (bat_empty <= BATTERY_EMPTY_COUNT) {
        bat_empty = BATTERY_EMPTY_COUNT;
    }
}

void battery_check_critical_low(void) {
    if (voltage < SHUTDOWN_VOLTAGE_VALUE) {
        if (critical_low <= CRITICAL_LOW_COUNT) {
            if (++critical_low > CRITICAL_LOW_COUNT) bluetooth_low_battery_shutdown();
        }
    } else if (critical_low <= CRITICAL_LOW_COUNT) {
        critical_low = 0;
    }
}

void battery_task(void) {
    if (get_transport() == TRANSPORT_BLUETOOTH && bluetooth_get_state() == BLUETOOTH_CONNECTED) {
        if (sync_timer_elapsed32(bat_monitor_timer_buffer) > VOLTAGE_MEASURE_INTERVAL) {
            battery_check_empty();
            battery_check_critical_low();

            bat_monitor_timer_buffer = sync_timer_read32();
            battery_measure();
        }
    }

    if ((bat_empty || critical_low) && usb_power_connected()) {
        bat_empty    = false;
        critical_low = false;
        indicator_battery_low_enable(false);
    }
}
