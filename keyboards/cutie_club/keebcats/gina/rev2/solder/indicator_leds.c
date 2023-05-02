/*
Copyright 2023 Cutie Club

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
#include "pcal6416a/pcal6416a.h"

#include "quantum.h"
#include "i2c_master.h"

#ifndef NUM_LOCK_PCAL_PINS
#define NUM_LOCK_PCAL_PINS {}
#endif

#ifndef SCROLL_LOCK_PCAL_PINS
#define SCROLL_LOCK_PCAL_PINS {}
#endif

#ifndef CAPS_LOCK_PCAL_PINS
#define CAPS_LOCK_PCAL_PINS {}
#endif

static const pcal_gpio_pin num_lock_pins[] = NUM_LOCK_PCAL_PINS;
static const pcal_gpio_pin scroll_lock_pins[] = SCROLL_LOCK_PCAL_PINS;
static const pcal_gpio_pin caps_lock_pins[] = CAPS_LOCK_PCAL_PINS;

#define PIN_ARR_SIZE(ARR) (sizeof(ARR)/sizeof(pcal_gpio_pin))

int indicator_leds_init(void) {
    RETURN_IF_I2C_FAIL(set_pin_array_initial_state(num_lock_pins, PIN_ARR_SIZE(num_lock_pins), LOW), -1);
    RETURN_IF_I2C_FAIL(set_pin_array_initial_state(scroll_lock_pins, PIN_ARR_SIZE(scroll_lock_pins), LOW), -1);
    RETURN_IF_I2C_FAIL(set_pin_array_initial_state(caps_lock_pins, PIN_ARR_SIZE(caps_lock_pins), LOW), -1);
    return 0;
}

bool led_update_kb(led_t led_state) {
    bool res = led_update_user(led_state);
    if(res) {
        RETURN_IF_I2C_FAIL(set_pin_array_state(num_lock_pins, PIN_ARR_SIZE(num_lock_pins), led_state.num_lock), res);
        RETURN_IF_I2C_FAIL(set_pin_array_state(scroll_lock_pins, PIN_ARR_SIZE(scroll_lock_pins), led_state.scroll_lock), res);
        RETURN_IF_I2C_FAIL(set_pin_array_state(caps_lock_pins, PIN_ARR_SIZE(caps_lock_pins), led_state.caps_lock), res);
    }

    return res;
}
