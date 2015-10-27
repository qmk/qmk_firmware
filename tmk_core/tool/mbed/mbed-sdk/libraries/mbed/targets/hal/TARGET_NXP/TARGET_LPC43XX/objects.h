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
#ifndef MBED_OBJECTS_H
#define MBED_OBJECTS_H

#include "cmsis.h"
#include "PortNames.h"
#include "PeripheralNames.h"
#include "PinNames.h"
#include "gpio_object.h"

#ifdef __cplusplus
extern "C" {
#endif

struct gpio_irq_s {
    uint32_t port;
    uint32_t pin;
    uint32_t ch;
};

struct port_s {
    __IO uint32_t *reg_dir;
    __IO uint32_t *reg_out;
    __I  uint32_t *reg_in;
    PortName port;
    uint32_t mask;
};

struct pwmout_s {
    PWMName pwm;
    uint8_t mr;
};

struct serial_s {
    LPC_USART_T *uart;
    int index;
};

struct analogin_s {
    LPC_ADC_T *adc;
    uint8_t num;
    uint8_t ch;
};

struct dac_s {
    DACName dac;
};

struct can_s {
    LPC_CCAN_T *dev;
};

struct i2c_s {
    LPC_I2C_T *i2c;
};

struct spi_s {
    LPC_SSP_T *spi;
};

#ifdef __cplusplus
}
#endif

#endif
