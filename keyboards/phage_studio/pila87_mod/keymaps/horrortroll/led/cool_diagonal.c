static HSV COOL_DIAGONAL_math(HSV hsv, uint8_t i, uint8_t time) {
    hsv.h = (g_led_config.point[i].x / 4) - g_led_config.point[i].y - time;
    return hsv;
}

bool COOL_DIAGONAL(effect_params_t* params) { return effect_runner_i(params, &COOL_DIAGONAL_math); }