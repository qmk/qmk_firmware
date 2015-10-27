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
#include "cmsis.h"
#include "gpio_irq_api.h"
#include "mbed_error.h"
#include "gpio_api.h"

// The chip is capable of 42 GPIO interrupts.
// PIO0_0..PIO0_11, PIO1_0..PIO1_11, PIO2_0..PIO2_11, PIO3_0..PIO3_5
#define CHANNEL_NUM 42

static uint32_t channel_ids[CHANNEL_NUM] = {0};
static gpio_irq_handler irq_handler;

static inline int numofbits(uint32_t bits)
{
    // Count number of bits
    bits = (bits & 0x55555555) + (bits >> 1 & 0x55555555);
    bits = (bits & 0x33333333) + (bits >> 2 & 0x33333333);
    bits = (bits & 0x0f0f0f0f) + (bits >> 4 & 0x0f0f0f0f);
    bits = (bits & 0x00ff00ff) + (bits >> 8 & 0x00ff00ff);
    return (bits & 0x0000ffff) + (bits >>16 & 0x0000ffff);
}

static inline void handle_interrupt_in(uint32_t port) {
    // Find out whether the interrupt has been triggered by a high or low value...
    // As the LPC1114 doesn't have a specific register for this, we'll just have to read
    // the level of the pin as if it were just a normal input...
    
    uint32_t channel;
    
    // Get the number of the pin being used and the port typedef
    LPC_GPIO_TypeDef *port_reg = ((LPC_GPIO_TypeDef *) (LPC_GPIO0_BASE + (port * 0x10000)));
    
    // Get index of function table from Mask Interrupt Status register
    channel = numofbits(port_reg->MIS - 1) + (port * 12);
    
    if (port_reg->MIS & port_reg->IBE) {
        // both edge, read the level of pin
        if ((port_reg->DATA & port_reg->MIS) != 0)
            irq_handler(channel_ids[channel], IRQ_RISE);
        else
            irq_handler(channel_ids[channel], IRQ_FALL);
    }
    else if (port_reg->MIS & port_reg->IEV) {
        irq_handler(channel_ids[channel], IRQ_RISE);
    }
    else {
        irq_handler(channel_ids[channel], IRQ_FALL);
    }

    // Clear the interrupt...
    port_reg->IC = port_reg->MIS;
}

void gpio_irq0(void) {handle_interrupt_in(0);}
void gpio_irq1(void) {handle_interrupt_in(1);}
void gpio_irq2(void) {handle_interrupt_in(2);}
void gpio_irq3(void) {handle_interrupt_in(3);}

int gpio_irq_init(gpio_irq_t *obj, PinName pin, gpio_irq_handler handler, uint32_t id) {
    int channel;
    uint32_t port_num;
    
    if (pin == NC) return -1;
    
    // Firstly, we'll put some data in *obj so we can keep track of stuff.
    obj->pin = pin;
    
    // Set the handler to be the pointer at the top...
    irq_handler = handler;
    
    // Which port are we using?
    port_num = ((pin & 0xF000) >> PORT_SHIFT);
    
    switch (port_num) {
        case 0:
            NVIC_SetVector(EINT0_IRQn, (uint32_t)gpio_irq0);
            NVIC_EnableIRQ(EINT0_IRQn);
            break;
        case 1:
            NVIC_SetVector(EINT1_IRQn, (uint32_t)gpio_irq1);
            NVIC_EnableIRQ(EINT1_IRQn);
            break;
        case 2:
            NVIC_SetVector(EINT2_IRQn, (uint32_t)gpio_irq2);
            NVIC_EnableIRQ(EINT2_IRQn);
            break;
        case 3:
            NVIC_SetVector(EINT3_IRQn, (uint32_t)gpio_irq3);
            NVIC_EnableIRQ(EINT3_IRQn);
            break;
        default:
            return -1;
    }
    
    // Generate index of function pointer table
    // PIO0_0 - PIO0_11 :  0..11
    // PIO1_0 - PIO1_11 : 12..23
    // PIO2_0 - PIO2_11 : 24..35
    // PIO3_0 - PIO3_5  : 36..41
    channel = (port_num * 12) + ((pin & 0x0F00) >> PIN_SHIFT);
    
    channel_ids[channel] = id;
    obj->ch = channel;
    
    return 0;
}

void gpio_irq_free(gpio_irq_t *obj) {
    channel_ids[obj->ch] = 0;
}

void gpio_irq_set(gpio_irq_t *obj, gpio_irq_event event, uint32_t enable) {
    // Firstly, check if there is an existing event stored...

    LPC_GPIO_TypeDef *port_reg = ((LPC_GPIO_TypeDef *) (LPC_GPIO0_BASE + (((obj->pin & 0xF000) >> PORT_SHIFT) * 0x10000)));

    // Need to get the pin number of the pin, not the value of the enum
    uint32_t pin_num = (1 << ((obj->pin & 0x0f00) >> PIN_SHIFT));
   
    // Clear
    port_reg->IC |= pin_num;
    
    // Make it edge sensitive.
    port_reg->IS &= ~pin_num;

    if ( (port_reg->IE & pin_num) != 0) {
    // We have an event.
    // Enable both edge interrupts.

        if (enable) {
            port_reg->IBE |= pin_num;
            port_reg->IE  |= pin_num;
        }
        else {
            // These all need to be opposite, to reenable the other one.
            port_reg->IBE &= ~pin_num;

            if (event == IRQ_RISE)
                port_reg->IEV &= ~pin_num;
            else 
                port_reg->IEV |=  pin_num;

            port_reg->IE |= pin_num;
        }
    }
    else {
        // One edge
        port_reg->IBE &= ~pin_num;
        // Rising/falling?
        if (event == IRQ_RISE)
            port_reg->IEV |=  pin_num;
        else
            port_reg->IEV &= ~pin_num;

        if (enable) {
            port_reg->IE |= pin_num;
        }
    }

}

void gpio_irq_enable(gpio_irq_t *obj) {
    uint32_t port_num = ((obj->pin & 0xF000) >> PORT_SHIFT);
    switch (port_num) {
        case 0:
            NVIC_EnableIRQ(EINT0_IRQn);
            break;
        case 1:
            NVIC_EnableIRQ(EINT1_IRQn);
            break;
        case 2:
            NVIC_EnableIRQ(EINT2_IRQn);
            break;
        case 3:
            NVIC_EnableIRQ(EINT3_IRQn);
            break;
        default:
            break;
    }
}

void gpio_irq_disable(gpio_irq_t *obj) {
    uint32_t port_num = ((obj->pin & 0xF000) >> PORT_SHIFT);
    switch (port_num) {
        case 0:
            NVIC_DisableIRQ(EINT0_IRQn);
            break;
        case 1:
            NVIC_DisableIRQ(EINT1_IRQn);
            break;
        case 2:
            NVIC_DisableIRQ(EINT2_IRQn);
            break;
        case 3:
            NVIC_DisableIRQ(EINT3_IRQn);
            break;
        default:
            break;
    }
}
