// Copyright 2022 dvermd (@dvermd)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "config_common.h"

#if defined(BLUEPILL)
    #define SOFT_SERIAL_PIN B6
#else
    #error "splittest bitbang keymap not implemented for this MCU yet"
#endif
