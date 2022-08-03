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

#pragma once

/* Type of an enumeration of the possible BT events.*/
typedef enum {
    EVT_NONE = 0,
    EVT_RESET,
    EVT_DISCOVERABLE,
    EVT_RECONNECTING,
    EVT_CONNECTED,
    EVT_DISCONNECTED,
    EVT_PINCODE_ENTRY,
    EVT_EXIT_PINCODE_ENTRY,
    EVT_HID_SET_PROTOCOL,
    EVT_HID_INDICATOR,
    EVT_CONECTION_INTERVAL,
} event_type_t;

typedef struct {
    event_type_t evt_type; /*The type of the event. */
    union {
        uint8_t reason;    /* Parameters to BLUETOOTH_RESET event */
        uint8_t hostIndex; /* Parameters to connection event from EVT_DISCOVERABLE to EVT_DISCONECTED */
        uint8_t led;       /* Parameters to EVT_HID_INDICATOR event */
        uint8_t protocol;  /* Parameters to EVT_HID_SET_PROTOCOL event */
        uint8_t interval;  /* Parameters to EVT_CONECTION_INTERVAL event */
    } params;
} bluetooth_event_t;

