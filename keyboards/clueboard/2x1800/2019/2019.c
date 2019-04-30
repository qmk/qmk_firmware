/* Copyright 2017 Zach White <skullydazed@gmail.com>
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
#include "2019.h"
#include "encoder.h"

void matrix_init_kb(void) {
    // Set our LED pins as output
    setPinOutput(B4);
    setPinOutput(B5);
    setPinOutput(B6);

    // Set our Tilt Sensor pins as input
    setPinInputHigh(SHAKE_PIN_A);
    setPinInputHigh(SHAKE_PIN_B);

    // Run the keymap level init
    matrix_init_user();
}

#ifdef SHAKE_ENABLE
uint8_t tilt_state[2] = {1,1};
uint8_t detected_shakes = 0;
static uint16_t shake_timer;
#endif

void matrix_scan_kb(void) {
#ifdef SHAKE_ENABLE
    // Read the current state of the tilt sensor. It is physically
    // impossible for both pins to register a low state at the same time.
    uint8_t tilt_read[2] = {readPin(SHAKE_PIN_A), readPin(SHAKE_PIN_B)};

    // Check to see if the tilt sensor has changed state since our last read
    for (uint8_t i = 0; i < 2; i++) {
        if (tilt_state[i] != tilt_read[i]) {
            shake_timer = timer_read();
            detected_shakes++;
            tilt_state[i] = tilt_read[i];
        }
    }

    if ((detected_shakes > 0) && (timer_elapsed(shake_timer) > SHAKE_TIMEOUT)) {
        if (detected_shakes > SHAKE_COUNT) {
            dprintf("Shake detected! We had %d shakes detected.\n", detected_shakes);
            tap_code16(SHAKE_KEY);
        }
        detected_shakes = 0;
    }
#endif

    matrix_scan_user();
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    return process_record_user(keycode, record);
}

void led_set_kb(uint8_t usb_led) {
    // Toggle numlock as needed
    if (usb_led & (1<<USB_LED_NUM_LOCK)) {
        writePinHigh(B4);
    } else {
        writePinLow(B4);
    }

    // Toggle capslock as needed
    if (usb_led & (1<<USB_LED_CAPS_LOCK)) {
        writePinHigh(B5);
    } else {
        writePinLow(B5);
    }

    // Toggle scrolllock as needed
    if (usb_led & (1<<USB_LED_SCROLL_LOCK)) {
        writePinHigh(B6);
    } else {
        writePinLow(B6);
    }
}

bool encoder_update_keymap(int8_t index, bool clockwise) {
    return false;
}

void encoder_update_kb(int8_t index, bool clockwise) {
    if (!encoder_update_keymap(index, clockwise)) {
        // Encoder 1, outside left
        if (index == 0 && clockwise) {
            tap_code(KC_MS_U);  // turned right
        } else if (index == 0) {
            tap_code(KC_MS_D);  // turned left
        }

        // Encoder 2, inside left
        else if (index == 1 && clockwise) {
            tap_code(KC_WH_D);  // turned right
        } else if (index == 1) {
            tap_code(KC_WH_U);  // turned left
        }

        // Encoder 3, inside right
        else if (index == 2 && clockwise) {
            tap_code(KC_VOLU);  // turned right
        } else if (index == 2) {
            tap_code(KC_VOLD);  // turned left
        }

        // Encoder 4, outside right
        else if (index == 3 && clockwise) {
            tap_code(KC_MS_R);   // turned right
        } else if (index == 3) {
            tap_code(KC_MS_L);   // turned left
        }
    }
}
