// Copyright 2022-2023 Thomas Autiello Jr (@fearherbs1)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"
#ifdef OLED_ENABLE
bool oled_task_kb(void) {
    if (!oled_task_user()) {
        return false;
    }
    // Host Keyboard Layer Status
    oled_write_P(PSTR("Blue Team Pad \nCurrent Layer: "), false);

    switch (get_highest_layer(layer_state)) {
        case 0:
            oled_write_P(PSTR("0\n"), false);
            break;
        case 1:
            oled_write_P(PSTR("1\n"), false);
            break;
        case 2:
            oled_write_P(PSTR("2\n"), false);
            break;
        case 3:
            oled_write_P(PSTR("3\n"), false);
            break;
        case 4:
            oled_write_P(PSTR("4\n"), false);
            break;
        case 5:
            oled_write_P(PSTR("5\n"), false);
            break;
        default:
            // Or use the write_ln shortcut over adding '\n' to the end of your string
            oled_write_ln_P(PSTR("Undefined"), false);
    }
    return false;
}
#endif
