 /* Copyright 2021 Domanic Calleja
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
#include "lyra.h"

#ifdef OLED_ENABLE

// 'lyralogooled', 32x128px
oled_rotation_t oled_init_kb(oled_rotation_t rotation) {
    if (is_keyboard_master()) {
        return OLED_ROTATION_270;
    }
    return rotation;
}

__attribute__((weak)) void oled_task_user(void) {
    if (is_keyboard_master()) {
        oled_write_P(PSTR("      "), false);
#    ifdef WPM_ENABLE
      uint8_t n = get_current_wpm();
        char wpm_counter[4];
        wpm_counter[3] = '\0';
        wpm_counter[2] = '0' + n % 10;
        wpm_counter[1] = (n /= 10) % 10 ? '0' + (n) % 10 : (n / 10) % 10 ? '0' : ' ';
        wpm_counter[0] = n / 10 ? '0' + n / 10 : ' ';
        oled_write(wpm_counter, false);
        oled_write_ln_P(PSTR("   WPM"), false);
#    else
        oled_advance_page(true);
#    endif
        oled_advance_page(true);
        led_t led_usb_state = host_keyboard_led_state();
        oled_write_ln_P(PSTR("CPSLK"), led_usb_state.caps_lock);
        oled_advance_page(true);  oled_advance_page(true);
        oled_write_ln_P(PSTR("Lyra"), false);
        oled_write_ln_P(PSTR("v1.1"), false);
        oled_write_ln_P(PSTR("by"), false);
        oled_write_P(PSTR("Dom C"), false);
    } else {
        static const char PROGMEM QMK_logo[] = {
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xe0, 0x78, 0x18, 0x0c, 0x04, 0x06, 0x02, 
            0x02, 0x82, 0xc0, 0xf0, 0x38, 0x8c, 0xf2, 0x3e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
            0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
            0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0xc0, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x40, 0x40, 0x40, 0xc0, 0x80, 
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
            0x00, 0x00, 0x00, 0x80, 0x40, 0xc0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x1f, 0x18, 0x30, 0x20, 0xa0, 0xe0, 0xf8, 
            0x3e, 0x1f, 0x13, 0x0c, 0x06, 0xc3, 0xf0, 0x60, 0x00, 0x80, 0xf0, 0xe0, 0x00, 0x38, 0xfe, 0x67, 
            0x7b, 0xa5, 0xf3, 0xf0, 0x70, 0x00, 0x00, 0x80, 0xc0, 0xc0, 0xe0, 0x70, 0x30, 0x20, 0x00, 0x00, 
            0x00, 0x80, 0x00, 0x00, 0x00, 0x7f, 0xc0, 0xdd, 0xdd, 0xdd, 0xe3, 0x7e, 0x3c, 0x3e, 0x61, 0xdf, 
            0xde, 0xde, 0x01, 0xff, 0xfe, 0x00, 0x80, 0x80, 0x80, 0xff, 0xc0, 0xdf, 0xdf, 0xdf, 0xe0, 0xff, 
            0x7f, 0x3c, 0x62, 0xdd, 0xdd, 0xdd, 0xe3, 0x7e, 0x3c, 0xfe, 0xc1, 0xfd, 0x7d, 0xc3, 0xfd, 0x7d, 
            0xc3, 0xfe, 0xfc, 0x30, 0xea, 0xd5, 0xd5, 0xd5, 0xc3, 0xff, 0xfe, 0x7e, 0xc1, 0xfd, 0x7d, 0x7d, 
            0xc3, 0xfe, 0xfc, 0x3f, 0xe1, 0xff, 0xff, 0x3c, 0x62, 0xdd, 0xdd, 0xdd, 0xf7, 0xe6, 0x00, 0x00, 
            0x00, 0x78, 0xc4, 0xc2, 0x82, 0x82, 0x82, 0x82, 0xc2, 0xe4, 0x74, 0x7c, 0x3f, 0x1f, 0x31, 0x60, 
            0xe0, 0xc0, 0x80, 0x9c, 0xbf, 0xe7, 0xf1, 0x78, 0x3e, 0x1f, 0x0b, 0x04, 0x02, 0x01, 0x00, 0x1c, 
            0x3e, 0x2f, 0x13, 0x10, 0x0c, 0x1e, 0x3f, 0x2f, 0x13, 0x09, 0x1c, 0x3e, 0x2f, 0x10, 0x08, 0x06, 
            0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x06, 
            0x06, 0x06, 0x07, 0x03, 0x7f, 0xc1, 0xbe, 0xbe, 0xbe, 0xa6, 0xe7, 0xc7, 0x60, 0xd4, 0xaa, 0xaa, 
            0xaa, 0x86, 0xfe, 0xfc, 0x7f, 0xc0, 0xff, 0xff, 0x7f, 0xc0, 0xff, 0xff, 0xc4, 0xaa, 0xaa, 0xaa, 
            0xa6, 0xfc, 0xf8, 0xff, 0x02, 0xff, 0xff, 0x60, 0xd4, 0xaa, 0xaa, 0xaa, 0x86, 0xfe, 0xfc, 0x00, 
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
            0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x28, 0x24, 
            0x32, 0x1b, 0x1f, 0x0f, 0x0f, 0x1f, 0x1f, 0x3c, 0x38, 0x38, 0x78, 0x70, 0x70, 0x70, 0x30, 0x38, 
            0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x01, 0x01, 
            0x01, 0x01, 0x01, 0x01, 0x00, 0x01, 0x01, 0x01, 0x00, 0x01, 0x01, 0x01, 0x00, 0x01, 0x01, 0x01, 
            0x01, 0x01, 0x07, 0x0d, 0x0e, 0x07, 0x03, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 
        };
        oled_write_raw_P(QMK_logo, sizeof(QMK_logo));
    }
}
#endif 
