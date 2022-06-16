/*
 * This file is subject to the terms of the GFX License. If a copy of
 * the license was not distributed with this file, you can obtain one at:
 *
 *              http://ugfx.io/license.html
 */

#include "../../gfx.h"

#if GFX_USE_OS_RAWRTOS

#include <string.h>
#include "raw_api.h"
#include "raw_config.h"

#if CONFIG_RAW_MUTEX != 1
	#error "GOS: CONFIG_RAW_MUTEX must be defined in raw_config.h"
#endif

#if CONFIG_RAW_SEMAPHORE != 1
	#error "GOS: CONFIG_RAW_SEMAPHORE must be defined in raw_config.h"
#endif


void _gosInit(void)
{
	#if !GFX_OS_NO_INIT
		#error "GOS: Operating System initialization for RawRTOS is not yet implemented in uGFX. Please set GFX_OS_NO_INIT to GFXON in your gfxconf.h"
	#endif
	#if !GFX_OS_INIT_NO_WARNING
		#if GFX_COMPILER_WARNING_TYPE == GFX_COMPILER_WARNING_DIRECT
			#warning "GOS: Operating System initialization has been turned off. Make sure you call raw_os_start() before gfxInit() in your application!"
		#elif GFX_COMPILER_WARNING_TYPE == GFX_COMPILER_WARNING_MACRO
			COMPILER_WARNING("GOS: Operating System initialization has been turned off. Make sure you call raw_os_start() before gfxInit() in your application!")
		#endif
	#endif
}

void _gosPostInit(void)
{
}

void _gosDeinit(void)
{
}


void gfxSleepMilliseconds(gDelay ms)
{
	gTicks ticks = ms*RAW_TICKS_PER_SECOND/1000;
	if(!ticks)ticks = 1;
	raw_sleep(ticks);
}

void gfxSleepMicroseconds(gDelay us)
{
	gTicks ticks = (us/1000)*RAW_TICKS_PER_SECOND/1000;
	if(!ticks)ticks = 1;
	raw_sleep(ticks);
}

gBool gfxSemWait(gSem* psem, gDelay ms)
{
	gTicks ticks = ms*RAW_TICKS_PER_SECOND/1000;
	if(!ticks)ticks=1;
	if(raw_semaphore_get((psem), ticks)==RAW_SUCCESS)
		return gTrue;
	return gFalse;
}

gBool gfxSemWaitI(gSem* psem)
{
	if(raw_semaphore_get((psem), RAW_NO_WAIT)==RAW_SUCCESS)
		return gTrue;
	return gFalse;
}

gThread gfxThreadCreate(void *stackarea, gMemSize stacksz, gThreadpriority prio, GFX_THREAD_FUNCTION((*fn),p), void *param)
{
	RAW_U16 ret;
	gThread taskobj;

	taskobj = gfxAlloc(sizeof(RAW_TASK_OBJ));
	ret = raw_task_create(taskobj, (RAW_U8  *)"uGFX_TASK", param,
	                         prio, 0,  stackarea, 
	                         stacksz/sizeof(PORT_STACK) ,  fn, 1); 

	if (ret != RAW_SUCCESS) {
		for (;;);
	}

	return (taskobj);
}


#endif



