// Copyright 2022 HorrorTroll <https://github.com/HorrorTroll>
// Copyright 2023 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
// SPDX-License-Identifier: GPL-3.0-or-later

RGB_MATRIX_EFFECT(COOL_DIAGONAL)

#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

static HSV COOL_DIAGONAL_math(HSV hsv, uint8_t i, uint8_t time) {
    hsv.h = (g_led_config.point[i].x / 4) - g_led_config.point[i].y - time;
    return hsv;
}

bool COOL_DIAGONAL(effect_params_t* params) {
    return effect_runner_i(params, &COOL_DIAGONAL_math);
}
#endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
