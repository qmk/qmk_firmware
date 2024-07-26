/* Copyright 2021 Jose Luis Adelantado Torres
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

#include "oled_display.h"
#include "keycodes.h"
#include "progmem.h"
#include "host.h"
#include "timer.h"
#include "wpm.h"
#include "rgblight.h"
#include "oled_driver.h"

static const char PROGMEM oled_mode_messages[5][15] = {
    "",
    "Volume Up",
    "Volume Down",
    "RGB ON",
    "RGB OFF"
};

static const char PROGMEM oled_mode_icons[5][3][5] = {
    {{128,129,130,131,0},{160,161,162,163,0},{192,193,194,195,0}},
    {{132,133,134,135,0},{164,165,166,167,0},{196,197,198,199,0}},
    {{136,137,138,139,0},{168,169,170,171,0},{200,201,202,203,0}},
    {{140,141,142,143,0},{172,173,174,175,0},{204,205,206,207,0}},
    {{144,145,146,147,0},{176,177,178,179,0},{208,209,210,211,0}}
};

void set_oled_mode(oled_mode_t mode) {
    oled_mode = mode;
}

void process_record_encoder_oled(uint16_t keycode) {
    oled_timer = timer_read32();
    switch (keycode) {
        case KC_VOLU:
            set_oled_mode(OLED_MODE_VOLUME_UP);
            break;
        case KC_VOLD:
            set_oled_mode(OLED_MODE_VOLUME_DOWN);
            break;
        default:
            set_oled_mode(OLED_MODE_IDLE);
            break;
    }
}

void process_record_keymap_oled(uint16_t keycode) {
    oled_timer = timer_read32();
    if(rgblight_is_enabled()) {
        set_oled_mode(OLED_MODE_RGB_OFF);
    } else {
        set_oled_mode(OLED_MODE_RGB_ON);
    }
}

void render_wpm(void) {
    uint8_t n = get_current_wpm();
    char wpm_counter[4];
    wpm_counter[3] = '\0';
    wpm_counter[2] = '0' + n % 10;
    wpm_counter[1] = '0' + (n /= 10) % 10;
    wpm_counter[0] = '0' + n / 10 ;
    oled_write_P(PSTR("                 "), false);
    oled_write(wpm_counter, false);
}

void render_idle(void) {
    // Host Keyboard LED Status
    led_t led_state = host_keyboard_led_state();

    // Printing logo, state
    oled_write_P(oled_mode_icons[0][0], false);
    oled_write_P(PSTR("        "), false);
    oled_write_P(led_state.scroll_lock ? PSTR("S ") : PSTR("  "), false);
    oled_write_P(led_state.num_lock ? PSTR("N ") : PSTR("  "), false);
    oled_write_P(led_state.caps_lock ? PSTR("C ") : PSTR("  "), false);
    oled_write_P(PSTR("\n"), false);
    oled_write_P(oled_mode_icons[0][1], false);
    oled_write_P(PSTR("  Nibble"), false);
    oled_write_P(PSTR("\n"), false);
    oled_write_P(oled_mode_icons[0][2], false);
    oled_write_P(PSTR("\n"), false);

    // Printing WPM
    render_wpm();
}

void render_status_mode_message(void) {
    // Printing state icon with message
    oled_write_P(oled_mode_icons[oled_mode][0], false);
    oled_write_P(PSTR("\n"), false);
    oled_write_P(oled_mode_icons[oled_mode][1], false);
    oled_write_P(PSTR("  "), false);
    oled_write_P(oled_mode_messages[oled_mode], false);
    oled_write_P(PSTR("\n"), false);
    oled_write_P(oled_mode_icons[oled_mode][2], false);
    oled_write_P(PSTR("\n\n"), false);
}

void render_frame(void) {
    switch (oled_mode) {
        case OLED_MODE_VOLUME_UP:
        case OLED_MODE_VOLUME_DOWN:
        case OLED_MODE_RGB_ON:
        case OLED_MODE_RGB_OFF:
            render_status_mode_message();
            break;
        default:
            render_idle();
            break;
    }
}
