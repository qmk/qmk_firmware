/*
 * This file is subject to the terms of the GFX License. If a copy of
 * the license was not distributed with this file, you can obtain one at:
 *
 *              http://ugfx.io/license.html
 */

/**
 * @file    src/gos/gos_rtx5.h
 * @brief   GOS - Operating System Support header file for Keil RTX
 */

#ifndef _GOS_RTX5_H
#define _GOS_RTX5_H

#if GFX_USE_OS_RTX5

/*
 * Keil RTX uses the CMSIS RTOS interface. Therefore, just use the CMSIS2 RTOS port
 */

// Disable KEIL to avoid error: "GOS: More than one operation system has been defined as GFXON."
#undef GFX_USE_OS_RTX5
#define GFX_USE_OS_RTX5 GFXOFF

// Enable generic CMSIS RTOS implementation
#undef GFX_USE_OS_CMSIS2
#define GFX_USE_OS_CMSIS2 GFXON
#include "gos_cmsis2.h"

#endif /* GFX_USE_OS_RTX5 */
#endif /* _GOS_RTX5_H */
