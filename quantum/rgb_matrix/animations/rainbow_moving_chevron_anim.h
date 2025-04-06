#ifdef ENABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON
RGB_MATRIX_EFFECT(RAINBOW_MOVING_CHEVRON)
#    ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

static hsv_t RAINBOW_MOVING_CHEVRON_math(hsv_t hsv, uint8_t i, uint8_t time) {
    hsv.h += abs8(g_led_config.point[i].y - k_rgb_matrix_center.y) + (g_led_config.point[i].x - time);
    return hsv;
}

bool RAINBOW_MOVING_CHEVRON(effect_params_t* params) {
    return effect_runner_i(params, &RAINBOW_MOVING_CHEVRON_math);
}

#    endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
#endif     // ENABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON
