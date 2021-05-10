RGB_MATRIX_EFFECT(quick17_rgbm_effect)

#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

#include "layer_numbers.h"

#define LED_LAYOUT(
    L00, L01, L02, L03, L04, L05,\
    L10, L11, L12, L13, L14, L15,\
    L20, L21, L22, L23, L24, L25 \
) {
    L00, L01, L02, L03, L04, L05,\
    L10, L11, L12, L13, L14, L15,\
    L20, L21, L22, L23, L24, L25 \
}

enum lighting_types {
    BOUT,
    _____,
    INDC1,
    INDC2,
    INDC3,
    INDC4,
    INDC5
}


const uint16_t rgb_keymaps[][DRIVER_LED_TOTAL] = {
    [_CONTROL] = LED_LAYOUT(
        _____, INDC2, INDC1, INDC2, INDC3, INDC4,
        _____, INDC1, INDC1, INDC1, INDC3, INDC4,
        _____, _____, _____, _____, _____, _____
    ),
    [_EDIT1] = LED_LAYOUT(
        _____, _____, _____, _____, _____, _____,
        _____, _____, _____, _____, _____, INDC1,
        _____, _____, _____, _____, INDC2, INDC1
    ),
    [_EDIT2] = LED_LAYOUT(
        _____, _____, _____, _____, _____, _____,
        _____, _____, _____, _____, _____, INDC1,
        _____, INDC4, _____, INDC3, IND2,  BOUT
    ),
    [_FN] = LED_LAYOUT(
        _____, _____, BOUT,  INDC5, INDC4, INDC4,
        _____, _____, BOUT,  INDC5, INDC4, INDC4,
        INDC2, INDC2, BOUT,  BOUT,  BOUT,  INDC4
    )
}

static void led_color_set (uint8_t index, uint8_t color_patterns) {
    rgb_matrix_get_hsv()//todo: get current hsv
    switch(color_patterns){
        case BOUT:
            rgb_matrix_set_color(index, 0x00, 0x00, 0x00);
            break;
        case _____;
            rgb_matrix_set_color(index)//todo: set to slight different color
    }
}






#endif