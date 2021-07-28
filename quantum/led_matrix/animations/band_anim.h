#ifdef ENABLE_LED_MATRIX_BAND
LED_MATRIX_EFFECT(BAND)
#    ifdef LED_MATRIX_CUSTOM_EFFECT_IMPLS

static uint8_t BAND_math(uint8_t val, uint8_t i, uint8_t time) {
    int16_t v = val - abs(scale8(g_led_config.point[i].x, 228) + 28 - time) * 8;
    return scale8(v < 0 ? 0 : v, val);
}

bool BAND(effect_params_t* params) { return effect_runner_i(params, &BAND_math); }

#    endif  // LED_MATRIX_CUSTOM_EFFECT_IMPLS
#endif      // DISABLE_LED_MATRIX_BAND
