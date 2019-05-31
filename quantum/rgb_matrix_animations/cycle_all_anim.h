#ifndef DISABLE_RGB_MATRIX_CYCLE_ALL
RGB_MATRIX_EFFECT(CYCLE_ALL)
#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

static void CYCLE_ALL_math(HSV* hsv, uint8_t i, uint8_t time)
{
    hsv->h = time;
}

bool CYCLE_ALL(effect_params_t* params) {
    return effect_runner_i(params, &CYCLE_ALL_math);
}

#endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
#endif // DISABLE_RGB_MATRIX_CYCLE_ALL
