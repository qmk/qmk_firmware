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
#include "port_api.h"
#include "pinmap.h"
#include "gpio_api.h"

#if DEVICE_PORTIN || DEVICE_PORTOUT

PinName port_pin(PortName port, int pin_n) {
    return pin_n + (port << 4);
}

void port_init(port_t *obj, PortName port, int mask, PinDirection dir) {
    obj->port = port;
    obj->mask = mask;

    uint32_t port_index = (uint32_t) port;

    GPIO_TypeDef *port_reg = (GPIO_TypeDef *)(GPIOA_BASE + (port_index << 10));
    // Enable GPIO peripheral clock
    RCC->AHB1ENR |= 1 << port_index;

    obj->reg_mode = &port_reg->MODER;
    obj->reg_set = &port_reg->BSRRH;
    obj->reg_clr = &port_reg->BSRRL;
    obj->reg_in  = &port_reg->IDR;
    obj->reg_out  = &port_reg->ODR;

    port_dir(obj, dir);
}

void port_mode(port_t *obj, PinMode mode) {
    uint32_t i;
    // The mode is set per pin: reuse pinmap logic
    for (i=0; i<16; i++) {
        if (obj->mask & (1<<i)) {
            pin_mode(port_pin(obj->port, i), mode);
        }
    }
}

void port_dir(port_t *obj, PinDirection dir) {
    obj->direction = dir;
    uint32_t tmp = *obj->reg_mode;
    for (int i=0; i<16; i++) {
        if (obj->mask & (1 << i)) {
            // Clear the mode bits (i.e. set to input)
            tmp &= ~(0x3 << (i << 1));
            if (dir == PIN_OUTPUT) {
                // Set to output
                tmp |= 0x1 << (i << 1);
            }
        }
    }
    *obj->reg_mode = tmp;
}

void port_write(port_t *obj, int value) {
    *obj->reg_out = (*obj->reg_out & ~obj->mask) | (value & obj->mask);
}

int port_read(port_t *obj) {
    switch (obj->direction) {
        case PIN_OUTPUT: return *obj->reg_out & obj->mask;
        case PIN_INPUT: return *obj->reg_in & obj->mask;
    }
    return 0;
}

#endif
