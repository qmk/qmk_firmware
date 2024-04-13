/* Copyright 2021 Jessica Sullivan and Don Kjer
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

#include "dgk6x.h"

/* Private Functions */
void off_all_leds(void) {
    writePinHigh(LED_CAPS_LOCK_PIN);
    writePinHigh(LED_WIN_LOCK_PIN);
    writePinHigh(LED_MR_LOCK_PIN);
}

void on_all_leds(void) {
    writePinLow(LED_CAPS_LOCK_PIN);
    writePinLow(LED_WIN_LOCK_PIN);
    writePinLow(LED_MR_LOCK_PIN);
}

/* WinLock and MR LEDs are non-standard. Need to override led init */
void led_init_ports(void) {
    setPinOutput(LED_CAPS_LOCK_PIN);
    setPinOutput(LED_WIN_LOCK_PIN);
    setPinOutput(LED_MR_LOCK_PIN);
    off_all_leds();
}


#ifndef WINLOCK_DISABLED
bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case GU_TOGG:
            if (record->event.pressed) {
                // Toggle LED on key press
                togglePin(LED_WIN_LOCK_PIN);
            }
            break;
    }
    return process_record_user(keycode, record);
}
#endif /* WINLOCK_DISABLED */

#ifdef RGB_MATRIX_ENABLE

bool rgb_matrix_indicators_kb(void) {
    if (!rgb_matrix_indicators_user()) {
        return false;
    }

    if (host_keyboard_led_state().caps_lock) {
        rgb_matrix_set_color(CAPS_LED, 0xFF, 0xFF, 0xFF);
    }
    return true;
}
#endif /* RGB_MATRIX_ENABLE */
