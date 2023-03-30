// ----------------------------------------------------------------------------
// Second stage boot code
// Copyright (c) 2019-2021 Raspberry Pi (Trading) Ltd.
// SPDX-License-Identifier: BSD-3-Clause
// ----------------------------------------------------------------------------
//
// This implementation uses the PICO_BOOT_STAGE2_CHOOSE_ preprocessor defines to pick
// amongst a menu of known boot stage 2 implementations, allowing the board
// configuration header to be able to specify the boot stage 2

#include "boot_stage2/config.h"

#ifdef PICO_BUILD_BOOT_STAGE2_NAME
    // boot stage 2 is configured by cmake, so use the name specified there
    #error PICO_BUILD_BOOT_STAGE2_NAME should not be defined for compile_time_choice builds
#else
    // boot stage 2 is selected by board config header, and PICO_BOOT_STAGE2_ASM is set in boot_stage2/config.h
    #include PICO_BOOT_STAGE2_ASM
#endif
