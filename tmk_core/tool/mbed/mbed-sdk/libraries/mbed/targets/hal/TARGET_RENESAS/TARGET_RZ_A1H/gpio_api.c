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
#include "pinmap.h"
#include "gpio_addrdefine.h"


uint32_t gpio_set(PinName pin) {
    pin_function(pin, 0);
    return (1 << PINNO(pin));
}

void gpio_init(gpio_t *obj, PinName pin) {
    int group ;
    obj->pin = pin;
    if(pin == NC) return;
    
    obj->mask = gpio_set(pin);

    group = PINGROUP(pin);
    if (group > 11) return;

    obj->reg_set = (volatile uint32_t *) PSR(group);
    obj->reg_in  = (volatile uint32_t *) PPR(group);
    obj->reg_dir = (volatile uint32_t *)PMSR(group);
    obj->reg_buf = (volatile uint32_t *)PIBC(group);
}

void gpio_mode(gpio_t *obj, PinMode mode) {
/* Pull up and Pull down settings aren't supported because RZ/A1H doesn't have pull up/down for pins(signals). */
}

void gpio_dir(gpio_t *obj, PinDirection direction) {
    switch (direction) {
        case PIN_INPUT :
            *obj->reg_dir = (obj->mask << 16) | obj->mask;
            *obj->reg_buf |=  obj->mask;
            break;
        case PIN_OUTPUT:
            *obj->reg_dir = (obj->mask << 16) | 0;
            *obj->reg_buf &= ~obj->mask;
            break;
    }
}
