/*
 * This file is subject to the terms of the GFX License. If a copy of
 * the license was not distributed with this file, you can obtain one at:
 *
 *              http://ugfx.io/license.html
 */

/**
 * @file    src/gqueue/gqueue_rules.h
 * @brief   GQUEUE safety rules header file.
 *
 * @addtogroup GQUEUE
 * @{
 */

#ifndef _GQUEUE_RULES_H
#define _GQUEUE_RULES_H

#if GFX_USE_GQUEUE
	#if GQUEUE_NEED_BUFFERS && !GQUEUE_NEED_GSYNC
		#if GFX_DISPLAY_RULE_WARNINGS
			#if GFX_COMPILER_WARNING_TYPE == GFX_COMPILER_WARNING_DIRECT
				#warning "GQUEUE: GQUEUE_NEED_GSYNC is required if GQUEUE_NEED_BUFFERS is GFXON. It has been turned on for you."
			#elif GFX_COMPILER_WARNING_TYPE == GFX_COMPILER_WARNING_MACRO
				COMPILER_WARNING("GQUEUE: GQUEUE_NEED_GSYNC is required if GQUEUE_NEED_BUFFERS is GFXON. It has been turned on for you.")
			#endif
		#endif
		#undef GQUEUE_NEED_GSYNC
		#define	GQUEUE_NEED_GSYNC		GFXON
	#endif
#endif

#endif /* _GQUEUE_RULES_H */
/** @} */
