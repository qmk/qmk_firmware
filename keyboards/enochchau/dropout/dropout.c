// Copyright 2025 Enoch Chau <enoch965@gmail.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"

// Mimic handle_backlight_caps_lock to use num lock indicator for backlight
void handle_backlight_num_lock(led_t led_state) {
    // Use backlight as num_lock indicator
    uint8_t bl_toggle_lvl     = 0;
    bool    backlight_enabled = is_backlight_enabled();

    if (led_state.num_lock && !backlight_enabled) {
        // Turning num_lock ON and backlight is disabled in config
        // Toggling backlight to the brightest level
        bl_toggle_lvl = BACKLIGHT_LEVELS;
    } else if (!led_state.num_lock && backlight_enabled) {
        // Turning num_lock OFF and backlight is enabled in config
        // Toggling backlight and restoring config level
        bl_toggle_lvl = get_backlight_level();
    }

    backlight_set(bl_toggle_lvl);
}

bool led_update_kb(led_t led_state) {
    bool res = led_update_user(led_state);
    if (res) {
#ifdef BACKLIGHT_ENABLE
        handle_backlight_num_lock(led_state);
#endif
    }
    return res;
}
