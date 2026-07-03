// Copyright 2022 @art-was-here
// SPDX-License-Identifier: GPL-2.0+

#ifdef ENABLE_RGB_MATRIX_STARLIGHT_SMOOTH
RGB_MATRIX_EFFECT(STARLIGHT_SMOOTH)
#    ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

static uint8_t phase_offsets[RGB_MATRIX_LED_COUNT];

hsv_t STARLIGHT_SMOOTH_math(hsv_t hsv, uint8_t i, uint8_t time) {
    if (phase_offsets[i] == 0) {
        phase_offsets[i] = random8();
    }
    hsv.v = scale8(abs8(sin8((time + phase_offsets[i]) / 2) - 128) * 2, hsv.v);
    return hsv;
}

bool STARLIGHT_SMOOTH(effect_params_t* params) {
    if (params->init) {
        memset(phase_offsets, 0, sizeof(phase_offsets));
    }
    return effect_runner_i(params, &STARLIGHT_SMOOTH_math);
}

#    endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
#endif     // ENABLE_RGB_MATRIX_STARLIGHT_SMOOTH
