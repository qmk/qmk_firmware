/*
 * This file is subject to the terms of the GFX License. If a copy of
 * the license was not distributed with this file, you can obtain one at:
 *
 *              http://ugfx.io/license.html
 */

#include "../../gfx.h"

#if GOS_NEED_X_THREADS

/*********************************************************
 * Semaphores and critical region functions
 *********************************************************/

#if !defined(INTERRUPTS_OFF) || !defined(INTERRUPTS_ON)
	#define INTERRUPTS_OFF()
	#define INTERRUPTS_ON()
#endif

void gfxSystemLock(void) {
	INTERRUPTS_OFF();
}

void gfxSystemUnlock(void) {
	INTERRUPTS_ON();
}

void gfxMutexInit(gMutex *pmutex) {
	pmutex[0] = 0;
}

void gfxMutexEnter(gMutex *pmutex) {
	INTERRUPTS_OFF();
	while (pmutex[0]) {
		INTERRUPTS_ON();
		gfxYield();
		INTERRUPTS_OFF();
	}
	pmutex[0] = 1;
	INTERRUPTS_ON();
}

void gfxMutexExit(gMutex *pmutex) {
	pmutex[0] = 0;
}

void gfxSemInit(gSem *psem, gSemcount val, gSemcount limit) {
	psem->cnt = val;
	psem->limit = limit;
}

gBool gfxSemWait(gSem *psem, gDelay ms) {
	gTicks	starttm, delay;

	// Convert our delay to ticks
	starttm = 0;
	switch (ms) {
	case gDelayNone:
		delay = gDelayNone;
		break;
	case gDelayForever:
		delay = gDelayForever;
		break;
	default:
		delay = gfxMillisecondsToTicks(ms);
		if (!delay) delay = 1;
		starttm = gfxSystemTicks();
	}

	INTERRUPTS_OFF();
	while (psem->cnt <= 0) {
		INTERRUPTS_ON();
		// Check if we have exceeded the defined delay
		switch (delay) {
		case gDelayNone:
			return gFalse;
		case gDelayForever:
			break;
		default:
			if (gfxSystemTicks() - starttm >= delay)
				return gFalse;
			break;
		}
		gfxYield();
		INTERRUPTS_OFF();
	}
	psem->cnt--;
	INTERRUPTS_ON();
	return gTrue;
}

gBool gfxSemWaitI(gSem *psem) {
	if (psem->cnt <= 0)
		return gFalse;
	psem->cnt--;
	return gTrue;
}

void gfxSemSignal(gSem *psem) {
	INTERRUPTS_OFF();
	gfxSemSignalI(psem);
	INTERRUPTS_ON();
}

void gfxSemSignalI(gSem *psem) {
	if (psem->cnt < psem->limit)
		psem->cnt++;
}

/*********************************************************
 * Sleep functions
 *********************************************************/

void gfxSleepMilliseconds(gDelay ms) {
	gTicks	starttm, delay;

	// Safety first
	switch (ms) {
	case gDelayNone:
		return;
	case gDelayForever:
		while(1)
			gfxYield();
		return;
	}

	// Convert our delay to ticks
	delay = gfxMillisecondsToTicks(ms);
	starttm = gfxSystemTicks();

	do {
		gfxYield();
	} while (gfxSystemTicks() - starttm < delay);
}

void gfxSleepMicroseconds(gDelay ms) {
	gTicks	starttm, delay;

	// Safety first
	switch (ms) {
	case gDelayNone:
		return;
	case gDelayForever:
		while(1)
			gfxYield();
		return;
	}

	// Convert our delay to ticks
	delay = gfxMillisecondsToTicks(ms/1000);
	starttm = gfxSystemTicks();

	do {
		gfxYield();
	} while (gfxSystemTicks() - starttm < delay);
}

/*********************************************************
 * Threading functions
 *********************************************************/

/** For each scheduler the following need to be defined...
 *
 * void _gfxThreadsInit(void);								- Initialise the scheduler
 * void _gfxStartThread(thread *oldt, thread *newt);		- Start a new thread
 * void _gfxTaskSwitch(thread *oldt, thread *newt);			- Switch to a different thread
 *
 */

typedef struct thread {
	struct thread *	next;					// Next thread
	int				flags;					// Flags
		#define FLG_THD_ALLOC	0x0001
		#define FLG_THD_MAIN	0x0002
		#define FLG_THD_DEAD	0x0004
		#define FLG_THD_WAIT	0x0008
	gMemSize		size;					// Size of the thread stack (including this structure)
	gThreadreturn	(*fn)(void *param);		// Thread function
	void *			param;					// Parameter for the thread function
	void *			cxt;					// The current thread context.
	} thread;

