#include "brandonschlack.h"
#include "rgb_bs.h"

#if defined(RGBLIGHT_ENABLE)
extern rgblight_config_t rgblight_config;
#elif defined(RGB_MATRIX_ENABLE)
extern rgb_config_t rgb_matrix_config;
extern bool g_suspend_state;
extern led_config_t g_led_config;
#endif

void keyboard_post_init_rgb(void) {
    layer_state_set_user(layer_state);
#if defined(RGBLIGHT_ENABLE)
    rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
#elif defined(RGB_MATRIX_ENABLE)
    rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
#endif
}

#ifdef RGB_MATRIX_ENABLE
void rgb_matrix_layer_helper (uint8_t red, uint8_t green, uint8_t blue, uint8_t led_type) {
    for (int i = 0; i < DRIVER_LED_TOTAL; i++) {
        if (!HAS_ANY_FLAGS(g_led_config.flags[i], led_type)) {
            rgb_matrix_set_color( i, red, green, blue );
        }
    }
}

void rgb_matrix_cycle_flag (void) {
    switch (rgb_matrix_get_flags()) {
        case LED_FLAG_ALL:
            rgb_matrix_set_flags(LED_FLAG_ALL_KEYS);
            rgb_matrix_set_color_all(0, 0, 0);
            break;
        case LED_FLAG_ALL_KEYS:
            rgb_matrix_set_flags(LED_FLAG_UNDERGLOW);
            rgb_matrix_set_color_all(0, 0, 0);
            break;
        case LED_FLAG_UNDERGLOW:
            rgb_matrix_set_flags(LED_FLAG_NONE);
            rgb_matrix_set_color_all(0, 0, 0);
            break;
        default:
            rgb_matrix_set_flags(LED_FLAG_ALL);
            rgb_matrix_enable_noeeprom();
            break;
    }
}
#endif

void rgb_layer_helper(uint8_t hue, uint8_t sat, uint8_t val) {
#if defined(RGBLIGHT_ENABLE) || defined(RGB_MATRIX_ENABLE)
    rgblight_sethsv_noeeprom(hue, sat, val);
#ifdef RGB_MATRIX_ENABLE
    rgb_matrix_layer_helper(0, 0, 0, rgb_matrix_get_flags());
#endif
}
#endif

layer_state_t layer_state_set_rgb(layer_state_t state) {
    #if defined(RGBLIGHT_ENABLE) || defined(RGB_MATRIX_ENABLE)
    switch (biton32(state)) {
#ifndef IS_MACROPAD
        case _MACFN:
            rgb_layer_helper(HSV_PINK);
            break;
        case _WINFN:
            rgb_layer_helper(HSV_CYAN);
            break;
#else
        case _REEDER:
            rgb_layer_helper(HSV_PINK);
            break;
        case _MEDIA:
            rgb_layer_helper(HSV_BLUE);
            break;
        case _KEYPAD:
            rgb_layer_helper(HSV_CYAN);
            break;
#endif
        case _MAGIC:
            rgb_layer_helper(HSV_GREEN);
            break;
        default:
            switch (biton32(default_layer_state)) {
    #ifndef IS_MACROPAD
                case _MAC:
                    rgb_layer_helper(HSV_PURPLE);
                    break;
                case _WIN:
                    rgb_layer_helper(HSV_BLUE);
                    break;
    #else
                case _NAVI:
                    rgb_layer_helper(HSV_PURPLE);
                    break;
    #endif
            }
            break;
    }
#endif // RGBLIGHT_ENABLE
    return state;
}
