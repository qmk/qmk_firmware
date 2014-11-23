/*
Copyright 2014 Ralf Schmitt <ralf@bunkertor.net>

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

#include <avr/io.h>
#include "backlight.h"
#include "led.h"

void backlight_init_ports()
{
    DDRB |= 0b11100000; // PB7 (switch), PB6 (pcb), PB5 (caps)
}

void led_set(uint8_t usb_led)
{
    (usb_led & (1<<USB_LED_CAPS_LOCK)) ? backlight_caps_enable() : backlight_caps_disable();
}

void backlight_set(uint8_t level)
{
    (level & BACKLIGHT_SWITCH) ? backlight_switch_enable() : backlight_switch_disable();
    (level & BACKLIGHT_PCB) ? backlight_pcb_enable() : backlight_pcb_disable();
}

void backlight_switch_enable()
{
    PORTB |= 0b10000000;
}

void backlight_switch_disable()
{
    PORTB &= ~0b10000000;
}

void backlight_switch_invert()
{
    PORTB ^= 0b10000000;
}

void backlight_pcb_enable()
{
    PORTB |= 0b01000000;
}

void backlight_pcb_disable()
{
    PORTB &= ~0b01000000;
}

void backlight_pcb_invert()
{
    PORTB ^= 0b01000000;
}

void backlight_caps_enable()
{
    PORTB |= 0b00100000;
}

void backlight_caps_disable()
{
    PORTB &= ~0b00100000;
}

void backlight_caps_invert()
{
    PORTB ^= 0b00100000;
}
