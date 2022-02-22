/*
Copyright (C) 2021 Westberry Technology (ChangZhou) Corp., Ltd

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

#include "wb32_spi_master.h"

#include "timer.h"

#ifndef WB32_SPI_DRIVER
#    define WB32_SPI_DRIVER SPIDQ
#endif

#ifndef WB32_SPI_SCK_PIN
#    define WB32_SPI_SCK_PIN A5
#endif

#ifndef WB32_SPI_MOSI_PIN
#    define WB32_SPI_MOSI_PIN A7
#endif

#ifndef WB32_SPI_MISO_PIN
#    define WB32_SPI_MISO_PIN A6
#endif

#ifndef WB32_SPI_SCK_PAL_MODE
#    define WB32_SPI_SCK_PAL_MODE 5
#endif

#ifndef WB32_SPI_MOSI_PAL_MODE
#    define WB32_SPI_MOSI_PAL_MODE 5
#endif

#ifndef WB32_SPI_MISO_PAL_MODE
#    define WB32_SPI_MISO_PAL_MODE 5
#endif

static pin_t currentSlavePin = NO_PIN;

static SPIConfig spiConfig = {false, NULL, 0, 0, 0, 0};

 void wb32_spi_init(void) {
    static bool is_initialised = false;
    if (!is_initialised) {
        is_initialised = true;

        // Try releasing special pins for a short time
        setPinInput(WB32_SPI_SCK_PIN);
        setPinInput(WB32_SPI_MOSI_PIN);
        setPinInput(WB32_SPI_MISO_PIN);

        chThdSleepMilliseconds(10);

        palSetPadMode(PAL_PORT(WB32_SPI_SCK_PIN), PAL_PAD(WB32_SPI_SCK_PIN), PAL_MODE_ALTERNATE(WB32_SPI_SCK_PAL_MODE) | PAL_OUTPUT_TYPE_PUSHPULL | PAL_OUTPUT_SPEED_HIGHEST);
        palSetPadMode(PAL_PORT(WB32_SPI_MOSI_PIN), PAL_PAD(WB32_SPI_MOSI_PIN), PAL_MODE_ALTERNATE(WB32_SPI_MOSI_PAL_MODE) | PAL_OUTPUT_TYPE_PUSHPULL | PAL_OUTPUT_SPEED_HIGHEST);
        palSetPadMode(PAL_PORT(WB32_SPI_MISO_PIN), PAL_PAD(WB32_SPI_MISO_PIN), PAL_MODE_ALTERNATE(WB32_SPI_MISO_PAL_MODE) | PAL_OUTPUT_TYPE_PUSHPULL | PAL_OUTPUT_SPEED_HIGHEST);
        PAL_PORT(WB32_SPI_SCK_PIN)->CFGMSK = ~(1 << PAL_PAD(WB32_SPI_SCK_PIN));
        PAL_PORT(WB32_SPI_SCK_PIN)->CURRENT = 0x03;
    }
}

bool wb32_spi_start(pin_t slavePin, bool lsbFirst, uint8_t mode, uint16_t divisor) {
    if (currentSlavePin != NO_PIN || slavePin == NO_PIN) {
        return false;
    }

    if (!lsbFirst) {
        osalDbgAssert(lsbFirst != FALSE, "unsupported lsbFirst");
    }

    if (divisor < 1) {
        return false;
    }

    spiConfig.SPI_BaudRatePrescaler = (divisor << 2);

    switch (mode) {
        case 0:
            spiConfig.SPI_CPHA = SPI_CPHA_1Edge;
            spiConfig.SPI_CPOL = SPI_CPOL_Low;
            break;
        case 1:
            spiConfig.SPI_CPHA = SPI_CPHA_2Edge;
            spiConfig.SPI_CPOL = SPI_CPOL_Low;
            break;
        case 2:
            spiConfig.SPI_CPHA = SPI_CPHA_1Edge;
            spiConfig.SPI_CPOL = SPI_CPOL_High;
            break;
        case 3:
            spiConfig.SPI_CPHA = SPI_CPHA_2Edge;
            spiConfig.SPI_CPOL = SPI_CPOL_High;
            break;
    }

    currentSlavePin  = slavePin;
    spiConfig.ssport = PAL_PORT(slavePin);
    spiConfig.sspad  = PAL_PAD(slavePin);

    setPinOutput(slavePin);
    spiStart(&WB32_SPI_DRIVER, &spiConfig);
    spiSelect(&WB32_SPI_DRIVER);

    return true;
}

spi_status_t wb32_spi_write(uint8_t data) {
    uint8_t rxData;
    spiExchange(&WB32_SPI_DRIVER, 1, &data, &rxData);

    return rxData;
}

spi_status_t wb32_spi_read(void) {
    uint8_t data = 0;
    spiReceive(&WB32_SPI_DRIVER, 1, &data);

    return data;
}

spi_status_t wb32_spi_transmit(const uint8_t *data, uint16_t length) {
    spiSend(&WB32_SPI_DRIVER, length, data);
    return SPI_STATUS_SUCCESS;
}

spi_status_t wb32_spi_receive(uint8_t *data, uint16_t length) {
    spiReceive(&WB32_SPI_DRIVER, length, data);
    return SPI_STATUS_SUCCESS;
}

void wb32_spi_stop(void) {
    if (currentSlavePin != NO_PIN) {
        spiUnselect(&WB32_SPI_DRIVER);
        spiStop(&WB32_SPI_DRIVER);
        currentSlavePin = NO_PIN;
    }
}
