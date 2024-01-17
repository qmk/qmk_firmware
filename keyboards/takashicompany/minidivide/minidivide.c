// Copyright 2023 takashicompany (@takashicompany)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"

#ifdef OLED_ENABLE

oled_rotation_t oled_init_kb(oled_rotation_t rotation) {
    return OLED_ROTATION_270;
}

//Variable that stores the number of times the key was pressed
static uint16_t press_count = 0;

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_user(keycode, record)) {
        return false;
    }
     // Increment the counter when a key is pressed
    if (record->event.pressed) {
        press_count++;
    }

    return process_record_user(keycode, record);
}

bool oled_task_kb(void) {

    if (!oled_task_user()) { return false; }

	oled_write_ln_P(PSTR("mini"), false);
	oled_write_ln_P(PSTR("Divide"), false);

    oled_set_cursor(0, 5);

    oled_write_ln_P(PSTR("Layer"), false);
    oled_write_ln(get_u8_str(get_highest_layer(layer_state), ' '), false);

    oled_write_ln_P(PSTR(" "), false);
    oled_write_ln_P(PSTR(" "), false);

    oled_write_ln_P(PSTR("Count"), false);
    oled_write_ln(get_u16_str(press_count, ' '), false);

    return false;

}
#endif