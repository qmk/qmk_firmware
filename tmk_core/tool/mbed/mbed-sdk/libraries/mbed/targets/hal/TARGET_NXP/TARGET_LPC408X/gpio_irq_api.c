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
#include <stddef.h>
#include "gpio_irq_api.h"
#include "mbed_error.h"
#include "cmsis.h"

#define CHANNEL_NUM    64

static uint32_t channel_ids[CHANNEL_NUM] = {0};
static gpio_irq_handler irq_handler;

static void handle_interrupt_in(void) {
    // Read in all current interrupt registers. We do this once as the
    // GPIO interrupt registers are on the APB bus, and this is slow.
    uint32_t rise0 = LPC_GPIOINT->IO0IntStatR;
    uint32_t fall0 = LPC_GPIOINT->IO0IntStatF;
    uint32_t rise2 = LPC_GPIOINT->IO2IntStatR;
    uint32_t fall2 = LPC_GPIOINT->IO2IntStatF;

    uint8_t bitloc;

    // Continue as long as there are interrupts pending
    while(rise0 > 0) {
        // CLZ returns number of leading zeros, 31 minus that is location of
        // first pending interrupt
        bitloc = 31 - __CLZ(rise0);
        if (channel_ids[bitloc] != 0)
            irq_handler(channel_ids[bitloc], IRQ_RISE); //Run that interrupt

        // Both clear the interrupt with clear register, and remove it from
        // our local copy of the interrupt pending register
        LPC_GPIOINT->IO0IntClr = 1 << bitloc;
        rise0 -= 1<<bitloc;
    }

    // Continue as long as there are interrupts pending
    while(fall0 > 0) {
        // CLZ returns number of leading zeros, 31 minus that is location of
        // first pending interrupt
        bitloc = 31 - __CLZ(fall0);
        if (channel_ids[bitloc] != 0)
            irq_handler(channel_ids[bitloc], IRQ_FALL); //Run that interrupt

        // Both clear the interrupt with clear register, and remove it from
        // our local copy of the interrupt pending register
        LPC_GPIOINT->IO0IntClr = 1 << bitloc;
        fall0 -= 1<<bitloc;
    }

    // Same for port 2

    // Continue as long as there are interrupts pending
    while(rise2 > 0) {
        // CLZ returns number of leading zeros, 31 minus that is location of
        // first pending interrupt
        bitloc = 31 - __CLZ(rise2);
        if (channel_ids[bitloc+32] != 0)
            irq_handler(channel_ids[bitloc+32], IRQ_RISE); //Run that interrupt

        // Both clear the interrupt with clear register, and remove it from
        // our local copy of the interrupt pending register
        LPC_GPIOINT->IO2IntClr = 1 << bitloc;
        rise2 -= 1<<bitloc;
    }

    // Continue as long as there are interrupts pending
    while(fall2 > 0) {
        // CLZ returns number of leading zeros, 31 minus that is location of
        // first pending interrupt
        bitloc = 31 - __CLZ(fall2);
        if (channel_ids[bitloc+32] != 0)
            irq_handler(channel_ids[bitloc+32], IRQ_FALL); //Run that interrupt

        // Both clear the interrupt with clear register, and remove it from
        // our local copy of the interrupt pending register
        LPC_GPIOINT->IO2IntClr = 1 << bitloc;
        fall2 -= 1<<bitloc;
    }
}

int gpio_irq_init(gpio_irq_t *obj, PinName pin, gpio_irq_handler handler, uint32_t id) {
    if (pin == NC) return -1;
    
    irq_handler = handler;
    
    obj->port = ((int)(LPC_GPIO0_BASE+pin) & ~0x1F);
    obj->pin = (int)pin % 32;
    
    // Interrupts available only on GPIO0 and GPIO2
    if (obj->port != LPC_GPIO0_BASE && obj->port != LPC_GPIO2_BASE) {
        error("pins on this port cannot generate interrupts");
    }
    
    // put us in the interrupt table
    int index = (obj->port == LPC_GPIO0_BASE) ? obj->pin : obj->pin + 32;
    channel_ids[index] = id;
    obj->ch = index;
    
    NVIC_SetVector(GPIO_IRQn, (uint32_t)handle_interrupt_in);
    NVIC_EnableIRQ(GPIO_IRQn);
    
    return 0;
}

void gpio_irq_free(gpio_irq_t *obj) {
    channel_ids[obj->ch] = 0;
}

void gpio_irq_set(gpio_irq_t *obj, gpio_irq_event event, uint32_t enable) {
    // ensure nothing is pending
    switch (obj->port) {
         case LPC_GPIO0_BASE: LPC_GPIOINT->IO0IntClr = 1 << obj->pin; break;
         case LPC_GPIO2_BASE: LPC_GPIOINT->IO2IntClr = 1 << obj->pin; break;
    }
    
    // enable the pin interrupt
    if (event == IRQ_RISE) {
        switch (obj->port) {
            case LPC_GPIO0_BASE:
                if (enable) {
                    LPC_GPIOINT->IO0IntEnR |= 1 << obj->pin;
                } else {
                    LPC_GPIOINT->IO0IntEnR &= ~(1 << obj->pin);
                }
                break;
            case LPC_GPIO2_BASE:
                if (enable) {
                    LPC_GPIOINT->IO2IntEnR |= 1 << obj->pin;
                } else {
                    LPC_GPIOINT->IO2IntEnR &= ~(1 << obj->pin);
                }
                break;
        }
    } else {
        switch (obj->port) {
            case LPC_GPIO0_BASE:
                if (enable) {
                    LPC_GPIOINT->IO0IntEnF |= 1 << obj->pin;
                } else {
                    LPC_GPIOINT->IO0IntEnF &= ~(1 << obj->pin);
                }
                break;
            case LPC_GPIO2_BASE:
                if (enable) {
                    LPC_GPIOINT->IO2IntEnF |= 1 << obj->pin;
                } else {
                    LPC_GPIOINT->IO2IntEnF &= ~(1 << obj->pin);
                }
                break;
        }
    }
}

void gpio_irq_enable(gpio_irq_t *obj) {
    NVIC_EnableIRQ(GPIO_IRQn);
}

void gpio_irq_disable(gpio_irq_t *obj) {
    NVIC_DisableIRQ(GPIO_IRQn);
}
