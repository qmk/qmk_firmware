RGB_MATRIX_EFFECT(SINGLE_COLOR_RAINDROPS)
RGB_MATRIX_EFFECT(STATIC_GAME_MODE)
#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

/* This effect has been partially derived from quantum/rgb_matrix/animations/pixel_rain_anim.h and raindrops_anim.h 
It sets random LEDs to matrix color (with very slight hue variation) but random intensity */
static bool SINGLE_COLOR_RAINDROPS(effect_params_t* params) {
    static uint32_t wait_timer = 0;

    // interval function and timing in general taken from pixel rain animation
    inline uint32_t interval(void) {
        return 500 / scale16by8(qadd8(rgb_matrix_config.speed, 16), 16);
    }

    void single_color_raindrops_set_color(uint8_t i, effect_params_t * params) {
        if (!HAS_ANY_FLAGS(g_led_config.flags[i], params->flags)) {
            return;
        }
        
        // Take matrix color, add between -5 and +5 to hue, random brightness between 0 and val, set to 0 if val between 0 and 5, then write to LED
        hsv_t hsv = rgb_matrix_get_hsv();
        hsv.h = rgb_matrix_get_hue() - 2 + random8() % 5;
        hsv.v = random8() % rgb_matrix_get_val();
        if (hsv.v < 5) { 
            hsv.v = 0;
        }
        rgb_t rgb = rgb_matrix_hsv_to_rgb(hsv);
        rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
        wait_timer = g_rgb_timer + interval();
    }

    RGB_MATRIX_USE_LIMITS(led_min, led_max);
    if (!params->init) {
        if (g_rgb_timer > wait_timer) {
            single_color_raindrops_set_color(mod8(random8(), RGB_MATRIX_LED_COUNT), params);
        }
    } else {
        for (int i = led_min; i < led_max; i++) {
            single_color_raindrops_set_color(i, params);
        }
    }
    return rgb_matrix_check_finished_leds(led_max);
}

/* This "effect" is a workaround to fix long matrix scan pauses caused by i2c communication.
When enabled, it writes all relevant LEDs once to static colors, then halts LED refreshes until a different animation is selcted. */
bool STATIC_GAME_MODE(effect_params_t* params) {

    void game_mode_set_color(int i, effect_params_t* params) {
        if (!HAS_ANY_FLAGS(g_led_config.flags[i], params->flags)) {
            return;
        }

        hsv_t hsv = rgb_matrix_get_hsv();

        switch (i) {
            case W_LED_INDEX:
            case A_LED_INDEX:
            case S_LED_INDEX:
            case D_LED_INDEX:

            case M_LED_INDEX:
            case K_LED_INDEX:
            case O_LED_INDEX:
            case P_LED_INDEX:
            case NUM_0_LED_INDEX:
            case SLSH_LED_INDEX:
                break;

            case SCLN_LED_INDEX:
            case ANV_A_LED_INDEX:
            case ANV_N_LED_INDEX:
            case ANV_V_LED_INDEX:
            case ANV_I_LED_INDEX:
            case ANV_L_LED_INDEX:
                hsv.s = 255;
                hsv.h = rgb_matrix_get_hue()+30;
                break;

            case NUM_1_LED_INDEX:
            case NUM_2_LED_INDEX:
            case NUM_3_LED_INDEX:
            case NUM_4_LED_INDEX:
            case NUM_5_LED_INDEX:
                hsv.s = 255;
                hsv.h = rgb_matrix_get_hue()+30;
                hsv.v = rgb_matrix_get_val()*2/3;
                break;

            default:
                hsv.v = 0;
                break;
        }

        rgb_t rgb = hsv_to_rgb(hsv);
        rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
    }

    RGB_MATRIX_USE_LIMITS(led_min, led_max);
    if (!params->init) {
        // Do not update LEDs after initial blanking
    } else {
        for (int i = led_min; i < led_max; i++) {
            game_mode_set_color(i, params);
        }
    }
    return rgb_matrix_check_finished_leds(led_max);
}

#endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
