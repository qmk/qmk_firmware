/*******************************************************************************
 * Copyright (C) 2015 Maxim Integrated Products, Inc., All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL MAXIM INTEGRATED BE LIABLE FOR ANY CLAIM, DAMAGES
 * OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Except as contained in this notice, the name of Maxim Integrated
 * Products, Inc. shall not be used except as stated in the Maxim Integrated
 * Products, Inc. Branding Policy.
 *
 * The mere transfer of this software does not imply any licenses
 * of trade secrets, proprietary technology, copyrights, patents,
 * trademarks, maskwork rights, or any other form of intellectual
 * property whatsoever. Maxim Integrated Products, Inc. retains all
 * ownership rights.
 *******************************************************************************
 */
 
#include <stddef.h>
#include "cmsis.h"
#include "gpio_irq_api.h"
#include "mbed_error.h"

#define NUM_PORTS           8
#define NUM_PINS_PER_PORT   8

static uint32_t ids[NUM_PORTS][NUM_PINS_PER_PORT] = {{0}};
static gpio_irq_handler irq_handler;

static void handle_irq(unsigned int port)
{
    uint32_t intfl, in_val;
    uint32_t mask;
    unsigned int pin;

    /* Read pin state */
    in_val = MXC_GPIO->in_val[port];

    /* Read interrupts */
    intfl = MXC_GPIO->intfl[port] & MXC_GPIO->inten[port];
    
    mask = 1;

    for (pin = 0; pin < NUM_PINS_PER_PORT; pin++) {
        if (intfl & mask) {
            if (ids[port][pin]) {
                if (in_val & mask) {
                    irq_handler(ids[port][pin], IRQ_RISE);
                } else {
                    irq_handler(ids[port][pin], IRQ_FALL);
                }
            }
            MXC_GPIO->intfl[port] = mask;    /* clear interrupt */
        }
        mask <<= 1;
    }
}

void gpio_irq_0(void) { handle_irq(0); }
void gpio_irq_1(void) { handle_irq(1); }
void gpio_irq_2(void) { handle_irq(2); }
void gpio_irq_3(void) { handle_irq(3); }
void gpio_irq_4(void) { handle_irq(4); }
void gpio_irq_5(void) { handle_irq(5); }
void gpio_irq_6(void) { handle_irq(6); }
void gpio_irq_7(void) { handle_irq(7); }

int gpio_irq_init(gpio_irq_t *obj, PinName name, gpio_irq_handler handler, uint32_t id)
{
    if (name == NC)
        return -1;

    uint8_t port = PINNAME_TO_PORT(name);
    uint8_t pin = PINNAME_TO_PIN(name);

    if ((port > NUM_PORTS) || (pin > NUM_PINS_PER_PORT)) {
        return 1;
    }

    obj->port = port;
    obj->pin = pin;

    irq_handler = handler;

    ids[port][pin] = id;

    /* register handlers */
    NVIC_SetVector(GPIO_P0_IRQn, (uint32_t)gpio_irq_0);
    NVIC_SetVector(GPIO_P1_IRQn, (uint32_t)gpio_irq_1);
    NVIC_SetVector(GPIO_P2_IRQn, (uint32_t)gpio_irq_2);
    NVIC_SetVector(GPIO_P3_IRQn, (uint32_t)gpio_irq_3);
    NVIC_SetVector(GPIO_P4_IRQn, (uint32_t)gpio_irq_4);
    NVIC_SetVector(GPIO_P5_IRQn, (uint32_t)gpio_irq_5);
    NVIC_SetVector(GPIO_P6_IRQn, (uint32_t)gpio_irq_6);
    NVIC_SetVector(GPIO_P7_IRQn, (uint32_t)gpio_irq_7);

    /* disable the interrupt locally */
    MXC_GPIO->int_mode[port] &= ~(0xF << (pin*4));

    /* clear a pending request */
    MXC_GPIO->intfl[port] = 1 << pin;

    /* enable the requested interrupt */
    MXC_GPIO->inten[port] |= (1 << pin);
    NVIC_EnableIRQ((IRQn_Type)((uint32_t)GPIO_P0_IRQn + port));

    return 0;
}

void gpio_irq_free(gpio_irq_t *obj)
{
    /* disable interrupt */
    MXC_GPIO->inten[obj->port] &= ~(1 << obj->pin);
    MXC_GPIO->int_mode[obj->port] &= ~(0xF << (obj->pin*4));

    ids[obj->port][obj->pin] = 0;
}

void gpio_irq_set(gpio_irq_t *obj, gpio_irq_event event, uint32_t enable)
{
    uint32_t int_mode = MXC_GPIO->int_mode[obj->port];
    uint32_t curr_mode = (int_mode >> (obj->pin*4)) & 0x3;   /* only supporting edge interrupts */

    uint32_t new_mode = curr_mode;
    if (event == IRQ_FALL) {
        if (enable) {
            new_mode |= 0x1;
        } else {
            new_mode &= ~0x1;
        }
    } else if (event == IRQ_RISE) {
        if (enable) {
            new_mode |= 0x2;
        } else {
            new_mode &= ~0x2;
        }
    }

    int_mode &= ~(0xF << (obj->pin*4));
    int_mode |= (new_mode << (obj->pin*4));
    MXC_GPIO->int_mode[obj->port] = int_mode;
}

void gpio_irq_enable(gpio_irq_t *obj)
{
    MXC_GPIO->inten[obj->port] |= (1 << obj->pin);
}

void gpio_irq_disable(gpio_irq_t *obj)
{
    MXC_GPIO->inten[obj->port] &= ~(1 << obj->pin);
}
