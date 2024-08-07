// SPDX-FileCopyrightText: 2024 Takahiro Natsume ( @nuovotaka )
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"

#if defined(OLED_ENABLE) && !defined(OLEDKIT_DISABLE)

__attribute__((weak)) void oledkit_render_mylogo(void) {
    char ch = 0x80;
    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 5; x++) {
            oled_write_char(ch++, false);
        }
    }
    oled_advance_page(false);
}

__attribute__((weak)) void oledkit_render_info_user(void)
{
    oled_clear();
    oledkit_render_mylogo();
}

bool oled_task_kb(void) {
    if (!oled_task_user()) {
        return false;
    }
    oledkit_render_mylogo();
    oledkit_render_info_user();

    return false;
}

__attribute__((weak)) oled_rotation_t oled_init_kb(oled_rotation_t rotation) {
    return OLED_ROTATION_270;
}

#endif
