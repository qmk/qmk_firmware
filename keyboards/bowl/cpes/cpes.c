/* Copyright 2023 Gondolindrim <gondolindrim@acheronproject.com>
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
#include "ws2812.h"

// RGB indicators, in LED order: caps lock, num lock, scroll lock
#define INDICATOR_LEVEL 150

static void set_indicators(led_t led_state) {
    uint8_t caps   = led_state.caps_lock ? INDICATOR_LEVEL : 0;
    uint8_t num    = led_state.num_lock ? INDICATOR_LEVEL : 0;
    uint8_t scroll = led_state.scroll_lock ? INDICATOR_LEVEL : 0;
    ws2812_set_color(0, caps, caps, caps);
    ws2812_set_color(1, num, num, num);
    ws2812_set_color(2, scroll, scroll, scroll);
    ws2812_flush();
}

void keyboard_post_init_kb(void) {
    ws2812_init();
    set_indicators(host_keyboard_led_state());
    keyboard_post_init_user();
}

bool led_update_kb(led_t led_state) {
    bool res = led_update_user(led_state);
    if (res) {
        set_indicators(led_state);
    }
    return res;
}
