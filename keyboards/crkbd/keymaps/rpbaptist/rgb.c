// Copyright 2023 Your Name (@rpbaptist)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "rpbaptist.h"

uint32_t transport_user_config = 0;

void user_config_sync(uint8_t initiator2target_buffer_size, const void* initiator2target_buffer, uint8_t target2initiator_buffer_size, void* target2initiator_buffer) {
    if (initiator2target_buffer_size == sizeof(transport_user_config)) {
        memcpy(&transport_user_config, initiator2target_buffer, initiator2target_buffer_size);
    }
}

#ifdef OLED_ENABLE
const char* rgb_matrix_anim_oled_text(uint8_t mode) {
    switch (mode) {
        case RGB_MATRIX_TYPING_HEATMAP:
            return PSTR("Heat ");
        case RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS:
            return PSTR("Nexus");
        case RGB_MATRIX_SOLID_REACTIVE_SIMPLE:
            return PSTR("Ease ");
        case RGB_MATRIX_SOLID_COLOR:
            return PSTR("Solid");
        case RGB_MATRIX_BREATHING:
            return PSTR("Fade ");
        case RGB_MATRIX_CYCLE_ALL:
            return PSTR("Cycle");
        case RGB_MATRIX_RAINBOW_PINWHEELS:
            return PSTR("Wheel");
        case RGB_MATRIX_CYCLE_LEFT_RIGHT:
            return PSTR("Wave ");
        default:
            return PSTR("");
    }
}
#endif

extern led_config_t g_led_config;

void rgb_matrix_layer_helper(uint8_t hue, uint8_t sat, uint8_t val, uint8_t led_min, uint8_t led_max) {
    HSV hsv = {hue, sat, val};
    if (hsv.v > rgb_matrix_get_val()) {
        hsv.v = rgb_matrix_get_val();
    }

    RGB rgb = hsv_to_rgb(hsv);
    for (uint8_t i = 0; i < led_max; i++) {
        if (HAS_FLAGS(g_led_config.flags[i], LED_FLAG_UNDERGLOW)) {
            rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
        }
    }
}

extern user_config_t user_config;

bool rgb_matrix_in_idle(void) {
    return (user_config.rgb_matrix_idle_anim && rgb_matrix_get_mode() == user_config.rgb_matrix_idle_mode);
}

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    if (user_config.rgb_layer_indicator && !rgb_matrix_in_idle()) {
        switch (get_highest_layer(layer_state | default_layer_state)) {
            case _GAMING_EXT:
                rgb_matrix_layer_helper(HSV_PURPLE, led_min, led_max);
                break;
            case _SYM:
                rgb_matrix_layer_helper(HSV_YELLOW, led_min, led_max);
                break;
            case _NAV:
                rgb_matrix_layer_helper(HSV_SPRINGGREEN, led_min, led_max);
                break;
            case _UTIL:
                rgb_matrix_layer_helper(HSV_PINK, led_min, led_max);
                break;
            case _NUMPAD:
                rgb_matrix_layer_helper(HSV_CORAL, led_min, led_max);
                break;
            case _GAMING:
            case _WASD:
                rgb_matrix_layer_helper(HSV_RED, led_min, led_max);
                break;
            default:
                rgb_matrix_layer_helper(THEME_HSV, led_min, led_max);
                break;
        }
    }
    return false;
}

void rgb_matrix_turn_off_underglow(void) {
    rgb_matrix_layer_helper(0, 0, 0, 0, 54);
}

uint8_t rgb_matrix_speed_for_mode(uint8_t mode) {
    switch (mode) {
        case RGB_MATRIX_SOLID_REACTIVE_SIMPLE:
        case RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS:
            return RGB_MATRIX_ANIMATION_SPEED_FAST;
        case RGB_MATRIX_BREATHING:
        case RGB_MATRIX_CYCLE_LEFT_RIGHT:
        case RGB_MATRIX_RAINBOW_PINWHEELS:
            return RGB_MATRIX_ANIMATION_SPEED_SLOW;
        case RGB_MATRIX_CYCLE_ALL:
            return RGB_MATRIX_ANIMATION_SPEED_SLOWER;
        default:
            return RGB_MATRIX_ANIMATION_SPEED_MEDIUM;
    }
}

