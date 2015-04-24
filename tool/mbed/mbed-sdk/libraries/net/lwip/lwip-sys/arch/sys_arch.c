/* Copyright (C) 2012 mbed.org, MIT License
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 * and associated documentation files (the "Software"), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge, publish, distribute,
 * sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or
 * substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 * BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
#include <string.h>

/* mbed includes */
#include "mbed_error.h"
#include "mbed_interface.h"
#include "us_ticker_api.h"

/* lwIP includes. */
#include "lwip/opt.h"
#include "lwip/debug.h"
#include "lwip/def.h"
#include "lwip/sys.h"
#include "lwip/mem.h"

 #if NO_SYS==1
#include "cmsis.h"

/* Saved total time in ms since timer was enabled */
static volatile u32_t systick_timems;

/* Enable systick rate and interrupt */
void SysTick_Init(void) {
    if (SysTick_Config(SystemCoreClock / 1000)) {
        while (1);     /* Capture error */
    }
}

/** \brief  SysTick IRQ handler and timebase management
 *
 *  This function keeps a timebase for the sysTick that can be
 * used for other functions. It also calls an external function
 * (SysTick_User) that must be defined outside this handler.
 */
void SysTick_Handler(void) {
    systick_timems++;
}

/* Delay for the specified number of milliSeconds */
void osDelay(uint32_t ms) {
    uint32_t to = ms + systick_timems;
    while (to > systick_timems);
}

/* Returns the current time in mS. This is needed for the LWIP timers */
u32_t sys_now(void) {
  return (u32_t) systick_timems;
}

#else
/* CMSIS-RTOS implementation of the lwip operating system abstraction */
#include "arch/sys_arch.h"

/*---------------------------------------------------------------------------*
 * Routine:  sys_mbox_new
 *---------------------------------------------------------------------------*
 * Description:
 *      Creates a new mailbox
 * Inputs:
 *      sys_mbox_t mbox         -- Handle of mailbox
 *      int queue_sz            -- Size of elements in the mailbox
 * Outputs:
 *      err_t                   -- ERR_OK if message posted, else ERR_MEM
 *---------------------------------------------------------------------------*/
err_t sys_mbox_new(sys_mbox_t *mbox, int queue_sz) {
    if (queue_sz > MB_SIZE)
        error("sys_mbox_new size error\n");
    
#ifdef CMSIS_OS_RTX
    memset(mbox->queue, 0, sizeof(mbox->queue));
    mbox->def.pool = mbox->queue;
    mbox->def.queue_sz = queue_sz;
#endif
    mbox->id = osMessageCreate(&mbox->def, NULL);
    return (mbox->id == NULL) ? (ERR_MEM) : (ERR_OK);
}

/*---------------------------------------------------------------------------*
 * Routine:  sys_mbox_free
 *---------------------------------------------------------------------------*
 * Description:
 *      Deallocates a mailbox. If there are messages still present in the
 *      mailbox when the mailbox is deallocated, it is an indication of a
 *      programming error in lwIP and the developer should be notified.
 * Inputs:
 *      sys_mbox_t *mbox         -- Handle of mailbox
 *---------------------------------------------------------------------------*/
void sys_mbox_free(sys_mbox_t *mbox) {
    osEvent event = osMessageGet(mbox->id, 0);
    if (event.status == osEventMessage)
        error("sys_mbox_free error\n");
}

/*---------------------------------------------------------------------------*
 * Routine:  sys_mbox_post
 *---------------------------------------------------------------------------*
 * Description:
 *      Post the "msg" to the mailbox.
 * Inputs:
 *      sys_mbox_t mbox        -- Handle of mailbox
 *      void *msg              -- Pointer to data to post
 *---------------------------------------------------------------------------*/
void sys_mbox_post(sys_mbox_t *mbox, void *msg) {
    if (osMessagePut(mbox->id, (uint32_t)msg, osWaitForever) != osOK)
        error("sys_mbox_post error\n");
}

/*---------------------------------------------------------------------------*
 * Routine:  sys_mbox_trypost
 *---------------------------------------------------------------------------*
 * Description:
 *      Try to post the "msg" to the mailbox.  Returns immediately with
 *      error if cannot.
 * Inputs:
 *      sys_mbox_t mbox         -- Handle of mailbox
 *      void *msg               -- Pointer to data to post
 * Outputs:
 *      err_t                   -- ERR_OK if message posted, else ERR_MEM
 *                                  if not.
 *---------------------------------------------------------------------------*/
