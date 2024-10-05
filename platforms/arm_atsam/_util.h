// Copyright 2023 Nick Brassel (@tzarc)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

#define RESIDENT_IN_RAM(funcname) __attribute__((section(".ramfunc." #funcname), noinline)) funcname

#if __has_include_next("_util.h")
#    include_next "_util.h"
#endif
