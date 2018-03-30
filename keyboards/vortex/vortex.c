/*
 * Copyright (c) 2018 Jonathan A. Kollasch
 *           (c) 2018 Charlie Waters
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

#include "vortex.h"
#include "quantum.h"

#define BOOTLOADER_MAGIC 0x55aafaf5U

void bootloader_jump(void) {
    // SBVT registers are not reset on reset
    // SBVT1 is read by pok3r bootloader to stop booting
    FMC->SBVT[1] = BOOTLOADER_MAGIC;
    NVIC_SystemReset();
}

__attribute__ ((weak))
void matrix_init_user(void) {

}

void matrix_init_kb(void) {
    // put your keyboard start-up code here
    // runs once when the firmware starts up
//    *MAGIC_ADDR = BOOTLOADER_MAGIC - 5;

    matrix_init_user();
}

__attribute__ ((weak))
void matrix_scan_user(void) {

}

void matrix_scan_kb(void) {
    // put your looping keyboard code here
    // runs every cycle (a lot)

    matrix_scan_user();
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    // put your per-action keyboard code here
    // runs for every action, just before processing by the firmware

    return process_record_user(keycode, record);
}

void led_set_kb(uint8_t usb_led) {
    if ((usb_led >> USB_LED_CAPS_LOCK) & 1) {
        palClearLine(LINE_LED65);
    } else {
        palSetLine(LINE_LED65);
    }
    led_set_user(usb_led);
}
