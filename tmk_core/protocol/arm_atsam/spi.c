/*
Copyright 2019 Massdrop Inc.

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

/* Shift Register output EXPander Data */
sr_exp_t sr_exp_data;

/* Shift Register output EXPander Write Data */
void SR_EXP_WriteData(void)
{
    SR_EXP_RCLK_LO;

    while (!(SR_EXP_SERCOM->SPI.INTFLAG.bit.DRE)) { DBGC(DC_SPI_EXP_WRITE_DRE); }

    /* Shift in bits 7 - 0 */
    SR_EXP_SERCOM->SPI.DATA.bit.DATA = sr_exp_data.reg & 0xFF;
    while (!(SR_EXP_SERCOM->SPI.INTFLAG.bit.TXC)) { DBGC(DC_SPI_EXP_WRITE_TXC_1); }

    /* Shift in bits 15 - 8 */
    SR_EXP_SERCOM->SPI.DATA.bit.DATA = (sr_exp_data.reg >> 8) & 0xFF;
    while (!(SR_EXP_SERCOM->SPI.INTFLAG.bit.TXC)) { DBGC(DC_SPI_EXP_WRITE_TXC_2); }

    SR_EXP_RCLK_HI;
}

/* Shift Register output EXPander Initialization */
void SR_EXP_Init(void)
{
    DBGC(DC_SPI_EXP_INIT_BEGIN);

    CLK_set_spi_freq(CHAN_SERCOM_SPI_EXP, FREQ_SPI_DEFAULT);

    /* Set up MCU shift register pins */
    PORT->Group[SR_EXP_RCLK_PORT].DIRSET.reg = (1 << SR_EXP_RCLK_PIN);
    PORT->Group[SR_EXP_OE_N_PORT].DIRSET.reg = (1 << SR_EXP_OE_N_PIN);

    /* Set up MCU SPI pins */
    PORT->Group[SR_EXP_DATAOUT_PORT].PMUX[SR_EXP_DATAOUT_PIN / 2].bit.SR_EXP_DATAOUT_MUX_SEL = SR_EXP_DATAOUT_MUX; //MUX select for sercom
    PORT->Group[SR_EXP_SCLK_PORT].PMUX[SR_EXP_SCLK_PIN / 2].bit.SR_EXP_SCLK_MUX_SEL = SR_EXP_SCLK_MUX; //MUX select for sercom
    PORT->Group[SR_EXP_DATAOUT_PORT].PINCFG[SR_EXP_DATAOUT_PIN].bit.PMUXEN = 1; //MUX Enable
    PORT->Group[SR_EXP_SCLK_PORT].PINCFG[SR_EXP_SCLK_PIN].bit.PMUXEN = 1; //MUX Enable

    /* Run keyboard init routine to finalize initialization */
    SR_EXP_Init_kb();

    DBGC(DC_SPI_EXP_INIT_COMPLETE);
}

#ifdef SR_KC_SERCOM_NUM

/* Shift Register Key matrix Column drive Data */
sr_kc_t sr_kc_data;

/* Shift Register Key matrix Column drive Write Data */
void SR_KC_WriteData(void)
{
    SR_KC_RCLK_LO;

    while (!(SR_KC_SERCOM->SPI.INTFLAG.bit.DRE)) { DBGC(DC_SPI_KC_WRITE_DRE); }

    /* Shift in bits 8 - 15 */
    SR_KC_SERCOM->SPI.DATA.bit.DATA = (sr_kc_data.reg >> 8) & 0xFF;
    while (!(SR_KC_SERCOM->SPI.INTFLAG.bit.TXC)) { DBGC(DC_SPI_KC_WRITE_TXC_1); }

    /* Shift in bits 0 - 7 */
    SR_KC_SERCOM->SPI.DATA.bit.DATA = sr_kc_data.reg & 0xFF;
    while (!(SR_KC_SERCOM->SPI.INTFLAG.bit.TXC)) { DBGC(DC_SPI_KC_WRITE_TXC_2); }

    SR_KC_RCLK_HI;
}

/* Shift Register Key matrix Column drive Initialization */
void SR_KC_Init(void)
{
    DBGC(DC_SPI_KC_INIT_BEGIN);

    CLK_set_spi_freq(CHAN_SERCOM_SPI_KC, FREQ_SPI_KC_DEFAULT);

    /* Set up MCU shift register pins */
    PORT->Group[SR_KC_RCLK_PORT].DIRSET.reg = (1 << SR_KC_RCLK_PIN);
    PORT->Group[SR_KC_OE_N_PORT].DIRSET.reg = (1 << SR_KC_OE_N_PIN);

    /* Set up MCU SPI pins */
    PORT->Group[SR_KC_DATAOUT_PORT].PMUX[SR_KC_DATAOUT_PIN / 2].bit.SR_KC_DATAOUT_MUX_SEL = SR_KC_DATAOUT_MUX; //MUX select for sercom
    PORT->Group[SR_KC_SCLK_PORT].PMUX[SR_KC_SCLK_PIN / 2].bit.SR_KC_SCLK_MUX_SEL = SR_KC_SCLK_MUX; //MUX select for sercom
    PORT->Group[SR_KC_DATAOUT_PORT].PINCFG[SR_KC_DATAOUT_PIN].bit.PMUXEN = 1; //MUX Enable
    PORT->Group[SR_KC_SCLK_PORT].PINCFG[SR_KC_SCLK_PIN].bit.PMUXEN = 1; //MUX Enable

    /* Initialize shift register */
    SR_KC_OE_N_DIS;
    SR_KC_RCLK_HI;

    SR_KC_SERCOM->SPI.CTRLA.bit.DORD = 0; //Data Order - MSB is transferred first
    SR_KC_SERCOM->SPI.CTRLA.bit.CPOL = 1; //Clock Polarity - SCK high when idle. Leading edge of cycle is falling. Trailing rising.
    SR_KC_SERCOM->SPI.CTRLA.bit.CPHA = 1; //Clock Phase - Leading Edge Falling, change, Trailing Edge - Rising, sample
    SR_KC_SERCOM->SPI.CTRLA.bit.DIPO = 3; //Data In Pinout - SERCOM PAD[3] is used as data input (Configure away from DOPO. Not using input.)
    SR_KC_SERCOM->SPI.CTRLA.bit.DOPO = 0; //Data Output PAD[0], Serial Clock PAD[1]
    SR_KC_SERCOM->SPI.CTRLA.bit.MODE = 3; //Operating Mode - Master operation

    SR_KC_SERCOM->SPI.CTRLA.bit.ENABLE = 1; //Enable - Peripheral is enabled or being enabled
    while (SR_KC_SERCOM->SPI.SYNCBUSY.bit.ENABLE) { DBGC(DC_SPI_KC_SYNC_ENABLING); }

    /* Set default shift register values */
    sr_kc_data.reg = 0;

    /* Write shift register data */
    SR_KC_WriteData();

    /* Enable shift register output */
    SR_KC_OE_N_ENA;

    DBGC(DC_SPI_KC_INIT_COMPLETE);
}

#endif //SR_KC_SERCOM
