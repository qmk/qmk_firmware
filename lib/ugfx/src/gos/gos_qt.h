/*
 * This file is subject to the terms of the GFX License. If a copy of
 * the license was not distributed with this file, you can obtain one at:
 *
 *              http://ugfx.io/license.html
 */

#ifndef _GOS_QT_H
#define _GOS_QT_H

#if GFX_USE_OS_QT

#define GFX_THREAD_FUNCTION(fnName, param)	gThreadreturn fnName(void *param)
#define GFX_THREAD_STACK(name, sz)          gU8 name[0]
#define gfxThreadReturn(retval)				return retval

#define gDelayNone				0
#define gDelayForever			((gDelay)-1)
#define gSemMaxCount			((gSemcount)(((unsigned long)((gSemcount)(-1))) >> 1))
#define gThreadpriorityLow		2
#define gThreadpriorityNormal	3
#define gThreadpriorityHigh		4

typedef int gTicks;
typedef int gDelay;
typedef void* gMutex;
typedef void* gSem;
typedef int gSemcount;
typedef int gThreadreturn;
typedef int gThreadpriority;
typedef void* gThread;

void _gosInit();
void _gosDeinit();

void gfxHalt(const char* msg);
void gfxExit(void);
void* gfxAlloc(gMemSize sz);
void* gfxRealloc(void *ptr, gMemSize oldsz, gMemSize newsz);
void gfxFree(void* ptr);
void gfxYield(void);
void gfxSleepMilliseconds(gDelay ms);
void gfxSleepMicroseconds(gDelay us);
gTicks gfxSystemTicks(void);
gTicks gfxMillisecondsToTicks(gDelay ms);
void gfxSystemLock(void);
void gfxSystemUnlock(void);
void gfxMutexInit(gMutex *pmutex);
void gfxMutexDestroy(gMutex *pmutex);
void gfxMutexEnter(gMutex *pmutex);
void gfxMutexExit(gMutex *pmutex);
void gfxSemInit(gSem *psem, gSemcount val, gSemcount limit);
void gfxSemDestroy(gSem *psem);
gBool gfxSemWait(gSem *psem, gDelay ms);
gBool gfxSemWaitI(gSem *psem);
void gfxSemSignal(gSem *psem);
void gfxSemSignalI(gSem *psem);
gThread gfxThreadCreate(void *stackarea, gMemSize stacksz, gThreadpriority prio, GFX_THREAD_FUNCTION((*fn),p), void *param);
gThreadreturn gfxThreadWait(gThread thread);
gThread gfxThreadMe(void);
void gfxThreadClose(gThread thread);

#endif /* GFX_USE_OS_QT */
#endif /* _GOS_QT_H */
