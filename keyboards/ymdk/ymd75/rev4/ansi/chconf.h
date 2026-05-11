// Copyright 2020 QMK
// Copyright 2026 Steffen Olszewski (@sodevel)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

#define CH_CFG_ST_TIMEDELTA 10000

#define CH_CFG_USE_REGISTRY TRUE

#define CH_CFG_USE_WAITEXIT TRUE

#define CH_CFG_USE_CONDVARS TRUE

#define CH_CFG_USE_CONDVARS_TIMEOUT FALSE

#define CH_CFG_USE_MESSAGES TRUE

#define CH_CFG_USE_MAILBOXES TRUE

#define CH_CFG_USE_HEAP TRUE

#include_next <chconf.h>
