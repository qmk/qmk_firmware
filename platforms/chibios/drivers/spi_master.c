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
#include "chibios_config.h"
#include <ch.h>
#include <hal.h>

#ifndef SPI_DRIVER
#    define SPI_DRIVER SPID2
#endif

#ifndef SPI_SCK_PIN
#    define SPI_SCK_PIN B13
#endif

#ifndef SPI_SCK_PAL_MODE
#    ifdef USE_GPIOV1
#        define SPI_SCK_PAL_MODE PAL_MODE_ALTERNATE_PUSHPULL
#    else
#        define SPI_SCK_PAL_MODE 5
#    endif
#endif

#ifndef SPI_MOSI_PIN
#    define SPI_MOSI_PIN B15
#endif

#ifndef SPI_MOSI_PAL_MODE
#    ifdef USE_GPIOV1
#        define SPI_MOSI_PAL_MODE PAL_MODE_ALTERNATE_PUSHPULL
#    else
#        define SPI_MOSI_PAL_MODE 5
#    endif
#endif

#ifndef SPI_MISO_PIN
#    define SPI_MISO_PIN B14
#endif

#ifndef SPI_MISO_PAL_MODE
#    ifdef USE_GPIOV1
#        define SPI_MISO_PAL_MODE PAL_MODE_ALTERNATE_PUSHPULL
#    else
#        define SPI_MISO_PAL_MODE 5
#    endif
#endif

static bool spiStarted = false;
#if SPI_SELECT_MODE == SPI_SELECT_MODE_NONE
static pin_t current_slave_pin     = NO_PIN;
static bool  current_cs_active_low = true;
#endif

static SPIConfig spiConfig;

static inline void spi_select(void) {
    spiSelect(&SPI_DRIVER);

#if SPI_SELECT_MODE == SPI_SELECT_MODE_NONE
    if (current_slave_pin != NO_PIN) {
        gpio_write_pin(current_slave_pin, current_cs_active_low ? 0 : 1);
    }
#endif
}

static inline void spi_unselect(void) {
#if SPI_SELECT_MODE == SPI_SELECT_MODE_NONE
    if (current_slave_pin != NO_PIN) {
        gpio_write_pin(current_slave_pin, current_cs_active_low ? 1 : 0);
    }
#endif

    spiUnselect(&SPI_DRIVER);
}

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

