// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later
#include <stdbool.h>
#include <string.h>

// TODO: Pack "enabled" of single LED more efficiently than as alpha channels
typedef struct PACKED rgba_t {
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
} rgba_t;

#define OVERLAY_DOUBLE_BUFFER
#ifdef OVERLAY_DOUBLE_BUFFER
rgba_t overlay_buffer_a[RGB_MATRIX_LED_COUNT] = {0};
rgba_t overlay_buffer_b[RGB_MATRIX_LED_COUNT] = {0};

rgba_t* overlay_buffer_render = overlay_buffer_a;
rgba_t* overlay_buffer_write  = overlay_buffer_b;
#else
rgba_t overlay_buffer[RGB_MATRIX_LED_COUNT] = {0};

rgba_t* overlay_buffer_render = overlay_buffer;
rgba_t* overlay_buffer_write  = overlay_buffer;
#endif

static bool is_enabled = false;

void rgb_matrix_overlay_enable(bool enable) {
    is_enabled = enable;
}

void rgb_matrix_overlay_set(uint8_t index, rgba_t color) {
    overlay_buffer_write[index] = color;
}

void rgb_matrix_overlay_flush(void) {
#ifdef OVERLAY_DOUBLE_BUFFER
    memcpy(overlay_buffer_render, overlay_buffer_write, sizeof(rgba_t) * RGB_MATRIX_LED_COUNT);

    rgba_t* buffer_tmp    = overlay_buffer_render;
    overlay_buffer_render = overlay_buffer_write;
    overlay_buffer_write  = buffer_tmp;
#endif
}

bool rgb_matrix_indicators_user(void) {
    if (!is_enabled) return true;

    for (uint8_t i = 0; i < RGB_MATRIX_LED_COUNT; i++) {
        rgba_t* led = &overlay_buffer_render[i];

        // Allow "transparent" to running effect?
        if (led->a) rgb_matrix_set_color(i, led->r, led->g, led->b);
    }

    return false;
}
