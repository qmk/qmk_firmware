// Copyright 2026
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"

/* No addressable LEDs are fitted on this PCB: the stock firmware carries a
 * WS2812 bitbang driver on PB9 (ws2812_setleds at 0x08005456) but nothing in
 * the image ever calls it, so RGBLIGHT is left disabled here. */
