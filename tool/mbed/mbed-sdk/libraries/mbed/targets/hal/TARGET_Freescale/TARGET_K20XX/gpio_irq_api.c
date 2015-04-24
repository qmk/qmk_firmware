/* mbed Microcontroller Library
 * Copyright (c) 2006-2015 ARM Limited
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

#define CHANNEL_NUM    160

static uint32_t channel_ids[CHANNEL_NUM] = {0};
static gpio_irq_handler irq_handler;

#define IRQ_DISABLED        (0)
#define IRQ_RAISING_EDGE    PORT_PCR_IRQC(9)
#define IRQ_FALLING_EDGE    PORT_PCR_IRQC(10)
#define IRQ_EITHER_EDGE     PORT_PCR_IRQC(11)

static void handle_interrupt_in(PORT_Type *port, int ch_base) {
    uint32_t isfr;
    uint32_t pin;

    while ((isfr = port->ISFR) != 0) {
        pin = 31 - __CLZ(isfr);
        uint32_t id = channel_ids[ch_base + pin];
        if (id == 0) {
            continue;
        }

        GPIO_Type *gpio = PTA;
        gpio_irq_event event = IRQ_NONE;
        uint32_t port_num = (port - PORTA) >> 12;

        switch (port->PCR[pin] & PORT_PCR_IRQC_MASK) {
            case IRQ_RAISING_EDGE:
                event = IRQ_RISE;
                break;
            case IRQ_FALLING_EDGE:
                event = IRQ_FALL;
                break;
            case IRQ_EITHER_EDGE:
                gpio += (port_num * 0x40);
                event = (gpio->PDIR & (1 << pin)) ? (IRQ_RISE) : (IRQ_FALL);
                break;
        }
        if (event != IRQ_NONE) {
            irq_handler(id, event);
        }
        port->ISFR = 1 << pin;
    }
}

void gpio_irqA(void) {
    handle_interrupt_in(PORTA, 0);
}

void gpio_irqB(void)
{
    handle_interrupt_in(PORTB, 32);
}

void gpio_irqC(void)
{
    handle_interrupt_in(PORTC, 64);
}

void gpio_irqD(void)
{
    handle_interrupt_in(PORTD, 96);
}

void gpio_irqE(void)
{
    handle_interrupt_in(PORTE, 128);
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
            ch_base = 0;
            irq_n = PORTA_IRQn;
            vector = (uint32_t)gpio_irqA;
            break;
        case PortB:
            ch_base = 32;
            irq_n = PORTB_IRQn;
            vector = (uint32_t)gpio_irqB;
            break;
        case PortC:
            ch_base = 64;
            irq_n = PORTC_IRQn;
            vector = (uint32_t)gpio_irqC;
            break;
        case PortD:
            ch_base = 96;
            irq_n = PORTD_IRQn; vector = (uint32_t)gpio_irqD;
            break;
        case PortE:
            ch_base = 128;
            irq_n = PORTE_IRQn;
            vector = (uint32_t)gpio_irqE;
            break;

        default:
            error("gpio_irq only supported on port A-E.");
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
            if (enable)
                irq_settings = (event == IRQ_RISE) ? (IRQ_RAISING_EDGE) : (IRQ_FALLING_EDGE);
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
    switch (obj->port) {
        case PortA:
            NVIC_EnableIRQ(PORTA_IRQn);
            break;
        case PortB:
            NVIC_EnableIRQ(PORTB_IRQn);
            break;
        case PortC:
            NVIC_EnableIRQ(PORTC_IRQn);
            break;
        case PortD:
            NVIC_EnableIRQ(PORTD_IRQn);
            break;
        case PortE:
            NVIC_EnableIRQ(PORTE_IRQn);
            break;
    }
}

void gpio_irq_disable(gpio_irq_t *obj) {
    switch (obj->port) {
        case PortA:
            NVIC_DisableIRQ(PORTA_IRQn);
            break;
        case PortB:
            NVIC_DisableIRQ(PORTB_IRQn);
            break;
        case PortC:
            NVIC_DisableIRQ(PORTC_IRQn);
            break;
        case PortD:
            NVIC_DisableIRQ(PORTD_IRQn);
            break;
        case PortE:
            NVIC_DisableIRQ(PORTE_IRQn);
            break;
    }
}
