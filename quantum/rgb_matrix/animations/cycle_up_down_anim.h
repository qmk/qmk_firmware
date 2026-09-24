#ifdef ENABLE_RGB_MATRIX_CYCLE_UP_DOWN
RGB_MATRIX_EFFECT(CYCLE_UP_DOWN)
#    ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

static hsv_t CYCLE_UP_DOWN_math(hsv_t hsv, uint8_t i, uint8_t time) {
    hsv.h = g_led_config.point[i].y - time;
    return hsv;
}

bool CYCLE_UP_DOWN(effect_params_t* params) {
    return effect_runner_i(params, &CYCLE_UP_DOWN_math);
}

#    endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
#endif     // ENABLE_RGB_MATRIX_CYCLE_UP_DOWN
