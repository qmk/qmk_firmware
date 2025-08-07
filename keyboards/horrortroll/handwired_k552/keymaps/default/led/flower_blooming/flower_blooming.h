#pragma once

typedef hsv_t (*flower_blooming_f)(hsv_t hsv, uint8_t i, uint8_t time);

bool effect_runner_bloom(effect_params_t* params, flower_blooming_f effect_func) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);

    uint8_t time = scale16by8(g_rgb_timer, qadd8(rgb_matrix_config.speed / 10, 1));
    for (uint8_t i = led_min; i < led_max; i++) {
        RGB_MATRIX_TEST_LED_FLAGS();
        if (g_led_config.point[i].y > k_rgb_matrix_center.y) {
            rgb_t bgr = rgb_matrix_hsv_to_rgb(effect_func(rgb_matrix_config.hsv, i, time));
            rgb_matrix_set_color(i, bgr.b, bgr.g, bgr.r);
        } else {
            rgb_t rgb = rgb_matrix_hsv_to_rgb(effect_func(rgb_matrix_config.hsv, i, time));
            rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
        }
    }
    return rgb_matrix_check_finished_leds(led_max);
}
