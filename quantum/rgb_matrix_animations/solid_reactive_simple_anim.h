#ifdef RGB_MATRIX_KEYREACTIVE_ENABLED
#ifndef DISABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE
RGB_MATRIX_EFFECT(SOLID_REACTIVE_SIMPLE)
#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

static void SOLID_REACTIVE_SIMPLE_math(HSV* hsv, uint16_t offset) {
    hsv->v = scale8(255 - offset, rgb_matrix_config.val);
}

bool SOLID_REACTIVE_SIMPLE(effect_params_t* params) {
    return effect_runner_reactive(params, &SOLID_REACTIVE_SIMPLE_math);
}

#endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
#endif // DISABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE
#endif // RGB_MATRIX_KEYREACTIVE_ENABLED
