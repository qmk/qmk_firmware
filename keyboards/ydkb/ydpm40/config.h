// Copyright 2022 anb (@anb)
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

#define USB_CFG_IOPORTNAME      D
#define USB_CFG_DMINUS_BIT      2
#define USB_CFG_DPLUS_BIT       3
#define USB_COUNT_SOF           0
