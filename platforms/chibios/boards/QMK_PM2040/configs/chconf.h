// Copyright 2022 Stefan Kerkmann
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define CH_CFG_SMP_MODE                     TRUE
#define CH_CFG_ST_RESOLUTION                32
#define CH_CFG_ST_FREQUENCY                 1000000
#define CH_CFG_INTERVALS_SIZE               32
#define CH_CFG_TIME_TYPES_SIZE              32
#define CH_CFG_ST_TIMEDELTA                 20

#include_next <chconf.h>
