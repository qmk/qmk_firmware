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
#include "fsl_clock_manager.h"
#include "fsl_i2c_hal.h"
#include "fsl_port_hal.h"
#include "fsl_sim_hal.h"
#include "PeripheralPins.h"

void i2c_init(i2c_t *obj, PinName sda, PinName scl) {
    uint32_t i2c_sda = pinmap_peripheral(sda, PinMap_I2C_SDA);
    uint32_t i2c_scl = pinmap_peripheral(scl, PinMap_I2C_SCL);
    obj->instance = pinmap_merge(i2c_sda, i2c_scl);
    MBED_ASSERT((int)obj->instance != NC);

    CLOCK_SYS_EnableI2cClock(obj->instance);
    uint32_t i2c_addrs[] = I2C_BASE_ADDRS;
    I2C_HAL_Init(i2c_addrs[obj->instance]);
    I2C_HAL_Enable(i2c_addrs[obj->instance]);
    I2C_HAL_SetIntCmd(i2c_addrs[obj->instance], true);
    i2c_frequency(obj, 100000);

    pinmap_pinout(sda, PinMap_I2C_SDA);
    pinmap_pinout(scl, PinMap_I2C_SCL);

    uint32_t port_addrs[] = PORT_BASE_ADDRS;
    PORT_HAL_SetOpenDrainCmd(port_addrs[sda >> GPIO_PORT_SHIFT], sda & 0xFF, true);
    PORT_HAL_SetOpenDrainCmd(port_addrs[scl >> GPIO_PORT_SHIFT], scl & 0xFF, true);
}

int i2c_start(i2c_t *obj) {
    uint32_t i2c_addrs[] = I2C_BASE_ADDRS;
    I2C_HAL_SendStart(i2c_addrs[obj->instance]);
    return 0;
}

int i2c_stop(i2c_t *obj) {
    volatile uint32_t n = 0;
    uint32_t i2c_addrs[] = I2C_BASE_ADDRS;
    if (I2C_HAL_IsMaster(i2c_addrs[obj->instance]))
        I2C_HAL_SendStop(i2c_addrs[obj->instance]);
    
    // It seems that there are timing problems
    // when there is no waiting time after a STOP.
    // This wait is also included on the samples
    // code provided with the freedom board
    for (n = 0; n < 200; n++) __NOP();
    return 0;
}

