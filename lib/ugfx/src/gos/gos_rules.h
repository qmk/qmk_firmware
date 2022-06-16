/*
 * This file is subject to the terms of the GFX License. If a copy of
 * the license was not distributed with this file, you can obtain one at:
 *
 *              http://ugfx.io/license.html
 */

/**
 * @file    src/gos/gos_rules.h
 * @brief   GOS safety rules header file.
 *
 * @addtogroup GOS
 * @{
 */

#ifndef _GOS_RULES_H
#define _GOS_RULES_H

#if !GFX_USE_OS_CHIBIOS && !GFX_USE_OS_WIN32 && !GFX_USE_OS_LINUX && !GFX_USE_OS_OSX && !GFX_USE_OS_RAW32 && !GFX_USE_OS_FREERTOS && !GFX_USE_OS_ECOS && !GFX_USE_OS_RAWRTOS && !GFX_USE_OS_ARDUINO && !GFX_USE_OS_CMSIS && !GFX_USE_OS_CMSIS2 && !GFX_USE_OS_KEIL && !GFX_USE_OS_RTX5 && !GFX_USE_OS_NIOS && !GFX_USE_OS_ZEPHYR && !GFX_USE_OS_QT
	#error "GOS: No operating system has been defined."
#endif

#if GFX_USE_OS_CHIBIOS + GFX_USE_OS_WIN32 + GFX_USE_OS_LINUX + GFX_USE_OS_OSX + GFX_USE_OS_RAW32 + GFX_USE_OS_FREERTOS + GFX_USE_OS_ECOS + GFX_USE_OS_RAWRTOS + GFX_USE_OS_ARDUINO + GFX_USE_OS_CMSIS + GFX_USE_OS_CMSIS2 + GFX_USE_OS_KEIL + GFX_USE_OS_RTX5 + GFX_USE_OS_NIOS + GFX_USE_OS_ZEPHYR + GFX_USE_OS_QT != 1 * GFXON
	#error "GOS: More than one operation system has been defined as GFXON."
#endif

#if GFX_FREERTOS_USE_TRACE && !GFX_USE_OS_FREERTOS
 	#error "GOS: GFX_FREERTOS_USE_TRACE is only available for the FreeRTOS port."
#endif

#if GFX_USE_OS_ZEPHYR && !defined(CONFIG_HEAP_MEM_POOL_SIZE)
	#error "GOS: CONFIG_HEAP_MEM_POOL_SIZE must be defined to use the Zephyr port."
#endif

#if GFX_EMULATE_MALLOC
	#if GFX_USE_OS_WIN32 || GFX_USE_OS_LINUX || GFX_USE_OS_OSX || GFX_USE_OS_ECOS || \
			(GFX_OS_HEAP_SIZE == 0 && (GFX_USE_OS_RAW32 || GFX_USE_OS_ARDUINO || GFX_USE_OS_CMSIS || GFX_USE_OS_CMSIS2 || GFX_USE_OS_KEIL || GFX_USE_OS_RTX5))
		#if GFX_DISPLAY_RULE_WARNINGS
			#if GFX_COMPILER_WARNING_TYPE == GFX_COMPILER_WARNING_DIRECT
				#warning "GOS: Cannot emulate malloc as gfxAlloc() internally uses malloc on this platform"
			#elif GFX_COMPILER_WARNING_TYPE == GFX_COMPILER_WARNING_MACRO
				COMPILER_WARNING("GOS: Cannot emulate malloc as gfxAlloc() internally uses malloc on this platform")
			#endif
		#endif
		#undef GFX_EMULATE_MALLOC
		#define GFX_EMULATE_MALLOC	GFXOFF
	#endif
#endif

#endif /* _GOS_RULES_H */
/** @} */
