/* mbed Microcontroller Library
 * Copyright (c) 2006-2015 ARM Limited
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
#include "clk_freqs.h"
#include "PeripheralPins.h"

static const uint16_t ICR[0x40] = {
      20,   22,   24,   26,   28,
      30,   34,   40,   28,   32,
      36,   40,   44,   48,   56,
      68,   48,   56,   64,   72,
      80,   88,  104,  128,   80,
      96,  112,  128,  144,  160,
      192,  240,  160,  192,  224,
      256,  288,  320,  384,  480,
      320,  384,  448,  512,  576,
      640,  768,  960,  640,  768,
      896, 1024, 1152, 1280, 1536,
      1920, 1280, 1536, 1792, 2048,
      2304, 2560, 3072, 3840
};


void i2c_init(i2c_t *obj, PinName sda, PinName scl) {
    // determine the I2C to use
    I2CName i2c_sda = (I2CName)pinmap_peripheral(sda, PinMap_I2C_SDA);
    I2CName i2c_scl = (I2CName)pinmap_peripheral(scl, PinMap_I2C_SCL);
    obj->i2c = (I2C_Type*)pinmap_merge(i2c_sda, i2c_scl);
    MBED_ASSERT((int)obj->i2c != NC);    
    
#if defined(TARGET_K20DX256)
    switch ((int)obj->i2c) {
        case I2C_0: SIM->SCGC4 |= SIM_SCGC4_I2C0_MASK;
        case I2C_1: SIM->SCGC4 |= SIM_SCGC4_I2C1_MASK;               
    }
#else
    SIM->SCGC4 |= SIM_SCGC4_I2C0_MASK;    		
#endif    

    // set default frequency at 100k
    i2c_frequency(obj, 100000);

    // enable I2C interface
    obj->i2c->C1 |= 0x80;

    pinmap_pinout(sda, PinMap_I2C_SDA);
    pinmap_pinout(scl, PinMap_I2C_SCL);
    /* enable open drain for I2C pins, only port b available */
    uint32_t pin_n  = (uint32_t)(sda & 0x7C) >> 2;
    PORTB->PCR[pin_n] |= PORT_PCR_ODE_MASK;
    pin_n  = (uint32_t)(scl & 0x7C) >> 2;
    PORTB->PCR[pin_n] |= PORT_PCR_ODE_MASK;
}

int i2c_start(i2c_t *obj) {
    // if we are in the middle of a transaction
    // activate the repeat_start flag
    if (obj->i2c->S & I2C_S_BUSY_MASK) {
        obj->i2c->C1 |= 0x04;
    } else {
        obj->i2c->C1 |= I2C_C1_MST_MASK;
        obj->i2c->C1 |= I2C_C1_TX_MASK;
    }
    return 0;
}

int i2c_stop(i2c_t *obj) {
    volatile uint32_t n = 0;
    obj->i2c->C1 &= ~I2C_C1_MST_MASK;
    obj->i2c->C1 &= ~I2C_C1_TX_MASK;

    // It seems that there are timing problems
    // when there is no waiting time after a STOP.
    // This wait is also included on the samples
    // code provided with the freedom board
    for (n = 0; n < 100; n++)
        __NOP();
    return 0;
}

static int timeout_status_poll(i2c_t *obj, uint32_t mask) {
    uint32_t i, timeout = 100000;

    for (i = 0; i < timeout; i++) {
        if (obj->i2c->S & mask)
            return 0;
    }

    return 1;
}

// this function waits the end of a tx transfer and return the status of the transaction:
//    0: OK ack received
//    1: OK ack not received
//    2: failure
static int i2c_wait_end_tx_transfer(i2c_t *obj) {

    // wait for the interrupt flag
    if (timeout_status_poll(obj, I2C_S_IICIF_MASK)) {
        return 2;
    }

    obj->i2c->S |= I2C_S_IICIF_MASK;

    // wait transfer complete
    if (timeout_status_poll(obj, I2C_S_TCF_MASK)) {
        return 2;
    }

    // check if we received the ACK or not
    return obj->i2c->S & I2C_S_RXAK_MASK ? 1 : 0;
}

// this function waits the end of a rx transfer and return the status of the transaction:
//    0: OK
//    1: failure
static int i2c_wait_end_rx_transfer(i2c_t *obj) {
    // wait for the end of the rx transfer
    if (timeout_status_poll(obj, I2C_S_IICIF_MASK)) {
        return 1;
    }

    obj->i2c->S |= I2C_S_IICIF_MASK;

    return 0;
}

static void i2c_send_nack(i2c_t *obj) {
    obj->i2c->C1 |= I2C_C1_TXAK_MASK; // NACK
}

static void i2c_send_ack(i2c_t *obj) {
    obj->i2c->C1 &= ~I2C_C1_TXAK_MASK; // ACK
}

static int i2c_do_write(i2c_t *obj, int value) {
    // write the data
    obj->i2c->D = value;

    // init and wait the end of the transfer
    return i2c_wait_end_tx_transfer(obj);
}

static int i2c_do_read(i2c_t *obj, char * data, int last) {
    if (last) {
        i2c_send_nack(obj);
    } else {
        i2c_send_ack(obj);
    }

    *data = (obj->i2c->D & 0xFF);

    // start rx transfer and wait the end of the transfer
    return i2c_wait_end_rx_transfer(obj);
}

