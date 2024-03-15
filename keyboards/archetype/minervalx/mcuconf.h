// Copyright 2023 Leon Anavi (@leon-anavi)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include_next <mcuconf.h>

#undef RP_PWM_USE_PWM5
#define RP_PWM_USE_PWM5 TRUE
