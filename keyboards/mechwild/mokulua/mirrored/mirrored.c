// Copyright 2022 Kyle McCreery (@Kyle McCreery)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "standard.h"

#ifdef ENCODER_ENABLE
bool encoder_update_kb(uint8_t index, bool clockwise) {
    if (!encoder_update_user(index, clockwise)) { return false; }
    switch (index) {
        case 0:
            if (clockwise) {
                tap_code(KC_VOLU);
            } else {
                tap_code(KC_VOLD);
            }
        break;
        case 1:
            if (clockwise) {
                tap_code(KC_PGUP);
            } else {
                tap_code(KC_PGDN);
            }
        break;

    }
    return true;
}
#endif

#ifdef OLED_ENABLE
	oled_rotation_t oled_init_user(oled_rotation_t rotation) {
		return OLED_ROTATION_270;       // flips the display 270 degrees
	}

	static void render_logo(void) {     // Render MechWild "MW" Logo
		static const char PROGMEM logo_1[] = {0x8A, 0x8B, 0x8C, 0x8D, 0x00};
		static const char PROGMEM logo_2[] = {0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0x00};
		static const char PROGMEM logo_3[] = {0xCA, 0xCB, 0xCC, 0xCD, 0x00};
		static const char PROGMEM logo_4[] = {0x20, 0x8E, 0x8F, 0x90, 0x00};
		oled_set_cursor(0,0);
		oled_write_P(logo_1, false);
		oled_set_cursor(0,1);
		oled_write_P(logo_2, false);
		oled_set_cursor(0,2);
		oled_write_P(logo_3, false);
		oled_set_cursor(0,3);
		oled_write_P(logo_4, false);
	}
	bool oled_task_kb(void) {
		if (!oled_task_user()) {
			return false;
		}
		render_logo();
		oled_set_cursor(0,6);
		
		oled_write_ln_P(PSTR("Layer"), false);
		
		switch (get_highest_layer(layer_state)) {
			case 0:
				oled_write_ln_P(PSTR("Base"), false);
				break;
			case 1:
				oled_write_ln_P(PSTR("FN 1"), false);
				break;
			case 2:
				oled_write_ln_P(PSTR("FN 2"), false);
				break;
			case 3:
				oled_write_ln_P(PSTR("FN 3"), false);
				break;
			default:
				oled_write_ln_P(PSTR("Undef"), false);
		}
		oled_write_ln_P(PSTR(""), false);
		// Host Keyboard LED Status
		led_t led_state = host_keyboard_led_state();
		oled_write_ln_P(led_state.num_lock ? PSTR("NUM ") : PSTR("    "), false);
		oled_write_ln_P(led_state.caps_lock ? PSTR("CAP ") : PSTR("    "), false);
		oled_write_ln_P(led_state.scroll_lock ? PSTR("SCR ") : PSTR("    "), false);
		return false;
    }
#endif
