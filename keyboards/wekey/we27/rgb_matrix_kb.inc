
//RGB_MATRIX_EFFECT(SOLID_REACTIVE_WIDE2)
RGB_MATRIX_EFFECT(SOLID_REACTIVE_MULTIWIDE2)
//RGB_MATRIX_EFFECT(SOLID_REACTIVE_NEXUS2)
//RGB_MATRIX_EFFECT(SOLID_REACTIVE_MULTINEXUS2)

#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

static HSV SOLID_REACTIVE_WIDE_math2(HSV hsv, int16_t dx, int16_t dy, uint8_t dist, uint16_t tick) {
    uint16_t effect = tick - dist > 255 || dist > 32 ? 255 : tick - dist;
    hsv.v           = qadd8(hsv.v, 255 - effect);
    return hsv;
}

static HSV SOLID_REACTIVE_NEXUS_math2(HSV hsv, int16_t dx, int16_t dy, uint8_t dist, uint16_t tick) {
    uint16_t effect = tick - dist > 255 || ((dx > 8 || dx < -8) && (dy > 8 || dy < -8)) ? 255 : tick - dist;
    hsv.v           = qadd8(hsv.v, 255 - effect);
    hsv.h           = rgb_matrix_config.hsv.h + dy / 4;
    return hsv;
}

bool SOLID_REACTIVE_WIDE2(effect_params_t* params) { return effect_runner_reactive_splash(qsub8(g_last_hit_tracker.count, 1), params, &SOLID_REACTIVE_WIDE_math2); }
bool SOLID_REACTIVE_MULTIWIDE2(effect_params_t* params) { return effect_runner_reactive_splash(0, params, &SOLID_REACTIVE_WIDE_math2); }
bool SOLID_REACTIVE_NEXUS2(effect_params_t* params) { return effect_runner_reactive_splash(qsub8(g_last_hit_tracker.count, 1), params, &SOLID_REACTIVE_NEXUS_math2); }
bool SOLID_REACTIVE_MULTINEXUS2(effect_params_t* params) { return effect_runner_reactive_splash(0, params, &SOLID_REACTIVE_NEXUS_math2); }

#endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS 
