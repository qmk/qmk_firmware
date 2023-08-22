// Copyright 2023 Nick Brassel (@tzarc)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

#define RESIDENT_IN_RAM(funcname) __attribute__((section(".ram0_init." #funcname), noinline)) funcname

#ifndef CORTEX_ENABLE_WFI_IDLE
#    define CORTEX_ENABLE_WFI_IDLE TRUE
#endif // CORTEX_ENABLE_WFI_IDLE
