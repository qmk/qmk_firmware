static HSV DIAGONAL_math(HSV hsv, uint8_t i, uint8_t time) {
    hsv.h = g_led_config.point[i].x - g_led_config.point[i].y - time;
    return hsv;
}

bool DIAGONAL(effect_params_t* params) { return effect_runner_i(params, &DIAGONAL_math); }