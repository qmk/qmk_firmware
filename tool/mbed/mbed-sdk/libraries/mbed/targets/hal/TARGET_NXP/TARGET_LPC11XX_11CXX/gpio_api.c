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
#include "reserved_pins.h"

static const PinName reserved_pins[] = TARGET_RESERVED_PINS;

uint32_t gpio_set(PinName pin) {
    MBED_ASSERT(pin != (PinName)NC);
    // PIO default value of following ports are not same as others
    unsigned i;
    int f = 0;

    for (i = 0; i < sizeof(reserved_pins) / sizeof(PinName); i ++) {
        if (pin == reserved_pins[i]) {
            f = 1;
            break;
        }
    }
    pin_function(pin, f);
    return ((pin & 0x0F00) >> 8);
}

void gpio_init(gpio_t *obj, PinName pin) {
    obj->pin = pin;
    if (pin == (PinName)NC)
        return;

    LPC_GPIO_TypeDef *port_reg = ((LPC_GPIO_TypeDef *) (LPC_GPIO0_BASE + (((pin & 0xF000) >> PORT_SHIFT) * 0x10000)));

    obj->reg_mask_read = &port_reg->MASKED_ACCESS[1 << gpio_set(pin)];
    obj->reg_dir       = &port_reg->DIR;
    obj->reg_write     = &port_reg->DATA;
}

void gpio_mode(gpio_t *obj, PinMode mode) {
    pin_mode(obj->pin, mode);
}

void gpio_dir(gpio_t *obj, PinDirection direction) {
    MBED_ASSERT(obj->pin != (PinName)NC);
    int pin_number = ((obj->pin & 0x0F00) >> 8);
    switch (direction) {
        case PIN_INPUT :
            *obj->reg_dir &= ~(1 << pin_number);
            break;
        case PIN_OUTPUT:
            *obj->reg_dir |= (1 << pin_number);
            break;
    }
}