err_t sys_mbox_trypost(sys_mbox_t *mbox, void *msg) {
    osStatus status = osMessagePut(mbox->id, (uint32_t)msg, 0);
    return (status == osOK) ? (ERR_OK) : (ERR_MEM);
}

/*---------------------------------------------------------------------------*
 * Routine:  sys_arch_mbox_fetch
 *---------------------------------------------------------------------------*
 * Description:
 *      Blocks the thread until a message arrives in the mailbox, but does
 *      not block the thread longer than "timeout" milliseconds (similar to
 *      the sys_arch_sem_wait() function). The "msg" argument is a result
 *      parameter that is set by the function (i.e., by doing "*msg =
 *      ptr"). The "msg" parameter maybe NULL to indicate that the message
 *      should be dropped.
 *
 *      The return values are the same as for the sys_arch_sem_wait() function:
 *      Number of milliseconds spent waiting or SYS_ARCH_TIMEOUT if there was a
 *      timeout.
 *
 *      Note that a function with a similar name, sys_mbox_fetch(), is
 *      implemented by lwIP.
 * Inputs:
 *      sys_mbox_t mbox         -- Handle of mailbox
 *      void **msg              -- Pointer to pointer to msg received
 *      u32_t timeout           -- Number of milliseconds until timeout
 * Outputs:
 *      u32_t                   -- SYS_ARCH_TIMEOUT if timeout, else number
 *                                  of milliseconds until received.
 *---------------------------------------------------------------------------*/
u32_t sys_arch_mbox_fetch(sys_mbox_t *mbox, void **msg, u32_t timeout) {
    u32_t start = us_ticker_read();
    
    osEvent event = osMessageGet(mbox->id, (timeout != 0)?(timeout):(osWaitForever));
    if (event.status != osEventMessage)
        return SYS_ARCH_TIMEOUT;
    
    *msg = (void *)event.value.v;
    
    return (us_ticker_read() - start) / 1000;
}

/*---------------------------------------------------------------------------*
 * Routine:  sys_arch_mbox_tryfetch
 *---------------------------------------------------------------------------*
 * Description:
 *      Similar to sys_arch_mbox_fetch, but if message is not ready
 *      immediately, we'll return with SYS_MBOX_EMPTY.  On success, 0 is
 *      returned.
 * Inputs:
 *      sys_mbox_t mbox         -- Handle of mailbox
 *      void **msg              -- Pointer to pointer to msg received
 * Outputs:
 *      u32_t                   -- SYS_MBOX_EMPTY if no messages.  Otherwise,
 *                                  return ERR_OK.
 *---------------------------------------------------------------------------*/
u32_t sys_arch_mbox_tryfetch(sys_mbox_t *mbox, void **msg) {
    osEvent event = osMessageGet(mbox->id, 0);
    if (event.status != osEventMessage)
        return SYS_MBOX_EMPTY;
    
    *msg = (void *)event.value.v;
    
    return ERR_OK;
}

/*---------------------------------------------------------------------------*
 * Routine:  sys_sem_new
 *---------------------------------------------------------------------------*
 * Description:
 *      Creates and returns a new semaphore. The "ucCount" argument specifies
 *      the initial state of the semaphore.
 *      NOTE: Currently this routine only creates counts of 1 or 0
 * Inputs:
 *      sys_sem_t sem         -- Handle of semaphore
 *      u8_t count            -- Initial count of semaphore
 * Outputs:
 *      err_t                 -- ERR_OK if semaphore created
 *---------------------------------------------------------------------------*/
err_t sys_sem_new(sys_sem_t *sem, u8_t count) {
#ifdef CMSIS_OS_RTX
    memset(sem->data, 0, sizeof(uint32_t)*2);
    sem->def.semaphore = sem->data;
#endif
    sem->id = osSemaphoreCreate(&sem->def, count);
    if (sem->id == NULL)
        error("sys_sem_new create error\n");
    
    return ERR_OK;
}

