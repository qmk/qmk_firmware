// Copyright 2023 Vinh Le (@vinhcatba)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "uncertainty.h"

#ifdef OLED_ENABLE
#include "bongo.h"
// Used to draw on to the oled screen
bool oled_minimal = true;
bool oled_task_kb(void) {
    if(!oled_task_user()) { return false; }
    draw_bongo(oled_minimal);
    return false;
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
     if (!process_record_user(keycode, record)) {
        return false;
    }

    switch (keycode) {
        case OLED_TOG:
            if (record->event.pressed) {
                oled_minimal = !oled_minimal;
            }
            return false;
        default:
            return true;
    }
}
#endif // endif OLED_ENABLE
