#pragma once

typedef uint8_t (*i_f)(uint8_t val, uint8_t i, uint8_t time);

bool effect_runner_i(effect_params_t* params, i_f effect_func) {
    LED_MATRIX_USE_LIMITS(led_min, led_max);

    uint8_t time = scale16by8(g_led_timer, led_matrix_eeconfig.speed / 4);
    for (uint8_t i = led_min; i < led_max; i++) {
        LED_MATRIX_TEST_LED_FLAGS();
        led_matrix_set_value(i, effect_func(led_matrix_eeconfig.val, i, time));
    }
    return led_max < DRIVER_LED_TOTAL;
}
