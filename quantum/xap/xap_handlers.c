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

#include <quantum.h>
#include <xap.h>

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

uint32_t xap_route_qmk_ffffffffffffffff_getter(void) {
    return 0x12345678;
}

bool xap_respond_info_json_gz(xap_token_t token, const uint8_t *data, size_t data_len) {
    if (data_len != 2) {
        xap_respond_failure(token, 0);
        return false;
    }

    uint8_t  blob[32] = {0};
    uint16_t offset   = ((uint16_t)data[0]) << 8 | data[1];

    void get_info_json_chunk(uint8_t * data, size_t offset);
    get_info_json_chunk(blob, offset);

    return xap_respond_data(token, blob, 32);
}
