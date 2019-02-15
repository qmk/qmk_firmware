#include <stdint.h>
#include <stdbool.h>
#include "action.h"
#include "action_layer.h"
#include "action_tapping.h"
#include "keycode.h"
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

__attribute__ ((weak))
uint16_t get_tapping_term(uint16_t keycode) {
  return TAPPING_TERM;
}

#ifdef TAPPING_TERM_PER_KEY
#define WITHIN_TAPPING_TERM(e)  (TIMER_DIFF_16(e.time, tapping_key.event.time) < get_tapping_term(get_event_keycode(tapping_key.event)))
#else
#define WITHIN_TAPPING_TERM(e)  (TIMER_DIFF_16(e.time, tapping_key.event.time) < TAPPING_TERM)
#endif

static keyrecord_t tapping_key = {};
static keyrecord_t waiting_buffer[WAITING_BUFFER_SIZE] = {};
static uint8_t waiting_buffer_head = 0;
static uint8_t waiting_buffer_tail = 0;

static bool process_tapping(keyrecord_t *record);
static bool waiting_buffer_enq(keyrecord_t record);
static void waiting_buffer_clear(void);
static bool waiting_buffer_typed(keyevent_t event);
static bool waiting_buffer_has_anykey_pressed(void);
static void waiting_buffer_scan_tap(void);
static void debug_tapping_key(void);
static void debug_waiting_buffer(void);


/** \brief Action Tapping Process
 *
 * FIXME: Needs doc
 */
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


/** \brief Tapping
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
                    debug_tapping_key();
                    process_record(&tapping_key);

                    // copy tapping state
                    keyp->tap = tapping_key.tap;
                    // enqueue
                    return false;
                }
                /* Process a key typed within TAPPING_TERM
                 * This can register the key before settlement of tapping,
                 * useful for long TAPPING_TERM but may prevent fast typing.
                 */
#if defined(TAPPING_TERM_PER_KEY) || (!defined(PER_KEY_TAPPING_TERM) && TAPPING_TERM >= 500) || defined(PERMISSIVE_HOLD)
#ifdef TAPPING_TERM_PER_KEY
                else if ( ( get_tapping_term(get_event_keycode(tapping_key.event)) >= 500) && IS_RELEASED(event) && waiting_buffer_typed(event))
#else
                else if ( IS_RELEASED(event) && waiting_buffer_typed(event))
#endif
                {
                    debug("Tapping: End. No tap. Interfered by typing key\n");
                    process_record(&tapping_key);
                    tapping_key = (keyrecord_t){};
                    debug_tapping_key();
                    // enqueue
                    return false;
                }
