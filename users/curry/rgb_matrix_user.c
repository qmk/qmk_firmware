#include "curry.h"
#include "rgb_matrix_user.h"
#include "lib/lib8tion/lib8tion.h"

static uint32_t     hypno_timer;
extern led_config_t g_led_config;

#define RGB_MATRIX_REST_MODE RGB_MATRIX_CYCLE_OUT_IN_DUAL

void suspend_power_down_keymap(void) { rgb_matrix_set_suspend_state(true); }

void suspend_wakeup_init_keymap(void) { rgb_matrix_set_suspend_state(false); }

void check_default_layer(uint8_t mode, uint8_t type) {
    switch (get_highest_layer(default_layer_state)) {
#if defined(ENABLE_QWERTY)
        case _QWERTY:
            rgb_matrix_layer_helper(HSV_CYAN, mode, rgb_matrix_config.speed, type);
            break;
#endif
#if defined(ENABLE_COLEMAK)
        case _COLEMAK:
            rgb_matrix_layer_helper(HSV_MAGENTA, mode, rgb_matrix_config.speed, type);
            break;
#endif
#if defined(ENABLE_DVORAK)
        case _DVORAK:
            rgb_matrix_layer_helper(HSV_SPRINGGREEN, mode, rgb_matrix_config.speed, type);
            break;
#endif
#if defined(ENABLE_WORKMAN)
        case _WORKMAN:
            rgb_matrix_layer_helper(HSV_GOLDENROD, mode, rgb_matrix_config.speed, type);
            break;
#endif
    }
}

void rgb_matrix_indicators_user(void) {
    if (userspace_config.rgb_layer_change && rgb_matrix_config.enable) {
        switch (get_highest_layer(layer_state)) {
            case _RAISE:
                rgb_matrix_layer_helper(HSV_YELLOW, 0, rgb_matrix_config.speed, LED_FLAG_UNDERGLOW);
                break;
            case _LOWER:
                rgb_matrix_layer_helper(HSV_GREEN, 0, rgb_matrix_config.speed, LED_FLAG_UNDERGLOW);
                break;
            case _ADJUST:
                rgb_matrix_layer_helper(HSV_RED, 0, rgb_matrix_config.speed, LED_FLAG_UNDERGLOW);
                break;
            default: {
                check_default_layer(IS_LAYER_ON(_MODS), LED_FLAG_UNDERGLOW);
                break;
            }
        }
        check_default_layer(0, LED_FLAG_MODIFIER);
    }
}

bool process_record_user_rgb(uint16_t keycode, keyrecord_t *record) {
    uint16_t temp_keycode = keycode;
    // Filter out the actual keycode from MT and LT keys.
    if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) || (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX)) {
        temp_keycode &= 0xFF;
    }

    hypno_timer = timer_read32();
    if (userspace_config.rgb_matrix_idle_anim && rgb_matrix_get_mode() == RGB_MATRIX_REST_MODE) {
        rgb_matrix_mode_noeeprom(RGB_MATRIX_TYPING_HEATMAP);
    }

    switch (temp_keycode) {
        case KC_RGB_T:  // This allows me to use underglow as layer indication, or as normal
            if (record->event.pressed) {
                userspace_config.rgb_layer_change ^= 1;
                dprintf("rgblight layer change [EEPROM]: %u\n", userspace_config.rgb_layer_change);
                eeconfig_update_user(userspace_config.raw);
                if (userspace_config.rgb_layer_change) {
                    layer_state_set(layer_state);  // This is needed to immediately set the layer color (looks better)
                }
            }
            break;
        case RGB_IDL:  // This allows me to use underglow as layer indication, or as normal
            if (record->event.pressed) {
                userspace_config.rgb_matrix_idle_anim ^= 1;
                dprintf("RGB Matrix Idle Animation [EEPROM]: %u\n", userspace_config.rgb_matrix_idle_anim);
                eeconfig_update_user(userspace_config.raw);
                if (userspace_config.rgb_matrix_idle_anim) {
                    rgb_matrix_mode_noeeprom(RGB_MATRIX_TYPING_HEATMAP);
                }
            }
            break;
        case RGB_MODE_FORWARD ... RGB_MODE_GRADIENT:  // quantum_keycodes.h L400 for definitions
            if (record->event.pressed) {
                bool is_eeprom_updated = false;
                if (userspace_config.rgb_matrix_idle_anim) {
                    userspace_config.rgb_matrix_idle_anim = false;
                    dprintf("RGB Matrix Idle Animation [EEPROM]: %u\n", userspace_config.rgb_matrix_idle_anim);
                    is_eeprom_updated = true;
                }
                if (is_eeprom_updated) {
                    eeconfig_update_user(userspace_config.raw);
                }
            }
            break;
    }
    return true;
}

void keyboard_post_init_rgb(void) {
    if (userspace_config.rgb_matrix_idle_anim) {
        rgb_matrix_mode_noeeprom(RGB_MATRIX_REST_MODE);
    }
}

void matrix_scan_rgb(void) {
    if (userspace_config.rgb_matrix_idle_anim && rgb_matrix_get_mode() == RGB_MATRIX_TYPING_HEATMAP && timer_elapsed32(hypno_timer) > 15000) {
        rgb_matrix_mode_noeeprom(RGB_MATRIX_REST_MODE);
    }
}

void rgb_matrix_layer_helper(uint8_t hue, uint8_t sat, uint8_t val, uint8_t mode, uint8_t speed, uint8_t led_type) {
    HSV hsv = {hue, sat, val};
    if (hsv.v > rgb_matrix_config.hsv.v) {
        hsv.v = rgb_matrix_config.hsv.v;
    }

    switch (mode) {
        case 1:  // breathing
        {
            uint16_t time = scale16by8(RGBLED_NUM, speed / 8);
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
