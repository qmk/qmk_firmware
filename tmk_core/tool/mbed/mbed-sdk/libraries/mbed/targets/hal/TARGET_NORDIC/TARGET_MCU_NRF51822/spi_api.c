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
//#include <math.h>
#include "mbed_assert.h"
#include "spi_api.h"
#include "cmsis.h"
#include "pinmap.h"
#include "mbed_error.h"

#define SPIS_MESSAGE_SIZE 1
volatile uint8_t m_tx_buf[SPIS_MESSAGE_SIZE] = {0};
volatile uint8_t m_rx_buf[SPIS_MESSAGE_SIZE] = {0};

// nRF51822's I2C_0 and SPI_0 (I2C_1, SPI_1 and SPIS1) share the same address.
// They can't be used at the same time. So we use two global variable to track the usage.
// See nRF51822 address information at nRF51822_PS v2.0.pdf - Table 15 Peripheral instance reference
extern volatile i2c_spi_peripheral_t i2c0_spi0_peripheral; // from i2c_api.c
extern volatile i2c_spi_peripheral_t i2c1_spi1_peripheral;

void spi_init(spi_t *obj, PinName mosi, PinName miso, PinName sclk, PinName ssel)
{
    SPIName spi;
    
    if (ssel == NC && i2c0_spi0_peripheral.usage == I2C_SPI_PERIPHERAL_FOR_SPI &&
            i2c0_spi0_peripheral.sda_mosi == (uint8_t)mosi &&
            i2c0_spi0_peripheral.scl_miso == (uint8_t)miso &&
            i2c0_spi0_peripheral.sclk     == (uint8_t)sclk) {
        // The SPI with the same pins is already initialized
        spi = SPI_0;
        obj->peripheral = 0x1;
    } else if (ssel == NC && i2c1_spi1_peripheral.usage == I2C_SPI_PERIPHERAL_FOR_SPI &&
            i2c1_spi1_peripheral.sda_mosi == (uint8_t)mosi &&
            i2c1_spi1_peripheral.scl_miso == (uint8_t)miso &&
            i2c1_spi1_peripheral.sclk     == (uint8_t)sclk) {
        // The SPI with the same pins is already initialized
        spi = SPI_1;
        obj->peripheral = 0x2;
    } else if (i2c1_spi1_peripheral.usage == 0) {
        i2c1_spi1_peripheral.usage = I2C_SPI_PERIPHERAL_FOR_SPI;
        i2c1_spi1_peripheral.sda_mosi = (uint8_t)mosi;
        i2c1_spi1_peripheral.scl_miso = (uint8_t)miso;
        i2c1_spi1_peripheral.sclk     = (uint8_t)sclk;
        
        spi = SPI_1;
        obj->peripheral = 0x2;
    } else if (i2c0_spi0_peripheral.usage == 0) {
        i2c0_spi0_peripheral.usage = I2C_SPI_PERIPHERAL_FOR_SPI;
        i2c0_spi0_peripheral.sda_mosi = (uint8_t)mosi;
        i2c0_spi0_peripheral.scl_miso = (uint8_t)miso;
        i2c0_spi0_peripheral.sclk     = (uint8_t)sclk;
        
        spi = SPI_0;
        obj->peripheral = 0x1;
    } else {
        // No available peripheral
        error("No available SPI");
    }

    if (ssel==NC) {
        obj->spi  = (NRF_SPI_Type *)spi;
        obj->spis = (NRF_SPIS_Type *)NC;
    } else {
        obj->spi  = (NRF_SPI_Type *)NC;
        obj->spis = (NRF_SPIS_Type *)spi;
    }

    // pin out the spi pins
    if (ssel != NC) { //slave
        obj->spis->POWER = 0;
        obj->spis->POWER = 1;

        NRF_GPIO->PIN_CNF[mosi] = (GPIO_PIN_CNF_SENSE_Disabled << GPIO_PIN_CNF_SENSE_Pos)
                                    | (GPIO_PIN_CNF_DRIVE_S0S1 << GPIO_PIN_CNF_DRIVE_Pos)
                                    | (GPIO_PIN_CNF_PULL_Disabled << GPIO_PIN_CNF_PULL_Pos)
                                    | (GPIO_PIN_CNF_INPUT_Connect << GPIO_PIN_CNF_INPUT_Pos)
                                    | (GPIO_PIN_CNF_DIR_Input << GPIO_PIN_CNF_DIR_Pos);
        NRF_GPIO->PIN_CNF[miso] = (GPIO_PIN_CNF_SENSE_Disabled << GPIO_PIN_CNF_SENSE_Pos)
                                    | (GPIO_PIN_CNF_DRIVE_S0S1 << GPIO_PIN_CNF_DRIVE_Pos)
                                    | (GPIO_PIN_CNF_PULL_Disabled << GPIO_PIN_CNF_PULL_Pos)
                                    | (GPIO_PIN_CNF_INPUT_Connect << GPIO_PIN_CNF_INPUT_Pos)
                                    | (GPIO_PIN_CNF_DIR_Input << GPIO_PIN_CNF_DIR_Pos);
        NRF_GPIO->PIN_CNF[sclk] = (GPIO_PIN_CNF_SENSE_Disabled << GPIO_PIN_CNF_SENSE_Pos)
                                    | (GPIO_PIN_CNF_DRIVE_S0S1 << GPIO_PIN_CNF_DRIVE_Pos)
                                    | (GPIO_PIN_CNF_PULL_Disabled << GPIO_PIN_CNF_PULL_Pos)
                                    | (GPIO_PIN_CNF_INPUT_Connect << GPIO_PIN_CNF_INPUT_Pos)
                                    | (GPIO_PIN_CNF_DIR_Input << GPIO_PIN_CNF_DIR_Pos);
        NRF_GPIO->PIN_CNF[ssel] = (GPIO_PIN_CNF_SENSE_Disabled << GPIO_PIN_CNF_SENSE_Pos)
                                    | (GPIO_PIN_CNF_DRIVE_S0S1 << GPIO_PIN_CNF_DRIVE_Pos)
                                    | (GPIO_PIN_CNF_PULL_Disabled << GPIO_PIN_CNF_PULL_Pos)
                                    | (GPIO_PIN_CNF_INPUT_Connect << GPIO_PIN_CNF_INPUT_Pos)
                                    | (GPIO_PIN_CNF_DIR_Input << GPIO_PIN_CNF_DIR_Pos);

        obj->spis->PSELMOSI = mosi;
        obj->spis->PSELMISO = miso;
        obj->spis->PSELSCK  = sclk;
        obj->spis->PSELCSN  = ssel;

        obj->spis->EVENTS_END      = 0;
        obj->spis->EVENTS_ACQUIRED = 0;
        obj->spis->MAXRX           = SPIS_MESSAGE_SIZE;
        obj->spis->MAXTX           = SPIS_MESSAGE_SIZE;
        obj->spis->TXDPTR          = (uint32_t)&m_tx_buf[0];
        obj->spis->RXDPTR          = (uint32_t)&m_rx_buf[0];
        obj->spis->SHORTS          = (SPIS_SHORTS_END_ACQUIRE_Enabled << SPIS_SHORTS_END_ACQUIRE_Pos);

        spi_format(obj, 8, 0, 1);  // 8 bits, mode 0, slave
    } else { //master
        obj->spi->POWER = 0;
        obj->spi->POWER = 1;

        //NRF_GPIO->DIR |= (1<<mosi);
        NRF_GPIO->PIN_CNF[mosi] = (GPIO_PIN_CNF_SENSE_Disabled << GPIO_PIN_CNF_SENSE_Pos)
                                    | (GPIO_PIN_CNF_DRIVE_S0S1 << GPIO_PIN_CNF_DRIVE_Pos)
                                    | (GPIO_PIN_CNF_PULL_Disabled << GPIO_PIN_CNF_PULL_Pos)
                                    | (GPIO_PIN_CNF_INPUT_Connect << GPIO_PIN_CNF_INPUT_Pos)
                                    | (GPIO_PIN_CNF_DIR_Output << GPIO_PIN_CNF_DIR_Pos);
        obj->spi->PSELMOSI = mosi;

        NRF_GPIO->PIN_CNF[sclk] = (GPIO_PIN_CNF_SENSE_Disabled << GPIO_PIN_CNF_SENSE_Pos)
                                    | (GPIO_PIN_CNF_DRIVE_S0S1 << GPIO_PIN_CNF_DRIVE_Pos)
                                    | (GPIO_PIN_CNF_PULL_Disabled << GPIO_PIN_CNF_PULL_Pos)
                                    | (GPIO_PIN_CNF_INPUT_Connect << GPIO_PIN_CNF_INPUT_Pos)
                                    | (GPIO_PIN_CNF_DIR_Output << GPIO_PIN_CNF_DIR_Pos);
        obj->spi->PSELSCK = sclk;

        //NRF_GPIO->DIR &= ~(1<<miso);
        NRF_GPIO->PIN_CNF[miso] = (GPIO_PIN_CNF_SENSE_Disabled << GPIO_PIN_CNF_SENSE_Pos)
                                    | (GPIO_PIN_CNF_DRIVE_S0S1 << GPIO_PIN_CNF_DRIVE_Pos)
                                    | (GPIO_PIN_CNF_PULL_Disabled << GPIO_PIN_CNF_PULL_Pos)
                                    | (GPIO_PIN_CNF_INPUT_Connect << GPIO_PIN_CNF_INPUT_Pos)
                                    | (GPIO_PIN_CNF_DIR_Input << GPIO_PIN_CNF_DIR_Pos);

        obj->spi->PSELMISO = miso;

        obj->spi->EVENTS_READY = 0U;

        spi_format(obj, 8, 0, 0);  // 8 bits, mode 0, master
        spi_frequency(obj, 1000000);
    }
}

