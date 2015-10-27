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
 
#include "mbed_assert.h"
#include "i2c_api.h"
#include "cmsis.h"
#include "i2cm_regs.h"
#include "clkman_regs.h"
#include "ioman_regs.h"
#include "PeripheralPins.h"

#define I2C_SLAVE_ADDR_READ_BIT     0x0001

#ifndef MXC_I2CM_TX_TIMEOUT
#define MXC_I2CM_TX_TIMEOUT         0x5000
#endif

#ifndef MXC_I2CM_RX_TIMEOUT
#define MXC_I2CM_RX_TIMEOUT         0x5000
#endif

typedef enum {
    /** 100KHz */
    MXC_E_I2CM_SPEED_100KHZ = 0,
    /** 400KHz */
    MXC_E_I2CM_SPEED_400KHZ,
    /** 1MHz */
    MXC_E_I2CM_SPEED_1MHZ
} i2cm_speed_t;

/* Clock divider lookup table */
static const uint32_t clk_div_table[3][8] = {
    /* MXC_E_I2CM_SPEED_100KHZ */
    {
        /* 0:       */ 0, /* not supported */
        /* 1: 6MHz  */ (( 3 << MXC_F_I2CM_CLK_DIV_FILTER_CLK_DIV_POS) | ( 7 << MXC_F_I2CM_CLK_DIV_SCL_HI_CNT_POS) | ( 36 << MXC_F_I2CM_CLK_DIV_SCL_LO_CNT_POS)),
        /* 2: 8MHz  */ (( 4 << MXC_F_I2CM_CLK_DIV_FILTER_CLK_DIV_POS) | (10 << MXC_F_I2CM_CLK_DIV_SCL_HI_CNT_POS) | ( 48 << MXC_F_I2CM_CLK_DIV_SCL_LO_CNT_POS)),
        /* 3: 12MHz */ (( 6 << MXC_F_I2CM_CLK_DIV_FILTER_CLK_DIV_POS) | (17 << MXC_F_I2CM_CLK_DIV_SCL_HI_CNT_POS) | ( 72 << MXC_F_I2CM_CLK_DIV_SCL_LO_CNT_POS)),
        /* 4: 16MHz */ (( 8 << MXC_F_I2CM_CLK_DIV_FILTER_CLK_DIV_POS) | (24 << MXC_F_I2CM_CLK_DIV_SCL_HI_CNT_POS) | ( 96 << MXC_F_I2CM_CLK_DIV_SCL_LO_CNT_POS)),
        /* 5:       */ 0, /* not supported */
        /* 6:       */ 0, /* not supported */
        /* 7: 24MHz */ ((12 << MXC_F_I2CM_CLK_DIV_FILTER_CLK_DIV_POS) | (38 << MXC_F_I2CM_CLK_DIV_SCL_HI_CNT_POS) | (144 << MXC_F_I2CM_CLK_DIV_SCL_LO_CNT_POS)),
    },
    /* MXC_E_I2CM_SPEED_400KHZ */
    {
        /* 0:       */ 0, /* not supported */
        /* 1:       */ 0, /* not supported */
        /* 2:       */ 0, /* not supported */
        /* 3: 12MHz */ ((2 << MXC_F_I2CM_CLK_DIV_FILTER_CLK_DIV_POS) | (1 << MXC_F_I2CM_CLK_DIV_SCL_HI_CNT_POS) | (18 << MXC_F_I2CM_CLK_DIV_SCL_LO_CNT_POS)),
        /* 4: 16MHz */ ((2 << MXC_F_I2CM_CLK_DIV_FILTER_CLK_DIV_POS) | (2 << MXC_F_I2CM_CLK_DIV_SCL_HI_CNT_POS) | (24 << MXC_F_I2CM_CLK_DIV_SCL_LO_CNT_POS)),
        /* 5:       */ 0, /* not supported */
        /* 6:       */ 0, /* not supported */
        /* 7: 24MHz */ ((3 << MXC_F_I2CM_CLK_DIV_FILTER_CLK_DIV_POS) | (5 << MXC_F_I2CM_CLK_DIV_SCL_HI_CNT_POS) | (36 << MXC_F_I2CM_CLK_DIV_SCL_LO_CNT_POS)),
    },
    /* MXC_E_I2CM_SPEED_1MHZ */
    {
        /* 0:       */ 0, /* not supported */
        /* 1:       */ 0, /* not supported */
        /* 2:       */ 0, /* not supported */
        /* 3:       */ 0, /* not supported */
        /* 4:       */ 0, /* not supported */
        /* 5:       */ 0, /* not supported */
        /* 6:       */ 0, /* not supported */
        /* 7: 24MHz */ ((1 << MXC_F_I2CM_CLK_DIV_FILTER_CLK_DIV_POS) | (0 << MXC_F_I2CM_CLK_DIV_SCL_HI_CNT_POS) | (14 << MXC_F_I2CM_CLK_DIV_SCL_LO_CNT_POS)),
    },
};

