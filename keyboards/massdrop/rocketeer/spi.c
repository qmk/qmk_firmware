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

void SR_EXP_Init_kb(void) {
    /* Initialize shift register */
    SR_EXP_OE_N_DIS;
    SR_EXP_RCLK_HI;

    SR_EXP_SERCOM->SPI.CTRLA.bit.DORD = 1;      //Data Order - LSB is transferred first
    SR_EXP_SERCOM->SPI.CTRLA.bit.CPOL = 1;      //Clock Polarity - SCK high when idle. Leading edge of cycle is falling. Trailing rising.
    SR_EXP_SERCOM->SPI.CTRLA.bit.CPHA = 1;      //Clock Phase - Leading Edge Falling, change, Trailing Edge - Rising, sample
    SR_EXP_SERCOM->SPI.CTRLA.bit.DIPO = 3;      //Data In Pinout - SERCOM PAD[3] is used as data input (Configure away from DOPO. Not using input.)
    SR_EXP_SERCOM->SPI.CTRLA.bit.DOPO = 0;      //Data Output PAD[0], Serial Clock PAD[1]
    SR_EXP_SERCOM->SPI.CTRLA.bit.MODE = 3;      //Operating Mode - Master operation

    SR_EXP_SERCOM->SPI.CTRLA.bit.ENABLE = 1;    //Enable - Peripheral is enabled or being enabled
    while (SR_EXP_SERCOM->SPI.SYNCBUSY.bit.ENABLE) { DBGC(DC_SPI_EXP_SYNC_ENABLING); }

    /* Set default shift register values */
    sr_exp_data.reg = 0;                        //Clear data register
    sr_exp_data.bit.HUB_CONNECT = 0;            //USB Hub disconnected
    sr_exp_data.bit.HUB_RESET_N = 0;            //USB Hub in reset state

    sr_exp_data.bit.SRC_1_A5 = 1;               //Set CON1 CC A5 as Rd 5.1k
    sr_exp_data.bit.SRC_1_B5 = 1;               //Set CON1 CC B5 as Rd 5.1k
    sr_exp_data.bit.SRC_2_A5 = 1;               //Set CON2 CC A5 as Rd 5.1k
    sr_exp_data.bit.SRC_2_B5 = 1;               //Set CON2 CC B5 as Rd 5.1k
    sr_exp_data.bit.S_A_UP = 0;                 //0 = DN1 to A and UP to B, 1 = DN1 to B and UP to A
    sr_exp_data.bit.S_A_EXT = 1;                //0 = Onboard, 1 = Offboard
    sr_exp_data.bit.S_B_EXT = 0;                //1 = Onboard, 0 = Offboard

    sr_exp_data.bit.ENB = 0;                    //Disable CON1
    sr_exp_data.bit.ENA = 0;                    //Disable CON2
    sr_exp_data.bit.E_VBUS_1 = 0;               //Disable CON1 5V
    sr_exp_data.bit.E_VBUS_2 = 0;               //Disable CON2 5V
    sr_exp_data.bit.IRST = 1;                   //LED drivers I2C in reset
    sr_exp_data.bit.SDB_N = 0;                  //LED drivers in shutdown

    /* Write shift register data */
    SR_EXP_WriteData();

    /* Enable shift register output */
    SR_EXP_OE_N_ENA;
}
