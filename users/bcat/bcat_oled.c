/* Copyright 2021 Jonathan Rascher
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

#include "bcat_oled.h"

#include <stdbool.h>
#include <stdint.h>

#include "bcat.h"
#include "led.h"
#include "oled_driver.h"
#include "progmem.h"
#include "quantum.h"
#include "timer.h"
#include "wpm.h"

static const char TRIANGLE_UP   = 0x1e;
static const char TRIANGLE_DOWN = 0x1f;

void render_oled_logo(void) {
    static const char PROGMEM logo[] = {
        // clang-format off
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4,
        0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4,
        0x00,
        // clang-format on
    };

    oled_write_P(logo, /*invert=*/false);
}

void render_oled_layers(void) {
    oled_advance_char();
    oled_advance_char();
#if defined(BCAT_ORTHO_LAYERS)
    oled_write_char(IS_LAYER_ON(LAYER_LOWER) ? TRIANGLE_DOWN : ' ', /*invert=*/false);
    oled_advance_char();
    oled_write_char(IS_LAYER_ON(LAYER_RAISE) ? TRIANGLE_UP : ' ', /*invert=*/false);
#else
    switch (get_highest_layer(layer_state)) {
        case LAYER_FUNCTION_1:
            oled_write_P(PSTR("FN1"), /*invert=*/false);
            break;
        case LAYER_FUNCTION_2:
            oled_write_P(PSTR("FN2"), /*invert=*/false);
            break;
        default:
            oled_write_P(PSTR("   "), /*invert=*/false);
            break;
    }
#endif
}

void render_oled_indicators(void) {
    led_t led_state = host_keyboard_led_state();
    oled_advance_char();
    oled_advance_char();
    oled_write_P(led_state.num_lock ? PSTR("NUM") : PSTR("   "), /*invert=*/false);
    oled_advance_char();
    oled_advance_char();
    oled_write_P(led_state.caps_lock ? PSTR("CAP") : PSTR("   "), /*invert=*/false);
    oled_advance_char();
    oled_advance_char();
    oled_write_P(led_state.scroll_lock ? PSTR("SCR") : PSTR("   "), /*invert=*/false);
}

void render_oled_wpm(void) {
    static const uint16_t UPDATE_INTERVAL_MILLIS = 100;
    static uint32_t       update_timeout         = 0;

    if (timer_expired32(timer_read32(), update_timeout)) {
        uint8_t wpm = get_current_wpm();

        char wpm_str[] = "   ";
        if (wpm > 0) {
            wpm_str[2] = '0' + wpm % 10;
        }
        if (wpm >= 10) {
            wpm_str[1] = '0' + wpm / 10 % 10;
        }
        if (wpm >= 100) {
            wpm_str[0] = '0' + wpm / 100 % 10;
        }

        oled_advance_char();
        oled_advance_char();
        oled_write_P(wpm > 0 ? PSTR("WPM") : PSTR("   "), /*invert=*/false);
        oled_advance_char();
        oled_advance_char();
        oled_write(wpm_str, /*invert=*/false);

        update_timeout = timer_read32() + UPDATE_INTERVAL_MILLIS;
    }
}
