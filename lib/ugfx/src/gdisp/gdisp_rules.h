/*
 * This file is subject to the terms of the GFX License. If a copy of
 * the license was not distributed with this file, you can obtain one at:
 *
 *              http://ugfx.io/license.html
 */

/**
 * @file    src/gdisp/gdisp_rules.h
 * @brief   GDISP safety rules header file.
 *
 * @addtogroup GDISP
 * @{
 */

#ifndef _GDISP_RULES_H
#define _GDISP_RULES_H

#if GFX_USE_GDISP
	#if !GFX_USE_GDRIVER
		#if GFX_DISPLAY_RULE_WARNINGS
			#if GFX_COMPILER_WARNING_TYPE == GFX_COMPILER_WARNING_DIRECT
				#warning "GDISP: GFX_USE_GDRIVER is required. GFX_USE_GDRIVER has turned on for you."
			#elif GFX_COMPILER_WARNING_TYPE == GFX_COMPILER_WARNING_MACRO
				COMPILER_WARNING("GDISP: GFX_USE_GDRIVER is required. GFX_USE_GDRIVER has turned on for you.")
			#endif
		#endif
		#undef GFX_USE_GDRIVER
		#define GFX_USE_GDRIVER				GFXON
	#endif
	#if defined(GDISP_DRIVER_LIST)
        #if GDISP_TOTAL_DISPLAYS != 1
            #error "GDISP Multiple Drivers: You can't specify both GDISP_TOTAL_DISPLAYS and GDISP_DRIVER_LIST"
        #endif
		#ifndef GDISP_PIXELFORMAT
			#error "GDISP Multiple Drivers: You must specify a value for GDISP_PIXELFORMAT when using GDISP_DRIVER_LIST"
		#endif
	#endif
	#if GDISP_NEED_AUTOFLUSH && GDISP_NEED_TIMERFLUSH
		#if GFX_DISPLAY_RULE_WARNINGS
			#if GFX_COMPILER_WARNING_TYPE == GFX_COMPILER_WARNING_DIRECT
				#warning "GDISP: Both GDISP_NEED_AUTOFLUSH and GDISP_NEED_TIMERFLUSH has been set. GDISP_NEED_TIMERFLUSH has been disabled for you."
			#elif GFX_COMPILER_WARNING_TYPE == GFX_COMPILER_WARNING_MACRO
				COMPILER_WARNING("GDISP: Both GDISP_NEED_AUTOFLUSH and GDISP_NEED_TIMERFLUSH has been set. GDISP_NEED_TIMERFLUSH has been disabled for you.")
			#endif
		#endif
		#undef GDISP_NEED_TIMERFLUSH
		#define GDISP_NEED_TIMERFLUSH		GFXOFF
	#endif
	#if GDISP_NEED_TIMERFLUSH
		#if GDISP_NEED_TIMERFLUSH < 50 || GDISP_NEED_TIMERFLUSH > 1200
			#error "GDISP: GDISP_NEED_TIMERFLUSH has been set to an invalid value (GFXOFF, 50-1200)."
		#endif
		#if !GFX_USE_GTIMER
			#if GFX_DISPLAY_RULE_WARNINGS
				#if GFX_COMPILER_WARNING_TYPE == GFX_COMPILER_WARNING_DIRECT
					#warning "GDISP: GDISP_NEED_TIMERFLUSH has been set but GFX_USE_GTIMER has not been set. It has been turned on for you."
				#elif GFX_COMPILER_WARNING_TYPE == GFX_COMPILER_WARNING_MACRO
					COMPILER_WARNING("GDISP: GDISP_NEED_TIMERFLUSH has been set but GFX_USE_GTIMER has not been set. It has been turned on for you.")
				#endif
			#endif
			#undef GFX_USE_GTIMER
			#define GFX_USE_GTIMER				GFXON
			#undef GDISP_NEED_MULTITHREAD
			#define GDISP_NEED_MULTITHREAD		GFXON
		#endif
	#endif
	#if GDISP_NEED_ANTIALIAS && !GDISP_NEED_PIXELREAD
		#if GDISP_HARDWARE_PIXELREAD
			#if GFX_DISPLAY_RULE_WARNINGS
				#if GFX_COMPILER_WARNING_TYPE == GFX_COMPILER_WARNING_DIRECT
					#warning "GDISP: GDISP_NEED_ANTIALIAS has been set but GDISP_NEED_PIXELREAD has not. It has been turned on for you."
				#elif GFX_COMPILER_WARNING_TYPE == GFX_COMPILER_WARNING_MACRO
					COMPILER_WARNING("GDISP: GDISP_NEED_ANTIALIAS has been set but GDISP_NEED_PIXELREAD has not. It has been turned on for you.")
				#endif
			#endif
			#undef GDISP_NEED_PIXELREAD
			#define GDISP_NEED_PIXELREAD	GFXON
		#else
			#if GFX_DISPLAY_RULE_WARNINGS
				#if GFX_COMPILER_WARNING_TYPE == GFX_COMPILER_WARNING_DIRECT
					#warning "GDISP: GDISP_NEED_ANTIALIAS has been set but your hardware does not support reading back pixels. Anti-aliasing will only occur for filled characters."
				#elif GFX_COMPILER_WARNING_TYPE == GFX_COMPILER_WARNING_MACRO
					COMPILER_WARNING("GDISP: GDISP_NEED_ANTIALIAS has been set but your hardware does not support reading back pixels. Anti-aliasing will only occur for filled characters.")
				#endif
			#endif
		#endif
	#endif
	#if (defined(GDISP_INCLUDE_FONT_SMALL) && GDISP_INCLUDE_FONT_SMALL) || (defined(GDISP_INCLUDE_FONT_LARGER) && GDISP_INCLUDE_FONT_LARGER)
		#if GFX_DISPLAY_RULE_WARNINGS
			#if GFX_COMPILER_WARNING_TYPE == GFX_COMPILER_WARNING_DIRECT
				#warning "GDISP: An old font (Small or Larger) has been defined. A single default font of UI2 has been added instead."
				#warning "GDISP: Please see <$(GFXLIB)/include/gdisp/fonts/fonts.h> for a list of available font names."
			#elif GFX_COMPILER_WARNING_TYPE == GFX_COMPILER_WARNING_MACRO
				COMPILER_WARNING("GDISP: An old font (Small or Larger) has been defined. A single default font of UI2 has been added instead.")
				COMPILER_WARNING("GDISP: Please see <$(GFXLIB)/include/gdisp/fonts/fonts.h> for a list of available font names.")
			#endif
		#endif
		#undef GDISP_INCLUDE_FONT_UI2
		#define GDISP_INCLUDE_FONT_UI2		GFXON
	#endif
	#if GDISP_NEED_IMAGE
		#if !GFX_USE_GFILE
			#if GFX_DISPLAY_RULE_WARNINGS
				#if GFX_COMPILER_WARNING_TYPE == GFX_COMPILER_WARNING_DIRECT
					#warning "GDISP: GFX_USE_GFILE is required when GDISP_NEED_IMAGE is GFXON. It has been turned on for you."
				#elif GFX_COMPILER_WARNING_TYPE == GFX_COMPILER_WARNING_MACRO
					COMPILER_WARNING("GDISP: GFX_USE_GFILE is required when GDISP_NEED_IMAGE is GFXON. It has been turned on for you.")
				#endif
			#endif
			#undef GFX_USE_GFILE
			#define GFX_USE_GFILE	GFXON
		#endif
	#endif
#endif

#endif /* _GDISP_RULES_H */
/** @} */
