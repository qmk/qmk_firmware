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

#include "ps2avrGB.h"
#include "rgblight.h"

#include <avr/pgmspace.h>

#include "action_layer.h"
#include "i2c.h"
#include "quantum.h"

extern rgblight_config_t rgblight_config;

void rgblight_set(void) {
    uint8_t data[3 * RGBLED_NUM];
    for (uint8_t i = 0; i < RGBLED_NUM; i++) {
        if (rgblight_config.enable) {
            data[3 * i] = led[i].g;
            data[3 * i + 1] = led[i].r;
            data[3 * i + 2] = led[i].b;
        } else {
            data[3 * i] = 0;
            data[3 * i + 1] = 0;
            data[3 * i + 2] = 0;
        }
    }

    i2c_init();
    i2c_send(0xb0, data, 48);
}

__attribute__ ((weak))
void matrix_scan_user(void) {
    rgblight_task();
}
