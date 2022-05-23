// Copyright 2022 Stefan Kerkmann (KarlK90)
// SPDX-License-Identifier: GPL-2.0-or-later

#include <hal.h>

inline bool spi_start_lld(SPIConfig* const spi_config, const bool lsb_first, const uint8_t spi_mode, const uint16_t clock_divisor) {
    int32_t rounded_clock_divisor = round_clock_divisor(clock_divisor);

    if (rounded_clock_divisor < 0) {
        return false;
    }

    spi_config->tar0 = SPIx_CTARn_FMSZ(7) | SPIx_CTARn_ASC(1);

    if (lsb_first) {
        spi_config->tar0 |= SPIx_CTARn_LSBFE;
    }

    switch (spi_mode) {
        case 0:
            break;
        case 1:
            spi_config->tar0 |= SPIx_CTARn_CPHA;
            break;
        case 2:
            spi_config->tar0 |= SPIx_CTARn_CPOL;
            break;
        case 3:
            spi_config->tar0 |= SPIx_CTARn_CPHA | SPIx_CTARn_CPOL;
            break;
    }

    switch (rounded_clock_divisor) {
        case 2:
            spi_config->tar0 |= SPIx_CTARn_BR(0);
            break;
        case 4:
            spi_config->tar0 |= SPIx_CTARn_BR(1);
            break;
        case 8:
            spi_config->tar0 |= SPIx_CTARn_BR(3);
            break;
        case 16:
            spi_config->tar0 |= SPIx_CTARn_BR(4);
            break;
        case 32:
            spi_config->tar0 |= SPIx_CTARn_BR(5);
            break;
        case 64:
            spi_config->tar0 |= SPIx_CTARn_BR(6);
            break;
        case 128:
            spi_config->tar0 |= SPIx_CTARn_BR(7);
            break;
        case 256:
            spi_config->tar0 |= SPIx_CTARn_BR(8);
            break;
    }

    return true;
}
