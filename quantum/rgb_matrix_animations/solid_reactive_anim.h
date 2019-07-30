#ifdef RGB_MATRIX_KEYREACTIVE_ENABLED
#ifndef DISABLE_RGB_MATRIX_SOLID_REACTIVE
RGB_MATRIX_EFFECT(SOLID_REACTIVE)
#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

static HSV SOLID_REACTIVE_math(HSV hsv,  uint16_t offset) {
    hsv.h += qsub8(130, offset);
    return hsv;
}

bool SOLID_REACTIVE(effect_params_t* params) {
    return effect_runner_reactive(params, &SOLID_REACTIVE_math);
}

#endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
#endif // DISABLE_RGB_MATRIX_SOLID_REACTIVE
#endif // RGB_MATRIX_KEYREACTIVE_ENABLED
