#if defined(VIALRGB_ENABLE) && !defined(VIALRGB_NO_DIRECT)
#define RGB_MATRIX_EFFECT_VIALRGB_DIRECT
RGB_MATRIX_EFFECT(VIALRGB_DIRECT)
#    ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

extern HSV g_direct_mode_colors[DRIVER_LED_TOTAL];

bool VIALRGB_DIRECT(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);

    for (uint8_t i = led_min; i < led_max; i++) {
        RGB rgb = rgb_matrix_hsv_to_rgb(g_direct_mode_colors[i]);
        rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
    }
    return led_max < DRIVER_LED_TOTAL;
}
#    endif
#endif
