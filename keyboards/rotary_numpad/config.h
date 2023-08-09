// Copyright 2023 rabijl (@rabijl)
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

// it seems that declaring encoder pins in info.json 
// is not working exactly and compilation fails when
// this macro is not set. But it will warn that the
// encoders have been declared twice ¯\_(ツ)_/¯
#define ENCODERS_PAD_A { D1, D4, D7}
#define ENCODERS_PAD_B { D0, C6, E6}
