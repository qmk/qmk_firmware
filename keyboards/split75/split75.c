/*
Copyright 2017 Luiz Ribeiro <luizribeiro@gmail.com>

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

#include "split75.h"
#include "rgblight.h"

#include <avr/pgmspace.h>
#include <i2c_master.h>

#include "action_layer.h"

#define I2C_TIMEOUT     10

#define LED_INDICATORS

// Use the backlight as caps lock indicator?
// Best used if you only solder an LED under caps lock
#define BL_AS_CAPSLOCK 

uint8_t led0 = 0, led1 = 0, led2 = 0;

void indicator_init(void) {
    // D0, D1, and D6 are the indicators and D4 is the backlight
    DDRD |= 0x53;
    PORTD |= 0x53;
}

// for keyboard subdirectory level init functions
// @Override
void matrix_init_kb(void) {
  // call user level keymaps, if any
  matrix_init_user();
}

#ifdef RGBLIGHT_ENABLE
extern rgblight_config_t rgblight_config;

// custom RGB driver
void rgblight_set(void) {
  if (!rgblight_config.enable) {
    for (uint8_t i=0; i<RGBLED_NUM; i++) {
      led[i].r = 0;
      led[i].g = 0;
      led[i].b = 0;
    }
  }

  i2c_transmit(0xb0, (uint8_t*)led, 3 * RGBLED_NUM, I2C_TIMEOUT);
}

bool rgb_init = false;

void matrix_scan_kb(void) {
  // if LEDs were previously on before poweroff, turn them back on
  if (rgb_init == false && rgblight_config.enable) {
    i2c_transmit(0xb0, (uint8_t*)led, 3 * RGBLED_NUM, I2C_TIMEOUT);
    rgb_init = true;
  }

  rgblight_task();
#else

void matrix_scan_kb(void) {
#endif
  matrix_scan_user();
  /* Nothing else for now. */
}

__attribute__((weak)) // overridable
void matrix_init_user(void) {

}

void keyboard_post_init_user(void) {
  // Customise these values to desired behaviour
  //debug_keyboard=true;
  //debug_mouse=true;
  led_set_user(0);
}

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {
};

#if defined(LED_INDICATORS)
void led_set_user(uint8_t usb_led) {
  if (IS_LED_ON(usb_led, USB_LED_NUM_LOCK)) {
    writePinHigh(D0);
  }
  else {
    writePinLow(D0);
  }

  if (IS_LED_ON(usb_led, USB_LED_CAPS_LOCK)) {
    writePinHigh(D1);
#if defined(BL_AS_CAPSLOCK)
    writePinHigh(D4);
#endif
  }
  else {
    writePinLow(D1);
#if defined(BL_AS_CAPSLOCK)
    writePinLow(D4);
#endif
  }

  if (IS_LED_ON(usb_led, USB_LED_SCROLL_LOCK)) {
    writePinHigh(D6);
  }
  else {
    writePinLow(D6);
  }
	
}
#endif