static int timeout_status_poll(i2c_t *obj, i2c_status_flag_t flag) {
    uint32_t i, timeout = 100000;
    uint32_t i2c_addrs[] = I2C_BASE_ADDRS;

    for (i = 0; i < timeout; i++) {
        if (I2C_HAL_GetStatusFlag(i2c_addrs[obj->instance], flag))
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
    uint32_t i2c_addrs[] = I2C_BASE_ADDRS;

    if (timeout_status_poll(obj, kI2CInterruptPending)) {
        return 2;
    }
    I2C_HAL_ClearInt(i2c_addrs[obj->instance]);

    // wait transfer complete
    if (timeout_status_poll(obj, kI2CTransferComplete)) {
        return 2;
    }

    // check if we received the ACK or not
    return I2C_HAL_GetStatusFlag(i2c_addrs[obj->instance], kI2CReceivedNak) ? 1 : 0;
}

// this function waits the end of a rx transfer and return the status of the transaction:
//    0: OK
//    1: failure
static int i2c_wait_end_rx_transfer(i2c_t *obj) {
    // wait for the end of the rx transfer
    if (timeout_status_poll(obj, kI2CInterruptPending)) {
        return 1;
    }
    uint32_t i2c_addrs[] = I2C_BASE_ADDRS;
    I2C_HAL_ClearInt(i2c_addrs[obj->instance]);

    return 0;
}

static int i2c_do_write(i2c_t *obj, int value) {
    uint32_t i2c_addrs[] = I2C_BASE_ADDRS;
    I2C_HAL_WriteByte(i2c_addrs[obj->instance], value);

    // init and wait the end of the transfer
    return i2c_wait_end_tx_transfer(obj);
}

static int i2c_do_read(i2c_t *obj, char * data, int last) {
    uint32_t i2c_addrs[] = I2C_BASE_ADDRS;
    if (last) {
        I2C_HAL_SendNak(i2c_addrs[obj->instance]);
    } else {
        I2C_HAL_SendAck(i2c_addrs[obj->instance]);
    }

    *data = (I2C_HAL_ReadByte(i2c_addrs[obj->instance]) & 0xFF);

    // start rx transfer and wait the end of the transfer
    return i2c_wait_end_rx_transfer(obj);
}

void i2c_frequency(i2c_t *obj, int hz) {
    uint32_t busClock;
    uint32_t i2c_addrs[] = I2C_BASE_ADDRS;
    clock_manager_error_code_t error = CLOCK_SYS_GetFreq(kBusClock, &busClock);
    if (error == kClockManagerSuccess) {
        I2C_HAL_SetBaudRate(i2c_addrs[obj->instance], busClock, hz / 1000, NULL);
    }
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
    uint32_t i2c_addrs[] = I2C_BASE_ADDRS;
    I2C_HAL_SetDirMode(i2c_addrs[obj->instance], kI2CReceive);

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
    data[count-1] = I2C_HAL_ReadByte(i2c_addrs[obj->instance]);

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
    uint32_t i2c_addrs[] = I2C_BASE_ADDRS;
    // set rx mode
    I2C_HAL_SetDirMode(i2c_addrs[obj->instance], kI2CReceive);

    // Setup read
    i2c_do_read(obj, &data, last);

    // set tx mode
    I2C_HAL_SetDirMode(i2c_addrs[obj->instance], kI2CSend);
    return I2C_HAL_ReadByte(i2c_addrs[obj->instance]);
}

int i2c_byte_write(i2c_t *obj, int data) {
    uint32_t i2c_addrs[] = I2C_BASE_ADDRS;
    // set tx mode
    I2C_HAL_SetDirMode(i2c_addrs[obj->instance], kI2CSend);

    return !i2c_do_write(obj, (data & 0xFF));
}


#if DEVICE_I2CSLAVE
void i2c_slave_mode(i2c_t *obj, int enable_slave) {
    uint32_t i2c_addrs[] = I2C_BASE_ADDRS;
    if (enable_slave) {
        // set slave mode
        BW_I2C_C1_MST(i2c_addrs[obj->instance], 0);
        I2C_HAL_SetIntCmd(i2c_addrs[obj->instance], true);
    } else {
        // set master mode
        BW_I2C_C1_MST(i2c_addrs[obj->instance], 1);
    }
}

int i2c_slave_receive(i2c_t *obj) {
    uint32_t i2c_addrs[] = I2C_BASE_ADDRS;
    switch(HW_I2C_S_RD(i2c_addrs[obj->instance])) {
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
    uint8_t *ptr;
    int count;
    uint32_t i2c_addrs[] = I2C_BASE_ADDRS;
    // set rx mode
    I2C_HAL_SetDirMode(i2c_addrs[obj->instance], kI2CSend);

    // first dummy read
    dummy_read = I2C_HAL_ReadByte(i2c_addrs[obj->instance]);
    if (i2c_wait_end_rx_transfer(obj))
        return 0;

    // read address
    dummy_read = I2C_HAL_ReadByte(i2c_addrs[obj->instance]);
    if (i2c_wait_end_rx_transfer(obj))
        return 0;

    // read (length - 1) bytes
    for (count = 0; count < (length - 1); count++) {
        data[count] = I2C_HAL_ReadByte(i2c_addrs[obj->instance]);
        if (i2c_wait_end_rx_transfer(obj))
            return count;
    }

    // read last byte
    ptr = (length == 0) ? &dummy_read : (uint8_t *)&data[count];
    *ptr = I2C_HAL_ReadByte(i2c_addrs[obj->instance]);

    return (length) ? (count + 1) : 0;
}

int i2c_slave_write(i2c_t *obj, const char *data, int length) {
    int i, count = 0;
    uint32_t i2c_addrs[] = I2C_BASE_ADDRS;

    // set tx mode
    I2C_HAL_SetDirMode(i2c_addrs[obj->instance], kI2CSend);

    for (i = 0; i < length; i++) {
        if (i2c_do_write(obj, data[count++]) == 2)
            return i;
    }

    // set rx mode
    I2C_HAL_SetDirMode(i2c_addrs[obj->instance], kI2CReceive);

    // dummy rx transfer needed
    // otherwise the master cannot generate a stop bit
    I2C_HAL_ReadByte(i2c_addrs[obj->instance]);
    if (i2c_wait_end_rx_transfer(obj) == 2)
        return count;

    return count;
}

void i2c_slave_address(i2c_t *obj, int idx, uint32_t address, uint32_t mask) {
    uint32_t i2c_addrs[] = I2C_BASE_ADDRS;
    I2C_HAL_SetUpperAddress7bit(i2c_addrs[obj->instance], address & 0xfe);
}
#endif

#endif
