/* mbed Microcontroller Library
 * Copyright (c) 2013 Nordic Semiconductor
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

#define CHANNEL_NUM    31

static uint32_t channel_ids[CHANNEL_NUM] = {0}; //each pin will be given an id, if id is 0 the pin can be ignored.
static uint8_t channel_enabled[CHANNEL_NUM] = {0};
static uint32_t portRISE = 0;
static uint32_t portFALL = 0;
static gpio_irq_handler irq_handler;

#ifdef __cplusplus
extern "C" {
#endif
void GPIOTE_IRQHandler(void)
{
    volatile uint32_t newVal = NRF_GPIO->IN;

    if ((NRF_GPIOTE->EVENTS_PORT != 0) && ((NRF_GPIOTE->INTENSET & GPIOTE_INTENSET_PORT_Msk) != 0)) {
        NRF_GPIOTE->EVENTS_PORT = 0;

        for (uint8_t i = 0; i<31; i++) {
            if (channel_ids[i]>0) {
                if (channel_enabled[i]) {
                    if( ((newVal>>i)&1)  && ( ( (NRF_GPIO->PIN_CNF[i] >>GPIO_PIN_CNF_SENSE_Pos) & GPIO_PIN_CNF_SENSE_Low) != GPIO_PIN_CNF_SENSE_Low) && ( (portRISE>>i)&1) ){
                        irq_handler(channel_ids[i], IRQ_RISE);
                    } else if ((((newVal >> i) & 1) == 0) &&
                               (((NRF_GPIO->PIN_CNF[i] >> GPIO_PIN_CNF_SENSE_Pos) & GPIO_PIN_CNF_SENSE_Low) == GPIO_PIN_CNF_SENSE_Low) &&
                               ((portFALL >> i) & 1)) {
                        irq_handler(channel_ids[i], IRQ_FALL);
                    }
                }

                if (NRF_GPIO->PIN_CNF[i] & GPIO_PIN_CNF_SENSE_Msk) {
                    NRF_GPIO->PIN_CNF[i] &= ~(GPIO_PIN_CNF_SENSE_Msk);

                    if (newVal >> i & 1) {
                        NRF_GPIO->PIN_CNF[i] |= (GPIO_PIN_CNF_SENSE_Low << GPIO_PIN_CNF_SENSE_Pos);
                    } else {
                        NRF_GPIO->PIN_CNF[i] |= (GPIO_PIN_CNF_SENSE_High << GPIO_PIN_CNF_SENSE_Pos);
                    }
                }
            }
        }
    }
}

#ifdef __cplusplus
}
#endif

int gpio_irq_init(gpio_irq_t *obj, PinName pin, gpio_irq_handler handler, uint32_t id)
{
    if (pin == NC) {
        return -1;
    }

    irq_handler             = handler;
    obj->ch                 = pin;
    NRF_GPIOTE->EVENTS_PORT = 0;
    channel_ids[pin]        = id;
    channel_enabled[pin]    = 1;
    NRF_GPIOTE->INTENSET    = GPIOTE_INTENSET_PORT_Set << GPIOTE_INTENSET_PORT_Pos;

    NVIC_SetPriority(GPIOTE_IRQn, 3);
    NVIC_EnableIRQ  (GPIOTE_IRQn);
    return 0;
}

void gpio_irq_free(gpio_irq_t *obj)
{
    channel_ids[obj->ch] = 0;
}

void gpio_irq_set(gpio_irq_t *obj, gpio_irq_event event, uint32_t enable)
{
    NRF_GPIO->PIN_CNF[obj->ch] &= ~(GPIO_PIN_CNF_SENSE_Msk);
    if (enable) {
        if (event == IRQ_RISE) {
            portRISE |= (1 << obj->ch);
        } else if (event == IRQ_FALL) {
            portFALL |= (1 << obj->ch);
        }
    } else {
        if (event == IRQ_RISE) {
            portRISE &= ~(1 << obj->ch);
        } else if (event == IRQ_FALL) {
            portFALL &= ~(1 << obj->ch);
        }
    }

    if (((portRISE >> obj->ch) & 1) || ((portFALL >> obj->ch) & 1)) {
        if ((NRF_GPIO->IN >> obj->ch) & 1) {
            NRF_GPIO->PIN_CNF[obj->ch] |= (GPIO_PIN_CNF_SENSE_Low << GPIO_PIN_CNF_SENSE_Pos);    // | (GPIO_PIN_CNF_PULL_Disabled << GPIO_PIN_CNF_PULL_Pos);
        } else {
            NRF_GPIO->PIN_CNF[obj->ch] |= (GPIO_PIN_CNF_SENSE_High << GPIO_PIN_CNF_SENSE_Pos);     //| (GPIO_PIN_CNF_PULL_Disabled << GPIO_PIN_CNF_PULL_Pos);
        }
    }
}

void gpio_irq_enable(gpio_irq_t *obj)
{
    channel_enabled[obj->ch] = 1;
}

void gpio_irq_disable(gpio_irq_t *obj)
{
    channel_enabled[obj->ch] = 0;
}
