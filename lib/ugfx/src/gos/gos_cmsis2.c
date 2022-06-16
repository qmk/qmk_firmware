/*
 * This file is subject to the terms of the GFX License. If a copy of
 * the license was not distributed with this file, you can obtain one at:
 *
 *              http://ugfx.io/license.html
 */

#include "../../gfx.h"
#include <string.h>

#if GFX_USE_OS_CMSIS2

#if !GFX_OS_NO_INIT && !GFX_OS_CALL_UGFXMAIN
	#error "GOS: Either GFX_OS_NO_INIT or GFX_OS_CALL_UGFXMAIN must be defined for CMSIS V2"
#endif

void _gosHeapInit(void);

void _gosInit(void)
{
	#if GFX_OS_NO_INIT && !GFX_OS_INIT_NO_WARNING
		#if GFX_COMPILER_WARNING_TYPE == GFX_COMPILER_WARNING_DIRECT
			#warning "GOS: Operating System initialization has been turned off. Make sure you call osKernelInitialize()."
		#elif GFX_COMPILER_WARNING_TYPE == GFX_COMPILER_WARNING_MACRO
			COMPILER_WARNING("GOS: Operating System initialization has been turned off. Make sure you call osKernelInitialize().")
		#endif
	#endif

	// Set up the heap allocator
	_gosHeapInit();
}

#if !GFX_OS_NO_INIT && GFX_OS_CALL_UGFXMAIN
	static GFX_THREAD_FUNCTION(startUGFX_CMSIS2, p) {
		(void) p;
		uGFXMain();
	}
#endif
void _gosPostInit(void)
{
	#if !GFX_OS_NO_INIT && GFX_OS_CALL_UGFXMAIN
		switch(osKernelGetState()) {
		case osKernelInactive:
			osKernelInitialize();
			/* Fall Through */
		case osKernelReady:
			gfxThreadCreate(0, GFX_OS_UGFXMAIN_STACKSIZE, gThreadpriorityNormal, startUGFX_CMSIS2, 0);
			osKernelStart();
			gfxHalt("Unable to start CMSIS V2 scheduler. Out of memory?");
			break;
		default:
			gfxThreadCreate(0, GFX_OS_UGFXMAIN_STACKSIZE, gThreadpriorityNormal, startUGFX_CMSIS2, 0);
			break;
		}
	#endif
}

void _gosDeinit(void)
{
}

void gfxMutexInit(gMutex* pmutex)
{
	*pmutex = osMutexNew(NULL);
}

void gfxSemInit(gSem* psem, gSemcount val, gSemcount limit)
{
	*psem = osSemaphoreNew(limit, val, NULL);
}

gBool gfxSemWait(gSem* psem, gDelay ms)
{
	if (osSemaphoreAcquire(*psem, gfxMillisecondsToTicks(ms)) == osOK)
		return gTrue;
	return gFalse;
}

gThread gfxThreadCreate(void* stackarea, gMemSize stacksz, gThreadpriority prio, GFX_THREAD_FUNCTION((*fn),p), void* param)
{
	osThreadAttr_t def;

	(void)stackarea;

	memset(&def, 0, sizeof(def));
	def.name = "uGFX";
	def.attr_bits = osThreadDetached;	// osThreadJoinable
	def.stack_mem = 0;
	def.stack_size = stacksz;
	def.priority = prio;
	//def.tz_module = ????;

	return osThreadNew((osThreadFunc_t)fn, param, &def);
}

gThreadreturn gfxThreadWait(gThread thread) {
	while(1) {
		switch(osThreadGetState(thread)) {
		case osThreadReady:
		case osThreadRunning:
		case osThreadBlocked:
			gfxYield();
			break;
		default:
			return;
		}
	}
}

#endif /* GFX_USE_OS_CMSIS2 */
