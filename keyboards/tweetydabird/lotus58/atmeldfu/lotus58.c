// Copyright 2022 Markus Knutsson (@TweetyDaBird)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"

oled_rotation_t oled_init_kb(oled_rotation_t rotation) {
	// Rotate OLED to fit
    if (is_keyboard_left()) {
        return OLED_ROTATION_270;
	}
    return OLED_ROTATION_270;
}

void render_logo(void) {
	// QMK Logo
    static const char PROGMEM qmk_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4,
        0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0x00
    };
    oled_write_P(qmk_logo, false);
}

static void print_status_narrow(void) {
	// Create OLED content
    oled_write_P(PSTR("\n"), false);
	oled_write_P(PSTR(""), false);
    oled_write_P(PSTR("Lotus -58-"), false);
	oled_write_P(PSTR("\n"), false);

    // Print current layer
    oled_write_P(PSTR("Layer"), false);
    switch (get_highest_layer(layer_state)) {
        case 0:
            oled_write_P(PSTR("-Base\n"), false);
            break;
        case 1:
            oled_write_P(PSTR("-Num \n"), false);
            break;
        case 2:
            oled_write_P(PSTR("-Func\n"), false);
            break;
        case 3:
            oled_write_P(PSTR("-Sys \n"), false);
            break;
        default:
            oled_write_P(PSTR("Undef"), false);
    }
	
	// Display autoshift
    oled_write_P(PSTR("\n"), false);
    led_t led_usb_state = host_keyboard_led_state();
    oled_write_ln_P(PSTR("Caps- lock"), led_usb_state.caps_lock);
	bool autoshift = get_autoshift_state();
	oled_write_P(PSTR("\n"), false);
	oled_write_P(PSTR("Auto-Shift"), autoshift);
	oled_write_P(PSTR("\n"), false);
	
}