// Copyright 2026 doombadroid (@doombadroid)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define NUC126_MCUCONF

/* Crystal-less board (PF3/PF4 are LED GPIO): HCLK + USB from HIRC48, trimmed to USB SOF at runtime. */
#define NUC126_HSI_ENABLED TRUE
#define NUC126_HSI48_ENABLED TRUE
#define NUC126_HSE_ENABLED FALSE
#define NUC126_LSE_ENABLED FALSE
#define NUC126_PLL_ENABLED FALSE

/* Never touch CONFIG0/1: they hold the LDROM boot select that makes D+L recovery work. */
#define NUC126_CONFIG_ENABLED FALSE

#define NUC126_USB_USE_USB1 TRUE
#define NUC126_USB_IRQ_PRIORITY 2