void i2c_init(i2c_t *obj, PinName sda, PinName scl)
{
    // determine the I2C to use
    I2CName i2c_sda = (I2CName)pinmap_peripheral(sda, PinMap_I2C_SDA);
    I2CName i2c_scl = (I2CName)pinmap_peripheral(scl, PinMap_I2C_SCL);
    mxc_i2cm_regs_t *i2c = (mxc_i2cm_regs_t*)pinmap_merge(i2c_sda, i2c_scl);
    MBED_ASSERT((int)i2c != NC);

    obj->i2c = i2c;
    obj->txfifo = (uint16_t*)MXC_I2CM_GET_BASE_TX_FIFO(MXC_I2CM_BASE_TO_INSTANCE(i2c));
    obj->rxfifo = (uint16_t*)MXC_I2CM_GET_BASE_RX_FIFO(MXC_I2CM_BASE_TO_INSTANCE(i2c));
    obj->start_pending = 0;
	obj->stop_pending = 0;

    // configure the pins
    pinmap_pinout(sda, PinMap_I2C_SDA);
    pinmap_pinout(scl, PinMap_I2C_SCL);

    // enable the clock
    MXC_CLKMAN->clk_ctrl_6_i2cm = MXC_E_CLKMAN_CLK_SCALE_ENABLED;

    // reset module
    i2c->ctrl = MXC_F_I2CM_CTRL_MSTR_RESET_EN;
    i2c->ctrl = 0;

    // set default frequency at 100k
    i2c_frequency(obj, 100000);

    // set timeout to 255 ms and turn on the auto-stop option
    i2c->timeout = (0xFF << MXC_F_I2CM_TIMEOUT_TX_TIMEOUT_POS) | MXC_F_I2CM_TIMEOUT_AUTO_STOP_EN;

    // enable tx_fifo and rx_fifo
    i2c->ctrl |= (MXC_F_I2CM_CTRL_TX_FIFO_EN | MXC_F_I2CM_CTRL_RX_FIFO_EN);
}

void i2c_frequency(i2c_t *obj, int hz)
{
    // compute clock array index
    int clki = ((SystemCoreClock + 1500000) / 3000000) - 1;

    // get clock divider settings from lookup table
    if ((hz < 400000) && (clk_div_table[MXC_E_I2CM_SPEED_100KHZ][clki] > 0)) {
        obj->i2c->fs_clk_div = clk_div_table[MXC_E_I2CM_SPEED_100KHZ][clki];
    } else if ((hz < 1000000) && (clk_div_table[MXC_E_I2CM_SPEED_400KHZ][clki] > 0)) {
        obj->i2c->fs_clk_div = clk_div_table[MXC_E_I2CM_SPEED_400KHZ][clki];
    } else if ((hz >= 1000000) && (clk_div_table[MXC_E_I2CM_SPEED_1MHZ][clki] > 0)) {
        obj->i2c->hs_clk_div = clk_div_table[MXC_E_I2CM_SPEED_1MHZ][clki];
    }
}

static int write_tx_fifo(i2c_t *obj, const uint16_t data)
{
    int timeout = MXC_I2CM_TX_TIMEOUT;

    while (*obj->txfifo) {
        uint32_t intfl = obj->i2c->intfl;
        if (intfl & MXC_F_I2CM_INTFL_TX_NACKED) {
            return I2C_ERROR_NO_SLAVE;
        }
        if (!timeout || (intfl & (MXC_F_I2CM_INTFL_TX_TIMEOUT | MXC_F_I2CM_INTFL_TX_LOST_ARBITR))) {
            return I2C_ERROR_BUS_BUSY;
        }
        timeout--;
    }
    *obj->txfifo = data;

    return 0;
}

