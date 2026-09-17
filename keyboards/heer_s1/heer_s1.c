// Copyright 2026 Heer (@heer)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"

#ifdef OLED_ENABLE

// The panel is mounted upside-down on the PCB, so the rotation belongs to the
// board rather than to any one keymap.
//
// This returns the rotation and nothing else. oled_driver.c does:
//
//     oled_rotation = oled_init_user(oled_init_kb(rotation));
//
// so the driver already chains the keymap's hook onto this one's result —
// calling oled_init_user() from in here would run it twice.
oled_rotation_t oled_init_kb(oled_rotation_t rotation) {
    return OLED_ROTATION_180;
}

// A keymap that draws its own screen returns false from oled_task_user, which
// stops the board's default display painting over it. This mirrors the weak
// default in oled_driver.c, which is simply `return oled_task_user();`.
bool oled_task_kb(void) {
    if (!oled_task_user()) {
        return false;
    }

    oled_set_cursor(0, 0);
    oled_write_P(PSTR("   HEER  S1"), false);

    oled_set_cursor(0, 1);
    oled_write_P(PSTR("---------------"), false);

    // Shown as a number, not a name: a board-level default cannot know what any
    // given keymap calls its layers.
    oled_set_cursor(0, 2);
    oled_write_P(PSTR("LAYER "), false);
    oled_write_char('0' + get_highest_layer(layer_state), false);

    oled_set_cursor(0, 3);
    oled_write_P(PSTR("["), false);
    for (uint8_t i = 0; i < 4; i++) {
        oled_write_P(get_highest_layer(layer_state) == i ? PSTR("*") : PSTR("-"), false);
    }
    oled_write_P(PSTR("]"), false);

    return true;
}

#endif // OLED_ENABLE
