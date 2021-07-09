/* SPDX-License-Identifier: GPL-2.0-or-later */
/* Based on https://github.com/qmk/qmk_firmware/pull/13036 */

#include "vialrgb.h"

#include <inttypes.h>
#include <string.h>
#include "rgb_matrix.h"
#include "vial.h"

typedef struct {
    uint16_t vialrgb_id;
    uint16_t qmk_id;
} vialrgb_supported_mode_t;

#include "vialrgb_effects.inc"

#define SUPPORTED_MODES_LENGTH (sizeof(supported_modes)/sizeof(*supported_modes))

static void get_supported(uint8_t *args, uint8_t length) {
    /* retrieve supported effects (VialRGB IDs) with ID > gt */
    uint16_t gt;
    memcpy(&gt, args, sizeof(gt));
    memset(args, 0xFF, length);
    for (size_t i = 0; i < SUPPORTED_MODES_LENGTH; ++i) {
        uint16_t id = pgm_read_word(&supported_modes[i].vialrgb_id);
        if (id > gt && length >= sizeof(id)) {
            memcpy(args, &id, sizeof(id));
            length -= sizeof(id);
            args += sizeof(id);
        }
    }
}

static uint16_t qmk_id_to_vialrgb_id(uint16_t id) {
    for (size_t i = 0; i < SUPPORTED_MODES_LENGTH; ++i) {
        uint16_t qmk_id = pgm_read_word(&supported_modes[i].qmk_id);
        uint16_t vialrgb_id = pgm_read_word(&supported_modes[i].vialrgb_id);
        if (qmk_id == id)
            return vialrgb_id;
    }
    return 0;
}

static uint16_t vialrgb_id_to_qmk_id(uint16_t id) {
    for (size_t i = 0; i < SUPPORTED_MODES_LENGTH; ++i) {
        uint16_t qmk_id = pgm_read_word(&supported_modes[i].qmk_id);
        uint16_t vialrgb_id = pgm_read_word(&supported_modes[i].vialrgb_id);
        if (vialrgb_id == id)
            return qmk_id;
    }
    return 0;
}

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
        uint16_t vialrgb_id = qmk_id_to_vialrgb_id(rgb_matrix_get_mode());
        args[0] = vialrgb_id & 0xFF;
        args[1] = vialrgb_id >> 8;
        args[2] = rgb_matrix_get_speed();
        args[3] = rgb_matrix_get_hue();
        args[4] = rgb_matrix_get_sat();
        args[5] = rgb_matrix_get_val();
        break;
    }
    case vialrgb_get_supported: {
        get_supported(args, length - 2);
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
        uint16_t vialrgb_id = args[0] | (args[1] << 8);
        rgb_matrix_mode_noeeprom(vialrgb_id_to_qmk_id(vialrgb_id));
        rgb_matrix_set_speed_noeeprom(args[2]);
        rgb_matrix_sethsv_noeeprom(args[3], args[4], args[5]);
        break;
    }
    }
}

void vialrgb_save(uint8_t *data, uint8_t length) {
    (void)data;
    (void)length;

    eeconfig_update_rgb_matrix();
}
