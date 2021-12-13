// Copyright 2021 Nicolas Druoton (druotoni)
// SPDX-License-Identifier: GPL-2.0-or-later
#include "fast_random.h"

// seed for random
static unsigned long g_seed = 0;

int fastrand(void) {
    // todo : try with random16();
    g_seed = (214013 * g_seed + 2531011);
    return (g_seed >> 16) & 0x7FFF;
}

unsigned long fastrand_long(void) {
    g_seed = (214013 * g_seed + 2531011);
    return g_seed;
}
