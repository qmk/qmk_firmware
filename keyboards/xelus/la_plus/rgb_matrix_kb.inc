// Step 1.
// Declare custom effects using the RGB_MATRIX_EFFECT macro
// (note the lack of semicolon after the macro!)
RGB_MATRIX_EFFECT(startup_animation_dots)
RGB_MATRIX_EFFECT(startup_animation_solid)

// Step 2.
// Define effects inside the `RGB_MATRIX_CUSTOM_EFFECT_IMPLS` ifdef block
#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

#include "eeprom.h"
#include "eeconfig.h"

static void startup_animation_setleds(effect_params_t* params, bool dots) {
    uint8_t factor = 5;
    hsv_t      hsv  = rgb_matrix_config.hsv;
    rgb_t rgb       = rgb_matrix_hsv_to_rgb(hsv);
    if (dots) {
        rgb_matrix_set_color_all(0, 0, 0);
    }
    int32_t num = (g_rgb_timer & (0b11111 << factor)) >> factor;

    if (num == 17 || num == 18 || num == 19 ||
        num == 20 || num == 21) {
        if (dots == true) {
            for (int i = 0; i < 28; i++) {
                rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
            }
        }
        return;
    } else if (num == 0 || num == 1 || num == 2) {
        return;
    } else if (num >= 22) {
        eeprom_read_block(&rgb_matrix_config, EECONFIG_RGB_MATRIX, sizeof(rgb_matrix_config));
        rgb_matrix_mode_noeeprom(rgb_matrix_config.mode);
        return;
    }

    int32_t num2 = (27/2) + num - 2;
    int32_t num1 = 27 - num2;
#ifdef CONSOLE_ENABLE
    uprintf("num: %u\n", num);
    uprintf("num1: %u\n", num1);
    uprintf("num2: %u\n", num2);
#endif
    rgb_matrix_set_color(num1, rgb.r, rgb.g, rgb.b);
    rgb_matrix_set_color(num2, rgb.r, rgb.g, rgb.b);
}

static bool startup_animation_dots(effect_params_t* params) {
    startup_animation_setleds(params, true);
    return false;
}
static bool startup_animation_solid(effect_params_t* params) {
    startup_animation_setleds(params, false);
    return false;
}

#endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
