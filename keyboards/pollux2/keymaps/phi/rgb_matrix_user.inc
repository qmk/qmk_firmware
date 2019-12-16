RGB_MATRIX_EFFECT(my_effect)

#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

#include "layer_numbers.h"

#define LED_LAYOUT(                                             \
    L00, L01, L02, L03, L04, L05, R00, R01, R02, R03, R04, R05, \
    L10, L11, L12, L13, L14, L15, R10, R11, R12, R13, R14, R15, \
    L20, L21, L22, L23, L24, L25, R20, R21, R22, R23, R24, R25, \
    /*               */ L34, L35, R30, R31                      \
) {                                                             \
    L00, L01, L02, L03, L04, L05,                               \
    L10, L11, L12, L13, L14, L15,                               \
    L20, L21, L22, L23, L24, L25,                               \
    L34, L35,                                                   \
    ___, ___, ___, ___, ___, ___,                               \
    R05, R04, R03, R02, R01, R00,                               \
    R15, R14, R13, R12, R11, R10,                               \
    R25, R24, R23, R22, R21, R20,                               \
    R31, R30,                                                   \
    ___, ___, ___, ___, ___, ___                                \
}

enum led_type_flags {
    XXX,
    ___,
    FN2,
    MOD,
    FN1
};

uint8_t layer_image [][DRIVER_LED_TOTAL] = {
    [BASE] = LED_LAYOUT(
        ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___,
        MOD, ___, ___, MOD, MOD, ___, ___, ___, ___, ___, ___, ___,
        MOD, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___,
        /*               */ MOD, FN1, FN1, MOD
    ),
    [RAISE] = LED_LAYOUT(
        FN2, ___, ___, ___, ___, ___, ___, ___, ___, ___, ___, FN1,
        XXX, XXX, XXX, FN1, FN1, FN1, FN1, FN1, FN1, XXX, FN1, FN1,
        XXX, ___, ___, ___, ___, ___, ___, ___, ___, XXX, XXX, FN1,
        /*               */ MOD, MOD, FN2, MOD
    ),
    [FUNCTION] = LED_LAYOUT(
        XXX, ___, ___, ___, ___, ___, ___, ___, ___, ___, FN2, XXX,
        XXX, FN1, FN1, FN1, FN1, MOD, XXX, XXX, XXX, XXX, XXX, XXX,
        XXX, FN1, FN1, FN1, FN1, XXX, XXX, XXX, XXX, XXX, XXX, XXX,
        /*               */ FN2, MOD, XXX, XXX
    ),
    [MOUSE] = LED_LAYOUT(
        XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX,
        XXX, XXX, MOD, MOD, MOD, XXX, FN1, FN1, FN1, FN1, XXX, XXX,
        XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX,
        /*               */ FN1, FN1, XXX, XXX
    ),
    [WHEEL] = LED_LAYOUT(
        XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX,
        XXX, XXX, MOD, MOD, MOD, XXX, FN1, FN1, FN1, FN1, XXX, XXX,
        XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX,
        /*               */ XXX, XXX, XXX, XXX
    ),
    [CURSOR] = LED_LAYOUT(
        XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX,
        XXX, XXX, XXX, MOD, MOD, XXX, FN1, FN1, FN1, FN1, XXX, XXX,
        XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX,
        /*               */ XXX, XXX, XXX, XXX
    ),
    [CURSOR_ACCL] = LED_LAYOUT(
        XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX,
        XXX, XXX, XXX, MOD, MOD, XXX, FN1, FN1, FN1, FN1, XXX, XXX,
        XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX,
        /*               */ XXX, XXX, XXX, XXX
    ),
    [MICROWRITER] = LED_LAYOUT(
        XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX,
        XXX, XXX, XXX, XXX, XXX, XXX, XXX, FN1, FN1, FN1, FN1, XXX,
        XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX,
        /*               */ XXX, XXX, FN1, FN2
    ),
};

#define _HSV(H, S, V) (HSV){ .h = H, .s = S, .v = V }
#define _RGB(rgb) rgb.r, rgb.g, rgb.b

static void set_color_internal (uint8_t index, uint8_t color_index) {
    HSV hsv = rgb_matrix_config.hsv;
    /* RGB base_color = hsv_to_rgb(hsv); */
    /* RGB accent1 = hsv_to_rgb(_HSV((hsv.h + 256 * 1 / 4) % 256, hsv.s, hsv.v)); */
    /* RGB accent2 = hsv_to_rgb(_HSV((hsv.h + 256 * 2 / 4) % 256, hsv.s, hsv.v)); */
    /* RGB accent3 = hsv_to_rgb(_HSV((hsv.h + 256 * 3 / 4) % 256, hsv.s, hsv.v)); */
    RGB base_color = hsv_to_rgb(_HSV(0, 0, hsv.v));
    RGB accent1 = hsv_to_rgb(_HSV((hsv.h + 256 * 0 / 3) % 256, hsv.s, hsv.v));
    RGB accent2 = hsv_to_rgb(_HSV((hsv.h + 256 * 1 / 3) % 256, hsv.s, hsv.v));
    RGB accent3 = hsv_to_rgb(_HSV((hsv.h + 256 * 2 / 3) % 256, hsv.s, hsv.v));

    switch (color_index) {
      case XXX:
        rgb_matrix_set_color(index, 0x00, 0x00, 0x00);
        break;
      case ___:
        rgb_matrix_set_color(index, _RGB(base_color));
        break;
      case FN1:
        rgb_matrix_set_color(index, _RGB(accent1));
        break;
      case FN2:
        rgb_matrix_set_color(index, _RGB(accent2));
        break;
      case MOD:
        rgb_matrix_set_color(index, _RGB(accent3));
        break;
    }
}

static bool my_effect (effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);
    for (uint8_t i = led_min; i < led_max; i++) {
        if (LAYER_ON(FUNCTION)) {
            set_color_internal(i, layer_image[FUNCTION][i]);
        } else if (LAYER_ON(RAISE)) {
            set_color_internal(i, layer_image[RAISE][i]);
        } else if (LAYER_ON(WHEEL)) {
            set_color_internal(i, layer_image[WHEEL][i]);
        } else if (LAYER_ON(MOUSE)) {
            set_color_internal(i, layer_image[MOUSE][i]);
        } else if (LAYER_ON(CURSOR_ACCL)) {
            set_color_internal(i, layer_image[CURSOR_ACCL][i]);
        } else if (LAYER_ON(CURSOR)) {
            set_color_internal(i, layer_image[CURSOR][i]);
        } else if (LAYER_ON(MICROWRITER)) {
            set_color_internal(i, layer_image[MICROWRITER][i]);
        } else {
            set_color_internal(i, layer_image[0][i]);
        }
    }
    return led_max < DRIVER_LED_TOTAL;
}

#endif
