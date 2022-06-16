/*
 * This file is subject to the terms of the GFX License. If a copy of
 * the license was not distributed with this file, you can obtain one at:
 *
 *              http://ugfx.io/license.html
 */

/**
 * @file    src/gos/gos_cmsis.h
 * @brief   GOS - Operating System Support header file for CMSIS RTOS.
 */

#ifndef _GOS_CMSIS_H
#define _GOS_CMSIS_H

#if GFX_USE_OS_CMSIS

#include "cmsis_os.h"

#ifndef GFX_OS_HEAP_SIZE
	#define GFX_OS_HEAP_SIZE 10240
#endif

/*===========================================================================*/
/* Type definitions                                                          */
/*===========================================================================*/

#define gDelayNone			0
#define gDelayForever		osWaitForever
typedef gU32				gDelay;
typedef gU32				gTicks;
typedef gU16				gSemcount;
typedef void				gThreadreturn;
typedef osPriority			gThreadpriority;

#define gSemMaxCount			osFeature_Semaphore
#define gThreadpriorityLow		osPriorityLow
#define gThreadpriorityNormal	osPriorityNormal
#define gThreadpriorityHigh		osPriorityHigh

typedef struct gSem {
	gU32		semaphore[2];
	osSemaphoreId	id;
	gSemcount		available;
} gSem;

typedef struct gMutex {
	gU32 mutex[4];
	osMutexId id;
} gMutex;

typedef osThreadId			gThread;

#define GFX_THREAD_STACK(name, sz)			gU8 name[1];	// Some compilers don't allow zero sized arrays. Let's waste one byte
#define GFX_THREAD_FUNCTION(fnName, param)	gThreadreturn fnName(void* param)
#define gfxThreadReturn(retval)				return

/*===========================================================================*/
/* Function declarations.                                                    */
/*===========================================================================*/

#define gfxExit()					os_error(0)
#define gfxHalt(msg)				os_error(1)
#define gfxSystemTicks()			osKernelSysTick()
#define gfxMillisecondsToTicks(ms)	osKernelSysTickMicroSec(1000*ms)
#define gfxSystemLock()				osKernelInitialize()
#define gfxSystemUnlock()			osKernelStart()
#define gfxSleepMilliseconds(ms) 	osDelay(ms)

void gfxMutexInit(gMutex* pmutex);
#define gfxMutexDestroy(pmutex)		osMutexDelete((pmutex)->id)
#define gfxMutexEnter(pmutex)		osMutexWait((pmutex)->id, gDelayForever)
#define gfxMutexExit(pmutex)		osMutexRelease((pmutex)->id)

void gfxSemInit(gSem* psem, gSemcount val, gSemcount limit);
void gfxSemDestroy(gSem* psem);
gBool gfxSemWait(gSem* psem, gDelay ms);
gBool gfxSemWaitI(gSem* psem);
void gfxSemSignal(gSem* psem);
void gfxSemSignalI(gSem* psem);

gThread gfxThreadCreate(void* stackarea, gMemSize stacksz, gThreadpriority prio, GFX_THREAD_FUNCTION((*fn),p), void* param);
#define gfxYield()					osThreadYield()
#define gfxThreadMe()				osThreadGetId()
#define gfxThreadClose(thread)		{}

/*===========================================================================*/
/* Use the generic heap handling                                             */
/*===========================================================================*/

#define GOS_NEED_X_HEAP GFXON
#include "gos_x_heap.h"

#endif /* GFX_USE_OS_CMSIS */
#endif /* _GOS_CMSIS_H */
