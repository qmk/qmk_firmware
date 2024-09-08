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

#include "timer.h"

static bool spiStarted = false;

#if SPI_SELECT_MODE == SPI_SELECT_MODE_NONE
static pin_t currentSlavePin;
#endif

static SPIConfig spiConfig;

__attribute__((weak)) void spi_init(void) {
    static bool is_initialised = false;
    if (!is_initialised) {
        is_initialised = true;

        // Try releasing special pins for a short time
        gpio_set_pin_input(SPI_SCK_PIN);
        if (SPI_MOSI_PIN != NO_PIN) {
            gpio_set_pin_input(SPI_MOSI_PIN);
        }
        if (SPI_MISO_PIN != NO_PIN) {
            gpio_set_pin_input(SPI_MISO_PIN);
        }

        chThdSleepMilliseconds(10);
#if defined(USE_GPIOV1)
        palSetPadMode(PAL_PORT(SPI_SCK_PIN), PAL_PAD(SPI_SCK_PIN), SPI_SCK_PAL_MODE);
        if (SPI_MOSI_PIN != NO_PIN) {
            palSetPadMode(PAL_PORT(SPI_MOSI_PIN), PAL_PAD(SPI_MOSI_PIN), SPI_MOSI_PAL_MODE);
        }
        if (SPI_MISO_PIN != NO_PIN) {
            palSetPadMode(PAL_PORT(SPI_MISO_PIN), PAL_PAD(SPI_MISO_PIN), SPI_MISO_PAL_MODE);
        }
#else
        palSetPadMode(PAL_PORT(SPI_SCK_PIN), PAL_PAD(SPI_SCK_PIN), SPI_SCK_FLAGS);
        if (SPI_MOSI_PIN != NO_PIN) {
            palSetPadMode(PAL_PORT(SPI_MOSI_PIN), PAL_PAD(SPI_MOSI_PIN), SPI_MOSI_FLAGS);
        }
        if (SPI_MISO_PIN != NO_PIN) {
            palSetPadMode(PAL_PORT(SPI_MISO_PIN), PAL_PAD(SPI_MISO_PIN), SPI_MISO_FLAGS);
        }
#endif
        spiStop(&SPI_DRIVER);
        spiStarted = false;
    }
}

