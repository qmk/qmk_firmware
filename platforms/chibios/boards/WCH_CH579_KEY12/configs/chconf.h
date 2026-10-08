/* Copyright 2024 QMK
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 */

#pragma once

/* CH579M uses ARM Cortex-M0 SysTick in periodic mode. */
#define CH_CFG_ST_TIMEDELTA 0

#include_next <chconf.h>
