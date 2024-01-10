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

#include "config.h"

//
#ifndef BT_HOST_DEVICES_COUNT
#    define BT_HOST_DEVICES_COUNT 3
#endif

#define P2P4G_HOST_DEVICES_COUNT 1

//  Uint: Second
#ifndef DISCONNECTED_BACKLIGHT_OFF_DELAY_TIME
#    define DISCONNECTED_BACKLIGHT_OFF_DELAY_TIME 40
#endif

//  Uint: Second, the timer restarts on key activities.
#ifndef CONNECTED_BACKLIGHT_OFF_DELAY_TIME
#    define CONNECTED_BACKLIGHT_OFF_DELAY_TIME 600
#endif
