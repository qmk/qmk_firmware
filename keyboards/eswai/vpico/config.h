// Copyright 2023 eswai (@eswai)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

/* disable debug print */
//#define NO_DEBUG

/* disable print */
//#define NO_PRINT

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT

// LinuxでのUNICODE入力のために必要な設定
#define USB_POLLING_INTERVAL_MS 8
#define TAP_CODE_DELAY 24