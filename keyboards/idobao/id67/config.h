// Copyright 2021 Tybera (@tybera)
// Copyright 2021 Werther (@thewerther)
// Copyright 2022 Vino Rodrigues (@vinorodrigues)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#if defined(RGB_MATRIX_ENABLE)
    #ifndef ID67_DISABLE_UNDERGLOW
        #define RGB_MATRIX_LED_COUNT 77
    #else
        #define RGB_MATRIX_LED_COUNT (77 - 10)
    #endif
#endif  // RGB_MATRIX_ENABLE

/* -----------------------
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 * ----------------------- */

/* disable debug print */
// #define NO_DEBUG

/* disable print */
// #define NO_PRINT

/* disable action features */
// #define NO_ACTION_LAYER
// #define NO_ACTION_TAPPING
// #define NO_ACTION_ONESHOT
