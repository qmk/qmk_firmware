// Copyright (C) 2022 @filterpaper
// SPDX-License-Identifier: GPL-2.0-or-later
// Inspired by 4x12 fractal from @GEIGEIGEIST

#ifdef ENABLE_RGB_MATRIX_PIXEL_FRACTAL
RGB_MATRIX_EFFECT(PIXEL_FRACTAL)
#    ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

static bool PIXEL_FRACTAL(effect_params_t* params) {
#        if MATRIX_COLS < 2
#            define MID_COL 1
#        else
#            define MID_COL MATRIX_COLS / 2
#        endif
    static bool     led[MATRIX_ROWS][MID_COL];
    static uint32_t wait_timer = 0;

    inline uint32_t interval(void) {
        return 3000 / scale16by8(qadd8(rgb_matrix_config.speed, 16), 16);
    }

    if (params->init) {
        rgb_matrix_set_color_all(0, 0, 0);
    }

    RGB_MATRIX_USE_LIMITS(led_min, led_max);

    if (g_rgb_timer > wait_timer) {
        rgb_t rgb = rgb_matrix_hsv_to_rgb(rgb_matrix_config.hsv);
        for (uint8_t h = 0; h < MATRIX_ROWS; ++h) {
            // Light and copy columns outward
            for (uint8_t l = 0; l < MID_COL - 1; ++l) {
                rgb_t index_rgb = led[h][l] ? (rgb_t){rgb.r, rgb.g, rgb.b} : (rgb_t){0, 0, 0};
                if (HAS_ANY_FLAGS(g_led_config.flags[g_led_config.matrix_co[h][l]], params->flags)) {
                    rgb_matrix_set_color(g_led_config.matrix_co[h][l], index_rgb.r, index_rgb.g, index_rgb.b);
                }
                if (HAS_ANY_FLAGS(g_led_config.flags[g_led_config.matrix_co[h][MATRIX_COLS - 1 - l]], params->flags)) {
                    rgb_matrix_set_color(g_led_config.matrix_co[h][MATRIX_COLS - 1 - l], index_rgb.r, index_rgb.g, index_rgb.b);
                }
                led[h][l] = led[h][l + 1];
            }

            // Light both middle columns
            rgb_t index_rgb = led[h][MID_COL - 1] ? (rgb_t){rgb.r, rgb.g, rgb.b} : (rgb_t){0, 0, 0};
            if (HAS_ANY_FLAGS(g_led_config.flags[g_led_config.matrix_co[h][MID_COL - 1]], params->flags)) {
                rgb_matrix_set_color(g_led_config.matrix_co[h][MID_COL - 1], index_rgb.r, index_rgb.g, index_rgb.b);
            }
            if (HAS_ANY_FLAGS(g_led_config.flags[g_led_config.matrix_co[h][MATRIX_COLS - MID_COL]], params->flags)) {
                rgb_matrix_set_color(g_led_config.matrix_co[h][MATRIX_COLS - MID_COL], index_rgb.r, index_rgb.g, index_rgb.b);
            }

            // Generate new random fractal column
            led[h][MID_COL - 1] = (random8() & 3) ? false : true;
        }

        wait_timer = g_rgb_timer + interval();
    }

    return rgb_matrix_check_finished_leds(led_max);
}
#    endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
#endif     // ENABLE_RGB_MATRIX_PIXEL_FRACTAL
