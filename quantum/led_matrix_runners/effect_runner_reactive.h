#pragma once

#ifdef LED_MATRIX_KEYREACTIVE_ENABLED

typedef uint8_t (*reactive_f)(uint8_t val, uint16_t offset);

bool effect_runner_reactive(effect_params_t* params, reactive_f effect_func) {
    LED_MATRIX_USE_LIMITS(led_min, led_max);

    uint16_t max_tick = 65535 / led_matrix_eeconfig.speed;
    for (uint8_t i = led_min; i < led_max; i++) {
        LED_MATRIX_TEST_LED_FLAGS();
        uint16_t tick = max_tick;
        // Reverse search to find most recent key hit
        for (int8_t j = g_last_hit_tracker.count - 1; j >= 0; j--) {
            if (g_last_hit_tracker.index[j] == i && g_last_hit_tracker.tick[j] < tick) {
                tick = g_last_hit_tracker.tick[j];
                break;
            }
        }

        uint16_t offset = scale16by8(tick, led_matrix_eeconfig.speed);
        led_matrix_set_value(i, effect_func(led_matrix_eeconfig.val, offset));
    }
    return led_max < DRIVER_LED_TOTAL;
}

#endif  // LED_MATRIX_KEYREACTIVE_ENABLED
