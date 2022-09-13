// Copyright 2022 Stefan Kerkmann
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define CH_CFG_SMP_MODE                     TRUE
#define CH_CFG_ST_RESOLUTION                32
#define CH_CFG_ST_FREQUENCY                 10000
#define CH_CFG_INTERVALS_SIZE               32
#define CH_CFG_TIME_TYPES_SIZE              32
#define CH_CFG_ST_TIMEDELTA                 0

/* Workaround a bug in chibios where port_timer_enable is not defined for RP2040 in tick mode */
#if !defined(_FROM_ASM_)
void stBind(void);
#define port_timer_enable(oip) stBind()
#endif

#include_next <chconf.h>
