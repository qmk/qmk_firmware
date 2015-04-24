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
#include "mbed_assert.h"
#include "i2c_api.h"
#include "cmsis.h"
#include "pinmap.h"
#include "mbed_error.h"

// nRF51822's I2C_0 and SPI_0 (I2C_1, SPI_1 and SPIS1) share the same address.
// They can't be used at the same time. So we use two global variable to track the usage.
// See nRF51822 address information at nRF51822_PS v2.0.pdf - Table 15 Peripheral instance reference
volatile i2c_spi_peripheral_t i2c0_spi0_peripheral = {0, 0, 0, 0};
volatile i2c_spi_peripheral_t i2c1_spi1_peripheral = {0, 0, 0, 0};

void i2c_interface_enable(i2c_t *obj)
{
    obj->i2c->ENABLE = (TWI_ENABLE_ENABLE_Enabled << TWI_ENABLE_ENABLE_Pos);
}

void twi_master_init(i2c_t *obj, PinName sda, PinName scl, int frequency)
{
    NRF_GPIO->PIN_CNF[scl] = ((GPIO_PIN_CNF_DIR_Input << GPIO_PIN_CNF_DIR_Pos) |
                              (GPIO_PIN_CNF_INPUT_Connect << GPIO_PIN_CNF_INPUT_Pos) |
                              (GPIO_PIN_CNF_PULL_Disabled << GPIO_PIN_CNF_PULL_Pos) |
                              (GPIO_PIN_CNF_DRIVE_S0D1 << GPIO_PIN_CNF_DRIVE_Pos) |
                              (GPIO_PIN_CNF_SENSE_Disabled << GPIO_PIN_CNF_SENSE_Pos));

    NRF_GPIO->PIN_CNF[sda] = ((GPIO_PIN_CNF_DIR_Input << GPIO_PIN_CNF_DIR_Pos) |
                              (GPIO_PIN_CNF_INPUT_Connect << GPIO_PIN_CNF_INPUT_Pos) |
                              (GPIO_PIN_CNF_PULL_Disabled << GPIO_PIN_CNF_PULL_Pos) |
                              (GPIO_PIN_CNF_DRIVE_S0D1 << GPIO_PIN_CNF_DRIVE_Pos) |
                              (GPIO_PIN_CNF_SENSE_Disabled << GPIO_PIN_CNF_SENSE_Pos));

    obj->i2c->PSELSCL = scl;
    obj->i2c->PSELSDA = sda;
    // set default frequency at 100k
    i2c_frequency(obj, frequency);
    i2c_interface_enable(obj);
}

void i2c_init(i2c_t *obj, PinName sda, PinName scl)
{
    NRF_TWI_Type *i2c;
  
    if (i2c0_spi0_peripheral.usage == I2C_SPI_PERIPHERAL_FOR_I2C &&
            i2c0_spi0_peripheral.sda_mosi == (uint8_t)sda &&
            i2c0_spi0_peripheral.scl_miso == (uint8_t)scl) {
        // The I2C with the same pins is already initialized
        i2c = (NRF_TWI_Type *)I2C_0;
        obj->peripheral = 0x1;
    } else if (i2c1_spi1_peripheral.usage == I2C_SPI_PERIPHERAL_FOR_I2C &&
            i2c1_spi1_peripheral.sda_mosi == (uint8_t)sda &&
            i2c1_spi1_peripheral.scl_miso == (uint8_t)scl) {
        // The I2C with the same pins is already initialized
        i2c = (NRF_TWI_Type *)I2C_1;
        obj->peripheral = 0x2;
    } else if (i2c0_spi0_peripheral.usage == 0) {
        i2c0_spi0_peripheral.usage = I2C_SPI_PERIPHERAL_FOR_I2C;
        i2c0_spi0_peripheral.sda_mosi = (uint8_t)sda;
        i2c0_spi0_peripheral.scl_miso = (uint8_t)scl;
        
        i2c = (NRF_TWI_Type *)I2C_0;
        obj->peripheral = 0x1;
    } else if (i2c1_spi1_peripheral.usage == 0) {
        i2c1_spi1_peripheral.usage = I2C_SPI_PERIPHERAL_FOR_I2C;
        i2c1_spi1_peripheral.sda_mosi = (uint8_t)sda;
        i2c1_spi1_peripheral.scl_miso = (uint8_t)scl;
        
        i2c = (NRF_TWI_Type *)I2C_1;
        obj->peripheral = 0x2;
    } else {
        // No available peripheral
        error("No available I2C");
    }

    obj->i2c               = i2c;
    obj->scl               = scl;
    obj->sda               = sda;
    obj->i2c->EVENTS_ERROR = 0;
    obj->i2c->ENABLE       = TWI_ENABLE_ENABLE_Disabled << TWI_ENABLE_ENABLE_Pos;
    obj->i2c->POWER        = 0;

    for (int i = 0; i<100; i++) {
    }

    obj->i2c->POWER = 1;
    twi_master_init(obj, sda, scl, 100000);
}

void i2c_reset(i2c_t *obj)
{
    obj->i2c->EVENTS_ERROR = 0;
    obj->i2c->ENABLE       = TWI_ENABLE_ENABLE_Disabled << TWI_ENABLE_ENABLE_Pos;
    obj->i2c->POWER        = 0;
    for (int i = 0; i<100; i++) {
    }

    obj->i2c->POWER = 1;
    twi_master_init(obj, obj->sda, obj->scl, obj->freq);
}