bool rgb_matrix_mode_active(uint8_t mode) {
    return (mode == RGB_MATRIX_SOLID_REACTIVE_SIMPLE || mode == RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS || mode == RGB_MATRIX_TYPING_HEATMAP);
}

void rgb_matrix_update_current_mode(uint8_t mode) {
    rgb_matrix_config.speed = rgb_matrix_speed_for_mode(mode);
    rgb_matrix_mode_noeeprom(mode);
}

void rgb_matrix_update_dynamic_mode(uint8_t mode) {
    uint8_t speed;
    speed = rgb_matrix_speed_for_mode(mode);

    if (rgb_matrix_mode_active(mode)) {
        user_config.rgb_matrix_active_speed = speed;
        user_config.rgb_matrix_active_mode  = mode;
    } else {
        user_config.rgb_matrix_idle_speed = speed;
        user_config.rgb_matrix_idle_mode  = mode;
    }
}

void rgb_matrix_update_mode(uint8_t mode) {
    if (user_config.rgb_matrix_idle_anim) {
        rgb_matrix_update_dynamic_mode(mode);
    }
    if (rgb_matrix_mode_active(mode) || !user_config.rgb_matrix_idle_anim) {
        rgb_matrix_update_current_mode(mode);
    }
}

uint8_t get_rgb_matrix_active_mode(void) {
    if (user_config.rgb_matrix_idle_anim) {
        return user_config.rgb_matrix_active_mode;
    } else {
        return rgb_matrix_get_mode();
    }
}

void rgb_matrix_toggle_active_mode(void) {
    switch (get_rgb_matrix_active_mode()) {
        case RGB_MATRIX_SOLID_REACTIVE_SIMPLE:
            rgb_matrix_update_mode(RGB_MATRIX_TYPING_HEATMAP);
            break;
        case RGB_MATRIX_TYPING_HEATMAP:
            rgb_matrix_update_mode(RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS);
            break;
        default:
            rgb_matrix_update_mode(RGB_MATRIX_SOLID_REACTIVE_SIMPLE);
            break;
    }
}

uint8_t get_rgb_matrix_idle_mode(void) {
    if (user_config.rgb_matrix_idle_anim) {
        return user_config.rgb_matrix_idle_mode;
    } else {
        return rgb_matrix_get_mode();
    }
}

void rgb_matrix_toggle_simple_passive_mode(void) {
    switch (get_rgb_matrix_idle_mode()) {
        case RGB_MATRIX_SOLID_COLOR:
            rgb_matrix_update_mode(RGB_MATRIX_BREATHING);
            break;
        case RGB_MATRIX_BREATHING:
            rgb_matrix_update_mode(RGB_MATRIX_CYCLE_ALL);
            break;
        default:
            rgb_matrix_update_mode(RGB_MATRIX_SOLID_COLOR);
            break;
    }
}

void rgb_matrix_toggle_color_passive_mode(void) {
    switch (get_rgb_matrix_idle_mode()) {
        case RGB_MATRIX_RAINBOW_PINWHEELS:
            rgb_matrix_update_mode(RGB_MATRIX_CYCLE_LEFT_RIGHT);
            break;
        default:
            rgb_matrix_update_mode(RGB_MATRIX_RAINBOW_PINWHEELS);
            break;
    }
}

void rgb_matrix_toggle_underglow_layer_indicator(void) {
    user_config.rgb_layer_indicator ^= 1;
    if (user_config.rgb_layer_indicator) {
        layer_state_set(layer_state); // This is needed to immediately set the layer color (looks better)
    } else {
        rgb_matrix_turn_off_underglow();
    }
}

void rgb_matrix_toggle_idle_animation_change(void) {
    user_config.rgb_matrix_idle_anim ^= 1;
    if (user_config.rgb_matrix_idle_anim) {
        rgb_matrix_update_mode(user_config.rgb_matrix_active_mode);
    } else {
        rgb_matrix_update_current_mode(user_config.rgb_matrix_idle_mode);
    }
}

void rgb_matrix_set_gaming_defaults(void) {
    if (!user_config.rgb_layer_indicator) {
        user_config.rgb_layer_indicator = true;
    }
    user_config.rgb_matrix_idle_timeout = GAMING_IDLE_TIMEOUT;
    rgb_matrix_update_mode(RGB_MATRIX_RAINBOW_PINWHEELS);
    rgb_matrix_update_mode(RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS);
}

