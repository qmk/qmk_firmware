#include <stdint.h>
#include <stdbool.h>

#include "action.h"
#include "action_layer.h"
#include "action_tapping.h"
#include "keycode.h"
#include "timer.h"

#ifndef NO_ACTION_TAPPING

#    if defined(IGNORE_MOD_TAP_INTERRUPT_PER_KEY)
#        error "IGNORE_MOD_TAP_INTERRUPT_PER_KEY has been removed; the code needs to be ported to use HOLD_ON_OTHER_KEY_PRESS_PER_KEY instead."
#    elif defined(IGNORE_MOD_TAP_INTERRUPT)
#        error "IGNORE_MOD_TAP_INTERRUPT is no longer necessary as it is now the default behavior of mod-tap keys. Please remove it from your config."
#    endif

#    ifndef COMBO_ENABLE
#        define IS_TAPPING_RECORD(r) (KEYEQ(tapping_key.event.key, (r->event.key)))
#    else
#        define IS_TAPPING_RECORD(r) (KEYEQ(tapping_key.event.key, (r->event.key)) && tapping_key.keycode == r->keycode)
#    endif
#    define WITHIN_TAPPING_TERM(e) (TIMER_DIFF_16(e.time, tapping_key.event.time) < GET_TAPPING_TERM(get_record_keycode(&tapping_key, false), &tapping_key))
#    define WITHIN_QUICK_TAP_TERM(e) (TIMER_DIFF_16(e.time, tapping_key.event.time) < GET_QUICK_TAP_TERM(get_record_keycode(&tapping_key, false), &tapping_key))

#    ifdef DYNAMIC_TAPPING_TERM_ENABLE
uint16_t g_tapping_term = TAPPING_TERM;
#    endif

#    ifdef TAPPING_TERM_PER_KEY
__attribute__((weak)) uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
#        ifdef DYNAMIC_TAPPING_TERM_ENABLE
    return g_tapping_term;
#        else
    return TAPPING_TERM;
#        endif
}
#    endif

#    ifdef QUICK_TAP_TERM_PER_KEY
__attribute__((weak)) uint16_t get_quick_tap_term(uint16_t keycode, keyrecord_t *record) {
    return QUICK_TAP_TERM;
}
#    endif

#    ifdef PERMISSIVE_HOLD_PER_KEY
__attribute__((weak)) bool get_permissive_hold(uint16_t keycode, keyrecord_t *record) {
    return false;
}
#    endif

#    ifdef HOLD_ON_OTHER_KEY_PRESS_PER_KEY
__attribute__((weak)) bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
    return false;
}
#    endif

#    if defined(AUTO_SHIFT_ENABLE) && defined(RETRO_SHIFT)
#        include "process_auto_shift.h"
#    endif

static keyrecord_t tapping_key                         = {};
static keyrecord_t waiting_buffer[WAITING_BUFFER_SIZE] = {};
static uint8_t     waiting_buffer_head                 = 0;
static uint8_t     waiting_buffer_tail                 = 0;

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
void action_tapping_process(keyrecord_t record) {
    if (process_tapping(&record)) {
        if (IS_EVENT(record.event)) {
            ac_dprintf("processed: ");
            debug_record(record);
            ac_dprintf("\n");
        }
    } else {
        if (!waiting_buffer_enq(record)) {
            // clear all in case of overflow.
            ac_dprintf("OVERFLOW: CLEAR ALL STATES\n");
            clear_keyboard();
            waiting_buffer_clear();
            tapping_key = (keyrecord_t){0};
        }
    }

    // process waiting_buffer
    if (IS_EVENT(record.event) && waiting_buffer_head != waiting_buffer_tail) {
        ac_dprintf("---- action_exec: process waiting_buffer -----\n");
    }
    for (; waiting_buffer_tail != waiting_buffer_head; waiting_buffer_tail = (waiting_buffer_tail + 1) % WAITING_BUFFER_SIZE) {
        if (process_tapping(&waiting_buffer[waiting_buffer_tail])) {
            ac_dprintf("processed: waiting_buffer[%u] =", waiting_buffer_tail);
            debug_record(waiting_buffer[waiting_buffer_tail]);
            ac_dprintf("\n\n");
        } else {
            break;
        }
    }
    if (IS_EVENT(record.event)) {
        ac_dprintf("\n");
    }
}

