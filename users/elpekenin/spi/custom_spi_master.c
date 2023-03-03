/* Copyright 2020 Nick Brassel (tzarc)
 * Copyright 2023 Pablo Martinez (elpekenin)
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

#include "custom_spi_master.h"

static pin_t slave_pins[] = {[0 ... SPI_COUNT-1] = NO_PIN};

static pin_t spi_sck_pins[]  = SPI_SCK_PINS;
static pin_t spi_mosi_pins[] = SPI_MOSI_PINS;
static pin_t spi_miso_pins[] = SPI_MISO_PINS;
_Static_assert(ARRAY_SIZE(spi_sck_pins)  == SPI_COUNT, "SPI_SCK_PINS has to match size with SPI_DRIVERS");
_Static_assert(ARRAY_SIZE(spi_mosi_pins) == SPI_COUNT, "SPI_MOSI_PINS has to match size with SPI_DRIVERS");
_Static_assert(ARRAY_SIZE(spi_miso_pins) == SPI_COUNT, "SPI_MISO_PINS has to match size with SPI_DRIVERS");

SPIDriver * drivers[] = SPI_DRIVERS;

static SPIConfig spi_configs[SPI_COUNT];

bool is_initialised[] = {[0 ... SPI_COUNT-1] = false};

__attribute__((weak)) void custom_spi_init(uint8_t index) {
    if (index > SPI_COUNT-1) {
        spi_dprintf("Index %d is not valid with the current SPI config\n", index);
        return;
    }

    if (!is_initialised[index]) {
        spi_dprintf("Initialising SPI for driver %d\n", index);
        is_initialised[index] = true;

#if defined(K20x) || defined(KL2x) || defined(RP2040)
        spi_configs[index] = (SPIConfig){NULL, 0, 0, 0};
#else
        spi_configs[index] = (SPIConfig){false, NULL, 0, 0, 0, 0};
#endif

        // Try releasing special pins for a short time
        setPinInput(spi_sck_pins[index]);
        setPinInput(spi_mosi_pins[index]);
        setPinInput(spi_miso_pins[index]);

        chThdSleepMilliseconds(10);
#if defined(USE_GPIOV1)
        palSetPadMode(PAL_PORT(spi_sck_pins[index]), PAL_PAD(spi_sck_pins[index]), SPI_SCK_PAL_MODE);
        palSetPadMode(PAL_PORT(spi_mosi_pins[index]), PAL_PAD(spi_mosi_pins[index]), SPI_MOSI_PAL_MODE);
        palSetPadMode(PAL_PORT(spi_miso_pins[index]), PAL_PAD(spi_miso_pins[index]), SPI_MISO_PAL_MODE);
#else
        palSetPadMode(PAL_PORT(spi_sck_pins[index]), PAL_PAD(spi_sck_pins[index]), SPI_SCK_FLAGS);
        palSetPadMode(PAL_PORT(spi_mosi_pins[index]), PAL_PAD(spi_mosi_pins[index]), SPI_MOSI_FLAGS);
        palSetPadMode(PAL_PORT(spi_miso_pins[index]), PAL_PAD(spi_miso_pins[index]), SPI_MISO_FLAGS);
#endif
        spiStop(drivers[index]);
        slave_pins[index] = NO_PIN;
    }
}

bool custom_spi_start(pin_t slavePin, bool lsbFirst, uint8_t mode, uint16_t divisor, uint8_t index) {
    if (index > SPI_COUNT-1) {
        spi_dprintf("Index %d is not valid with the current SPI config\n", index);
        return false;
    }

    spi_dprintf("Starting SPI for driver %d\n", index);

    if (slave_pins[index] != NO_PIN || slavePin == NO_PIN) {
        return false;
    }

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
    spi_configs[index].tar0 = SPIx_CTARn_FMSZ(7) | SPIx_CTARn_ASC(1);

    if (lsbFirst) {
        spi_configs[index].tar0 |= SPIx_CTARn_LSBFE;
    }

    switch (mode) {
        case 0:
            break;
        case 1:
            spi_configs[index].tar0 |= SPIx_CTARn_CPHA;
            break;
        case 2:
            spi_configs[index].tar0 |= SPIx_CTARn_CPOL;
            break;
        case 3:
            spi_configs[index].tar0 |= SPIx_CTARn_CPHA | SPIx_CTARn_CPOL;
            break;
    }

    switch (roundedDivisor) {
        case 2:
            spi_configs[index].tar0 |= SPIx_CTARn_BR(0);
            break;
        case 4:
            spi_configs[index].tar0 |= SPIx_CTARn_BR(1);
            break;
        case 8:
            spi_configs[index].tar0 |= SPIx_CTARn_BR(3);
            break;
        case 16:
            spi_configs[index].tar0 |= SPIx_CTARn_BR(4);
            break;
        case 32:
            spi_configs[index].tar0 |= SPIx_CTARn_BR(5);
            break;
        case 64:
            spi_configs[index].tar0 |= SPIx_CTARn_BR(6);
            break;
        case 128:
            spi_configs[index].tar0 |= SPIx_CTARn_BR(7);
            break;
        case 256:
            spi_configs[index].tar0 |= SPIx_CTARn_BR(8);
            break;
    }

#elif defined(HT32)
    spi_configs[index].cr0 = SPI_CR0_SELOEN;
    spi_configs[index].cr1 = SPI_CR1_MODE | 8; // 8 bits and in master mode

    if (lsbFirst) {
        spi_configs[index].cr1 |= SPI_CR1_FIRSTBIT;
    }

    switch (mode) {
        case 0:
            spi_configs[index].cr1 |= SPI_CR1_FORMAT_MODE0;
            break;
        case 1:
            spi_configs[index].cr1 |= SPI_CR1_FORMAT_MODE1;
            break;
        case 2:
            spi_configs[index].cr1 |= SPI_CR1_FORMAT_MODE2;
            break;
        case 3:
            spi_configs[index].cr1 |= SPI_CR1_FORMAT_MODE3;
            break;
    }

    spi_configs[index].cpr = (roundedDivisor - 1) >> 1;

#elif defined(WB32F3G71xx) || defined(WB32FQ95xx)
    if (!lsbFirst) {
        osalDbgAssert(lsbFirst != FALSE, "unsupported lsbFirst");
    }

    if (divisor < 1) {
        return false;
    }

    spi_configs[index].SPI_BaudRatePrescaler = (divisor << 2);

    switch (mode) {
        case 0:
            spi_configs[index].SPI_CPHA = SPI_CPHA_1Edge;
            spi_configs[index].SPI_CPOL = SPI_CPOL_Low;
            break;
        case 1:
            spi_configs[index].SPI_CPHA = SPI_CPHA_2Edge;
            spi_configs[index].SPI_CPOL = SPI_CPOL_Low;
            break;
        case 2:
            spi_configs[index].SPI_CPHA = SPI_CPHA_1Edge;
            spi_configs[index].SPI_CPOL = SPI_CPOL_High;
            break;
        case 3:
            spi_configs[index].SPI_CPHA = SPI_CPHA_2Edge;
            spi_configs[index].SPI_CPOL = SPI_CPOL_High;
            break;
    }
#elif defined(MCU_RP)
    if (lsbFirst) {
        osalDbgAssert(lsbFirst == false, "RP2040s PrimeCell SPI implementation does not support sending LSB first.");
    }

    // Motorola frame format and 8bit transfer data size.
    spi_configs[index].SSPCR0 = SPI_SSPCR0_FRF_MOTOROLA | SPI_SSPCR0_DSS_8BIT;
    // Serial output clock = (ck_sys or ck_peri) / (SSPCPSR->CPSDVSR * (1 +
    // SSPCR0->SCR)). SCR is always set to zero, as QMK SPI API expects the
    // passed divisor to be the only value to divide the input clock by.
    spi_configs[index].SSPCPSR = roundedDivisor; // Even number from 2 to 254

    switch (mode) {
        case 0:
            spi_configs[index].SSPCR0 &= ~SPI_SSPCR0_SPO; // Clock polarity: low
            spi_configs[index].SSPCR0 &= ~SPI_SSPCR0_SPH; // Clock phase: sample on first edge
            break;
        case 1:
            spi_configs[index].SSPCR0 &= ~SPI_SSPCR0_SPO; // Clock polarity: low
            spi_configs[index].SSPCR0 |= SPI_SSPCR0_SPH;  // Clock phase: sample on second edge transition
            break;
        case 2:
            spi_configs[index].SSPCR0 |= SPI_SSPCR0_SPO;  // Clock polarity: high
            spi_configs[index].SSPCR0 &= ~SPI_SSPCR0_SPH; // Clock phase: sample on first edge
            break;
        case 3:
            spi_configs[index].SSPCR0 |= SPI_SSPCR0_SPO; // Clock polarity: high
            spi_configs[index].SSPCR0 |= SPI_SSPCR0_SPH; // Clock phase: sample on second edge transition
            break;
    }
#else
    spi_configs[index].cr1 = 0;

    if (lsbFirst) {
        spi_configs[index].cr1 |= SPI_CR1_LSBFIRST;
    }

    switch (mode) {
        case 0:
            break;
        case 1:
            spi_configs[index].cr1 |= SPI_CR1_CPHA;
            break;
        case 2:
            spi_configs[index].cr1 |= SPI_CR1_CPOL;
            break;
        case 3:
            spi_configs[index].cr1 |= SPI_CR1_CPHA | SPI_CR1_CPOL;
            break;
    }

    switch (roundedDivisor) {
        case 2:
            break;
        case 4:
            spi_configs[index].cr1 |= SPI_CR1_BR_0;
            break;
        case 8:
            spi_configs[index].cr1 |= SPI_CR1_BR_1;
            break;
        case 16:
            spi_configs[index].cr1 |= SPI_CR1_BR_1 | SPI_CR1_BR_0;
            break;
        case 32:
            spi_configs[index].cr1 |= SPI_CR1_BR_2;
            break;
        case 64:
            spi_configs[index].cr1 |= SPI_CR1_BR_2 | SPI_CR1_BR_0;
            break;
        case 128:
            spi_configs[index].cr1 |= SPI_CR1_BR_2 | SPI_CR1_BR_1;
            break;
        case 256:
            spi_configs[index].cr1 |= SPI_CR1_BR_2 | SPI_CR1_BR_1 | SPI_CR1_BR_0;
            break;
    }
#endif

    slave_pins[index]  = slavePin;
    spi_configs[index].ssport = PAL_PORT(slavePin);
    spi_configs[index].sspad  = PAL_PAD(slavePin);

    setPinOutput(slavePin);
    spiStart(drivers[index], &spi_configs[index]);
    spiSelect(drivers[index]);

    return true;
}

spi_status_t custom_spi_write(uint8_t data, uint8_t index) {
    if (index > SPI_COUNT-1) {
        spi_dprintf("Index %d is not valid with the current SPI config\n", index);
        return SPI_STATUS_ERROR;
    }

    // spi_dprintf("Writing SPI for driver %d\n", index);

    uint8_t rxData;
    spiExchange(drivers[index], 1, &data, &rxData);

    return rxData;
}

spi_status_t custom_spi_read(uint8_t index) {
    if (index > SPI_COUNT-1) {
        spi_dprintf("Index %d is not valid with the current SPI config\n", index);
        return SPI_STATUS_ERROR;
    }

    // spi_dprintf("Reading SPI for driver %d\n", index);

    uint8_t data = 0;
    spiReceive(drivers[index], 1, &data);

    return data;
}

spi_status_t custom_spi_transmit(const uint8_t *data, uint16_t length, uint8_t index) {
    if (index > SPI_COUNT-1) {
        spi_dprintf("Index %d is not valid with the current SPI config\n", index);
        return SPI_STATUS_ERROR;
    }

    // spi_dprintf("Transmitting SPI for driver %d\n", index);

    spiSend(drivers[index], length, data);
    return SPI_STATUS_SUCCESS;
}

spi_status_t custom_spi_receive(uint8_t *data, uint16_t length, uint8_t index) {
    if (index > SPI_COUNT-1) {
        spi_dprintf("Index %d is not valid with the current SPI config\n", index);
        return SPI_STATUS_ERROR;
    }

    // spi_dprintf("Receiving SPI for driver %d\n", index);

    spiReceive(drivers[index], length, data);
    return SPI_STATUS_SUCCESS;
}

void custom_spi_stop(uint8_t index) {
    if (index > SPI_COUNT-1) {
        spi_dprintf("Index %d is not valid with the current SPI config\n", index);
        return;
    }

    spi_dprintf("Stopping SPI for driver %d\n", index);

    if (slave_pins[index] != NO_PIN) {
        spiUnselect(drivers[index]);
        spiStop(drivers[index]);
        slave_pins[index] = NO_PIN;
    }
}
