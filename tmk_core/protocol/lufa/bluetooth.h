/*
Bluefruit Protocol for TMK firmware
Author: Benjamin Gould, 2013
        Jack Humbert, 2015
        Joshua Rubin, 2020
Based on code Copyright 2011 Jun Wako <wakojun@gmail.com>
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>

#include "report.h"

/* Returns true if we believe that the BLE module is connected. This uses our
 * cached understanding that is maintained by calling bluetooth_task()
 * periodically. */
bool bluetooth_is_connected(void);

/* Clears bluetooth bonding information allowing it to connnect to a new host */
void bluetooth_unpair(void);

/* Call this periodically to process bluetooth-originated things */
void bluetooth_task(void);

/* Generates keypress events for a set of keys. The hid modifier mask specifies
 * the state of the modifier keys for this set of keys. Also sends a key release
 * indicator, so that the keys do not remain held down. */
void bluetooth_send_keyboard(report_keyboard_t *report);

/* Send a consumer keycode, holding it down for the specified duration
 * (milliseconds) */
void bluetooth_send_consumer(uint16_t keycode, int hold_duration);

#ifdef MOUSE_ENABLE
/* Send a mouse/wheel movement report. The parameters are signed and indicate
 * positive of negative direction change. */
void bluetooth_send_mouse(report_mouse_t *report);
#endif

#ifdef BLUETOOTH_BATTERY_ENABLE
uint8_t bluetooth_get_battery_level(void);
uint8_t bluetooth_get_battery_level_user(void);
#endif

#ifdef __cplusplus
}
#endif
