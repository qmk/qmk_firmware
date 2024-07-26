#pragma once

typedef uint8_t (*dx_dy_f)(uint8_t val, int16_t dx, int16_t dy, uint8_t time);

bool effect_runner_dx_dy(effect_params_t* params, dx_dy_f effect_func) {
    LED_MATRIX_USE_LIMITS(led_min, led_max);

    uint8_t time = scale16by8(g_led_timer, led_matrix_eeconfig.speed / 2);
    for (uint8_t i = led_min; i < led_max; i++) {
        LED_MATRIX_TEST_LED_FLAGS();
        int16_t dx = g_led_config.point[i].x - k_led_matrix_center.x;
        int16_t dy = g_led_config.point[i].y - k_led_matrix_center.y;
        led_matrix_set_value(i, effect_func(led_matrix_eeconfig.val, dx, dy, time));
    }
    return led_matrix_check_finished_leds(led_max);
}
