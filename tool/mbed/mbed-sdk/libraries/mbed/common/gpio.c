/* mbed Microcontroller Library
 * Copyright (c) 2006-2013 ARM Limited
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "gpio_api.h"

static inline void _gpio_init_in(gpio_t* gpio, PinName pin, PinMode mode)
{
    gpio_init(gpio, pin);
    if (pin != NC) {
        gpio_dir(gpio, PIN_INPUT);
        gpio_mode(gpio, mode);
    }
}

static inline void _gpio_init_out(gpio_t* gpio, PinName pin, PinMode mode, int value)
{
    gpio_init(gpio, pin);
    if (pin != NC) {
        gpio_write(gpio, value);
        gpio_dir(gpio, PIN_OUTPUT);
        gpio_mode(gpio, mode);
    }
}

void gpio_init_in(gpio_t* gpio, PinName pin) {
    gpio_init_in_ex(gpio, pin, PullDefault);
}

void gpio_init_in_ex(gpio_t* gpio, PinName pin, PinMode mode) {
    _gpio_init_in(gpio, pin, mode);
}

void gpio_init_out(gpio_t* gpio, PinName pin) {
    gpio_init_out_ex(gpio, pin, 0);
}

void gpio_init_out_ex(gpio_t* gpio, PinName pin, int value) {
    _gpio_init_out(gpio, pin, PullNone, value);
}

void gpio_init_inout(gpio_t* gpio, PinName pin, PinDirection direction, PinMode mode, int value) {
    if (direction == PIN_INPUT) {
        _gpio_init_in(gpio, pin, mode);
        if (pin != NC)
            gpio_write(gpio, value); // we prepare the value in case it is switched later
    } else {
        _gpio_init_out(gpio, pin, mode, value);
    }
}
