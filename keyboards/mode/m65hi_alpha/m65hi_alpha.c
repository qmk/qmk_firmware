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

#include "m65hi_alpha.h"

void board_init(void) {
    setPinInput(B9);
    setPinInput(B10);
}

#define LED_PIN_ON_STATE 1
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

uint8_t prng(void) {
    static uint8_t s = 0xAA, a = 0;
    s ^= s << 3;
    s ^= s >> 5;
    s ^= a++ >> 2;
    return s;
}

void keyboard_post_init_user(void) {
    // Customise these values to desired behaviour
    debug_enable = true;
    // debug_matrix = true;
    // debug_keyboard=true;
    // debug_mouse=true;
}

void matrix_scan_user(void) {
    static uint32_t last_eeprom_access = 0;
    uint32_t        now                = timer_read32();
    if (now - last_eeprom_access > 5000) {
        dprint("reading eeprom\n");
        last_eeprom_access = now;

        union {
            uint8_t  bytes[4];
            uint32_t raw;
        } tmp;
        tmp.bytes[0] = prng();
        tmp.bytes[1] = prng();
        tmp.bytes[2] = prng();
        tmp.bytes[3] = prng();

        eeconfig_update_user(tmp.raw);
        uint32_t value = eeconfig_read_user();
        if (value != tmp.raw) {
            dprint("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
            dprint("!! EEPROM readback mismatch!\n");
            dprint("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
        }
    }
}
