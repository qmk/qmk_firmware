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
#include "wait.h"
#include "gpio.h"

// #define SR_USE_BITBANG

// Bodge for when spi_master is not available
#ifdef SR_USE_BITBANG
#    define CLOCK_DELAY 10

void shift_init_impl(void) {
    setPinOutput(SR_EXP_RCLK_PIN);
    setPinOutput(SPI_DATAOUT_PIN);
    setPinOutput(SPI_SCLK_PIN);
}

void shift_out_impl(const uint8_t *data, uint16_t length) {
    writePinLow(SR_EXP_RCLK_PIN);
    for (uint16_t i = 0; i < length; i++) {
        uint8_t val = data[i];

        // shift out lsb first
        for (uint8_t bit = 0; bit < 8; bit++) {
            writePin(SPI_DATAOUT_PIN, !!(val & (1 << bit)));
            writePin(SPI_SCLK_PIN, true);
            wait_us(CLOCK_DELAY);

            writePin(SPI_SCLK_PIN, false);
            wait_us(CLOCK_DELAY);
        }
    }
    writePinHigh(SR_EXP_RCLK_PIN);
    return SPI_STATUS_SUCCESS;
}

#else

void shift_init_impl(void) { spi_init(); }

void shift_out_impl(const uint8_t *data, uint16_t length) {
    spi_start(SR_EXP_RCLK_PIN, true, 0, 0);

    spi_transmit(data, length);

    spi_stop();
}
#endif

// ***************************************************************

void shift_out(const uint8_t *data, uint16_t length) { shift_out_impl(data, length); }

void shift_enable(void) {
    setPinOutput(SR_EXP_OE_PIN);
    writePinLow(SR_EXP_OE_PIN);
}

void shift_disable(void) {
    setPinOutput(SR_EXP_OE_PIN);
    writePinHigh(SR_EXP_OE_PIN);
}

void shift_init(void) {
    shift_disable();
    shift_init_impl();
}

// ***************************************************************

sr_exp_t sr_exp_data;

void SR_EXP_WriteData(void) {
    uint8_t data[2] = {
        sr_exp_data.reg & 0xFF,         // Shift in bits 7-0
        (sr_exp_data.reg >> 8) & 0xFF,  // Shift in bits 15-8
    };
    shift_out(data, 2);
}

void SR_EXP_Init(void) {
    shift_init();

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

    shift_enable();
}
