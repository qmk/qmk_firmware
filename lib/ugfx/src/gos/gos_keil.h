/*
 * This file is subject to the terms of the GFX License. If a copy of
 * the license was not distributed with this file, you can obtain one at:
 *
 *              http://ugfx.io/license.html
 */

/**
 * @file    src/gos/gos_keil.h
 * @brief   GOS - Operating System Support header file for Keil RTX
 */

#ifndef _GOS_KEIL_H
#define _GOS_KEIL_H

#if GFX_USE_OS_KEIL

/*
 * Keil RTX uses the CMSIS RTOS interface. Therefore, just use the CMSIS RTOS port
 */

// Disable KEIL to avoid error: "GOS: More than one operation system has been defined as GFXON."
#undef GFX_USE_OS_KEIL
#define GFX_USE_OS_KEIL GFXOFF

// Enable generic CMSIS RTOS implementation
#undef GFX_USE_OS_CMSIS
#define GFX_USE_OS_CMSIS GFXON
#include "gos_cmsis.h"

#endif /* GFX_USE_OS_KEIL */
#endif /* _GOS_KEIL_H */
