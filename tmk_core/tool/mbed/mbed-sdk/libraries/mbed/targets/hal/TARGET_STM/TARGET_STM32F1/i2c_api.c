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
#include "mbed_assert.h"
#include "i2c_api.h"

#if DEVICE_I2C

#include "cmsis.h"
#include "pinmap.h"
#include "PeripheralPins.h"

/* Timeout values for flags and events waiting loops. These timeouts are
   not based on accurate values, they just guarantee that the application will
   not remain stuck if the I2C communication is corrupted. */
#define FLAG_TIMEOUT ((int)0x1000)
#define LONG_TIMEOUT ((int)0x8000)

I2C_HandleTypeDef I2cHandle;

void i2c_init(i2c_t *obj, PinName sda, PinName scl)
{
    static int i2c1_inited = 0;
    static int i2c2_inited = 0;

    // Determine the I2C to use
    I2CName i2c_sda = (I2CName)pinmap_peripheral(sda, PinMap_I2C_SDA);
    I2CName i2c_scl = (I2CName)pinmap_peripheral(scl, PinMap_I2C_SCL);

    obj->i2c = (I2CName)pinmap_merge(i2c_sda, i2c_scl);
    MBED_ASSERT(obj->i2c != (I2CName)NC);

    // Check if I2C peripherals are already configured
    if ((obj->i2c == I2C_1) && i2c1_inited) return;
    if ((obj->i2c == I2C_2) && i2c2_inited) return;

    // Set I2C clock
    if (obj->i2c == I2C_1) {
        i2c1_inited = 1;
        __I2C1_CLK_ENABLE();
    }

    if (obj->i2c == I2C_2) {
        i2c2_inited = 1;
        __I2C2_CLK_ENABLE();
    }

    // Configure I2C pins
    pinmap_pinout(sda, PinMap_I2C_SDA);
    pinmap_pinout(scl, PinMap_I2C_SCL);
    pin_mode(sda, OpenDrain);
    pin_mode(scl, OpenDrain);

    // Reset to clear pending flags if any
    i2c_reset(obj);

    // I2C configuration
    i2c_frequency(obj, 100000); // 100 kHz per default

    // I2C master by default
    obj->slave = 0;
}

void i2c_frequency(i2c_t *obj, int hz)
{
    MBED_ASSERT((hz != 0) && (hz <= 400000));
    I2cHandle.Instance = (I2C_TypeDef *)(obj->i2c);
    int timeout;

    // wait before init
    timeout = LONG_TIMEOUT;
    while ((__HAL_I2C_GET_FLAG(&I2cHandle, I2C_FLAG_BUSY)) && (timeout-- != 0));

    // I2C configuration
    I2cHandle.Init.ClockSpeed       = hz;
    I2cHandle.Init.DutyCycle        = I2C_DUTYCYCLE_2;
    I2cHandle.Init.OwnAddress1      = 0;
    I2cHandle.Init.AddressingMode   = I2C_ADDRESSINGMODE_7BIT;
    I2cHandle.Init.DualAddressMode  = I2C_DUALADDRESS_DISABLED;
    I2cHandle.Init.OwnAddress2      = 0;
    I2cHandle.Init.GeneralCallMode  = I2C_GENERALCALL_DISABLED;
    I2cHandle.Init.NoStretchMode    = I2C_NOSTRETCH_DISABLED;
    HAL_I2C_Init(&I2cHandle);

    if (obj->slave) {
        // Enable Address Acknowledge
        I2cHandle.Instance->CR1 |= I2C_CR1_ACK;
    }
}

inline int i2c_start(i2c_t *obj)
{
    I2C_TypeDef *i2c = (I2C_TypeDef *)(obj->i2c);
    int timeout;

    I2cHandle.Instance = (I2C_TypeDef *)(obj->i2c);

    // Clear Acknowledge failure flag
    __HAL_I2C_CLEAR_FLAG(&I2cHandle, I2C_FLAG_AF);

    // Generate the START condition
    i2c->CR1 |= I2C_CR1_START;

    // Wait the START condition has been correctly sent
    timeout = FLAG_TIMEOUT;
    while (__HAL_I2C_GET_FLAG(&I2cHandle, I2C_FLAG_SB) == RESET) {
        if ((timeout--) == 0) {
            return 1;
        }
    }

    return 0;
}

inline int i2c_stop(i2c_t *obj)
{
    I2C_TypeDef *i2c = (I2C_TypeDef *)(obj->i2c);

    // Generate the STOP condition
    i2c->CR1 |= I2C_CR1_STOP;

    return 0;
}

