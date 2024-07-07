#include "action_layer.h"
#include "keymap_common.h"
#include "rgb_matrix.h"
#include "rgb_matrix_types.h"

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    uint8_t layer = get_highest_layer(layer_state);
    switch (layer) {
        case 0:
        case 2:
            break;
        default: {
            for (uint8_t row = 0; row < MATRIX_ROWS; ++row) {
                for (uint8_t col = 0; col < MATRIX_COLS; ++col) {
                    uint8_t index = g_led_config.matrix_co[row][col];

                    if (index >= led_min && index <= led_max && index != NO_LED && keymap_key_to_keycode(layer, (keypos_t){col, row}) > KC_TRNS) {
                        rgb_matrix_set_color(index, 225, 65, 140);
                    }
                }
            }
        }
    }

    return true;
}

// TODO: implement custom colors based on custom codes
// - debounce groups (green press, red release)
// - sleep group - cyan / lightblue
// - logo led - white
// - side led - yellow
// - rgb matrix keycodes - purple
// - wireless modes - blue
// - other utilitary keys (reset, rgb test, etc) - off state (Black)?
