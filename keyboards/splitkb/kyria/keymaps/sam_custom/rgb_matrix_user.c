#include QMK_KEYBOARD_H
#include "rgb_matrix_user.h"
#include "keymap.h"
#include "capsword.h"
#include "transactions.h"
#include "print.h"

// 62 - 12 underglow (unused), 50 keys
keypos_t led_index_key_position[RGB_MATRIX_LED_COUNT];

// https://github.com/LooLzzz/qmk_firmware/blob/8c28582b37aa9d0d74cacc2dc3a6b8643679170f/keyboards/keychron/q3/ansi_encoder/keymaps/loolzzz/rgb_matrix/rgb_matrix_user.c
// Initialize RGB matrix; invert the mapping of g_led_config.matrix_co,
// so instead of a mapping from key position to led index, we now create
// led index to key position.
void rgb_matrix_init_user() {
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        for (uint8_t col = 0; col < MATRIX_COLS; col++) {
            uint8_t led_index = g_led_config.matrix_co[row][col];
            if (led_index != NO_LED) {
                led_index_key_position[led_index] = (keypos_t){.row = row, .col = col};
            }
        }
    }
}

void rgb_matrix_set_color_by_keycode(
    uint8_t led_min,
    uint8_t led_max,
    uint8_t layer,
    bool (*is_keycode)(uint16_t),
    uint8_t red,
    uint8_t green,
    uint8_t blue
) {
    for (uint8_t i = led_min; i < led_max; i++) {
        uint16_t keycode = keymap_key_to_keycode(layer, led_index_key_position[i]);
        if ((*is_keycode)(keycode))
            rgb_matrix_set_color(i, red, green, blue);
    }
}

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    uint8_t current_layer = get_highest_layer(layer_state);

    switch (current_layer) {
        case _QWERTY:
            for (uint8_t i = led_min; i < led_max; i++) {
                // add 6 to account for the 6 underglow LEDs per half that we aren't using
                uint16_t keycode = keymap_key_to_keycode(current_layer, led_index_key_position[i+6]);
                if (is_capsword_enabled) {
                    if (keycode == OSM(MOD_LSFT)) {
                        rgb_matrix_set_color(i, 169, 32, 0); // burnt orange
                    }
                };

            };
            break;
        case _SYMBOL:
            for (uint8_t i = led_min; i < led_max; i++) {
                // add 6 to account for the 6 underglow LEDs per half that we aren't using
                uint16_t keycode = keymap_key_to_keycode(current_layer, led_index_key_position[i+6]);
                switch (keycode) {
                    case TO(0):
                        rgb_matrix_set_color(i, RGB_PURPLE);
                        break;
                    default:
                        rgb_matrix_set_color(i, RGB_OFF);
                        break;
                }
            }
            break;
        case _NUMPAD:
            for (uint8_t i = led_min; i < led_max; i++) {
                // add 6 to account for the 6 underglow LEDs per half that we aren't using
                uint16_t keycode = keymap_key_to_keycode(current_layer, led_index_key_position[i+6]);
                switch (keycode) {
                    case KC_1:
                    case KC_2:
                    case KC_3:
                    case KC_4:
                    case KC_5:
                    case KC_6:
                    case KC_7:
                    case KC_8:
                    case KC_9:
                    case KC_0:
                        rgb_matrix_set_color(i, 169, 32, 0); // burnt orange
                        break;
                    case TO(0):
                        rgb_matrix_set_color(i, RGB_PURPLE);
                        break;
                    case KC_PSCR:
                        rgb_matrix_set_color(i, RGB_RED);
                        break;
                    default:
                        rgb_matrix_set_color(i, RGB_OFF);
                        break;
                }
            }
            break;
        case _WINDOW:
            for (uint8_t i = led_min; i < led_max; i++) {
                // add 6 to account for the 6 underglow LEDs per half that we aren't using
                uint16_t keycode = keymap_key_to_keycode(current_layer, led_index_key_position[i+6]);
                switch (keycode) {
                    case WMGMT_MONITOR_1:
                    case WMGMT_MONITOR_2:
                    case WMGMT_MONITOR_3:
                    case WMGMT_MONITOR_4:
                        rgb_matrix_set_color(i, RGB_RED);
                        break;
                    case WMGMT_LEFT_50:
                    case WMGMT_DOWN_50:
                    case WMGMT_UP_50:
                    case WMGMT_RIGHT_50:
                        rgb_matrix_set_color(i, RGB_ORANGE);
                        break;
                    case WMGMT_TOPLEFT:
                    case WMGMT_TOPRIGHT:
                    case WMGMT_BOTTOMLEFT:
                    case WMGMT_BOTTOMRIGHT:
                        rgb_matrix_set_color(i, RGB_YELLOW);
                        break;
                    case WMGMT_LEFT_33:
                    case WMGMT_HCENTER_33:
                    case WMGMT_RIGHT_33:
                        rgb_matrix_set_color(i, RGB_CYAN);
                        break;
                    case WMGMT_TOP_33:
                    case WMGMT_VCENTER_33:
                    case WMGMT_BOTTOM_33:
                        rgb_matrix_set_color(i, RGB_BLUE);
                        break;
                    case WMGMT_LEFT_66:
                    case WMGMT_RIGHT_66:
                        rgb_matrix_set_color(i, RGB_MAGENTA);
                        break;
                    case WMGMT_FULLSCREEN:
                        rgb_matrix_set_color(i, RGB_ORANGE);
                        break;
                    case WMGMT_CENTER:
                    case WMGMT_NEXT_WALLPAPER:
                        rgb_matrix_set_color(i, RGB_GREEN);
                        break;
                    case WMGMT_NEXT_MONITOR:
                    case WMGMT_PREV_MONITOR:
                        rgb_matrix_set_color(i, RGB_TURQUOISE);
                        break;
                    default:
                        rgb_matrix_set_color(i, RGB_OFF);
                        break;
                }
            }
            break;
        default:
            break;
    }
    return false;
}
