/*
 * This file is subject to the terms of the GFX License. If a copy of
 * the license was not distributed with this file, you can obtain one at:
 *
 *              http://ugfx.io/license.html
 */

#include "../../gfx.h"

#if GFX_USE_OS_ARDUINO

#include <string.h>				// Prototype for memcpy()

void _gosHeapInit(void);
void _gosThreadsInit(void);

/*********************************************************
 * Initialise
 *********************************************************/

void _gosInit(void)
{
	/* No initialization of the operating system itself is needed as there isn't one.
	 * On the other hand the C runtime should still already be initialized before
	 * getting here!
	 */
	#if !GFX_OS_INIT_NO_WARNING
		#if GFX_COMPILER_WARNING_TYPE == GFX_COMPILER_WARNING_DIRECT
			#warning "GOS: Arduino - Make sure you initialize your hardware and the C runtime before calling gfxInit() in your application!"
		#elif GFX_COMPILER_WARNING_TYPE == GFX_COMPILER_WARNING_MACRO
			COMPILER_WARNING("GOS: Arduino - Make sure you initialize your hardware and the C runtime before calling gfxInit() in your application!")
		#endif
	#endif

	// Start the heap allocator
	_gosHeapInit();

	// Start the scheduler
	_gosThreadsInit();
}

void _gosPostInit(void)
{
}

void _gosDeinit(void)
{
	/* ToDo */
}

/*********************************************************
 * Exit everything functions
 *********************************************************/

void gfxHalt(const char *msg) {
	volatile gU32	dummy;
	(void)				msg;

	while(1)
		dummy++;
}

void gfxExit(void) {
	volatile gU32	dummy;

	while(1)
		dummy++;
}


/*********************************************************
 * Sleep functions
 *********************************************************/

gTicks gfxSystemTicks(void) {
	return millis();
}
gTicks gfxMillisecondsToTicks(gDelay ms) {
	return ms;
}

#endif /* GFX_USE_OS_ARDUINO */
