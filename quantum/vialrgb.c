/* SPDX-License-Identifier: GPL-2.0-or-later */

#include "vialrgb.h"

#include <inttypes.h>
#include "rgb_matrix.h"
#include "vial.h"

#if !defined(RGB_MATRIX_MAXIMUM_BRIGHTNESS) || RGB_MATRIX_MAXIMUM_BRIGHTNESS > UINT8_MAX
#    undef RGB_MATRIX_MAXIMUM_BRIGHTNESS
#    define RGB_MATRIX_MAXIMUM_BRIGHTNESS UINT8_MAX
#endif

/* Based on https://github.com/qmk/qmk_firmware/pull/13036 */

void vialrgb_get_value(uint8_t *data, uint8_t length) {
    if (length != VIAL_RAW_EPSIZE) return;

    /* data[0] is used by VIA command id */
    uint8_t cmd = data[1];
    uint8_t *args = &data[2];
    switch (cmd) {
    case vialrgb_get_info:
        args[0] = VIALRGB_PROTOCOL_VERSION & 0xFF;
        args[1] = VIALRGB_PROTOCOL_VERSION >> 8;
        args[2] = RGB_MATRIX_MAXIMUM_BRIGHTNESS;
        break;
    case vialrgb_get_mode: {
        args[0] = rgb_matrix_get_mode();
        args[1] = rgb_matrix_get_speed();
        args[2] = rgb_matrix_get_hue();
        args[3] = rgb_matrix_get_sat();
        args[4] = rgb_matrix_get_val();
        break;
    }
    }
}

void vialrgb_set_value(uint8_t *data, uint8_t length) {
    if (length != VIAL_RAW_EPSIZE) return;

    /* data[0] is used by VIA command id */
    uint8_t cmd = data[1];
    uint8_t *args = &data[2];
    switch (cmd) {
    case vialrgb_set_mode: {
        rgb_matrix_mode_noeeprom(args[0]);
        rgb_matrix_set_speed_noeeprom(args[1]);
        rgb_matrix_sethsv_noeeprom(args[2], args[3], args[4]);
        break;
    }
    }
}

void vialrgb_save(uint8_t *data, uint8_t length) {
    (void)data;
    (void)length;

    eeconfig_update_rgb_matrix();
}
