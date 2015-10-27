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
#include "pinmap.h"
#include "mbed_error.h"

/**
 * Set the pin into input, output, alternate function or analog mode
 */
void pin_function(PinName pin, int data) {
    MBED_ASSERT(pin != (PinName)NC);
    
    int mode = STM_PIN_MODE(data);
    int func = STM_PIN_FUNC(data);
    
    uint32_t pin_number = (uint32_t)pin;
    int port_index = pin_number >> 4;
    int pin_index = (pin_number & 0xF);
    GPIO_TypeDef * gpio = ((GPIO_TypeDef *) (GPIOA_BASE + (port_index << 10)));
    
    // MODE
    int offset = pin_index << 1;
    gpio->MODER &= ~(0x3 << offset);
    gpio->MODER |= mode << offset;
    
    // Set high-speed mode
    gpio->OSPEEDR &= ~(0x3 << offset);
    gpio->OSPEEDR |= (0x2 << offset);
    
    // FUNCTION
    // Bottom seven pins are in AFR[0], top seven in AFR[1]
    offset = (pin_index & 0x7) << 2;
    if (pin_index <= 0x7) {
        gpio->AFR[0] &= ~(0xF << offset);
        gpio->AFR[0] |= func << offset;
    }
    else {
        gpio->AFR[1] &= ~(0xF << offset);
        gpio->AFR[1] |= func << offset;
    }
}

void pin_mode(PinName pin, PinMode mode) {
    MBED_ASSERT(pin != (PinName)NC);

    uint32_t pin_number = (uint32_t)pin;
    int port_index = pin_number >> 4;
    int pin_index = (pin_number & 0xF);
    int offset = pin_index << 1;

    GPIO_TypeDef * gpio = ((GPIO_TypeDef *) (GPIOA_BASE + (port_index << 10)));
    if (mode == OpenDrain) {
        gpio->OTYPER |= 1 << pin_index;
    }
    else {
        gpio->OTYPER &= ~(1 << pin_index);
        gpio->PUPDR &= ~(0x3 << offset);
        gpio->PUPDR |= mode << offset;
    }
}

