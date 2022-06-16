/*
 * This file is subject to the terms of the GFX License. If a copy of
 * the license was not distributed with this file, you can obtain one at:
 *
 *              http://ugfx.io/license.html
 */

// We need to include stdio.h below for Win32 emulation. Turn off GFILE_NEED_STDIO just for this file to prevent conflicts
#define GFILE_NEED_STDIO_MUST_BE_OFF

#include "../../gfx.h"

#if GFX_USE_OS_RAW32

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
			#warning "GOS: Raw32 - Make sure you initialize your hardware and the C runtime before calling gfxInit() in your application!"
		#elif GFX_COMPILER_WARNING_TYPE == GFX_COMPILER_WARNING_MACRO
			COMPILER_WARNING("GOS: Raw32 - Make sure you initialize your hardware and the C runtime before calling gfxInit() in your application!")
		#endif
	#endif

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
	/* ToDo */
}

/*********************************************************
 * For Win32 emulation - automatically add the tick functions
 * the user would normally have to provide for bare metal.
 *********************************************************/

#if defined(WIN32)
	// Win32 nasty stuff - we have conflicting definitions for Red, Green & Blue
	#ifndef _WIN32_WINNT
		#define _WIN32_WINNT 0x0501			// Windows XP and up
	#endif
	#if GFX_COMPAT_V2 && GFX_COMPAT_OLDCOLORS
		#undef Red
		#undef Green
		#undef Blue
	#endif
	#define WIN32_LEAN_AND_MEAN
	#include <windows.h>
	#undef WIN32_LEAN_AND_MEAN
	#if GFX_COMPAT_V2 && GFX_COMPAT_OLDCOLORS
		#define Red			GFX_RED
		#define Green		GFX_GREEN
		#define Blue		GFX_BLUE
	#endif

	#include <stdio.h>
	gTicks gfxSystemTicks(void)						{ return GetTickCount(); }
	gTicks gfxMillisecondsToTicks(gDelay ms)	{ return ms; }
#endif

/*********************************************************
 * Exit everything functions
 *********************************************************/

void gfxHalt(const char *msg) {
	#if defined(WIN32)
		fprintf(stderr, "%s\n", msg);
		ExitProcess(1);
	#else
		volatile gU32	dummy;
		(void)				msg;

		while(1)
			dummy++;
	#endif
}

void gfxExit(void) {
	#if defined(WIN32)
		ExitProcess(0);
	#else
		volatile gU32	dummy;

		while(1)
			dummy++;
	#endif
}

#endif /* GFX_USE_OS_RAW32 */
