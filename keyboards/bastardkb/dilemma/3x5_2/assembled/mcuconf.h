// Copyright 2022 Charly Delay <charly@codesink.dev> (@0xcharly)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

#include_next <mcuconf.h>

#undef RP_SPI_USE_SPI0
#define RP_SPI_USE_SPI0 TRUE