void spi_free(spi_t *obj)
{
}

static inline void spi_disable(spi_t *obj, int slave)
{
    if (slave) {
        obj->spis->ENABLE = (SPIS_ENABLE_ENABLE_Disabled << SPIS_ENABLE_ENABLE_Pos);
    } else {
        obj->spi->ENABLE = (SPI_ENABLE_ENABLE_Disabled << SPI_ENABLE_ENABLE_Pos);
    }
}

static inline void spi_enable(spi_t *obj, int slave)
{
    if (slave) {
        obj->spis->ENABLE = (SPIS_ENABLE_ENABLE_Enabled << SPIS_ENABLE_ENABLE_Pos);
    } else {
        obj->spi->ENABLE = (SPI_ENABLE_ENABLE_Enabled << SPI_ENABLE_ENABLE_Pos);
    }
}

void spi_format(spi_t *obj, int bits, int mode, int slave)
{
    uint32_t config_mode = 0;
    spi_disable(obj, slave);

    if (bits != 8) {
        error("Only 8bits SPI supported");
    }

    switch (mode) {
        case 0:
            config_mode = (SPI_CONFIG_CPHA_Leading << SPI_CONFIG_CPHA_Pos) | (SPI_CONFIG_CPOL_ActiveHigh << SPI_CONFIG_CPOL_Pos);
            break;
        case 1:
            config_mode = (SPI_CONFIG_CPHA_Trailing << SPI_CONFIG_CPHA_Pos) | (SPI_CONFIG_CPOL_ActiveHigh << SPI_CONFIG_CPOL_Pos);
            break;
        case 2:
            config_mode = (SPI_CONFIG_CPHA_Leading << SPI_CONFIG_CPHA_Pos) | (SPI_CONFIG_CPOL_ActiveLow << SPI_CONFIG_CPOL_Pos);
            break;
        case 3:
            config_mode = (SPI_CONFIG_CPHA_Trailing << SPI_CONFIG_CPHA_Pos) | (SPI_CONFIG_CPOL_ActiveLow << SPI_CONFIG_CPOL_Pos);
            break;
        default:
            error("SPI format error");
            break;
    }
    //default to msb first
    if (slave) {
        obj->spis->CONFIG = (config_mode | (SPI_CONFIG_ORDER_MsbFirst << SPI_CONFIG_ORDER_Pos));
    } else {
        obj->spi->CONFIG = (config_mode | (SPI_CONFIG_ORDER_MsbFirst << SPI_CONFIG_ORDER_Pos));
    }

    spi_enable(obj, slave);
}

