/* Copyright 2021 Nick Brassel (@tzarc)
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

#include <stdlib.h>
#include <stdint.h>

#include <xap_generated.h>

#ifndef XAP_SUBSYSTEM_VERSION_KB
#    define XAP_SUBSYSTEM_VERSION_KB 0
#endif

#ifndef XAP_SUBSYSTEM_VERSION_USER
#    define XAP_SUBSYSTEM_VERSION_USER 0
#endif

bool xap_respond_success(xap_token_t token);
void xap_respond_failure(xap_token_t token, xap_response_flags_t response_flags);
bool xap_respond_u32(xap_token_t token, uint32_t value);
bool xap_respond_data(xap_token_t token, const void *data, size_t length);
bool xap_respond_data_P(xap_token_t token, const void *data, size_t length);

void xap_send(xap_token_t token, xap_response_flags_t response_flags, const void *data, size_t length);
void xap_broadcast(uint8_t type, const void *data, size_t length);
