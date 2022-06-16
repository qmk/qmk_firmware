/*
 * This file is subject to the terms of the GFX License. If a copy of
 * the license was not distributed with this file, you can obtain one at:
 *
 *              http://ugfx.io/license.html
 */

/**
 * @file    src/gos/gos_cmsis2.h
 * @brief   GOS - Operating System Support header file for CMSIS 2.0 RTOS.
 */

#ifndef _GOS_CMSIS2_H
#define _GOS_CMSIS2_H

#if GFX_USE_OS_CMSIS2

#include "cmsis_os2.h"

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
typedef osPriority_t		gThreadpriority;

#define gSemMaxCount			65535UL
#define gThreadpriorityLow		osPriorityLow
#define gThreadpriorityNormal	osPriorityNormal
#define gThreadpriorityHigh		osPriorityHigh

typedef osSemaphoreId_t		gSem;

typedef osMutexId_t 		gMutex;

typedef osThreadId_t		gThread;

#define GFX_THREAD_STACK(name, sz)			gU8 name[1];	// Some compilers don't allow zero sized arrays. Let's waste one byte
#define GFX_THREAD_FUNCTION(fnName, param)	gThreadreturn fnName(void* param)
#define gfxThreadReturn(retval)				return

/*===========================================================================*/
/* Function declarations.                                                    */
/*===========================================================================*/

#define gfxExit()					os_error(0)
#define gfxHalt(msg)				os_error(1)
#define gfxSystemTicks()			osKernelGetTickCount()
#define gfxMillisecondsToTicks(ms)	(1000*(ms)/osKernelGetTickFreq())
#define gfxSystemLock()				osKernelLock()
#define gfxSystemUnlock()			osKernelUnlock()
#define gfxSleepMilliseconds(ms) 	osDelay(ms)

void gfxMutexInit(gMutex* pmutex);
#define gfxMutexDestroy(pmutex)		osMutexDelete(*(pmutex))
#define gfxMutexEnter(pmutex)		osMutexAcquire(*(pmutex), gDelayForever)
#define gfxMutexExit(pmutex)		osMutexRelease(*(pmutex))

void gfxSemInit(gSem* psem, gSemcount val, gSemcount limit);
#define gfxSemDestroy(psem)		osSemaphoreDelete(*(psem))
gBool gfxSemWait(gSem* psem, gDelay ms);
#define gfxSemWaitI(psem)		gfxSemWait((psem), 0)
#define gfxSemSignal(psem)		osSemaphoreRelease(*(psem))
#define gfxSemSignalI(psem)		osSemaphoreRelease(*(psem))

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
