// Copyright 2026 silly group (@stwupid)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"

#ifdef OLED_ENABLE
bool oled_task_kb(oled_rotation_t rotation) {
    if (!oled_task_user(rotation)) {
        return false;
    }
    
    // Display MeowyPad logo/text
    oled_write_ln_P(PSTR("MeowyPad"), false);
    oled_write_ln_P(PSTR("by silly group"), false);
    oled_write_ln_P(PSTR(""), false);
    
    // Display current layer
    oled_write_P(PSTR("Layer: "), false);
    oled_write_char('0' + get_highest_layer(layer_state), false);
    oled_write_ln_P(PSTR(""), false);
    
    return false;
}
#endif
