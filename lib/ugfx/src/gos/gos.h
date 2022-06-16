/*
 * This file is subject to the terms of the GFX License. If a copy of
 * the license was not distributed with this file, you can obtain one at:
 *
 *              http://ugfx.io/license.html
 */

/**
 * @file    src/gos/gos.h
 * @brief   GOS - Operating System Support header file
 *
 * @addtogroup GOS
 *
 * @brief	Module to build a uniform abstraction layer between uGFX and the underlying system
 *
 * @note	Some of the routines specified below may be implemented simply as
 * 			a macro to the real operating system call.
 * @{
 */

#ifndef _GOS_H
#define _GOS_H

#if defined(__DOXYGEN__)
	/*===========================================================================*/
	/* Type definitions                                                          */
	/*===========================================================================*/

	/**
	 * @name	Various integer sizes
	 * @note	Your platform may define these differently to these.
	 * @note	These sizes are guaranteed minimum sizes for the type. It might actually be larger.
	 *			eg gI8 may actually be 9 bits.
	 * @{
	 */
	typedef unsigned char	gBool;
	typedef signed char		gI8;
	typedef unsigned char	gU8;
	typedef short			gI16;
	typedef unsigned short	gU16;
	typedef long			gI32;
	typedef unsigned long	gU32;
	/** @} */
	
	/**
	 * @name	More integer sizes
	 * @pre		These are only available if GFX_TYPE_64 is GFXON as not all compilers support 64 bit.
	 * @note	GFX_TYPE_64 is set to GFXON or GFXOFF by the compiler detector. It is not a user configuration macro.
	 * @{
	 */
	typedef long long			gI64;
	typedef unsigned long long	gU64;
	/** @} */

	/**
	 * @name	Various platform (and operating system) dependent types
	 * @note	Your platform may use slightly different definitions to these
	 * @{
	 */
	typedef unsigned long	gDelay;
	typedef unsigned long	gTicks;
	typedef short			gSemcount;
	typedef int				gThreadreturn;
	typedef int				gThreadpriority;
	/** @} */

	/**
	 * @brief	Declare a thread function
	 *
	 * @param[in] fnName	The name of the function
	 * @param[in] param 	A custom parameter that is passed to the function
	 */
	#define GFX_THREAD_FUNCTION(fnName, param)	gThreadreturn fnName(void *param)

	/**
	 * @brief	Declare a thread stack
	 *
	 * @param[in] name 		The name of the stack
	 * @param[in] sz 		The size of the stack in bytes
	 *
	 * @note	The size provided is just a suggestion to the required stack size.
	 * 			Many platforms will round the size to ensure correct stack alignment.
	 *			Other platforms may entirely ignore the suggested size.
	 */
	#define GFX_THREAD_STACK(name, sz)			gU8 name[sz];

	/**
	 * @name	Various platform (and operating system) constants
	 * @note	Your platform may use slightly different definitions to these
	 * @{
	 */
	#define gDelayNone					0
	#define gDelayForever				((gDelay)-1)
	#define gSemMaxCount				((gSemcount)(((unsigned long)((gSemcount)(-1))) >> 1))
	#define gThreadpriorityLow			0
	#define gThreadpriorityNormal		1
	#define gThreadpriorityHigh			2
	/** @} */

	/**
	 * @brief	A semaphore
	 * @note	Your operating system will have a proper definition for this structure
	 */
	typedef struct {} gSem;

	/**
	 * @brief	A mutex
	 * @note	Your operating system will have a proper definition for this structure
	 */
	typedef struct {} gMutex;

	/**
	 * @brief	A thread handle
	 * @note	Your operating system will have a proper definition for this.
	 */
	typedef void * gThread;

	/*===========================================================================*/
	/* Function declarations.                                                    */
	/*===========================================================================*/

	/**
	 * @brief	Halt the GFX application due to an error.
	 *
	 * @param[in] msg	An optional debug message to show (Can be NULL)
	 *
	 * @api
	 */
	void gfxHalt(const char *msg);

	/**
	 * @brief	Exit the GFX application.
	 *
	 * @api
	 */
	void gfxExit(void);

	/**
	 * @brief	Allocate memory
	 * @return	A pointer to the memory allocated or NULL if there is no more memory available
	 *
	 * @param[in] sz	The size in bytes of the area to allocate
	 *
	 * @api
	 */
	void *gfxAlloc(gMemSize sz);

	/**
	 * @brief	Re-allocate memory
	 * @return	A pointer to the new memory area or NULL if there is no more memory available
	 *
	 * @param[in] ptr		The old memory area to be increased/decreased in size
	 * @param[in] oldsz		The size in bytes of the old memory area
	 * @param[in] newsz		The size in bytes of the new memory area
	 *
	 * @note		Some operating systems don't use the oldsz parameter as they implicitly know the size of
	 * 				old memory area. The parameter must always be supplied however for API compatibility.
	 * @note		gfxRealloc() can make the area smaller or larger but may have to return a different pointer.
	 * 				If this occurs the new area contains a copy of the data from the old area. The old memory
	 * 				pointer should not be used after this routine as the original area may have been freed.
	 * @note		If there is insufficient memory to create the new memory region, NULL is returned and the
	 * 				old memory area is left unchanged.
	 *
	 * @api
	 */
	void *gfxRealloc(void *ptr, gMemSize oldsz, gMemSize newsz);

	/**
	 * @brief	Free memory
	 *
	 * @param[in] ptr	The memory to free
	 *
	 * @api
	 */
	void gfxFree(void *ptr);

	/**
	 * @brief	Use gfxAlloc and gfxFree to implement malloc() and free()
	 *
	 * @note	Sometimes your application will include functions that
	 * 			want to internally use malloc() and free(). As the default
	 * 			implementations of these in your C library are almost
	 * 			invariably incorrect for an embedded platform, this option
	 * 			allows you to emulate those calls with gfxAlloc() and gfxFree().
	 *			An example is the C library routine rand() which on many
	 *			implementations internally uses malloc().
	 *
	 * @api
	 */
	#ifndef GFX_EMULATE_MALLOC
		#define GFX_EMULATE_MALLOC			GFXOFF
	#endif

	/**
	 * @brief	Yield the current thread
	 * @details	Give up the rest of the current time slice for this thread in order to give other threads
	 * 			a chance to run.
	 *
	 * @api
	 */
	void gfxYield(void);

	/**
	 * @brief	Put the current thread to sleep for the specified period in milliseconds
	 *
	 * @param[in] ms	The number milliseconds to sleep
	 *
	 * @note		Specifying gDelayNone will yield the current thread but return
	 * 				on the next time slice.
	 * @note		Specifying gDelayForever will sleep forever.
	 *
	 * @api
	 */
	void gfxSleepMilliseconds(gDelay ms);

	/**
	 * @brief	Put the current thread to sleep for the specified period in microseconds
	 *
	 * @param[in] us	The number microseconds to sleep
	 *
	 * @note		Specifying gDelayNone will return immediately (no sleeping)
	 * @note		Specifying gDelayForever will sleep forever.
	 *
	 * @api
	 */
	void gfxSleepMicroseconds(gDelay us);

	/**
	 * @brief	Get the current operating system tick time
	 * @return	The current tick time
	 *
	 * @note	A "tick" is an arbitrary period of time that the operating
	 * 			system uses to mark time.
	 * @note	The absolute value of this call is relatively meaningless. Its usefulness
	 * 			is in calculating periods between two calls to this function.
	 * @note	As the value from this function can wrap it is important that any periods are calculated
	 * 			as t2 - t1 and then compared to the desired period rather than comparing
	 * 			t1 + period to t2
	 *
	 * @api
	 */
	gTicks gfxSystemTicks(void);

	/**
	 * @brief	Convert a given number of millseconds to a number of operating system ticks
	 * @return	The period in system ticks.
	 *
	 * @note	A "tick" is an arbitrary period of time that the operating
	 * 			system uses to mark time.
	 *
	 * @param[in] ms	The number of millseconds
	 *
	 * @api
	 */
	gTicks gfxMillisecondsToTicks(gDelay ms);

	/**
	 * @brief	Lock the operating system to protect a sequence of code
	 *
	 * @note	Calling this will lock out all other threads from executing even at interrupt level
	 * 			within the GFX system. On hardware this may be implemented as a disabling of interrupts,
	 * 			however in an operating system which hides real interrupt level code it may simply use a
	 * 			mutex lock.
	 * @note	The thread MUST NOT block whilst the system is locked. It must execute in this state for
	 * 			as short a period as possible as this can seriously affect interrupt latency on some
	 * 			platforms.
	 * @note	While locked only interrupt level (iclass) GFX routines may be called.
	 *
	 * @api
	 */
	void gfxSystemLock(void);

	/**
	 * @brief	Unlock the operating system previous locked by gfxSystemLock()
	 *
	 * @api
	 */
	void gfxSystemUnlock(void);

	/**
	 * @brief	Initialise a mutex to protect a region of code from other threads.
	 *
	 * @param[in]	pmutex	A pointer to the mutex
	 *
	 * @note	Whilst a counting semaphore with a limit of 1 can be used for similiar purposes
	 * 			on many operating systems using a seperate mutex structure is more efficient.
	 *
	 * @api
	 */
	void gfxMutexInit(gMutex *pmutex);

	/**
	 * @brief	Destroy a Mutex.
	 *
	 * @param[in]	pmutex	A pointer to the mutex
	 *
	 * @api
	 */
	void gfxMutexDestroy(gMutex *pmutex);

	/**
	 * @brief	Enter the critical code region protected by the mutex.
	 * @details	Blocks until there is no other thread in the critical region.
	 *
	 * @param[in]	pmutex	A pointer to the mutex
	 *
	 * @api
	 */
	void gfxMutexEnter(gMutex *pmutex);

	/**
	 * @brief	Exit the critical code region protected by the mutex.
	 * @details	May cause another thread waiting on the mutex to now be placed into the run queue.
	 *
	 * @param[in]	pmutex	A pointer to the mutex
	 *
	 * @api
	 */
	void gfxMutexExit(gMutex *pmutex);

	/**
	 * @brief	Initialise a Counted Semaphore
	 *
	 * @param[in] psem		A pointer to the semaphore
	 * @param[in] val		The initial value of the semaphore
	 * @param[in] limit		The maxmimum value of the semaphore
	 *
	 * @note	Operations defined for counted semaphores:
	 * 				Signal: The semaphore counter is increased and if the result is non-positive then a waiting thread
	 * 						 is queued for execution. Note that once the thread reaches "limit", further signals are
	 * 						 ignored.
	 * 				Wait: The semaphore counter is decreased and if the result becomes negative the thread is queued
	 * 						in the semaphore and suspended.
	 *
	 * @api
	 */
	void gfxSemInit(gSem *psem, gSemcount val, gSemcount limit);

	/**
	 * @brief	Destroy a Counted Semaphore
	 *
	 * @param[in] psem		A pointer to the semaphore
	 *
	 * @note	Any threads waiting on the semaphore will be released
	 *
	 * @api
	 */
	void gfxSemDestroy(gSem *psem);

	/**
	 * @brief	Wait on a semaphore
	 * @details	The semaphore counter is decreased and if the result becomes negative the thread waits for it to become
	 * 				non-negative again
	 * @return	gFalse if the wait timeout occurred otherwise gTrue
	 *
	 * @param[in] psem		A pointer to the semaphore
	 * @param[in] ms		The maximum time to wait for the semaphore
	 *
	 * @api
	 */
	gBool gfxSemWait(gSem *psem, gDelay ms);

	/**
	 * @brief	Test if a wait on a semaphore can be satisfied immediately
	 * @details	Equivalent to @p gfxSemWait(psem, gDelayNone) except it can be called at interrupt level
	 * @return	gFalse if the wait would occur occurred otherwise gTrue
	 *
	 * @param[in] psem		A pointer to the semaphore
	 *
	 * @iclass
	 * @api
	 */
	gBool gfxSemWaitI(gSem *psem);

	/**
	 * @brief	Signal a semaphore
	 * @details	The semaphore counter is increased and if the result is non-positive then a waiting thread
	 * 						 is queued for execution. Note that once the thread reaches "limit", further signals are
	 * 						 ignored.
	 *
	 * @param[in] psem		A pointer to the semaphore
	 *
	 * @api
	 */
	void gfxSemSignal(gSem *psem);

	/**
	 * @brief	Signal a semaphore
	 * @details	The semaphore counter is increased and if the result is non-positive then a waiting thread
	 * 						 is queued for execution. Note that once the thread reaches "limit", further signals are
	 * 						 ignored.
	 *
	 * @param[in] psem		A pointer to the semaphore
	 *
	 * @iclass
	 * @api
	 */
	void gfxSemSignalI(gSem *psem);

	/**
	 * @brief	Start a new thread.
	 * @return	Returns a thread handle if the thread was started, NULL on an error
	 *
	 * @param[in]	stackarea	A pointer to the area for the new threads stack or NULL to dynamically allocate it
	 * @param[in]	stacksz		The size of the thread stack. 0 means the default operating system size although this
	 * 							is only valid when stackarea is dynamically allocated.
	 * @param[in]	prio		The priority of the new thread
	 * @param[in]	fn			The function the new thread will run
	 * @param[in]	param		A parameter to pass the thread function.
	 *
	 * @api
	 */
	gThread gfxThreadCreate(void *stackarea, gMemSize stacksz, gThreadpriority prio, GFX_THREAD_FUNCTION((*fn),p), void *param);

	/**
	 * @brief	Wait for a thread to finish.
	 * @return	Returns the thread exit code.
	 *
	 * @param[in]	thread		The Thread Handle
	 *
	 * @note		This will also close the thread handle as it is no longer useful
	 * 				once the thread has ended.
	 * @api
	 */
	gThreadreturn gfxThreadWait(gThread thread);

	/**
	 * @brief	Get the current thread handle.
	 * @return	A thread handle
	 *
	 * @api
	 */
	gThread gfxThreadMe(void);

	/**
	 * @brief	Close the thread handle.
	 *
	 * @param[in]	thread		The Thread Handle
	 *
	 * @note	This does not affect the thread, it just closes our handle to the thread.
	 *
	 * @api
	 */
	void gfxThreadClose(gThread thread);

	/*
	 * @brief	Return from a thread
	 *
	 * @details	Some underlying operating systems allow to return a value from a thread while others don't.
	 *			For systems that don't allow to return a value from a thread function this call is simply ignored.
	 * @pre		This pseudo function can only be called within the main body of the thread function (not a sub-function)
	 *
	 * @param[in] reval		The value which should be returned
	 */
	#define gfxThreadReturn(retval)				return retval

