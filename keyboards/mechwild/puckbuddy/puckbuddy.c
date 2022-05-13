/* Copyright 2021 Kyle McCreery
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "puckbuddy.h"

void board_init(void) {
    // B9 is configured as I2C1_SDA in the board file; that function must be
    // disabled before using B7 as I2C1_SDA.
    setPinInputHigh(B9);
}

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
        case 1:
            if (clockwise) {
                tap_code(KC_VOLU);
            } else {
                tap_code(KC_VOLD);
            }
        break;
    }
    return true;
}
#endif

//#ifdef OLED_ENABLE   // OLED Functionality
//    oled_rotation_t oled_init_user(oled_rotation_t rotation) {
//        return OLED_ROTATION_180;       // flips the display 180 degrees if offhand
//    }
//    
//    static void render_logo(void) {     // Render MechWild "MW" Logo
//        static const char PROGMEM logo_1[] = {0x97, 0x98, 0x99, 0x9A,0x00};
//        static const char PROGMEM logo_2[] = {0xB7, 0xB8, 0xB9, 0xBA, 0xBB, 0xBC, 0xBD, 0x00};
//        static const char PROGMEM logo_3[] = {0xD7, 0xD8, 0xD9, 0xDA, 0xDB, 0xDC, 0xDD, 0xB6, 0x00};
//        static const char PROGMEM logo_4[] = {0xB6, 0xB6, 0xB6, 0x9B, 0x9C, 0x9D, 0x9E, 0x00};
//        oled_set_cursor(0,0);
//        oled_write_P(logo_1, false);
//        oled_set_cursor(0,1);
//        oled_write_P(logo_2, false);
//        oled_set_cursor(0,2);
//        oled_write_P(logo_3, false);
//        oled_set_cursor(0,3);
//        oled_write_P(logo_4, false);
//    }
//    
//    bool oled_task_user(void) {
//        render_logo();
//        oled_set_cursor(8,2);
//        switch(selected_layer){
//            case 0:
//                oled_write_P(PSTR("Lock Layer 0"), false);
//                break;
//            case 1:
//                oled_write_P(PSTR("Lock Layer 1"), false);
//                break;
//            case 2:
//                oled_write_P(PSTR("Lock Layer 2"), false);
//                break;
//            case 3:
//                oled_write_P(PSTR("Lock Layer 3"), false);
//                break;
//            default:
//                oled_write_P(PSTR("Lock Layer ?"), false);    // Should never display, here as a catchall
//        }
//        oled_set_cursor(8,3);
//        if (get_highest_layer(layer_state) == selected_layer) {
//            oled_write_P(PSTR("            "), false);
//        } else {
//            switch (get_highest_layer(layer_state)) {
//                case 0:
//                    oled_write_P(PSTR("Temp Layer 0"), false);
//                    break;
//                case 1:
//                    oled_write_P(PSTR("Temp Layer 1"), false);
//                    break;
//                case 2:
//                    oled_write_P(PSTR("Temp Layer 2"), false);
//                    break;
//                case 3:
//                    oled_write_P(PSTR("Temp Layer 3"), false);
//                    break;
//                default:
//                    oled_write_P(PSTR("Temp Layer ?"), false);    // Should never display, here as a catchall
//            }
//        }
//        led_t led_state = host_keyboard_led_state();
//        oled_set_cursor(8,0);
//        oled_write_P(led_state.scroll_lock ? PSTR("SCRLK") : PSTR("     "), false);
//        oled_set_cursor(8,1);
//        oled_write_P(led_state.num_lock ? PSTR("NLCK ") : PSTR("     "), false);
//        oled_write_P(led_state.caps_lock ? PSTR("CAPS ") : PSTR("     "), false);
//    }
//#endif


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

	bool oled_task_user(void) {
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