/*---------------------------------------------------------------------------*
 * Routine:  sys_arch_sem_wait
 *---------------------------------------------------------------------------*
 * Description:
 *      Blocks the thread while waiting for the semaphore to be
 *      signaled. If the "timeout" argument is non-zero, the thread should
 *      only be blocked for the specified time (measured in
 *      milliseconds).
 *
 *      If the timeout argument is non-zero, the return value is the number of
 *      milliseconds spent waiting for the semaphore to be signaled. If the
 *      semaphore wasn't signaled within the specified time, the return value is
 *      SYS_ARCH_TIMEOUT. If the thread didn't have to wait for the semaphore
 *      (i.e., it was already signaled), the function may return zero.
 *
 *      Notice that lwIP implements a function with a similar name,
 *      sys_sem_wait(), that uses the sys_arch_sem_wait() function.
 * Inputs:
 *      sys_sem_t sem           -- Semaphore to wait on
 *      u32_t timeout           -- Number of milliseconds until timeout
 * Outputs:
 *      u32_t                   -- Time elapsed or SYS_ARCH_TIMEOUT.
 *---------------------------------------------------------------------------*/
u32_t sys_arch_sem_wait(sys_sem_t *sem, u32_t timeout) {
    u32_t start = us_ticker_read();
    
    if (osSemaphoreWait(sem->id, (timeout != 0)?(timeout):(osWaitForever)) < 1)
        return SYS_ARCH_TIMEOUT;
    
    return (us_ticker_read() - start) / 1000;
}

/*---------------------------------------------------------------------------*
 * Routine:  sys_sem_signal
 *---------------------------------------------------------------------------*
 * Description:
 *      Signals (releases) a semaphore
 * Inputs:
 *      sys_sem_t sem           -- Semaphore to signal
 *---------------------------------------------------------------------------*/
void sys_sem_signal(sys_sem_t *data) {
    if (osSemaphoreRelease(data->id) != osOK)
        mbed_die(); /* Can be called by ISR do not use printf */
}

/*---------------------------------------------------------------------------*
 * Routine:  sys_sem_free
 *---------------------------------------------------------------------------*
 * Description:
 *      Deallocates a semaphore
 * Inputs:
 *      sys_sem_t sem           -- Semaphore to free
 *---------------------------------------------------------------------------*/
void sys_sem_free(sys_sem_t *sem) {}

/** Create a new mutex
 * @param mutex pointer to the mutex to create
 * @return a new mutex */
err_t sys_mutex_new(sys_mutex_t *mutex) {
#ifdef CMSIS_OS_RTX
    memset(mutex->data, 0, sizeof(int32_t)*3);
    mutex->def.mutex = mutex->data;
#endif
    mutex->id = osMutexCreate(&mutex->def);
    if (mutex->id == NULL)
        return ERR_MEM;
    
    return ERR_OK;
}

/** Lock a mutex
 * @param mutex the mutex to lock */
void sys_mutex_lock(sys_mutex_t *mutex) {
    if (osMutexWait(mutex->id, osWaitForever) != osOK)
        error("sys_mutex_lock error\n");
}

/** Unlock a mutex
 * @param mutex the mutex to unlock */
void sys_mutex_unlock(sys_mutex_t *mutex) {
    if (osMutexRelease(mutex->id) != osOK)
        error("sys_mutex_unlock error\n");
}

/** Delete a mutex
 * @param mutex the mutex to delete */
void sys_mutex_free(sys_mutex_t *mutex) {}

/*---------------------------------------------------------------------------*
 * Routine:  sys_init
 *---------------------------------------------------------------------------*
 * Description:
 *      Initialize sys arch
 *---------------------------------------------------------------------------*/
osMutexId lwip_sys_mutex;
osMutexDef(lwip_sys_mutex);

void sys_init(void) {
    us_ticker_read(); // Init sys tick
    lwip_sys_mutex = osMutexCreate(osMutex(lwip_sys_mutex));
    if (lwip_sys_mutex == NULL)
        error("sys_init error\n");
}

/*---------------------------------------------------------------------------*
 * Routine:  sys_jiffies
 *---------------------------------------------------------------------------*
 * Description:
 *      Used by PPP as a timestamp-ish value
 *---------------------------------------------------------------------------*/
u32_t sys_jiffies(void) {
    static u32_t jiffies = 0;
    jiffies += 1 + (us_ticker_read()/10000);
    return jiffies;
}

