/*
 *  Copyright (C) 2023  System76
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#pragma once

enum SecurityState {
    // Default value, flashing is prevented, cannot be set with CMD_SECURITY_SET
    SECURITY_STATE_LOCK = 0,
    // Flashing is allowed, cannot be set with CMD_SECURITY_SET
    SECURITY_STATE_UNLOCK = 1,
    // Flashing will be prevented on the next reboot
    SECURITY_STATE_PREPARE_LOCK = 2,
    // Flashing will be allowed on the next reboot
    SECURITY_STATE_PREPARE_UNLOCK = 3,
};

extern bool input_disabled;

void system76_ec_unlock(void);
bool system76_ec_is_unlocked(void);

bool system76_ec_fan_get(uint8_t index, uint8_t * duty);
bool system76_ec_fan_set(uint8_t index, uint8_t duty);
bool system76_ec_fan_tach(uint8_t index, uint16_t * tach);

bool system76_ec_led_get_mode(uint8_t layer, uint8_t * mode, uint8_t * speed);
bool system76_ec_led_set_mode(uint8_t layer, uint8_t mode, uint8_t speed);

bool system76_ec_security_get(enum SecurityState * state);
bool system76_ec_security_set(enum SecurityState state);