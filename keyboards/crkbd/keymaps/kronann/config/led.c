#include QMK_KEYBOARD_H
#include "layers.h"

#ifdef RGB_MATRIX_ENABLE

bool rgb_matrix_indicators_user(void) {
    switch (get_highest_layer(layer_state)) {
        case _LOWER:
            rgb_matrix_set_color_all(0, 204, 0);
            break;
        case _RAISE:
            rgb_matrix_set_color_all(102, 178, 255);
            break;
        case _ADJUST:
            rgb_matrix_set_color_all(255, 0, 0);
            break;
        default:
            rgb_matrix_set_color_all(0, 0, 0);
            break;
    }
    return false;
}

#endif
