/*
 * This file is subject to the terms of the GFX License. If a copy of
 * the license was not distributed with this file, you can obtain one at:
 *
 *              http://ugfx.io/license.html
 */

/**
 * This threading implementation supports most 32 bit processors with or without an
 * 	underlying operating system. It uses cooperative multi-tasking. Be careful
 * 	when writing device drivers not to disturb the assumptions this creates by performing
 * 	call-backs from interrupt handlers to uGFX code unless you define the INTERRUPTS_OFF()
 * 	and INTERRUPTS_ON() macros.
 * 	It still requires some C runtime library support for the setjmp implementation...
 * 		setjmp() and longjmp()			- for threading
 * 		memcpy()						- for heap and threading
 *
 * 	You must also define the following routines in your own code so that timing functions will work...
 * 		gTicks gfxSystemTicks(void);
 *		gTicks gfxMillisecondsToTicks(gDelay ms);
 */
#ifndef _GOS_X_THREADS_H
#define _GOS_X_THREADS_H

#if GOS_NEED_X_THREADS

typedef gU32		gDelay;
typedef gU32		gTicks;
typedef short			gSemcount;
typedef int				gThreadreturn;
typedef int				gThreadpriority;

#define GFX_THREAD_FUNCTION(fnName, param)	gThreadreturn fnName(void *param)
#define GFX_THREAD_STACK(name, sz)			gU8 name[(sz) & ~3];
#define gfxThreadReturn(retval)				return retval

#define gDelayNone				0
#define gDelayForever			((gDelay)-1)
#define gSemMaxCount			0x7FFF
#define gThreadpriorityLow		0
#define gThreadpriorityNormal	1
#define gThreadpriorityHigh		2

typedef struct {
	gSemcount		cnt;
	gSemcount		limit;
} gSem;

typedef gU32		gMutex;
typedef void *			gThread;

// Required timing functions - supplied by the user or the operating system
gTicks gfxSystemTicks(void);
gTicks gfxMillisecondsToTicks(gDelay ms);

// Sleep Functions
void gfxSleepMilliseconds(gDelay ms);
void gfxSleepMicroseconds(gDelay ms);
void gfxYield(void);

// System Locking
void gfxSystemLock(void);
void gfxSystemUnlock(void);

// Mutexes
void gfxMutexInit(gMutex *pmutex);
#define gfxMutexDestroy(pmutex)
void gfxMutexEnter(gMutex *pmutex);
void gfxMutexExit(gMutex *pmutex);

// Semaphores
void gfxSemInit(gSem *psem, gSemcount val, gSemcount limit);
#define gfxSemDestroy(psem)
gBool gfxSemWait(gSem *psem, gDelay ms);
gBool gfxSemWaitI(gSem *psem);
void gfxSemSignal(gSem *psem);
void gfxSemSignalI(gSem *psem);

// Threads
gThread gfxThreadCreate(void *stackarea, gMemSize stacksz, gThreadpriority prio, GFX_THREAD_FUNCTION((*fn),p), void *param);
#define gfxThreadClose(thread)
gThreadreturn gfxThreadWait(gThread thread);
gThread gfxThreadMe(void);

/** The following is not part of the public ugfx API as some operating systems
 * 	simply do not provide this capability.
 * 	For RAW32 we need it anyway so we might as well declare it here.
 */
void gfxThreadExit(gThreadreturn ret);

#endif /* GOS_NEED_X_THREADS */
#endif /* _GOS_X_THREADS_H */
