/*
 * This file is subject to the terms of the GFX License. If a copy of
 * the license was not distributed with this file, you can obtain one at:
 *
 *              http://ugfx.io/license.html
 */

// We need to include stdio.h below. Turn off GFILE_NEED_STDIO just for this file to prevent conflicts
#define GFILE_NEED_STDIO_MUST_BE_OFF

#include "../../gfx.h"

#if GFX_USE_OS_OSX

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>
#include <sys/time.h>
#include <sched.h>
#include <mach/clock.h>
#include <mach/mach.h>

static gMutex		SystemMutex;

void _gosInit(void)
{
	/* No initialization of the operating system itself is needed */
	gfxMutexInit(&SystemMutex);
}

void _gosPostInit(void)
{
}

void _gosDeinit(void)
{
	/* ToDo */
}

void gfxSystemLock(void) {
	gfxMutexEnter(&SystemMutex);
}

void gfxSystemUnlock(void) {
	gfxMutexExit(&SystemMutex);
}

void gfxHalt(const char *msg) {
	if (msg)
		fprintf(stderr, "%s\n", msg);
	exit(1);
}

void gfxSleepMilliseconds(gDelay ms) {
	struct timespec	ts;

	switch(ms) {
	case gDelayNone:	gfxYield();			return;
	case gDelayForever:		while(1) sleep(60);			return;
	default:
		ts.tv_sec = ms / 1000;
		ts.tv_nsec = (ms % 1000) * 1000000;
		nanosleep(&ts, 0);
		return;
	}
}

void gfxSleepMicroseconds(gDelay us) {
	struct timespec	ts;

	switch(us) {
	case gDelayNone:	gfxYield();			return;
	case gDelayForever:		while(1) sleep(60);			return;
	default:
		ts.tv_sec = us / 1000000;
		ts.tv_nsec = (us % 1000000) * 1000;
		nanosleep(&ts, 0);
		return;
	}
}

gTicks gfxSystemTicks(void) {
	mach_timespec_t	ts;
	clock_serv_t	cclock;

	host_get_clock_service(mach_host_self(), SYSTEM_CLOCK, &cclock);
	clock_get_time(cclock, &ts);
	mach_port_deallocate(mach_task_self(), cclock);

	return ts.tv_sec * 1000UL + ts.tv_nsec / 1000000;
}

gThread gfxThreadCreate(void *stackarea, gMemSize stacksz, gThreadpriority prio, GFX_THREAD_FUNCTION((*fn),p), void *param) {
	gThread		th;
	(void)				stackarea;
	(void)				stacksz;
	(void)				prio;

	// Implementing priority with pthreads is a rats nest that is also pthreads implementation dependent.
	//	Only some pthreads schedulers support it, some implementations use the operating system process priority mechanisms.
	//	Even those that do support it can have different ranges of priority and "normal" priority is an undefined concept.
	//	Across different UNIX style operating systems things can be very different (let alone OS's such as Windows).
	//	Even just Linux changes the way priority works with different kernel schedulers and across kernel versions.
	//	For these reasons we ignore the priority.

	if (pthread_create(&th, 0, fn, param))
		return 0;
	return th;
}

gThreadreturn gfxThreadWait(gThread thread) {
	gThreadreturn	retval;

	if (pthread_join(thread, &retval))
		return 0;
	return retval;
}

void gfxSemInit(gSem *pSem, gSemcount val, gSemcount limit) {
	pthread_mutex_init(&pSem->mtx, 0);
	pthread_cond_init(&pSem->cond, 0);
	pthread_mutex_lock(&pSem->mtx);
	pSem->cnt = val;
	pSem->max = limit;
	pthread_mutex_unlock(&pSem->mtx);
}

void gfxSemDestroy(gSem *pSem) {
	pthread_mutex_destroy(&pSem->mtx);
	pthread_cond_destroy(&pSem->cond);
}

gBool gfxSemWait(gSem *pSem, gDelay ms) {
	pthread_mutex_lock(&pSem->mtx);
	switch (ms) {
	case gDelayForever:
		while (!pSem->cnt)
			pthread_cond_wait(&pSem->cond, &pSem->mtx);
		break;
	case gDelayNone:
		if (!pSem->cnt) {
			pthread_mutex_unlock(&pSem->mtx);
			return gFalse;
		}
		break;
	default:
		{
			struct timeval now;
			struct timespec	tm;

			gettimeofday(&now, 0);
			tm.tv_sec = now.tv_sec + ms / 1000;
			tm.tv_nsec = now.tv_usec * 1000 + (ms % 1000) * 1000000;
			while (!pSem->cnt) {
				// We used to test the return value for ETIMEDOUT. This doesn't
				//	work in some current pthread libraries which return -1 instead
				//	and set errno to ETIMEDOUT. So, we will return gFalse on any error
				//	including a ETIMEDOUT.
				if (pthread_cond_timedwait(&pSem->cond, &pSem->mtx, &tm)) {
					pthread_mutex_unlock(&pSem->mtx);
					return gFalse;
				}
			}
		}
		break;
	}
	pSem->cnt--;
	pthread_mutex_unlock(&pSem->mtx);
	return gTrue;
}

void gfxSemSignal(gSem *pSem) {
	pthread_mutex_lock(&pSem->mtx);
	if (pSem->cnt < pSem->max) {
		pSem->cnt++;
		pthread_cond_signal(&pSem->cond);
	}
	pthread_mutex_unlock(&pSem->mtx);
}

#endif /* GFX_USE_OS_OSX */
