/* Copyright 2020 Dimitris Papavasiliou <dpapavas@protonmail.ch>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <LUFA/Drivers/USB/USB.h>

#include "lagrange.h"

#ifndef SPLIT_USB_TIMEOUT_POLL
#    define SPLIT_USB_TIMEOUT_POLL 10
#endif

/* Instead of timing out, the slave waits indefinitely for the other
 * side to signal that it has become master.  This avoids both sides
 * assuming the slave role when the USB port is powered but not
 * otherwise active (e.g. when the host is turned off, or suspended).
 * The SPI SS line is used for signaling.  On power-up it is
 * configured as input with pull-up enabled.  When one side assumes
 * the master role, it reconfigures the line for SPI, and pulls it low
 * to select the slave, which doubles as the signal. */

bool is_keyboard_master(void) {
    static int8_t is_master = -1;

    if (is_master < 0) {
        while (gpio_read_pin(SPI_SS_PIN)) {
            if (USB_Device_IsAddressSet()) {
                is_master = 1;
                return is_master;
            }
            wait_ms(SPLIT_USB_TIMEOUT_POLL);
        }

        is_master = 0;

        USB_Disable();
        USB_DeviceState = DEVICE_STATE_Unattached;
    }

    return is_master;
}

void keyboard_pre_init_kb(void) {
    gpio_set_pin_input_high(SPI_SS_PIN);

    keyboard_pre_init_user();
}
