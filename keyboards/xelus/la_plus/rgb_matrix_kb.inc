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

// e.g: A simple effect, self-contained within a single method
static void startup_animation_setleds(effect_params_t* params, bool off) {
    uint8_t factor = 7;
    HSV      hsv  = rgb_matrix_config.hsv;
    RGB rgb       = rgb_matrix_hsv_to_rgb(hsv);
    if (off) {
        rgb_matrix_set_color_all(0, 0, 0);
    }

    switch ((g_rgb_timer & (0b11111 << factor)) >> factor) {
        case 0:
        case 1:
        case 2:
        case 3: {
            rgb_matrix_set_color(13, rgb.r, rgb.g, rgb.b);
            rgb_matrix_set_color(14, rgb.r, rgb.g, rgb.b);
            break;
        }
        case 4: {
            rgb_matrix_set_color(12, rgb.r, rgb.g, rgb.b);
            rgb_matrix_set_color(15, rgb.r, rgb.g, rgb.b);
            break;
        }
        case 5: {
            rgb_matrix_set_color(11, rgb.r, rgb.g, rgb.b);
            rgb_matrix_set_color(16, rgb.r, rgb.g, rgb.b);
            break;
        }
        case 6: {
            rgb_matrix_set_color(10, rgb.r, rgb.g, rgb.b);
            rgb_matrix_set_color(17, rgb.r, rgb.g, rgb.b);
            break;
        }
        case 7: {
            rgb_matrix_set_color(9, rgb.r, rgb.g, rgb.b);
            rgb_matrix_set_color(18, rgb.r, rgb.g, rgb.b);
            break;
        }
        case 8: {
            rgb_matrix_set_color(8, rgb.r, rgb.g, rgb.b);
            rgb_matrix_set_color(19, rgb.r, rgb.g, rgb.b);
            break;
        }
        case 9: {
            rgb_matrix_set_color(7, rgb.r, rgb.g, rgb.b);
            rgb_matrix_set_color(20, rgb.r, rgb.g, rgb.b);
            break;
        }
        case 10: {
            rgb_matrix_set_color(6, rgb.r, rgb.g, rgb.b);
            rgb_matrix_set_color(21, rgb.r, rgb.g, rgb.b);
            break;
        }
        case 11: {
            rgb_matrix_set_color(5, rgb.r, rgb.g, rgb.b);
            rgb_matrix_set_color(22, rgb.r, rgb.g, rgb.b);
            break;
        }
        case 12: {
            rgb_matrix_set_color(4, rgb.r, rgb.g, rgb.b);
            rgb_matrix_set_color(23, rgb.r, rgb.g, rgb.b);
            break;
        }
        case 13: {
            rgb_matrix_set_color(3, rgb.r, rgb.g, rgb.b);
            rgb_matrix_set_color(24, rgb.r, rgb.g, rgb.b);
            break;
        }
        case 14: {
            rgb_matrix_set_color(2, rgb.r, rgb.g, rgb.b);
            rgb_matrix_set_color(25, rgb.r, rgb.g, rgb.b);
            break;
        }
        case 15: {
            rgb_matrix_set_color(1, rgb.r, rgb.g, rgb.b);
            rgb_matrix_set_color(26, rgb.r, rgb.g, rgb.b);
            break;
        }
        case 16: {
            rgb_matrix_set_color(0, rgb.r, rgb.g, rgb.b);
            rgb_matrix_set_color(27, rgb.r, rgb.g, rgb.b);
            break;
        }
        case 17: {
            for (int i = 0; i < 28; i++) {
                rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
            }
            break;
        }
        case 18:
        case 19: {
            for (int i = 0; i < 28; i++) {
                rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
            }
            break;
        }
        case 20: {
            eeprom_read_block(&rgb_matrix_config, EECONFIG_RGB_MATRIX, sizeof(rgb_matrix_config));
            rgb_matrix_mode_noeeprom(rgb_matrix_config.mode);
            break;
        }
    }
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
