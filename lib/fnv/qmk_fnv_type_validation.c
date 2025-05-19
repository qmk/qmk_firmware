// Copyright 2022 Nick Brassel (@tzarc)
// SPDX-License-Identifier: GPL-2.0-or-later
#include "fnv.h"
#include "compiler_support.h"

// This library was originally sourced from:
//     http://www.isthe.com/chongo/tech/comp/fnv/index.html
//
// Version at the time of retrieval on 2022-06-26: v5.0.3

STATIC_ASSERT(sizeof(long long) == 8, "long long should be 64 bits");
STATIC_ASSERT(sizeof(unsigned long long) == 8, "unsigned long long should be 64 bits");

STATIC_ASSERT(sizeof(Fnv32_t) == 4, "Fnv32_t should be 32 bits");
STATIC_ASSERT(sizeof(Fnv64_t) == 8, "Fnv64_t should be 64 bits");
