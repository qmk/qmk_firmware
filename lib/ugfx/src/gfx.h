/*
 * This file is subject to the terms of the GFX License. If a copy of
 * the license was not distributed with this file, you can obtain one at:
 *
 *              http://ugfx.io/license.html
 */

/**
 * @file    gfx.h
 * @brief   GFX system header file.
 *
 * @addtogroup GFX
 *
 * @brief	Main module to glue all the others together
 *
 * @{
 */

#ifndef _GFX_H
#define _GFX_H

// Everything here is C, not C++
#ifdef __cplusplus
extern "C" {
#endif

// ------------------------------ Initial preparation ---------------------------------
#undef  GFX_COMPILESTAGE
#define GFX_COMPILESTAGE				GFX_COMPILESTAGE_PREP

// Compiling stages
#define GFX_COMPILESTAGE_USERPROGRAM		0		// Compiling the user program
#define GFX_COMPILESTAGE_PREP				1		// gfx.h: Initial preparation
#define GFX_COMPILESTAGE_USERCONFIG			2		// gfx.h: Load the user configuration
#define GFX_COMPILESTAGE_COMPILECONFIG		3		// gfx.h: Determine build environment info - COMPILER, CPU etc
#define GFX_COMPILESTAGE_OPTIONS			4		// gfx.h: Enumerate all options
#define GFX_COMPILESTAGE_RULES				5		// gfx.h: Apply configuration rules
#define GFX_COMPILESTAGE_APIDEFS			6		// gfx.h: Define API definitions
#define GFX_COMPILESTAGE_COMPILECAPI		100		// gfx.c: Compile the uGFX C API
#define GFX_COMPILESTAGE_COMPILEDRIVERINIT	101		// gfx.c: Compile driver init structures
#define GFX_COMPILESTAGE_COMPILECPPAPI		102		// gfx.cpp: Compile the uGFX C++ API

// ------------------------------ Load the user configuration ---------------------------------
#undef  GFX_COMPILESTAGE
#define GFX_COMPILESTAGE				GFX_COMPILESTAGE_USERCONFIG

// Definitions for option configuration
#define GFXOFF		(0)
#define GFXON		(-1)

// gfxconf.h is the user's project configuration for the GFX system.
#include "gfxconf.h"

// ------------------------------ Determine build environment info - COMPILER, CPU etc ---------------------------------
#undef  GFX_COMPILESTAGE
#define GFX_COMPILESTAGE				GFX_COMPILESTAGE_COMPILECONFIG

/**
 * @name    GFX compatibility options
 * @{
 */
	/**
	 * @brief   Include the uGFX V2.x API
	 * @details	Defaults to GFXON
	 */
	#ifndef GFX_COMPAT_V2
		#define GFX_COMPAT_V2				GFXON
	#endif
/** @} */

#if GFX_COMPAT_V2
	// These need to be defined here for compatibility with V2.x user config files
	#if !defined(FALSE)
		#define FALSE       0
	#endif
	#if !defined(TRUE)
		#define TRUE        -1
	#endif
#endif

// Are we in the uGFX library implementation itself? - not API documented
#ifndef GFX_COMPILE_INTERNAL_API
	#define GFX_COMPILE_INTERNAL_API		GFXOFF
#endif

// Macro concatination and strify - not API documented
#define GFXCAT(a, b)	a ## b
#define GFXCATX(a, b)	GFXCAT(a, b)
#define GFXSTR(a)		#a
#define GFXSTRX(a)		GFXSTR(a)

// Include Compiler and CPU support
#include "gfx_compilers.h"

// Include standard types
#include "gfx_types.h"

// Public uGFX API calling convention
#ifndef GFXAPI
	#define GFXAPI
#endif

// Public uGFX API callback convention
#ifndef GFXUSERFN
	#define GFXUSERFN		GFXAPI
#endif

// Private uGFX API calling convention
#if GFX_COMPILE_INTERNAL_API && !defined(GFXINTERNAL)
	#define GFXINTERNAL
#endif

// ------------------------------ Enumerate all options ---------------------------------
#undef  GFX_COMPILESTAGE
#define GFX_COMPILESTAGE				GFX_COMPILESTAGE_OPTIONS

/**
 * Get all the options for each sub-system.
 */
#include "gfx_options.h"
#include "gos/gos_options.h"
#include "gdriver/gdriver_options.h"
#include "gfile/gfile_options.h"
#include "gmisc/gmisc_options.h"
#include "gtrans/gtrans_options.h"
#include "gqueue/gqueue_options.h"
#include "gevent/gevent_options.h"
#include "gtimer/gtimer_options.h"
#include "gdisp/gdisp_options.h"
#include "gwin/gwin_options.h"
#include "ginput/ginput_options.h"
#include "gadc/gadc_options.h"
#include "gaudio/gaudio_options.h"

// ------------------------------ Apply configuration rules ---------------------------------
#undef  GFX_COMPILESTAGE
#define GFX_COMPILESTAGE				GFX_COMPILESTAGE_RULES

/**
 * Interdependency safety checks on the sub-systems.
 * These must be in dependency order.
 */
#ifndef GFX_DISPLAY_RULE_WARNINGS
	#define GFX_DISPLAY_RULE_WARNINGS	GFXOFF
#endif
#include "gwin/gwin_rules.h"
#include "ginput/ginput_rules.h"
#include "gdisp/gdisp_rules.h"
#include "gaudio/gaudio_rules.h"
#include "gadc/gadc_rules.h"
#include "gevent/gevent_rules.h"
#include "gtimer/gtimer_rules.h"
#include "gqueue/gqueue_rules.h"
#include "gmisc/gmisc_rules.h"
#include "gtrans/gtrans_rules.h"
#include "gfile/gfile_rules.h"
#include "gdriver/gdriver_rules.h"
#include "gos/gos_rules.h"

// ------------------------------ Define API definitions ---------------------------------
#undef  GFX_COMPILESTAGE
#define GFX_COMPILESTAGE				GFX_COMPILESTAGE_APIDEFS

/**
 *  Include the sub-system header files
 */
#include "gos/gos.h"
#if GFX_COMPILE_INTERNAL_API
	#include "gdriver/gdriver.h"
#endif
#include "gfile/gfile.h"
#include "gmisc/gmisc.h"
#include "gtrans/gtrans.h"
#include "gqueue/gqueue.h"
#include "gevent/gevent.h"
#include "gtimer/gtimer.h"
#include "gdisp/gdisp.h"
#include "gwin/gwin.h"
#include "ginput/ginput.h"
#include "gadc/gadc.h"
#include "gaudio/gaudio.h"

/**
 * @brief	The one call to start it all
 *
 * @note	This will initialise each sub-system that has been turned on.
 * 			For example, if GFX_USE_GDISP is defined then display will be initialised
 * 			and cleared to black.
 * @note	If you define GFX_OS_NO_INIT as GFXON in your gfxconf.h file then ugfx doesn't try to
 * 			initialise the operating system for you when you call @p gfxInit().
 * @note	If you define GFX_OS_EXTRA_INIT_FUNCTION in your gfxconf.h file the macro is the
 * 			name of a void function with no parameters that is called immediately after
 * 			operating system initialisation (whether or not GFX_OS_NO_INIT is set).
 * @note	If you define GFX_OS_EXTRA_DEINIT_FUNCTION in your gfxconf.h file the macro is the
 * 			name of a void function with no parameters that is called immediately before
 * 			operating system de-initialisation (as ugfx is exiting).
 * @note	If GFX_OS_CALL_UGFXMAIN is set uGFXMain() is called after all initialisation is complete.
 *
 * @api
 */
void GFXAPI gfxInit(void);

/**
 * @brief	The one call to end it all
 *
 * @note	This will de-initialise each sub-system that has been turned on.
 *
 * @api
 */
void GFXAPI gfxDeinit(void);

#if GFX_OS_CALL_UGFXMAIN || defined(__DOXYGEN__)
	/**
	 * @brief	The user supplied function containing all the user uGFX application code.
	 *
	 * @note	This is called by gfxInit() and is expected to never return.
	 * 			It is defined by the user.
	 *
	 * @pre		GFX_OS_CALL_UGFXMAIN is GFXON
	 */
	void GFXUSERFN uGFXMain(void);
#endif

// ------------------------------ Compiling the user program ---------------------------------
#undef  GFX_COMPILESTAGE
#define GFX_COMPILESTAGE				GFX_COMPILESTAGE_USERPROGRAM

#ifdef __cplusplus
}
#endif
#endif /* _GFX_H */
/** @} */
