#include <stdint.h>
#include <stdbool.h>
#include "action.h"
#include "action_tapping.h"
#include "timer.h"

#ifdef DEBUG_ACTION
#include "debug.h"
#else
#include "nodebug.h"
#endif

#ifndef NO_ACTION_TAPPING

#define IS_TAPPING()            !IS_NOEVENT(tapping_key.event)
#define IS_TAPPING_PRESSED()    (IS_TAPPING() && tapping_key.event.pressed)
#define IS_TAPPING_RELEASED()   (IS_TAPPING() && !tapping_key.event.pressed)
#define IS_TAPPING_KEY(k)       (IS_TAPPING() && KEYEQ(tapping_key.event.key, (k)))
#define WITHIN_TAPPING_TERM(e)  (TIMER_DIFF_16(e.time, tapping_key.event.time) < TAPPING_TERM)


static keyrecord_t tapping_key = {};
static keyrecord_t waiting_buffer[WAITING_BUFFER_SIZE] = {};
static uint8_t waiting_buffer_head = 0;
static uint8_t waiting_buffer_tail = 0;

static bool process_tapping(keyrecord_t *record);
static bool waiting_buffer_enq(keyrecord_t record);
static void waiting_buffer_clear(void);
#if TAPPING_TERM >= 500
static bool waiting_buffer_typed(keyevent_t event);
#endif
static bool waiting_buffer_has_anykey_pressed(void);
static void waiting_buffer_scan_tap(void);
static void debug_tapping_key(void);
static void debug_waiting_buffer(void);


void action_tapping_process(keyrecord_t record)
{
    if (process_tapping(&record)) {
        if (!IS_NOEVENT(record.event)) {
            debug("processed: "); debug_record(record); debug("\n");
        }
    } else {
        if (!waiting_buffer_enq(record)) {
            // clear all in case of overflow.
            debug("OVERFLOW: CLEAR ALL STATES\n");
            clear_keyboard();
            waiting_buffer_clear();
            tapping_key = (keyrecord_t){};
        }
    }

    // process waiting_buffer
    if (!IS_NOEVENT(record.event) && waiting_buffer_head != waiting_buffer_tail) {
        debug("---- action_exec: process waiting_buffer -----\n");
    }
    for (; waiting_buffer_tail != waiting_buffer_head; waiting_buffer_tail = (waiting_buffer_tail + 1) % WAITING_BUFFER_SIZE) {
        if (process_tapping(&waiting_buffer[waiting_buffer_tail])) {
            debug("processed: waiting_buffer["); debug_dec(waiting_buffer_tail); debug("] = ");
            debug_record(waiting_buffer[waiting_buffer_tail]); debug("\n\n");
        } else {
            break;
        }
    }
    if (!IS_NOEVENT(record.event)) {
        debug("\n");
    }
}


/* Tapping
 *
 * Rule: Tap key is typed(pressed and released) within TAPPING_TERM.
 *       (without interfering by typing other key)
 */
