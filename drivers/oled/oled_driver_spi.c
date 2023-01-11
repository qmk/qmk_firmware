/*
Copyright 2019 Ryan Caltabiano <https://github.com/XScorpion2>

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

#include "spi_master.h"
#include "oled_driver.h"
#include "oled_common.h"
#include "progmem.h"
#include "wait.h"

#ifndef OLED_DC_PIN
#    error "The OLED driver in SPI needs a D/C pin defined"
#endif
#ifndef OLED_CS_PIN
#    error "The OLED driver in SPI needs a CS pin defined"
#endif
#ifndef OLED_SPI_MODE
#    define OLED_SPI_MODE 3
#endif
#ifndef OLED_SPI_DIVISOR
#    define OLED_SPI_DIVISOR 2
#endif

// offest arrays by 1 so i2c command doesn't need to be removed.

// Transmit/Write Funcs.
bool oled_cmd(const uint8_t *data, uint16_t size) {
    spi_start(OLED_CS_PIN, false, OLED_SPI_MODE, OLED_SPI_DIVISOR);
    // Command Mode
    writePinLow(OLED_DC_PIN);
    // Send the commands
    if (spi_transmit(&data[1], size - 1) != SPI_STATUS_SUCCESS) {
        spi_stop();
        return false;
    }
    spi_stop();
    return true;
}

bool oled_cmd_P(const uint8_t *data, uint16_t size) {
    return oled_cmd(data, size);
}

bool oled_write_reg(const uint8_t *data, uint16_t size) {
    spi_start(OLED_CS_PIN, false, OLED_SPI_MODE, OLED_SPI_DIVISOR);
    // Command Mode
    writePinHigh(OLED_DC_PIN);
    // Send the commands
    if (spi_transmit(data, size) != SPI_STATUS_SUCCESS) {
        spi_stop();
        return false;
    }
    spi_stop();
    return true;
}

void oled_driver_init(void) {
    spi_init();
    setPinOutput(OLED_CS_PIN);
    writePinHigh(OLED_CS_PIN);

    setPinOutput(OLED_DC_PIN);
    writePinLow(OLED_DC_PIN);
#ifdef OLED_RST_PIN
    /* Reset device */
    setPinOutput(OLED_RST_PIN);
    writePinLow(OLED_RST_PIN);
    wait_ms(20);
    writePinHigh(OLED_RST_PIN);
    wait_ms(20);
#endif
}
