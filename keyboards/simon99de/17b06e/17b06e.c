// Copyright 2025 FabiClawZ (@FFS2309)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#ifdef OLED_ENABLE

#include <./lib/layer_select_4.h>
oled_rotation_t oled_init_kb(oled_rotation_t rotation){
    return OLED_ROTATION_180;
}
bool oled_task_kb(void) {
    render_layer_status();

    return oled_task_user();
}
#endif
