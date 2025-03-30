#ifdef ENABLE_RGB_MATRIX_RIVERFLOW
RGB_MATRIX_EFFECT(RIVERFLOW)
#    ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

// inspired by @PleasureTek's Massdrop Alt LED animation

hsv_t RIVERFLOW_math(hsv_t hsv, uint8_t i, uint8_t time) {
    time  = scale16by8(g_rgb_timer + (i * 315), rgb_matrix_config.speed / 8);
    hsv.v = scale8(abs8(sin8(time) - 128) * 2, hsv.v);
    return hsv;
}

bool RIVERFLOW(effect_params_t* params) {
    return effect_runner_i(params, &RIVERFLOW_math);
}

#    endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
#endif     // ENABLE_RGB_MATRIX_RIVERFLOW