int i2c_read(i2c_t *obj, int address, char *data, int length, int stop)
{
    I2C_TypeDef *i2c = (I2C_TypeDef *)(obj->i2c);
    I2cHandle.Instance = (I2C_TypeDef *)(obj->i2c);
    int timeout;
    int count;
    int value;

    // Generate start condition
    i2c_start(obj);

    // Send address for read
    i2c->DR = __HAL_I2C_7BIT_ADD_READ(address);

    // Wait address is acknowledged
    timeout = FLAG_TIMEOUT;
    while (__HAL_I2C_GET_FLAG(&I2cHandle, I2C_FLAG_ADDR) == RESET) {
        timeout--;
        if (timeout == 0) {
            return -1;
        }
    }
    __HAL_I2C_CLEAR_ADDRFLAG(&I2cHandle);

    // Read all bytes except last one
    for (count = 0; count < (length - 1); count++) {
        value = i2c_byte_read(obj, 0);
        data[count] = (char)value;
    }

    // If not repeated start, send stop.
    // Warning: must be done BEFORE the data is read.
    if (stop) {
        i2c_stop(obj);
    }

    // Read the last byte
    value = i2c_byte_read(obj, 1);
    data[count] = (char)value;

    return length;
}

int i2c_write(i2c_t *obj, int address, const char *data, int length, int stop)
{
    I2C_TypeDef *i2c = (I2C_TypeDef *)(obj->i2c);
    I2cHandle.Instance = (I2C_TypeDef *)(obj->i2c);
    int timeout;
    int count;

    // Generate start condition
    i2c_start(obj);

    // Send address for write
    i2c->DR = __HAL_I2C_7BIT_ADD_WRITE(address);

    // Wait address is acknowledged
    timeout = FLAG_TIMEOUT;
    while (__HAL_I2C_GET_FLAG(&I2cHandle, I2C_FLAG_ADDR) == RESET) {
        timeout--;
        if (timeout == 0) {
            return -1;
        }
    }
    __HAL_I2C_CLEAR_ADDRFLAG(&I2cHandle);

    // Write all bytes
    for (count = 0; count < length; count++) {
        if (i2c_byte_write(obj, data[count]) != 1) {
            i2c_stop(obj);
            return -1;
        }
    }

    // If not repeated start, send stop.
    if (stop) {
        i2c_stop(obj);
    }

    return count;
}

int i2c_byte_read(i2c_t *obj, int last)
{
    I2C_TypeDef *i2c = (I2C_TypeDef *)(obj->i2c);
    int timeout;

    if (last) {
        // Don't acknowledge the last byte
        i2c->CR1 &= ~I2C_CR1_ACK;
    } else {
        // Acknowledge the byte
        i2c->CR1 |= I2C_CR1_ACK;
    }

    // Wait until the byte is received
    timeout = FLAG_TIMEOUT;
    while (__HAL_I2C_GET_FLAG(&I2cHandle, I2C_FLAG_RXNE) == RESET) {
        if ((timeout--) == 0) {
            return -1;
        }
    }

    return (int)i2c->DR;
}

int i2c_byte_write(i2c_t *obj, int data)
{
    I2C_TypeDef *i2c = (I2C_TypeDef *)(obj->i2c);
    int timeout;

    i2c->DR = (uint8_t)data;

    // Wait until the byte is transmitted
    timeout = FLAG_TIMEOUT;
    while ((__HAL_I2C_GET_FLAG(&I2cHandle, I2C_FLAG_TXE) == RESET) &&
            (__HAL_I2C_GET_FLAG(&I2cHandle, I2C_FLAG_BTF) == RESET)) {
        if ((timeout--) == 0) {
            return 0;
        }
    }

    return 1;
}

void i2c_reset(i2c_t *obj)
{
    int timeout;

    // Wait before reset
    timeout = LONG_TIMEOUT;
    while ((__HAL_I2C_GET_FLAG(&I2cHandle, I2C_FLAG_BUSY)) && (timeout-- != 0));

    if (obj->i2c == I2C_1) {
        __I2C1_FORCE_RESET();
        __I2C1_RELEASE_RESET();
    }

    if (obj->i2c == I2C_2) {
        __I2C2_FORCE_RESET();
        __I2C2_RELEASE_RESET();
    }
}

#if DEVICE_I2CSLAVE

void i2c_slave_address(i2c_t *obj, int idx, uint32_t address, uint32_t mask)
{
    I2C_TypeDef *i2c = (I2C_TypeDef *)(obj->i2c);
    uint16_t tmpreg = 0;

    // Get the old register value
    tmpreg = i2c->OAR1;
    // Reset address bits
    tmpreg &= 0xFC00;
    // Set new address
    tmpreg |= (uint16_t)((uint16_t)address & (uint16_t)0x00FE); // 7-bits
    // Store the new register value
    i2c->OAR1 = tmpreg;
}

