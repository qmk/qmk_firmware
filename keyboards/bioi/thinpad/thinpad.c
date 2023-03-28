/* Copyright 2021 Basic I/O Instruments (Scott Wei)
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

#include "thinpad.h"
#include "action.h"
#include "quantum.h"

void led_set_kb(uint8_t usb_led) {
    if (IS_LED_ON(usb_led, USB_LED_CAPS_LOCK)) {
        writePinLow(F0);
    } else {
        writePinHigh(F0);
    }
    led_set_user(usb_led);
}

void keyboard_pre_init_kb(void) {
    setPinOutput(F0);
    writePinHigh(F0);
    keyboard_pre_init_user();
}

bool encoder_update_kb(uint8_t index, bool clockwise) {
    if (index == 0) { /* First encoder */
        if (clockwise) {
            action_exec((keyevent_t){.key = (keypos_t){.row = 0, .col = 0}, .pressed = 1, .time = 5});
            action_exec((keyevent_t){.key = (keypos_t){.row = 0, .col = 0}, .pressed = 0, .time = 5});
        } else {
            action_exec((keyevent_t){.key = (keypos_t){.row = 0, .col = 1}, .pressed = 1, .time = 5});
            action_exec((keyevent_t){.key = (keypos_t){.row = 0, .col = 1}, .pressed = 0, .time = 5});
        }
    } else if (index == 1) { /* Second encoder */
        if (clockwise) {
            action_exec((keyevent_t){.key = (keypos_t){.row = 2, .col = 3}, .pressed = 1, .time = 5});
            action_exec((keyevent_t){.key = (keypos_t){.row = 2, .col = 3}, .pressed = 0, .time = 5});
        } else {
            action_exec((keyevent_t){.key = (keypos_t){.row = 4, .col = 3}, .pressed = 1, .time = 5});
            action_exec((keyevent_t){.key = (keypos_t){.row = 4, .col = 3}, .pressed = 0, .time = 5});
        }
    }
    return encoder_update_user(index, clockwise);
}