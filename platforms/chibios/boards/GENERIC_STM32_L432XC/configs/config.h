// Copyright 2021 Nick Brassel (@tzarc)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

// Fixup equivalent usages within QMK as the base board definitions only go up to high
#define PAL_STM32_OSPEED_HIGHEST PAL_STM32_OSPEED_HIGH

#ifndef EARLY_INIT_PERFORM_BOOTLOADER_JUMP
#    define EARLY_INIT_PERFORM_BOOTLOADER_JUMP TRUE
#endif