static int wait_tx_in_progress(i2c_t *obj)
{
    int timeout = MXC_I2CM_TX_TIMEOUT;

    while ((obj->i2c->trans & MXC_F_I2CM_TRANS_TX_IN_PROGRESS) && --timeout);

    uint32_t intfl = obj->i2c->intfl;

    if (intfl & MXC_F_I2CM_INTFL_TX_NACKED) {
        i2c_reset(obj);
        return I2C_ERROR_NO_SLAVE;
    }

    if (!timeout || (intfl & (MXC_F_I2CM_INTFL_TX_TIMEOUT | MXC_F_I2CM_INTFL_TX_LOST_ARBITR))) {
        i2c_reset(obj);
        return I2C_ERROR_BUS_BUSY;
    }

    return 0;
}

int i2c_start(i2c_t *obj)
{
    obj->start_pending = 1;
    return 0;
}

int i2c_stop(i2c_t *obj)
{
    obj->start_pending = 0;
    write_tx_fifo(obj, MXC_S_I2CM_TRANS_TAG_STOP);

    return wait_tx_in_progress(obj);
}

void i2c_reset(i2c_t *obj)
{
    obj->i2c->ctrl = MXC_F_I2CM_CTRL_MSTR_RESET_EN;
    obj->i2c->intfl = 0x3FF; // clear all interrupts
    obj->i2c->ctrl = MXC_F_I2CM_CTRL_TX_FIFO_EN | MXC_F_I2CM_CTRL_RX_FIFO_EN;
    obj->start_pending = 0;
}

int i2c_byte_write(i2c_t *obj, int data)
{
    int err;

    // clear all interrupts
    obj->i2c->intfl = 0x3FF;

    if (obj->start_pending) {
        obj->start_pending = 0;
        data = (data & 0xFF) | MXC_S_I2CM_TRANS_TAG_START;
    } else {
        data = (data & 0xFF) | MXC_S_I2CM_TRANS_TAG_TXDATA_ACK;
    }

    if ((err = write_tx_fifo(obj, data)) != 0) {
        return err;
    }

    obj->i2c->trans |= MXC_F_I2CM_TRANS_TX_START;

    return 0;
}

int i2c_byte_read(i2c_t *obj, int last)
{
    uint16_t fifo_value;
    int err;

    // clear all interrupts
    obj->i2c->intfl = 0x3FF;

    if (last) {
        fifo_value = MXC_S_I2CM_TRANS_TAG_RXDATA_NACK;
    } else {
        fifo_value = MXC_S_I2CM_TRANS_TAG_RXDATA_COUNT;
    }

    if ((err = write_tx_fifo(obj, fifo_value)) != 0) {
        return err;
    }

    obj->i2c->trans |= MXC_F_I2CM_TRANS_TX_START;

    int timeout = MXC_I2CM_RX_TIMEOUT;
    while (!(obj->i2c->intfl & MXC_F_I2CM_INTFL_RX_FIFO_NOT_EMPTY) &&
            (!(obj->i2c->bb & MXC_F_I2CM_BB_RX_FIFO_CNT))) {
        if ((--timeout < 0) || !(obj->i2c->trans & MXC_F_I2CM_TRANS_TX_IN_PROGRESS)) {
            break;
        }
    }

    if (obj->i2c->intfl & MXC_F_I2CM_INTFL_RX_FIFO_NOT_EMPTY) {
        obj->i2c->intfl = MXC_F_I2CM_INTFL_RX_FIFO_NOT_EMPTY;
        return *obj->rxfifo;
    }

    return -1;
}

