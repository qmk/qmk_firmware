/* Copyright 2023 Cutie Club

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "indicator_leds.h"

#include "lib/i2c_helpers.h"
#include "lib/pcal6416a/pcal6416a.h"

#include "quantum.h"
#include "quantum/rgblight/rgblight.h"

static const pcal_gpio_pin led_pins[]     = LED_PCAL_PINS;
static const uint8_t       led_pins_count = sizeof(led_pins) / sizeof(pcal_gpio_pin);

static enum indicator_key enabled_indicator_key;

int indicator_leds_init(void) {
    RETURN_IF_I2C_FAIL(set_pin_array_initial_state(led_pins, led_pins_count, LOW), -1);
    return 0;
}

bool led_update_kb(led_t led_state) {
    bool res = led_update_user(led_state);
    if (res) {
        if ((led_state.num_lock && enabled_indicator_key == NUM_LOCK) || (led_state.scroll_lock && enabled_indicator_key == SCROLL_LOCK) || (led_state.caps_lock && enabled_indicator_key == CAPS_LOCK)) {
            set_pin_array_state(led_pins, led_pins_count, HIGH);
            rgblight_enable_noeeprom();
        } else {
            set_pin_array_state(led_pins, led_pins_count, LOW);
            rgblight_disable_noeeprom();
        }
    }

    return res;
}

void set_enabled_indicator_key(enum indicator_key key) {
    enabled_indicator_key = key;
    led_update_kb(host_keyboard_led_state()); // re-set the indicator keys to match new state
}

enum indicator_key get_enabled_indicator_key(void) {
    return enabled_indicator_key;
}
