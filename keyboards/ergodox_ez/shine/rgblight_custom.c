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

void setleds_custom(rgb_led_t *led, uint16_t led_num) {
    uint16_t length = 0;
    int i = 0;
    int j = 0;
#    ifdef RGBW
    int bytes_per_led = 4;
#    else
    int bytes_per_led = 3;
#    endif
#    if defined(ERGODOX_LED_30)
    // prevent right-half code from trying to bitbang all 30
    // so with 30 LEDs, we count from 29 to 15 here, and the
    // other half does 0 to 14.
    uint8_t half_led_num = RGBLIGHT_LED_COUNT / 2;
    length = half_led_num * bytes_per_led;
    uint8_t data[length];
    for (i = half_led_num + half_led_num - 1; i >= half_led_num; --i)
#    elif defined(ERGODOX_LED_15_MIRROR)
    length = led_num * bytes_per_led;
    uint8_t data[length];
    for (i = 0; i < led_num; ++i)
#    else  // ERGDOX_LED_15 non-mirrored
    length = led_num * bytes_per_led;
    uint8_t data[length];
    for (i = led_num - 1; i >= 0; --i)
#    endif
    {
        uint8_t *data_byte = (uint8_t *)(led + i);
        data[j++] = data_byte[0];
        data[j++] = data_byte[1];
        data[j++] = data_byte[2];
#ifdef RGBW
        data[j++] = data_byte[3];
#endif
    }
    i2c_transmit(0x84, data, sizeof(data), ERGODOX_EZ_I2C_TIMEOUT);

    ws2812_setleds(led, led_num);
}

const rgblight_driver_t rgblight_driver = {
    .init    = ws2812_init,
    .setleds = setleds_custom,
};