typedef struct threadQ {
	thread *head;
	thread *tail;
} threadQ;

static threadQ		readyQ;					// The list of ready threads
static threadQ		deadQ;					// Where we put threads waiting to be deallocated
thread *			_gfxCurrentThread;		// The current running thread - unfortunately this has to be non-static for the keil compiler
static thread		mainthread;				// The main thread context

#undef GFX_THREADS_DONE

#if GFX_CPU == GFX_CPU_CORTEX_M0 || GFX_CPU == GFX_CPU_CORTEX_M1
	#include "gos_x_threads_cortexm01.h"
#elif GFX_CPU == GFX_CPU_CORTEX_M3 || GFX_CPU == GFX_CPU_CORTEX_M4 || GFX_CPU == GFX_CPU_CORTEX_M7
	#include "gos_x_threads_cortexm347.h"
#elif GFX_CPU == GFX_CPU_CORTEX_M4_FP || GFX_CPU == GFX_CPU_CORTEX_M7_FP
	#include "gos_x_threads_cortexm47fp.h"
#endif

#ifndef GFX_THREADS_DONE
	#define GFX_THREADS_DONE

	#include <string.h>				// Prototype for memcpy()
	#include <setjmp.h>

	/**
	 * Some compilers define a _setjmp() and a setjmp().
	 * The difference between them is that setjmp() saves the signal masks.
	 * That is of no use to us so we prefer to use the _setjmp() methods.
	 * If they don't exist compile them to be the standard setjmp() function.
	 * Similarly for longjmp().
	 */
	#if (!defined(setjmp) && !defined(_setjmp)) || GFX_COMPILER == GFX_COMPILER_KEIL || GFX_COMPILER == GFX_COMPILER_MINGW32 || GFX_COMPILER == GFX_COMPILER_MINGW64
		#define CXT_SAVE 		setjmp
	#else
		#define CXT_SAVE 		_setjmp
	#endif
	#if (!defined(longjmp) && !defined(_longjmp)) || GFX_COMPILER == GFX_COMPILER_KEIL || GFX_COMPILER == GFX_COMPILER_MINGW32 || GFX_COMPILER == GFX_COMPILER_MINGW64
		#define CXT_RESTORE 	longjmp
	#else
		#define CXT_RESTORE 	_longjmp
	#endif

	// A place to store the main thread context.
	// All other threads will store the context directly after the thread structure (as part of the stack space).
	static jmp_buf				maincxt;

	/**
	 * There are some compilers we know how they store the jmpbuf. For those
	 * we can use the constant macro definitions. For others we have to "auto-detect".
	 * Auto-detection is hairy and there is no guarantee it will work on all architectures.
	 * For those it doesn't - read the compiler manuals and the library source code to
	 * work out the correct macro values.
	 * You can use the debugger to work out the values for your compiler and put them here.
	 * Defining these macros as constant values makes the system behaviour guaranteed but also
	 * makes your code compiler and cpu architecture dependent. It also saves a heap of code
	 * and a few bytes of RAM.
	 *
	 * MACROS:
	 *
	 *	AUTO_DETECT_STACKFRAME	GFXON/GFXOFF			- GFXON to auto-detect stack frame structure
	 *	STACK_DIR_UP			Macro/gBool		- GFXON if the stack grows up instead of down
	 *	MASK1					Macro/gU32		- The 1st mask of jmp_buf elements that need relocation
	 *	MASK2					Macro/gU32		- The 2nd mask of jmp_buf elements that need relocation
	 *	STACK_BASE				Macro/gMemSize		- The base of the stack frame relative to the local variables
	 *	_gfxThreadsInit()		Macro/Function		- Initialise the scheduler
	 *
	 */
	#if GFX_COMPILER == GFX_COMPILER_MINGW32

		#define AUTO_DETECT_STACKFRAME	GFXOFF
		#define STACK_DIR_UP		GFXOFF
		#define MASK1				0x00000011
		#define MASK2				0x00000000
		#define STACK_BASE			12
		#define _gfxThreadsInit()	mainthread.cxt = maincxt

	#else

		// Use auto-detection of the stack frame format
		// Assumes all the relevant stuff to be relocated is in the first 256 bytes of the jmpbuf.
		#define AUTO_DETECT_STACKFRAME	GFXON
		#define STACK_DIR_UP		stackdirup			// GFXON if the stack grow up instead of down
		#define MASK1				jmpmask1			// The 1st mask of jmp_buf elements that need relocation
		#define MASK2				jmpmask2			// The 2nd mask of jmp_buf elements that need relocation
		#define STACK_BASE			stackbase			// The base of the stack frame relative to the local variables

		// The structure for the saved stack frame information
		typedef struct saveloc {
			char *		localptr;
			jmp_buf		cxt;
		} saveloc;

		static gBool		stackdirup;
		static gU32		jmpmask1;
		static gU32		jmpmask2;
		static gMemSize		stackbase;
		static saveloc		*pframeinfo;

		// These two functions are not static to prevent the compiler removing them as functions
		void _gfxGetStackState(void) {
			char *c;
			pframeinfo->localptr = (char *)&c;
			CXT_SAVE(pframeinfo->cxt);
		}
		void _gfxGetStackStateInFn(void) {
			pframeinfo++;
			_gfxGetStackState();
			pframeinfo--;
		}
		static void _gfxThreadsInit(void) {
			gU32	i;
			char **		pout;
			char **		pin;
			gPtrDiff	diff;
			char *		framebase;
			saveloc		tmpsaveloc[2];

			// Create the main thread context
			mainthread.cxt = maincxt;

			// Allocate a buffer to store our test data
			pframeinfo = tmpsaveloc;

			// Get details of the stack frame from within a function
			_gfxGetStackStateInFn();

			// Get details of the stack frame outside the function
			_gfxGetStackState();

			/* Work out the frame entries to relocate by treating the jump buffer as an array of pointers */
			stackdirup =  pframeinfo[1].localptr > pframeinfo[0].localptr;
			pout = (char **)pframeinfo[0].cxt;
			pin =  (char **)pframeinfo[1].cxt;
			diff = pframeinfo[0].localptr - pframeinfo[1].localptr;
			framebase = pframeinfo[0].localptr;
			jmpmask1 = jmpmask2 = 0;
			for (i = 0; i < sizeof(jmp_buf)/sizeof(char *); i++, pout++, pin++) {
				if ((gPtrDiff)(*pout - *pin) == diff) {
					if (i < 32)
						jmpmask1 |= 1 << i;
					else
						jmpmask2 |= 1 << (i-32);

					if (stackdirup) {
						if (framebase > *pout)
							framebase = *pout;
					} else {
						if (framebase < *pout)
							framebase = *pout;
					}
				}
			}
			stackbase = stackdirup ? (pframeinfo[0].localptr - framebase) : (framebase - pframeinfo[0].localptr);
		}

	#endif

	// Move the stack frame and relocate the context data
	static void _gfxAdjustCxt(thread *t) {
		char **	s;
		char *	nf;
		int		diff;
		gU32	i;

		// Copy the stack frame
		s = 0;
		#if AUTO_DETECT_STACKFRAME
			if (STACK_DIR_UP) {					// Stack grows up
				nf = (char *)(t) + sizeof(thread) + sizeof(jmp_buf) + STACK_BASE;
				memcpy(t+1, (char *)&s - STACK_BASE, STACK_BASE+sizeof(char *));
			} else {							// Stack grows down
				nf = (char *)(t) + t->size - (STACK_BASE + sizeof(char *));
				memcpy(nf, &s, STACK_BASE+sizeof(char *));
			}
		#elif STACK_DIR_UP
			// Stack grows up
			nf = (char *)(t) + sizeof(thread) + sizeof(jmp_buf) + STACK_BASE;
			memcpy(t+1, (char *)&s - STACK_BASE, STACK_BASE+sizeof(char *));
		#else
			// Stack grows down
			nf = (char *)(t) + t->size - (STACK_BASE + sizeof(char *));
			memcpy(nf, &s, STACK_BASE+sizeof(char *));
		#endif

		// Relocate the context data
		s = (char **)(t->cxt);
		diff = nf - (char *)&s;

		// Relocate the elements we know need to be relocated
		for (i = MASK1; i ; i >>= 1, s++) {
			if ((i & 1))
				*s += diff;
		}
		#ifdef MASK2
			s = (char **)(t->cxt)+32;
			for (i = MASK2; i ; i >>= 1, s++) {
				if ((i & 1))
					*s += diff;
			}
		#endif
	}
	static void _gfxXSwitch(thread *oldt, thread *newt, gBool doBuildFrame) {

		// Save the old context
		if (CXT_SAVE(oldt->cxt)) return;

		// Do we need to build a new context?
		if (doBuildFrame) {

			// Save our existing context as a starting point for the new context
			newt->cxt = newt+1;
			if (CXT_SAVE(newt->cxt)) {

				// We are now running the new thread

				// We can't use any of the above function parameters here
				//	as we are on a different stack.

				// Run the users function.
				gfxThreadExit(_gfxCurrentThread->fn(_gfxCurrentThread->param));

				// We never get here as gfxThreadExit() never returns
			}

			// Adjust the new context so the stack references are correct
			_gfxAdjustCxt(newt);
		}

		// Start the new context
		CXT_RESTORE(newt->cxt, 1);
	}

	#define _gfxTaskSwitch(oldt, newt)		_gfxXSwitch(oldt, newt, gFalse)
	#define _gfxStartThread(oldt, newt)		_gfxXSwitch(oldt, newt, gTrue)
