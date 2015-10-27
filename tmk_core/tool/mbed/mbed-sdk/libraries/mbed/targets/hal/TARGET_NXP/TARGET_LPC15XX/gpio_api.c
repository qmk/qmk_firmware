/* mbed Microcontroller Library
 * Copyright (c) 2006-2014 ARM Limited
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

static int  gpio_enabled = 0;

static void gpio_enable(void) {
    gpio_enabled = 1;
    
    /* Enable AHB clock to the GPIO0/1/2 and IOCON domain. */
    LPC_SYSCON->SYSAHBCLKCTRL0 |= (0xFUL << 13);
}

uint32_t gpio_set(PinName pin) {
    MBED_ASSERT(pin != (PinName)NC);
    if (!gpio_enabled)
         gpio_enable();
    
    return (1UL << ((int)pin & 0x1f));
}

void gpio_init(gpio_t *obj, PinName pin) {
    obj->pin = pin;
    if (pin == (PinName)NC)
        return;

    obj->mask = gpio_set(pin);
    
    unsigned int port = (unsigned int)(pin >> 5);
    
    obj->reg_set = &LPC_GPIO_PORT->SET[port];
    obj->reg_clr = &LPC_GPIO_PORT->CLR[port];
    obj->reg_in  = &LPC_GPIO_PORT->PIN[port];
    obj->reg_dir = &LPC_GPIO_PORT->DIR[port];
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
