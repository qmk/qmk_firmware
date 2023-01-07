RGB_MATRIX_EFFECT(quick17_rgbm_effect)

#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

#include "quick17_prefs.h"

#define LED_LAYOUT(\
    L00, L01, L02, L03, L04, L05, \
    L10, L11, L12, L13, L14, L15, \
    L20, L21, L22, L23, L24, L25 \
) {\
    L10, L11, L20, L21, L22, L23,\
    L24, L25, L15, L14, L13, L12,\
    L00, L01, L02, L03, L04, L05\
}

enum lighting_types {
    BOUT,
    _____,
    INDC1,
    INDC2,
    INDC3,
    INDC4,
    INDC5,
    JA_EN,
    CAPSL,
    NUM_L
};

const uint8_t rgb_keymaps [][RGB_MATRIX_LED_COUNT] = {
    [_CONTROL] = LED_LAYOUT(
        _____, INDC2, INDC1, INDC2, INDC3, INDC4,
        _____, INDC1, INDC1, INDC1, INDC3, INDC4,
        _____, _____, _____, _____, INDC5, INDC5
    ),
    [_EDIT1] = LED_LAYOUT(
        _____, _____, _____, _____, _____, INDC4,
        _____, _____, _____, _____, _____, INDC1,
        _____, _____, _____, _____, INDC5, INDC1
    ),
    [_EDIT2] = LED_LAYOUT(
        _____, _____, _____, _____, _____, INDC4,
        _____, _____, _____, _____, _____, INDC1,
        _____, INDC5, INDC3, INDC5, INDC5, BOUT
    ),
    [_FN] = LED_LAYOUT(
        _____, JA_EN, BOUT,  INDC3, INDC4, INDC4,
        CAPSL, NUM_L, BOUT,  INDC3, INDC4, INDC4,
        INDC2, INDC2, INDC1, INDC1, INDC5, INDC4
    )
};

static void led_color_set(uint8_t index, uint8_t color_patterns) {
    HSV hsv = rgb_matrix_config.hsv; // 'quantum/color.h'
    RGB rgb_white = hsv_to_rgb(_HSV(  0,   0, hsv.v)); // HSV_WHITE
    RGB rgb_indc1 = hsv_to_rgb(_HSV(128, 255, hsv.v)); // HSV_TEAL
    RGB rgb_indc2 = hsv_to_rgb(_HSV(191, 255, hsv.v)); // HSV_PURPLE
    RGB rgb_indc3 = hsv_to_rgb(_HSV( 64, 255, hsv.v)); // HSV_CHARTREUSE
    RGB rgb_indc4 = hsv_to_rgb(_HSV(106, 255, hsv.v)); // HSV_SPRINGGREEN
    RGB rgb_indc5 = hsv_to_rgb(_HSV(234, 128, hsv.v)); // HSV_PINK
    RGB rgb_indc6 = hsv_to_rgb(_HSV(213, 255, hsv.v)); // HSV_MAGENTA
    RGB rgb_indc_ja =  hsv_to_rgb(_HSV(  0, 255, hsv.v)); // HSV_RED
    RGB rgb_indc_en =  hsv_to_rgb(_HSV( 85, 255, hsv.v)); // HSV_GREEN
    RGB rgb_indc_win = hsv_to_rgb(_HSV(170, 255, hsv.v)); // HSV_BLUE
    switch(color_patterns){
        case BOUT:  rgb_matrix_set_color(index, RGB_BLACK); break;
        case _____: rgb_matrix_set_color(index, _RGB(rgb_white)); break;
        case INDC1: rgb_matrix_set_color(index, _RGB(rgb_indc1)); break;
        case INDC2: rgb_matrix_set_color(index, _RGB(rgb_indc2)); break;
        case INDC3: rgb_matrix_set_color(index, _RGB(rgb_indc3)); break;
        case INDC4: rgb_matrix_set_color(index, _RGB(rgb_indc4)); break;
        case INDC5: rgb_matrix_set_color(index, _RGB(rgb_indc5)); break;
        case JA_EN:
            if (keymap_config.swap_lctl_lgui == false) {
                rgb_matrix_set_color(index, _RGB(rgb_indc_win));
            } else {
                if (input_mode()){
                    rgb_matrix_set_color(index, _RGB(rgb_indc_ja));
                } else {
                    rgb_matrix_set_color(index, _RGB(rgb_indc_en));
                }
            }
            break;
        case CAPSL:
            if (host_keyboard_led_state().caps_lock) {
                rgb_matrix_set_color(index, _RGB(rgb_indc6));
            } else {
                rgb_matrix_set_color(index, _RGB(rgb_white));
            }
            break;
        case NUM_L:
            if (host_keyboard_led_state().num_lock) {
                rgb_matrix_set_color(index, _RGB(rgb_indc6));
            } else {
                rgb_matrix_set_color(index, _RGB(rgb_white));
            }
            break;
    }
}

static bool quick17_rgbm_effect (effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);
    for (uint8_t i = led_min; i < led_max; i++) {
        if (IS_LAYER_ON(_EDIT2)){
            led_color_set(i, rgb_keymaps[_EDIT2][i]);
        } else if (IS_LAYER_ON(_EDIT1)){
            led_color_set(i, rgb_keymaps[_EDIT1][i]);
        } else if (IS_LAYER_ON(_FN)){
            led_color_set(i, rgb_keymaps[_FN][i]);
        } else { // IS_LAYER_ON(_CONTROL)
            led_color_set(i, rgb_keymaps[_CONTROL][i]);
        }
    }
    return rgb_matrix_check_finished_leds(led_max);
}

#endif