#endif
#undef GFX_THREADS_DONE

static void Qinit(threadQ * q) {
	q->head = q->tail = 0;
}

static void Qadd(threadQ * q, thread *t) {
	t->next = 0;
	if (q->head) {
		q->tail->next = t;
		q->tail = t;
	} else
		q->head = q->tail = t;
}

static thread *Qpop(threadQ * q) {
	struct thread * t;

	if (!q->head)
		return 0;
	t = q->head;
	q->head = t->next;
	return t;
}

void _gosThreadsInit(void) {
	Qinit(&readyQ);

	mainthread.next = 0;
	mainthread.size = sizeof(thread);
	mainthread.flags = FLG_THD_MAIN;
	mainthread.fn = 0;
	mainthread.param = 0;

	_gfxThreadsInit();

	_gfxCurrentThread = &mainthread;
}

gThread gfxThreadMe(void) {
	return (gThread)_gfxCurrentThread;
}

// Check if there are dead processes to deallocate
static void cleanUpDeadThreads(void) {
	thread *p;

	while ((p = Qpop(&deadQ)))
		gfxFree(p);
}

void gfxYield(void) {
	thread	*me;

	// Clean up zombies
	cleanUpDeadThreads();

	// Is there another thread to run?
	if (!readyQ.head)
		return;

	Qadd(&readyQ, me = _gfxCurrentThread);
	_gfxCurrentThread = Qpop(&readyQ);
	_gfxTaskSwitch(me, _gfxCurrentThread);
}

