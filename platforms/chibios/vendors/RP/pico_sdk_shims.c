// Copyright 2022 Stefan Kerkmann
// SPDX-License-Identifier: GPL-2.0-or-later

#include <stdbool.h>
#include <ch.h>

void panic(const char *fmt, ...) {
    chSysHalt(fmt);
}
