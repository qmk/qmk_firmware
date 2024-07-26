/* Copyright 2021 duoshock 
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

#include "quantum.h"

#ifndef WPM_ENABLE
#    define get_current_wpm() 0
#endif

#ifdef OLED_ENABLE
void suspend_power_down_kb(void) {
    oled_off();
    suspend_power_down_user();
}

oled_rotation_t oled_init_kb(oled_rotation_t rotation) {
    if (is_keyboard_master()) {
        return OLED_ROTATION_90;
    }

    return rotation;
}

//UM-80 logo
static void render_logo(void) {
    static const char PROGMEM raw_logo[] = {
        0,0,0,0,0,0,0,0,0,0,128,192,192,224,224,224,224,224,224,224,224,224,224,224,224,224,224,192,192,128,128,192,
        192,224,224,224,224,224,224,224,224,192,192,128,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,15,3,1,0,1,255,255,255,
        255,255,255,255,255,255,255,255,255,255,255,254,252,240,0,0,0,0,0,0,0,0,0,254,254,254,0,0,0,0,0,0,254,254,254,
        0,0,0,254,254,254,252,248,224,192,128,224,248,252,254,254,254,0,0,128,128,128,128,128,128,0,0,0,120,252,254,206,
        206,206,206,254,124,120,0,0,240,248,252,62,30,14,14,30,62,252,248,240,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,255,255,255,
        255,255,255,255,255,255,255,255,255,255,255,255,255,255,240,192,128,0,128,255,255,255,255,255,255,255,255,255,255,
        255,255,255,255,127,63,15,0,0,0,0,0,0,0,0,0,15,63,63,124,112,112,112,112,124,63,63,15,0,0,0,127,127,127,0,1,7,15,
        15,7,1,0,127,127,127,0,0,3,3,3,3,3,3,1,0,30,63,127,123,113,113,113,123,127,63,30,0,0,15,31,63,124,120,112,112,120,
        124,63,31,15,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,3,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,3,3,1,1,3,3,7,7,7,7,7,7,7,7,3,3,1,
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
    };
    oled_write_raw_P(raw_logo, sizeof(raw_logo));
}


// 32 * 18 Merge logo
static const char PROGMEM merge_logo[] = {
    0xf8, 0xfe, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x3f, 0x0e,
    0x06, 0x04, 0xfe, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xfe, 0xfc, 0xf8, 0xf0, 0xc0,
    0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0xc0,
    0x80, 0x80, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x3f, 0x0f,
    0x00, 0x01, 0x01, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x01,
    0x01, 0x00, 0x01, 0x01, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00
};

static void print_status_narrow(void) {
    oled_set_cursor(0,1);
    oled_write_raw_P(merge_logo, sizeof(merge_logo));
    oled_set_cursor(0,5);
    oled_write_P(PSTR("-----"), false);
    oled_set_cursor(0,6);
    oled_write_P(PSTR("LYR "), false);
    switch (get_highest_layer(layer_state)) {
        case 0:
            oled_write_P(PSTR("0"), false);
            break;
        case 1:
            oled_write_P(PSTR("1"), false);
            break;
        case 2:
            oled_write_P(PSTR("2"), false);
            break;
        case 3:
            oled_write_P(PSTR("3"), false);
            break;
        default:
            oled_write_ln_P(PSTR("Undef"), false);
    }
    led_t led_usb_state = host_keyboard_led_state();
    oled_write_ln_P(PSTR(" "), false);
    oled_write_P(PSTR("CAP "), false);
    oled_write_P(PSTR("."), led_usb_state.caps_lock);
    oled_write_P(PSTR("NUM "), false);
    oled_write_P(PSTR("."), led_usb_state.num_lock);
    oled_write_P(PSTR("SCR "), false);
    oled_write_P(PSTR("."), led_usb_state.scroll_lock);
    //oled_write_ln_P(PSTR(" "), false);
    oled_write_P(PSTR("-----"), false);

    // WPM counter Start
    oled_set_cursor(0,13);
    oled_write(" ", false);
    oled_write(get_u8_str(get_current_wpm(), '0'), false);
    oled_set_cursor(0,14);
    oled_write(" WPM ", false);
    // WPM counter End
}

bool oled_task_kb(void) {
    if (!oled_task_user()) { return false; }
    if (is_keyboard_master()) {
        print_status_narrow();
        //render_logo();
    } else {
        render_logo();
        //print_status_narrow();
    }
    return false;
}

#endif