// Copyright 2024-2025 QMK
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include_next <mcuconf.h>

#undef RP_SIO_USE_USART1
#define RP_SIO_USE_USART1 TRUE
