/* SPDX-License-Identifier: GPL-2.0-or-later */
/* Based on https://github.com/qmk/qmk_firmware/pull/13036 */

#include "vialrgb.h"

#include <inttypes.h>
#include <string.h>
#include "rgb_matrix.h"
#include "vial.h"

/* Note - never reorder or remove these, only add new animations at the end */
enum {
    VIALRGB_EFFECT_OFF = 0,
    VIALRGB_EFFECT_DIRECT,
    VIALRGB_EFFECT_SOLID_COLOR,
    VIALRGB_EFFECT_ALPHAS_MODS,
    VIALRGB_EFFECT_GRADIENT_UP_DOWN_ANIM,
    VIALRGB_EFFECT_GRADIENT_LEFT_RIGHT_ANIM,
    VIALRGB_EFFECT_BREATHING_ANIM,
    VIALRGB_EFFECT_COLORBAND_SAT_ANIM,
    VIALRGB_EFFECT_COLORBAND_VAL_ANIM,
    VIALRGB_EFFECT_COLORBAND_PINWHEEL_SAT_ANIM,
    VIALRGB_EFFECT_COLORBAND_PINWHEEL_VAL_ANIM,
    VIALRGB_EFFECT_COLORBAND_SPIRAL_SAT_ANIM,
    VIALRGB_EFFECT_COLORBAND_SPIRAL_VAL_ANIM,
    VIALRGB_EFFECT_CYCLE_ALL_ANIM,
    VIALRGB_EFFECT_CYCLE_LEFT_RIGHT_ANIM,
    VIALRGB_EFFECT_CYCLE_UP_DOWN_ANIM,
    VIALRGB_EFFECT_RAINBOW_MOVING_CHEVRON_ANIM,
    VIALRGB_EFFECT_CYCLE_OUT_IN_ANIM,
    VIALRGB_EFFECT_CYCLE_OUT_IN_DUAL_ANIM,
    VIALRGB_EFFECT_CYCLE_PINWHEEL_ANIM,
    VIALRGB_EFFECT_CYCLE_SPIRAL_ANIM,
    VIALRGB_EFFECT_DUAL_BEACON_ANIM,
    VIALRGB_EFFECT_RAINBOW_BEACON_ANIM,
    VIALRGB_EFFECT_RAINBOW_PINWHEELS_ANIM,
    VIALRGB_EFFECT_RAINDROPS_ANIM,
    VIALRGB_EFFECT_JELLYBEAN_RAINDROPS_ANIM,
    VIALRGB_EFFECT_HUE_BREATHING_ANIM,
    VIALRGB_EFFECT_HUE_PENDULUM_ANIM,
    VIALRGB_EFFECT_HUE_WAVE_ANIM,
    VIALRGB_EFFECT_TYPING_HEATMAP_ANIM,
    VIALRGB_EFFECT_DIGITAL_RAIN_ANIM,
    VIALRGB_EFFECT_SOLID_REACTIVE_SIMPLE_ANIM,
    VIALRGB_EFFECT_SOLID_REACTIVE_ANIM,
    VIALRGB_EFFECT_SOLID_REACTIVE_WIDE,
    VIALRGB_EFFECT_SOLID_REACTIVE_CROSS,
    VIALRGB_EFFECT_SOLID_REACTIVE_NEXUS,
    VIALRGB_EFFECT_SPLASH_ANIM,
    VIALRGB_EFFECT_SOLID_SPLASH_ANIM,
};

typedef struct {
    uint16_t vialrgb_id;
    uint16_t qmk_id;
} vialrgb_supported_mode_t;

static const PROGMEM vialrgb_supported_mode_t supported_modes[] = {
    { VIALRGB_EFFECT_OFF, 0 },
    // { VIALRGB_EFFECT_DIRECT, 0 }, TODO
#ifdef RGB_MATRIX_EFFECT_SOLID_COLOR
    { VIALRGB_EFFECT_SOLID_COLOR, RGB_MATRIX_SOLID_COLOR },
#endif
#ifdef RGB_MATRIX_EFFECT_ALPHAS_MODS
    { VIALRGB_EFFECT_ALPHAS_MODS, RGB_MATRIX_ALPHAS_MODS },
#endif
};

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
        args[0] = qmk_id_to_vialrgb_id(rgb_matrix_get_mode());
        args[1] = rgb_matrix_get_speed();
        args[2] = rgb_matrix_get_hue();
        args[3] = rgb_matrix_get_sat();
        args[4] = rgb_matrix_get_val();
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
        rgb_matrix_mode_noeeprom(vialrgb_id_to_qmk_id(args[0]));
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
