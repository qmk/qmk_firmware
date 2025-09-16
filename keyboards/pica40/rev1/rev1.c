// Copyright 2022 zzeneg (@zzeneg)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"

#ifdef PICA40_RGBLIGHT_TIMEOUT

uint16_t check_rgblight_timer = 0;
uint16_t idle_timer = 0;
uint8_t counter = 0;

void housekeeping_task_kb(void) {
    if (timer_elapsed(check_rgblight_timer) > 1000) {
        check_rgblight_timer = timer_read();

        if (rgblight_is_enabled() && timer_elapsed(idle_timer) > 10000) {
            idle_timer = timer_read();
            counter++;
        }

        if (rgblight_is_enabled() && counter > PICA40_RGBLIGHT_TIMEOUT * 6) {
            counter = 0;
            rgblight_disable_noeeprom();
        }
    }
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed && timer_elapsed(idle_timer) > 1000) {
        idle_timer = timer_read();
        counter = 0;
        if (!rgblight_is_enabled()) {
            rgblight_enable_noeeprom();
        }
    }

    return process_record_user(keycode, record);
}

void keyboard_post_init_kb(void) {
    check_rgblight_timer = timer_read();
    idle_timer = timer_read();
    rgblight_enable_noeeprom();

    keyboard_post_init_user();
}


#endif // PICA40_RGBLIGHT_TIMEOUT

#ifdef OLED_ENABLE

oled_rotation_t oled_init_kb(oled_rotation_t rotation) {
    return OLED_ROTATION_270;
}

void render_mods(uint8_t modifiers) {
    oled_write_ln_P((modifiers & MOD_MASK_CTRL) ? PSTR("Ctrl") : PSTR(" "), false);
    oled_write_ln_P((modifiers & MOD_MASK_ALT) ? PSTR("Alt") : PSTR(" "), false);
    oled_write_ln_P((modifiers & MOD_MASK_SHIFT) ? PSTR("Shft") : PSTR(" "), false);
    oled_write_ln_P((modifiers & MOD_MASK_GUI) ? PSTR("GUI") : PSTR(" "), false);
}

bool oled_task_kb(void) {
    // display's top is hidden by cover
    oled_write_ln_P(PSTR(" "), false);
    oled_write_ln_P(PSTR(" "), false);
    oled_write_ln_P(PSTR(" "), false);

    if (!oled_task_user()) return false;

    render_mods(get_mods());

    return true;
}

#endif // OLED_ENABLE
