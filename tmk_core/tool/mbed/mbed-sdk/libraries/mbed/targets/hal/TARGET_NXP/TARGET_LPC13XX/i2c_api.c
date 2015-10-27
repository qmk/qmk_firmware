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
#include "mbed_error.h"

static const PinMap PinMap_I2C_SDA[] = {
    {P0_5, I2C_0, 1},
    {NC  , NC   , 0}
};

static const PinMap PinMap_I2C_SCL[] = {
    {P0_4, I2C_0, 1},
    {NC  , NC,    0}
};

#define I2C_CONSET(x)       (x->i2c->CONSET)
#define I2C_CONCLR(x)       (x->i2c->CONCLR)
#define I2C_STAT(x)         (x->i2c->STAT)
#define I2C_DAT(x)          (x->i2c->DAT)
#define I2C_SCLL(x, val)    (x->i2c->SCLL = val)
#define I2C_SCLH(x, val)    (x->i2c->SCLH = val)

static const uint32_t I2C_addr_offset[2][4] = {
    {0x0C, 0x20, 0x24, 0x28},
    {0x30, 0x34, 0x38, 0x3C}
};

static inline void i2c_conclr(i2c_t *obj, int start, int stop, int interrupt, int acknowledge) {
    I2C_CONCLR(obj) = (start << 5)
                    | (stop << 4)
                    | (interrupt << 3)
                    | (acknowledge << 2);
}

static inline void i2c_conset(i2c_t *obj, int start, int stop, int interrupt, int acknowledge) {
    I2C_CONSET(obj) = (start << 5)
                    | (stop << 4)
                    | (interrupt << 3)
                    | (acknowledge << 2);
}

// Clear the Serial Interrupt (SI)
static inline void i2c_clear_SI(i2c_t *obj) {
    i2c_conclr(obj, 0, 0, 1, 0);
}

static inline int i2c_status(i2c_t *obj) {
    return I2C_STAT(obj);
}

// Wait until the Serial Interrupt (SI) is set
static int i2c_wait_SI(i2c_t *obj) {
    int timeout = 0;
    while (!(I2C_CONSET(obj) & (1 << 3))) {
        timeout++;
        if (timeout > 100000) return -1;
    }
    return 0;
}

static inline void i2c_interface_enable(i2c_t *obj) {
    I2C_CONSET(obj) = 0x40;
}

static inline void i2c_power_enable(i2c_t *obj) {
    LPC_SYSCON->SYSAHBCLKCTRL |= (1 << 5);
    LPC_SYSCON->PRESETCTRL |= 1 << 1;
}

void i2c_init(i2c_t *obj, PinName sda, PinName scl) {
    // determine the SPI to use
    I2CName i2c_sda = (I2CName)pinmap_peripheral(sda, PinMap_I2C_SDA);
    I2CName i2c_scl = (I2CName)pinmap_peripheral(scl, PinMap_I2C_SCL);
    obj->i2c = (LPC_I2C_Type *)pinmap_merge(i2c_sda, i2c_scl);
    MBED_ASSERT((int)obj->i2c != NC);
    
    // enable power
    i2c_power_enable(obj);
    
    // set default frequency at 100k
    i2c_frequency(obj, 100000);
    i2c_conclr(obj, 1, 1, 1, 1);
    i2c_interface_enable(obj);
    
    pinmap_pinout(sda, PinMap_I2C_SDA);
    pinmap_pinout(scl, PinMap_I2C_SCL);
}

inline int i2c_start(i2c_t *obj) {
    int status = 0;
    // 8.1 Before master mode can be entered, I2CON must be initialised to:
    //  - I2EN STA STO SI AA - -
    //  -  1    0   0   0  x - -
    // if AA = 0, it can't enter slave mode
    i2c_conclr(obj, 1, 1, 1, 1);
    
    // The master mode may now be entered by setting the STA bit
    // this will generate a start condition when the bus becomes free
    i2c_conset(obj, 1, 0, 0, 1);
    
    i2c_wait_SI(obj);
    status = i2c_status(obj);
    
    // Clear start bit now transmitted, and interrupt bit
    i2c_conclr(obj, 1, 0, 0, 0);
    return status;
}

inline int i2c_stop(i2c_t *obj) {
    int timeout = 0;

    // write the stop bit
    i2c_conset(obj, 0, 1, 0, 0);
    i2c_clear_SI(obj);
    
    // wait for STO bit to reset
    while(I2C_CONSET(obj) & (1 << 4)) {
        timeout ++;
        if (timeout > 100000) return 1;
    }

    return 0;
}


static inline int i2c_do_write(i2c_t *obj, int value, uint8_t addr) {
    // write the data
    I2C_DAT(obj) = value;
    
    // clear SI to init a send
    i2c_clear_SI(obj);
    
    // wait and return status
    i2c_wait_SI(obj);
    return i2c_status(obj);
}

