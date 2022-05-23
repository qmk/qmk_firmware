// Copyright 2022 Stefan Kerkmann (KarlK90)
// SPDX-License-Identifier: GPL-2.0-or-later

#include <hal.h>

inline bool spi_start_lld(SPIConfig* const spi_config, const bool lsb_first, const uint8_t spi_mode, const uint16_t clock_divisor) {
   if (!lsb_first) {
        osalDbgAssert(lsbFirst != FALSE, "LSB first SPI is unsupported by WB32");
    }

    if (clock_divisor < 1) {
        return false;
    }

    spi_config->SPI_BaudRatePrescaler = (clock_divisor << 2);

    switch (spi_mode) {
        case 0:
            spi_config->SPI_CPHA = SPI_CPHA_1Edge;
            spi_config->SPI_CPOL = SPI_CPOL_Low;
            break;
        case 1:
            spi_config->SPI_CPHA = SPI_CPHA_2Edge;
            spi_config->SPI_CPOL = SPI_CPOL_Low;
            break;
        case 2:
            spi_config->SPI_CPHA = SPI_CPHA_1Edge;
            spi_config->SPI_CPOL = SPI_CPOL_High;
            break;
        case 3:
            spi_config->SPI_CPHA = SPI_CPHA_2Edge;
            spi_config->SPI_CPOL = SPI_CPOL_High;
            break;
    }

    return true;
}
