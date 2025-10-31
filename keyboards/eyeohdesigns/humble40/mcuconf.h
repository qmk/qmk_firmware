// Copyright 2023 The QMK Community (@qmk)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include_next <mcuconf.h>

#undef RP_PWM_USE_PWM6
#define RP_PWM_USE_PWM6 TRUE
