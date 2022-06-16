/*
 * Copyright (c) 2012, 2013, Joel Bodenmann aka Tectu <joel@unormal.org>
 * Copyright (c) 2012, 2013, Andrew Hannam aka inmarket
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *    * Redistributions of source code must retain the above copyright
 *      notice, this list of conditions and the following disclaimer.
 *    * Redistributions in binary form must reproduce the above copyright
 *      notice, this list of conditions and the following disclaimer in the
 *      documentation and/or other materials provided with the distribution.
 *    * Neither the name of the <organization> nor the
 *      names of its contributors may be used to endorse or promote products
 *      derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef _GFXCONF_H
#define _GFXCONF_H

//* The operating system to use. One of these must be defined - preferably in your Makefile */
//#define GFX_USE_OS_CHIBIOS	GFXOFF
//#define GFX_USE_OS_WIN32		GFXOFF
//#define GFX_USE_OS_LINUX		GFXOFF
//#define GFX_USE_OS_OSX		GFXOFF

/* GFX sub-systems to turn on */
#define GFX_USE_GDISP			GFXON

/* Features for the GDISP sub-system. */
#define GDISP_NEED_VALIDATION	GFXON
#define GDISP_NEED_CLIP			GFXON
#define GDISP_NEED_TEXT			GFXON

#define GDISP_INCLUDE_FONT_UI2	GFXON

/* You must either define GDISP_TOTAL_DISPLAYS or GDISP_DRIVER_LIST for multiple displays.
 * You cannot define both!
 *
 * Defining GDISP_TOTAL_DISPLAYS will create multiple instances of the one default driver.
 * Defining GDISP_DRIVER_LIST allows you to specify multiple different drivers.
 *
 * Extra Notes for GDISP_DRIVER_LIST:
 *-----------------------------------
 *
 * The same controller can appear more than once in the list.
 *
 * You must specify a GDISP_PIXELFORMAT that the application will work in. This
 *   is translated into each drivers internal pixel format by the driver. You the
 *   pixel format that is most common across your drivers (for efficiency).
 *
 * Optionally, you can also specify hardware characteristics that are common to
 * all your controllers. This significantly improves code and speed efficiency
 * as the program doesn't have to detect the hardware method to use on each call.
 *
 * Hardware definitions can be set to:
 * 		- GFXON		- all controllers support this routine
 * 		- GFXOFF	- no controllers support this routine
 * 		- if not specified then the code auto-detects the hardware.
 *
 * e.g
 * 		#define GDISP_HARDWARE_STREAM_WRITE	GFXOFF
 * 		#define GDISP_HARDWARE_STREAM_READ	GFXOFF
 * 		#define GDISP_HARDWARE_DRAWPIXEL	GFXON
 * 		#define GDISP_HARDWARE_FILLS		GFXON
 */
#if GFX_USE_OS_WIN32 || GFX_USE_OS_LINUX || GFX_USE_OS_OSX
	// Emulator
	#define GDISP_TOTAL_DISPLAYS    2

	//#define GDISP_DRIVER_LIST     GDISPVMT_Win32, GDISPVMT_Win32
	//#define GDISP_PIXELFORMAT     GDISP_PIXELFORMAT_RGB888

#elif !defined(GDISP_TOTAL_DISPLAYS) && (!defined(GDISP_PIXELFORMAT) || !defined(GDISP_DRIVER_LIST))
	#error "gfxconf.h: You have not defined multiple displays properly. Try defining GDISP_TOTAL_DISPLAYS or, GDISP_PIXELFORMAT and GDISP_DRIVER_LIST in your makefile"
#endif

/*
 * The following are needed only for the sprintg() call
 */
#define GFX_USE_GFILE						GFXON
#define GFILE_NEED_PRINTG					GFXON
#define GFILE_NEED_STRINGS					GFXON

#endif /* _GFXCONF_H */