// This routine is not currently public - but it could be.
void gfxThreadExit(gThreadreturn ret) {
	thread	*me;

	// Save the results in case someone is waiting
	me = _gfxCurrentThread;
	me->param = (void *)ret;
	me->flags |= FLG_THD_DEAD;

	// Add us to the dead list if we need deallocation as we can't free ourselves.
	// If someone is waiting on the thread they will do the cleanup.
	if ((me->flags & (FLG_THD_ALLOC|FLG_THD_WAIT)) == FLG_THD_ALLOC)
		Qadd(&deadQ, me);

	// Set the next thread. Exit if it was the last thread
	if (!(_gfxCurrentThread = Qpop(&readyQ)))
		gfxExit();

	// Switch to the new thread
	_gfxTaskSwitch(me, _gfxCurrentThread);

	// We never get back here as we didn't re-queue ourselves
}

gThread gfxThreadCreate(void *stackarea, gMemSize stacksz, gThreadpriority prio, GFX_THREAD_FUNCTION((*fn),p), void *param) {
	thread *	t;
	thread *	me;
	(void)		prio;

	// Ensure we have a minimum stack size
	if (stacksz < sizeof(thread)+64) {
		stacksz = sizeof(thread)+64;
		stackarea = 0;
	}

	if (stackarea) {
		t = (thread *)stackarea;
		t->flags = 0;
	} else {
		t = (thread *)gfxAlloc(stacksz);
		if (!t)
			return 0;
		t->flags = FLG_THD_ALLOC;
	}
	t->size = stacksz;
	t->fn = fn;
	t->param = param;

	// Add the current thread to the queue because we are starting a new thread.
	me = _gfxCurrentThread;
	Qadd(&readyQ, me);
	_gfxCurrentThread = t;

	_gfxStartThread(me, t);

	// Return the new thread handle
	return t;
}

gThreadreturn gfxThreadWait(gThread th) {
	thread *		t;

	t = th;
	if (t == _gfxCurrentThread)
		return -1;

	// Mark that we are waiting
	t->flags |= FLG_THD_WAIT;

	// Wait for the thread to die
	while(!(t->flags & FLG_THD_DEAD))
		gfxYield();

	// Unmark
	t->flags &= ~FLG_THD_WAIT;

	// Clean up resources if needed
	if (t->flags & FLG_THD_ALLOC)
		gfxFree(t);

	// Return the status left by the dead process
	return (gThreadreturn)t->param;
}

#endif