bool spi_start_extended(spi_start_config_t *start_config) {
#if (SPI_USE_MUTUAL_EXCLUSION == TRUE)
    spiAcquireBus(&SPI_DRIVER);
#endif // (SPI_USE_MUTUAL_EXCLUSION == TRUE)

    if (spiStarted) {
        return false;
    }
#if SPI_SELECT_MODE != SPI_SELECT_MODE_NONE
    if (start_config->slave_pin == NO_PIN) {
        return false;
    }
#endif

#if !(defined(WB32F3G71xx) || defined(WB32FQ95xx))
    uint16_t roundedDivisor = 2;
    while (roundedDivisor < start_config->divisor) {
        roundedDivisor <<= 1;
    }

#    if defined(AT32F415)
    if (roundedDivisor < 2 || roundedDivisor > 1024) {
        return false;
    }
#    else
    if (roundedDivisor < 2 || roundedDivisor > 256) {
        return false;
    }
#    endif
#endif

#if defined(K20x) || defined(KL2x)
    spiConfig.tar0 = SPIx_CTARn_FMSZ(7) | SPIx_CTARn_ASC(1);

    if (start_config->lsb_first) {
        spiConfig.tar0 |= SPIx_CTARn_LSBFE;
    }

    switch (start_config->mode) {
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

    if (start_config->lsb_first) {
        spiConfig.cr1 |= SPI_CR1_FIRSTBIT;
    }

    switch (start_config->mode) {
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
    if (!start_config->lsb_first) {
        osalDbgAssert(start_config->lsb_first != FALSE, "unsupported lsb_first");
    }

    if (start_config->divisor < 1) {
        return false;
    }

    spiConfig.SPI_BaudRatePrescaler = (start_config->divisor << 2);

    switch (start_config->mode) {
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
    if (start_config->lsb_first) {
        osalDbgAssert(start_config->lsb_first == false, "RP2040s PrimeCell SPI implementation does not support sending LSB first.");
    }

    // Motorola frame format and 8bit transfer data size.
    spiConfig.SSPCR0 = SPI_SSPCR0_FRF_MOTOROLA | SPI_SSPCR0_DSS_8BIT;
    // Serial output clock = (ck_sys or ck_peri) / (SSPCPSR->CPSDVSR * (1 +
    // SSPCR0->SCR)). SCR is always set to zero, as QMK SPI API expects the
    // passed divisor to be the only value to divide the input clock by.
    spiConfig.SSPCPSR = roundedDivisor; // Even number from 2 to 254

    switch (start_config->mode) {
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
#elif defined(AT32F415)
    spiConfig.ctrl1 = 0;

    if (start_config->lsb_first) {
        spiConfig.ctrl1 |= SPI_CTRL1_LTF;
    }

    switch (start_config->mode) {
        case 0:
            break;
        case 1:
            spiConfig.ctrl1 |= SPI_CTRL1_CLKPHA;
            break;
        case 2:
            spiConfig.ctrl1 |= SPI_CTRL1_CLKPOL;
            break;
        case 3:
            spiConfig.ctrl1 |= SPI_CTRL1_CLKPHA | SPI_CTRL1_CLKPOL;
            break;
    }

    switch (roundedDivisor) {
        case 2:
            break;
        case 4:
            spiConfig.ctrl1 |= SPI_CTRL1_MDIV_0;
            break;
        case 8:
            spiConfig.ctrl1 |= SPI_CTRL1_MDIV_1;
            break;
        case 16:
            spiConfig.ctrl1 |= SPI_CTRL1_MDIV_1 | SPI_CTRL1_MDIV_0;
            break;
        case 32:
            spiConfig.ctrl1 |= SPI_CTRL1_MDIV_2;
            break;
        case 64:
            spiConfig.ctrl1 |= SPI_CTRL1_MDIV_2 | SPI_CTRL1_MDIV_0;
            break;
        case 128:
            spiConfig.ctrl1 |= SPI_CTRL1_MDIV_2 | SPI_CTRL1_MDIV_1;
            break;
        case 256:
            spiConfig.ctrl1 |= SPI_CTRL1_MDIV_2 | SPI_CTRL1_MDIV_1 | SPI_CTRL1_MDIV_0;
            break;
        case 512:
            spiConfig.ctrl2 |= SPI_CTRL1_MDIV_3;
            break;
        case 1024:
            spiConfig.ctrl2 |= SPI_CTRL1_MDIV_3;
            spiConfig.ctrl1 |= SPI_CTRL1_MDIV_0;
            break;
    }
#else
    spiConfig.cr1 = 0;

    if (start_config->lsb_first) {
        spiConfig.cr1 |= SPI_CR1_LSBFIRST;
    }

    switch (start_config->mode) {
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
    current_slave_pin     = start_config->slave_pin;
    current_cs_active_low = start_config->cs_active_low;
#endif
#if SPI_SELECT_MODE == SPI_SELECT_MODE_PAD
    spiConfig.ssport = PAL_PORT(start_config->slave_pin);
    spiConfig.sspad  = PAL_PAD(start_config->slave_pin);
    gpio_set_pin_output(start_config->slave_pin);
#elif SPI_SELECT_MODE == SPI_SELECT_MODE_NONE
    if (start_config->slave_pin != NO_PIN) {
        gpio_set_pin_output(start_config->slave_pin);
    }
#else
#    error "Unsupported SPI_SELECT_MODE"
#endif

    spiStart(&SPI_DRIVER, &spiConfig);
    spi_select();

    return true;
}

bool spi_start(pin_t slavePin, bool lsbFirst, uint8_t mode, uint16_t divisor) {
    spi_start_config_t start_config = {0};
    start_config.slave_pin          = slavePin;
    start_config.lsb_first          = lsbFirst;
    start_config.mode               = mode;
    start_config.divisor            = divisor;
    start_config.cs_active_low      = true;
    return spi_start_extended(&start_config);
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
        spi_unselect();
        spiStop(&SPI_DRIVER);
        spiStarted = false;
    }

#if (SPI_USE_MUTUAL_EXCLUSION == TRUE)
    spiReleaseBus(&SPI_DRIVER);
#endif // (SPI_USE_MUTUAL_EXCLUSION == TRUE)
}
