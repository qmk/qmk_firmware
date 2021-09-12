#ifdef ENABLE_RGB_MATRIX_HUE_PENDULUM
#define RGB_MATRIX_EFFECT_HUE_PENDULUM
RGB_MATRIX_EFFECT(HUE_PENDULUM)
#    ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

// Change huedelta to adjust range of hue change. 0-255.
// Looks better with a low value and slow speed for subtle change.
// Hue Pendulum - color changes in a wave to the right before reversing direction
static HSV HUE_PENDULUM_math(HSV hsv, uint8_t i, uint8_t time) {
    uint8_t huedelta = 12;
    hsv.h            = hsv.h + scale8(abs8(sin8(time) + (g_led_config.point[i].x) - 128) * 2, huedelta);
    return hsv;
}

bool HUE_PENDULUM(effect_params_t* params) { return effect_runner_i(params, &HUE_PENDULUM_math); }

#    endif  // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
#endif      // DISABLE_RGB_HUE_PENDULUM