void i2c_slave_mode(i2c_t *obj, int enable_slave)
{
    I2cHandle.Instance = (I2C_TypeDef *)(obj->i2c);
    if (enable_slave) {
        obj->slave = 1;
        /* Enable Address Acknowledge */
        I2cHandle.Instance->CR1 |= I2C_CR1_ACK;
    }
}

// See I2CSlave.h
#define NoData         0 // the slave has not been addressed
#define ReadAddressed  1 // the master has requested a read from this slave (slave = transmitter)
#define WriteGeneral   2 // the master is writing to all slave
#define WriteAddressed 3 // the master is writing to this slave (slave = receiver)

int i2c_slave_receive(i2c_t *obj)
{
    I2cHandle.Instance = (I2C_TypeDef *)(obj->i2c);
    int retValue = NoData;

    if (__HAL_I2C_GET_FLAG(&I2cHandle, I2C_FLAG_BUSY) == 1) {
        if (__HAL_I2C_GET_FLAG(&I2cHandle, I2C_FLAG_ADDR) == 1) {
            if (__HAL_I2C_GET_FLAG(&I2cHandle, I2C_FLAG_TRA) == 1) {
                retValue = ReadAddressed;
            } else {
                retValue = WriteAddressed;
            }
            __HAL_I2C_CLEAR_FLAG(&I2cHandle, I2C_FLAG_ADDR);
        }
    }

    return (retValue);
}

int i2c_slave_read(i2c_t *obj, char *data, int length)
{
    uint32_t Timeout;
    int size = 0;

    I2cHandle.Instance = (I2C_TypeDef *)(obj->i2c);

    while (length > 0) {
        // Wait until RXNE flag is set
        // Wait until the byte is received
        Timeout = FLAG_TIMEOUT;
        while (__HAL_I2C_GET_FLAG(&I2cHandle, I2C_FLAG_RXNE) == RESET) {
            Timeout--;
            if (Timeout == 0) {
                return -1;
            }
        }

        // Read data
        (*data++) = I2cHandle.Instance->DR;
        length--;
        size++;

        if ((__HAL_I2C_GET_FLAG(&I2cHandle, I2C_FLAG_BTF) == SET) && (length != 0)) {
            // Read data
            (*data++) = I2cHandle.Instance->DR;
            length--;
            size++;
        }
    }

    // Wait until STOP flag is set
    Timeout = FLAG_TIMEOUT;
    while (__HAL_I2C_GET_FLAG(&I2cHandle, I2C_FLAG_STOPF) == RESET) {
        Timeout--;
        if (Timeout == 0) {
            return -1;
        }
    }

    // Clear STOP flag
    __HAL_I2C_CLEAR_STOPFLAG(&I2cHandle);

    // Wait until BUSY flag is reset
    Timeout = FLAG_TIMEOUT;
    while (__HAL_I2C_GET_FLAG(&I2cHandle, I2C_FLAG_BUSY) == SET) {
        Timeout--;
        if (Timeout == 0) {
            return -1;
        }
    }

    return size;
}

int i2c_slave_write(i2c_t *obj, const char *data, int length)
{
    uint32_t Timeout;
    int size = 0;

    I2cHandle.Instance = (I2C_TypeDef *)(obj->i2c);

    while (length > 0) {
        // Wait until TXE flag is set
        Timeout = FLAG_TIMEOUT;
        while (__HAL_I2C_GET_FLAG(&I2cHandle, I2C_FLAG_TXE) == RESET) {
            Timeout--;
            if (Timeout == 0) {
                return -1;
            }
        }

        // Write data
        I2cHandle.Instance->DR = (*data++);
        length--;
        size++;

        if ((__HAL_I2C_GET_FLAG(&I2cHandle, I2C_FLAG_BTF) == SET) && (length != 0)) {
            // Write data to DR
            I2cHandle.Instance->DR = (*data++);
            length--;
            size++;
        }
    }

    // Wait until AF flag is set
    Timeout = FLAG_TIMEOUT;
    while (__HAL_I2C_GET_FLAG(&I2cHandle, I2C_FLAG_AF) == RESET) {
        Timeout--;
        if (Timeout == 0) {
            return -1;
        }
    }

    // Clear AF flag
    __HAL_I2C_CLEAR_FLAG(&I2cHandle, I2C_FLAG_AF);

    // Wait until BUSY flag is reset
    Timeout = FLAG_TIMEOUT;
    while (__HAL_I2C_GET_FLAG(&I2cHandle, I2C_FLAG_BUSY) == SET) {
        Timeout--;
        if (Timeout == 0) {
            return -1;
        }
    }

    return size;
}


#endif // DEVICE_I2CSLAVE

#endif // DEVICE_I2C
