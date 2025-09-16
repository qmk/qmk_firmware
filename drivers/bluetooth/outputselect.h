/*
Copyright 2017 Priyadi Iman Nurcahyo
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include "connection.h"

// DEPRECATED - DO NOT USE

#define OUTPUT_AUTO CONNECTION_HOST_AUTO
#define OUTPUT_NONE CONNECTION_HOST_NONE
#define OUTPUT_USB CONNECTION_HOST_USB
#define OUTPUT_BLUETOOTH CONNECTION_HOST_BLUETOOTH

#define set_output connection_set_host_noeeprom
#define where_to_send connection_get_host
#define auto_detect_output connection_auto_detect_host

void set_output_user(uint8_t output);
