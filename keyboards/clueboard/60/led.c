/*
 * Copyright 2017 skully <skullydazed@gmail.com>
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

#include "hal.h"
#include "backlight.h"
#include "led.h"
#include "printf.h"

void backlight_init_ports(void) {
    printf("backlight_init_ports()\n");
    #ifdef BACKLIGHT_ENABLE
    palSetPadMode(GPIOB, 8, PAL_MODE_OUTPUT_PUSHPULL);
    palSetPad(GPIOB, 8);
    #endif
}

void backlight_set(uint8_t level) {
    printf("backlight_set(%d)\n", level);
    #ifdef BACKLIGHT_ENABLE
    if (level == 0) {
        // Turn backlight off
        palSetPad(GPIOB, 8);
    } else {
        // Turn backlight on
        palClearPad(GPIOB, 8);
    }
    #endif
}

void led_set_kb(uint8_t usb_led) {
    printf("led_set_kb(%d)\n", usb_led);
    if (usb_led & (1<<USB_LED_CAPS_LOCK)) {
        // Turn capslock on
        palSetPad(GPIOB, 7);
    } else {
        // Turn capslock off
        palClearPad(GPIOB, 7);
    }
}
