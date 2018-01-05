/* Copyright 2017 MechMerlin <mechmerlin@gmail.com>
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
#include "v1.h"

enum BACKLIGHT_AREAS {
  BACKLIGHT_ALPHA    = 0b0000001,
  BACKLIGHT_EXTRA    = 0b0000010,
  BACKLIGHT_MODNUM   = 0b0000100,
  BACKLIGHT_FROW     = 0b0001000,
  BACKLIGHT_RGB      = 0b0010000,
  BACKLIGHT_RGBRED   = 0b0010000,
  BACKLIGHT_RGBGREEN = 0b0100000,
  BACKLIGHT_RGBBLUE  = 0b1000000,
  BACKLIGHT_SWITCH   = 0b0001111
};

uint8_t backlight_os_state = 0;
uint32_t backlight_layer_state = 0;

void backlight_set(uint8_t level) {
  level & BACKLIGHT_ALPHA ? (PORTB |= 0b00000010) : (PORTB &= ~0b00000010);
  level & BACKLIGHT_EXTRA ? (PORTB |= 0b00000100) : (PORTB &= ~0b00000100);
  level & BACKLIGHT_MODNUM ? (PORTB |= 0b00001000) : (PORTB &= ~0b00001000);
  level & BACKLIGHT_FROW ? (PORTE |= 0b01000000) : (PORTE &= ~0b01000000);
  level & BACKLIGHT_RGBRED ? (PORTD |= 0b01000000) : (PORTD &= ~0b01000000);
  level & BACKLIGHT_RGBGREEN ? (PORTD |= 0b10000000) : (PORTD &= ~0b10000000);
  level & BACKLIGHT_RGBBLUE ? (PORTD |= 0b00010000) : (PORTD &= ~0b00010000);
}

void led_set_kb(uint8_t usb_led) {
  backlight_os_state & (1<<USB_LED_CAPS_LOCK) ? (PORTB &= ~0b00000001) : (PORTB |= 0b00000001);
  backlight_os_state & (1<<USB_LED_SCROLL_LOCK) ? (PORTB &= ~0b00010000) : (PORTB |= 0b00010000);
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
  return process_record_user(keycode, record);
}
