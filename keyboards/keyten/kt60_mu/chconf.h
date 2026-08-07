// Copyright 2024 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include_next <chconf.h>

#undef CH_CFG_ST_RESOLUTION 
#define CH_CFG_ST_RESOLUTION 16
