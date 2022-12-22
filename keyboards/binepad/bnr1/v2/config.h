// Copyright 2022 BINEPAD (@binepad)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "config_common.h"

#define WEAR_LEVELING_LOGICAL_SIZE 1024
#define WEAR_LEVELING_BACKING_SIZE (WEAR_LEVELING_LOGICAL_SIZE * 2)

#ifdef VIA_ENABLE
    #define VIA_FIRMWARE_VERSION 0
#endif
