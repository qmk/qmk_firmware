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
 *
 * Ported to NXP LPC43XX by Micromint USA <support@micromint.com>
 */
#include <stddef.h>
#include "gpio_irq_api.h"
#include "mbed_error.h"
#include "cmsis.h"

/* The LPC43xx implements GPIO pin and group interrupts. Any pin in the
 * 8 32-bit GPIO ports can interrupt. On group interrupts a pin can
 * only interrupt on the rising or falling edge, not both as required
 * by mbed. Also, group interrupts can't be cleared individually.
 * This implementation uses pin interrupts (8 on M4/M3, 1 on M0).
 * A future implementation may provide group interrupt support.
 */
#if !defined(CORE_M0)
#define CHANNEL_MAX    8
#else
#define CHANNEL_MAX    1
#endif

static uint32_t channel_ids[CHANNEL_MAX] = {0};
static uint8_t channel = 0;
static gpio_irq_handler irq_handler;

static void handle_interrupt_in(void) {
    uint32_t rise = LPC_GPIO_PIN_INT->RISE;
    uint32_t fall = LPC_GPIO_PIN_INT->FALL;
    uint32_t pmask;
    int i;

    for (i = 0; i < CHANNEL_MAX; i++) {
        pmask = (1 << i);
        if (rise & pmask) {
            /* Rising edge interrupts */
            if (channel_ids[i] != 0) {
                irq_handler(channel_ids[i], IRQ_RISE);
            }
            /* Clear rising edge detected */
            LPC_GPIO_PIN_INT->RISE = pmask;
        }
        if (fall & pmask) {
            /* Falling edge interrupts */
            if (channel_ids[i] != 0) {
                irq_handler(channel_ids[i], IRQ_FALL);
            }
            /* Clear falling edge detected */
            LPC_GPIO_PIN_INT->FALL = pmask;
        }
    }
}

int gpio_irq_init(gpio_irq_t *obj, PinName pin, gpio_irq_handler handler, uint32_t id) {
    uint32_t portnum, pinnum; //, pmask;

    if (pin == NC) return -1;

    irq_handler = handler;

    /* Set port and pin numbers */
    obj->port = portnum = MBED_GPIO_PORT(pin);
    obj->pin = pinnum = MBED_GPIO_PIN(pin);

    /* Add to channel table */
    channel_ids[channel] = id;
    obj->ch = channel;

	  /* Clear rising and falling edge detection */
    //pmask = (1 << channel);
    //LPC_GPIO_PIN_INT->IST = pmask;

    /* Set SCU */
    if (channel < 4) {
        LPC_SCU->PINTSEL0 &= ~(0xFF << (portnum << 3));
        LPC_SCU->PINTSEL0 |= (((portnum << 5) | pinnum) << (channel << 3));
    } else {
        LPC_SCU->PINTSEL1 &= ~(0xFF << ((portnum - 4) << 3));
        LPC_SCU->PINTSEL1 |= (((portnum << 5) | pinnum) << ((channel - 4) << 3));
    }
	
#if !defined(CORE_M0)
    NVIC_SetVector((IRQn_Type)(PIN_INT0_IRQn + channel), (uint32_t)handle_interrupt_in);
    NVIC_EnableIRQ((IRQn_Type)(PIN_INT0_IRQn + channel));
#else
    NVIC_SetVector((IRQn_Type)PIN_INT4_IRQn, (uint32_t)handle_interrupt_in);
    NVIC_EnableIRQ((IRQn_Type)PIN_INT4_IRQn);
#endif

    // Increment channel number
    channel++;
    channel %= CHANNEL_MAX;

    return 0;
}

void gpio_irq_free(gpio_irq_t *obj) {
    channel_ids[obj->ch] = 0;
}

void gpio_irq_set(gpio_irq_t *obj, gpio_irq_event event, uint32_t enable) {
    uint32_t pmask;

    /* Clear pending interrupts */
    pmask = (1 << obj->ch);
    LPC_GPIO_PIN_INT->IST = pmask;

    /* Configure pin interrupt */
    LPC_GPIO_PIN_INT->ISEL &= ~pmask;
    if (event == IRQ_RISE) {
        /* Rising edge interrupts */
        if (enable) {
            LPC_GPIO_PIN_INT->SIENR |= pmask;
        } else {
            LPC_GPIO_PIN_INT->CIENR |= pmask;
        }
    } else {
        /* Falling edge interrupts */
        if (enable) {
            LPC_GPIO_PIN_INT->SIENF |= pmask;
        } else {
            LPC_GPIO_PIN_INT->CIENF |= pmask;
        }
    }
}

void gpio_irq_enable(gpio_irq_t *obj) {
#if !defined(CORE_M0)
    NVIC_EnableIRQ((IRQn_Type)(PIN_INT0_IRQn + obj->ch));
#else
    NVIC_EnableIRQ((IRQn_Type)(PIN_INT4_IRQn + obj->ch));
#endif
}

void gpio_irq_disable(gpio_irq_t *obj) {
#if !defined(CORE_M0)
    NVIC_DisableIRQ((IRQn_Type)(PIN_INT0_IRQn + obj->ch));
#else
    NVIC_DisableIRQ((IRQn_Type)(PIN_INT4_IRQn + obj->ch));
#endif
}
