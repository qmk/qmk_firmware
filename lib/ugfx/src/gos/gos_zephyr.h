/*
 * This file is subject to the terms of the GFX License. If a copy of
 * the license was not distributed with this file, you can obtain one at:
 *
 *              http://ugfx.io/license.html
 */

/**
 * @file    src/gos/gos_zepyhr.h
 * @brief   GOS - Operating System Support header file for Zephyr RTOS.
 *			Zephyr SDK 0.9.1
 */

#ifndef _GOS_ZEPHYR_H
#define _GOS_ZEPHYR_H

#if GFX_USE_OS_ZEPHYR

#include <zephyr.h>

/*===========================================================================*/
/* Type definitions                                                          */
/*===========================================================================*/

typedef s32_t 	gDelay;
typedef u32_t	gTicks;
typedef u32_t	gSemcount;
typedef void	gThreadreturn;
typedef int	gThreadpriority;

#define GFX_THREAD_FUNCTION(fnName, param)	gThreadreturn fnName(void* param, void* p2, void* p3)

#define GFX_THREAD_STACK(name, sz)			K_THREAD_STACK_DEFINE(name, sz)

#define gfxThreadReturn(retval)				return

#define gDelayNone				K_NO_WAIT
#define gDelayForever			K_FOREVER
#define gSemMaxCount			((gSemcount)(((unsigned long)((gSemcount)(-1))) >> 1))
#define gThreadpriorityLow		CONFIG_NUM_PREEMPT_PRIORITIES-1
#define gThreadpriorityNormal	1
#define gThreadpriorityHigh		0

typedef struct k_sem gSem;

typedef struct k_mutex gMutex;

typedef k_tid_t gThread;

/*===========================================================================*/
/* Function declarations.                                                    */
/*===========================================================================*/

#define gfxHalt(msg)	do{}while(0)
#define gfxExit()		do{}while(0)

// Don't forget to set CONFIG_HEAP_MEM_POOL_SIZE
#define gfxAlloc(sz)					k_malloc(sz)
#define gfxFree(ptr)					k_free(ptr)
#define gfxRealloc(ptr, oldsz, newsz)	do{}while(0)

#define gfxYield()						k_yield()
#define gfxSleepMilliseconds(ms)		k_sleep(ms)
#define gfxSleepMicroseconds(us)		do{}while(0)
#define gfxMillisecondsToTicks(ms)		CONFIG_SYS_CLOCK_TICKS_PER_SEC*ms/1000
gTicks gfxSystemTicks();

#define gfxSystemLock()					k_sched_lock()
#define gfxSystemUnlock()				k_sched_unlock()

#define gfxMutexInit(pmutex)			k_mutex_init(pmutex)
#define gfxMutexDestroy(pmutex)			do{}while(0)
#define gfxMutexEnter(pmutex)			k_mutex_lock(pmutex, K_FOREVER)
#define gfxMutexExit(pmutex)			k_mutex_unlock(pmutex)

#define gfxSemInit(psem, val, limit) 	k_sem_init(psem, val, limit)
#define gfxSemDestroy(psem)				do{}while(0)
#define gfxSemWait(psem, ms)  			(k_sem_take(psem, ms) == 0) ? gTrue : gFalse
#define gfxSemWaitI(psem) 				(k_sem_take(psem, K_NO_WAIT) == 0) ? gTrue : gFalse
#define gfxSemSignal(psem)				k_sem_give(psem)
#define gfxSemSignalI(psem)				k_sem_give(psem)
#define gfxSemCounter(psem)				k_sem_count_get(psem)
#define gfxSemCounterI(psem)			k_sem_count_get(psem)

#define gfxThreadCreate(stackarea, stacksz, prio, fn, param)\
	k_thread_spawn(stackarea, stacksz, fn, param, NULL, NULL, prio, 0, K_NO_WAIT)
#define gfxThreadWait(thread)			0
#define gfxThreadMe()					k_current_get()
#define gfxThreadClose(thread)			k_thread_abort(thread)

#endif /* GFX_USE_OS_ZEPHYR */
#endif /* _GOS_H */
/** @} */