void rgb_matrix_set_typing_defaults(void) {
    user_config.rgb_matrix_idle_timeout = IDLE_TIMEOUT;
    rgb_matrix_update_mode(RGB_MATRIX_TYPING_PASSIVE);
    rgb_matrix_update_mode(RGB_MATRIX_TYPING_ACTIVE);
}

void rgb_matrix_set_defaults(void) {
    rgb_matrix_enable_noeeprom();
    rgb_matrix_sethsv_noeeprom(THEME_HSV);

    user_config.rgb_layer_indicator  = true;
    user_config.rgb_matrix_idle_anim = true;

    rgb_matrix_set_typing_defaults();

    rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_REACTIVE_SIMPLE);
}

void matrix_scan_rgb(void) {
    if (user_config.rgb_matrix_idle_anim && rgb_matrix_get_mode() == user_config.rgb_matrix_active_mode && last_input_activity_elapsed() > user_config.rgb_matrix_idle_timeout) {
        if (user_config.rgb_layer_indicator) {
            rgb_matrix_turn_off_underglow();
        }
        rgb_matrix_update_current_mode(user_config.rgb_matrix_idle_mode);
    }
}

void user_transport_sync(void) {
    // Keep track of the last state, so that we can tell if we need to propagate to slave
    static uint32_t last_config = 0, last_sync = 0;

    // Check if the state values are different
    // or if sync timer elapsed
    if (memcmp(&user_config, &last_config, sizeof(transport_user_config)) || (timer_elapsed32(last_sync) > 250)) {
        memcpy(&last_config, &user_config, sizeof(transport_user_config));

        if (transaction_rpc_send(USER_CONFIG_SYNC, sizeof(transport_user_config), &transport_user_config)) {
            last_sync = timer_read32();
        }
    }
}

void user_transport_update(void) {
    if (is_keyboard_master()) {
        transport_user_config = user_config.raw;
        user_transport_sync();
    } else {
        user_config.raw = transport_user_config;
    }
}

void housekeeping_task_user(void) {
    static bool has_ran_yet;
    if (!has_ran_yet) {
        has_ran_yet = true;
        startup_user();
    }
    matrix_scan_rgb();

    // Update config to slave
    user_transport_update();
}

void eeconfig_init_user(void) {
    user_config.raw                  = 0;
    user_config.rgb_layer_indicator  = true;
    user_config.rgb_matrix_idle_anim = true;

    rgb_matrix_enable();
    rgb_matrix_sethsv(THEME_HSV);
    rgb_matrix_mode(RGB_MATRIX_SOLID_REACTIVE_SIMPLE);

    eeconfig_update_user(user_config.raw);
}

void keyboard_post_init_user(void) {
    set_single_persistent_default_layer(_COLEMAKDH);
    rgb_matrix_set_defaults();

    // Register user config sync
    transaction_register_rpc(USER_CONFIG_SYNC, user_config_sync);
}

bool process_record_user_rgb_matrix(uint16_t keycode, keyrecord_t* record) {
    if (user_config.rgb_matrix_idle_anim) {
        if (rgb_matrix_get_mode() == user_config.rgb_matrix_idle_mode) {
            rgb_matrix_update_current_mode(user_config.rgb_matrix_active_mode);
            if (!user_config.rgb_layer_indicator) {
                rgb_matrix_turn_off_underglow();
            }
        }
    }

    switch (keycode) {
        case RGB_RST:
            if (record->event.pressed) {
                rgb_matrix_set_defaults();
            }
            break;
        case RGB_UND: // Toggle separate underglow status
            if (record->event.pressed) {
                rgb_matrix_toggle_underglow_layer_indicator();
            }
            break;
        case RGB_IDL: // Toggle idle/heatmap animation
            if (record->event.pressed) {
                rgb_matrix_toggle_idle_animation_change();
            }
            break;
        case RGB_ATG:
            if (record->event.pressed) {
                rgb_matrix_toggle_active_mode();
            }
            break;
        case RGB_PST:
            if (record->event.pressed) {
                rgb_matrix_toggle_simple_passive_mode();
            }
            break;
        case RGB_PCT:
            if (record->event.pressed) {
                rgb_matrix_toggle_color_passive_mode();
            }
            break;
    }
    return true;
}
