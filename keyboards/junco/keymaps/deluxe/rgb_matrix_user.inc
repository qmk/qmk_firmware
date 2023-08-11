// Copyright 2022 Dane Skalski (@Daneski13)
// SPDX-License-Identifier: GPL-2.0-or-later

RGB_MATRIX_EFFECT(WHITE_UNDERGLOW_CYCLE)
RGB_MATRIX_EFFECT(PIXEL_RAIN_UNDERGLOW_CYCLE)

#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

// This is a modified version of the effect_runner_dx_dy_dist function from rgb_matrix
// that only applies the effect to the underglow LEDs of this keyboard
static bool underglow_effect_runner(effect_params_t* params, dx_dy_dist_f underglow_effect_func, bool backlight_white) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);

    HSV hsv = rgb_matrix_config.hsv;
    HSV white = {0, 0, hsv.v};
    RGB rgb = rgb_matrix_hsv_to_rgb(white);
    uint8_t time = scale16by8(g_rgb_timer, rgb_matrix_config.speed / 2);
    for (uint8_t i = led_min; i < led_max; i++) {
        // Underglow LEDs are indicies 0 - 7 and 37 - 44
        if ((i <= 7) || (37 <= i && i <= 44)) {
            // Apply the maths and colors to the underglow LEDs
            RGB_MATRIX_TEST_LED_FLAGS();
            int16_t dx   = g_led_config.point[i].x - k_rgb_matrix_center.x;
            int16_t dy   = g_led_config.point[i].y - k_rgb_matrix_center.y;
            uint8_t dist = sqrt16(dx * dx + dy * dy);
            RGB     rgb  = rgb_matrix_hsv_to_rgb(underglow_effect_func(hsv, dx, dy, dist, time));
            rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
        } else {
            // Set the backlight to white if needed
            if (!backlight_white) continue;
            rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
        }
    }
    return rgb_matrix_check_finished_leds(led_max);
}

// Solid white but the underglow is a rainbow spiral
static bool WHITE_UNDERGLOW_CYCLE(effect_params_t* params) {
    return underglow_effect_runner(params, &CYCLE_SPIRAL_math, true);
}

// Pixel rain effect but the underglow is a rainbow spiral
static bool PIXEL_RAIN_UNDERGLOW_CYCLE(effect_params_t* params) {
    PIXEL_RAIN(params);
    return underglow_effect_runner(params, &CYCLE_SPIRAL_math, false);
}

#endif
