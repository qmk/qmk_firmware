#include "bocaj.h"

#include "lib/lib8tion/lib8tion.h"
extern led_config_t g_led_config;

static uint32_t hypno_timer;
#if defined(SPLIT_KEYBOARD) || defined(KEYBOARD_ergodox_ez) || defined(KEYBOARD_crkbd)
#    define RGB_MATRIX_REST_MODE RGB_MATRIX_CYCLE_OUT_IN_DUAL
#else
#    define RGB_MATRIX_REST_MODE RGB_MATRIX_CYCLE_OUT_IN
#endif

void rgb_matrix_set_color_row(uint8_t row, uint8_t red, uint8_t green, uint8_t blue) {
#ifdef KEYBOARD_planck_ez
    if (row > 2) {
        row = 0;
    }
    uint8_t row_multiplier = row * 12;

    rgb_matrix_set_color(1 + row_multiplier, red, green, blue);
    rgb_matrix_set_color(2 + row_multiplier, red, green, blue);
    rgb_matrix_set_color(3 + row_multiplier, red, green, blue);
    rgb_matrix_set_color(4 + row_multiplier, red, green, blue);
    rgb_matrix_set_color(5 + row_multiplier, red, green, blue);
    rgb_matrix_set_color(6 + row_multiplier, red, green, blue);
    rgb_matrix_set_color(7 + row_multiplier, red, green, blue);
    rgb_matrix_set_color(8 + row_multiplier, red, green, blue);
    rgb_matrix_set_color(9 + row_multiplier, red, green, blue);
    rgb_matrix_set_color(10 + row_multiplier, red, green, blue);
#endif
}

void rgb_matrix_layer_helper(uint8_t hue, uint8_t sat, uint8_t val, uint8_t mode, uint8_t speed, uint8_t led_type) {
    HSV hsv = {hue, sat, val};
    if (hsv.v > rgb_matrix_get_val()) {
        hsv.v = rgb_matrix_get_val();
    }

    switch (mode) {
        case 1:  // breathing
        {
            uint16_t time = scale16by8(g_rgb_timer, speed / 8);
            hsv.v         = scale8(abs8(sin8(time) - 128) * 2, hsv.v);
            RGB rgb       = hsv_to_rgb(hsv);
            for (uint8_t i = 0; i < DRIVER_LED_TOTAL; i++) {
                if (HAS_FLAGS(g_led_config.flags[i], led_type)) {
                    rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
                }
            }
            break;
        }
        default:  // Solid Color
        {
            RGB rgb = hsv_to_rgb(hsv);
            for (uint8_t i = 0; i < DRIVER_LED_TOTAL; i++) {
                if (HAS_FLAGS(g_led_config.flags[i], led_type)) {
                    rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
                }
            }
            break;
        }
    }
}

__attribute__((weak)) void rgb_matrix_indicator_keymap(void) {}

void matrix_scan_rgb_matrix(void) {
#if defined(RGB_MATRIX_FRAMEBUFFER_EFFECTS)
    if (userspace_config.rgb_matrix_idle_anim && rgb_matrix_get_mode() == RGB_MATRIX_TYPING_HEATMAP && timer_elapsed32(hypno_timer) > 15000) {
        rgb_matrix_mode_noeeprom(RGB_MATRIX_REST_MODE);
    }
#endif
    rgb_matrix_indicator_keymap();
}

void keyboard_post_init_rgb_matrix(void) {
#if defined(RGB_MATRIX_FRAMEBUFFER_EFFECTS)
    if (userspace_config.rgb_matrix_idle_anim) {
        rgb_matrix_mode_noeeprom(RGB_MATRIX_REST_MODE);
    }
#endif
}

bool process_record_user_rgb_matrix(uint16_t keycode, keyrecord_t *record) {
#if defined(RGB_MATRIX_FRAMEBUFFER_EFFECTS)
    hypno_timer = timer_read32();
    if (userspace_config.rgb_matrix_idle_anim && rgb_matrix_get_mode() == RGB_MATRIX_REST_MODE) {
        rgb_matrix_mode_noeeprom(RGB_MATRIX_TYPING_HEATMAP);
    }
#endif
    switch (keycode) {
        case RGB_IDL:
#if defined(RGB_MATRIX_ENABLE) && defined(RGB_MATRIX_FRAMEBUFFER_EFFECTS)
            if (record->event.pressed) {
                userspace_config.rgb_matrix_idle_anim ^= 1;
                dprintf("RGB Matrix Idle Animation [EEPROM]: %u\n", userspace_config.rgb_matrix_idle_anim);
                eeconfig_update_user(userspace_config.raw);
                if (userspace_config.rgb_matrix_idle_anim) {
                    rgb_matrix_mode_noeeprom(RGB_MATRIX_TYPING_HEATMAP);
                }
            }
#endif
            break;
    }
    return true;
}
