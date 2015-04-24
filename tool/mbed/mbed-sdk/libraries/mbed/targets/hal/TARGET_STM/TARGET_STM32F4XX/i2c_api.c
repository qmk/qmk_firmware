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
#include "mbed_assert.h"
#include "i2c_api.h"

#if DEVICE_I2C

#include "cmsis.h"
#include "pinmap.h"
#include "mbed_error.h"

static const PinMap PinMap_I2C_SDA[] = {
    {PB_7,  I2C_1, STM_PIN_DATA(2, 4)},
    {PB_9,  I2C_1, STM_PIN_DATA(2, 4)},
    {PB_11, I2C_2, STM_PIN_DATA(2, 4)},
    {PC_9,  I2C_3, STM_PIN_DATA(2, 4)},
    {PF_0,  I2C_2, STM_PIN_DATA(2, 4)},
    {PH_5,  I2C_2, STM_PIN_DATA(2, 4)},
    {PH_8,  I2C_3, STM_PIN_DATA(2, 4)},
    {NC,    NC,    0}
};

static const PinMap PinMap_I2C_SCL[] = {
    {PA_8,  I2C_3, STM_PIN_DATA(2, 4)},
    {PB_6,  I2C_1, STM_PIN_DATA(2, 4)},
    {PB_8,  I2C_1, STM_PIN_DATA(2, 4)},
    {PB_10, I2C_2, STM_PIN_DATA(2, 4)},
    {PF_1,  I2C_2, STM_PIN_DATA(2, 4)},
    {PH_4,  I2C_2, STM_PIN_DATA(2, 4)},
    {PH_7,  I2C_3, STM_PIN_DATA(2, 4)},
    {NC,    NC,    0}
};

static const uint32_t I2C_addr_offset[2][4] = {
    {0x0C, 0x20, 0x24, 0x28},
    {0x30, 0x34, 0x38, 0x3C}
};


static inline void i2c_interface_enable(i2c_t *obj) {
    obj->i2c->CR1 |= I2C_CR1_PE;
}

static inline void i2c_interface_disable(i2c_t *obj) {
    obj->i2c->CR1 &= ~I2C_CR1_PE;
}


static inline void i2c_power_enable(i2c_t *obj) {
    switch ((int)obj->i2c) {
        case I2C_1:
            RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
            RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;
            break;
        case I2C_2:
            RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN | RCC_AHB1ENR_GPIOFEN |
                            RCC_AHB1ENR_GPIOHEN;
            RCC->APB1ENR |= RCC_APB1ENR_I2C2EN;
            break;
        case I2C_3:
            RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIOCEN |
                            RCC_AHB1ENR_GPIOHEN;
            RCC->APB1ENR |= RCC_APB1ENR_I2C3EN;
            break;
    }
}

static inline void i2c_wait_status(i2c_t *obj, uint32_t sr1_mask,
                                   uint32_t sr2_mask) {
    while (!(((obj->i2c->SR1 & sr1_mask) >= sr1_mask) &&
             ((obj->i2c->SR2 & sr2_mask) == sr2_mask)));
}

// Wait until the slave address has been acknowledged
static inline void i2c_wait_addr_tx(i2c_t *obj) {
    uint32_t sr1_mask = I2C_SR1_ADDR | I2C_SR1_TXE;
    uint32_t sr2_mask = I2C_SR2_MSL | I2C_SR2_BUSY | I2C_SR2_TRA;
    i2c_wait_status(obj, sr1_mask, sr2_mask);
}

// Wait until the slave address has been acknowledged
static inline void i2c_wait_addr_rx(i2c_t *obj) {
    uint32_t sr1_mask = I2C_SR1_ADDR;
    uint32_t sr2_mask = I2C_SR2_MSL | I2C_SR2_BUSY;
    i2c_wait_status(obj, sr1_mask, sr2_mask);
}


// Wait until a byte has been sent
static inline void i2c_wait_send(i2c_t *obj) {
    uint32_t sr1_mask = I2C_SR1_BTF | I2C_SR1_TXE;
    uint32_t sr2_mask = I2C_SR2_MSL | I2C_SR2_BUSY | I2C_SR2_TRA;
    i2c_wait_status(obj, sr1_mask, sr2_mask);
}

// Wait until a byte has been received
static inline void i2c_wait_receive(i2c_t *obj) {
    uint32_t sr1_mask = I2C_SR1_RXNE;
    uint32_t sr2_mask = I2C_SR2_MSL | I2C_SR2_BUSY;
    i2c_wait_status(obj, sr1_mask, sr2_mask);
}

// Wait until the start condition has been accepted
static inline void i2c_wait_start(i2c_t *obj) {
    uint32_t sr1_mask = I2C_SR1_SB;
    uint32_t sr2_mask = I2C_SR2_MSL | I2C_SR2_BUSY;
    i2c_wait_status(obj, sr1_mask, sr2_mask);
}

