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
#include "gpio_api.h"
#include "mbed_error.h"

#define CHANNEL_NUM    96

static uint32_t channel_ids[CHANNEL_NUM] = {0};
static gpio_irq_handler irq_handler;

#define IRQ_DISABLED        (0)
#define IRQ_RAISING_EDGE    PORT_PCR_IRQC(9)
#define IRQ_FALLING_EDGE    PORT_PCR_IRQC(10)
#define IRQ_EITHER_EDGE     PORT_PCR_IRQC(11)

const uint32_t search_bits[] = {0x0000FFFF, 0x000000FF, 0x0000000F, 0x00000003, 0x00000001};

static void handle_interrupt_in(PORT_Type *port, int ch_base) {
    uint32_t isfr;
    uint8_t location;

    while((isfr = port->ISFR) != 0) {
        location = 0;
        for (int i = 0; i < 5; i++) {
            if (!(isfr & (search_bits[i] << location)))
                location += 1 << (4 - i);
        }
        
        uint32_t id = channel_ids[ch_base + location];
        if (id == 0) {
            continue;
        }

        GPIO_Type *gpio;
        gpio_irq_event event = IRQ_NONE;
        switch (port->PCR[location] & PORT_PCR_IRQC_MASK) {
            case IRQ_RAISING_EDGE:
                event = IRQ_RISE;
                break;

            case IRQ_FALLING_EDGE:
                event = IRQ_FALL;
                break;

            case IRQ_EITHER_EDGE:
                if (port == PORTA) {
                    gpio = GPIOA;
                } else if (port == PORTC) {
                    gpio = GPIOC;
                } else {
                    gpio = GPIOD;
                }
                event = (gpio->PDIR & (1<<location)) ? (IRQ_RISE) : (IRQ_FALL);
                break;
        }
        if (event != IRQ_NONE) {
            irq_handler(id, event);
        }
        port->ISFR = 1 << location;
    }
}

void gpio_irqA(void) {
    handle_interrupt_in(PORTA, 0);
}

/* PORTC and PORTD share same vector */
void gpio_irqCD(void) {
    if ((SIM->SCGC5 & SIM_SCGC5_PORTC_MASK) && (PORTC->ISFR)) {
        handle_interrupt_in(PORTC, 32);
    } else if ((SIM->SCGC5 & SIM_SCGC5_PORTD_MASK) && (PORTD->ISFR)) {
        handle_interrupt_in(PORTD, 64);
    }
}

int gpio_irq_init(gpio_irq_t *obj, PinName pin, gpio_irq_handler handler, uint32_t id) {
    if (pin == NC)
        return -1;

    irq_handler = handler;

    obj->port = pin >> PORT_SHIFT;
    obj->pin = (pin & 0x7F) >> 2;

    uint32_t ch_base, vector;
    IRQn_Type irq_n;
    switch (obj->port) {
            case PortA:
                ch_base = 0;  irq_n = PORTA_IRQn; vector = (uint32_t)gpio_irqA;
                break;

            case PortC:
                ch_base = 32; irq_n = PORTCD_IRQn; vector = (uint32_t)gpio_irqCD;
                break;

            case PortD:
                ch_base = 64; irq_n = PORTCD_IRQn; vector = (uint32_t)gpio_irqCD;
                break;

            default:
                error("gpio_irq only supported on port A,C and D");
                break;
    }
    NVIC_SetVector(irq_n, vector);
    NVIC_EnableIRQ(irq_n);

    obj->ch = ch_base + obj->pin;
    channel_ids[obj->ch] = id;

    return 0;
}

void gpio_irq_free(gpio_irq_t *obj) {
    channel_ids[obj->ch] = 0;
}

void gpio_irq_set(gpio_irq_t *obj, gpio_irq_event event, uint32_t enable) {
    PORT_Type *port = (PORT_Type *)(PORTA_BASE + 0x1000 * obj->port);

    uint32_t irq_settings = IRQ_DISABLED;

    switch (port->PCR[obj->pin] & PORT_PCR_IRQC_MASK) {
        case IRQ_DISABLED:
            if (enable) {
                irq_settings = (event == IRQ_RISE) ? (IRQ_RAISING_EDGE) : (IRQ_FALLING_EDGE);
            }
            break;

        case IRQ_RAISING_EDGE:
            if (enable) {
                irq_settings = (event == IRQ_RISE) ? (IRQ_RAISING_EDGE) : (IRQ_EITHER_EDGE);
            } else {
                if (event == IRQ_FALL)
                    irq_settings = IRQ_RAISING_EDGE;
            }
            break;

        case IRQ_FALLING_EDGE:
            if (enable) {
                irq_settings = (event == IRQ_FALL) ? (IRQ_FALLING_EDGE) : (IRQ_EITHER_EDGE);
            } else {
                if (event == IRQ_RISE)
                    irq_settings = IRQ_FALLING_EDGE;
            }
            break;

        case IRQ_EITHER_EDGE:
            if (enable) {
                irq_settings = IRQ_EITHER_EDGE;
            } else {
                irq_settings = (event == IRQ_RISE) ? (IRQ_FALLING_EDGE) : (IRQ_RAISING_EDGE);
            }
            break;
    }

    // Interrupt configuration and clear interrupt
    port->PCR[obj->pin] = (port->PCR[obj->pin] & ~PORT_PCR_IRQC_MASK) | irq_settings | PORT_PCR_ISF_MASK;
}

void gpio_irq_enable(gpio_irq_t *obj) {
    if (obj->port == PortA) {
        NVIC_EnableIRQ(PORTA_IRQn);
    } else {
        NVIC_EnableIRQ(PORTCD_IRQn);
    }
}

void gpio_irq_disable(gpio_irq_t *obj) {
    if (obj->port == PortA) {
        NVIC_DisableIRQ(PORTA_IRQn);
    } else {
        NVIC_DisableIRQ(PORTCD_IRQn);
    }
}
