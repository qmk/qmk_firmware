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
 
#ifndef MBED_OBJECTS_H
#define MBED_OBJECTS_H

#include "cmsis.h"
#include "PortNames.h"
#include "PeripheralNames.h"
#include "PinNames.h"
#include "gpio_object.h"
#include "gpio_regs.h"
#include "uart_regs.h"
#include "i2cm_regs.h"
#include "spi_regs.h"
#include "pt_regs.h"
#include "adc_regs.h"
#include "dac_regs.h"

#ifdef __cplusplus
extern "C" {
#endif

struct port_s {
    PortName port;
    uint32_t mask;
    __IO uint32_t *reg_out;
    __I  uint32_t *reg_in;
};

struct gpio_irq_s {
    uint8_t port;
    uint8_t pin;
};

struct serial_s {
    int index;
    mxc_uart_regs_t *uart;
};

struct i2c_s {
    int index;
    mxc_i2cm_regs_t *i2c;
    volatile uint16_t *txfifo;
    volatile uint16_t *rxfifo;
    int start_pending;
    int stop_pending;
};

struct spi_s {
    int index;
    mxc_spi_regs_t *spi;
    mxc_spi_rxfifo_regs_t *rxfifo;
    mxc_spi_txfifo_regs_t *txfifo;
};

struct pwmout_s {
    mxc_pt_regs_t *pwm;
    int period;
    int pulse_width;
};

struct analogin_s {
    mxc_adc_regs_t *adc;
    mxc_adccfg_regs_t *adccfg;
    mxc_adc_fifo_regs_t * adc_fifo;
    PinName adc_pin;
};

struct dac_s {
    int index;
    uint16_t out;
    mxc_dac_regs_t *dac;
    mxc_dac_fifo_t * dac_fifo;
};

typedef struct {
    volatile uint32_t *reg_req;
    volatile uint32_t *reg_ack;
    uint32_t req_val;
    uint32_t ack_mask;
} pin_function_t;

#ifdef __cplusplus
}
#endif

#endif
