/* Copyright 2025
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

#include "framework_touchpad.h"
#include "i2c_master.h"
#include "print.h"

#define FRAMEWORK_TOUCHPAD_I2C_ADDRESS (0x2c << 1)

void framework_touchpad_init(void) {
    i2c_init();
}

void framework_touchpad_task(void) {
    int     length     = 0;
    int     status     = I2C_STATUS_SUCCESS;
    uint8_t buffer[37] = {0};
    uint8_t report[34] = {0};

    status = i2c_receive(FRAMEWORK_TOUCHPAD_I2C_ADDRESS, buffer, 1, 100);
    length = buffer[0];
    if (status != I2C_STATUS_SUCCESS || buffer[0] <= 0) {
        return;
    }

    status = i2c_receive(FRAMEWORK_TOUCHPAD_I2C_ADDRESS, buffer, length, 100);
    if (status != I2C_STATUS_SUCCESS || buffer[2] != 0x01) {
        return;
    }

    memcpy(report, buffer + 3, 34);

    void host_framework_touchpad_send(uint8_t(*report)[34]);
    host_framework_touchpad_send(&report);
}