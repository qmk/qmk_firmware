/**
 * @file nico.c
 *
    Copyright 2023 astro

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

#include "quantum.h"
#include "ws2812.h"
#ifdef RGBLIGHT_ENABLE

static bool alert = false;
static bool backup = false;
static rgb_led_t caps_led;
static uint16_t last_ticks = 0;

#define ALERT_INTERVAL      500
#define ALERM_LED_R     0xFF
#define ALERM_LED_G     0xA5
#define ALERM_LED_B     0x00
//golden 0xFF, 0xD9, 0x00

void housekeeping_task_kb(void)
{
    if (host_keyboard_led_state().caps_lock) {
        if (!backup) {
            caps_led.r = led[4].r;
            caps_led.g = led[4].g;
            caps_led.b = led[4].b;
            backup = true;
        }
        if(alert) {
            led[4].r = ALERM_LED_G;
            led[4].g = ALERM_LED_R;
            led[4].b = ALERM_LED_B;
        } else {
            led[4].r = 0;
            led[4].g = 0;
            led[4].b = 0;
        }
        if (timer_elapsed(last_ticks) > ALERT_INTERVAL) {
            alert = !alert;
            last_ticks = timer_read();
        }
        ws2812_setleds(led, RGBLIGHT_LED_COUNT);
    } else {
        if (backup) {
            led[4].r = caps_led.r;
            led[4].g = caps_led.g;
            led[4].b = caps_led.b;
            backup = false;
            ws2812_setleds(led, RGBLIGHT_LED_COUNT);
        }
    }
    housekeeping_task_user();
}

void setleds_custom(rgb_led_t *start_led, uint16_t num_leds)
{
    start_led[2].r = start_led[0].r;
    start_led[2].g = start_led[0].g;
    start_led[2].b = start_led[0].b;

    start_led[3].r = start_led[1].r;
    start_led[3].g = start_led[1].g;
    start_led[3].b = start_led[1].b;

    uint8_t tmp = start_led[4].g;
    start_led[4].g = start_led[4].r;
    start_led[4].r = tmp;
    ws2812_setleds(start_led, RGBLIGHT_LED_COUNT);
}

const rgblight_driver_t rgblight_driver = {
    .setleds = setleds_custom,
};
#endif