/*
 * This file is subject to the terms of the GFX License. If a copy of
 * the license was not distributed with this file, you can obtain one at:
 *
 *              http://ugfx.io/license.html
 */

#ifndef _GOS_NIOS_H
#define _GOS_NIOS_H

#if GFX_USE_OS_NIOS

#include <sys/alt_alarm.h>

typedef alt_u32 gTicks;
typedef alt_u32 gDelay;

void gfxHalt(const char* msg);
void gfxExit(void);
gTicks gfxSystemTicks(void);
gTicks gfxMillisecondsToTicks(gDelay ms);

// Use the generic thread handling and heap handling
#define GOS_NEED_X_THREADS	GFXON
#define GOS_NEED_X_HEAP		GFXON

#include "gos_x_threads.h"
#include "gos_x_heap.h"

#endif /* GFX_USE_OS_NIOS */
#endif /* _GOS_NIOS_H */