int i2c_write(i2c_t *obj, int address, const char *data, int length, int stop)
{
    int err, retval = 0;
    int i;

    if (!(obj->stop_pending) && (obj->i2c->trans & MXC_F_I2CM_TRANS_TX_IN_PROGRESS)) {
        return 0;
    }

    // clear all interrupts
    obj->i2c->intfl = 0x3FF;

    // write the address to the fifo
    if ((err = write_tx_fifo(obj, (MXC_S_I2CM_TRANS_TAG_START | address))) != 0) { // start + addr (write)
        return err;
    }
    obj->start_pending = 0;

    // start the transaction
    obj->i2c->trans |= MXC_F_I2CM_TRANS_TX_START;

    // load as much of the cmd into the FIFO as possible
    for (i = 0; i < length; i++) {
        if ((err = write_tx_fifo(obj, (MXC_S_I2CM_TRANS_TAG_TXDATA_ACK | data[i]))) != 0) { // cmd (expect ACK)
            retval = (retval ? retval : err);
            break;
        }
    }

    if (stop) {
		obj->stop_pending = 0;
        if ((err = write_tx_fifo(obj, MXC_S_I2CM_TRANS_TAG_STOP)) != 0) { // stop condition
            retval = (retval ? retval : err);
        }

        if ((err = wait_tx_in_progress(obj)) != 0) {
            retval = (retval ? retval : err);
        }
    } else {
        obj->stop_pending = 1;
        int timeout = MXC_I2CM_TX_TIMEOUT;
        // Wait for TX fifo to be empty
        while(!(obj->i2c->intfl & MXC_F_I2CM_INTFL_TX_FIFO_EMPTY) && timeout--) {}
    }

    if (retval == 0) {
        return length;
    }

    return retval;
}

int i2c_read(i2c_t *obj, int address, char *data, int length, int stop)
{
    int err, retval = 0;
    int i = length;
    int timeout;

    if (!(obj->stop_pending) && (obj->i2c->trans & MXC_F_I2CM_TRANS_TX_IN_PROGRESS)) {
        return 0;
    }

    // clear all interrupts
    obj->i2c->intfl = 0x3FF;

    // start + addr (read)
    if ((retval = write_tx_fifo(obj, (MXC_S_I2CM_TRANS_TAG_START | address | I2C_SLAVE_ADDR_READ_BIT))) != 0) {
        goto read_done;
    }
    obj->start_pending = 0;

    while (i > 256) {
        if ((retval = write_tx_fifo(obj, (MXC_S_I2CM_TRANS_TAG_RXDATA_COUNT | 255))) != 0) {
            goto read_done;
        }
        i -= 256;
    }

    if (i > 1) {
        if ((retval = write_tx_fifo(obj, (MXC_S_I2CM_TRANS_TAG_RXDATA_COUNT | (i - 2)))) != 0) {
            goto read_done;
        }
    }

    // start the transaction
    obj->i2c->trans |= MXC_F_I2CM_TRANS_TX_START;

    if ((retval = write_tx_fifo(obj, MXC_S_I2CM_TRANS_TAG_RXDATA_NACK)) != 0) { // NACK last data byte
        goto read_done;
    }

    if (stop) {
        if ((retval = write_tx_fifo(obj, MXC_S_I2CM_TRANS_TAG_STOP)) != 0) { // stop condition
            goto read_done;
        }
    }

    timeout = MXC_I2CM_RX_TIMEOUT;
    i = 0;
    while (i < length) {
        while (!(obj->i2c->intfl & MXC_F_I2CM_INTFL_RX_FIFO_NOT_EMPTY) &&
                (!(obj->i2c->bb & MXC_F_I2CM_BB_RX_FIFO_CNT))) {
            if ((--timeout < 0) || !(obj->i2c->trans & MXC_F_I2CM_TRANS_TX_IN_PROGRESS)) {
                retval = -3;
                goto read_done;
            }
        }

        timeout = MXC_I2CM_RX_TIMEOUT;

        obj->i2c->intfl = MXC_F_I2CM_INTFL_RX_FIFO_NOT_EMPTY;

        uint16_t temp = *obj->rxfifo;

        if (temp & MXC_S_I2CM_RSTLS_TAG_EMPTY) {
            continue;
        }
        data[i++] = (uint8_t) temp;
    }

read_done:

    if (stop) {
        obj->stop_pending = 0;
        if ((err = wait_tx_in_progress(obj)) != 0) {
            retval = (retval ? retval : err);
        }
    } else {
        obj->stop_pending = 1;
    }

    if (retval == 0) {
        return length;
    }

    return retval;
}
