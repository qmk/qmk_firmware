/*
 * This file is subject to the terms of the GFX License. If a copy of
 * the license was not distributed with this file, you can obtain one at:
 *
 *              http://ugfx.io/license.html
 */

/**
 * @file    src/gadc/gadc_rules.h
 * @brief   GADC safety rules header file.
 *
 * @addtogroup GADC
 * @{
 */

#ifndef _GADC_RULES_H
#define _GADC_RULES_H

#if GFX_USE_GADC
	#if !GFX_USE_GTIMER
		#if GFX_DISPLAY_RULE_WARNINGS
			#if GFX_COMPILER_WARNING_TYPE == GFX_COMPILER_WARNING_DIRECT
				#warning "GADC: GFX_USE_GTIMER is required if GFX_USE_GADC is GFXON. It has been turned on for you."
			#elif GFX_COMPILER_WARNING_TYPE == GFX_COMPILER_WARNING_MACRO
				COMPILER_WARNING("GADC: GFX_USE_GTIMER is required if GFX_USE_GADC is GFXON. It has been turned on for you.")
			#endif
		#endif
		#undef GFX_USE_GTIMER
		#define	GFX_USE_GTIMER		GFXON
	#endif
	#if !GFX_USE_GQUEUE || !GQUEUE_NEED_GSYNC || !GQUEUE_NEED_BUFFERS
		#if GFX_DISPLAY_RULE_WARNINGS
			#if GFX_COMPILER_WARNING_TYPE == GFX_COMPILER_WARNING_DIRECT
				#warning "GADC: GFX_USE_GQUEUE, GQUEUE_NEED_BUFFERS and GQUEUE_NEED_GSYNC are required if GFX_USE_GADC is GFXON. They have been turned on for you."
			#elif GFX_COMPILER_WARNING_TYPE == GFX_COMPILER_WARNING_MACRO
				COMPILER_WARNING("GADC: GFX_USE_GQUEUE, GQUEUE_NEED_BUFFERS and GQUEUE_NEED_GSYNC are required if GFX_USE_GADC is GFXON. They have been turned on for you.")
			#endif
		#endif
		#undef GFX_USE_GQUEUE
		#define	GFX_USE_GQUEUE		GFXON
		#undef GQUEUE_NEED_BUFFERS
		#define	GQUEUE_NEED_BUFFERS		GFXON
		#undef GQUEUE_NEED_GSYNC
		#define	GQUEUE_NEED_GSYNC		GFXON
	#endif
#endif

#endif /* _GADC_RULES_H */
/** @} */
