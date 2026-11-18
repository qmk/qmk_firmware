// Copyright 2024-2026 DeskDaily (@DeskDaily), gregandcin <gregandcinbusiness@gmail.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#ifdef OLED_ENABLE
#    include "common/oled.h"

bool oled_task_kb(void) {
    if (!oled_task_user()) {
        return false;
    }

    if (OLED_redraw) {
        oled_clear();
        last_bongo_frame = 12; // Force a redraw.
        draw_bongo_table();
        OLED_redraw = false;
    }
    draw_bongocat();

    led_t led_state = host_keyboard_led_state();
    oled_set_cursor(0, 0);
    oled_write_P(led_state.caps_lock ? PSTR("CAPS  ") : PSTR("      "), false);
    oled_set_cursor(0, 1);
    oled_write_P(led_state.scroll_lock ? PSTR("SCR   ") : PSTR("      "), false);
    return false;
}
#endif
