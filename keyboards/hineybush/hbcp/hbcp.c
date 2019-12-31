/* Copyright 2019 Josh Hinnebusch
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
#include "hbcp.h"

// Indicator color definitions
#ifndef HSV_CAPS
    #define HSV_CAPS  0, 0, 120 // Define caps lock color (H, S, V)
#endif

#ifndef HSV_NLCK
    #define HSV_NLCK  0, 0, 120 // Define num lock color (H, S, V)
#endif

#ifndef HSV_SCRL
    #define HSV_SCRL  0, 0, 120 // Define scroll lock color (H, S, V)
#endif

#ifndef HSV_BLACK
    #define HSV_BLACK  0, 0, 0  // Define 'black' color, more like 'LED off' (H, S, V)
#endif

// #define HSV_custom_color H, S, V


// Optional override functions below.
// You can leave any or all of these undefined.
// These are only required if you want to perform custom actions.


void matrix_init_kb(void) {
  // put your keyboard start-up code here
  // runs once when the firmware starts up

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

void led_set_kb(uint8_t usb_led) {
  // put your keyboard LED indicator (ex: Caps Lock LED) toggling code here

  led_set_user(usb_led);
}

#ifdef RGBLIGHT_ENABLE

__attribute__ ((weak))
void led_set_user(uint8_t usb_led) {
    if (IS_LED_ON(usb_led, USB_LED_CAPS_LOCK)) {
        sethsv_raw(HSV_CAPS, (LED_TYPE *)&led[0]);
    } else {
        sethsv(HSV_BLACK, (LED_TYPE *)&led[0]);
    }
    if (IS_LED_ON(usb_led, USB_LED_NUM_LOCK)) {
        sethsv_raw(HSV_NLCK, (LED_TYPE *)&led[1]);
    } else {
        sethsv(HSV_BLACK, (LED_TYPE *)&led[1]);
    }
    if (IS_LED_ON(usb_led, USB_LED_SCROLL_LOCK)) {
        sethsv_raw(HSV_SCRL, (LED_TYPE *)&led[2]);
    } else {
        sethsv(HSV_BLACK, (LED_TYPE *)&led[2]);
    }
    rgblight_set();
}

__attribute__ ((weak))
void keyboard_post_init_user(void) {
    rgblight_set_effect_range(3, RGBLED_NUM-3);
    led_set_user(_BV(USB_LED_CAPS_LOCK)|_BV(USB_LED_NUM_LOCK)|_BV(USB_LED_SCROLL_LOCK));
    wait_ms(300);
    led_set_user(0);
}

__attribute__ ((weak))
void hbcp_sethsv_range(uint8_t hue, uint8_t sat, uint8_t val, uint8_t start, uint8_t end) {
  LED_TYPE tmp_led;
  sethsv_raw(hue, sat, val, &tmp_led);
  for (uint8_t i = start; i < end; i++) {
      led[i] = tmp_led;
  }
  rgblight_set();
}

#endif