bool spi_start(pin_t slavePin, bool lsbFirst, uint8_t mode, uint16_t divisor) {
#if (SPI_USE_MUTUAL_EXCLUSION == TRUE)
    spiAcquireBus(&SPI_DRIVER);
#endif // (SPI_USE_MUTUAL_EXCLUSION == TRUE)

    if (spiStarted) {
        return false;
    }

#if SPI_SELECT_MODE != SPI_SELECT_MODE_NONE
    if (slavePin == NO_PIN) {
        return false;
    }
#endif

#if !(defined(WB32F3G71xx) || defined(WB32FQ95xx))
    uint16_t roundedDivisor = 2;
    while (roundedDivisor < divisor) {
        roundedDivisor <<= 1;
    }

    if (roundedDivisor < 2 || roundedDivisor > 256) {
        return false;
    }
#endif

#if defined(K20x) || defined(KL2x)
    spiConfig.tar0 = SPIx_CTARn_FMSZ(7) | SPIx_CTARn_ASC(1);

    if (lsbFirst) {
        spiConfig.tar0 |= SPIx_CTARn_LSBFE;
    }

    switch (mode) {
        case 0:
            break;
        case 1:
            spiConfig.tar0 |= SPIx_CTARn_CPHA;
            break;
        case 2:
            spiConfig.tar0 |= SPIx_CTARn_CPOL;
            break;
        case 3:
            spiConfig.tar0 |= SPIx_CTARn_CPHA | SPIx_CTARn_CPOL;
            break;
    }

    switch (roundedDivisor) {
        case 2:
            spiConfig.tar0 |= SPIx_CTARn_BR(0);
            break;
        case 4:
            spiConfig.tar0 |= SPIx_CTARn_BR(1);
            break;
        case 8:
            spiConfig.tar0 |= SPIx_CTARn_BR(3);
            break;
        case 16:
            spiConfig.tar0 |= SPIx_CTARn_BR(4);
            break;
        case 32:
            spiConfig.tar0 |= SPIx_CTARn_BR(5);
            break;
        case 64:
            spiConfig.tar0 |= SPIx_CTARn_BR(6);
            break;
        case 128:
            spiConfig.tar0 |= SPIx_CTARn_BR(7);
            break;
        case 256:
            spiConfig.tar0 |= SPIx_CTARn_BR(8);
            break;
    }

#elif defined(HT32)
    spiConfig.cr0 = SPI_CR0_SELOEN;
    spiConfig.cr1 = SPI_CR1_MODE | 8; // 8 bits and in master mode

    if (lsbFirst) {
        spiConfig.cr1 |= SPI_CR1_FIRSTBIT;
    }

    switch (mode) {
        case 0:
            spiConfig.cr1 |= SPI_CR1_FORMAT_MODE0;
            break;
        case 1:
            spiConfig.cr1 |= SPI_CR1_FORMAT_MODE1;
            break;
        case 2:
            spiConfig.cr1 |= SPI_CR1_FORMAT_MODE2;
            break;
        case 3:
            spiConfig.cr1 |= SPI_CR1_FORMAT_MODE3;
            break;
    }

    spiConfig.cpr = (roundedDivisor - 1) >> 1;

#elif defined(WB32F3G71xx) || defined(WB32FQ95xx)
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
#elif defined(MCU_RP)
    if (lsbFirst) {
        osalDbgAssert(lsbFirst == false, "RP2040s PrimeCell SPI implementation does not support sending LSB first.");
    }

    // Motorola frame format and 8bit transfer data size.
    spiConfig.SSPCR0 = SPI_SSPCR0_FRF_MOTOROLA | SPI_SSPCR0_DSS_8BIT;
    // Serial output clock = (ck_sys or ck_peri) / (SSPCPSR->CPSDVSR * (1 +
    // SSPCR0->SCR)). SCR is always set to zero, as QMK SPI API expects the
    // passed divisor to be the only value to divide the input clock by.
    spiConfig.SSPCPSR = roundedDivisor; // Even number from 2 to 254

    switch (mode) {
        case 0:
            spiConfig.SSPCR0 &= ~SPI_SSPCR0_SPO; // Clock polarity: low
            spiConfig.SSPCR0 &= ~SPI_SSPCR0_SPH; // Clock phase: sample on first edge
            break;
        case 1:
            spiConfig.SSPCR0 &= ~SPI_SSPCR0_SPO; // Clock polarity: low
            spiConfig.SSPCR0 |= SPI_SSPCR0_SPH;  // Clock phase: sample on second edge transition
            break;
        case 2:
            spiConfig.SSPCR0 |= SPI_SSPCR0_SPO;  // Clock polarity: high
            spiConfig.SSPCR0 &= ~SPI_SSPCR0_SPH; // Clock phase: sample on first edge
            break;
        case 3:
            spiConfig.SSPCR0 |= SPI_SSPCR0_SPO; // Clock polarity: high
            spiConfig.SSPCR0 |= SPI_SSPCR0_SPH; // Clock phase: sample on second edge transition
            break;
    }
#else
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
#endif

    spiStarted = true;
#if SPI_SELECT_MODE == SPI_SELECT_MODE_NONE
    currentSlavePin = slavePin;
#endif
#if SPI_SELECT_MODE == SPI_SELECT_MODE_PAD
    spiConfig.ssport = PAL_PORT(slavePin);
    spiConfig.sspad  = PAL_PAD(slavePin);
    gpio_set_pin_output(slavePin);
#elif SPI_SELECT_MODE == SPI_SELECT_MODE_NONE
    if (slavePin != NO_PIN) {
        gpio_set_pin_output(slavePin);
    }
#else
#    error "Unsupported SPI_SELECT_MODE"
#endif

    spiStart(&SPI_DRIVER, &spiConfig);
    spiSelect(&SPI_DRIVER);
#if SPI_SELECT_MODE == SPI_SELECT_MODE_NONE
    if (slavePin != NO_PIN) {
        gpio_write_pin_low(slavePin);
    }
#endif

    return true;
}

spi_status_t spi_write(uint8_t data) {
    uint8_t rxData;
    spiExchange(&SPI_DRIVER, 1, &data, &rxData);

    return rxData;
}

spi_status_t spi_read(void) {
    uint8_t data = 0;
    spiReceive(&SPI_DRIVER, 1, &data);

    return data;
}

spi_status_t spi_transmit(const uint8_t *data, uint16_t length) {
    spiSend(&SPI_DRIVER, length, data);
    return SPI_STATUS_SUCCESS;
}

spi_status_t spi_receive(uint8_t *data, uint16_t length) {
    spiReceive(&SPI_DRIVER, length, data);
    return SPI_STATUS_SUCCESS;
}

void spi_stop(void) {
    if (spiStarted) {
#if SPI_SELECT_MODE == SPI_SELECT_MODE_NONE
        if (currentSlavePin != NO_PIN) {
            gpio_write_pin_high(currentSlavePin);
        }
#endif
        spiUnselect(&SPI_DRIVER);
        spiStop(&SPI_DRIVER);
        spiStarted = false;
    }

#if (SPI_USE_MUTUAL_EXCLUSION == TRUE)
    spiReleaseBus(&SPI_DRIVER);
#endif // (SPI_USE_MUTUAL_EXCLUSION == TRUE)
}
