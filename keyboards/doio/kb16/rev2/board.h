// Copyright 2026 Isaac Larson
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

#include_next <board.h>

/*
 * Leave PA11 (USB D-) and PA12 (USB D+) as floating inputs.
 * The shared STM32duino board enables the internal pull-up on them, and the
 * pull-up on D- stays on once USB starts. That makes Apple-silicon Macs fail
 * to enumerate the board when it is plugged directly into a built-in USB-C
 * port (it still works through a hub).
 */
#undef VAL_GPIOACRH
#define VAL_GPIOACRH 0x888444B8 /* PA15...PA8 */
