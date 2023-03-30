/*
 * Copyright (c) 2022 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/** \file pico/async_context.h
 *  \defgroup pico_async_context pico_async_context
 *
 * An \ref async_context provides a logically single-threaded context for performing work, and responding
 * to asynchronous events. Thus an async_context instance is suitable for servicing third-party libraries
 * that are not re-entrant.
 *
 * The "context" in async_context refers to the fact that when calling workers or timeouts within the
 * async_context various pre-conditions hold:
 *
 * <ol>
 * <li>That there is a single logical thread of execution; i.e. that the context does not call any worker
 * functions concurrently.
 * <li>That the context always calls workers from the same processor core, as most uses of async_context rely on interaction
 * with IRQs which are themselves core-specific.
 * </ol>
 *
 * THe async_context provides two mechanisms for asynchronous work:
 *
 * * <em>when_pending</em> workers, which are processed whenever they have work pending. See \ref async_context_add_when_pending_worker,
 * \ref async_context_remove_when_pending_worker, and \ref async_context_set_work_pending, the latter of which can be used from an interrupt handler
 * to signal that servicing work is required to be performed by the worker from the regular async_context.
 * * <em>at_time</em> workers, that are executed after at a specific time.
 *
 * Note: "when pending" workers with work pending are executed before "at time" workers.
 *
 * The async_context provides locking mechanisms, see \ref async_context_acquire_lock_blocking,
 * \ref async_context_release_lock and \ref async_context_check_lock which can be used by
 * external code to ensure execution of external code does not happen concurrently with worker code.
 * Locked code runs on the calling core, however \ref async_context_execute_sync is provided to
 * synchronously run a function from the core of the async_context.
 *
 * The SDK ships with the following default async_contexts:
 *
 * async_context_poll - this context is not thread-safe, and the user is responsible for calling
 * \ref async_context_poll() periodically, and can use async_context_wait_for_work_until() to sleep
 * between calls until work is needed if the user has nothing else to do.
 *
 * async_context_threadsafe_background - in order to work in the background, a low priority IRQ is used
 * to handle callbacks. Code is usually invoked from this IRQ context, but may be invoked after any other code
 * that uses the async context in another (non-IRQ) context on the same core. Calling \ref async_context_poll() is
 * not required, and is a no-op. This context implements async_context locking and is thus safe to call
 * from either core, according to the specific notes on each API.
 *
 * async_context_freertos - Work is performed from a separate "async_context" task, however once again, code may
 * also be invoked after a direct use of the async_context on the same core that the async_context belongs to. Calling
 * \ref async_context_poll() is not required, and is a no-op. This context implements async_context locking and is thus
 * safe to call from any task, and from either core, according to the specific notes on each API.
 *
 * Each async_context provides bespoke methods of instantiation which are provided in the corresponding headers (e.g.
 * async_context_poll.h, async_context_threadsafe_background.h, asycn_context_freertos.h).
 * async_contexts are de-initialized by the common async_context_deint() method.
 *
 * Multiple async_context instances can be used by a single application, and they will operate independently.
 */

#ifndef _PICO_ASYNC_CONTEXT_H
#define _PICO_ASYNC_CONTEXT_H

#include "pico.h"
#include "pico/time.h"

