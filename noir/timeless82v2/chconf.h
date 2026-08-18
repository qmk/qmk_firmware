// Copyright 2024 Su (@isuua)
// SPDX-License-Identifier: GPL-2.0-or-later

#include_next <chconf.h>

#undef CH_CFG_ST_TIMEDELTA
#define CH_CFG_ST_TIMEDELTA 2

#undef CH_CFG_ST_RESOLUTION
#define CH_CFG_ST_RESOLUTION 16
