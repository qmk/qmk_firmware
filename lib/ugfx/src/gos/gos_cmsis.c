/*
 * This file is subject to the terms of the GFX License. If a copy of
 * the license was not distributed with this file, you can obtain one at:
 *
 *              http://ugfx.io/license.html
 */

#include "../../gfx.h"
#include <string.h>

#if GFX_USE_OS_CMSIS

void _gosHeapInit(void);

void _gosInit(void)
{
	#if !GFX_OS_NO_INIT
		osKernelInitialize();
		if (!osKernelRunning())
			osKernelStart();
	#elif !GFX_OS_INIT_NO_WARNING
		#if GFX_COMPILER_WARNING_TYPE == GFX_COMPILER_WARNING_DIRECT
			#warning "GOS: Operating System initialization has been turned off. Make sure you call osKernelInitialize() and osKernelStart() before gfxInit() in your application!"
		#elif GFX_COMPILER_WARNING_TYPE == GFX_COMPILER_WARNING_MACRO
			COMPILER_WARNING("GOS: Operating System initialization has been turned off. Make sure you call osKernelInitialize() and osKernelStart() before gfxInit() in your application!")
		#endif
	#endif

	// Set up the heap allocator
	_gosHeapInit();
}

void _gosPostInit(void)
{
}

void _gosDeinit(void)
{
}

void gfxMutexInit(gMutex* pmutex)
{
	osMutexDef_t def;
	def.mutex = pmutex->mutex;
	
	pmutex->id = osMutexCreate(&def);
}

void gfxSemInit(gSem* psem, gSemcount val, gSemcount limit)
{
	osSemaphoreDef_t def;
	def.semaphore = psem->semaphore;
	
	if (val > limit) val = limit;
	psem->available = limit - val;
	psem->id = osSemaphoreCreate(&def, val);
}

void gfxSemDestroy(gSem* psem)
{
	osSemaphoreDelete(psem->id);
}

gBool gfxSemWait(gSem* psem, gDelay ms)
{
	if (osSemaphoreWait(psem->id, ms) > 0) {
		psem->available++;
		return gTrue;
	}
	return gFalse;
}

gBool gfxSemWaitI(gSem* psem)
{
	return gfxSemWait(psem, 0);
}

void gfxSemSignal(gSem* psem)
{
	gfxSemSignalI(psem);
}

void gfxSemSignalI(gSem* psem)
{
	if (psem->available) {
		psem->available--;
		osSemaphoreRelease(psem->id);
	}
}

gThread gfxThreadCreate(void* stackarea, gMemSize stacksz, gThreadpriority prio, GFX_THREAD_FUNCTION((*fn),p), void* param)
{	
	osThreadDef_t def;

	(void)stackarea;
	
	def.pthread = (os_pthread)fn;
	def.tpriority = prio;
	def.instances = 1;
	def.stacksize = stacksz;

	return osThreadCreate(&def, param);
}

gThreadreturn gfxThreadWait(gThread thread) {
	while(osThreadGetPriority(thread) == osPriorityError)
		gfxYield();
}

#endif /* GFX_USE_OS_CMSIS */
