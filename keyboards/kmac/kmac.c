/* Copyright 2017 Mathias Andersson <wraul@dbox.se>
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
#include "kmac.h"

void matrix_init_kb(void) {
    // put your keyboard start-up code here
    // runs once when the firmware starts up
    led_init_ports();
    matrix_init_user();
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

void led_init_ports(void) {
    DDRB |= (1<<0); // OUT
    DDRE |= (1<<6); // OUT
}

/* LED pin configuration
 * Scroll Lock: Low PE6
 * Caps Lock: Low PB0
 */
void led_set_kb(uint8_t usb_led) {
    if (usb_led & (1<<USB_LED_CAPS_LOCK))
    {
        PORTB &= ~(1<<0); // LO
    }
    else
    {
        PORTB |= (1<<0); // HI
    }

    if (usb_led & (1<<USB_LED_SCROLL_LOCK))
    {
        PORTE &= ~(1<<6); // LO
    }
    else
    {
        PORTE |= (1<<6); // HI
    }

    led_set_user(usb_led);
}

void backlight_init_ports(void) {
    DDRB |= (1<<1) | (1<<2) | (1<<3) | (1<<4); // OUT
    DDRD |= (1<<7); // OUT
}

/* Backlight pin configuration
 * F-row: High PB1
 * W: Low PB4
 * A: Low PB2
 * S: Low PB3
 * D: Low PD7
 */
void backlight_set(uint8_t level)
{
    // F-row
    if(level & (1<<0))
    {
        PORTB |= (1<<1); // HI
    }
    else
    {
        PORTB &= ~(1<<1); // LO
    }

    // WASD
    if(level & (1<<1))
    {
        PORTB &= ~(1<<4); // LO
        PORTB &= ~(1<<2); // LO
        PORTB &= ~(1<<3); // LO
        PORTD &= ~(1<<7); // LO
    }
    else
    {
        PORTB |= (1<<4); // HI
        PORTB |= (1<<2); // HI
        PORTB |= (1<<3); // HI
        PORTD |= (1<<7); // HI
    }
}
