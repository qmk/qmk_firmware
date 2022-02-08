// Copyright 2022 Nick Brassel (@tzarc)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

#ifndef EEPROM_SIZE
#    include "eeconfig.h"
#    define EEPROM_SIZE (((EECONFIG_SIZE + 3) / 4) * 4)  // based off eeconfig's current usage, aligned to 4-byte sizes, to deal with LTO
#endif
