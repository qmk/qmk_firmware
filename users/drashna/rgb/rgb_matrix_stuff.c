// Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "drashna.h"
#include "rgb_matrix.h"
#include "lib/lib8tion/lib8tion.h"
extern led_config_t g_led_config;

static uint32_t hypno_timer;

void rgb_matrix_layer_helper(uint8_t hue, uint8_t sat, uint8_t val, uint8_t mode, uint8_t speed, uint8_t led_type, uint8_t led_min, uint8_t led_max) {
    HSV hsv = {hue, sat, val};
    if (hsv.v > rgb_matrix_get_val()) {
        hsv.v = rgb_matrix_get_val();
    }

    switch (mode) {
        case 1: // breathing
        {
            uint16_t time = scale16by8(g_rgb_timer, speed / 8);
            hsv.v         = scale8(abs8(sin8(time) - 128) * 2, hsv.v);
            RGB rgb       = hsv_to_rgb(hsv);
            for (uint8_t i = 0; i < RGB_MATRIX_LED_COUNT; i++) {
                if (HAS_FLAGS(g_led_config.flags[i], led_type)) {
                    RGB_MATRIX_INDICATOR_SET_COLOR(i, rgb.r, rgb.g, rgb.b);
                }
            }
            break;
        }
        default: // Solid Color
        {
            RGB rgb = hsv_to_rgb(hsv);
            for (uint8_t i = 0; i < RGB_MATRIX_LED_COUNT; i++) {
                if (HAS_FLAGS(g_led_config.flags[i], led_type)) {
                    RGB_MATRIX_INDICATOR_SET_COLOR(i, rgb.r, rgb.g, rgb.b);
                }
            }
            break;
        }
    }
}

void housekeeping_task_rgb_matrix(void) {
#if defined(RGB_MATRIX_FRAMEBUFFER_EFFECTS)
    if (userspace_config.rgb_matrix_idle_anim && rgb_matrix_get_mode() == RGB_MATRIX_TYPING_HEATMAP && sync_timer_elapsed32(hypno_timer) > 15000) {
        rgb_matrix_mode_noeeprom(RGB_MATRIX_REST_MODE);
    }
#endif
}

void keyboard_post_init_rgb_matrix(void) {
#if defined(RGB_MATRIX_FRAMEBUFFER_EFFECTS)
    if (userspace_config.rgb_matrix_idle_anim) {
        rgb_matrix_mode_noeeprom(RGB_MATRIX_REST_MODE);
    }
#endif
    if (userspace_config.rgb_layer_change) {
        rgb_matrix_set_flags(LED_FLAG_UNDERGLOW | LED_FLAG_KEYLIGHT | LED_FLAG_INDICATOR);
    } else {
        rgb_matrix_set_flags(LED_FLAG_ALL);
    }
}

bool process_record_user_rgb_matrix(uint16_t keycode, keyrecord_t *record) {
#if defined(RGB_MATRIX_FRAMEBUFFER_EFFECTS)
    hypno_timer = sync_timer_read32();
    if (userspace_config.rgb_matrix_idle_anim && rgb_matrix_get_mode() == RGB_MATRIX_REST_MODE) {
        rgb_matrix_mode_noeeprom(RGB_MATRIX_TYPING_HEATMAP);
    }
#endif
    switch (keycode) {
        case RGB_IDL: // This allows me to use underglow as layer indication, or as normal
#if defined(RGB_MATRIX_ENABLE) && defined(RGB_MATRIX_FRAMEBUFFER_EFFECTS)
            if (record->event.pressed) {
                userspace_config.rgb_matrix_idle_anim ^= 1;
                dprintf("RGB Matrix Idle Animation [EEPROM]: %u\n", userspace_config.rgb_matrix_idle_anim);
                eeconfig_update_user_config(&userspace_config.raw);
                if (userspace_config.rgb_matrix_idle_anim) {
                    rgb_matrix_mode_noeeprom(RGB_MATRIX_TYPING_HEATMAP);
                }
            }
#endif
            break;
    }
    return true;
}

__attribute__((weak)) bool rgb_matrix_indicators_advanced_keymap(uint8_t led_min, uint8_t led_max) {
    return true;
}
bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    if (!rgb_matrix_indicators_advanced_keymap(led_min, led_max)) {
        return false;
    }

