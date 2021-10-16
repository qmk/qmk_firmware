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
#include "spi_master.h"

sr_exp_t sr_exp_data;

void SR_EXP_WriteData(void) {
    spi_start(SR_EXP_RCLK_PIN, true, 0, 0);

    spi_write(sr_exp_data.reg & 0xFF);         // Shift in bits 7-0
    spi_write((sr_exp_data.reg >> 8) & 0xFF);  // Shift in bits 15-8

    spi_stop();
}

void SR_EXP_Init(void) {
    // Initialize Shift Register
    setPinOutput(SR_EXP_OE_PIN);
    writePinHigh(SR_EXP_OE_PIN);

    spi_init();

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
    writePinLow(SR_EXP_OE_PIN);
}
