// Copyright 2026 Mauro DiBenedetto
// Copyright 2026 Antonio SJ Musumeci (@trapexit)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

#define CH_CFG_ST_FREQUENCY 1000
#define CH_CFG_ST_TIMEDELTA 0
#define CH_CFG_TIME_QUANTUM 20

#include_next <chconf.h>

#include "tex_hw.h"

// The stock firmware arms the watchdog; feed it every tick, and fall back to the
// TEX bootloader if ChibiOS halts.
#undef CH_CFG_SYSTEM_TICK_HOOK
#define CH_CFG_SYSTEM_TICK_HOOK() \
    {                             \
        TEX_WDT_RELOAD();         \
    }
#undef CH_CFG_SYSTEM_HALT_HOOK
#define CH_CFG_SYSTEM_HALT_HOOK(reason) \
    {                                   \
        (void)(reason);                 \
        TEX_ENTER_IAP();                \
    }
