/*
Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2013 Oleg Kostyuk <cub.uanic@gmail.com>
Copyright 2015 ZSA Technology Labs Inc (@zsa)
Copyright 2020 Christopher Courtney <drashna@live.com> (@drashna)

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

#include "ergodox_ez.h"
#include "ws2812.h"

#define WS2812_I2C_ADDRESS_LEFT 0x84

#if defined(ERGODOX_LED_30)
#    define WS2812_LED_COUNT_LEFT (RGBLIGHT_LED_COUNT / 2)
ws2812_led_t ws2812_leds_left[WS2812_LED_COUNT_LEFT];
#else
#    define WS2812_LED_COUNT_LEFT RGBLIGHT_LED_COUNT
ws2812_led_t ws2812_leds_left[WS2812_LED_COUNT_LEFT];
#endif

void set_color_left(int index, uint8_t red, uint8_t green, uint8_t blue) {
    ws2812_leds_left[index].r = red;
    ws2812_leds_left[index].g = green;
    ws2812_leds_left[index].b = blue;
#if defined(WS2812_RGBW)
    ws2812_rgb_to_rgbw(&ws2812_leds_left[index]);
#endif
}

void set_color_custom(int index, uint8_t red, uint8_t green, uint8_t blue) {
#if defined(ERGODOX_LED_30)
    if (index < WS2812_LED_COUNT_LEFT) {
        ws2812_set_color(index, red, green, blue);
    } else {
        set_color_left(RGBLIGHT_LED_COUNT - index - 1, red, green, blue);
    }
#elif defined(ERGODOX_LED_15_MIRROR)
    ws2812_set_color(index, red, green, blue);
    set_color_left(index, red, green, blue);
#else
    ws2812_set_color(index, red, green, blue);
    set_color_left(WS2812_LED_COUNT_LEFT - index - 1, red, green, blue);
#endif
}

void set_color_all_custom(uint8_t red, uint8_t green, uint8_t blue) {
    for (int i = 0; i < RGBLIGHT_LED_COUNT; i++) {
        set_color_custom(i, red, green, blue);
    }
}

void flush_custom(void) {
    i2c_transmit(WS2812_I2C_ADDRESS_LEFT, (uint8_t *)ws2812_leds_left, sizeof(ws2812_leds_left), ERGODOX_EZ_I2C_TIMEOUT);
    ws2812_flush();
}

const rgblight_driver_t rgblight_driver = {
    .init          = ws2812_init,
    .set_color     = set_color_custom,
    .set_color_all = set_color_all_custom,
    .flush         = flush_custom,
};
