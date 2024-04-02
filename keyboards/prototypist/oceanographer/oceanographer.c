// Copyright 2023 Anjheos (@Anjheos)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"

#ifdef OLED_ENABLE 
oled_rotation_t oled_init_kb(oled_rotation_t rotation) {
    return OLED_ROTATION_90;  
}

bool oled_task_kb(void) {
    if (!oled_task_user()){
        return false;
    }
    
    oled_write_ln_P(PSTR("LAYER"), false);

    switch (get_highest_layer(layer_state)) {

        case 0:
            oled_write_ln_P(PSTR("L1"), false);
            break;

        case 1:
            oled_write_ln_P(PSTR("L2"), false);
            break;

        case 2:
            oled_write_ln_P(PSTR("L3"), false);
            break;

        case 3:
            oled_write_ln_P(PSTR("L4"), false);
            break;

        default:
            oled_write_ln_P(PSTR(" "), false);

    }

    oled_write_ln_P(PSTR("     "), false);

    oled_write_ln_P(PSTR("LOCK:"), false);
    
    led_t led_state = host_keyboard_led_state();
    
    oled_write_P(led_state.caps_lock ? PSTR ("CAPS ") : PSTR("     "), false);
    oled_write_P(led_state.scroll_lock ? PSTR ("SCROL") : PSTR("     "), false);
    oled_write_ln_P(led_state.num_lock ? PSTR ("NUM ") : PSTR("     "), false);

    return false;
}

#endif