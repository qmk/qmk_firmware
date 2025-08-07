// Copyright 2022 dvermd (@dvermd)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#if !(defined(USE_SDI1_ON_STANDARD_ROLE_PINS) || defined(USE_SDI1_ON_ALTERNATE_ROLE_PINS) || defined(USE_SDI2))
    #define USE_SDI1_ON_STANDARD_ROLE_PINS
#endif