#endif
                /* Process release event of a key pressed before tapping starts
                 * Without this unexpected repeating will occur with having fast repeating setting
                 * https://github.com/tmk/tmk_keyboard/issues/60
                 */
                else if (IS_RELEASED(event) && !waiting_buffer_typed(event)) {
                    // Modifier should be retained till end of this tapping.
                    action_t action = layer_switch_get_action(event.key);
                    switch (action.kind.id) {
                        case ACT_LMODS:
                        case ACT_RMODS:
                            if (action.key.mods && !action.key.code) return false;
                            if (IS_MOD(action.key.code)) return false;
                            break;
                        case ACT_LMODS_TAP:
                        case ACT_RMODS_TAP:
                            if (action.key.mods && keyp->tap.count == 0) return false;
                            if (IS_MOD(action.key.code)) return false;
                            break;
                    }
                    // Release of key should be process immediately.
                    debug("Tapping: release event of a key pressed before tapping\n");
                    process_record(keyp);
                    return true;
                }
                else {
                    // set interrupted flag when other key preesed during tapping
                    if (event.pressed) {
                        tapping_key.tap.interrupted = true;
                    }
                    // enqueue
                    return false;
                }
            }
            // tap_count > 0
            else {
                if (IS_TAPPING_KEY(event.key) && !event.pressed) {
                    debug("Tapping: Tap release("); debug_dec(tapping_key.tap.count); debug(")\n");
                    keyp->tap = tapping_key.tap;
                    process_record(keyp);
                    tapping_key = *keyp;
                    debug_tapping_key();
                    return true;
                }
                else if (is_tap_key(event.key) && event.pressed) {
                    if (tapping_key.tap.count > 1) {
                        debug("Tapping: Start new tap with releasing last tap(>1).\n");
                        // unregister key
                        process_record(&(keyrecord_t){
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
                    if (!IS_NOEVENT(event)) {
                        debug("Tapping: key event while last tap(>0).\n");
                    }
                    process_record(keyp);
                    return true;
                }
            }
        }
        // after TAPPING_TERM
        else {
            if (tapping_key.tap.count == 0) {
                debug("Tapping: End. Timeout. Not tap(0): ");
                debug_event(event); debug("\n");
                process_record(&tapping_key);
                tapping_key = (keyrecord_t){};
                debug_tapping_key();
                return false;
            }  else {
                if (IS_TAPPING_KEY(event.key) && !event.pressed) {
                    debug("Tapping: End. last timeout tap release(>0).");
                    keyp->tap = tapping_key.tap;
                    process_record(keyp);
                    tapping_key = (keyrecord_t){};
                    return true;
                }
                else if (is_tap_key(event.key) && event.pressed) {
                    if (tapping_key.tap.count > 1) {
                        debug("Tapping: Start new tap with releasing last timeout tap(>1).\n");
                        // unregister key
                        process_record(&(keyrecord_t){
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
                    if (!IS_NOEVENT(event)) {
                        debug("Tapping: key event while last timeout tap(>0).\n");
                    }
                    process_record(keyp);
                    return true;
                }
            }
        }
    } else if (IS_TAPPING_RELEASED()) {
        if (WITHIN_TAPPING_TERM(event)) {
            if (event.pressed) {
                if (IS_TAPPING_KEY(event.key)) {
#ifndef TAPPING_FORCE_HOLD
                    if (!tapping_key.tap.interrupted && tapping_key.tap.count > 0) {
                        // sequential tap.
                        keyp->tap = tapping_key.tap;
                        if (keyp->tap.count < 15) keyp->tap.count += 1;
                        debug("Tapping: Tap press("); debug_dec(keyp->tap.count); debug(")\n");
                        process_record(keyp);
                        tapping_key = *keyp;
                        debug_tapping_key();
                        return true;
                    }
#endif
                    // FIX: start new tap again
                    tapping_key = *keyp;
                    return true;
                } else if (is_tap_key(event.key)) {
                    // Sequential tap can be interfered with other tap key.
                    debug("Tapping: Start with interfering other tap.\n");
                    tapping_key = *keyp;
                    waiting_buffer_scan_tap();
                    debug_tapping_key();
                    return true;
                } else {
                    // should none in buffer
                    // FIX: interrupted when other key is pressed
                    tapping_key.tap.interrupted = true;
                    process_record(keyp);
                    return true;
                }
            } else {
                if (!IS_NOEVENT(event)) debug("Tapping: other key just after tap.\n");
                process_record(keyp);
                return true;
            }
        } else {
            // FIX: process_action here?
            // timeout. no sequential tap.
            debug("Tapping: End(Timeout after releasing last tap): ");
            debug_event(event); debug("\n");
            tapping_key = (keyrecord_t){};
            debug_tapping_key();
            return false;
        }
    }
    // not tapping state
    else {
        if (event.pressed && is_tap_key(event.key)) {
            debug("Tapping: Start(Press tap key).\n");
            tapping_key = *keyp;
            process_record_tap_hint(&tapping_key);
            waiting_buffer_scan_tap();
            debug_tapping_key();
            return true;
        } else {
            process_record(keyp);
            return true;
        }
    }
}


/** \brief Waiting buffer enq
 *
 * FIXME: Needs docs
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

/** \brief Waiting buffer clear
 *
 * FIXME: Needs docs
 */
void waiting_buffer_clear(void)
{
    waiting_buffer_head = 0;
    waiting_buffer_tail = 0;
}

/** \brief Waiting buffer typed
 *
 * FIXME: Needs docs
 */
bool waiting_buffer_typed(keyevent_t event)
{
    for (uint8_t i = waiting_buffer_tail; i != waiting_buffer_head; i = (i + 1) % WAITING_BUFFER_SIZE) {
        if (KEYEQ(event.key, waiting_buffer[i].event.key) && event.pressed !=  waiting_buffer[i].event.pressed) {
            return true;
        }
    }
    return false;
}

/** \brief Waiting buffer has anykey pressed
 *
 * FIXME: Needs docs
 */
__attribute__((unused))
bool waiting_buffer_has_anykey_pressed(void)
{
    for (uint8_t i = waiting_buffer_tail; i != waiting_buffer_head; i = (i + 1) % WAITING_BUFFER_SIZE) {
        if (waiting_buffer[i].event.pressed) return true;
    }
    return false;
}

/** \brief Scan buffer for tapping
 *
 * FIXME: Needs docs
 */
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
            process_record(&tapping_key);

            debug("waiting_buffer_scan_tap: found at ["); debug_dec(i); debug("]\n");
            debug_waiting_buffer();
            return;
        }
    }
}


/** \brief Tapping key debug print
 *
 * FIXME: Needs docs
 */
static void debug_tapping_key(void)
{
    debug("TAPPING_KEY="); debug_record(tapping_key); debug("\n");
}

/** \brief Waiting buffer debug print
 *
 * FIXME: Needs docs
 */
static void debug_waiting_buffer(void)
{
    debug("{ ");
    for (uint8_t i = waiting_buffer_tail; i != waiting_buffer_head; i = (i + 1) % WAITING_BUFFER_SIZE) {
        debug("["); debug_dec(i); debug("]="); debug_record(waiting_buffer[i]); debug(" ");
    }
    debug("}\n");
}

#endif
