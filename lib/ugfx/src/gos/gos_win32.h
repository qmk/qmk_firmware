/*
 * This file is subject to the terms of the GFX License. If a copy of
 * the license was not distributed with this file, you can obtain one at:
 *
 *              http://ugfx.io/license.html
 */

/**
 * @file    src/gos/gos_win32.h
 * @brief   GOS - Operating System Support header file for WIN32.
 */

#ifndef _GOS_WIN32_H
#define _GOS_WIN32_H

#if GFX_USE_OS_WIN32

#ifndef _WIN32_WINNT
	#define _WIN32_WINNT 0x0501			// Windows XP and up
#endif

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#undef WIN32_LEAN_AND_MEAN

#include <malloc.h>

typedef DWORD				gDelay;
typedef DWORD				gTicks;
typedef LONG				gSemcount;
typedef DWORD				gThreadreturn;
typedef int					gThreadpriority;

#define GFX_THREAD_FUNCTION(fnName, param)	gThreadreturn (WINAPI fnName)(void *param)
#define GFX_THREAD_STACK(name, sz)			gU8 name[1];
#define gfxThreadReturn(retval)				return retval

#define gDelayNone					0
#define gDelayForever				INFINITE
#define gSemMaxCount				((gSemcount)(((unsigned long)((gSemcount)(-1))) >> 1))
#define gThreadpriorityLow			THREAD_PRIORITY_BELOW_NORMAL
#define gThreadpriorityNormal		THREAD_PRIORITY_NORMAL
#define gThreadpriorityHigh			THREAD_PRIORITY_ABOVE_NORMAL

typedef HANDLE gSem;
typedef HANDLE gMutex;
typedef HANDLE gThread;

#define gfxExit()						ExitProcess(0)
#define gfxAlloc(sz)					malloc(sz)
#define gfxRealloc(p,osz,nsz)			realloc(p, nsz)
#define gfxFree(ptr)					free(ptr)
#define gfxSleepMilliseconds(ms)		Sleep(ms)
#define gfxYield()						Sleep(0)
#define gfxSystemTicks()				GetTickCount()
#define gfxMillisecondsToTicks(ms)		(ms)
#define gfxMutexInit(pmutex)			*(pmutex) = CreateMutex(0, FALSE, 0)
#define gfxMutexDestroy(pmutex)			CloseHandle(*(pmutex))
#define gfxMutexEnter(pmutex) 			WaitForSingleObject(*(pmutex), INFINITE)
#define gfxMutexExit(pmutex)			ReleaseMutex(*(pmutex))
#define gfxSemInit(psem, val, limit)	*(psem) = CreateSemaphore(0, val, limit, 0)
#define gfxSemDestroy(psem)				CloseHandle(*(psem))
#define gfxSemWaitI(psem)				gfxSemWait((psem), gDelayNone)
#define gfxSemSignal(psem)				ReleaseSemaphore(*(psem), 1, 0)
#define gfxSemSignalI(psem)				ReleaseSemaphore(*(psem), 1, 0)
#define gfxThreadMe()					GetCurrentThread()
#define gfxThreadClose(thread)			CloseHandle(thread)

/*===========================================================================*/
/* Function declarations.                                                    */
/*===========================================================================*/

void gfxHalt(const char *msg);
void gfxSleepMicroseconds(gDelay ms);
gBool gfxSemWait(gSem *psem, gDelay ms);
void gfxSystemLock(void);
void gfxSystemUnlock(void);
gThread gfxThreadCreate(void *stackarea, gMemSize stacksz, gThreadpriority prio, GFX_THREAD_FUNCTION(*fn,p), void *param);
gThreadreturn gfxThreadWait(gThread thread);

#endif /* GFX_USE_OS_WIN32 */
#endif /* _GOS_WIN32_H */

