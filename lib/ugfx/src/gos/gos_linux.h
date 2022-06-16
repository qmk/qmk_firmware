/*
 * This file is subject to the terms of the GFX License. If a copy of
 * the license was not distributed with this file, you can obtain one at:
 *
 *              http://ugfx.io/license.html
 */

#ifndef _GOS_LINUX_H
#define _GOS_LINUX_H

#if GFX_USE_OS_LINUX

// We don't put this in the general sys_options.h as it is Linux specific.
#ifndef GFX_USE_POSIX_SEMAPHORES
	#define GFX_USE_POSIX_SEMAPHORES	GFXON
#endif

#include <sys/types.h>
#include <stdlib.h>
#include <pthread.h>

#if GFX_USE_POSIX_SEMAPHORES
	#include <semaphore.h>
#endif

typedef unsigned long		gTicks;
typedef void *				gThreadreturn;
typedef unsigned long		gDelay;
typedef pthread_t 			gThread;
typedef int					gThreadpriority;
typedef gU32				gSemcount;
typedef pthread_mutex_t		gMutex;

#define GFX_THREAD_FUNCTION(fnName, param)	gThreadreturn fnName(void *param)
#define GFX_THREAD_STACK(name, sz)			gU8 name[0];
#define gfxThreadReturn(retval)				return retval

#define gfxExit()						exit(0)
#define gfxAlloc(sz)					malloc(sz)
#define gfxRealloc(p,osz,nsz)			realloc(p, nsz)
#define gfxFree(ptr)					free(ptr)
#define gfxMillisecondsToTicks(ms)		(ms)
#define gfxThreadMe()					pthread_self()
#define gfxThreadClose(th)				(void)th
#define gfxMutexInit(pmtx)				pthread_mutex_init(pmtx, 0)
#define gfxMutexDestroy(pmtx)			pthread_mutex_destroy(pmtx)
#define gfxMutexEnter(pmtx)				pthread_mutex_lock(pmtx)
#define gfxMutexExit(pmtx)				pthread_mutex_unlock(pmtx)
#define gfxSemWaitI(psem)				gfxSemWait(psem, gDelayNone)
#define gfxSemSignalI(psem)				gfxSemSignal(psem)

#define gDelayNone				0
#define gDelayForever			((gDelay)-1)
#define gSemMaxCount			((gSemcount)-1)
#define gThreadpriorityLow		10
#define gThreadpriorityNormal	0
#define gThreadpriorityHigh		-10

#if GFX_USE_POSIX_SEMAPHORES
	typedef struct gSem {
		sem_t			sem;
		gSemcount		max;
	} gSem;
#else
	typedef struct gSem {
		pthread_mutex_t	mtx;
		pthread_cond_t	cond;
		gSemcount		cnt;
		gSemcount		max;
	} gSem;
#endif

/*===========================================================================*/
/* Function declarations.                                                    */
/*===========================================================================*/

void gfxYield(void);
void gfxHalt(const char *msg);
void gfxSleepMilliseconds(gDelay ms);
void gfxSleepMicroseconds(gDelay ms);
gTicks gfxSystemTicks(void);
void gfxSystemLock(void);
void gfxSystemUnlock(void);
void gfxSemInit(gSem *psem, gSemcount val, gSemcount limit);
void gfxSemDestroy(gSem *psem);
gBool gfxSemWait(gSem *psem, gDelay ms);
void gfxSemSignal(gSem *psem);
gThread gfxThreadCreate(void *stackarea, gMemSize stacksz, gThreadpriority prio, GFX_THREAD_FUNCTION((*fn),p), void *param);
gThreadreturn gfxThreadWait(gThread thread);

#endif /* GFX_USE_OS_LINUX */

#endif /* _GOS_LINUX_H */
