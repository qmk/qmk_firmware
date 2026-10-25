#include QMK_KEYBOARD_H
#include "layers.h"

#ifdef RGB_MATRIX_ENABLE

bool rgb_matrix_indicators_user(void) {
    switch (get_highest_layer(layer_state)) {
        case _BASE:
            rgb_matrix_set_color_all(0, 0, 0);
            break;
        default:
            rgb_matrix_set_color_all(255, 255, 255);
            break;
    }
    return false;
}

#endif