void i2c_init(i2c_t *obj, PinName sda, PinName scl) {
    // determine the SPI to use
    I2CName i2c_sda = (I2CName)pinmap_peripheral(sda, PinMap_I2C_SDA);
    I2CName i2c_scl = (I2CName)pinmap_peripheral(scl, PinMap_I2C_SCL);
    obj->i2c = (I2C_TypeDef *)pinmap_merge(i2c_sda, i2c_scl);
    MBED_ASSERT((int)obj->i2c != NC);

    // enable power
    i2c_power_enable(obj);

    pinmap_pinout(sda, PinMap_I2C_SDA);
    pinmap_pinout(scl, PinMap_I2C_SCL);

    pin_mode(sda, OpenDrain);
    pin_mode(scl, OpenDrain);

    // Force reset if the bus is stuck in the BUSY state
    if (obj->i2c->SR2 & I2C_SR2_BUSY) {
        obj->i2c->CR1 |= I2C_CR1_SWRST;
        obj->i2c->CR1 &= ~I2C_CR1_SWRST;
    }

    // Set the peripheral clock frequency
    obj->i2c->CR2 |= 42;

    // set default frequency at 100k
    i2c_frequency(obj, 100000);
    i2c_interface_enable(obj);
}

inline int i2c_start(i2c_t *obj) {
    // Wait until we are not busy any more
    while (obj->i2c->SR2 & I2C_SR2_BUSY);

    // Generate the start condition
    obj->i2c->CR1 |= I2C_CR1_START;
    i2c_wait_start(obj);

    return 0;
}

inline int i2c_stop(i2c_t *obj) {
    // Generate the stop condition
    obj->i2c->CR1 |= I2C_CR1_STOP;
    return 0;
}


static inline int i2c_do_write(i2c_t *obj, int value, uint8_t addr) {
    obj->i2c->DR = value;
    return 0;
}

static inline int i2c_do_read(i2c_t *obj, int last) {
    if(last) {
        // Don't acknowledge the byte
        obj->i2c->CR1 &= ~(I2C_CR1_ACK);
    } else {
        // Acknowledge the byte
        obj->i2c->CR1 |= I2C_CR1_ACK;
    }

    // Wait until we receive the byte
    i2c_wait_receive(obj);

    int data = obj->i2c->DR;
    return data;
}

void i2c_frequency(i2c_t *obj, int hz) {
    i2c_interface_disable(obj);
    obj->i2c->CCR &= ~(I2C_CCR_CCR | I2C_CCR_FS);
    if (hz > 100000) {
        // Fast Mode
        obj->i2c->CCR |= I2C_CCR_FS;
        int result = 42000000 / (hz * 3);
        obj->i2c->CCR |= result & I2C_CCR_CCR;
        obj->i2c->TRISE = ((42 * 300) / 1000) + 1;
    }
    else {
        // Standard mode
        obj->i2c->CCR &= ~I2C_CCR_FS;
        int result = 42000000 / (hz << 1);
        result = result < 0x4 ? 0x4 : result;
        obj->i2c->CCR |= result & I2C_CCR_CCR;
        obj->i2c->TRISE = 42 + 1;
    }
    i2c_interface_enable(obj);
}

// The I2C does a read or a write as a whole operation
// There are two types of error conditions it can encounter
//  1) it can not obtain the bus
//  2) it gets error responses at part of the transmission
//
// We tackle them as follows:
//  1) we retry until we get the bus. we could have a "timeout" if we can not get it
//      which basically turns it in to a 2)
//  2) on error, we use the standard error mechanisms to report/debug
//
// Therefore an I2C transaction should always complete. If it doesn't it is usually
// because something is setup wrong (e.g. wiring), and we don't need to programatically
// check for that

int i2c_read(i2c_t *obj, int address, char *data, int length, int stop) {
    int count;

    i2c_start(obj);

    // Send the slave address
    i2c_do_write(obj, (address | 0x01), 1);

    // Wait until we have transmitted and the ADDR byte is set
    i2c_wait_addr_rx(obj);

    // Read in all except last byte
    for (count = 0; count < (length - 1); count++) {
        int value = i2c_do_read(obj, 0);
        data[count] = (char) value;
    }

    // read in last byte
    int value = i2c_do_read(obj, 1);
    data[count] = (char) value;

    // If not repeated start, send stop.
    if (stop) {
        i2c_stop(obj);
    }

    return length;
}

int i2c_write(i2c_t *obj, int address, const char *data, int length, int stop) {
    int i;

    i2c_start(obj);

    // Send the slave address
    i2c_do_write(obj, (address & 0xFE), 1);
    i2c_wait_addr_tx(obj);

    for (i=0; i<length; i++) {
        i2c_do_write(obj, data[i], 0);
        i2c_wait_send(obj);
    }

    // If not repeated start, send stop.
    if (stop) {
        i2c_stop(obj);
    }

    return length;
}

void i2c_reset(i2c_t *obj) {
    i2c_stop(obj);
}

int i2c_byte_read(i2c_t *obj, int last) {
    return (i2c_do_read(obj, last) & 0xFF);
}

int i2c_byte_write(i2c_t *obj, int data) {
    i2c_do_write(obj, (data & 0xFF), 0);
    i2c_wait_send(obj);

    // TODO: Should return whether write has been acknowledged
    return 1;
}

#endif
