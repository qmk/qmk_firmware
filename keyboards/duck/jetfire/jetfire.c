/* Copyright 2018 MechMerlin
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
#include "jetfire.h"
#include "indicator_leds.h"

enum BACKLIGHT_AREAS {
    BACKLIGHT_ALPHA    = 0b0000001,
    BACKLIGHT_MOD      = 0b0000010,
    BACKLIGHT_FROW     = 0b0000100,
    BACKLIGHT_NUMBLOCK = 0b0001000,
    BACKLIGHT_RGB      = 0b0010000,
    BACKLIGHT_SWITCH   = 0b0001111
};

enum StateLed {
    STATE_LED_SCROLL_LOCK,
    STATE_LED_CAPS_LOCK,
    STATE_LED_NUM_LOCK,
    STATE_LED_LAYER_0,
    STATE_LED_LAYER_1,
    STATE_LED_LAYER_2,
    STATE_LED_LAYER_3,
    STATE_LED_LAYER_4
};

uint8_t backlight_rgb_r = 255;
uint8_t backlight_rgb_g = 0;
uint8_t backlight_rgb_b = 0;
uint8_t backlight_state_led = 1<<STATE_LED_LAYER_0;


void backlight_toggle_rgb(bool enabled)
{
  uint8_t rgb[RGBLED_NUM][3] = { 0 };

  if(enabled) {
    for(uint8_t i = 0; i < RGBLED_NUM; ++i) {
      rgb[i][0] = backlight_rgb_r;
      rgb[i][1] = backlight_rgb_g;
      rgb[i][2] = backlight_rgb_b;
    }
  }
  backlight_set_rgb(rgb);
}

void backlight_set_rgb(uint8_t cfg[RGBLED_NUM][3])
{
  cli();
  for(uint8_t i = 0; i < RGBLED_NUM; ++i) {
    send_color(cfg[i][0], cfg[i][1], cfg[i][2], Device_PCBRGB);
  }
  sei();
  show();
}


void backlight_set(uint8_t level)
{
  level & BACKLIGHT_ALPHA    ? (PORTB |= 0b00000010) : (PORTB &= ~0b00000010);
  level & BACKLIGHT_MOD      ? (PORTB |= 0b00000100) : (PORTB &= ~0b00000100);
  level & BACKLIGHT_FROW     ? (PORTB |= 0b00001000) : (PORTB &= ~0b00001000);
  level & BACKLIGHT_NUMBLOCK ? (PORTE |= 0b01000000) : (PORTE &= ~0b01000000);
  backlight_toggle_rgb(level & BACKLIGHT_RGB);
}

void backlight_update_state()
{
  cli();
  send_color(backlight_state_led & (1<<STATE_LED_SCROLL_LOCK) ? 255 : 0,
             backlight_state_led & (1<<STATE_LED_CAPS_LOCK) ? 255 : 0,
             backlight_state_led & (1<<STATE_LED_NUM_LOCK) ? 255 : 0,
             Device_STATUSLED);
  send_color(backlight_state_led & (1<<STATE_LED_LAYER_1) ? 255 : 0,
             backlight_state_led & (1<<STATE_LED_LAYER_2) ? 255 : 0,
             backlight_state_led & (1<<STATE_LED_LAYER_0) ? 255 : 0,
             Device_STATUSLED);
  send_color(backlight_state_led & (1<<STATE_LED_LAYER_4) ? 255 : 0,
             backlight_state_led & (1<<STATE_LED_LAYER_3) ? 255 : 0,
             0,
             Device_STATUSLED);
  sei();
  show();
}

void led_set_kb(uint8_t usb_led)
{
  if(usb_led & (1<<USB_LED_CAPS_LOCK)) {
    backlight_state_led |=   1<<STATE_LED_CAPS_LOCK;
  } else {
    backlight_state_led &= ~(1<<STATE_LED_CAPS_LOCK);
  }
  if(usb_led & (1<<USB_LED_SCROLL_LOCK)) {
    backlight_state_led |=   1<<STATE_LED_SCROLL_LOCK;
  } else {
    backlight_state_led &= ~(1<<STATE_LED_SCROLL_LOCK);
  }
  if(usb_led & (1<<USB_LED_NUM_LOCK)) {
    backlight_state_led |=   1<<STATE_LED_NUM_LOCK;
  } else {
    backlight_state_led &= ~(1<<STATE_LED_NUM_LOCK);
  }
  backlight_update_state();
}
