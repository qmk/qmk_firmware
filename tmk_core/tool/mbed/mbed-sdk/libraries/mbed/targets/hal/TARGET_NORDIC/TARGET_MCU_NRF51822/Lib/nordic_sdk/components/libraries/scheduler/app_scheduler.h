/* Copyright (c) 2012 Nordic Semiconductor. All Rights Reserved.
 *
 * The information contained herein is property of Nordic Semiconductor ASA.
 * Terms and conditions of usage are described in detail in NORDIC
 * SEMICONDUCTOR STANDARD SOFTWARE LICENSE AGREEMENT.
 *
 * Licensees are granted free, non-transferable use of the information. NO
 * WARRANTY of ANY KIND is provided. This heading must NOT be removed from
 * the file.
 *
 */

/** @file
 *
 * @defgroup app_scheduler Scheduler
 * @{
 * @ingroup app_common
 *
 * @brief The scheduler is used for transferring execution from the interrupt context to the main
 *        context.
 *
 * @details See @ref seq_diagrams_sched for sequence diagrams illustrating the flow of events
 *          when using the Scheduler.
 *
 * @section app_scheduler_req Requirements:
 *
 * @subsection main_context_logic Logic in main context:
 *
 *   - Define an event handler for each type of event expected.
 *   - Initialize the scheduler by calling the APP_SCHED_INIT() macro before entering the
 *     application main loop.
 *   - Call app_sched_execute() from the main loop each time the application wakes up because of an
 *     event (typically when sd_app_evt_wait() returns).
 *
 * @subsection int_context_logic Logic in interrupt context:
 *
 *   - In the interrupt handler, call app_sched_event_put()
 *     with the appropriate data and event handler. This will insert an event into the
 *     scheduler's queue. The app_sched_execute() function will pull this event and call its
 *     handler in the main context.
 *
 * @if (SD_S110 && !SD_S310)
 * For an example usage of the scheduler, see the implementations of
 * @ref ble_sdk_app_hids_mouse and @ref ble_sdk_app_hids_keyboard.
 * @endif
 *
 * @image html scheduler_working.jpg The high level design of the scheduler
 */

#ifndef APP_SCHEDULER_H__
#define APP_SCHEDULER_H__

#include <stdint.h>
#include "app_error.h"

#define APP_SCHED_EVENT_HEADER_SIZE 8       /**< Size of app_scheduler.event_header_t (only for use inside APP_SCHED_BUF_SIZE()). */

/**@brief Compute number of bytes required to hold the scheduler buffer.
 *
 * @param[in] EVENT_SIZE   Maximum size of events to be passed through the scheduler.
 * @param[in] QUEUE_SIZE   Number of entries in scheduler queue (i.e. the maximum number of events
 *                         that can be scheduled for execution).
 *
 * @return    Required scheduler buffer size (in bytes).
 */
#define APP_SCHED_BUF_SIZE(EVENT_SIZE, QUEUE_SIZE)                                                 \
            (((EVENT_SIZE) + APP_SCHED_EVENT_HEADER_SIZE) * ((QUEUE_SIZE) + 1))
            
/**@brief Scheduler event handler type. */
typedef void (*app_sched_event_handler_t)(void * p_event_data, uint16_t event_size);

/**@brief Macro for initializing the event scheduler.
 *
 * @details It will also handle dimensioning and allocation of the memory buffer required by the
 *          scheduler, making sure the buffer is correctly aligned.
 *
 * @param[in] EVENT_SIZE   Maximum size of events to be passed through the scheduler.
 * @param[in] QUEUE_SIZE   Number of entries in scheduler queue (i.e. the maximum number of events
 *                         that can be scheduled for execution).
 *
 * @note Since this macro allocates a buffer, it must only be called once (it is OK to call it
 *       several times as long as it is from the same location, e.g. to do a reinitialization).
 */
#define APP_SCHED_INIT(EVENT_SIZE, QUEUE_SIZE)                                                     \
    do                                                                                             \
    {                                                                                              \
        static uint32_t APP_SCHED_BUF[CEIL_DIV(APP_SCHED_BUF_SIZE((EVENT_SIZE), (QUEUE_SIZE)),     \
                                               sizeof(uint32_t))];                                 \
        uint32_t ERR_CODE = app_sched_init((EVENT_SIZE), (QUEUE_SIZE), APP_SCHED_BUF);             \
        APP_ERROR_CHECK(ERR_CODE);                                                                 \
    } while (0)

/**@brief Function for initializing the Scheduler.
 *
 * @details It must be called before entering the main loop.
 *
 * @param[in]   max_event_size   Maximum size of events to be passed through the scheduler.
 * @param[in]   queue_size       Number of entries in scheduler queue (i.e. the maximum number of
 *                               events that can be scheduled for execution).
 * @param[in]   p_evt_buffer   Pointer to memory buffer for holding the scheduler queue. It must
 *                               be dimensioned using the APP_SCHED_BUFFER_SIZE() macro. The buffer
 *                               must be aligned to a 4 byte boundary.
 *
 * @note Normally initialization should be done using the APP_SCHED_INIT() macro, as that will both
 *       allocate the scheduler buffer, and also align the buffer correctly.
 *
 * @retval      NRF_SUCCESS               Successful initialization.
 * @retval      NRF_ERROR_INVALID_PARAM   Invalid parameter (buffer not aligned to a 4 byte
 *                                        boundary).
 */
uint32_t app_sched_init(uint16_t max_event_size, uint16_t queue_size, void * p_evt_buffer);

/**@brief Function for executing all scheduled events.
 *
 * @details This function must be called from within the main loop. It will execute all events
 *          scheduled since the last time it was called.
 */
void app_sched_execute(void);

/**@brief Function for scheduling an event.
 *
 * @details Puts an event into the event queue.
 *
 * @param[in]   p_event_data   Pointer to event data to be scheduled.
 * @param[in]   event_size   Size of event data to be scheduled.
 * @param[in]   handler        Event handler to receive the event.
 *
 * @return      NRF_SUCCESS on success, otherwise an error code.
 */
uint32_t app_sched_event_put(void *                    p_event_data,
                             uint16_t                  event_size,
                             app_sched_event_handler_t handler);

#ifdef APP_SCHEDULER_WITH_PAUSE
/**@brief A function to pause the scheduler.
 *
 * @details When the scheduler is paused events are not pulled from the scheduler queue for
 *          processing. The function can be called multiple times. To unblock the scheduler the
 *          function @ref app_sched_resume has to be called the same number of times.
 */
void app_sched_pause(void);

/**@brief A function to resume a scheduler.
 *
 * @details To unblock the scheduler this function has to be called the same number of times as
 *          @ref app_sched_pause function.
 */
void app_sched_resume(void);
#endif
#endif // APP_SCHEDULER_H__

/** @} */
