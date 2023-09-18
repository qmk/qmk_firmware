// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later
#include "sendchar.h"
int8_t console_write(uint8_t c);

int8_t sendchar(uint8_t c) {
    return console_write(c);
}