/* Some conditionally defined helper macros to keep process_tapping more
 * readable. The conditional definition of tapping_keycode and all the
 * conditional uses of it are hidden inside macros named TAP_...
 */
#    if (defined(AUTO_SHIFT_ENABLE) && defined(RETRO_SHIFT)) || defined(PERMISSIVE_HOLD_PER_KEY) || defined(HOLD_ON_OTHER_KEY_PRESS_PER_KEY)
#        define TAP_DEFINE_KEYCODE const uint16_t tapping_keycode = get_record_keycode(&tapping_key, false)
#    else
#        define TAP_DEFINE_KEYCODE
#    endif

#    if defined(AUTO_SHIFT_ENABLE) && defined(RETRO_SHIFT)
#        ifdef RETRO_TAPPING_PER_KEY
#            define TAP_GET_RETRO_TAPPING get_retro_tapping(tapping_keycode, &tapping_key)
#        else
#            define TAP_GET_RETRO_TAPPING true
#        endif
#        define MAYBE_RETRO_SHIFTING(ev) (TAP_GET_RETRO_TAPPING && (RETRO_SHIFT + 0) != 0 && TIMER_DIFF_16((ev).time, tapping_key.event.time) < (RETRO_SHIFT + 0))
#        define TAP_IS_LT IS_QK_LAYER_TAP(tapping_keycode)
#        define TAP_IS_MT IS_QK_MOD_TAP(tapping_keycode)
#        define TAP_IS_RETRO IS_RETRO(tapping_keycode)
#    else
#        define TAP_GET_RETRO_TAPPING false
#        define MAYBE_RETRO_SHIFTING(ev) false
#        define TAP_IS_LT false
#        define TAP_IS_MT false
#        define TAP_IS_RETRO false
#    endif

#    ifdef PERMISSIVE_HOLD_PER_KEY
#        define TAP_GET_PERMISSIVE_HOLD get_permissive_hold(tapping_keycode, &tapping_key)
#    elif defined(PERMISSIVE_HOLD)
#        define TAP_GET_PERMISSIVE_HOLD true
#    else
#        define TAP_GET_PERMISSIVE_HOLD false
#    endif

#    ifdef HOLD_ON_OTHER_KEY_PRESS_PER_KEY
#        define TAP_GET_HOLD_ON_OTHER_KEY_PRESS get_hold_on_other_key_press(tapping_keycode, &tapping_key)
#    elif defined(HOLD_ON_OTHER_KEY_PRESS)
#        define TAP_GET_HOLD_ON_OTHER_KEY_PRESS true
#    else
#        define TAP_GET_HOLD_ON_OTHER_KEY_PRESS false
#    endif

/** \brief Tapping
 *
 * Rule: Tap key is typed(pressed and released) within TAPPING_TERM.
 *       (without interfering by typing other key)
 */
