/* Copyright 2016 Jack Humbert
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

#ifndef _API_SYSEX_H_
#define _API_SYSEX_H_

#include "api.h"

void send_bytes_sysex(uint8_t message_type, uint8_t data_type, uint8_t* bytes, uint16_t length);

#define SEND_BYTES(mt, dt, b, l) send_bytes_sysex(mt, dt, b, l)

#endif
