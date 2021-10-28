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
#include "gpio.h"

/* Determine bits to set for mux selection */
#if SPI_DATAOUT_PIN % 2 == 0
#    define SPI_DATAOUT_MUX_SEL PMUXE
#else
#    define SPI_DATAOUT_MUX_SEL PMUXO
#endif

/* Determine bits to set for mux selection */
#if SPI_SCLK_PIN % 2 == 0
#    define SPI_SCLK_MUX_SEL PMUXE
#else
#    define SPI_SCLK_MUX_SEL PMUXO
#endif

static pin_t currentSelectPin = NO_PIN;

__attribute__((weak)) void spi_init(void) {
    static bool is_initialised = false;
    if (!is_initialised) {
        is_initialised = true;

        DBGC(DC_SPI_INIT_BEGIN);

        CLK_set_spi_freq(CHAN_SERCOM_SPI, FREQ_SPI_DEFAULT);

        // Set up MCU SPI pins
        PORT->Group[SAMD_PORT(SPI_DATAOUT_PIN)].PMUX[SAMD_PIN(SPI_DATAOUT_PIN) / 2].bit.SPI_DATAOUT_MUX_SEL = SPI_DATAOUT_MUX;  // MUX select for sercom
        PORT->Group[SAMD_PORT(SPI_SCLK_PIN)].PMUX[SAMD_PIN(SPI_SCLK_PIN) / 2].bit.SPI_SCLK_MUX_SEL          = SPI_SCLK_MUX;     // MUX select for sercom
        PORT->Group[SAMD_PORT(SPI_DATAOUT_PIN)].PINCFG[SAMD_PIN(SPI_DATAOUT_PIN)].bit.PMUXEN                = 1;                // MUX Enable
        PORT->Group[SAMD_PORT(SPI_SCLK_PIN)].PINCFG[SAMD_PIN(SPI_SCLK_PIN)].bit.PMUXEN                      = 1;                // MUX Enable

        DBGC(DC_SPI_INIT_COMPLETE);
    }
}

bool spi_start(pin_t csPin, bool lsbFirst, uint8_t mode, uint16_t divisor) {
    if (currentSelectPin != NO_PIN || csPin == NO_PIN) {
        return false;
    }

    currentSelectPin = csPin;
    setPinOutput(currentSelectPin);
    writePinLow(currentSelectPin);

    SPI_SERCOM->SPI.CTRLA.bit.DORD = lsbFirst;  // Data Order - LSB is transferred first
    SPI_SERCOM->SPI.CTRLA.bit.CPOL = 1;         // Clock Polarity - SCK high when idle. Leading edge of cycle is falling. Trailing rising.
    SPI_SERCOM->SPI.CTRLA.bit.CPHA = 1;         // Clock Phase - Leading Edge Falling, change, Trailing Edge - Rising, sample
    SPI_SERCOM->SPI.CTRLA.bit.DIPO = 3;         // Data In Pinout - SERCOM PAD[3] is used as data input (Configure away from DOPO. Not using input.)
    SPI_SERCOM->SPI.CTRLA.bit.DOPO = 0;         // Data Output PAD[0], Serial Clock PAD[1]
    SPI_SERCOM->SPI.CTRLA.bit.MODE = 3;         // Operating Mode - Master operation

    SPI_SERCOM->SPI.CTRLA.bit.ENABLE = 1;  // Enable - Peripheral is enabled or being enabled
    while (SPI_SERCOM->SPI.SYNCBUSY.bit.ENABLE) {
        DBGC(DC_SPI_SYNC_ENABLING);
    }
    return true;
}

spi_status_t spi_transmit(const uint8_t *data, uint16_t length) {
    while (!(SPI_SERCOM->SPI.INTFLAG.bit.DRE)) {
        DBGC(DC_SPI_WRITE_DRE);
    }

    for (uint16_t i = 0; i < length; i++) {
        SPI_SERCOM->SPI.DATA.bit.DATA = data[i];
        while (!(SPI_SERCOM->SPI.INTFLAG.bit.TXC)) {
            DBGC(DC_SPI_WRITE_TXC_1);
        }
    }

    return SPI_STATUS_SUCCESS;
}

void spi_stop(void) {
    if (currentSelectPin != NO_PIN) {
        setPinOutput(currentSelectPin);
        writePinHigh(currentSelectPin);
        currentSelectPin = NO_PIN;
    }
}

// Not implemented yet....

spi_status_t spi_write(uint8_t data);

spi_status_t spi_read(void);

spi_status_t spi_receive(uint8_t *data, uint16_t length);
