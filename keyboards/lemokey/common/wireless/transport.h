/* Copyright 2023 @ lokher (https://www.keychron.com)
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

typedef enum {
    TRANSPORT_NONE,
    TRANSPORT_USB       = 0x01 << 0,
    TRANSPORT_BLUETOOTH = 0x01 << 1,
    TRANSPORT_P2P4      = 0x01 << 2,
    TRANSPORT_MAX,
} transport_t;

#ifdef NKRO_ENABLE
typedef struct {
    bool usb : 1;
    bool bluetooth : 1;
} nkro_t;
#endif

#define TRANSPORT_WIRELESS (TRANSPORT_BLUETOOTH | TRANSPORT_P2P4)

void        set_transport(transport_t new_transport);
transport_t get_transport(void);

void usb_power_connect(void);
void usb_power_disconnect(void);
void usb_transport_enable(bool enable);
void usb_remote_wakeup(void);
