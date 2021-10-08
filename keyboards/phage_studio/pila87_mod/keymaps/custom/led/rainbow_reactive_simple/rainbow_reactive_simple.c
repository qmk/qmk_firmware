#include "led/rainbow_reactive_simple/rainbow_reactive_simple.h"

static HSV RAINBOW_REACTIVE_SIMPLE_math(HSV hsv, uint8_t i, uint8_t time, uint16_t offset) {
    hsv.h = g_led_config.point[i].x - time;
    hsv.v = scale8(255 - offset, hsv.v);
    return hsv;
}

bool RAINBOW_REACTIVE_SIMPLE(effect_params_t* params) { return effect_rainbow_reactive(params, &RAINBOW_REACTIVE_SIMPLE_math); }