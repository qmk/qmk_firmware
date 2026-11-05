// Copyright 2026 QuadState (@QuadState)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

// SW1..SW4: XIAO RP2040 pins D8, D9, D2, D1
#define EC_GPIO_PINS \
    { GP2, GP4, GP28, GP27 }

// Thresholds above each key's baseline, in 16 ns ticks (ecmacro4h.c).
// Measured on the 4H PCB, with a 680 kOhm resistor from each electrode to
// ground: a released key reads within about 10 ticks of its baseline, a
// pressed one 180 to 245 ticks above it.
#define EC_PRESS_TICKS 120
#define EC_RELEASE_TICKS 60
