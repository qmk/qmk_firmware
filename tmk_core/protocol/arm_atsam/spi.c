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

sr_exp_t sr_exp_data;

void SR_EXP_WriteData(void) {
    SR_EXP_RCLK_LO;

    while (!(SR_EXP_SERCOM->SPI.INTFLAG.bit.DRE)) {
        DBGC(DC_SPI_WRITE_DRE);
    }

    SR_EXP_SERCOM->SPI.DATA.bit.DATA = sr_exp_data.reg & 0xFF;  // Shift in bits 7-0
    while (!(SR_EXP_SERCOM->SPI.INTFLAG.bit.TXC)) {
        DBGC(DC_SPI_WRITE_TXC_1);
    }

    SR_EXP_SERCOM->SPI.DATA.bit.DATA = (sr_exp_data.reg >> 8) & 0xFF;  // Shift in bits 15-8
    while (!(SR_EXP_SERCOM->SPI.INTFLAG.bit.TXC)) {
        DBGC(DC_SPI_WRITE_TXC_2);
    }

    SR_EXP_RCLK_HI;
}

void SR_EXP_Init(void) {
    DBGC(DC_SPI_INIT_BEGIN);

    CLK_set_spi_freq(CHAN_SERCOM_SPI, FREQ_SPI_DEFAULT);

    // Set up MCU Shift Register pins
    PORT->Group[SR_EXP_RCLK_PORT].DIRSET.reg = (1 << SR_EXP_RCLK_PIN);
    PORT->Group[SR_EXP_OE_N_PORT].DIRSET.reg = (1 << SR_EXP_OE_N_PIN);

    // Set up MCU SPI pins
    PORT->Group[SR_EXP_DATAOUT_PORT].PMUX[SR_EXP_DATAOUT_PIN / 2].bit.SR_EXP_DATAOUT_MUX_SEL = SR_EXP_DATAOUT_MUX;  // MUX select for sercom
    PORT->Group[SR_EXP_SCLK_PORT].PMUX[SR_EXP_SCLK_PIN / 2].bit.SR_EXP_SCLK_MUX_SEL          = SR_EXP_SCLK_MUX;     // MUX select for sercom
    PORT->Group[SR_EXP_DATAOUT_PORT].PINCFG[SR_EXP_DATAOUT_PIN].bit.PMUXEN                   = 1;                   // MUX Enable
    PORT->Group[SR_EXP_SCLK_PORT].PINCFG[SR_EXP_SCLK_PIN].bit.PMUXEN                         = 1;                   // MUX Enable

    // Initialize Shift Register
    SR_EXP_OE_N_DIS;
    SR_EXP_RCLK_HI;

    SR_EXP_SERCOM->SPI.CTRLA.bit.DORD = 1;  // Data Order - LSB is transferred first
    SR_EXP_SERCOM->SPI.CTRLA.bit.CPOL = 1;  // Clock Polarity - SCK high when idle. Leading edge of cycle is falling. Trailing rising.
    SR_EXP_SERCOM->SPI.CTRLA.bit.CPHA = 1;  // Clock Phase - Leading Edge Falling, change, Trailing Edge - Rising, sample
    SR_EXP_SERCOM->SPI.CTRLA.bit.DIPO = 3;  // Data In Pinout - SERCOM PAD[3] is used as data input (Configure away from DOPO. Not using input.)
    SR_EXP_SERCOM->SPI.CTRLA.bit.DOPO = 0;  // Data Output PAD[0], Serial Clock PAD[1]
    SR_EXP_SERCOM->SPI.CTRLA.bit.MODE = 3;  // Operating Mode - Master operation

    SR_EXP_SERCOM->SPI.CTRLA.bit.ENABLE = 1;  // Enable - Peripheral is enabled or being enabled
    while (SR_EXP_SERCOM->SPI.SYNCBUSY.bit.ENABLE) {
        DBGC(DC_SPI_SYNC_ENABLING);
    }

    sr_exp_data.reg             = 0;
    sr_exp_data.bit.HUB_CONNECT = 0;
    sr_exp_data.bit.HUB_RESET_N = 0;
    sr_exp_data.bit.S_UP        = 0;
    sr_exp_data.bit.E_UP_N      = 1;
    sr_exp_data.bit.S_DN1       = 1;
    sr_exp_data.bit.E_DN1_N     = 1;
    sr_exp_data.bit.E_VBUS_1    = 0;
    sr_exp_data.bit.E_VBUS_2    = 0;
    sr_exp_data.bit.SRC_1       = 1;
    sr_exp_data.bit.SRC_2       = 1;
    sr_exp_data.bit.IRST        = 1;
    sr_exp_data.bit.SDB_N       = 0;
    SR_EXP_WriteData();

    // Enable Shift Register output
    SR_EXP_OE_N_ENA;

    DBGC(DC_SPI_INIT_COMPLETE);
}