#if defined(RGBLIGHT_ENABLE)
    if (!userspace_config.rgb_layer_change)
#else
    if (userspace_config.rgb_layer_change)
#endif
    {
        switch (get_highest_layer(layer_state & ~((layer_state_t)1 << _MOUSE))) {
            case _GAMEPAD:
                rgb_matrix_layer_helper(HSV_ORANGE, 1, rgb_matrix_config.speed, LED_FLAG_MODIFIER, led_min, led_max);
                break;
            case _DIABLO:
                rgb_matrix_layer_helper(HSV_RED, 1, rgb_matrix_config.speed * 8, LED_FLAG_MODIFIER, led_min, led_max);
                break;
            case _RAISE:
                rgb_matrix_layer_helper(HSV_YELLOW, 1, rgb_matrix_config.speed, LED_FLAG_MODIFIER, led_min, led_max);
                break;
            case _LOWER:
                rgb_matrix_layer_helper(HSV_GREEN, 1, rgb_matrix_config.speed, LED_FLAG_MODIFIER, led_min, led_max);
                break;
            case _ADJUST:
                rgb_matrix_layer_helper(HSV_RED, 1, rgb_matrix_config.speed, LED_FLAG_MODIFIER, led_min, led_max);
                break;
            default:
                if (layer_state_is(_MOUSE)) {
                    rgb_matrix_layer_helper(HSV_PURPLE, 1, rgb_matrix_config.speed, LED_FLAG_MODIFIER, led_min, led_max);
                } else {
                    switch (get_highest_layer(default_layer_state)) {
                        case _DEFAULT_LAYER_1:
                            rgb_matrix_layer_helper(DEFAULT_LAYER_1_HSV, 0, rgb_matrix_config.speed, LED_FLAG_MODIFIER, led_min, led_max);
                            break;
                        case _DEFAULT_LAYER_2:
                            rgb_matrix_layer_helper(DEFAULT_LAYER_2_HSV, 0, rgb_matrix_config.speed, LED_FLAG_MODIFIER, led_min, led_max);
                            break;
                        case _DEFAULT_LAYER_3:
                            rgb_matrix_layer_helper(DEFAULT_LAYER_3_HSV, 0, rgb_matrix_config.speed, LED_FLAG_MODIFIER, led_min, led_max);
                            break;
                        case _DEFAULT_LAYER_4:
                            rgb_matrix_layer_helper(DEFAULT_LAYER_4_HSV, 0, rgb_matrix_config.speed, LED_FLAG_MODIFIER, led_min, led_max);
                            break;
                    }
                }
                break;
        }
    }
    return false;
}

__attribute__((weak)) bool rgb_matrix_indicators_keymap(void) {
    return true;
}
bool rgb_matrix_indicators_user(void) {
    return rgb_matrix_indicators_keymap();
}


//----------------------------------------------------------
// RGB Matrix naming
#include <rgb_matrix.h>

#if defined(RGB_MATRIX_EFFECT)
#    undef RGB_MATRIX_EFFECT
#endif // defined(RGB_MATRIX_EFFECT)

#define RGB_MATRIX_EFFECT(x) RGB_MATRIX_EFFECT_##x,
enum {
    RGB_MATRIX_EFFECT_NONE,
#include "rgb_matrix_effects.inc"
#undef RGB_MATRIX_EFFECT
#ifdef RGB_MATRIX_CUSTOM_KB
#    include "rgb_matrix_kb.inc"
#endif
#ifdef RGB_MATRIX_CUSTOM_USER
#    include "rgb_matrix_user.inc"
#endif
};

#define RGB_MATRIX_EFFECT(x)    \
    case RGB_MATRIX_EFFECT_##x: \
        return #x;
const char* rgb_matrix_name(uint8_t effect) {
    switch (effect) {
        case RGB_MATRIX_EFFECT_NONE:
            return "NONE";
#include "rgb_matrix_effects.inc"
#undef RGB_MATRIX_EFFECT
#ifdef RGB_MATRIX_CUSTOM_KB
#    include "rgb_matrix_kb.inc"
#endif
#ifdef RGB_MATRIX_CUSTOM_USER
#    include "rgb_matrix_user.inc"
#endif
        default:
            return "UNKNOWN";
    }
}
