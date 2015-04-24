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
    pin_function(pin, 1);
    return 1 << ((pin & 0x7F) >> 2);
}

void gpio_init(gpio_t *obj, PinName pin) {
    obj->pin = pin;
    if (pin == (PinName)NC)
        return;

    obj->mask = gpio_set(pin);

    unsigned int port = (unsigned int)pin >> PORT_SHIFT;

#if defined(TARGET_KL43Z)
    GPIO_Type *reg = (GPIO_Type *)(GPIOA_BASE + port * 0x40);
#else
    FGPIO_Type *reg = (FGPIO_Type *)(FPTA_BASE + port * 0x40);
#endif
    obj->reg_set = &reg->PSOR;
    obj->reg_clr = &reg->PCOR;
    obj->reg_in  = &reg->PDIR;
    obj->reg_dir = &reg->PDDR;
}

void gpio_mode(gpio_t *obj, PinMode mode) {
    pin_mode(obj->pin, mode);
}

void gpio_dir(gpio_t *obj, PinDirection direction) {
    MBED_ASSERT(obj->pin != (PinName)NC);
    switch (direction) {
        case PIN_INPUT :
            *obj->reg_dir &= ~obj->mask;
            break;
        case PIN_OUTPUT:
            *obj->reg_dir |=  obj->mask;
            break;
    }
}
