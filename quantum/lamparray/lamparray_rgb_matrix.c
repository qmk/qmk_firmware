// Copyright 2024 QMK
// SPDX-License-Identifier: GPL-2.0-or-later
#include "lamparray.h"
#include "lamparray_surface.h"
#include "rgb_matrix.h"

/**
 * \brief Get feature specific lamp info.
 *
 * Scales the LED config with the assumed RGB Matrix dimensions (224x64), for simplicity, as a completely flat device.
 * Assumes all keys are either on the top or bottom of the resulting rectangle.
 */
__attribute__((weak)) void lamparray_get_lamp_impl(uint16_t lamp_id, lamparray_attributes_response_t* data) {
    data->position.x = (LAMPARRAY_WIDTH / 224) * g_led_config.point[lamp_id].x;
    data->position.y = (LAMPARRAY_HEIGHT / 64) * g_led_config.point[lamp_id].y;

    if (g_led_config.flags[lamp_id] & LED_FLAG_UNDERGLOW) {
        data->position.z = LAMPARRAY_DEPTH;
        data->purposes   = LAMP_PURPOSE_ACCENT;
    } else if (g_led_config.flags[lamp_id] & LED_FLAG_INDICATOR) {
        data->position.z = 0;
        data->purposes   = LAMP_PURPOSE_STATUS;
    } else {
        data->position.z = 0;
        data->purposes   = LAMP_PURPOSE_CONTROL;
    }
}

/**
 * \brief Query a HID usage for a given lamp
 */
__attribute__((weak)) uint8_t lamparray_get_lamp_binding_impl(uint16_t lamp_id) {
    for (uint8_t i_row = 0; i_row < MATRIX_ROWS; i_row++) {
        for (uint8_t i_col = 0; i_col < MATRIX_COLS; i_col++) {
            if (g_led_config.matrix_co[i_row][i_col] == lamp_id) {
                return lamparray_binding_at_keymap_location(i_row, i_col);
            }
        }
    }
    return 0;
}

// TODO: temporay binding of storage and render
#include "rgb_matrix/overlay.c"

void lamparray_surface_enable(bool enable) {
    rgb_matrix_overlay_enable(enable);
}

void lamparray_surface_set_item(uint16_t index, lamp_state_t color) {
    rgb_matrix_overlay_set(index, (rgba_t){color.red, color.green, color.blue, color.intensity ? 0xFF : 0});
}

void lamparray_surface_update_finished(void) {
    rgb_matrix_overlay_flush();
}
