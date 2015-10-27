/*
 * Copyright (c) 2013 - 2014, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#if !defined(__FSL_OS_ABSTRACTION_H__)
#define __FSL_OS_ABSTRACTION_H__

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

#if defined __CC_ARM
#define inline      __inline
#endif

/*!
 * @addtogroup os_abstraction
 * @{
 */

/*! @brief Status values to be returned by functions. */
typedef enum
{
    kSuccess = 0,  /*!< Functions work correctly.                   */
    kError,        /*!< Functions work failed.                      */
    kTimeout,      /*!< Timeout occurs while waiting for an object. */
    kIdle          /*!< Can not get the object in non-blocking mode.*/
}fsl_rtos_status;

/*! @brief The event flags are set or not.*/
typedef enum
{
    kFlagNotSet = 0, /*!< The flags checked are set.     */
    kFlagSet         /*!< The flags checked are not set. */
}event_status;

/*! @brief The event flags are cleared automatically or manually.*/
typedef enum
{
    kEventAutoClr = 0, /*!< The flags of the event will be cleared automatically. */
    kEventManualClr    /*!< The flags of the event will be cleared manually.      */
}event_clear_type;

// Temporary "fix", until the proper macros are integrated in the on-line build system
#define FSL_RTOS_MBED

/* Include required header file based on RTOS selection */
#if defined (FSL_RTOS_MQX)
    /*! @brief Macro to set message queue copy messages to internal memory or not. */
    #define __FSL_RTOS_MSGQ_COPY_MSG__  1
    #include "fsl_os_abstraction_mqx.h"

#elif defined (FSL_RTOS_FREE_RTOS)
    #define __FSL_RTOS_MSGQ_COPY_MSG__  1
    #include "fsl_os_abstraction_free_rtos.h"

#elif defined (FSL_RTOS_UCOSII)
    #define __FSL_RTOS_MSGQ_COPY_MSG__  1
    #include "fsl_os_abstraction_ucosii.h"

#elif defined (FSL_RTOS_UCOSIII)
    #define __FSL_RTOS_MSGQ_COPY_MSG__  1
    #include "fsl_os_abstraction_ucosiii.h"

#elif defined (FSL_RTOS_CMSIS)
    #define __FSL_RTOS_MSGQ_COPY_MSG__  0
    #include "fsl_os_abstraction_cmsis.h"

#elif defined (FSL_RTOS_MBED)
    #define __FSL_RTOS_MSGQ_COPY_MSG__  1
    #include "fsl_os_abstraction_mbed.h"

#else
    #define __FSL_RTOS_MSGQ_COPY_MSG__  1
    #include "fsl_os_abstraction_bm.h"
