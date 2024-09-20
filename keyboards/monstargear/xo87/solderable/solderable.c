/* Copyright 2021 datafx
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

#include "solderable.h"

#define noLed {255,255}

#define ledSollSP (80+3)
#define ledNumSP (80+7)
#define ledCapSP (80+8)

void backlight_init_ports(void) {
    gpio_set_pin_output(Lseg0);
    gpio_set_pin_output(Lseg1);
    gpio_set_pin_output(Lseg2);
    gpio_set_pin_output(Lseg3);
    gpio_set_pin_output(Lseg4);
    gpio_set_pin_output(Lseg5);
    gpio_set_pin_output(Lcom0);
    gpio_set_pin_output(Lcom1);
    gpio_set_pin_output(Lcom2);
    gpio_set_pin_output(Lcom3);
    gpio_set_pin_output(Lcom4);
    gpio_set_pin_output(Lcom5);
    gpio_set_pin_output(Lcom6);
    gpio_set_pin_output(Lcom7);
    gpio_set_pin_output(Lcom8);
    gpio_set_pin_output(Lcom9);
    gpio_set_pin_output(Lcom10);
    gpio_set_pin_output(Lcom11);
    gpio_set_pin_output(Lcom12);
    gpio_set_pin_output(Lcom13);
    gpio_set_pin_output(Lcom14);
    gpio_set_pin_output(Lcom15);
}

void backlight_set(uint8_t level) {
}

void backlight_task(void) {
    // This is a temporary workaround to get the status LEDs working until we can figure out the LED matrix
    led_t host_leds = host_keyboard_led_state();
    if (host_leds.scroll_lock) {
    gpio_write_pin_high(Lcom3);
    gpio_write_pin_high(Lseg5);
    } else {
    gpio_write_pin_low(Lcom3);
    }
    if (host_leds.num_lock) {
    gpio_write_pin_high(Lcom7);
    gpio_write_pin_high(Lseg5);
    } else {
    gpio_write_pin_low(Lcom7);
    }
    if (host_leds.caps_lock) {
    gpio_write_pin_high(Lcom8);
    gpio_write_pin_high(Lseg5);
    } else {
    gpio_write_pin_low(Lcom8);
    }
}