void spi_frequency(spi_t *obj, int hz)
{
    if ((int)obj->spi==NC) {
        return;
    }
    spi_disable(obj, 0);

    if (hz<250000) { //125Kbps
        obj->spi->FREQUENCY = (uint32_t) SPI_FREQUENCY_FREQUENCY_K125;
    } else if (hz<500000) { //250Kbps
        obj->spi->FREQUENCY = (uint32_t) SPI_FREQUENCY_FREQUENCY_K250;
    } else if (hz<1000000) { //500Kbps
        obj->spi->FREQUENCY = (uint32_t) SPI_FREQUENCY_FREQUENCY_K500;
    } else if (hz<2000000) { //1Mbps
        obj->spi->FREQUENCY = (uint32_t) SPI_FREQUENCY_FREQUENCY_M1;
    } else if (hz<4000000) { //2Mbps
        obj->spi->FREQUENCY = (uint32_t) SPI_FREQUENCY_FREQUENCY_M2;
    } else if (hz<8000000) { //4Mbps
        obj->spi->FREQUENCY = (uint32_t) SPI_FREQUENCY_FREQUENCY_M4;
    } else { //8Mbps
        obj->spi->FREQUENCY = (uint32_t) SPI_FREQUENCY_FREQUENCY_M8;
    }

    spi_enable(obj, 0);
}

static inline int spi_readable(spi_t *obj)
{
    return (obj->spi->EVENTS_READY == 1);
}

static inline int spi_writeable(spi_t *obj)
{
    return (obj->spi->EVENTS_READY == 0);
}

static inline int spi_read(spi_t *obj)
{
    while (!spi_readable(obj)) {
    }

    obj->spi->EVENTS_READY = 0;
    return (int)obj->spi->RXD;
}

int spi_master_write(spi_t *obj, int value)
{
    while (!spi_writeable(obj)) {
    }
    obj->spi->TXD = (uint32_t)value;
    return spi_read(obj);
}

//static inline int spis_writeable(spi_t *obj) {
//    return (obj->spis->EVENTS_ACQUIRED==1);
//}

int spi_slave_receive(spi_t *obj)
{
    return obj->spis->EVENTS_END;
}

int spi_slave_read(spi_t *obj)
{
    return m_rx_buf[0];
}

void spi_slave_write(spi_t *obj, int value)
{
    m_tx_buf[0]                = value & 0xFF;
    obj->spis->TASKS_RELEASE   = 1;
    obj->spis->EVENTS_ACQUIRED = 0;
    obj->spis->EVENTS_END      = 0;
}
