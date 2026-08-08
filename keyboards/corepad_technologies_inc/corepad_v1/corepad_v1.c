// Copyright 2026 albertphu07
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H
#include "lib/logo.h"

// The XIAO RP2040's onboard WS2812 LED sits behind a power load-switch that
// must be enabled before the LED will light up. This runs before
// rgblight_init(), so the power rail is up in time for the boot flash below.
void keyboard_pre_init_kb(void) {
    gpio_set_pin_output(GP11);
    gpio_write_pin_high(GP11);

    keyboard_pre_init_user();
}

// Quick boot flash (red -> green -> blue -> white), then restores whatever
// effect/color was last saved to EEPROM - this never overwrites the user's
// configured lighting, it just announces "I'm alive" on power-up.
void keyboard_post_init_kb(void) {
#if defined(RGBLIGHT_ENABLE)
    rgblight_enable_noeeprom();
    rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);

    rgblight_sethsv_noeeprom(HSV_RED);
    wait_ms(150);
    rgblight_sethsv_noeeprom(HSV_GREEN);
    wait_ms(150);
    rgblight_sethsv_noeeprom(HSV_BLUE);
    wait_ms(150);
    rgblight_sethsv_noeeprom(HSV_WHITE);
    wait_ms(150);
#endif

    keyboard_post_init_user();
}

#if defined(OLED_ENABLE)
oled_rotation_t oled_init_kb(oled_rotation_t rotation) {
    return OLED_ROTATION_0;
}

bool oled_task_kb(void) {
    if (!oled_task_user()) {
        return false;
    }

    oled_write_raw_P(corepad_logo, sizeof(corepad_logo));
    return false;
}
#endif