/*---------------------------------------------------------------------------*
 * Routine:  sys_arch_protect
 *---------------------------------------------------------------------------*
 * Description:
 *      This optional function does a "fast" critical region protection and
 *      returns the previous protection level. This function is only called
 *      during very short critical regions. An embedded system which supports
 *      ISR-based drivers might want to implement this function by disabling
 *      interrupts. Task-based systems might want to implement this by using
 *      a mutex or disabling tasking. This function should support recursive
 *      calls from the same task or interrupt. In other words,
 *      sys_arch_protect() could be called while already protected. In
 *      that case the return value indicates that it is already protected.
 *
 *      sys_arch_protect() is only required if your port is supporting an
 *      operating system.
 * Outputs:
 *      sys_prot_t              -- Previous protection level (not used here)
 *---------------------------------------------------------------------------*/
sys_prot_t sys_arch_protect(void) {
    if (osMutexWait(lwip_sys_mutex, osWaitForever) != osOK)
        error("sys_arch_protect error\n");
    return (sys_prot_t) 1;
}

/*---------------------------------------------------------------------------*
 * Routine:  sys_arch_unprotect
 *---------------------------------------------------------------------------*
 * Description:
 *      This optional function does a "fast" set of critical region
 *      protection to the value specified by pval. See the documentation for
 *      sys_arch_protect() for more information. This function is only
 *      required if your port is supporting an operating system.
 * Inputs:
 *      sys_prot_t              -- Previous protection level (not used here)
 *---------------------------------------------------------------------------*/
void sys_arch_unprotect(sys_prot_t p) {
    if (osMutexRelease(lwip_sys_mutex) != osOK)
        error("sys_arch_unprotect error\n");
}

u32_t sys_now(void) {
    return us_ticker_read() / 1000;
}

void sys_msleep(u32_t ms) {
    osDelay(ms);
}

// Keep a pool of thread structures
static int thread_pool_index = 0;
static sys_thread_data_t thread_pool[SYS_THREAD_POOL_N];

/*---------------------------------------------------------------------------*
 * Routine:  sys_thread_new
 *---------------------------------------------------------------------------*
 * Description:
 *      Starts a new thread with priority "prio" that will begin its
 *      execution in the function "thread()". The "arg" argument will be
 *      passed as an argument to the thread() function. The id of the new
 *      thread is returned. Both the id and the priority are system
 *      dependent.
 * Inputs:
 *      char *name                -- Name of thread
 *      void (*thread)(void *arg) -- Pointer to function to run.
 *      void *arg                 -- Argument passed into function
 *      int stacksize             -- Required stack amount in bytes
 *      int priority              -- Thread priority
 * Outputs:
 *      sys_thread_t              -- Pointer to thread handle.
 *---------------------------------------------------------------------------*/
sys_thread_t sys_thread_new(const char *pcName,
                            void (*thread)(void *arg),
                            void *arg, int stacksize, int priority) {
    LWIP_DEBUGF(SYS_DEBUG, ("New Thread: %s\n", pcName));
    
    if (thread_pool_index >= SYS_THREAD_POOL_N)
        error("sys_thread_new number error\n");
    sys_thread_t t = (sys_thread_t)&thread_pool[thread_pool_index];
    thread_pool_index++;
    
#ifdef CMSIS_OS_RTX
    t->def.pthread = (os_pthread)thread;
    t->def.tpriority = (osPriority)priority;
    t->def.stacksize = stacksize;
#ifndef __MBED_CMSIS_RTOS_CA9
    t->def.stack_pointer = (uint32_t*)malloc(stacksize);
    if (t->def.stack_pointer == NULL) {
      error("Error allocating the stack memory");
    }
#endif
#endif
    t->id = osThreadCreate(&t->def, arg);
    if (t->id == NULL)
        error("sys_thread_new create error\n");
    
    return t;
}

#endif

#ifdef LWIP_DEBUG

/** \brief  Displays an error message on assertion

    This function will display an error message on an assertion
    to the debug output.

    \param[in]    msg   Error message to display
    \param[in]    line  Line number in file with error
    \param[in]    file  Filename with error
 */
void assert_printf(char *msg, int line, char *file) {
    if (msg)
        error("%s:%d in file %s\n", msg, line, file);
    else
        error("LWIP ASSERT\n");
}

#endif /* LWIP_DEBUG */