#endif

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @name Synchronization
 * @{
 */

/*!
 * @brief Initialize a synchronization object to a given state.
 *
 * @param obj The sync object to initialize.
 * @param initValue The initial value the object will be set to.
 * 
 * @retval kSuccess The object was successfully created.
 * @retval kError Invalid parameter or no more objects can be created.
 */
fsl_rtos_status sync_create(sync_object_t *obj, uint8_t initValue);

/*!
 * @brief Wait for the synchronization object.
 *
 * This function checks the sync object's counting value, if it is
 * positive, decreases it and returns kSuccess, otherwise, timeout will be
 * used for wait.
 *
 * @param obj Pointer to the synchronization object.
 * @param timeout The maximum number of milliseconds to wait for the object to be signalled.
 *      Pass the #kSyncWaitForever constant to wait indefinitely for someone to signal the object.
 *      A value of 0 should not be passed to this function. Instead, use sync_poll for
 *      a non blocking check.
 *
 * @retval kSuccess The object was signalled.
 * @retval kTimeout A timeout occurred.
 * @retval kError An incorrect parameter was passed.
 * @retval kIdle The object has not been signalled.
 *
 * @note There could be only one process waiting for the object at the same time.
 */
fsl_rtos_status sync_wait(sync_object_t *obj, uint32_t timeout);

/*!
 * @brief Checks a synchronization object's status.
 *
 * This function is used to poll a sync object's status.
 * If the sync object's counting value is positive, decrease it and return
 * kSuccess. If the object's counting value is 0, the function will
 * return kIdle immediately
 *
 * @param obj The synchronization object.
 *
 * @retval kSuccess The object was signalled.
 * @retval kIdle The object was not signalled.
 * @retval kError An incorrect parameter was passed.
 */
fsl_rtos_status sync_poll(sync_object_t *obj);

/*!
 * @brief Signal for someone waiting on the synchronization object to wake up.
 *
 * This function should not be called from an ISR.
 *
 * @param obj The synchronization object to signal.
 * 
 * @retval kSuccess The object was successfully signaled.
 * @retval kError The object can not be signaled or invalid parameter.
 */
fsl_rtos_status sync_signal(sync_object_t *obj);

/*!
 * @brief Signal for someone waiting on the synchronization object to wake up.
 *
 * This function should only be called from an ISR.
 *
 * @param obj The synchronization object to signal.
 * 
 * @retval kSuccess The object was successfully signaled.
 * @retval kError The object can not be signaled or invalid parameter.
 */
fsl_rtos_status sync_signal_from_isr(sync_object_t *obj);

/*!
 * @brief Destroy a previously created synchronization object.
 *
 * @param obj The synchronization object to destroy.
 * 
 * @retval kSuccess The object was successfully destroyed.
 * @retval kError Object destruction failed.
 */
fsl_rtos_status sync_destroy(sync_object_t *obj);

/* @} */

/*!
 * @name Resource locking
 * @{
 */

/*!
 * @brief Initialize a locking object.
 *
 * @param obj The lock object to initialize.
 *
 * @retval kSuccess The lock is created successfully.
 * @retval kError Tke lock creation failed.
 */
fsl_rtos_status lock_create(lock_object_t *obj);

/*!
 * @brief Wait for the object to be unlocked and lock it.
 *
 * This function will wait for some time or wait forever if could not get the lock.
 *
 * @param obj The locking object.
 * @param timeout The maximum number of milliseconds to wait for the mutex.
 *      Pass the #kSyncWaitForever constant to wait indefinitely for someone to unlock the object.
 *      A value of 0 should not be passed to this function. Instead, use lock_poll for a non
 *      blocking check.
 *
 * @retval kSuccess The lock was obtained.
 * @retval kTimeout A timeout occurred.
 * @retval kError An incorrect parameter was passed.
 */
fsl_rtos_status lock_wait(lock_object_t *obj, uint32_t timeout);

/*!
 * @brief Checks if a locking object can be locked and locks it if possible.
 *
 * This function returns instantly if could not get the lock.
 *
 * @param obj The locking object.
 *
 * @retval kSuccess The lock was obtained.
 * @retval kIdle The lock could not be obtained.
 * @retval kError An incorrect parameter was passed.
 *
 * @note There could be only one process waiting for the object at the same time.
 * For RTOSes, wait for a lock recursively by one task is not supported.
 *
 */
fsl_rtos_status lock_poll(lock_object_t *obj);

/*!
 * @brief Unlock a previously locked object.
 *
 * @param obj The locking object to unlock.
 * 
 * @retval kSuccess The object was successfully unlocked.
 * @retval kError The object can not be unlocked or invalid parameter.
 */
fsl_rtos_status lock_release(lock_object_t *obj);

/*!
 * @brief Destroy a previously created locking object.
 *
 * @param obj The locking object to destroy.
 * 
 * @retval kSuccess The object was successfully destroyed.
 * @retval kError Object destruction failed.
 */
fsl_rtos_status lock_destroy(lock_object_t *obj);

/* @} */

/*!
 * @name Event signaling
 * @{
 */

/*!
 * @brief Initializes the event object.
 *
 * When the object is created, the flags is 0.
 *
 * @param obj Pointer to the event object to initialize.
 * @param clearType The event is auto-clear or manual-clear.
 *
 * @retval kSuccess The object was successfully created.
 * @retval kError Incorrect parameter or no more objects can be created.
 */
fsl_rtos_status event_create(event_object_t *obj, event_clear_type clearType);

/*!
 * @brief Wait for any event flags to be set.
 *
 * This function will wait for some time or wait forever if no flags are set. Any flags set
 * will wake up the function.
 *
 * @param obj The event object.
 * @param timeout The maximum number of milliseconds to wait for the event.
 *      Pass the #kSyncWaitForever constant to wait indefinitely. A value of 0 should not be passed 
 *      to this function.
 * @param setFlags Pointer to receive the flags that were set.
 *
 * @retval kSuccess An event was set.
 * @retval kTimeout A timeout occurred.
 * @retval kError An incorrect parameter was passed.
 */
fsl_rtos_status event_wait(event_object_t *obj, uint32_t timeout, event_group_t *setFlags);

/*!
 * @brief Set one or more event flags of an event object.
 *
 * This function should not be called from an ISR.
 *
 * @param obj The event object.
 * @param flags Event flags to be set.
 *
 * @retval kSuccess The flags were successfully set.
 * @retval kError An incorrect parameter was passed.
 *
 * @note There could be only one process waiting for the event.
 *
 */
fsl_rtos_status event_set(event_object_t *obj, event_group_t flags);

/*!
 * @brief Set one or more event flags of an event object.
 *
 * This function should only be called from an ISR.
 *
 * @param obj The event object.
 * @param flags Event flags to be set.
 *
 * @retval kSuccess The flags were successfully set.
 * @retval kError An incorrect parameter was passed.
 */
fsl_rtos_status event_set_from_isr(event_object_t *obj, event_group_t flags);

/*!
 * @brief Clear one or more events of an event object.
 *
 * This function should not be called from an ISR.
 *
 * @param obj The event object.
 * @param flags Event flags to be clear.
 *
 * @retval kSuccess The flags were successfully cleared.
 * @retval kError An incorrect parameter was passed.
 */
fsl_rtos_status event_clear(event_object_t *obj, event_group_t flags);

/*!
 * @brief Check the flags are set or not.
 *
 * @param obj The event object.
 * @param flag The flag to check.
 *
 * @retval kFlagsSet The flags checked are set.
 * @retval kFlagsNotSet The flags checked are not set or got an error.
 */
event_status event_check_flags(event_object_t *obj, event_group_t flag);

/*!
 * @brief Destroy a previously created event object.
 *
 * @param obj The event object to destroy.
 * 
 * @retval kSuccess The object was successfully destroyed.
 * @retval kError Event destruction failed.
 */
fsl_rtos_status event_destroy(event_object_t *obj);
/* @} */

/*!
 * @name Thread management
 * @{
 */

/*!
 * @brief Create a task.
 *
 * This function is wrapped by the macro task_create. Generally, this function is for
 * internal use only, applications must use FSL_RTOS_TASK_DEFINE to define resources for
 * task statically then use task_create to create task. If applications have prepare
 * the resouces for task dynamically, they can use this function to create the task.
 *
 * @param task The task function.
 * @param name The name of this task.
 * @param stackSize The stack size in byte.
 * @param stackMem Pointer to the stack. For bare metal, MQX and FreeRTOS, this could be NULL.
 * @param priority Initial priority of the task.
 * @param param Pointer to be passed to the task when it is created.
 * @param usesFloat This task will use float register or not.
 * @param handler Pointer to the task handler.
 *
 * @retval kSuccess The task was successfully created.
 * @retval kError The task could not be created.
 *
 * @note Different tasks can not use the same task function.
 */
fsl_rtos_status __task_create(task_t task, uint8_t *name, uint16_t stackSize,
                              task_stack_t *stackMem, uint16_t priority,
                              void *param, bool usesFloat, task_handler_t *handler);

/*!
 * @brief Destroy a previously created task.
 * @note Depending on the RTOS, task resources may or may not be automatically freed,
 *       and this function may not return if the current task is destroyed.
 *
 * @param handler The handler of the task to destroy. Returned by the task_create function.
 * 
 * @retval kSuccess The task was successfully destroyed.
 * @retval kError Task destruction failed or invalid parameter.
 */
fsl_rtos_status task_destroy(task_handler_t handler);
/* @} */

/*!
 * @name Message queues
 * @{
 */

/*!
 * @brief Initialize the message queue.
 *
 * This function will initialize the message queue that declared previously.
 * Here is an example demonstrating how to use:
   @code
   msg_queue_handler_t handler;
   MSG_QUEUE_DECLARE(my_message, msg_num, msg_size);
   handler = msg_queue_create(&my_message, msg_num, msg_size);
   @endcode
 *
 * @param queue The queue declared through the MSG_QUEUE_DECLARE macro.
 * @param number The number of elements in the queue.
 * @param size Size of every elements in words.
 * 
 * @retval Handler to access the queue for put and get operations. If message queue
 *         created failed, return 0.
 */
msg_queue_handler_t msg_queue_create(msg_queue_t *queue, uint16_t number, uint16_t size);

/*!
 * @brief Introduce an element at the tail of the queue.
 *
 * @param handler Queue handler returned by the msg_queue_create function.
 * @param item Pointer to the element to be introduced in the queue.
 * 
 * @retval kSuccess Element successfully introduced in the queue.
 * @retval kError The queue was full or an invalid parameter was passed.
 */
fsl_rtos_status msg_queue_put(msg_queue_handler_t handler, msg_queue_item_t item);

/*!
 * @brief Read and remove an element at the head of the queue.
 *
 * @param handler Queue handler returned by the msg_queue_create function.
 * @param item Pointer to store a pointer to the element of the queue.
 * @param timeout In case the queue is empty, the number of milliseconds to
 *        wait for an element to be introduced into the queue. Use 0 to return
 *        immediately or #kSyncWaitForever to wait indefinitely.
 * 
 * @retval kSuccess Element successfully obtained from the queue.
 * @retval kTimeout If a timeout was specified, the queue remained empty after timeout.
 * @retval kError The queue was empty or the handler was invalid.
 * @retval kIdle The queue was empty and the timeout has not expired.
 *
 * @note There should be only one process waiting on the queue.
 */
fsl_rtos_status msg_queue_get(msg_queue_handler_t handler,
                              msg_queue_item_t   *item,
                              uint32_t            timeout);

/*!
 * @brief Discards all elements in the queue and leaves the queue empty.
 *
 * @param handler Queue handler returned by the msg_queue_create function.
 * 
 * @retval kSuccess Queue successfully emptied.
 * @retval kError Emptying queue failed.
 */
fsl_rtos_status msg_queue_flush(msg_queue_handler_t handler);

/*!
 * @brief Destroy a previously created queue.
 *
 * @param handler Queue handler returned by the msg_queue_create function.
 * 
 * @retval kSuccess The queue was successfully destroyed.
 * @retval kError Message queue destruction failed.
 */
fsl_rtos_status msg_queue_destroy(msg_queue_handler_t handler);

/* @} */

#ifndef FSL_RTOS_MBED
/*!
 * @name Memory Management
 * @{
 */

/*!
 * @brief Reserves the requested amount of memory in bytes.
 *
 * @param size Amount of bytes to reserve.
 *
 * @retval Pointer to the reserved memory. NULL if memory could not be allocated.
 */
void * mem_allocate(size_t size);

/*!
 * @brief Reserves the requested amount of memory in bytes and initializes it to 0.
 *
 * @param size Amount of bytes to reserve.
 *
 * @retval Pointer to the reserved memory. NULL if memory could not be allocated.
 */
void * mem_allocate_zero(size_t size);

/*!
 * @brief Releases the memory previously reserved.
 *
 * @param ptr Pointer to the start of the memory block previously reserved.
 *
 * @retval kSuccess Memory correctly released.
 */
fsl_rtos_status mem_free(void *ptr);
#endif

/* @} */

/*!
 * @name Time management
 * @{
 */

/*!
 * @brief Delays execution for a number of milliseconds.
 *
 * @param delay The time in milliseconds to wait.
 */
void time_delay(uint32_t delay);

/* @} */

/*!
 * @name Interrupt management
 * @{
 */

/*!
 * @brief Install interrupt handler.
 *
 * @param irqNumber IRQ number of the interrupt.
 * @param handler The interrupt handler to install.
 *
 * @retval kSuccess Handler is installed successfully.
 * @retval kSuccess Handler could not be installed.
 */
fsl_rtos_status interrupt_handler_register(int32_t irqNumber, void (*handler)(void));

/* @} */

#if defined(__cplusplus)
}
#endif

/*! @}*/

#endif /* __FSL_OS_ABSTRACTION_H__ */
/*******************************************************************************
 * EOF
 ******************************************************************************/

