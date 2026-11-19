// Copyright 2024 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "serial.h"
#include <hal.h>

#if !defined(FDCAN_RX_PIN)
#    error FDCAN_RX_PIN not set
#endif

#if !defined(FDCAN_TX_PIN)
#    error FDCAN_TX_PIN not set
#endif

#if HAL_USE_CAN

typedef CANDriver QMKCANDriver;
typedef CANConfig QMKCANConfig;

#endif

#if !defined(USE_GPIOV1)
/* The default PAL alternate modes are used to signal that the pins are used for USART. */
#    if !defined(FDCAN_RX_PAL_MODE)
#        define FDCAN_RX_PAL_MODE 9
#    endif
#    if !defined(FDCAN_TX_PAL_MODE)
#        define FDCAN_TX_PAL_MODE 9
#    endif
#endif

#if !defined(FDCAN_NBTP)
#    define FDCAN_NBTP 0x06000A03 // use default value from stm32g4 reference manual
#endif

#if !defined(FDCAN_DBTP)
#    define FDCAN_DBTP 0x00000A33 // use default value from stm32g4 reference manual
#endif