/* return true when key event is processed or consumed. */
bool process_tapping(keyrecord_t *keyp) {
    const keyevent_t event = keyp->event;

    // state machine is in the "reset" state, no tapping key is to be
    // processed
    if (IS_NOEVENT(tapping_key.event)) {
        if (!IS_EVENT(event)) {
            // early return for tick events
        } else if (event.pressed && is_tap_record(keyp)) {
            // the currently pressed key is a tapping key, therefore transition
            // into the "pressed" tapping key state
            ac_dprintf("Tapping: Start(Press tap key).\n");
            tapping_key = *keyp;
            process_record_tap_hint(&tapping_key);
            waiting_buffer_scan_tap();
            debug_tapping_key();
        } else {
            // the current key is just a regular key, pass it on for regular
            // processing
            process_record(keyp);
        }

        return true;
    }

    TAP_DEFINE_KEYCODE;

    // process "pressed" tapping key state
    if (tapping_key.event.pressed) {
        if (WITHIN_TAPPING_TERM(event) || MAYBE_RETRO_SHIFTING(event)) {
            if (IS_NOEVENT(event)) {
                // early return for tick events
                return true;
            }
            if (tapping_key.tap.count == 0) {
                if (IS_TAPPING_RECORD(keyp) && !event.pressed) {
#    if defined(AUTO_SHIFT_ENABLE) && defined(RETRO_SHIFT)
                    retroshift_swap_times();
#    endif
                    // first tap!
                    ac_dprintf("Tapping: First tap(0->1).\n");
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
                // clang-format off
                else if (
                    (
                        !event.pressed && waiting_buffer_typed(event) &&
                        TAP_GET_PERMISSIVE_HOLD
                    )
                    // Causes nested taps to not wait past TAPPING_TERM/RETRO_SHIFT
                    // unnecessarily and fixes them for Layer Taps.
                    || (TAP_GET_RETRO_TAPPING &&
                        (
                            // Rolled over the two keys.
                            (tapping_key.tap.interrupted == true && (
                                (TAP_IS_LT && TAP_GET_HOLD_ON_OTHER_KEY_PRESS) ||
                                (TAP_IS_MT && TAP_GET_HOLD_ON_OTHER_KEY_PRESS)
                                )
                            )
                            // Makes Retro Shift ignore the default behavior of
                            // MTs and LTs on nested taps below TAPPING_TERM or RETRO_SHIFT
                            || (
                                TAP_IS_RETRO
                                && (event.key.col != tapping_key.event.key.col || event.key.row != tapping_key.event.key.row)
                                && !event.pressed && waiting_buffer_typed(event)
                            )
                        )
                    )
                ) {
                    // clang-format on
                    ac_dprintf("Tapping: End. No tap. Interfered by typing key\n");
                    process_record(&tapping_key);
                    tapping_key = (keyrecord_t){0};
                    debug_tapping_key();
                    // enqueue
                    return false;
                }
                /* Process release event of a key pressed before tapping starts
                 * Without this unexpected repeating will occur with having fast repeating setting
                 * https://github.com/tmk/tmk_keyboard/issues/60
                 */
                else if (!event.pressed && !waiting_buffer_typed(event)) {
                    // Modifier/Layer should be retained till end of this tapping.
                    action_t action = layer_switch_get_action(event.key);
                    switch (action.kind.id) {
                        case ACT_LMODS:
                        case ACT_RMODS:
                            if (action.key.mods && !action.key.code) return false;
                            if (IS_MODIFIER_KEYCODE(action.key.code)) return false;
                            break;
                        case ACT_LMODS_TAP:
                        case ACT_RMODS_TAP:
                            if (action.key.mods && keyp->tap.count == 0) return false;
                            if (IS_MODIFIER_KEYCODE(action.key.code)) return false;
                            break;
                        case ACT_LAYER_TAP:
                        case ACT_LAYER_TAP_EXT:
                            switch (action.layer_tap.code) {
                                case 0 ...(OP_TAP_TOGGLE - 1):
                                case OP_ON_OFF:
                                case OP_OFF_ON:
                                case OP_SET_CLEAR:
                                    return false;
                            }
                            break;
                    }
                    // Release of key should be process immediately.
                    ac_dprintf("Tapping: release event of a key pressed before tapping\n");
                    process_record(keyp);
                    return true;
                } else {
                    // set interrupted flag when other key preesed during tapping
                    if (event.pressed) {
                        tapping_key.tap.interrupted = true;
                        if (TAP_GET_HOLD_ON_OTHER_KEY_PRESS) {
                            ac_dprintf("Tapping: End. No tap. Interfered by pressed key\n");
                            process_record(&tapping_key);
                            tapping_key = (keyrecord_t){0};
                            debug_tapping_key();
                            // enqueue
                            return false;
                        }
                    }
                    // enqueue
                    return false;
                }
            }
            // tap_count > 0
            else {
                if (IS_TAPPING_RECORD(keyp) && !event.pressed) {
                    ac_dprintf("Tapping: Tap release(%u)\n", tapping_key.tap.count);
                    keyp->tap = tapping_key.tap;
                    process_record(keyp);
                    tapping_key = *keyp;
                    debug_tapping_key();
                    return true;
                } else if (is_tap_record(keyp) && event.pressed) {
                    if (tapping_key.tap.count > 1) {
                        ac_dprintf("Tapping: Start new tap with releasing last tap(>1).\n");
                        // unregister key
                        process_record(&(keyrecord_t){
                            .tap           = tapping_key.tap,
                            .event.key     = tapping_key.event.key,
                            .event.time    = event.time,
                            .event.pressed = false,
                            .event.type    = tapping_key.event.type,
#    ifdef COMBO_ENABLE
                            .keycode = tapping_key.keycode,
#    endif
                        });
                    } else {
                        ac_dprintf("Tapping: Start while last tap(1).\n");
                    }
                    tapping_key = *keyp;
                    waiting_buffer_scan_tap();
                    debug_tapping_key();
                    return true;
                } else {
                    ac_dprintf("Tapping: key event while last tap(>0).\n");
                    process_record(keyp);
                    return true;
                }
            }
        }
        // after TAPPING_TERM
        else {
            if (tapping_key.tap.count == 0) {
                ac_dprintf("Tapping: End. Timeout. Not tap(0): ");
                debug_event(event);
                ac_dprintf("\n");
                process_record(&tapping_key);
                tapping_key = (keyrecord_t){0};
                debug_tapping_key();
                return false;
            } else {
                if (IS_NOEVENT(event)) {
                    return true;
                }
                if (IS_TAPPING_RECORD(keyp) && !event.pressed) {
                    ac_dprintf("Tapping: End. last timeout tap release(>0).");
                    keyp->tap = tapping_key.tap;
                    process_record(keyp);
                    tapping_key = (keyrecord_t){0};
                    return true;
                } else if (is_tap_record(keyp) && event.pressed) {
                    if (tapping_key.tap.count > 1) {
                        ac_dprintf("Tapping: Start new tap with releasing last timeout tap(>1).\n");
                        // unregister key
                        process_record(&(keyrecord_t){
                            .tap           = tapping_key.tap,
                            .event.key     = tapping_key.event.key,
                            .event.time    = event.time,
                            .event.pressed = false,
                            .event.type    = tapping_key.event.type,
#    ifdef COMBO_ENABLE
                            .keycode = tapping_key.keycode,
#    endif
                        });
                    } else {
                        ac_dprintf("Tapping: Start while last timeout tap(1).\n");
                    }
                    tapping_key = *keyp;
                    waiting_buffer_scan_tap();
                    debug_tapping_key();
                    return true;
                } else {
                    ac_dprintf("Tapping: key event while last timeout tap(>0).\n");
                    process_record(keyp);
                    return true;
                }
            }
        }
    }
    // process "released" tapping key state
    else {
        if (WITHIN_TAPPING_TERM(event) || MAYBE_RETRO_SHIFTING(event)) {
            if (IS_NOEVENT(event)) {
                // early return for tick events
                return true;
            }
            if (event.pressed) {
                if (IS_TAPPING_RECORD(keyp)) {
                    if (WITHIN_QUICK_TAP_TERM(event) && !tapping_key.tap.interrupted && tapping_key.tap.count > 0) {
                        // sequential tap.
                        keyp->tap = tapping_key.tap;
                        if (keyp->tap.count < 15) keyp->tap.count += 1;
                        ac_dprintf("Tapping: Tap press(%u)\n", keyp->tap.count);
                        process_record(keyp);
                        tapping_key = *keyp;
                        debug_tapping_key();
                        return true;
                    }
                    // FIX: start new tap again
                    tapping_key = *keyp;
                    return true;
                } else if (is_tap_record(keyp)) {
                    // Sequential tap can be interfered with other tap key.
                    ac_dprintf("Tapping: Start with interfering other tap.\n");
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
                ac_dprintf("Tapping: other key just after tap.\n");
                process_record(keyp);
                return true;
            }
        } else {
            // Timeout - reset state machine.
            ac_dprintf("Tapping: End(Timeout after releasing last tap): ");
            debug_event(event);
            ac_dprintf("\n");
            tapping_key = (keyrecord_t){0};
            debug_tapping_key();
            return false;
        }
    }
}

/** \brief Waiting buffer enq
 *
 * FIXME: Needs docs
 */
bool waiting_buffer_enq(keyrecord_t record) {
    if (IS_NOEVENT(record.event)) {
        return true;
    }

    if ((waiting_buffer_head + 1) % WAITING_BUFFER_SIZE == waiting_buffer_tail) {
        ac_dprintf("waiting_buffer_enq: Over flow.\n");
        return false;
    }

    waiting_buffer[waiting_buffer_head] = record;
    waiting_buffer_head                 = (waiting_buffer_head + 1) % WAITING_BUFFER_SIZE;

    ac_dprintf("waiting_buffer_enq: ");
    debug_waiting_buffer();
    return true;
}

/** \brief Waiting buffer clear
 *
 * FIXME: Needs docs
 */
void waiting_buffer_clear(void) {
    waiting_buffer_head = 0;
    waiting_buffer_tail = 0;
}

/** \brief Waiting buffer typed
 *
 * FIXME: Needs docs
 */
bool waiting_buffer_typed(keyevent_t event) {
    for (uint8_t i = waiting_buffer_tail; i != waiting_buffer_head; i = (i + 1) % WAITING_BUFFER_SIZE) {
        if (KEYEQ(event.key, waiting_buffer[i].event.key) && event.pressed != waiting_buffer[i].event.pressed) {
            return true;
        }
    }
    return false;
}

/** \brief Waiting buffer has anykey pressed
 *
 * FIXME: Needs docs
 */
__attribute__((unused)) bool waiting_buffer_has_anykey_pressed(void) {
    for (uint8_t i = waiting_buffer_tail; i != waiting_buffer_head; i = (i + 1) % WAITING_BUFFER_SIZE) {
        if (waiting_buffer[i].event.pressed) return true;
    }
    return false;
}

/** \brief Scan buffer for tapping
 *
 * FIXME: Needs docs
 */
void waiting_buffer_scan_tap(void) {
    // early return if:
    // - tapping already is settled
    // - invalid state: tapping_key released && tap.count == 0
    if ((tapping_key.tap.count > 0) || !tapping_key.event.pressed) {
        return;
    }

    for (uint8_t i = waiting_buffer_tail; i != waiting_buffer_head; i = (i + 1) % WAITING_BUFFER_SIZE) {
        keyrecord_t *candidate = &waiting_buffer[i];
        if (IS_EVENT(candidate->event) && KEYEQ(candidate->event.key, tapping_key.event.key) && !candidate->event.pressed && WITHIN_TAPPING_TERM(candidate->event)) {
            tapping_key.tap.count = 1;
            candidate->tap.count  = 1;
            process_record(&tapping_key);

            ac_dprintf("waiting_buffer_scan_tap: found at [%u]\n", i);
            debug_waiting_buffer();
            return;
        }
    }
}

/** \brief Tapping key debug print
 *
 * FIXME: Needs docs
 */
static void debug_tapping_key(void) {
    ac_dprintf("TAPPING_KEY=");
    debug_record(tapping_key);
    ac_dprintf("\n");
}

/** \brief Waiting buffer debug print
 *
 * FIXME: Needs docs
 */
static void debug_waiting_buffer(void) {
    ac_dprintf("{ ");
    for (uint8_t i = waiting_buffer_tail; i != waiting_buffer_head; i = (i + 1) % WAITING_BUFFER_SIZE) {
        ac_dprintf("[%u]=", i);
        debug_record(waiting_buffer[i]);
        ac_dprintf(" ");
    }
    ac_dprintf("}\n");
}

#endif
