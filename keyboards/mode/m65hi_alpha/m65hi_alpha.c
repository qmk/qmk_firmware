/*
 Copyright 2020 Álvaro "Gondolindrim" Volpato <alvaro.volpato@usp.br>

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

#include "quantum.h"

void board_init(void) {
    setPinInput(B10);
}

void led_init_ports(void) {

/** If the OPENDRAIN_INDICATORS option is not defined in config.h, the indicator
    pins default to push-pull output. Else, they are defined as open-drain. The
    pin mode configuration is done through the INDICATOR_PIN_MODE which is
    attributed right at the beggining. **/

#ifndef OPENDRAIN_INDICATORS
#    define INDICATOR_PIN_MODE PAL_MODE_OUTPUT_PUSHPULL
#else
#    define INDICATOR_PIN_MODE PAL_MODE_OUTPUT_OPENDRAIN
#endif

#ifdef LED_NUM_LOCK_PIN
    palSetLineMode(LED_NUM_LOCK_PIN, INDICATOR_PIN_MODE);
#endif
#ifdef LED_CAPS_LOCK_PIN
    palSetLineMode(LED_CAPS_LOCK_PIN, INDICATOR_PIN_MODE);
#endif
#ifdef LED_SCROLL_LOCK_PIN
    palSetLineMode(LED_SCROLL_LOCK_PIN, INDICATOR_PIN_MODE);
#endif
#ifdef LED_COMPOSE_PIN
    palSetLineMode(LED_COMPOSE_PIN, INDICATOR_PIN_MODE);
#endif
#ifdef LED_KANA_PIN
    palSetLineMode(LED_KANA_PIN, INDICATOR_PIN_MODE);
#endif
}

bool led_update_kb(led_t led_state) {
    bool res = led_update_user(led_state);
    if(res) {
        // writePin sets the pin high for 1 and low for 0.
        // In this example the pins are inverted, setting
        // it low/0 turns it on, and high/1 turns the LED off.
        // This behavior depends on whether the LED is between the pin
        // and VCC or the pin and GND.
        writePin(LED_CAPS_LOCK_PIN, !led_state.caps_lock);
    }
    return res;
}
