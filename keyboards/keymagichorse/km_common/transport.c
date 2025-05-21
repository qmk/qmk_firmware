/* Copyright 2025 keymagichorse
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

// Very few codes are borrowed from https://www.keychron.com
#include "quantum.h"
#include "bhq.h"
#include "transport.h"
#include "km_printf.h"
#include "outputselect.h"
static kb_transport_t transport = KB_TRANSPORT_USB; // 默认上电就是usb

void transport_set(kb_transport_t new_transport)
{
    transport = new_transport;
    if (IS_WIRELESS_TRANSPORT(transport)) 
    {
        set_output(OUTPUT_BLUETOOTH);
    }
    else if(transport == KB_TRANSPORT_USB)
    {
        set_output(OUTPUT_USB);
    }
    else
    {
        set_output(OUTPUT_NONE);
    }
}
kb_transport_t transport_get(void)
{
    return transport;
}

