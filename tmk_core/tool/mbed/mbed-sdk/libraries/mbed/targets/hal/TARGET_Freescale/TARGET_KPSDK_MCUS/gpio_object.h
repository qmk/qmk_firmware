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
#ifndef MBED_GPIO_OBJECT_H
#define MBED_GPIO_OBJECT_H

#include "mbed_assert.h"
#include "fsl_gpio_hal.h"
// #include "cmsis.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    PinName pin;
} gpio_t;

static inline void gpio_write(gpio_t *obj, int value) {
    MBED_ASSERT(obj->pin != (PinName)NC);
    uint32_t port = obj->pin >> GPIO_PORT_SHIFT;
    uint32_t pin = obj->pin & 0xFF;
    uint32_t gpio_addrs[] = GPIO_BASE_ADDRS;

    GPIO_HAL_WritePinOutput(gpio_addrs[port], pin, value);
}

static inline int gpio_read(gpio_t *obj) {
    MBED_ASSERT(obj->pin != (PinName)NC);
    uint32_t port = obj->pin >> GPIO_PORT_SHIFT;
    uint32_t pin = obj->pin & 0xFF;
    uint32_t gpio_addrs[] = GPIO_BASE_ADDRS;

    return (int)GPIO_HAL_ReadPinInput(gpio_addrs[port], pin);
}

static inline int gpio_is_connected(const gpio_t *obj) {
    return obj->pin != (PinName)NC;
}

#ifdef __cplusplus
}
#endif

#endif
