// Copyright 2023 td2sk (@td2sk)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

#include <stdint.h>

void     XL9555_set_polarity(uint8_t port0, uint8_t port1);
uint16_t XL9555_read(void);
