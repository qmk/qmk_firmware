// Copyright 2024 jack (@waffle87)
// SPDX-License-Identifier: GPL-2.0-or-later
#include "quantum.h"
#include "lib/oled.h"

#ifdef OLED_ENABLE
bool oled_task_kb(void) {
    if (!oled_task_user()) {
        return false;
    }
    render_layer_state();
    return false;
}
#endif
