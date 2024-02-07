RGB_MATRIX_EFFECT(SIGNALRGB)
#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

bool SIGNALRGB(effect_params_t* params) 
{
    RGB_MATRIX_USE_LIMITS(led_min, led_max);

    return rgb_matrix_check_finished_leds(led_max);
}

#endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
