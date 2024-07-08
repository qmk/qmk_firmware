#include "action_layer.h"
#include "color.h"
#include "keycodes.h"
#include "keymap_common.h"
#include "rgb_matrix.h"
#include "rgb_matrix_types.h"
#include "ansi.h"

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

                    if (index >= led_min && index <= led_max && index != NO_LED) {
                        int keycode = keymap_key_to_keycode(layer, (keypos_t){col, row});

                        if (keycode >= LOGO_VAI && keycode <= LOGO_SPD) {
                            rgb_matrix_set_color(index, RGB_WHITE);
                        } else if (keycode >= SIDE_VAI && keycode <= SIDE_SPD) {
                            rgb_matrix_set_color(index, RGB_YELLOW);
                        } else if (keycode >= DEBOUNCE_PRESS_INC && keycode <= DEBOUNCE_PRESS_SHOW) {
                            rgb_matrix_set_color(index, 0, 255, 0);
                        } else if (keycode >= DEBOUNCE_RELEASE_INC && keycode <= DEBOUNCE_RELEASE_SHOW) {
                            rgb_matrix_set_color(index, 255, 0, 0);
                        } else if (keycode == SLEEP_MODE || keycode == TOG_USB_SLP || keycode == DEEP_SLEEP_TOGGLE || (keycode >= SLEEP_TIMEOUT_INC && keycode <= SLEEP_TIMEOUT_SHOW)) {
                           rgb_matrix_set_color(index, RGB_CYAN);
                        } else if (keycode >= LNK_USB && keycode <= LNK_BLE3) {
                           rgb_matrix_set_color(index, RGB_BLUE);
                        } else if (IS_RGB_KEYCODE(keycode)) {
                           rgb_matrix_set_color(index, RGB_PURPLE);
                        } else if (keycode > KC_TRNS) {
                            rgb_matrix_set_color(index, 225, 65, 140);
                        }
                    }
                }
            }
        }
    }

    return true;
}

// TODO: implement custom colors based on custom codes
// + debounce groups (green press, red release)
// + sleep group - cyan / lightblue
// + logo led - white
// + side led - yellow
// + wireless modes - blue
// + other utilitary keys (reset, rgb test, etc) - current pink-ish
