#pragma once

typedef uint8_t (*sin_cos_i_f)(uint8_t val, int8_t sin, int8_t cos, uint8_t i, uint8_t time);

bool effect_runner_sin_cos_i(effect_params_t* params, sin_cos_i_f effect_func) {
    LED_MATRIX_USE_LIMITS(led_min, led_max);

    uint16_t time      = scale16by8(g_led_timer, led_matrix_eeconfig.speed / 4);
    int8_t   cos_value = cos8(time) - 128;
    int8_t   sin_value = sin8(time) - 128;
    for (uint8_t i = led_min; i < led_max; i++) {
        LED_MATRIX_TEST_LED_FLAGS();
        led_matrix_set_value(i, effect_func(led_matrix_eeconfig.val, cos_value, sin_value, i, time));
    }
    return led_max < DRIVER_LED_TOTAL;
}
