/* Copyright 2020 Nick Brassel (tzarc)
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "spi_master.h"
#include "quantum.h"
#include "timer.h"

static pin_t     currentSlavePin = NO_PIN;
static SPIConfig spiConfig       = {false, NULL, 0, 0, 0, 0};

__attribute__((weak)) void spi_init(void) {
    // Try releasing special pins for a short time
    palSetPadMode(PAL_PORT(SPI_SCK_PIN), PAL_PAD(SPI_SCK_PIN), PAL_MODE_INPUT);
    palSetPadMode(PAL_PORT(SPI_MOSI_PIN), PAL_PAD(SPI_MOSI_PIN), PAL_MODE_INPUT);
    palSetPadMode(PAL_PORT(SPI_MISO_PIN), PAL_PAD(SPI_MISO_PIN), PAL_MODE_INPUT);

    chThdSleepMilliseconds(10);
#if defined(USE_GPIOV1)
    palSetPadMode(PAL_PORT(SPI_SCK_PIN), PAL_PAD(SPI_SCK_PIN), PAL_MODE_STM32_ALTERNATE_PUSHPULL);
    palSetPadMode(PAL_PORT(SPI_MOSI_PIN), PAL_PAD(SPI_MOSI_PIN), PAL_MODE_STM32_ALTERNATE_PUSHPULL);
    palSetPadMode(PAL_PORT(SPI_MISO_PIN), PAL_PAD(SPI_MISO_PIN), PAL_MODE_STM32_ALTERNATE_PUSHPULL);
#else
    palSetPadMode(PAL_PORT(SPI_SCK_PIN), PAL_PAD(SPI_SCK_PIN), PAL_MODE_ALTERNATE(SPI_SCK_PAL_MODE) | PAL_STM32_OTYPE_PUSHPULL | PAL_STM32_OSPEED_HIGHEST);
    palSetPadMode(PAL_PORT(SPI_MOSI_PIN), PAL_PAD(SPI_MOSI_PIN), PAL_MODE_ALTERNATE(SPI_MOSI_PAL_MODE) | PAL_STM32_OTYPE_PUSHPULL | PAL_STM32_OSPEED_HIGHEST);
    palSetPadMode(PAL_PORT(SPI_MISO_PIN), PAL_PAD(SPI_MISO_PIN), PAL_MODE_ALTERNATE(SPI_MISO_PAL_MODE) | PAL_STM32_OTYPE_PUSHPULL | PAL_STM32_OSPEED_HIGHEST);
#endif
}

bool spi_start(pin_t slavePin, bool lsbFirst, uint8_t mode, uint16_t divisor) {
    if (currentSlavePin != NO_PIN || slavePin == NO_PIN) {
        return false;
    }

    uint16_t roundedDivisor = 2;
    while (roundedDivisor < divisor) {
        roundedDivisor <<= 1;
    }

    if (roundedDivisor < 2 || roundedDivisor > 256) {
        return false;
    }

    spiConfig.cr1 = 0;

    if (lsbFirst) {
        spiConfig.cr1 |= SPI_CR1_LSBFIRST;
    }

    switch (mode) {
        case 0:
            break;
        case 1:
            spiConfig.cr1 |= SPI_CR1_CPHA;
            break;
        case 2:
            spiConfig.cr1 |= SPI_CR1_CPOL;
            break;
        case 3:
            spiConfig.cr1 |= SPI_CR1_CPHA | SPI_CR1_CPOL;
            break;
    }

    switch (roundedDivisor) {
        case 2:
            break;
        case 4:
            spiConfig.cr1 |= SPI_CR1_BR_0;
            break;
        case 8:
            spiConfig.cr1 |= SPI_CR1_BR_1;
            break;
        case 16:
            spiConfig.cr1 |= SPI_CR1_BR_1 | SPI_CR1_BR_0;
            break;
        case 32:
            spiConfig.cr1 |= SPI_CR1_BR_2;
            break;
        case 64:
            spiConfig.cr1 |= SPI_CR1_BR_2 | SPI_CR1_BR_0;
            break;
        case 128:
            spiConfig.cr1 |= SPI_CR1_BR_2 | SPI_CR1_BR_1;
            break;
        case 256:
            spiConfig.cr1 |= SPI_CR1_BR_2 | SPI_CR1_BR_1 | SPI_CR1_BR_0;
            break;
    }

    currentSlavePin  = slavePin;
    spiConfig.ssport = PAL_PORT(slavePin);
    spiConfig.sspad  = PAL_PAD(slavePin);

    setPinOutput(slavePin);
    spiStart(&SPI_DRIVER, &spiConfig);
    spiSelect(&SPI_DRIVER);

    return true;
}

spi_status_t spi_write(uint8_t data, uint16_t timeout) { return spi_transmit(&data, 1, timeout); }

spi_status_t spi_read(uint16_t timeout) {
    uint8_t data = 0;
    spi_receive(&data, 1, timeout);
    return data;
}

spi_status_t spi_transmit(const uint8_t *data, uint16_t length, uint16_t timeout) {
    spiSend(&SPI_DRIVER, length, data);
    return SPI_STATUS_SUCCESS;
}

spi_status_t spi_receive(uint8_t *data, uint16_t length, uint16_t timeout) {
    spiReceive(&SPI_DRIVER, length, data);
    return SPI_STATUS_SUCCESS;
}

void spi_stop(void) {
    if (currentSlavePin != NO_PIN) {
        spiUnselect(&SPI_DRIVER);
        spiStop(&SPI_DRIVER);
        currentSlavePin = NO_PIN;
    }
}
