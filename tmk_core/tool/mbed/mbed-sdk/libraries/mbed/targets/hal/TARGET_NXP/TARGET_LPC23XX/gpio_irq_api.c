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
#include "gpio_irq_api.h"
#include "mbed_error.h"
#include <stddef.h>
#include "cmsis.h"

#define CHANNEL_NUM     48

static uint32_t channel_ids[CHANNEL_NUM] = {0};
static gpio_irq_handler irq_handler;

static void handle_interrupt_in(void) {
    // Read in all current interrupt registers. We do this once as the
    // GPIO interrupt registers are on the APB bus, and this is slow.
    uint32_t rise0 = LPC_GPIOINT->IO0IntStatR;
    uint32_t fall0 = LPC_GPIOINT->IO0IntStatF;
    uint32_t rise2 = LPC_GPIOINT->IO2IntStatR;
    uint32_t fall2 = LPC_GPIOINT->IO2IntStatF;
    uint32_t mask0 = 0;
    uint32_t mask2 = 0;
    int i;
    
    // P0.0-0.31
    for (i = 0; i < 32; i++) {
        uint32_t pmask = (1 << i);
        if (rise0 & pmask) {
            mask0 |= pmask;
            if (channel_ids[i] != 0)
                irq_handler(channel_ids[i], IRQ_RISE);
        }
        if (fall0 & pmask) {
            mask0 |= pmask;
            if (channel_ids[i] != 0)
                irq_handler(channel_ids[i], IRQ_FALL);
        }
    }
    
    // P2.0-2.15
    for (i = 0; i < 16; i++) {
        uint32_t pmask = (1 << i);
        int channel_index = i + 32;
        if (rise2 & pmask) {
            mask2 |= pmask;
            if (channel_ids[channel_index] != 0)
                irq_handler(channel_ids[channel_index], IRQ_RISE);
        }
        if (fall2 & pmask) {
            mask2 |= pmask;
            if (channel_ids[channel_index] != 0)
                irq_handler(channel_ids[channel_index], IRQ_FALL);
        }
    }
    
    // Clear the interrupts we just handled
    LPC_GPIOINT->IO0IntClr = mask0;
    LPC_GPIOINT->IO2IntClr = mask2;
}

int gpio_irq_init(gpio_irq_t *obj, PinName pin, gpio_irq_handler handler, uint32_t id) {
    if (pin == NC) return -1;
    
    irq_handler = handler;
    
    obj->port = (int)pin & ~0x1F;
    obj->pin = (int)pin & 0x1F;
    
    // Interrupts available only on GPIO0 and GPIO2
    if (obj->port != LPC_GPIO0_BASE && obj->port != LPC_GPIO2_BASE) {
        error("pins on this port cannot generate interrupts");
    }
    
    // put us in the interrupt table
    int index = (obj->port == LPC_GPIO0_BASE) ? obj->pin : obj->pin + 32;
    channel_ids[index] = id;
    obj->ch = index;
    
    NVIC_SetVector(EINT3_IRQn, (uint32_t)handle_interrupt_in);
    NVIC_EnableIRQ(EINT3_IRQn);
    
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
    NVIC_EnableIRQ(EINT3_IRQn);
}

void gpio_irq_disable(gpio_irq_t *obj) {
    NVIC_DisableIRQ(EINT3_IRQn);
}

