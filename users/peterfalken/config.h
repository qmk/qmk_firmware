// Copyright 2023 Peter.Falken (@PeterFalken)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

// Fix warning - "Attached USB accessory uses too much power."
#ifndef USB_MAX_POWER_CONSUMPTION
    #define USB_MAX_POWER_CONSUMPTION 100
#endif

// Fix unresponsiveness on wake from sleep
#ifndef USB_SUSPEND_WAKEUP_DELAY
    #define USB_SUSPEND_WAKEUP_DELAY 200
#endif

// Space optimizations
#define LAYER_STATE_8BIT
#undef LOCKING_SUPPORT_ENABLE
#undef LOCKING_RESYNC_ENABLE

// Disable animations for RGB underglow & key matrix
#define DISABLE_RGB_LIGHT_ANIMATIONS
#define DISABLE_RGB_MATRIX_ANIMATIONS
