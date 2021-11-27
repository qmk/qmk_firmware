#if defined(RGB_MATRIX_KEYPRESSES)
RGB_MATRIX_EFFECT(saturated_solid_multisplash)

#   if defined(RGB_MATRIX_CUSTOM_EFFECT_IMPLS)

static bool saturated_solid_multisplash(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);

    uint8_t count = g_last_hit_tracker.count;
    for (uint8_t i = led_min; i < led_max; i++) {
        RGB_MATRIX_TEST_LED_FLAGS();
        HSV hsv = rgb_matrix_config.hsv;
        hsv.v   = 0;
        for (uint8_t j = 0; j < count; j++) {
            int16_t  dx   = g_led_config.point[i].x - g_last_hit_tracker.x[j];
            int16_t  dy   = g_led_config.point[i].y - g_last_hit_tracker.y[j];
            uint8_t  dist = sqrt16(dx * dx + dy * dy);
            uint16_t tick = scale16by8(g_last_hit_tracker.tick[j], qadd8(rgb_matrix_config.speed, 1));

            uint16_t effect = tick - dist;
            if (effect > 255) effect = 255;
            uint16_t vdiff = scale16by8(255 - effect, 255 - dist);
            hsv.v = qadd8(hsv.v, vdiff);
            hsv.s = qsub8(hsv.s, qsub8(127, effect));
        }
        hsv.v   = scale8(hsv.v, rgb_matrix_config.hsv.v);
        RGB rgb = rgb_matrix_hsv_to_rgb(hsv);
        rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
    }
    return led_max < DRIVER_LED_TOTAL;
}

#   endif   // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
#endif      // RGB_MATRIX_KEYPRESSES
