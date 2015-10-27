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

#include <string.h>
#include "mbed_assert.h"
#include "cmsis.h"
#include "spi_api.h"
#include "pinmap.h"
#include "ioman_regs.h"
#include "clkman_regs.h"
#include "PeripheralPins.h"

#define DEFAULT_CHAR	8
#define DEFAULT_MODE	0
#define DEFAULT_FREQ 	1000000

// Formatting settings
static int spi_bits;

//******************************************************************************
void spi_init(spi_t *obj, PinName mosi, PinName miso, PinName sclk, PinName ssel)
{
    // Make sure pins are pointing to the same SPI instance
    SPIName spi_mosi = (SPIName)pinmap_peripheral(mosi, PinMap_SPI_MOSI);
    SPIName spi_miso = (SPIName)pinmap_peripheral(miso, PinMap_SPI_MISO);
    SPIName spi_sclk = (SPIName)pinmap_peripheral(sclk, PinMap_SPI_SCLK);
    SPIName spi_ssel = (SPIName)pinmap_peripheral(ssel, PinMap_SPI_SSEL);

    SPIName spi_data = (SPIName)pinmap_merge(spi_mosi, spi_miso);
    SPIName spi_cntl;

    // Give the application the option to manually control Slave Select
    if((SPIName)spi_ssel != (SPIName)NC) {
        spi_cntl = (SPIName)pinmap_merge(spi_sclk, spi_ssel);
    } else {
        spi_cntl = spi_sclk;
    }

    SPIName spi = (SPIName)pinmap_merge(spi_data, spi_cntl);

    MBED_ASSERT((SPIName)spi != (SPIName)NC);

    // Set the obj pointer to the proper SPI Instance
    obj->spi = (mxc_spi_regs_t*)spi;

    // Set the SPI index and FIFOs
    obj->index = MXC_SPI_BASE_TO_INSTANCE(obj->spi);
    obj->rxfifo = MXC_SPI_GET_RXFIFO(obj->index);
    obj->txfifo = MXC_SPI_GET_TXFIFO(obj->index);

    // Configure the pins
    pinmap_pinout(mosi, PinMap_SPI_MOSI);
    pinmap_pinout(miso, PinMap_SPI_MISO);
    pinmap_pinout(sclk, PinMap_SPI_SCLK);
    pinmap_pinout(ssel, PinMap_SPI_SSEL);

    // Enable SPI and FIFOs
    obj->spi->gen_ctrl = (MXC_F_SPI_GEN_CTRL_SPI_MSTR_EN |
                          MXC_F_SPI_GEN_CTRL_TX_FIFO_EN |
                          MXC_F_SPI_GEN_CTRL_RX_FIFO_EN );

    // Give instance the default settings
    spi_format(obj, DEFAULT_CHAR, DEFAULT_MODE, 0);
    spi_frequency(obj, DEFAULT_FREQ);
}

//******************************************************************************
void spi_format(spi_t *obj, int bits, int mode, int slave)
{
    // Check the validity of the inputs
    MBED_ASSERT(((bits >= 1) && (bits <= 32)) && ((mode >= 0) && (mode <= 3)));

    // Only supports master mode
    MBED_ASSERT(!slave);

    // Save formatting data
    spi_bits = bits;

    // Set the mode
    obj->spi->mstr_cfg &= ~(MXC_F_SPI_MSTR_CFG_SPI_MODE);
    obj->spi->mstr_cfg |= (mode << MXC_F_SPI_MSTR_CFG_SPI_MODE_POS);
}

//******************************************************************************
void spi_frequency(spi_t *obj, int hz)
{
    // Maximum frequency is half the system frequency
    MBED_ASSERT((unsigned int)hz < (SystemCoreClock / 2));
    unsigned clocks = ((SystemCoreClock/2)/(hz));

    // Figure out the divider ratio
    int clk_div = 1;
    while(clk_div < 10) {
        if(clocks < 0x10) {
            break;
        }
        clk_div++;
        clocks = clocks >> 1;
    }

    // Turn on the SPI clock
    if(obj->index == 0) {
        MXC_CLKMAN->clk_ctrl_3_spi0 = clk_div;
    } else if(obj->index == 1) {
        MXC_CLKMAN->clk_ctrl_4_spi1 = clk_div;
    } else if(obj->index == 2) {
        MXC_CLKMAN->clk_ctrl_5_spi2 = clk_div;
    } else {
        MBED_ASSERT(0);
    }

    // Set the number of clocks to hold sclk high and low
    MXC_SET_FIELD(&obj->spi->mstr_cfg, (MXC_F_SPI_MSTR_CFG_SCK_HI_CLK | MXC_F_SPI_MSTR_CFG_SCK_LO_CLK),
        ((clocks << MXC_F_SPI_MSTR_CFG_SCK_HI_CLK_POS) | (clocks << MXC_F_SPI_MSTR_CFG_SCK_LO_CLK_POS)));
}

//******************************************************************************
int spi_master_write(spi_t *obj, int value)
{
    int bits = spi_bits;
    if(spi_bits == 32) {
        bits = 0;
    }
    // Create the header
    uint16_t header = ((0x3 << MXC_F_SPI_FIFO_DIR_POS ) |  // TX and RX
                       (0x0 << MXC_F_SPI_FIFO_UNIT_POS) | // Send bits
                       (bits << MXC_F_SPI_FIFO_SIZE_POS) | // Number of units
                       (0x1 << MXC_F_SPI_FIFO_DASS_POS));      // Deassert SS

    // Send the message header
    obj->txfifo->txfifo_16 = header;

    // Send the data
    if(spi_bits < 17) {
        obj->txfifo->txfifo_16 = (uint16_t)value;
    } else {
        obj->txfifo->txfifo_32 = (uint32_t)value;
    }

    // Get the data
    bits = spi_bits;
    int result = 0;
    int i = 0;
    while(bits > 0) {
        // Wait for data
        while(((obj->spi->fifo_ctrl & MXC_F_SPI_FIFO_CTRL_RX_FIFO_USED)
                >> MXC_F_SPI_FIFO_CTRL_RX_FIFO_USED_POS) < 1) {}

        result |= (obj->rxfifo->rxfifo_8 << (i++*8));
        bits-=8;
    }

    return result;
}

//******************************************************************************
int spi_busy(spi_t *obj)
{
    return !(obj->spi->intfl & MXC_F_SPI_INTFL_TX_READY);
}
