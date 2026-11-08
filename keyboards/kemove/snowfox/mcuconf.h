// Copyright 2026 Michael Loukeris (@milouk)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include_next <mcuconf.h>

/* SPI to the two LED drivers */
#undef LPC_SPI_USE_SPI1
#define LPC_SPI_USE_SPI1 TRUE

/* UART to the Bluetooth module */
#undef LPC_SERIAL_USE_UART1
#define LPC_SERIAL_USE_UART1 TRUE
