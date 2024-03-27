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

#include <string.h>
#include "quantum.h"
#include "xap.h"

#include "secure.h"
#ifndef SECURE_ENABLE
#    define secure_get_status() SECURE_UNLOCKED
#    define secure_request_unlock()
#    define secure_lock()
#endif

bool xap_respond_success(xap_token_t token) {
    xap_send(token, XAP_RESPONSE_FLAG_SUCCESS, NULL, 0);
    return true;
}

void xap_respond_failure(xap_token_t token, xap_response_flags_t response_flags) {
    xap_send(token, response_flags, NULL, 0);
}

bool xap_respond_data(xap_token_t token, const void *data, size_t length) {
    xap_send(token, XAP_RESPONSE_FLAG_SUCCESS, data, length);
    return true;
}

bool xap_respond_data_P(xap_token_t token, const void *data, size_t length) {
    uint8_t blob[length];
    memcpy_P(blob, data, length);
    return xap_respond_data(token, blob, length);
}

bool xap_respond_u32(xap_token_t token, uint32_t value) {
    xap_send(token, XAP_RESPONSE_FLAG_SUCCESS, &value, sizeof(value));
    return true;
}

#include "handlers/core.c"
#include "handlers/remapping.c"
#include "handlers/lighting.c"
#include "handlers/audio.c"
