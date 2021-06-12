/* Copyright 2021 QMK
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
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "usb_util.h"
#include "wait.h"

__attribute__((weak)) void usb_disable(void) {}
__attribute__((weak)) bool usb_connected_state(void) { return true; }
__attribute__((weak)) bool usb_vbus_state(void) {
#ifdef USB_VBUS_PIN
    setPinInput(USB_VBUS_PIN);
    wait_us(5);
    return readPin(USB_VBUS_PIN);
#else
    return true;
#endif
}
