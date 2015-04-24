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

#if DEVICE_PORTIN || DEVICE_PORTOUT

#include "pinmap.h"
#include "gpio_api.h"

PinName port_pin(PortName port, int pin_n) {
    return (PinName)((port << GPIO_PORT_SHIFT) | pin_n);
}

void port_init(port_t *obj, PortName port, int mask, PinDirection dir) {
    obj->port = port;
    obj->mask = mask;

    // The function is set per pin: reuse gpio logic
    for (uint32_t i = 0; i < 32; i++) {
        if (obj->mask & (1 << i)) {
            gpio_set(port_pin(obj->port, i));
        }
    }

    port_dir(obj, dir);
}

void port_mode(port_t *obj, PinMode mode) {

    // The mode is set per pin: reuse pinmap logic
    for (uint32_t i = 0; i < 32; i++) {
        if (obj->mask & (1 << i)) {
            pin_mode(port_pin(obj->port, i), mode);
        }
    }
}

void port_dir(port_t *obj, PinDirection dir) {
    uint32_t port_addrs[] = PORT_BASE_ADDRS;
    uint32_t direction = GPIO_HAL_GetPortDir(port_addrs[obj->port]);
    switch (dir) {
        case PIN_INPUT :
            direction &= ~obj->mask;
            GPIO_HAL_SetPortDir(port_addrs[obj->port], direction);
            break;
        case PIN_OUTPUT:
            direction |= obj->mask;
            GPIO_HAL_SetPortDir(port_addrs[obj->port], direction);
            break;
    }
}

void port_write(port_t *obj, int value) {
    uint32_t port_addrs[] = PORT_BASE_ADDRS;
    uint32_t input = GPIO_HAL_ReadPortInput(port_addrs[obj->port]) & ~obj->mask;
    GPIO_HAL_WritePortOutput(port_addrs[obj->port], input | (uint32_t)(value & obj->mask));
}

int port_read(port_t *obj) {
    uint32_t port_addrs[] = PORT_BASE_ADDRS;
    return (int)(GPIO_HAL_ReadPortInput(port_addrs[obj->port]) & obj->mask);
}

#endif
