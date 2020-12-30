RGB_MATRIX_EFFECT(rainbow_stripe)

#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

static HSV rainbow_stripe_math(HSV hsv, uint8_t i, uint8_t time) {
    if (i >= 14 && i <= 21) {
        hsv.h = g_led_config.point[i].x - time;
    } else {
        hsv.v = 0;
    }
    return hsv;
}

bool rainbow_stripe(effect_params_t* params) {
    return effect_runner_i(params, &rainbow_stripe_math);
}

#endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
