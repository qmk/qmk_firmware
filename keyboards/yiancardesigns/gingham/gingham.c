/* Copyright 2019 Yiancar
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
#include "gingham.h"
#include "i2c_master.h"

uint8_t send_data;

void matrix_init_kb(void) {
    // Due to the way the port expander is setup both LEDs are already outputs. This is set n matrix.copy
    //Turn the red LED on as power indicator.
    send_data = 0x10;
    i2c_writeReg((PORT_EXPANDER_ADDRESS << 1), 0x09, &send_data, 1, 20);

    matrix_init_user();
}

void led_set_kb(uint8_t usb_led) {
    // Bit 3 is Green LED, bit 4 is Red LED.
    if (IS_LED_ON(usb_led, USB_LED_CAPS_LOCK)) {
        send_data = 0x18;
    } else {
        send_data = 0x10;
    }
    i2c_writeReg((PORT_EXPANDER_ADDRESS << 1), 0x09, &send_data, 1, 20);

    led_set_user(usb_led);
}