/**
 * All the above was just for the doxygen documentation. All the implementation of the above
 * (without any of the documentation overheads) is in the files below.
 */
#elif GFX_USE_OS_RAWRTOS
 	#include "gos_rawrtos.h"
#elif GFX_USE_OS_CHIBIOS
	#include "gos_chibios.h"
#elif GFX_USE_OS_FREERTOS
	#include "gos_freertos.h"
#elif GFX_USE_OS_WIN32
	#include "gos_win32.h"
#elif GFX_USE_OS_LINUX
	#include "gos_linux.h"
#elif GFX_USE_OS_OSX
	#include "gos_osx.h"
#elif GFX_USE_OS_RAW32
	#include "gos_raw32.h"
#elif GFX_USE_OS_ECOS
	#include "gos_ecos.h"
#elif GFX_USE_OS_ARDUINO
	#include "gos_arduino.h"
#elif GFX_USE_OS_CMSIS
 	#include "gos_cmsis.h"
#elif GFX_USE_OS_CMSIS2
 	#include "gos_cmsis2.h"
#elif GFX_USE_OS_KEIL
    #include "gos_keil.h"
#elif GFX_USE_OS_RTX5
    #include "gos_rtx5.h"
#elif GFX_USE_OS_NIOS
    #include "gos_nios.h"
