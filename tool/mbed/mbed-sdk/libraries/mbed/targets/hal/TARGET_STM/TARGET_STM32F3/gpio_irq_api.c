/* mbed Microcontroller Library
 *******************************************************************************
 * Copyright (c) 2014, STMicroelectronics
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. Neither the name of STMicroelectronics nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *******************************************************************************
 */
#include <stddef.h>
#include "cmsis.h"
#include "gpio_irq_api.h"
#include "pinmap.h"
#include "mbed_error.h"

#define EDGE_NONE (0)
#define EDGE_RISE (1)
#define EDGE_FALL (2)
#define EDGE_BOTH (3)

// Number of EXTI irq vectors (EXTI0, EXTI1, EXTI2, EXTI3, EXTI4, EXTI5_9, EXTI10_15)
#define CHANNEL_NUM (7)

// Max pins for one line (max with EXTI10_15)
#define MAX_PIN_LINE (6)

typedef struct gpio_channel {
    uint32_t pin_mask;                   // bitmask representing which pins are configured for receiving interrupts
    uint32_t channel_ids[MAX_PIN_LINE];  // mbed "gpio_irq_t gpio_irq" field of instance
    uint32_t channel_gpio[MAX_PIN_LINE]; // base address of gpio port group
    uint32_t channel_pin[MAX_PIN_LINE];  // pin number in port group
} gpio_channel_t;

static gpio_channel_t channels[CHANNEL_NUM] = {
    {.pin_mask = 0},
    {.pin_mask = 0},
    {.pin_mask = 0},
    {.pin_mask = 0},
    {.pin_mask = 0},
    {.pin_mask = 0},
    {.pin_mask = 0}
};

// Used to return the index for channels array.
static uint32_t pin_base_nr[16] = {
    // EXTI0
    0, // pin 0
    // EXTI1
    0, // pin 1
    // EXTI2
    0, // pin 2
    // EXTI3
    0, // pin 3
    // EXTI4
    0, // pin 4
    // EXTI5_9
    0, // pin 5
    1, // pin 6
    2, // pin 7
    3, // pin 8
    4, // pin 9
    // EXTI10_15
    0, // pin 10
    1, // pin 11
    2, // pin 12
    3, // pin 13
    4, // pin 14
    5  // pin 15
};

static gpio_irq_handler irq_handler;

static void handle_interrupt_in(uint32_t irq_index, uint32_t max_num_pin_line)
{
    gpio_channel_t *gpio_channel = &channels[irq_index];
    uint32_t gpio_idx;

    for (gpio_idx = 0; gpio_idx < max_num_pin_line; gpio_idx++) {
        uint32_t current_mask = (1 << gpio_idx);

        if (gpio_channel->pin_mask & current_mask) {
            // Retrieve the gpio and pin that generate the irq
            GPIO_TypeDef *gpio = (GPIO_TypeDef *)(gpio_channel->channel_gpio[gpio_idx]);
            uint32_t pin = (uint32_t)(1 << (gpio_channel->channel_pin[gpio_idx]));

            // Clear interrupt flag
            if (__HAL_GPIO_EXTI_GET_FLAG(pin) != RESET) {
                __HAL_GPIO_EXTI_CLEAR_FLAG(pin);

                if (gpio_channel->channel_ids[gpio_idx] == 0) continue;

                // Check which edge has generated the irq
                if ((gpio->IDR & pin) == 0) {
                    irq_handler(gpio_channel->channel_ids[gpio_idx], IRQ_FALL);
                } else  {
                    irq_handler(gpio_channel->channel_ids[gpio_idx], IRQ_RISE);
                }
            }
        }
    }
}

// EXTI line 0
static void gpio_irq0(void)
{
    handle_interrupt_in(0, 1);
}

// EXTI line 1
static void gpio_irq1(void)
{
    handle_interrupt_in(1, 1);
}

// EXTI line 2
static void gpio_irq2(void)
{
    handle_interrupt_in(2, 1);
}

// EXTI line 3
static void gpio_irq3(void)
{
    handle_interrupt_in(3, 1);
}

// EXTI line 4
static void gpio_irq4(void)
{
    handle_interrupt_in(4, 1);
}

// EXTI lines 5 to 9
static void gpio_irq5(void)
{
    handle_interrupt_in(5, 5);
}

// EXTI lines 10 to 15
static void gpio_irq6(void)
{
    handle_interrupt_in(6, 6);
}

extern uint32_t Set_GPIO_Clock(uint32_t port_idx);

