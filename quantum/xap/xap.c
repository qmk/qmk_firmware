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

#include "info_json_gz.h"
bool get_info_json_chunk(uint16_t offset, uint8_t *data, uint8_t data_len) {
    if (offset + data_len > INFO_JSON_GZ_LEN) {
        data_len = INFO_JSON_GZ_LEN - offset;
    }

    memcpy_P(data, &info_json_gz[offset], data_len);
    return true;
}

#define QSTR2(z) #z
#define QSTR(z) QSTR2(z)

typedef enum xap_route_type_t {
    XAP_UNUSED = 0, // "Unused" needs to be zero -- undefined routes (through preprocessor) will be skipped
    XAP_ROUTE,
    XAP_EXECUTE,
    XAP_VALUE,
    XAP_GETTER,
    XAP_CONST_MEM,
    TOTAL_XAP_ROUTE_TYPES
} xap_route_type_t;

#define XAP_ROUTE_TYPE_BIT_COUNT 3

typedef struct __attribute__((packed)) xap_route_flags_t {
    xap_route_type_t type : XAP_ROUTE_TYPE_BIT_COUNT;
    uint8_t          is_secure : 1;
} xap_route_flags_t;

_Static_assert(TOTAL_XAP_ROUTE_TYPES <= (1 << (XAP_ROUTE_TYPE_BIT_COUNT)), "Number of XAP route types is too large for XAP_ROUTE_TYPE_BITS.");
_Static_assert(sizeof(xap_route_flags_t) == 1, "xap_route_flags_t is not length of 1");

typedef struct xap_route_t xap_route_t;
struct __attribute__((packed)) xap_route_t {
    const xap_route_flags_t flags;
    union {
        // XAP_ROUTE
        struct {
            const xap_route_t *child_routes;
            const uint8_t      child_routes_len;
        };

        // XAP_EXECUTE
        bool (*handler)(xap_token_t token, const uint8_t *data, size_t data_len);

        // XAP_GETTER
        uint32_t (*u32getter)(void);

        // XAP_VALUE / XAP_CONST_MEM
        struct {
            const void *  const_data;
            const uint8_t const_data_len;
        };
    };
};

#include <xap_generated.inl>

void xap_execute_route(xap_token_t token, const xap_route_t *routes, size_t max_routes, const uint8_t *data, size_t data_len) {
    if (data_len == 0) return;
    xap_identifier_t id = data[0];

    if (id < max_routes) {
        xap_route_t route;
        memcpy_P(&route, &routes[id], sizeof(xap_route_t));

#ifdef SECURE_ENABLE
        if (route.flags.is_secure && secure_get_status() != SECURE_UNLOCKED) {
            xap_respond_failure(token, XAP_RESPONSE_FLAG_SECURE_FAILURE);
            return;
        }

        // TODO: All other subsystems are disabled during unlock.
        //       how to flag status route as still allowed?
        // if (!route.flags.is_secure && secure_get_status() == SECURE_PENDING) {
        //     xap_respond_failure(token, XAP_RESPONSE_FLAG_UNLOCK_IN_PROGRESS);
        //     return;
        // }
#endif

        switch (route.flags.type) {
            case XAP_ROUTE:
                if (route.child_routes != NULL && route.child_routes_len > 0 && data_len > 0) {
                    xap_execute_route(token, route.child_routes, route.child_routes_len, &data[1], data_len - 1);
                    return;
                }
                break;

            case XAP_EXECUTE:
                if (route.handler != NULL) {
                    bool ok = (route.handler)(token, data_len == 1 ? NULL : &data[1], data_len - 1);
                    if (ok) return;
                }
                break;

            case XAP_GETTER:
                if (route.u32getter != NULL) {
                    const uint32_t ret = (route.u32getter)();
                    xap_respond_data(token, &ret, sizeof(ret));
                    return;
                }
                break;

            case XAP_VALUE:
                xap_respond_data(token, route.const_data, route.const_data_len);
                return;

            case XAP_CONST_MEM:
                xap_respond_data_P(token, route.const_data, route.const_data_len);
                return;

            default:
                break;
        }
    }

    // Nothing got handled, so we respond with failure.
    xap_respond_failure(token, XAP_RESPONSE_FLAG_FAILED);
}

void xap_receive(xap_token_t token, const uint8_t *data, size_t length) {
    xap_execute_route(token, xap_route_table, sizeof(xap_route_table) / sizeof(xap_route_t), data, length);
}

void xap_event_task(void) {
#ifdef SECURE_ENABLE
    static secure_status_t last_status = -1;

    secure_status_t status = secure_get_status();
    if (last_status != status) {
        last_status = status;
        xap_broadcast_secure_status(status);
    }
#endif
}
