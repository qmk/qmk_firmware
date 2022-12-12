// Copyright 2022 PeterFalken  (@PeterFalken)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "config_common.h"

// Fix warning - "Attached USB accessory uses too much power."
#ifndef USB_MAX_POWER_CONSUMPTION
    #define USB_MAX_POWER_CONSUMPTION 100
#endif

// Fix unresponsive on wake from sleep
#ifndef USB_SUSPEND_WAKEUP_DELAY
    #define USB_SUSPEND_WAKEUP_DELAY 200
#endif