int i2c_start(i2c_t *obj)
{
    int status = 0;
    i2c_reset(obj);
    obj->address_set = 0;
    return status;
}

int i2c_stop(i2c_t *obj)
{
    int timeOut = 100000;
    obj->i2c->EVENTS_STOPPED = 0;
    // write the stop bit
    obj->i2c->TASKS_STOP = 1;
    while (!obj->i2c->EVENTS_STOPPED) {
        timeOut--;
        if (timeOut<0) {
            return 1;
        }
    }
    obj->address_set = 0;
    i2c_reset(obj);
    return 0;
}

int i2c_do_write(i2c_t *obj, int value)
{
    int timeOut = 100000;
    obj->i2c->TXD = value;
    while (!obj->i2c->EVENTS_TXDSENT) {
        timeOut--;
        if (timeOut<0) {
            return 1;
        }
    }
    obj->i2c->EVENTS_TXDSENT = 0;
    return 0;
}

int i2c_do_read(i2c_t *obj, char *data, int last)
{
    int timeOut = 100000;

    if (last) {
        // To trigger stop task when a byte is received,
        // must be set before resume task.
        obj->i2c->SHORTS = 2;
    }

    obj->i2c->TASKS_RESUME = 1;

    while (!obj->i2c->EVENTS_RXDREADY) {
        timeOut--;
        if (timeOut<0) {
            return 1;
        }
    }
    obj->i2c->EVENTS_RXDREADY = 0;
    *data = obj->i2c->RXD;

    return 0;
}

void i2c_frequency(i2c_t *obj, int hz)
{
    if (hz<250000) {
        obj->freq           = 100000;
        obj->i2c->FREQUENCY = (TWI_FREQUENCY_FREQUENCY_K100 << TWI_FREQUENCY_FREQUENCY_Pos);
    } else if (hz<400000) {
        obj->freq           = 250000;
        obj->i2c->FREQUENCY = (TWI_FREQUENCY_FREQUENCY_K250 << TWI_FREQUENCY_FREQUENCY_Pos);
    } else {
        obj->freq           = 400000;
        obj->i2c->FREQUENCY = (TWI_FREQUENCY_FREQUENCY_K400 << TWI_FREQUENCY_FREQUENCY_Pos);
    }
}

int checkError(i2c_t *obj)
{
    if (obj->i2c->EVENTS_ERROR == 1) {
        if (obj->i2c->ERRORSRC & TWI_ERRORSRC_ANACK_Msk) {
            obj->i2c->EVENTS_ERROR = 0;
            obj->i2c->TASKS_STOP   = 1;
            return I2C_ERROR_BUS_BUSY;
        }

        obj->i2c->EVENTS_ERROR = 0;
        obj->i2c->TASKS_STOP   = 1;
        return I2C_ERROR_NO_SLAVE;
    }
    return 0;
}

int i2c_read(i2c_t *obj, int address, char *data, int length, int stop)
{
    int status, count, errorResult;
    obj->i2c->ADDRESS         = (address >> 1);
    obj->i2c->SHORTS          = 1;  // to trigger suspend task when a byte is received
    obj->i2c->EVENTS_RXDREADY = 0;
    obj->i2c->TASKS_STARTRX   = 1;

    // Read in all except last byte
    for (count = 0; count < (length - 1); count++) {
        status = i2c_do_read(obj, &data[count], 0);
        if (status) {
            errorResult = checkError(obj);
            i2c_reset(obj);
            if (errorResult<0) {
                return errorResult;
            }
            return count;
        }
    }

    // read in last byte
    status = i2c_do_read(obj, &data[length - 1], 1);
    if (status) {
        i2c_reset(obj);
        return length - 1;
    }
    // If not repeated start, send stop.
    if (stop) {
        while (!obj->i2c->EVENTS_STOPPED) {
        }
        obj->i2c->EVENTS_STOPPED = 0;
    }
    return length;
}

int i2c_write(i2c_t *obj, int address, const char *data, int length, int stop)
{
    int status, errorResult;
    obj->i2c->ADDRESS       = (address >> 1);
    obj->i2c->SHORTS        = 0;
    obj->i2c->TASKS_STARTTX = 1;

    for (int i = 0; i<length; i++) {
        status = i2c_do_write(obj, data[i]);
        if (status) {
            i2c_reset(obj);
            errorResult = checkError(obj);
            if (errorResult<0) {
                return errorResult;
            }
            return i;
        }
    }

    // If not repeated start, send stop.
    if (stop) {
        if (i2c_stop(obj)) {
            return I2C_ERROR_NO_SLAVE;
        }
    }
    return length;
}

int i2c_byte_read(i2c_t *obj, int last)
{
    char data;
    int status;

    status = i2c_do_read(obj, &data, last);
    if (status) {
        i2c_reset(obj);
    }
    return data;
}

int i2c_byte_write(i2c_t *obj, int data)
{
    int status = 0;
    if (!obj->address_set) {
        obj->address_set  = 1;
        obj->i2c->ADDRESS = (data >> 1);

        if (data & 1) {
            obj->i2c->EVENTS_RXDREADY = 0;
            obj->i2c->SHORTS          = 1;
            obj->i2c->TASKS_STARTRX   = 1;
        } else {
            obj->i2c->SHORTS        = 0;
            obj->i2c->TASKS_STARTTX = 1;
        }
    } else {
        status = i2c_do_write(obj, data);
        if (status) {
            i2c_reset(obj);
        }
    }
    return (1 - status);
}
