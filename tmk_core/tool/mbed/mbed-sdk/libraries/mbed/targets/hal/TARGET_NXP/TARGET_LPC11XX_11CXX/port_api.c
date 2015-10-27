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

// LPC114 IOCON offset table [port][pin]

static uint8_t iocon_offset[4][12] = {
    {0x0c,0x10,0x1c,0x2c,0x30,0x34,0x4c,0x50,0x60,0x64,0x68,0x74}, // PORT 0
    {0x78,0x7c,0x80,0x90,0x94,0xa0,0xa4,0xa8,0x14,0x38,0x6c,0x98}, // PORT 1
    {0x08,0x28,0x5c,0x8c,0x40,0x44,0x00,0x20,0x24,0x54,0x58,0x70}, // PORT 2
    {0x84,0x88,0x9c,0xac,0x3c,0x48}                                // PORT 3
};

PinName port_pin(PortName port, int pin) {
    return (PinName)((port << PORT_SHIFT) | (pin << PIN_SHIFT) | (uint32_t)iocon_offset[port][pin]);
}

void port_init(port_t *obj, PortName port, int mask, PinDirection dir) {
    obj->port = port;
    obj->mask = mask;
    
    LPC_GPIO_TypeDef *port_reg = ((LPC_GPIO_TypeDef *) (LPC_GPIO0_BASE + (port * 0x10000)));
    
    obj->reg_data  = &port_reg->DATA;
    obj->reg_dir = &port_reg->DIR;
    
    uint32_t i;
    // The function is set per pin: reuse gpio logic
    for (i=0; i<12; i++) {
        if (obj->mask & (1<<i)) {
            gpio_set(port_pin(obj->port, i));
        }
    }
    
    port_dir(obj, dir);
}

void port_mode(port_t *obj, PinMode mode) {
    uint32_t i;
    // The mode is set per pin: reuse pinmap logic
    for (i=0; i<12; i++) {
        if (obj->mask & (1<<i)) {
            pin_mode(port_pin(obj->port, i), mode);
        }
    }
}

void port_dir(port_t *obj, PinDirection dir) {
    switch (dir) {
        case PIN_INPUT : *obj->reg_dir &= ~obj->mask; break;
        case PIN_OUTPUT: *obj->reg_dir |=  obj->mask; break;
    }
}

void port_write(port_t *obj, int value) {
    *obj->reg_data = (value & obj->mask);
}

int port_read(port_t *obj) {
    return (*obj->reg_data & obj->mask);
}

