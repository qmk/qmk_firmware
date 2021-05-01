#ifdef RGB_MATRIX_KEYREACTIVE_ENABLED
RGB_MATRIX_EFFECT(my_reactive_col)

#    ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

static HSV my_reactive_col_math(HSV hsv, int16_t dx, int16_t dy, uint8_t dist, uint16_t tick) {
    uint16_t effect = tick + dist;
    dx              = dx < 0 ? dx * -1 : dx;
    dx              = dx * 16 > 255 ? 255 : dx * 16;
    effect += dx;
    if (effect > 255) effect = 255;
    hsv.v = qadd8(hsv.v, 255 - effect);
    // hsv.h += qsub8(130, effect);
    return hsv;
}

bool my_reactive_col(effect_params_t* params) {
    return effect_runner_reactive_splash(0, params, &my_reactive_col_math);
}

#    endif      // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
#endif          // RGB_MATRIX_KEYREACTIVE_ENABLED