#ifdef __cplusplus
extern "C" {
#endif

enum {
    ASYNC_CONTEXT_POLL = 1,
    ASYNC_CONTEXT_THREADSAFE_BACKGROUND = 2,
    ASYNC_CONTEXT_FREERTOS = 3,
};

typedef struct async_context async_context_t;

/*! \brief A "timeout" instance used by an async_context
 *  \ingroup pico_async_context
 *
 *  A "timeout" represents some future action that must be taken at a specific time.
 *  It's methods are called from the async_context under lock at the given time
 *
 * \see async_context_add_worker_at
 * \see async_context_add_worker_in_ms
 */
typedef struct async_work_on_timeout {
    /*!
     * private link list pointer
     */
    struct async_work_on_timeout *next;
    /*!
     * Method called when the timeout is reached; may not be NULL
     *
     * Note, that when this method is called, the timeout has been removed from the async_context, so
     * if you want the timeout to repeat, you should re-add it during this callback
     * @param context
     * @param timeout
     */
    void (*do_work)(async_context_t *context, struct async_work_on_timeout *timeout);
    /*!
     * The next timeout time; this should only be modified during the above methods
     * or via async_context methods
     */
    absolute_time_t next_time;
    /*!
     * User data associated with the timeout instance
     */
    void *user_data;
} async_at_time_worker_t;

/*! \brief A "worker" instance used by an async_context
 *  \ingroup pico_async_context
 *
 *  A "worker" represents some external entity that must do work in response
 *  to some external stimulus (usually an IRQ).
 *  It's methods are called from the async_context under lock at the given time
 *
 * \see async_context_add_worker_at
 * \see async_context_add_worker_in_ms
 */
typedef struct async_when_pending_worker {
    /*!
     * private link list pointer
     */
    struct async_when_pending_worker *next;
    /*!
     * Called by the async_context when the worker has been marked as having "work pending"
     *
     * @param context the async_context
     * @param worker the function to be called when work is pending
     */
    void (*do_work)(async_context_t *context, struct async_when_pending_worker *worker);
    /**
     * True if the worker need do_work called
     */
    bool work_pending;
} async_when_pending_worker_t;

#define ASYNC_CONTEXT_FLAG_CALLBACK_FROM_NON_IRQ 0x1
#define ASYNC_CONTEXT_FLAG_CALLBACK_FROM_IRQ 0x2
#define ASYNC_CONTEXT_FLAG_POLLED 0x4

/*!
 * \brief Implementation of an async_context type, providing methods common to that type
 * \ingroup pico_async_context
 */
typedef struct async_context_type {
    uint16_t type;
    // see wrapper functions for documentation
    void (*acquire_lock_blocking)(async_context_t *self);
    void (*release_lock)(async_context_t *self);
    void (*lock_check)(async_context_t *self);
    uint32_t (*execute_sync)(async_context_t *context, uint32_t (*func)(void *param), void *param);
    bool (*add_at_time_worker)(async_context_t *self, async_at_time_worker_t *worker);
    bool (*remove_at_time_worker)(async_context_t *self, async_at_time_worker_t *worker);
    bool (*add_when_pending_worker)(async_context_t *self, async_when_pending_worker_t *worker);
    bool (*remove_when_pending_worker)(async_context_t *self, async_when_pending_worker_t *worker);
    void (*set_work_pending)(async_context_t *self, async_when_pending_worker_t *worker);
    void (*poll)(async_context_t *self); // may be NULL
    void (*wait_until)(async_context_t *self, absolute_time_t until);
    void (*wait_for_work_until)(async_context_t *self, absolute_time_t until);
    void (*deinit)(async_context_t *self);
} async_context_type_t;

/*!
 * \brief Base structure type of all async_contexts. For details about its use, see \ref pico_async_context.
 * \ingroup pico_async_context
 *
 * Individual async_context_types with additional state, should contain this structure at the start.
 */
struct async_context {
    const async_context_type_t *type;
    async_when_pending_worker_t *when_pending_list;
    async_at_time_worker_t *at_time_list;
    absolute_time_t next_time;
    uint16_t flags;
    uint8_t  core_num;
};

/*!
 * \brief Acquire the async_context lock
 * \ingroup pico_async_context
 *
 * The owner of the async_context lock is the logic owner of the async_context
 * and other work related to this async_context will not happen concurrently.
 *
 * This method may be called in a nested fashion by the the lock owner.
 *
 * \note the async_context lock is nestable by the same caller, so an internal count is maintained
 * 
 * \note for async_contexts that provide locking (not async_context_poll), this method is threadsafe. and may be called from within any 
 * worker method called by the async_context or from any other non-IRQ context.
 *
 * \param context the async_context
 *
 * \see async_context_release_lock
 */
static inline void async_context_acquire_lock_blocking(async_context_t *context) {
    context->type->acquire_lock_blocking(context);
}

/*!
 * \brief Release the async_context lock
 * \ingroup pico_async_context
 *
 * \note the async_context lock may be called in a nested fashion, so an internal count is maintained. On the outermost
 * release, When the outermost lock is released, a check is made for work which might have been skipped while the lock was held,
 * and any such work may be performed during this call IF the call is made from the same core that the async_context belongs to.
 *
 * \note for async_contexts that provide locking (not async_context_poll), this method is threadsafe. and may be called from within any 
 * worker method called by the async_context or from any other non-IRQ context.
 *
 * \param context the async_context
 *
 * \see async_context_acquire_lock_blocking
 */
static inline void async_context_release_lock(async_context_t *context) {
    context->type->release_lock(context);
}

/*!
 * \brief Assert if the caller does not own the lock for the async_context
 * \ingroup pico_async_context
 * \note this method is thread-safe
 *
 * \param context the async_context
 */
static inline void async_context_lock_check(async_context_t *context) {
    context->type->lock_check(context);
}

/*!
 * \brief Execute work synchronously on the core the async_context belongs to.
 * \ingroup pico_async_context
 *
 * This method is intended for code external to the async_context (e.g. another thread/task) to
 * execute a function with the same guarantees (single core, logical thread of execution) that
 * async_context workers are called with.
 *
 * \note you should NOT call this method while holding the async_context's lock
 *
 * \param context the async_context
 * \param func the function to call
 * \param parm the paramter to pass to the function
 * \return the return value from func
 */
static inline uint32_t async_context_execute_sync(async_context_t *context, uint32_t (*func)(void *param), void *param) {
    return context->type->execute_sync(context, func, param);
}

/*!
 * \brief Add an "at time" worker to a context
 * \ingroup pico_async_context
 *
 * An "at time" worker will run at or after a specific point in time, and is automatically when (just before) it runs.
 *
 * The time to fire is specified in the next_time field of the worker.
 *
 * \note for async_contexts that provide locking (not async_context_poll), this method is threadsafe. and may be called from within any 
 * worker method called by the async_context or from any other non-IRQ context.
 *
 * \param context the async_context
 * \param worker the "at time" worker to add
 * \return true if the worker was added, false if the worker was already present.
 */
static inline bool async_context_add_at_time_worker(async_context_t *context, async_at_time_worker_t *worker) {
    return context->type->add_at_time_worker(context, worker);
}

/*!
 * \brief Add an "at time" worker to a context
 * \ingroup pico_async_context
 *
 * An "at time" worker will run at or after a specific point in time, and is automatically when (just before) it runs.
 *
 * The time to fire is specified by the at parameter.
 *
 * \note for async_contexts that provide locking (not async_context_poll), this method is threadsafe. and may be called from within any 
 * worker method called by the async_context or from any other non-IRQ context.
 *
 * \param context the async_context
 * \param worker the "at time" worker to add
 * \param at the time to fire at
 * \return true if the worker was added, false if the worker was already present.
 */
static inline bool async_context_add_at_time_worker_at(async_context_t *context, async_at_time_worker_t *worker, absolute_time_t at) {
    worker->next_time = at;
    return context->type->add_at_time_worker(context, worker);
}

/*!
 * \brief Add an "at time" worker to a context
 * \ingroup pico_async_context
 *
 * An "at time" worker will run at or after a specific point in time, and is automatically when (just before) it runs.
 *
 * The time to fire is specified by a delay via the ms parameter 
 *
 * \note for async_contexts that provide locking (not async_context_poll), this method is threadsafe. and may be called from within any 
 * worker method called by the async_context or from any other non-IRQ context.
 *
 * \param context the async_context
 * \param worker the "at time" worker to add
 * \param ms the number of milliseconds from now to fire after
 * \return true if the worker was added, false if the worker was already present.
 */
static inline bool async_context_add_at_time_worker_in_ms(async_context_t *context, async_at_time_worker_t *worker, uint32_t ms) {
    worker->next_time = make_timeout_time_ms(ms);
    return context->type->add_at_time_worker(context, worker);
}

/*!
 * \brief Remove an "at time" worker from a context
 * \ingroup pico_async_context
 *
 * \note for async_contexts that provide locking (not async_context_poll), this method is threadsafe. and may be called from within any 
 * worker method called by the async_context or from any other non-IRQ context.
 *
 * \param context the async_context
 * \param worker the "at time" worker to remove
 * \return true if the worker was removed, false if the instance not present.
 */
static inline bool async_context_remove_at_time_worker(async_context_t *context, async_at_time_worker_t *worker) {
    return context->type->remove_at_time_worker(context, worker);
}

/*!
 * \brief Add a "when pending" worker to a context
 * \ingroup pico_async_context
 *
 * An "when pending" worker will run when it is pending (can be set via \ref async_context_set_work_pending), and
 * is NOT automatically removed when it runs.
 *
 * The time to fire is specified by a delay via the ms parameter
 *
 * \note for async_contexts that provide locking (not async_context_poll), this method is threadsafe. and may be called from within any 
 * worker method called by the async_context or from any other non-IRQ context.
 *
 * \param context the async_context
 * \param worker the "when pending" worker to add
 * \return true if the worker was added, false if the worker was already present.
 */
static inline bool async_context_add_when_pending_worker(async_context_t *context, async_when_pending_worker_t *worker) {
    return context->type->add_when_pending_worker(context, worker);
}

/*!
 * \brief Remove a "when pending" worker from a context
 * \ingroup pico_async_context
 *
 * \note for async_contexts that provide locking (not async_context_poll), this method is threadsafe. and may be called from within any 
 * worker method called by the async_context or from any other non-IRQ context.
 *
 * \param context the async_context
 * \param worker the "when pending" worker to remove
 * \return true if the worker was removed, false if the instance not present.
 */
static inline bool async_context_remove_when_pending_worker(async_context_t *context, async_when_pending_worker_t *worker) {
    return context->type->remove_when_pending_worker(context, worker);
}

/*!
 * \brief Mark a "when pending" worker as having work pending
 * \ingroup pico_async_context
 *
 * The worker will be run from the async_context at a later time.
 *
 * \note this method may be called from any context including IRQs
 *
 * \param context the async_context
 * \param worker the "when pending" worker to mark as pending.
 */
static inline void async_context_set_work_pending(async_context_t *context, async_when_pending_worker_t *worker) {
    context->type->set_work_pending(context, worker);
}

/*!
 * \brief Perform any pending work for polling style async_context
 * \ingroup pico_async_context
 * 
 * For a polled async_context (e.g. \ref async_context_poll) the user is responsible for calling this method
 * periodically to perform any required work.
 * 
 * This method may immediately perform outstanding work on other context types, but is not required to.
 *
 * \param context the async_context
 */
static inline void async_context_poll(async_context_t *context) {
    if (context->type->poll) context->type->poll(context);
}

/*!
 * \brief sleep until the specified time in an async_context callback safe way
 * \ingroup pico_async_context
 *
 * \note for async_contexts that provide locking (not async_context_poll), this method is threadsafe. and may be called from within any
 * worker method called by the async_context or from any other non-IRQ context.
 *
 * \param context the async_context
 * \param until the time to sleep until
 */
static inline void async_context_wait_until(async_context_t *context, absolute_time_t until) {
    context->type->wait_until(context, until);
}

/*!
 * \brief Block until work needs to be done or the specified time has been reached
 * \ingroup pico_async_context
 *
 * \note this method should not be called from a worker callback
 *
 * \param context the async_context
 * \param until the time to return at if no work is required
 */
static inline void async_context_wait_for_work_until(async_context_t *context, absolute_time_t until) {
    context->type->wait_for_work_until(context, until);
}

/*!
 * \brief Block until work needs to be done or the specified number of milliseconds have passed
 * \ingroup pico_async_context
 *
 * \note this method should not be called from a worker callback
 *
 * \param context the async_context
 * \param ms the number of milliseconds to return after if no work is required
 */
static inline void async_context_wait_for_work_ms(async_context_t *context, uint32_t ms) {
    async_context_wait_for_work_until(context, make_timeout_time_ms(ms));
}

/*!
 * \brief Return the processor core this async_context belongs to
 * \ingroup pico_async_context
 *
 * \param context the async_context
 * \return the physical core number
 */
static inline uint async_context_core_num(const async_context_t *context) {
    return context->core_num;
}

/*!
 * \brief End async_context processing, and free any resources
 * \ingroup pico_async_context
 *
 * Note the user should clean up any resources associated with workers
 * in the async_context themselves.
 *
 * Asynchronous (non-polled) async_contexts guarantee that no
 * callback is being called once this method returns.
 *
 * \param context the async_context
 * \return the physical core number
 */
static inline void async_context_deinit(async_context_t *context) {
    context->type->deinit(context);
}

#ifdef __cplusplus
}
#endif

#endif