/*
 * Copyright (c) 2021 Valentin Milea <valentin.milea@gmail.com>
 * Copyright (c) 2023 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _PICO_I2C_SLAVE_H
#define _PICO_I2C_SLAVE_H

#include "hardware/i2c.h"

#ifdef __cplusplus
extern "C" {
#endif

/** \file pico/i2c_slave.h
 * \defgroup pico_i2c_slave pico_i2c_slave
 *
 * Functions providing an interrupt driven I2C slave interface.
 *
 * This I2C slave helper library configures slave mode and hooks the relevant I2C IRQ
 * so that a user supplied handler is called with enumerated I2C events.
 *
 * An example application \c slave_mem_i2c, which makes use of this library, can be found in 
 * <a href="https://github.com/raspberrypi/pico-examples/blob/master/i2c/slave_mem_i2c/slave_mem_i2c.c">pico_examples</a>.
 */

/**
 * \brief I2C slave event types.
 * \ingroup pico_i2c_slave
 */
typedef enum i2c_slave_event_t
{
    I2C_SLAVE_RECEIVE, /**< Data from master is available for reading. Slave must read from Rx FIFO. */
    I2C_SLAVE_REQUEST, /**< Master is requesting data. Slave must write into Tx FIFO. */
    I2C_SLAVE_FINISH, /**< Master has sent a Stop or Restart signal. Slave may prepare for the next transfer. */
} i2c_slave_event_t;

/**
 * \brief I2C slave event handler
 * \ingroup pico_i2c_slave
 * 
 * The event handler will run from the I2C ISR, so it should return quickly (under 25 us at 400 kb/s).
 * Avoid blocking inside the handler and split large data transfers across multiple calls for best results.
 * When sending data to master, up to \ref i2c_get_write_available()  bytes can be written without blocking.
 * When receiving data from master, up to \ref 2c_get_read_available() bytes can be read without blocking.
 *
 * \param i2c Either \ref i2c0 or \ref i2c1
 * \param event Event type.
 */
typedef void (*i2c_slave_handler_t)(i2c_inst_t *i2c, i2c_slave_event_t event);

/**
 * \brief Configure an I2C instance for slave mode.
 * \ingroup pico_i2c_slave
 * \param i2c I2C instance.
 * \param address 7-bit slave address.
 * \param handler Callback for events from I2C master. It will run from the I2C ISR, on the CPU core
 *                where the slave was initialised.
 */
void i2c_slave_init(i2c_inst_t *i2c, uint8_t address, i2c_slave_handler_t handler);

/**
 * \brief Restore an I2C instance to master mode.
 * \ingroup pico_i2c_slave
 * \param i2c Either \ref i2c0 or \ref i2c1
 */
void i2c_slave_deinit(i2c_inst_t *i2c);

#ifdef __cplusplus
}
#endif

#endif // _PICO_I2C_SLAVE_H_
