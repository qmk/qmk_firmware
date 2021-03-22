/*
Copyright 2021 Sekigon

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

#pragma once

#include "apidef.h"

typedef uint8_t                  pin_t;
static const bmp_api_gpio_mode_t bmp_gpio_in_pu = {
    .dir  = BMP_MODE_INPUT,
    .pull = BMP_PULLUP,
};
static const bmp_api_gpio_mode_t bmp_gpio_in_pd = {
    .dir  = BMP_MODE_INPUT,
    .pull = BMP_PULLDOWN,
};
static const bmp_api_gpio_mode_t bmp_gpio_out_pp = {.dir   = BMP_MODE_OUTPUT,
                                                    .pull  = BMP_PULL_NONE,
                                                    .drive = BMP_PIN_S0S1};
#define setPinInput(pin) BMPAPI->gpio.set_mode(pin, &bmp_gpio_in_pu)
#define setPinInputHigh(pin) BMPAPI->gpio.set_mode(pin, &bmp_gpio_in_pu)
#define setPinInputLow(pin) BMPAPI->gpio.set_mode(pin, &bmp_gpio_in_pd)
#define setPinOutput(pin) BMPAPI->gpio.set_mode(pin, &bmp_gpio_out_pp)
#define writePinHigh(pin) BMPAPI->gpio.set_pin(pin)
#define writePinLow(pin) BMPAPI->gpio.clear_pin(pin)
#define writePin(pin, level) ((level) ? writePinHigh(pin) : writePinLow(pin))

#define readPin(pin) BMPAPI->gpio.read_pin(pin)
