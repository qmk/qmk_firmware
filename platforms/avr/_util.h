// Copyright 2023 Nick Brassel (@tzarc)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

// AVR can't actually run anything from RAM, so just no-op the define.
#define RESIDENT_IN_RAM(funcname) funcname

#if __has_include_next("_util.h")
#    include_next "_util.h"
#endif
