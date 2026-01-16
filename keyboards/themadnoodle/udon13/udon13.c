// Copyright 2023 The Mad Noodle(@the_mad_noodle)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"

#ifdef OLED_ENABLE

/* OLED Settings */
//------------------------------------------------------------------------------------------------

static void render_logo(void) { // Render Mad Noodle logo
    static const char PROGMEM logo_1[] = {0x00, 0x00, 0x80, 0xc0, 0x60, 0x30, 0x18, 0x0c, 0x04, 0x06, 0x82, 0xc3, 0x43, 0x61, 0xa1, 0xa1, 0xa1, 0xa1, 0x61, 0x43, 0xc3, 0x82, 0x06, 0x04, 0x0c, 0x18, 0x30, 0x60, 0xc0, 0x80, 0x00, 0x00};
    static const char PROGMEM logo_2[] = {0xf8, 0x1e, 0xc3, 0xf8, 0x5c, 0x76, 0x7b, 0x6d, 0x75, 0x55, 0x55, 0x75, 0x6d, 0x7b, 0x76, 0x5e, 0x7e, 0x77, 0x5b, 0x6d, 0x75, 0x55, 0x55, 0x75, 0x4d, 0x7b, 0x66, 0x5c, 0xf0, 0xc3, 0x3e, 0xf0};
    static const char PROGMEM logo_3[] = {0x1f, 0x78, 0xc1, 0x0f, 0x38, 0xe0, 0xc0, 0x00, 0x00, 0x02, 0x0e, 0x0e, 0x8e, 0xc6, 0xc0, 0x40, 0x40, 0xc0, 0xc6, 0x8e, 0x0e, 0x0e, 0x02, 0x00, 0x80, 0xc0, 0x60, 0x38, 0x0f, 0xc0, 0x7c, 0x0f};
    static const char PROGMEM logo_4[] = {0x00, 0x00, 0x01, 0x03, 0x06, 0x0c, 0x18, 0x31, 0x23, 0x66, 0x44, 0x44, 0xc4, 0xc4, 0x84, 0x84, 0x84, 0x84, 0xc4, 0xc4, 0x44, 0x46, 0x66, 0x23, 0x11, 0x18, 0x0c, 0x06, 0x03, 0x00, 0x00, 0x00};
    oled_set_cursor(0, 0);
    oled_write_raw_P(logo_1, sizeof(logo_1));
    oled_set_cursor(0, 1);
    oled_write_raw_P(logo_2, sizeof(logo_2));
    oled_set_cursor(0, 2);
    oled_write_raw_P(logo_3, sizeof(logo_3));
    oled_set_cursor(0, 3);
    oled_write_raw_P(logo_4, sizeof(logo_4));
}
//-----------

bool oled_task_kb(void) {
    if (!oled_task_user()) { return false; }
    render_logo();
    oled_set_cursor(7, 0);
    oled_write_P(PSTR("The Mad Noodle"), false);

    oled_set_cursor(7, 1);
    oled_write_P(PSTR("Layer: "), false);

    /*
    To change LAYER NAMES displayed on the OLED ensure they are a total of 6 characters, including spaces.
    Example:
    ---------------------------------------------------
    case 0:
          oled_write_P(PSTR("Base  "), false);
          break;
    ---------------------------------------------------
    "B A S E *SPACE* *SPACE*" = 6 characters
    This would change layer 0 to Base on the OLED
    */

    switch (get_highest_layer(layer_state)) {
        case 0:
            oled_write_P(PSTR("Zero  "), false);
            break;
        case 1:
            oled_write_P(PSTR("One   "), false);
            break;
        case 2:
            oled_write_P(PSTR("Two   "), false);
            break;
        case 3:
            oled_write_P(PSTR("Three "), false);
            break;

        default:
            oled_write_P(PSTR("N/A   "), false);
    }
    oled_set_cursor(7, 2);
    oled_write_P(PSTR("Status: "), false);
    oled_set_cursor(7, 3);
    led_t led_state = host_keyboard_led_state();
    oled_write_P(led_state.num_lock ? PSTR("NUM ") : PSTR("   "), false);
    oled_write_P(led_state.caps_lock ? PSTR("CAP ") : PSTR("   "), false);
    oled_write_P(led_state.scroll_lock ? PSTR("SCR ") : PSTR("   "), false);

    return false;
}

#endif