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
#include "mbed_assert.h"
#include "gpio_api.h"
#include "pinmap.h"

uint32_t gpio_set(PinName pin) {
    MBED_ASSERT(pin != (PinName)NC);
    uint32_t port_index = (uint32_t) pin >> 4;

    // Enable GPIO peripheral clock
    RCC->AHB1ENR |= 1 << port_index;

    pin_function(pin, STM_PIN_DATA(0, 0));
    return 1 << ((uint32_t) pin & 0xF);
}

void gpio_init(gpio_t *obj, PinName pin) {
    obj->pin = pin;
    if (pin == (PinName)NC)
        return;

    obj->mask = gpio_set(pin);

    uint32_t port_index = (uint32_t) pin >> 4;
    
    GPIO_TypeDef *port_reg = (GPIO_TypeDef *) (GPIOA_BASE + (port_index << 10));
    obj->reg_mode = &port_reg->MODER;
    obj->reg_set = &port_reg->BSRRL;
    obj->reg_clr = &port_reg->BSRRH;
    obj->reg_in  = &port_reg->IDR;
}

void gpio_mode(gpio_t *obj, PinMode mode) {
    pin_mode(obj->pin, mode);
}

void gpio_dir(gpio_t *obj, PinDirection direction) {
    MBED_ASSERT(obj->pin != (PinName)NC);
    switch (direction) {
        case PIN_INPUT :
            pin_function(obj->pin, STM_PIN_DATA(0, 0));
            break;
        case PIN_OUTPUT:
            pin_function(obj->pin, STM_PIN_DATA(1, 0));
            break;
    }
}
