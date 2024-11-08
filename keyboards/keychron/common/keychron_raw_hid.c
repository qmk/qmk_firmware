/* Copyright 2024 @ Keychron (https://www.keychron.com)
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

#include QMK_KEYBOARD_H
#include "keychron_common.h"
#include "raw_hid.h"
#include "version.h"
#ifdef FACTORY_TEST_ENABLE
#    include "factory_test.h"
#endif
#ifdef LK_WIRELESS_ENABLE
#    include "lkbt51.h"
#endif
#ifdef ANANLOG_MATRIX
#    include "analog_matrix.h"
#endif

#define PROTOCOL_VERSION 0x02

enum {
    KC_GET_PROTOCOL_VERSION = 0xA0,
    KC_GET_FIRMWARE_VERSION = 0xA1,
    KC_GET_SUPPORT_FEATURE  = 0xA2,
    KC_GET_DEFAULT_LAYER    = 0xA3,
    KC_ANALOG_MATRIX        = 0xA9,
    KC_WIRELESS_DFU         = 0xAA,
    KC_FACTORY_TEST         = 0xAB
};

enum {
    FEATURE_DEFAULT_LAYER = 0x01 << 0,
    FEATURE_BLUETOOTH     = 0x01 << 1,
    FEATURE_P2P4G         = 0x01 << 2,
    FEATURE_ANALOG_MATRIX = 0x01 << 3,
};

void get_support_feature(uint8_t *data) {
    data[1] = FEATURE_DEFAULT_LAYER
#ifdef KC_BLUETOOTH_ENABLE
              | FEATURE_BLUETOOTH
#endif
#ifdef LK_WIRELESS_ENABLE
              | FEATURE_BLUETOOTH | FEATURE_P2P4G
#endif
#ifdef ANANLOG_MATRIX
              | FEATURE_ANALOG_MATRIX
#endif
        ;
}

#ifdef ANANLOG_MATRIX
void send_analog_matrix(uint8_t *data, uint8_t length) {
    uint8_t offset = data[2];
    uint8_t rows = 28 / ((MATRIX_COLS + 7) / 8);
    uint8_t i    = 3;
    for (uint8_t row = 0; row < rows && row + offset < MATRIX_ROWS; row++) {
        matrix_row_t value = analog_matrix_get_row(row + offset);
#    if (MATRIX_COLS > 24)
        data[i++] = (value >> 24) & 0xFF;
#    endif
#    if (MATRIX_COLS > 16)
        data[i++] = (value >> 16) & 0xFF;
#    endif
#    if (MATRIX_COLS > 8)
        data[i++] = (value >> 8) & 0xFF;
#    endif
        data[i++] = value & 0xFF;
    }
    raw_hid_send(data, length);
}
#endif

bool kc_raw_hid_rx(uint8_t *data, uint8_t length) {
#if defined(ANANLOG_MATRIX) && defined(VIA_ENABLE)
    if (data[0] == id_get_keyboard_value && data[1] == id_switch_matrix_state) {
        send_analog_matrix(data, length);
        return false;
    }
#endif

    switch (data[0]) {
        case KC_GET_PROTOCOL_VERSION:
            data[1] = PROTOCOL_VERSION;
            break;

        case KC_GET_FIRMWARE_VERSION: {
            uint8_t i = 1;
            data[i++] = 'v';
            if ((DEVICE_VER & 0xF000) != 0) itoa((DEVICE_VER >> 12), (char *)&data[i++], 16);
            itoa((DEVICE_VER >> 8) & 0xF, (char *)&data[i++], 16);
            data[i++] = '.';
            itoa((DEVICE_VER >> 4) & 0xF, (char *)&data[i++], 16);
            data[i++] = '.';
            itoa(DEVICE_VER & 0xF, (char *)&data[i++], 16);
            data[i++] = ' ';
            memcpy(&data[i], QMK_BUILDDATE, sizeof(QMK_BUILDDATE));
            i += sizeof(QMK_BUILDDATE);
        } break;

        case KC_GET_SUPPORT_FEATURE:
            get_support_feature(&data[1]);
            break;

        case KC_GET_DEFAULT_LAYER:
            data[1] = get_highest_layer(default_layer_state);
            break;

#ifdef ANANLOG_MATRIX
        case KC_ANALOG_MATRIX:
            analog_matrix_rx(data, length);
            return true;
#endif
#ifdef LK_WIRELESS_ENABLE
        case KC_WIRELESS_DFU:
            lkbt51_dfu_rx(data, length);
            return true;
#endif
#ifdef FACTORY_TEST_ENABLE
        case KC_FACTORY_TEST:
            factory_test_rx(data, length);
            return true;
#endif
        default:
            return false;
    }

    raw_hid_send(data, length);
    return true;
}

#if defined(VIA_ENABLE)
bool via_command_kb(uint8_t *data, uint8_t length) {
    return kc_raw_hid_rx(data, length);
}
#else
void raw_hid_receive(uint8_t *data, uint8_t length) {
    kc_raw_hid_rx(data, length);
}
#endif
