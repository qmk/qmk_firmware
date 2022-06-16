/*
 * This file is subject to the terms of the GFX License. If a copy of
 * the license was not distributed with this file, you can obtain one at:
 *
 *              http://ugfx.io/license.html
 */

#include "../../gfx.h"

#if GFX_USE_OS_NIOS

void _gosHeapInit(void);
void _gosThreadsInit(void);

/*********************************************************
 * Initialise
 *********************************************************/

void _gosInit(void)
{
	// Set up the heap allocator
	_gosHeapInit();

	// Start the scheduler
	_gosThreadsInit();
}

void _gosPostInit(void)
{
}

void _gosDeinit(void)
{
}

void gfxHalt(const char *msg)
{
	volatile gU32 dummy;

	(void)msg;

	while(1) {
		dummy++;
	}
}

void gfxExit(void) {
	volatile gU32 dummy;

	while(1) {
		dummy++;
	}
}

gTicks gfxSystemTicks(void)
{
	return alt_nticks();
}

gTicks gfxMillisecondsToTicks(gDelay ms)
{
	return ms;
}

#endif /* GFX_USE_OS_NIOS */
