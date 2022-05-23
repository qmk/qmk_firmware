// Copyright 2022 Stefan Kerkmann (KarlK90)
// SPDX-License-Identifier: GPL-2.0-or-later

#include <hal.h>

inline bool spi_start_lld(SPIConfig* const spi_config, const bool lsb_first, const uint8_t spi_mode, const uint16_t clock_divisor) {
    int32_t rounded_clock_divisor = round_clock_divisor(clock_divisor);

    if (rounded_clock_divisor < 0) {
        return false;
    }

    spi_config->cr0 = SPI_CR0_SELOEN;
    spi_config->cr1 = SPI_CR1_MODE | 8; // 8 bits and in master mode

    if (lsb_first) {
        spi_config->cr1 |= SPI_CR1_FIRSTBIT;
    }

    switch (spi_mode) {
        case 0:
            spi_config->cr1 |= SPI_CR1_FORMAT_MODE0;
            break;
        case 1:
            spi_config->cr1 |= SPI_CR1_FORMAT_MODE1;
            break;
        case 2:
            spi_config->cr1 |= SPI_CR1_FORMAT_MODE2;
            break;
        case 3:
            spi_config->cr1 |= SPI_CR1_FORMAT_MODE3;
            break;
    }

    spi_config->cpr = (rounded_clock_divisor - 1) >> 1;

    return true;
}
