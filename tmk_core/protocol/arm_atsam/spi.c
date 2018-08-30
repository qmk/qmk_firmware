/*
Copyright 2018 Massdrop Inc.

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "arm_atsam_protocol.h"

Srdata_t srdata;

void SPI_WriteSRData(void)
{
    uint16_t timeout;

    SC2_RCLCK_LO;

    timeout = 50000;
    while (!(SCSPI->SPI.INTFLAG.bit.DRE) && --timeout) { DBGC(DC_SPI_WRITE_DRE); }

    SCSPI->SPI.DATA.bit.DATA = srdata.reg & 0xFF; //Shift in bits 7-0
    timeout = 50000;
    while (!(SCSPI->SPI.INTFLAG.bit.TXC) && --timeout) { DBGC(DC_SPI_WRITE_TXC_1); }

    SCSPI->SPI.DATA.bit.DATA = (srdata.reg >> 8) & 0xFF; //Shift in bits 15-8
    timeout = 50000;
    while (!(SCSPI->SPI.INTFLAG.bit.TXC) && --timeout) { DBGC(DC_SPI_WRITE_TXC_2); }

    SC2_RCLCK_HI;
}

void SPI_Init(void)
{
    uint32_t timeout;

    DBGC(DC_SPI_INIT_BEGIN);

    CLK_set_spi_freq(CHAN_SERCOM_SPI, FREQ_SPI_DEFAULT);

    PORT->Group[0].PMUX[6].bit.PMUXE = 2;
    PORT->Group[0].PMUX[6].bit.PMUXO = 2;
    PORT->Group[0].PINCFG[12].bit.PMUXEN = 1;
    PORT->Group[0].PINCFG[13].bit.PMUXEN = 1;

    //Configure Shift Registers
    SC2_DIRSET;
    SC2_RCLCK_HI;
    SC2_OE_DIS;

    SCSPI->SPI.CTRLA.bit.DORD = 1;
    SCSPI->SPI.CTRLA.bit.CPOL = 1;
    SCSPI->SPI.CTRLA.bit.CPHA = 1;
    SCSPI->SPI.CTRLA.bit.DIPO = 3;
    SCSPI->SPI.CTRLA.bit.MODE = 3; //master

    SCSPI->SPI.CTRLA.bit.ENABLE = 1;
    timeout = 50000;
    while (SCSPI->SPI.SYNCBUSY.bit.ENABLE && timeout--) { DBGC(DC_SPI_SYNC_ENABLING); }

    srdata.reg = 0;
    srdata.bit.HUB_CONNECT = 0;
    srdata.bit.HUB_RESET_N = 0;
    srdata.bit.S_UP = 0;
    srdata.bit.E_UP_N = 1;
    srdata.bit.S_DN1 = 1;
    srdata.bit.E_DN1_N = 1;
    srdata.bit.E_VBUS_1 = 0;
    srdata.bit.E_VBUS_2 = 0;
    srdata.bit.SRC_1 = 1;
    srdata.bit.SRC_2 = 1;
    srdata.bit.IRST = 1;
    srdata.bit.SDB_N = 0;
    SPI_WriteSRData();

    //Enable register output
    SC2_OE_ENA;

    DBGC(DC_SPI_INIT_COMPLETE);
}

