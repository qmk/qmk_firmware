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

#ifdef RGBLIGHT_ENABLE

#    include "ergodox_ez.h"

void rgblight_call_driver(LED_TYPE *led, uint8_t led_num) {
    i2c_init();
    i2c_start(0x84, ERGODOX_EZ_I2C_TIMEOUT);
    int i = 0;
#    if defined(ERGODOX_LED_30)
    // prevent right-half code from trying to bitbang all 30
    // so with 30 LEDs, we count from 29 to 15 here, and the
    // other half does 0 to 14.
    uint8_t half_led_num = RGBLED_NUM / 2;
    for (i = half_led_num + half_led_num - 1; i >= half_led_num; --i)
#    elif defined(ERGODOX_LED_15_MIRROR)
    for (i = 0; i < led_num; ++i)
#    else  // ERGDOX_LED_15 non-mirrored
    for (i = led_num - 1; i >= 0; --i)
#    endif
    {
        uint8_t *data = (uint8_t *)(led + i);
        i2c_write(*data++, ERGODOX_EZ_I2C_TIMEOUT);
        i2c_write(*data++, ERGODOX_EZ_I2C_TIMEOUT);
        i2c_write(*data++, ERGODOX_EZ_I2C_TIMEOUT);
#ifdef RGBW
        i2c_write(*data++, ERGODOX_EZ_I2C_TIMEOUT);
#endif
    }
    i2c_stop();

    ws2812_setleds(led, led_num);
}


#endif  // RGBLIGHT_ENABLE