#elif GFX_USE_OS_ZEPHYR
	#include "gos_zephyr.h"
#elif GFX_USE_OS_QT
    #include "gos_qt.h"
#else
	#error "Your operating system is not supported yet"
#endif

#if GFX_COMPAT_V2
	typedef gDelay			delaytime_t;
		#if !GFX_USE_OS_CHIBIOS
			// These values are defined by ChibiOS itself
			#define TIME_IMMEDIATE	gDelayNone
			#define TIME_INFINITE	gDelayForever
		#endif
	typedef gTicks			systemticks_t;
	typedef gThread			gfxThreadHandle;
		#define DECLARE_THREAD_FUNCTION	GFX_THREAD_FUNCTION
		#define DECLARE_THREAD_STACK	GFX_THREAD_STACK
	typedef gThreadreturn	threadreturn_t;
		#define THREAD_RETURN		gfxThreadReturn
	typedef gThreadpriority	threadpriority_t;
		#define LOW_PRIORITY		gThreadpriorityLow
		#define NORMAL_PRIORITY		gThreadpriorityNormal
		#define HIGH_PRIORITY		gThreadpriorityHigh
	typedef gSem			gfxSem;
		#define MAX_SEMAPHORE_COUNT	gSemMaxCount
	typedef gMutex			gfxMutex;
#endif

#endif /* _GOS_H */
/** @} */
