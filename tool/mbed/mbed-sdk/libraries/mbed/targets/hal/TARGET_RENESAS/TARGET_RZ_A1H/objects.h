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

#include <stdint.h>
#include "cmsis.h"
#include "PortNames.h"
#include "PeripheralNames.h"
#include "PinNames.h"
#include "gpio_object.h"
#include "rspi_iodefine.h"

#ifdef __cplusplus
extern "C" {
#endif

struct i2c_s {
    uint32_t i2c;
    uint32_t dummy;
    uint8_t  pclk_bit;
    uint8_t  width_low;
    uint8_t  width_hi;
    int      bbsy_wait_cnt;
    int      last_stop_flag;
};

struct spi_s {
    struct st_rspi *spi;
    uint32_t       bits;
};

struct gpio_irq_s {
    uint32_t port;
    uint32_t pin;
    uint32_t ch;
    uint8_t  int_enable;
};

struct port_s {
    __IO uint32_t *reg_dir;
    __IO uint32_t *reg_out;
    __I  uint32_t *reg_in;
    PortName port;
    uint32_t mask;
};

struct serial_s {
    struct st_scif *uart;
    int index;
};

struct pwmout_s {
    uint32_t ch;
    PWMName pwm;
};

struct analogin_s {
    ADCName adc;
};

#ifdef __cplusplus
}
#endif

#endif
