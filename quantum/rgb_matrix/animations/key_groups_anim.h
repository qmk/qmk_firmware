#ifdef ENABLE_RGB_MATRIX_KEY_GROUPS
RGB_MATRIX_EFFECT(KEY_GROUPS)
#    ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS
#include "keymap_common.h"
#include "keycode_types.h"

#ifndef RGB_MATRIX_KEY_GROUPS_MIN_VAL
#define RGB_MATRIX_KEY_GROUPS_MIN_VAL 0x60
#endif

#define SET_COLOR(rgb) (rgb_matrix_set_color(index, (rgb).r, (rgb).g, (rgb).b))

// base keys = variable hue as configured with RM_HUE* keycodes,
// modifiers and layer toggles = shifted hues with equal distance around the color wheel.
bool KEY_GROUPS(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);
    uint8_t layer = get_highest_layer(layer_state);
    hsv_t hsv = rgb_matrix_config.hsv;
    // If the animation is active, the user can disable the lights on the default layer by decreasing val to 0,
    // and still get orientation lights on the other layers.
    if (layer > 0 && hsv.v == 0) {
        hsv.v = RGB_MATRIX_KEY_GROUPS_MIN_VAL;
    }
    uint8_t delta_hue = rgb_matrix_config.speed / 4;
    rgb_t rgb_chars = rgb_matrix_hsv_to_rgb(hsv);
    hsv.h += delta_hue;
    rgb_t rgb_other = rgb_matrix_hsv_to_rgb(hsv);
    hsv.h += delta_hue;
    rgb_t rgb_highlight = rgb_matrix_hsv_to_rgb(hsv);
    hsv.h += delta_hue;
    rgb_t rgb_toggles = rgb_matrix_hsv_to_rgb(hsv);

    for (uint8_t row = 0; row < MATRIX_ROWS; ++row) {
        for (uint8_t col = 0; col < MATRIX_COLS; ++col) {
            uint8_t index = g_led_config.matrix_co[row][col];
            if (!HAS_ANY_FLAGS(g_led_config.flags[index], params->flags) || index < led_min || index >= led_max) {
                continue;
            }
            uint16_t keycode = keymap_key_to_keycode(layer, (keypos_t){col,row});
            if (keycode <= KC_TRANSPARENT) {
                rgb_matrix_set_color(index, RGB_BLACK);
                continue;
            }
            if (is_modifier_keycode(keycode) || is_arrow_keycode(keycode) || is_media_keycode(keycode)) {
                SET_COLOR(rgb_highlight);
            } else if (is_character_keycode(keycode)) {
                SET_COLOR(rgb_chars);
            } else if (IS_QK_BASIC(keycode) || IS_QK_MODS(keycode)) {
                SET_COLOR(rgb_other);
            } else {
                SET_COLOR(rgb_toggles);
            }
        }
    }
    return rgb_matrix_check_finished_leds(led_max);
}

#    endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
#endif     // ENABLE_RGB_MATRIX_KEY_GROUPS
