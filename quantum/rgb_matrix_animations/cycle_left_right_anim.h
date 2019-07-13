#ifndef DISABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT
RGB_MATRIX_EFFECT(CYCLE_LEFT_RIGHT)
#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

static HSV CYCLE_LEFT_RIGHT_math(HSV hsv,  uint8_t i, uint8_t time) {
    hsv.h = g_led_config.point[i].x - time;
    return hsv;
}

bool CYCLE_LEFT_RIGHT(effect_params_t* params) {
    return effect_runner_i(params, &CYCLE_LEFT_RIGHT_math);
}

#endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
#endif // DISABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT
