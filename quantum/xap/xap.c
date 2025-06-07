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
#include "secure.h"

#ifdef RGBLIGHT_ENABLE
#    include "rgblight/lighting_map.h"
#endif
#ifdef RGB_MATRIX_ENABLE
#    include "rgb_matrix/lighting_map.h"
#endif
#ifdef LED_MATRIX_ENABLE
#    include "led_matrix/lighting_map.h"
#endif

#include "config_blob_gz.h"
bool get_config_blob_chunk(uint16_t offset, uint8_t *data, uint8_t data_len) {
    if (offset >= CONFIG_BLOB_GZ_LEN) {
        return false;
    }

    if (offset + data_len >= CONFIG_BLOB_GZ_LEN) {
        data_len = (CONFIG_BLOB_GZ_LEN - 1) - offset;
    }

    memcpy_P(data, &config_blob_gz[offset], data_len);
    return true;
}

// TODO: move to better location?
#ifdef BACKLIGHT_BREATHING
#    define ENABLED_BACKLIGHT_EFFECTS 0b00000001
#else
#    define ENABLED_BACKLIGHT_EFFECTS 0b00000000
#endif

bool xap_ensure_unlocked(xap_token_t token) {
#ifdef SECURE_ENABLE
    if (!secure_is_unlocked()) {
        xap_respond_failure(token, XAP_RESPONSE_FLAG_SECURE_FAILURE);
        return true;
    }

    // TODO: XAP messages extend unlocked timeout?
    secure_activity_event();
#endif
    return false;
}

#define QSTR2(z) #z
#define QSTR(z) QSTR2(z)

#include <xap_generated.inl>

void xap_receive(xap_token_t token, const uint8_t *data, size_t length) {
    extern bool xap_route_route_handler(xap_token_t token, const uint8_t *data, size_t data_len);
    if (!xap_route_route_handler(token, data, length)) {
        // Nothing got handled, so we respond with failure.
        xap_respond_failure(token, XAP_RESPONSE_FLAG_FAILED);
    }
}