void i2c_frequency(i2c_t *obj, int hz) {
    uint8_t icr = 0;
    uint8_t mult = 0;
    uint32_t error = 0;
    uint32_t p_error = 0xffffffff;
    uint32_t ref = 0;
    uint8_t i, j;
    // bus clk
    uint32_t PCLK = bus_frequency();
    uint32_t pulse = PCLK / (hz * 2);

    // we look for the values that minimize the error

    // test all the MULT values
    for (i = 1; i < 5; i*=2) {
        for (j = 0; j < 0x40; j++) {
            ref = PCLK / (i*ICR[j]);
            if (ref > (uint32_t)hz)
                continue;
            error = hz - ref;
            if (error < p_error) {
                icr = j;
                mult = i/2;
                p_error = error;
            }
        }
    }
    pulse = icr | (mult << 6);

    // I2C Rate
    obj->i2c->F = pulse;
}

int i2c_read(i2c_t *obj, int address, char *data, int length, int stop) {
    int count;
    char dummy_read, *ptr;

    if (i2c_start(obj)) {
        i2c_stop(obj);
        return I2C_ERROR_BUS_BUSY;
    }

    if (i2c_do_write(obj, (address | 0x01))) {
        i2c_stop(obj);
        return I2C_ERROR_NO_SLAVE;
    }

    // set rx mode
    obj->i2c->C1 &= ~I2C_C1_TX_MASK;

    // Read in bytes
    for (count = 0; count < (length); count++) {
        ptr = (count == 0) ? &dummy_read : &data[count - 1];
        uint8_t stop_ = (count == (length - 1)) ? 1 : 0;
        if (i2c_do_read(obj, ptr, stop_)) {
            i2c_stop(obj);
            return count;
        }
    }

    // If not repeated start, send stop.
    if (stop)
        i2c_stop(obj);

    // last read
    data[count-1] = obj->i2c->D;

    return length;
}
int i2c_write(i2c_t *obj, int address, const char *data, int length, int stop) {
    int i;

    if (i2c_start(obj)) {
        i2c_stop(obj);
        return I2C_ERROR_BUS_BUSY;
    }

    if (i2c_do_write(obj, (address & 0xFE))) {
        i2c_stop(obj);
        return I2C_ERROR_NO_SLAVE;
    }

    for (i = 0; i < length; i++) {
        if(i2c_do_write(obj, data[i])) {
            i2c_stop(obj);
            return i;
        }
    }

    if (stop)
        i2c_stop(obj);

    return length;
}

void i2c_reset(i2c_t *obj) {
    i2c_stop(obj);
}

int i2c_byte_read(i2c_t *obj, int last) {
    char data;
    
    // set rx mode
    obj->i2c->C1 &= ~I2C_C1_TX_MASK;
    
    // Setup read
    i2c_do_read(obj, &data, last);

    // set tx mode
    obj->i2c->C1 |= I2C_C1_TX_MASK;
    return obj->i2c->D;
}

int i2c_byte_write(i2c_t *obj, int data) {
    // set tx mode
    obj->i2c->C1 |= I2C_C1_TX_MASK;

    return !i2c_do_write(obj, (data & 0xFF));
}


#if DEVICE_I2CSLAVE
void i2c_slave_mode(i2c_t *obj, int enable_slave) {
    if (enable_slave) {
        // set slave mode
        obj->i2c->C1 &= ~I2C_C1_MST_MASK;
        obj->i2c->C1 |= I2C_C1_IICIE_MASK;
    } else {
        // set master mode
        obj->i2c->C1 |= I2C_C1_MST_MASK;
    }
}

int i2c_slave_receive(i2c_t *obj) {
    switch(obj->i2c->S) {
        // read addressed
        case 0xE6:
            return 1;
        // write addressed
        case 0xE2:
            return 3;
        default:
            return 0;
    }
}

int i2c_slave_read(i2c_t *obj, char *data, int length) {
    uint8_t dummy_read;
    uint8_t * ptr;
    int count;

    // set rx mode
    obj->i2c->C1 &= ~I2C_C1_TX_MASK;

    // first dummy read
    dummy_read = obj->i2c->D;
    if (i2c_wait_end_rx_transfer(obj))
        return 0;

    // read address
    dummy_read = obj->i2c->D;
    if (i2c_wait_end_rx_transfer(obj))
        return 0;

    // read (length - 1) bytes
    for (count = 0; count < (length - 1); count++) {
        data[count] = obj->i2c->D;
        if (i2c_wait_end_rx_transfer(obj))
            return count;
    }

    // read last byte
    ptr = (length == 0) ? &dummy_read : (uint8_t *)&data[count];
    *ptr = obj->i2c->D;

    return (length) ? (count + 1) : 0;
}

int i2c_slave_write(i2c_t *obj, const char *data, int length) {
    int i, count = 0;

    // set tx mode
    obj->i2c->C1 |= I2C_C1_TX_MASK;

    for (i = 0; i < length; i++) {
        if (i2c_do_write(obj, data[count++]) == 2)
            return i;
    }

    // set rx mode
    obj->i2c->C1 &= ~I2C_C1_TX_MASK;

    // dummy rx transfer needed
    // otherwise the master cannot generate a stop bit
    obj->i2c->D;
    if (i2c_wait_end_rx_transfer(obj) == 2)
        return count;

    return count;
}

void i2c_slave_address(i2c_t *obj, int idx, uint32_t address, uint32_t mask) {
    obj->i2c->A1 = address & 0xfe;
}
#endif
