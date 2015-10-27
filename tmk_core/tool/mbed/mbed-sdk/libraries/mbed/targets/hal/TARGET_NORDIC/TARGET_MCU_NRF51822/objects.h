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
#ifndef MBED_OBJECTS_H
#define MBED_OBJECTS_H

#include "cmsis.h"
#include "PortNames.h"
#include "PeripheralNames.h"
#include "PinNames.h"

#ifdef __cplusplus
extern "C" {
#endif

#define I2C_SPI_PERIPHERAL_FOR_I2C      1
#define I2C_SPI_PERIPHERAL_FOR_SPI      2

typedef struct {
    uint8_t usage;   // I2C: 1, SPI: 2
    uint8_t sda_mosi;
    uint8_t scl_miso;
    uint8_t sclk;
} i2c_spi_peripheral_t;

struct serial_s {
    NRF_UART_Type *uart;
    int index;
};

struct spi_s {
    NRF_SPI_Type *spi;
    NRF_SPIS_Type *spis;
    uint8_t peripheral;
};

struct port_s {
    __IO uint32_t *reg_cnf;
    __IO uint32_t *reg_out;
    __I  uint32_t *reg_in;
    PortName port;
    uint32_t mask;
};

struct pwmout_s {
    PWMName pwm;
    PinName pin;
};

struct i2c_s {
    NRF_TWI_Type *i2c;
    PinName sda;
    PinName scl;
    int freq;
    uint8_t address_set;
    uint8_t peripheral;
};

struct analogin_s {
    ADCName adc;
    uint8_t adc_pin;
};

struct gpio_irq_s {
    uint32_t ch;
};

#include "gpio_object.h"

#ifdef __cplusplus
}
#endif

#endif