int gpio_irq_init(gpio_irq_t *obj, PinName pin, gpio_irq_handler handler, uint32_t id)
{
    IRQn_Type irq_n = (IRQn_Type)0;
    uint32_t vector = 0;
    uint32_t irq_index;
    gpio_channel_t *gpio_channel;
    uint32_t gpio_idx;

    if (pin == NC) return -1;

    uint32_t port_index = STM_PORT(pin);
    uint32_t pin_index  = STM_PIN(pin);

    // Select irq number and interrupt routine
    switch (pin_index) {
        case 0:
            irq_n = EXTI0_IRQn;
            vector = (uint32_t)&gpio_irq0;
            irq_index = 0;
            break;
        case 1:
            irq_n = EXTI1_IRQn;
            vector = (uint32_t)&gpio_irq1;
            irq_index = 1;
            break;
        case 2:
            irq_n = EXTI2_TSC_IRQn;
            vector = (uint32_t)&gpio_irq2;
            irq_index = 2;
            break;
        case 3:
            irq_n = EXTI3_IRQn;
            vector = (uint32_t)&gpio_irq3;
            irq_index = 3;
            break;
        case 4:
            irq_n = EXTI4_IRQn;
            vector = (uint32_t)&gpio_irq4;
            irq_index = 4;
            break;
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
            irq_n = EXTI9_5_IRQn;
            vector = (uint32_t)&gpio_irq5;
            irq_index = 5;
            break;
        case 10:
        case 11:
        case 12:
        case 13:
        case 14:
        case 15:
            irq_n = EXTI15_10_IRQn;
            vector = (uint32_t)&gpio_irq6;
            irq_index = 6;
            break;
        default:
            error("InterruptIn error: pin not supported.\n");
            return -1;
    }

    // Enable GPIO clock
    uint32_t gpio_add = Set_GPIO_Clock(port_index);

    // Configure GPIO
    pin_function(pin, STM_PIN_DATA(STM_MODE_IT_FALLING, GPIO_NOPULL, 0));

    // Enable EXTI interrupt
    NVIC_SetVector(irq_n, vector);
    NVIC_EnableIRQ(irq_n);

    // Save informations for future use
    obj->irq_n = irq_n;
    obj->irq_index = irq_index;
    obj->event = EDGE_NONE;
    obj->pin = pin;

    gpio_channel = &channels[irq_index];
    gpio_idx = pin_base_nr[pin_index];
    gpio_channel->pin_mask |= (1 << gpio_idx);
    gpio_channel->channel_ids[gpio_idx] = id;
    gpio_channel->channel_gpio[gpio_idx] = gpio_add;
    gpio_channel->channel_pin[gpio_idx] = pin_index;

    irq_handler = handler;

    return 0;
}

void gpio_irq_free(gpio_irq_t *obj)
{
    gpio_channel_t *gpio_channel = &channels[obj->irq_index];
    uint32_t pin_index  = STM_PIN(obj->pin);
    uint32_t gpio_idx = pin_base_nr[pin_index];

    gpio_channel->pin_mask &= ~(1 << gpio_idx);
    gpio_channel->channel_ids[gpio_idx] = 0;
    gpio_channel->channel_gpio[gpio_idx] = 0;
    gpio_channel->channel_pin[gpio_idx] = 0;

    // Disable EXTI line
    pin_function(obj->pin, STM_PIN_DATA(STM_MODE_INPUT, GPIO_NOPULL, 0));
    obj->event = EDGE_NONE;
}

void gpio_irq_set(gpio_irq_t *obj, gpio_irq_event event, uint32_t enable)
{
    uint32_t mode = STM_MODE_IT_EVT_RESET;
    uint32_t pull = GPIO_NOPULL;

    if (enable) {
        if (event == IRQ_RISE) {
            if ((obj->event == EDGE_FALL) || (obj->event == EDGE_BOTH)) {
                mode = STM_MODE_IT_RISING_FALLING;
                obj->event = EDGE_BOTH;
            } else { // NONE or RISE
                mode = STM_MODE_IT_RISING;
                obj->event = EDGE_RISE;
            }
        }
        if (event == IRQ_FALL) {
            if ((obj->event == EDGE_RISE) || (obj->event == EDGE_BOTH)) {
                mode = STM_MODE_IT_RISING_FALLING;
                obj->event = EDGE_BOTH;
            } else { // NONE or FALL
                mode = STM_MODE_IT_FALLING;
                obj->event = EDGE_FALL;
            }
        }
    } else { // Disable
        if (event == IRQ_RISE) {
            if ((obj->event == EDGE_FALL) || (obj->event == EDGE_BOTH)) {
                mode = STM_MODE_IT_FALLING;
                obj->event = EDGE_FALL;
            } else { // NONE or RISE
                mode = STM_MODE_IT_EVT_RESET;
                obj->event = EDGE_NONE;
            }
        }
        if (event == IRQ_FALL) {
            if ((obj->event == EDGE_RISE) || (obj->event == EDGE_BOTH)) {
                mode = STM_MODE_IT_RISING;
                obj->event = EDGE_RISE;
            } else { // NONE or FALL
                mode = STM_MODE_IT_EVT_RESET;
                obj->event = EDGE_NONE;
            }
        }
    }

    pin_function(obj->pin, STM_PIN_DATA(mode, pull, 0));
}

void gpio_irq_enable(gpio_irq_t *obj)
{
    NVIC_EnableIRQ(obj->irq_n);
}

void gpio_irq_disable(gpio_irq_t *obj)
{
    NVIC_DisableIRQ(obj->irq_n);
    obj->event = EDGE_NONE;
}
