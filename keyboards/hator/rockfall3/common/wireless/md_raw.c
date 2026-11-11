/* Copyright (C) 2024 koosikus
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

#if RAW_ENABLE

#    include "quantum.h"
#    include "wireless.h"
#    include "usb_endpoints.h"
#    include "usb_main.h"

void replaced_hid_send(uint8_t *data, uint8_t length) {

    if (length != RAW_EPSIZE) {
        return;
    }

    if (get_transport() == TRANSPORT_USB) {
        send_report(USB_ENDPOINT_IN_RAW, data, length);
    } else {
        md_send_raw(data, length);
    }
}

void md_receive_raw_cb(uint8_t *data, uint8_t length) {
    void raw_hid_receive(uint8_t * data, uint8_t length);

    raw_hid_receive(data, length);
}

#endif
