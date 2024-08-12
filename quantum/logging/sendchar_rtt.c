// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include "sendchar.h"
#include "SEGGER_RTT.h"

int8_t sendchar(uint8_t c) {
    return SEGGER_RTT_PutChar(0, (char)c);
}