/* return true when key event is processed or consumed. */
bool process_tapping(keyrecord_t *keyp)
{
    keyevent_t event = keyp->event;

    // if tapping
    if (IS_TAPPING_PRESSED()) {
        if (WITHIN_TAPPING_TERM(event)) {
            if (tapping_key.tap.count == 0) {
                if (IS_TAPPING_KEY(event.key) && !event.pressed) {
                    // first tap!
                    debug("Tapping: First tap(0->1).\n");
                    tapping_key.tap.count = 1;
                    tapping_key.tap.interrupted  = (waiting_buffer_has_anykey_pressed() ? true : false);
                    debug_tapping_key();
                    process_action(&tapping_key);

                    // enqueue
                    keyp->tap = tapping_key.tap;
                    return false;
                }
#if TAPPING_TERM >= 500
                /* This can prevent from typing some tap keys in a row at a time. */
                else if (!event.pressed && waiting_buffer_typed(event)) {
                    // other key typed. not tap.
                    debug("Tapping: End. No tap. Interfered by typing key\n");
                    process_action(&tapping_key);
                    tapping_key = (keyrecord_t){};
                    debug_tapping_key();

                    // enqueue
                    return false;
                }
#endif
                else {
                    // other key events shall be enq'd till tapping state settles.
                    return false;
                }
            }
            // tap_count > 0
            else {
                if (IS_TAPPING_KEY(event.key) && !event.pressed) {
                    debug("Tapping: Tap release("); debug_dec(tapping_key.tap.count); debug(")\n");
                    keyp->tap = tapping_key.tap;
                    process_action(keyp);
                    tapping_key = *keyp;
                    debug_tapping_key();
                    return true;
                }
                else if (is_tap_key(keyp->event.key) && event.pressed) {
                    if (tapping_key.tap.count > 1) {
                        debug("Tapping: Start new tap with releasing last tap(>1).\n");
                        // unregister key
                        process_action(&(keyrecord_t){
                                .tap = tapping_key.tap,
                                .event.key = tapping_key.event.key,
                                .event.time = event.time,
                                .event.pressed = false
                        });
                    } else {
                        debug("Tapping: Start while last tap(1).\n");
                    }
                    tapping_key = *keyp;
                    waiting_buffer_scan_tap();
                    debug_tapping_key();
                    return true;
                }
                else {
                    if (!IS_NOEVENT(keyp->event)) {
                        debug("Tapping: key event while last tap(>0).\n");
                    }
                    process_action(keyp);
                    return true;
                }
            }
        }
        // after TAPPING_TERM
        else {
            if (tapping_key.tap.count == 0) {
                debug("Tapping: End. Timeout. Not tap(0): ");
                debug_event(event); debug("\n");
                process_action(&tapping_key);
                tapping_key = (keyrecord_t){};
                debug_tapping_key();
                return false;
            }  else {
                if (IS_TAPPING_KEY(event.key) && !event.pressed) {
                    debug("Tapping: End. last timeout tap release(>0).");
                    keyp->tap = tapping_key.tap;
                    process_action(keyp);
                    tapping_key = (keyrecord_t){};
                    return true;
                }
                else if (is_tap_key(keyp->event.key) && event.pressed) {
                    if (tapping_key.tap.count > 1) {
                        debug("Tapping: Start new tap with releasing last timeout tap(>1).\n");
                        // unregister key
                        process_action(&(keyrecord_t){
                                .tap = tapping_key.tap,
                                .event.key = tapping_key.event.key,
                                .event.time = event.time,
                                .event.pressed = false
                        });
                    } else {
                        debug("Tapping: Start while last timeout tap(1).\n");
                    }
                    tapping_key = *keyp;
                    waiting_buffer_scan_tap();
                    debug_tapping_key();
                    return true;
                }
                else {
                    if (!IS_NOEVENT(keyp->event)) {
                        debug("Tapping: key event while last timeout tap(>0).\n");
                    }
                    process_action(keyp);
                    return true;
                }
            }
        }
    } else if (IS_TAPPING_RELEASED()) {
        if (WITHIN_TAPPING_TERM(event)) {
            if (tapping_key.tap.count > 0 && IS_TAPPING_KEY(event.key) && event.pressed) {
                // sequential tap.
                keyp->tap = tapping_key.tap;
                keyp->tap.count += 1;
                debug("Tapping: Tap press("); debug_dec(keyp->tap.count); debug(")\n");
                process_action(keyp);
                tapping_key = *keyp;
                debug_tapping_key();
                return true;
            } else if (event.pressed && is_tap_key(event.key)) {
                // Sequential tap can be interfered with other tap key.
                debug("Tapping: Start with interfering other tap.\n");
                tapping_key = *keyp;
                waiting_buffer_scan_tap();
                debug_tapping_key();
                return true;
            } else {
                if (!IS_NOEVENT(keyp->event)) debug("Tapping: other key just after tap.\n");
                process_action(keyp);
                return true;
            }
        } else {
            // timeout. no sequential tap.
            debug("Tapping: End(Timeout after releasing last tap): ");
            debug_event(event); debug("\n");
            tapping_key = (keyrecord_t){};
            debug_tapping_key();
            return false;
        }
    }
    // not tapping satate
    else {
        if (event.pressed && is_tap_key(event.key)) {
            debug("Tapping: Start(Press tap key).\n");
            tapping_key = *keyp;
            waiting_buffer_scan_tap();
            debug_tapping_key();
            return true;
        } else {
            process_action(keyp);
            return true;
        }
    }
}


/*
 * Waiting buffer
 */
bool waiting_buffer_enq(keyrecord_t record)
{
    if (IS_NOEVENT(record.event)) {
        return true;
    }

    if ((waiting_buffer_head + 1) % WAITING_BUFFER_SIZE == waiting_buffer_tail) {
        debug("waiting_buffer_enq: Over flow.\n");
        return false;
    }

    waiting_buffer[waiting_buffer_head] = record;
    waiting_buffer_head = (waiting_buffer_head + 1) % WAITING_BUFFER_SIZE;

    debug("waiting_buffer_enq: "); debug_waiting_buffer();
    return true;
}

void waiting_buffer_clear(void)
{
    waiting_buffer_head = 0;
    waiting_buffer_tail = 0;
}

#if TAPPING_TERM >= 500
bool waiting_buffer_typed(keyevent_t event)
{
    for (uint8_t i = waiting_buffer_tail; i != waiting_buffer_head; i = (i + 1) % WAITING_BUFFER_SIZE) {
        if (KEYEQ(event.key, waiting_buffer[i].event.key) && event.pressed !=  waiting_buffer[i].event.pressed) {
            return true;
        }
    }
    return false;
}
#endif

bool waiting_buffer_has_anykey_pressed(void)
{
    for (uint8_t i = waiting_buffer_tail; i != waiting_buffer_head; i = (i + 1) % WAITING_BUFFER_SIZE) {
        if (waiting_buffer[i].event.pressed) return true;
    }
    return false;
}

/* scan buffer for tapping */
void waiting_buffer_scan_tap(void)
{
    // tapping already is settled
    if (tapping_key.tap.count > 0) return;
    // invalid state: tapping_key released && tap.count == 0
    if (!tapping_key.event.pressed) return;

    for (uint8_t i = waiting_buffer_tail; i != waiting_buffer_head; i = (i + 1) % WAITING_BUFFER_SIZE) {
        if (IS_TAPPING_KEY(waiting_buffer[i].event.key) &&
                !waiting_buffer[i].event.pressed &&
                WITHIN_TAPPING_TERM(waiting_buffer[i].event)) {
            tapping_key.tap.count = 1;
            waiting_buffer[i].tap.count = 1;
            process_action(&tapping_key);

            debug("waiting_buffer_scan_tap: found at ["); debug_dec(i); debug("]\n");
            debug_waiting_buffer();
            return;
        }
    }
}


/*
 * debug print
 */
static void debug_tapping_key(void)
{
    debug("TAPPING_KEY="); debug_record(tapping_key); debug("\n");
}

static void debug_waiting_buffer(void)
{
    debug("{ ");
    for (uint8_t i = waiting_buffer_tail; i != waiting_buffer_head; i = (i + 1) % WAITING_BUFFER_SIZE) {
        debug("["); debug_dec(i); debug("]="); debug_record(waiting_buffer[i]); debug(" ");
    }
    debug("}\n");
}

#endif
