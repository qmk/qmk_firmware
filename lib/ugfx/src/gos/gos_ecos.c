/*
 * This file is subject to the terms of the GFX License. If a copy of
 * the license was not distributed with this file, you can obtain one at:
 *
 *              http://ugfx.io/license.html
 */

#include "../../gfx.h"

#if GFX_USE_OS_ECOS

void _gosInit(void)
{
	#if !GFX_OS_NO_INIT
		#error "GOS: Operating System initialization for eCos is not yet implemented in uGFX. Please set GFX_OS_NO_INIT to GFXON in your gfxconf.h"
	#endif
	#if !GFX_OS_INIT_NO_WARNING
		#if GFX_COMPILER_WARNING_TYPE == GFX_COMPILER_WARNING_DIRECT
			#warning "GOS: Operating System initialization has been turned off. Make sure you call cyg_scheduler_start() before gfxInit() in your application!"
		#elif GFX_COMPILER_WARNING_TYPE == GFX_COMPILER_WARNING_MACRO
			COMPILER_WARNING("GOS: Operating System initialization has been turned off. Make sure you call cyg_scheduler_start() before gfxInit() in your application!")
		#endif
	#endif
}

void _gosPostInit(void)
{
}

void _gosDeinit(void)
{
	/* ToDo */
}

void gfxSleepMilliseconds(gDelay ms)
{
	switch(ms) {
		case gDelayNone:	cyg_thread_yield();								return;
		case gDelayForever:		cyg_thread_suspend(cyg_thread_self());			return;
		default:				cyg_thread_delay(gfxMillisecondsToTicks(ms));	return;
	}
}

void gfxSleepMicroseconds(gDelay ms)
{
	switch(ms) {
		case gDelayNone:														return;
		case gDelayForever:		cyg_thread_suspend(cyg_thread_self());				return;
		default:				cyg_thread_delay(gfxMillisecondsToTicks(ms/1000));	return;
	}
}

void gfxSemInit(gSem *psem, gSemcount val, gSemcount limit)
{
	if (val > limit)
		val = limit;

	psem->limit = limit;
	cyg_semaphore_init(&psem->sem, val);
}

void gfxSemDestroy(gSem *psem)
{
	cyg_semaphore_destroy(&psem->sem);
}

gBool gfxSemWait(gSem *psem, gDelay ms)
{
	switch(ms) {
	case gDelayNone:	return cyg_semaphore_trywait(&psem->sem);
	case gDelayForever:		return cyg_semaphore_wait(&psem->sem);
	default:				return cyg_semaphore_timed_wait(&psem->sem, gfxMillisecondsToTicks(ms)+cyg_current_time());
	}
}

gBool gfxSemWaitI(gSem *psem)
{
	return cyg_semaphore_trywait(&psem->sem);
}

void gfxSemSignal(gSem *psem)
{
	if (psem->limit == gSemMaxCount)
		cyg_semaphore_post(&psem->sem);
	else {
		cyg_scheduler_lock();
		if (cyg_semaphore_peek(&psem->sem, &cnt) < psem->limit)
			cyg_semaphore_post(&psem->sem);
		cyg_scheduler_unlock();
	}
}

void gfxSemSignalI(gSem *psem)
{
	if (psem->limit == gSemMaxCount || cyg_semaphore_peek(&psem->sem, &cnt) < psem->limit)
		cyg_semaphore_post(&psem->sem);
}

gThread gfxThreadCreate(void *stackarea, gMemSize stacksz, gThreadpriority prio, GFX_THREAD_FUNCTION((*fn),p), void *param)
{
	gThread		th;

	if (!stackarea) {
		if (!stacksz) stacksz = CYGNUM_HAL_STACK_SIZE_TYPICAL;
		if (!(stackarea = gfxAlloc(stacksz+sizeof(cyg_thread))))
			return 0;
	}

	if (!stacksz)
		return 0;

    cyg_thread_create(prio, fn, param, "uGFX", (((cyg_thread *)stackarea)+1), stacksz, &th, (cyg_thread *)stackarea);
    cyg_thread_resume(th);
	return th;
}

#endif /* GFX_USE_OS_ECOS */
