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

#ifdef __cplusplus
extern "C" {
#endif

#if DEVICE_INTERRUPTIN
struct gpio_irq_s {
    uint32_t ch;
};
#endif

#if DEVICE_PWMOUT
struct pwmout_s {
     LPC_SCT0_Type* pwm;
     uint32_t pwm_ch;
};
#endif

#if DEVICE_SERIAL
struct serial_s {
    LPC_USART0_Type *uart;
    LPC_USART4_Type *mini_uart;
    unsigned char index;
};
#endif

#if DEVICE_ANALOGIN
struct analogin_s {
    ADCName adc;
};
#endif

#if DEVICE_ANALOGOUT
struct dac_s {
    DACName dac;
};
#endif

#if DEVICE_I2C
struct i2c_s {
    LPC_I2C0_Type *i2c;
};
#endif

#if DEVICE_SPI
struct spi_s {
    LPC_SSP0_Type *spi;
    unsigned char spi_n;
};
#endif

#include "gpio_object.h"

#ifdef __cplusplus
}
#endif

#endif
