/*
Copyright 2016 Ralf Schmitt <ralf@bunkertor.net>

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

#include <util/delay.h>
#include <stdint.h>
#include <stdbool.h>
#include "led.h"
#include "led_l3.h"
#include "config.h"
#include "tinycmd/tinycmdapi.h"

uint8_t led_mode = LED_EFFECT_ALWAYS;
uint8_t rgb_effect_index = 0;

void led_set(uint8_t usb_led)
{
  tinycmd_three_lock(usb_led & (1<<USB_LED_NUM_LOCK),
                     usb_led & (1<<USB_LED_CAPS_LOCK),
                     usb_led & (1<<USB_LED_SCROLL_LOCK),
                     false);
}

void rgb_off(void)
{
#ifndef RGB_LEDS_NOT_SOLDERED
  tinycmd_rgb_all(0, 0, 0, 0, true);
#endif
}

void rgb_on(void)
{
#ifndef RGB_LEDS_NOT_SOLDERED
  tinycmd_rgb_all(1, 0, 0, 250, true);
#endif
}

void led_off(void)
{
  uint8_t led_preset[3][5] = {{LED_EFFECT_OFF, LED_EFFECT_OFF, LED_EFFECT_OFF, LED_EFFECT_OFF, LED_EFFECT_OFF},
                              {LED_EFFECT_OFF, LED_EFFECT_OFF, LED_EFFECT_OFF, LED_EFFECT_OFF, LED_EFFECT_OFF},
                              {LED_EFFECT_OFF, LED_EFFECT_OFF, LED_EFFECT_OFF, LED_EFFECT_OFF, LED_EFFECT_OFF}};
  tinycmd_led_config_preset((uint8_t*)led_preset, true);
}

void led_on(void)
{
  uint8_t led_preset[3][5] = {{LED_EFFECT_NONE, LED_EFFECT_NONE, LED_EFFECT_NONE, led_mode, LED_EFFECT_NONE},
                              {LED_EFFECT_NONE, LED_EFFECT_NONE, LED_EFFECT_NONE, LED_EFFECT_NONE, LED_EFFECT_NONE},
                              {LED_EFFECT_NONE, LED_EFFECT_NONE, LED_EFFECT_NONE, LED_EFFECT_NONE, LED_EFFECT_NONE}};
  tinycmd_led_config_preset((uint8_t*)led_preset, true);
}

void led_change_mode(void)
{
  if(led_mode == LED_EFFECT_ALWAYS) {
    led_mode = LED_EFFECT_FADING;
  } else if(led_mode == LED_EFFECT_FADING) {
    led_mode = LED_EFFECT_BASECAPS;
  } else if(led_mode == LED_EFFECT_BASECAPS) {
    led_mode = LED_EFFECT_NONE;
  } else if(led_mode == LED_EFFECT_NONE) {
    led_mode = LED_EFFECT_ALWAYS;
  }
  led_on();
}

void led_speed(void)
{
#ifndef RGB_LEDS_NOT_SOLDERED
  tinycmd_rgb_effect_speed(300, true);
#endif
}

void led_rgb_preset(void)
{
#ifndef RGB_LEDS_NOT_SOLDERED
  uint8_t rgb_effect_param[6][4] = {{ RGB_EFFECT_BOOTHID, 0, 0, 0 },
                                    { RGB_EFFECT_FADE_BUF, FADE_HIGH_HOLD, FADE_LOW_HOLD, FADE_IN_ACCEL },
                                    { RGB_EFFECT_FADE_LOOP, FADE_HIGH_HOLD, FADE_LOW_HOLD, FADE_IN_ACCEL },
                                    { RGB_EFFECT_HEARTBEAT_BUF, HEARTBEAT_HIGH_HOLD, HEARTBEAT_LOW_HOLD, HEARTBEAT_IN_ACCEL },
                                    { RGB_EFFECT_HEARTBEAT_LOOP, HEARTBEAT_HIGH_HOLD, HEARTBEAT_LOW_HOLD, HEARTBEAT_IN_ACCEL },
                                    { RGB_EFFECT_BASIC, HEARTBEAT_HIGH_HOLD, HEARTBEAT_LOW_HOLD, HEARTBEAT_IN_ACCEL }};
  tinycmd_rgb_set_preset(rgb_effect_index, (rgb_effect_param_type *)&rgb_effect_param[rgb_effect_index], true);
#endif
}

void rgb_change_mode(void)
{
  /* rgb_effect_index = (rgb_effect_index + 1) % 6; */
  rgb_effect_index++;
  if(rgb_effect_index == 6) {
    rgb_effect_index = 0;
  }
  led_rgb_preset();
}

void backlight_set(uint8_t level)
{
  if(level & BACKLIGHT_PCB) {
    rgb_on();
    led_rgb_preset();
  } else {
    rgb_off();
  }
  if(level & BACKLIGHT_SWITCH) {
    led_on();
  } else {
    led_off();
  }
}
