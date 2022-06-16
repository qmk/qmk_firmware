/*
 * This file is subject to the terms of the GFX License. If a copy of
 * the license was not distributed with this file, you can obtain one at:
 *
 *              http://ugfx.io/license.html
 */

/**
 * @file    src/gaudio/gaudio_rules.h
 * @brief   GAUDIO safety rules header file.
 *
 * @addtogroup GAUDIO
 * @{
 */

#ifndef _GAUDIO_RULES_H
#define _GAUDIO_RULES_H

#if GFX_USE_GAUDIO
	#if !GAUDIO_NEED_PLAY && !GAUDIO_NEED_RECORD
		#error "GAUDIO: GAUDIO_NEED_PLAY and/or GAUDIO_NEED_RECORD is required if GFX_USE_GAUDIO is GFXON"
	#endif
	#if !GFX_USE_GQUEUE
		#if GFX_DISPLAY_RULE_WARNINGS
			#if GFX_COMPILER_WARNING_TYPE == GFX_COMPILER_WARNING_DIRECT
				#warning "GAUDIO: GFX_USE_GQUEUE is required if GFX_USE_GAUDIO is GFXON. It has been turned on for you."
			#elif GFX_COMPILER_WARNING_TYPE == GFX_COMPILER_WARNING_MACRO
				COMPILER_WARNING("GAUDIO: GFX_USE_GQUEUE is required if GFX_USE_GAUDIO is GFXON. It has been turned on for you.")
			#endif
		#endif
		#undef GFX_USE_GQUEUE
		#define	GFX_USE_GQUEUE		GFXON
	#endif
	#if GAUDIO_NEED_PLAY && !GQUEUE_NEED_ASYNC
		#if GFX_DISPLAY_RULE_WARNINGS
			#if GFX_COMPILER_WARNING_TYPE == GFX_COMPILER_WARNING_DIRECT
				#warning "GAUDIO: GQUEUE_NEED_ASYNC is required if GAUDIO_NEED_PLAY is GFXON. It has been turned on for you."
			#elif GFX_COMPILER_WARNING_TYPE == GFX_COMPILER_WARNING_MACRO
				COMPILER_WARNING("GAUDIO: GQUEUE_NEED_ASYNC is required if GAUDIO_NEED_PLAY is GFXON. It has been turned on for you.")
			#endif
		#endif
		#undef GQUEUE_NEED_ASYNC
		#define	GQUEUE_NEED_ASYNC		GFXON
	#endif
	#if !GQUEUE_NEED_GSYNC || !GQUEUE_NEED_BUFFERS
		#if GFX_DISPLAY_RULE_WARNINGS
			#if GFX_COMPILER_WARNING_TYPE == GFX_COMPILER_WARNING_DIRECT
				#warning "GAUDIO: GQUEUE_NEED_BUFFERS and GQUEUE_NEED_GSYNC are required if GFX_USE_GAUDIO is GFXON. They have been turned on for you."
			#elif GFX_COMPILER_WARNING_TYPE == GFX_COMPILER_WARNING_MACRO
				COMPILER_WARNING("GAUDIO: GQUEUE_NEED_BUFFERS and GQUEUE_NEED_GSYNC are required if GFX_USE_GAUDIO is GFXON. They have been turned on for you.")
			#endif
		#endif
		#undef GQUEUE_NEED_BUFFERS
		#define	GQUEUE_NEED_BUFFERS		GFXON
		#undef GQUEUE_NEED_GSYNC
		#define	GQUEUE_NEED_GSYNC		GFXON
	#endif
	#if GFX_USE_GEVENT && !GFX_USE_GTIMER
		#if GFX_DISPLAY_RULE_WARNINGS
			#if GFX_COMPILER_WARNING_TYPE == GFX_COMPILER_WARNING_DIRECT
				#warning "GAUDIO: GFX_USE_GTIMER is required if GFX_USE_GAUDIO and GFX_USE_GEVENT are GFXON. It has been turned on for you."
			#elif GFX_COMPILER_WARNING_TYPE == GFX_COMPILER_WARNING_MACRO
				COMPILER_WARNING("GAUDIO: GFX_USE_GTIMER is required if GFX_USE_GAUDIO and GFX_USE_GEVENT are GFXON. It has been turned on for you.")
			#endif
		#endif
		#undef GFX_USE_GTIMER
		#define	GFX_USE_GTIMER		GFXON
	#endif
#endif

#endif /* _GAUDIO_RULES_H */
/** @} */
