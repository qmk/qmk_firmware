#pragma once

#ifdef LED_MATRIX_KEYREACTIVE_ENABLED

typedef uint8_t (*reactive_splash_f)(uint8_t val, int16_t dx, int16_t dy, uint8_t dist, uint16_t tick);

bool effect_runner_reactive_splash(uint8_t start, effect_params_t* params, reactive_splash_f effect_func) {
    LED_MATRIX_USE_LIMITS(led_min, led_max);

    uint8_t count = g_last_hit_tracker.count;
    for (uint8_t i = led_min; i < led_max; i++) {
        LED_MATRIX_TEST_LED_FLAGS();
        uint8_t val = 0;
        for (uint8_t j = start; j < count; j++) {
            int16_t  dx   = g_led_config.point[i].x - g_last_hit_tracker.x[j];
            int16_t  dy   = g_led_config.point[i].y - g_last_hit_tracker.y[j];
            uint8_t  dist = sqrt16(dx * dx + dy * dy);
            uint16_t tick = scale16by8(g_last_hit_tracker.tick[j], led_matrix_eeconfig.speed);
            val           = effect_func(val, dx, dy, dist, tick);
        }
        led_matrix_set_value(i, scale8(val, led_matrix_eeconfig.val));
    }
    return led_matrix_check_finished_leds(led_max);
}

#endif // LED_MATRIX_KEYREACTIVE_ENABLED
