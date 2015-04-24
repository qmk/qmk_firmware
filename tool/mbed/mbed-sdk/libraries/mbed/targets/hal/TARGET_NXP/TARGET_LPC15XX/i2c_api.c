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
#include "cmsis.h"
#include "pinmap.h"

static uint8_t repeated_start = 0;

#define I2C_STAT(x)         ((LPC_I2C0->STAT >> 1) & (0x07))

static inline int i2c_status(i2c_t *obj) {
    return I2C_STAT(obj);
}

// Wait until the Serial Interrupt (SI) is set
static int i2c_wait_SI(i2c_t *obj) {
    volatile int timeout = 0;
    while (!(LPC_I2C0->STAT & (1 << 0))) {
        timeout++;
        if (timeout > 100000) return -1;
    }
    return 0;
}

static inline void i2c_interface_enable(i2c_t *obj) {
    LPC_I2C0->CFG |= (1 << 0);
}

void i2c_init(i2c_t *obj, PinName sda, PinName scl) {
    MBED_ASSERT((sda == P0_23) && (scl == P0_22));
    
    // Enables clock for I2C0
    LPC_SYSCON->SYSAHBCLKCTRL1 |= (1 << 13);

    LPC_SYSCON->PRESETCTRL1 |=  (1 << 13);
    LPC_SYSCON->PRESETCTRL1 &= ~(1 << 13);

    // pin enable
    LPC_SWM->PINENABLE1 &= ~(0x3 << 3);

    // set default frequency at 100kHz
    i2c_frequency(obj, 100000);
    i2c_interface_enable(obj);
}

inline int i2c_start(i2c_t *obj) {
    int status = 0;
    if (repeated_start) {
        LPC_I2C0->MSTCTL = (1 << 1) | (1 << 0);
        repeated_start = 0;
    } else {
        LPC_I2C0->MSTCTL = (1 << 1);
    }
    return status;
}

inline int i2c_stop(i2c_t *obj) {
    volatile int timeout = 0;

    LPC_I2C0->MSTCTL = (1 << 2) | (1 << 0);
    while ((LPC_I2C0->STAT & ((1 << 0) | (7 << 1))) != ((1 << 0) | (0 << 1))) {
        timeout ++;
        if (timeout > 100000) return 1;
    }

    return 0;
}


static inline int i2c_do_write(i2c_t *obj, int value, uint8_t addr) {
    // write the data
    LPC_I2C0->MSTDAT = value;
    
    if (!addr)
        LPC_I2C0->MSTCTL = (1 << 0);
    
    // wait and return status
    i2c_wait_SI(obj);
    return i2c_status(obj);
}

static inline int i2c_do_read(i2c_t *obj, int last) {
    // wait for it to arrive
    i2c_wait_SI(obj);
    if (!last)
        LPC_I2C0->MSTCTL = (1 << 0);
    
    // return the data
    return (LPC_I2C0->MSTDAT & 0xFF);
}

void i2c_frequency(i2c_t *obj, int hz) {
    // No peripheral clock divider on the M0
    uint32_t PCLK = SystemCoreClock;
    uint32_t clkdiv = PCLK / (hz * 4) - 1;
    
    LPC_I2C0->DIV = clkdiv;
    LPC_I2C0->MSTTIME = 0;
}

int i2c_read(i2c_t *obj, int address, char *data, int length, int stop) {
    int count, status;
    
    i2c_start(obj);
    
    LPC_I2C0->MSTDAT = (address | 0x01);
    LPC_I2C0->MSTCTL |= 0x20;
    if (i2c_wait_SI(obj) == -1)
        return -1;

    status = ((LPC_I2C0->STAT >> 1) & (0x07));
    if (status != 0x01) {
        i2c_stop(obj);
        return I2C_ERROR_NO_SLAVE;
    }
    
    // Read in all except last byte
    for (count = 0; count < (length - 1); count++) {
        if (i2c_wait_SI(obj) == -1)
            return -1;
        LPC_I2C0->MSTCTL = (1 << 0);
        data[count] = (LPC_I2C0->MSTDAT & 0xFF);
        status = ((LPC_I2C0->STAT >> 1) & (0x07));
        if (status != 0x01) {
            i2c_stop(obj);
            return count;
        }
    }
    
    // read in last byte
    if (i2c_wait_SI(obj) == -1)
        return -1;

    data[count] = (LPC_I2C0->MSTDAT & 0xFF);
    status = i2c_status(obj);
    if (status != 0x01) {
        i2c_stop(obj);
        return length - 1;
    }
    // If not repeated start, send stop.
    if (stop) {
        i2c_stop(obj);
    } else {
        repeated_start = 1;
    }
    
    return length;
}

int i2c_write(i2c_t *obj, int address, const char *data, int length, int stop) {
    int i, status;
    
    i2c_start(obj);
    
    LPC_I2C0->MSTDAT = (address & 0xFE);
    LPC_I2C0->MSTCTL |= 0x20;
    if (i2c_wait_SI(obj) == -1)
        return -1;

    status = ((LPC_I2C0->STAT >> 1) & (0x07));
    if (status != 0x02) {
        i2c_stop(obj);
        return I2C_ERROR_NO_SLAVE;
    }
    
    for (i=0; i<length; i++) {
        LPC_I2C0->MSTDAT = data[i];
        LPC_I2C0->MSTCTL = (1 << 0);
        if (i2c_wait_SI(obj) == -1)
            return -1;

        status = ((LPC_I2C0->STAT >> 1) & (0x07));
        if (status != 0x02) {
            i2c_stop(obj);
            return i;
        }
    }
    
    // If not repeated start, send stop.
    if (stop) {
        i2c_stop(obj);
    } else {
        repeated_start = 1;
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
    if (i2c_do_write(obj, (data & 0xFF), 0) == 2) {
        return 1;
    } else {
        return 0;
    }
}
