// Copyright 2025 QMK
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

#if defined(WEAR_LEVELING_EMBEDDED_FLASH)
#    include "wear_leveling/wear_leveling_efl_config.h"
#elif defined(WEAR_LEVELING_SPI_FLASH)
#    include "wear_leveling/wear_leveling_flash_spi_config.h"
#elif defined(WEAR_LEVELING_RP2040_FLASH)
#    include "wear_leveling/wear_leveling_rp2040_flash_config.h"
#elif defined(WEAR_LEVELING_LEGACY)
#    include "wear_leveling/wear_leveling_legacy_config.h"
#endif
