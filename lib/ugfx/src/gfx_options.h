/*
 * This file is subject to the terms of the GFX License. If a copy of
 * the license was not distributed with this file, you can obtain one at:
 *
 *              http://ugfx.io/license.html
 */

/**
 * @file    gfx_options.h
 * @brief   GFX system options.
 *
 * @addtogroup GFX
 * @{
 */

/**
 * @name    GFX sub-systems that can be turned on
 * @{
 */
	/**
	 * @brief   GFX Driver API
	 * @details	Defaults to GFXON
	 * @note	Not much useful can be done without a driver
	 */
	#ifndef GFX_USE_GDRIVER
		#define GFX_USE_GDRIVER	GFXON
	#endif
	/**
	 * @brief   GFX Graphics Display Basic API
	 * @details	Defaults to GFXOFF
	 * @note	Also add the specific hardware driver to your makefile.
	 * 			Eg.  include $(GFXLIB)/drivers/gdisp/Nokia6610/driver.mk
	 */
	#ifndef GFX_USE_GDISP
		#define GFX_USE_GDISP	GFXOFF
	#endif
	/**
	 * @brief   GFX Graphics Windowing API
	 * @details	Defaults to GFXOFF
	 * @details	Extends the GDISP API to add the concept of graphic windows.
	 * @note	Also supports high-level "window" objects such as console windows,
	 * 			buttons, graphing etc
	 */
	#ifndef GFX_USE_GWIN
		#define GFX_USE_GWIN	GFXOFF
	#endif
	/**
	 * @brief   GFX Event API
	 * @details	Defaults to GFXOFF
	 * @details	Defines the concept of a "Source" that can send "Events" to "Listeners".
	 */
	#ifndef GFX_USE_GEVENT
		#define GFX_USE_GEVENT	GFXOFF
	#endif
	/**
	 * @brief   GFX Timer API
	 * @details	Defaults to GFXOFF
	 * @details	Provides thread context timers - both one-shot and periodic.
	 */
	#ifndef GFX_USE_GTIMER
		#define GFX_USE_GTIMER	GFXOFF
	#endif
	/**
	 * @brief   GFX Queue API
	 * @details	Defaults to GFXOFF
	 * @details	Provides queue management.
	 */
	#ifndef GFX_USE_GQUEUE
		#define GFX_USE_GQUEUE	GFXOFF
	#endif
	/**
	 * @brief   GFX Input Device API
	 * @details	Defaults to GFXOFF
	 * @note	Also add the specific hardware drivers to your makefile.
	 * 			Eg.
	 * 				include $(GFXLIB)/drivers/ginput/toggle/Pal/driver.mk
	 * 			and...
	 * 				include $(GFXLIB)/drivers/ginput/touch/MCU/driver.mk
	 */
	#ifndef GFX_USE_GINPUT
		#define GFX_USE_GINPUT	GFXOFF
	#endif
	/**
	 * @brief   GFX Generic Periodic ADC API
	 * @details	Defaults to GFXOFF
	 */
	#ifndef GFX_USE_GADC
		#define GFX_USE_GADC	GFXOFF
	#endif
	/**
	 * @brief   GFX Audio API
	 * @details	Defaults to GFXOFF
	 * @note	Also add the specific hardware drivers to your makefile.
	 * 			Eg.
	 * 				include $(GFXLIB)/drivers/gaudio/GADC/driver.mk
	 */
	#ifndef GFX_USE_GAUDIO
		#define GFX_USE_GAUDIO	GFXOFF
	#endif
	/**
	 * @brief   GFX Miscellaneous Routines API
	 * @details	Defaults to GFXOFF
	 * @note	Turning this on without turning on any GMISC_NEED_xxx macros will result
	 * 			in no extra code being compiled in. GMISC is made up from the sum of its
	 * 			parts.
	 */
	#ifndef GFX_USE_GMISC
		#define GFX_USE_GMISC	GFXOFF
	#endif
	/**
	 * @brief   GFX File API
	 * @details	Defaults to GFXOFF
	 */
	#ifndef GFX_USE_GFILE
		#define GFX_USE_GFILE	GFXOFF
	#endif
	/**
	 * @brief   GFX Translation Support API
	 * @details	Defaults to GFXOFF
	 */
	#ifndef GFX_USE_GTRANS
		#define GFX_USE_GTRANS	GFXOFF
	#endif
/** @} */

/**
 * @name    GFX compatibility options
 * @{
 */
	/**
	 * @brief   Include the uGFX V2.x Old Colors
	 * @details	Defaults to GFXON
	 * @pre		Requires GFX_COMPAT_V2 to be GFXON
	 * @note	The old color definitions (particularly Red, Green & Blue) can
	 *			cause symbol conflicts with many platforms eg Win32, STM32 HAL etc.
	 *			Although officially these symbols are part of the V2.x API, this
	 *			option allows them to be turned off even when the rest of the V2.x
	 *			API is turned on.
	 */
	#ifndef GFX_COMPAT_OLDCOLORS
		#define GFX_COMPAT_OLDCOLORS		GFXON
	#endif
/** @} */

/** @} */