static inline int i2c_do_read(i2c_t *obj, int last) {
    // we are in state 0x40 (SLA+R tx'd) or 0x50 (data rx'd and ack)
    if (last) {
        i2c_conclr(obj, 0, 0, 0, 1); // send a NOT ACK
    } else {
        i2c_conset(obj, 0, 0, 0, 1); // send a ACK
    }
    
    // accept byte
    i2c_clear_SI(obj);
    
    // wait for it to arrive
    i2c_wait_SI(obj);
    
    // return the data
    return (I2C_DAT(obj) & 0xFF);
}

void i2c_frequency(i2c_t *obj, int hz) {
    // No peripheral clock divider on the M0
    uint32_t PCLK = SystemCoreClock;
    
    uint32_t pulse = PCLK / (hz * 2);
    
    // I2C Rate
    I2C_SCLL(obj, pulse);
    I2C_SCLH(obj, pulse);
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
    int count, status;
    
    status = i2c_start(obj);
    
    if ((status != 0x10) && (status != 0x08)) {
        i2c_stop(obj);
        return I2C_ERROR_BUS_BUSY;
    }
    
    status = i2c_do_write(obj, (address | 0x01), 1);
    if (status != 0x40) {
        i2c_stop(obj);
        return I2C_ERROR_NO_SLAVE;
    }

    // Read in all except last byte
    for (count = 0; count < (length - 1); count++) {
        int value = i2c_do_read(obj, 0);
        status = i2c_status(obj);
        if (status != 0x50) {
            i2c_stop(obj);
            return count;
        }
        data[count] = (char) value;
    }

    // read in last byte
    int value = i2c_do_read(obj, 1);
    status = i2c_status(obj);
    if (status != 0x58) {
        i2c_stop(obj);
        return length - 1;
    }
    
    data[count] = (char) value;
    
    // If not repeated start, send stop.
    if (stop) {
        i2c_stop(obj);
    }
    
    return length;
}

int i2c_write(i2c_t *obj, int address, const char *data, int length, int stop) {
    int i, status;
    
    status = i2c_start(obj);
    
    if ((status != 0x10) && (status != 0x08)) {
        i2c_stop(obj);
        return I2C_ERROR_BUS_BUSY;
    }
    
    status = i2c_do_write(obj, (address & 0xFE), 1);
    if (status != 0x18) {
        i2c_stop(obj);
        return I2C_ERROR_NO_SLAVE;
    }
    
    for (i=0; i<length; i++) {
        status = i2c_do_write(obj, data[i], 0);
        if(status != 0x28) {
            i2c_stop(obj);
            return i;
        }
    }
    
    // clearing the serial interrupt here might cause an unintended rewrite of the last byte
    // see also issue report https://mbed.org/users/mbed_official/code/mbed/issues/1
    // i2c_clear_SI(obj);
    
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
    int ack;
    int status = i2c_do_write(obj, (data & 0xFF), 0);
    
    switch(status) {
        case 0x18: case 0x28:       // Master transmit ACKs
            ack = 1;
            break;
        case 0x40:                  // Master receive address transmitted ACK
            ack = 1;
            break;
        case 0xB8:                  // Slave transmit ACK
            ack = 1;
            break;
        default:
            ack = 0;
            break;
    }

    return ack;
}

void i2c_slave_mode(i2c_t *obj, int enable_slave) {
    if (enable_slave != 0) {
        i2c_conclr(obj, 1, 1, 1, 0);
        i2c_conset(obj, 0, 0, 0, 1);
    } else {
        i2c_conclr(obj, 1, 1, 1, 1);
    }
}

int i2c_slave_receive(i2c_t *obj) {
    int status;
    int retval;
    
    status = i2c_status(obj);
    switch(status) {
        case 0x60: retval = 3; break;
        case 0x70: retval = 2; break;
        case 0xA8: retval = 1; break;
        default  : retval = 0; break;
    }
    
    return(retval);
}

int i2c_slave_read(i2c_t *obj, char *data, int length) {
    int count = 0;
    int status;
    
    do {
        i2c_clear_SI(obj);
        i2c_wait_SI(obj);
        status = i2c_status(obj);
        if((status == 0x80) || (status == 0x90)) {
            data[count] = I2C_DAT(obj) & 0xFF;
        }
        count++;
    } while (((status == 0x80) || (status == 0x90) ||
            (status == 0x060) || (status == 0x70)) && (count < length));
    
    if(status != 0xA0) {
        i2c_stop(obj);
    }
    
    i2c_clear_SI(obj);
    
    return count;
}

int i2c_slave_write(i2c_t *obj, const char *data, int length) {
    int count = 0;
    int status;
    
    if(length <= 0) {
        return(0);
    }
    
    do {
        status = i2c_do_write(obj, data[count], 0);
        count++;
    } while ((count < length) && (status == 0xB8));
    
    if((status != 0xC0) && (status != 0xC8)) {
        i2c_stop(obj);
    }
    
    i2c_clear_SI(obj);
    
    return(count);
}

void i2c_slave_address(i2c_t *obj, int idx, uint32_t address, uint32_t mask) {
    uint32_t addr;
    
    if ((idx >= 0) && (idx <= 3)) {
        addr = ((uint32_t)obj->i2c) + I2C_addr_offset[0][idx];
        *((uint32_t *) addr) = address & 0xFF;
    }
}
