/* Copyright 2024 QMK
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 */

#pragma once

/*
 * CH579M MCU configuration.
 * Overrides defaults in the CH579 HAL driver headers.
 */

#define CH579M_MCUCONF TRUE

/*
 * Clock — HSI 32 MHz (CK32M) direct as HCLK; PLL on for USB 48 MHz.
 * hal_lld_init() powers on the PLL (USB peripheral derives Fpll/10=48 MHz
 * independently) and switches HCLK to CK32M direct mode (CLK_SYS_MOD=10).
 * Datasheet Fsys spec: 32 MHz direct is within the valid range.
 */
#define CH579_HSECLK 0          /* No external crystal */
#define CH579_SYSCLK 32000000UL /* CK32M direct (32 MHz HCLK) */

/*
 * IRQ priorities (0 = highest on CM0, 3 = lowest).
 */
#define CH579_ST_IRQ_PRIORITY 2
#define CH579_USB_IRQ_PRIORITY 1
