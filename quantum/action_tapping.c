#include <stdint.h>
#include <stdbool.h>

#include "action.h"
#include "action_layer.h"
#include "action_tapping.h"
#include "action_util.h"
#include "keycode.h"
#include "keycode_config.h"
#include "quantum_keycodes.h"
#include "timer.h"
#include "wait.h"

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

#    ifdef SPECULATIVE_HOLD
typedef struct {
    keypos_t key;
    uint8_t  mods;
} speculative_key_t;
#        define SPECULATIVE_KEYS_SIZE 8
static speculative_key_t speculative_keys[SPECULATIVE_KEYS_SIZE] = {};
static uint8_t           num_speculative_keys                    = 0;
static uint8_t           prev_speculative_mods                   = 0;
static uint8_t           speculative_mods                        = 0;

/** Handler to be called on incoming press events. */
static void speculative_key_press(keyrecord_t *record);
#    endif // SPECULATIVE_HOLD

#    if defined(CHORDAL_HOLD) || defined(FLOW_TAP_TERM)
#        define REGISTERED_TAPS_SIZE 8
// Array of tap-hold keys that have been settled as tapped but not yet released.
static keypos_t registered_taps[REGISTERED_TAPS_SIZE] = {};
static uint8_t  num_registered_taps                   = 0;

/** Adds `key` to the registered_taps array. */
static void registered_taps_add(keypos_t key);
/** Returns the index of `key` in registered_taps, or -1 if not found. */
static int8_t registered_tap_find(keypos_t key);
/** Removes index `i` from the registered_taps array. */
static void registered_taps_del_index(uint8_t i);
/** Logs the registered_taps array for debugging. */
static void debug_registered_taps(void);

static bool is_mt_or_lt(uint16_t keycode) {
    return IS_QK_MOD_TAP(keycode) || IS_QK_LAYER_TAP(keycode);
}
#    endif // defined(CHORDAL_HOLD) || defined(FLOW_TAP_TERM)

#    if defined(CHORDAL_HOLD)
extern const char chordal_hold_layout[MATRIX_ROWS][MATRIX_COLS] PROGMEM;

/** \brief Finds which queued events should be held according to Chordal Hold.
 *
 * In a situation with multiple unsettled tap-hold key presses, scan the queue
 * up until the first release, non-tap-hold, or one-shot event and find the
 * latest event in the queue that settles as held according to
 * get_chordal_hold().
 *
 * \return Index of the first tap, or equivalently, one past the latest hold.
 */
static uint8_t waiting_buffer_find_chordal_hold_tap(void);

/** Processes queued events up to and including `key` as tapped. */
static void waiting_buffer_chordal_hold_taps_until(keypos_t key);

/** \brief Processes and pops buffered events until the first tap-hold event. */
static void waiting_buffer_process_regular(void);
#    endif // CHORDAL_HOLD

#    ifdef HOLD_ON_OTHER_KEY_PRESS_PER_KEY
__attribute__((weak)) bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
    return false;
}
#    endif

#    if defined(AUTO_SHIFT_ENABLE) && defined(RETRO_SHIFT)
#        include "process_auto_shift.h"
#    endif

#    if defined(FLOW_TAP_TERM)
static uint16_t flow_tap_prev_keycode = KC_NO;
static uint16_t flow_tap_prev_time    = 0;
static bool     flow_tap_expired      = true;

static bool flow_tap_key_if_within_term(keyrecord_t *record, uint16_t prev_time);
#    endif // defined(FLOW_TAP_TERM)

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
#    ifdef SPECULATIVE_HOLD
    prev_speculative_mods = speculative_mods;
    if (record.event.pressed) {
        speculative_key_press(&record);
    }
#    endif // SPECULATIVE_HOLD

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

#    ifdef SPECULATIVE_HOLD
    if (speculative_mods != prev_speculative_mods) {
        send_keyboard_report();
    }
#    endif // SPECULATIVE_HOLD

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
    } else {
#    ifdef FLOW_TAP_TERM
        if (!flow_tap_expired && TIMER_DIFF_16(record.event.time, flow_tap_prev_time) >= INT16_MAX / 2) {
            flow_tap_expired = true;
        }
#    endif // FLOW_TAP_TERM
    }
}

/* Some conditionally defined helper macros to keep process_tapping more
 * readable. The conditional definition of tapping_keycode and all the
 * conditional uses of it are hidden inside macros named TAP_...
 */
#    define TAP_DEFINE_KEYCODE const uint16_t tapping_keycode = get_record_keycode(&tapping_key, false)

#    if defined(AUTO_SHIFT_ENABLE) && defined(RETRO_SHIFT)
#        ifdef RETRO_TAPPING_PER_KEY
#            define TAP_GET_RETRO_TAPPING(keyp) get_auto_shifted_key(tapping_keycode, keyp) && get_retro_tapping(tapping_keycode, &tapping_key)
#        else
#            define TAP_GET_RETRO_TAPPING(keyp) get_auto_shifted_key(tapping_keycode, keyp)
#        endif
/* Used to extend TAPPING_TERM:
 *     indefinitely if RETRO_SHIFT does not have a value
 *     to RETRO_SHIFT if RETRO_SHIFT is set
 * for possibly retro shifted keys.
 */
#        define MAYBE_RETRO_SHIFTING(ev, keyp) (get_auto_shifted_key(tapping_keycode, keyp) && TAP_GET_RETRO_TAPPING(keyp) && ((RETRO_SHIFT + 0) == 0 || TIMER_DIFF_16((ev).time, tapping_key.event.time) < (RETRO_SHIFT + 0)))
#        define TAP_IS_LT IS_QK_LAYER_TAP(tapping_keycode)
#        define TAP_IS_MT IS_QK_MOD_TAP(tapping_keycode)
#        define TAP_IS_RETRO IS_RETRO(tapping_keycode)
#    else
#        define TAP_GET_RETRO_TAPPING(keyp) false
#        define MAYBE_RETRO_SHIFTING(ev, kp) false
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

#    if defined(CHORDAL_HOLD) || defined(FLOW_TAP_TERM)
    if (!event.pressed) {
        const int8_t i = registered_tap_find(event.key);
        if (i != -1) {
            // If a tap-hold key was previously settled as tapped, set its
            // tap.count correspondingly on release.
            keyp->tap.count = 1;
            registered_taps_del_index(i);
            ac_dprintf("Found tap release for [%d]\n", i);
            debug_registered_taps();
        }
    }
#    endif // defined(CHORDAL_HOLD) || defined(FLOW_TAP_TERM)

    // state machine is in the "reset" state, no tapping key is to be
    // processed
    if (IS_NOEVENT(tapping_key.event)) {
        if (!IS_EVENT(event)) {
            // early return for tick events
        } else if (event.pressed && is_tap_record(keyp)) {
            // the currently pressed key is a tapping key, therefore transition
            // into the "pressed" tapping key state

#    if defined(FLOW_TAP_TERM)
            if (flow_tap_key_if_within_term(keyp, flow_tap_prev_time)) {
                return true;
            }
#    endif // defined(FLOW_TAP_TERM)

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

#    if (defined(AUTO_SHIFT_ENABLE) && defined(RETRO_SHIFT)) || defined(PERMISSIVE_HOLD_PER_KEY) || defined(CHORDAL_HOLD) || defined(HOLD_ON_OTHER_KEY_PRESS_PER_KEY)
    TAP_DEFINE_KEYCODE;
#    endif

    // process "pressed" tapping key state
    if (tapping_key.event.pressed) {
        if (WITHIN_TAPPING_TERM(event) || MAYBE_RETRO_SHIFTING(event, keyp)) {
            if (IS_NOEVENT(event)) {
                // early return for tick events
                return true;
            }

            if (tapping_key.tap.count == 0) {
                if (IS_TAPPING_RECORD(keyp) && !event.pressed) {
                    // first tap!
                    ac_dprintf("Tapping: First tap(0->1).\n");
                    tapping_key.tap.count = 1;
                    debug_tapping_key();
                    process_record(&tapping_key);

                    // copy tapping state
                    keyp->tap = tapping_key.tap;

#    if defined(FLOW_TAP_TERM)
                    // Now that tapping_key has settled as tapped, check whether
                    // Flow Tap applies to following yet-unsettled keys.
                    uint16_t prev_time = tapping_key.event.time;
                    for (; waiting_buffer_tail != waiting_buffer_head; waiting_buffer_tail = (waiting_buffer_tail + 1) % WAITING_BUFFER_SIZE) {
                        keyrecord_t *record = &waiting_buffer[waiting_buffer_tail];
                        if (!record->event.pressed) {
                            break;
                        }
                        const int16_t next_time = record->event.time;
                        if (!is_tap_record(record)) {
                            process_record(record);
                        } else if (!flow_tap_key_if_within_term(record, prev_time)) {
                            break;
                        }
                        prev_time = next_time;
                    }
                    debug_waiting_buffer();
#    endif // defined(FLOW_TAP_TERM)

                    // enqueue
                    return false;
                }
#    if defined(CHORDAL_HOLD)
                else if (is_mt_or_lt(tapping_keycode) && !event.pressed && waiting_buffer_typed(event) && !get_chordal_hold(tapping_keycode, &tapping_key, get_record_keycode(keyp, false), keyp)) {
                    // Key release that is not a chord with the tapping key.
                    // Settle the tapping key and any other pending tap-hold
                    // keys preceding the press of this key as tapped.

                    ac_dprintf("Tapping: End. Chord considered a tap\n");
                    tapping_key.tap.count = 1;
                    registered_taps_add(tapping_key.event.key);
                    process_record(&tapping_key);
                    tapping_key = (keyrecord_t){0};

                    waiting_buffer_chordal_hold_taps_until(event.key);
                    debug_registered_taps();
                    debug_waiting_buffer();
                    // enqueue
                    return false;
                }
#    endif      // CHORDAL_HOLD
                /* Process a key typed within TAPPING_TERM
                 * This can register the key before settlement of tapping,
                 * useful for long TAPPING_TERM but may prevent fast typing.
                 */
                // clang-format off
                else if (
                    !event.pressed && waiting_buffer_typed(event) &&
                    (
                        TAP_GET_PERMISSIVE_HOLD ||
                        // Causes nested taps to not wait past TAPPING_TERM/RETRO_SHIFT
                        // unnecessarily and fixes them for Layer Taps.
                        TAP_GET_RETRO_TAPPING(keyp)
                    )
                ) {
                    // clang-format on
                    ac_dprintf("Tapping: End. No tap. Interfered by typing key\n");
                    process_record(&tapping_key);

#    if defined(CHORDAL_HOLD)
                    uint8_t first_tap = waiting_buffer_find_chordal_hold_tap();
                    ac_dprintf("first_tap = %u\n", first_tap);
                    if (first_tap < WAITING_BUFFER_SIZE) {
                        for (; waiting_buffer_tail != first_tap; waiting_buffer_tail = (waiting_buffer_tail + 1) % WAITING_BUFFER_SIZE) {
                            ac_dprintf("Processing [%u]\n", waiting_buffer_tail);
                            process_record(&waiting_buffer[waiting_buffer_tail]);
                        }
                    }

                    waiting_buffer_chordal_hold_taps_until(event.key);
                    debug_registered_taps();
                    debug_waiting_buffer();
#    endif // CHORDAL_HOLD

                    tapping_key = (keyrecord_t){0};
                    debug_tapping_key();
                    // enqueue
                    return false;
                }
                /* Process release event of a key pressed before tapping starts
                 * Without this unexpected repeating will occur with having fast repeating setting
                 * https://github.com/tmk/tmk_keyboard/issues/60
                 *
                 * NOTE: This workaround causes events to process out of order,
                 * e.g. in a rolled press of three tap-hold keys like
                 *
                 *   "A down, B down, C down, A up, B up, C up"
                 *
                 * events are processed as
                 *
                 *   "A down, B down, A up, B up, C down, C up"
                 *
                 * It seems incorrect to process keyp before the tapping key.
                 * This workaround is old, from 2013. This might no longer
                 * be needed for the original problem it was meant to address.
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
                    // set interrupted flag when other key pressed during tapping
                    if (event.pressed) {
                        tapping_key.tap.interrupted = true;

#    if defined(CHORDAL_HOLD)
                        if (is_mt_or_lt(tapping_keycode) && !get_chordal_hold(tapping_keycode, &tapping_key, get_record_keycode(keyp, false), keyp)) {
                            // In process_action(), HOLD_ON_OTHER_KEY_PRESS
                            // will revert interrupted events to holds, so
                            // this needs to be set false.
                            tapping_key.tap.interrupted = false;

                            if (!is_tap_record(keyp)) {
                                ac_dprintf("Tapping: End. Chord considered a tap\n");
                                tapping_key.tap.count = 1;
                                registered_taps_add(tapping_key.event.key);
                                debug_registered_taps();
                                process_record(&tapping_key);
                                tapping_key = (keyrecord_t){0};
                            }
                        } else
#    endif // CHORDAL_HOLD
                            if (TAP_GET_HOLD_ON_OTHER_KEY_PRESS
#    if defined(AUTO_SHIFT_ENABLE) && defined(RETRO_SHIFT)
                                // Auto Shift cannot evaluate this early
                                // Retro Shift uses the hold action for all nested taps even without HOLD_ON_OTHER_KEY_PRESS, so this is fine to skip
                                && !(MAYBE_RETRO_SHIFTING(event, keyp) && get_auto_shifted_key(get_record_keycode(keyp, false), keyp))
#    endif
                            ) {
                            // Settle the tapping key as *held*, since
                            // HOLD_ON_OTHER_KEY_PRESS is enabled for this key.
                            ac_dprintf("Tapping: End. No tap. Interfered by pressed key\n");
                            process_record(&tapping_key);

#    if defined(CHORDAL_HOLD)
                            if (waiting_buffer_tail != waiting_buffer_head && is_tap_record(&waiting_buffer[waiting_buffer_tail])) {
                                tapping_key = waiting_buffer[waiting_buffer_tail];
                                // Pop tail from the queue.
                                waiting_buffer_tail = (waiting_buffer_tail + 1) % WAITING_BUFFER_SIZE;
                                debug_waiting_buffer();
                            } else
#    endif // CHORDAL_HOLD
                            {
                                tapping_key = (keyrecord_t){0};
                            }
                            debug_tapping_key();

#    if defined(CHORDAL_HOLD)
                            waiting_buffer_process_regular();
#    endif // CHORDAL_HOLD
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
#    if defined(AUTO_SHIFT_ENABLE) && defined(RETRO_SHIFT)
                    retroshift_swap_times();
#    endif
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
        if (WITHIN_TAPPING_TERM(event) || MAYBE_RETRO_SHIFTING(event, keyp)) {
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
#    if defined(FLOW_TAP_TERM)
                    if (flow_tap_key_if_within_term(keyp, flow_tap_prev_time)) {
                        tapping_key = (keyrecord_t){0};
                        debug_tapping_key();
                        return true;
                    }
#    endif // defined(FLOW_TAP_TERM)
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

#    if (defined(AUTO_SHIFT_ENABLE) && defined(RETRO_SHIFT))
    TAP_DEFINE_KEYCODE;
#    endif
    for (uint8_t i = waiting_buffer_tail; i != waiting_buffer_head; i = (i + 1) % WAITING_BUFFER_SIZE) {
        keyrecord_t *candidate = &waiting_buffer[i];
        // clang-format off
        if (IS_EVENT(candidate->event) && KEYEQ(candidate->event.key, tapping_key.event.key) && !candidate->event.pressed && (
            WITHIN_TAPPING_TERM(waiting_buffer[i].event) || MAYBE_RETRO_SHIFTING(waiting_buffer[i].event, &tapping_key)
        )) {
            // clang-format on
            tapping_key.tap.count = 1;
            candidate->tap.count  = 1;
            process_record(&tapping_key);

            ac_dprintf("waiting_buffer_scan_tap: found at [%u]\n", i);
            debug_waiting_buffer();
            return;
        }
    }
}

#    ifdef SPECULATIVE_HOLD
static void debug_speculative_keys(void) {
    ac_dprintf("mods = { ");
    for (int8_t i = 0; i < num_speculative_keys; ++i) {
        ac_dprintf("%02X ", speculative_keys[i].mods);
    }
    ac_dprintf("}, keys = { ");
    for (int8_t i = 0; i < num_speculative_keys; ++i) {
        ac_dprintf("%02X%02X ", speculative_keys[i].key.row, speculative_keys[i].key.col);
    }
    ac_dprintf("}\n");
}

// Find key in speculative_keys. Returns num_speculative_keys if not found.
static int8_t speculative_keys_find(keypos_t key) {
    uint8_t i;
    for (i = 0; i < num_speculative_keys; ++i) {
        if (KEYEQ(speculative_keys[i].key, key)) {
            break;
        }
    }
    return i;
}

static void speculative_key_press(keyrecord_t *record) {
    if (num_speculative_keys >= SPECULATIVE_KEYS_SIZE) { // Overflow!
        ac_dprintf("SPECULATIVE KEYS OVERFLOW: IGNORING EVENT\n");
        return; // Don't trigger: speculative_keys is full.
    }
    if (speculative_keys_find(record->event.key) < num_speculative_keys) {
        return; // Don't trigger: key is already in speculative_keys.
    }

    const uint16_t keycode = get_record_keycode(record, false);
    if (!IS_QK_MOD_TAP(keycode)) {
        return; // Don't trigger: not a mod-tap key.
    }

    uint8_t mods = mod_config(QK_MOD_TAP_GET_MODS(keycode));
    if ((mods & 0x10) != 0) { // Unpack 5-bit mods to 8-bit representation.
        mods <<= 4;
    }
    if ((~(get_mods() | speculative_mods) & mods) == 0) {
        return; // Don't trigger: mods are already active.
    }

    // Don't do Speculative Hold when there are non-speculated buffered events,
    // since that could result in sending keys out of order.
    for (uint8_t i = waiting_buffer_tail; i != waiting_buffer_head; i = (i + 1) % WAITING_BUFFER_SIZE) {
        if (!waiting_buffer[i].tap.speculated) {
            return;
        }
    }

    if (get_speculative_hold(keycode, record)) {
        record->tap.speculated = true;
        speculative_mods |= mods;
        // Remember the keypos and mods associated with this key.
        speculative_keys[num_speculative_keys] = (speculative_key_t){
            .key  = record->event.key,
            .mods = mods,
        };
        ++num_speculative_keys;

        ac_dprintf("Speculative Hold: ");
        debug_speculative_keys();
    }
}

uint8_t get_speculative_mods(void) {
    return speculative_mods;
}

__attribute__((weak)) bool get_speculative_hold(uint16_t keycode, keyrecord_t *record) {
    const uint8_t mods = mod_config(QK_MOD_TAP_GET_MODS(keycode));
    return (mods & (MOD_LCTL | MOD_LSFT)) == mods;
}

void speculative_key_settled(keyrecord_t *record) {
    if (num_speculative_keys == 0) {
        return; // Early return when there are no active speculative keys.
    }

    uint8_t i = speculative_keys_find(record->event.key);

    const uint16_t keycode = get_record_keycode(record, false);
    if (IS_QK_MOD_TAP(keycode) && record->tap.count == 0) { // MT hold press.
        if (i < num_speculative_keys) {
            --num_speculative_keys;
            const uint8_t cleared_mods = speculative_keys[i].mods;

            if (num_speculative_keys) {
                speculative_mods &= ~cleared_mods;
                // Don't call send_keyboard_report() here; allow default
                // handling to reapply the mod before the next report.

                // Remove the ith entry from speculative_keys.
                for (uint8_t j = i; j < num_speculative_keys; ++j) {
                    speculative_keys[j] = speculative_keys[j + 1];
                }
            } else {
                speculative_mods = 0;
            }

            ac_dprintf("Speculative Hold: settled %02x, ", cleared_mods);
            debug_speculative_keys();
        }
    } else { // Tap press event; cancel speculatively-held mod.
        if (i >= num_speculative_keys) {
            i = 0;
        }

        // Clear mods for the ith key and all keys that follow.
        uint8_t cleared_mods = 0;
        for (uint8_t j = i; j < num_speculative_keys; ++j) {
            cleared_mods |= speculative_keys[j].mods;
        }

        num_speculative_keys = i; // Remove ith and following entries.

        if ((prev_speculative_mods & cleared_mods) != 0) {
#        ifdef DUMMY_MOD_NEUTRALIZER_KEYCODE
            neutralize_flashing_modifiers(get_mods() | prev_speculative_mods);
#        endif // DUMMY_MOD_NEUTRALIZER_KEYCODE
        }

        if (num_speculative_keys) {
            speculative_mods &= ~cleared_mods;
        } else {
            speculative_mods = 0;
        }

        send_keyboard_report();
        wait_ms(TAP_CODE_DELAY);

        ac_dprintf("Speculative Hold: canceled %02x, ", cleared_mods);
        debug_speculative_keys();
    }
}
#    endif // SPECULATIVE_HOLD

#    if defined(CHORDAL_HOLD) || defined(FLOW_TAP_TERM)
static void registered_taps_add(keypos_t key) {
    if (num_registered_taps >= REGISTERED_TAPS_SIZE) {
        ac_dprintf("TAPS OVERFLOW: CLEAR ALL STATES\n");
        clear_keyboard();
        num_registered_taps = 0;
    }

    registered_taps[num_registered_taps] = key;
    ++num_registered_taps;
}

static int8_t registered_tap_find(keypos_t key) {
    for (int8_t i = 0; i < num_registered_taps; ++i) {
        if (KEYEQ(registered_taps[i], key)) {
            return i;
        }
    }
    return -1;
}

static void registered_taps_del_index(uint8_t i) {
    if (i < num_registered_taps) {
        --num_registered_taps;
        if (i < num_registered_taps) {
            registered_taps[i] = registered_taps[num_registered_taps];
        }
    }
}

static void debug_registered_taps(void) {
    ac_dprintf("registered_taps = { ");
    for (int8_t i = 0; i < num_registered_taps; ++i) {
        ac_dprintf("%02X%02X ", registered_taps[i].row, registered_taps[i].col);
    }
    ac_dprintf("}\n");
}

#    endif // defined(CHORDAL_HOLD) || defined(FLOW_TAP_TERM)

#    ifdef CHORDAL_HOLD
__attribute__((weak)) bool get_chordal_hold(uint16_t tap_hold_keycode, keyrecord_t *tap_hold_record, uint16_t other_keycode, keyrecord_t *other_record) {
    return get_chordal_hold_default(tap_hold_record, other_record);
}

bool get_chordal_hold_default(keyrecord_t *tap_hold_record, keyrecord_t *other_record) {
    if (tap_hold_record->event.type != KEY_EVENT || other_record->event.type != KEY_EVENT) {
        return true; // Return true on combos or other non-key events.
    }

    char tap_hold_hand = chordal_hold_handedness(tap_hold_record->event.key);
    if (tap_hold_hand == '*') {
        return true;
    }
    char other_hand = chordal_hold_handedness(other_record->event.key);
    return other_hand == '*' || tap_hold_hand != other_hand;
}

__attribute__((weak)) char chordal_hold_handedness(keypos_t key) {
    return (char)pgm_read_byte(&chordal_hold_layout[key.row][key.col]);
}

static uint8_t waiting_buffer_find_chordal_hold_tap(void) {
    keyrecord_t *prev         = &tapping_key;
    uint16_t     prev_keycode = get_record_keycode(&tapping_key, false);
    uint8_t      first_tap    = WAITING_BUFFER_SIZE;
    for (uint8_t i = waiting_buffer_tail; i != waiting_buffer_head; i = (i + 1) % WAITING_BUFFER_SIZE) {
        keyrecord_t *  cur         = &waiting_buffer[i];
        const uint16_t cur_keycode = get_record_keycode(cur, false);
        if (!cur->event.pressed || !is_mt_or_lt(prev_keycode)) {
            break;
        } else if (get_chordal_hold(prev_keycode, prev, cur_keycode, cur)) {
            first_tap = i; // Track one index past the latest hold.
        }
        prev         = cur;
        prev_keycode = cur_keycode;
    }
    return first_tap;
}

static void waiting_buffer_chordal_hold_taps_until(keypos_t key) {
    while (waiting_buffer_tail != waiting_buffer_head) {
        keyrecord_t *record = &waiting_buffer[waiting_buffer_tail];
        ac_dprintf("waiting_buffer_chordal_hold_taps_until: processing [%u]\n", waiting_buffer_tail);
        if (record->event.pressed && is_tap_record(record)) {
            record->tap.count = 1;
            registered_taps_add(record->event.key);
        }
        process_record(record);
        waiting_buffer_tail = (waiting_buffer_tail + 1) % WAITING_BUFFER_SIZE;

        if (KEYEQ(key, record->event.key) && record->event.pressed) {
            break;
        }
    }
}

static void waiting_buffer_process_regular(void) {
    for (; waiting_buffer_tail != waiting_buffer_head; waiting_buffer_tail = (waiting_buffer_tail + 1) % WAITING_BUFFER_SIZE) {
        if (is_tap_record(&waiting_buffer[waiting_buffer_tail])) {
            break; // Stop once a tap-hold key event is reached.
        }
        ac_dprintf("waiting_buffer_process_regular: processing [%u]\n", waiting_buffer_tail);
        process_record(&waiting_buffer[waiting_buffer_tail]);
    }
    debug_waiting_buffer();
}
#    endif // CHORDAL_HOLD

#    ifdef FLOW_TAP_TERM
void flow_tap_update_last_event(keyrecord_t *record) {
    const uint16_t keycode = get_record_keycode(record, false);
    // Don't update while a tap-hold key is unsettled.
    if (record->tap.count == 0 && (waiting_buffer_tail != waiting_buffer_head || (tapping_key.event.pressed && tapping_key.tap.count == 0))) {
        return;
    }
    // Ignore releases of modifiers and held layer switches.
    if (!record->event.pressed) {
        switch (keycode) {
            case MODIFIER_KEYCODE_RANGE:
            case QK_MOMENTARY ... QK_MOMENTARY_MAX:
            case QK_LAYER_TAP_TOGGLE ... QK_LAYER_TAP_TOGGLE_MAX:
#        ifndef NO_ACTION_ONESHOT // Ignore one-shot keys.
            case QK_ONE_SHOT_MOD ... QK_ONE_SHOT_MOD_MAX:
            case QK_ONE_SHOT_LAYER ... QK_ONE_SHOT_LAYER_MAX:
#        endif                  // NO_ACTION_ONESHOT
#        ifdef TRI_LAYER_ENABLE // Ignore Tri Layer keys.
            case QK_TRI_LAYER_LOWER:
            case QK_TRI_LAYER_UPPER:
#        endif // TRI_LAYER_ENABLE
                return;
            case QK_MODS ... QK_MODS_MAX:
                if (QK_MODS_GET_BASIC_KEYCODE(keycode) == KC_NO) {
                    return;
                }
                break;
            case QK_MOD_TAP ... QK_MOD_TAP_MAX:
            case QK_LAYER_TAP ... QK_LAYER_TAP_MAX:
                if (record->tap.count == 0) {
                    return;
                }
                break;
        }
    }

    flow_tap_prev_keycode = keycode;
    flow_tap_prev_time    = record->event.time;
    flow_tap_expired      = false;
}

static bool flow_tap_key_if_within_term(keyrecord_t *record, uint16_t prev_time) {
    const uint16_t idle_time = TIMER_DIFF_16(record->event.time, prev_time);
    if (flow_tap_expired || idle_time >= 500) {
        return false;
    }

    const uint16_t keycode = get_record_keycode(record, false);
    if (is_mt_or_lt(keycode)) {
        uint16_t term = get_flow_tap_term(keycode, record, flow_tap_prev_keycode);
        if (term > 500) {
            term = 500;
        }
        if (idle_time < term) {
            debug_event(record->event);
            ac_dprintf(" within flow tap term (%u < %u) considered a tap\n", idle_time, term);
            record->tap.count = 1;
            registered_taps_add(record->event.key);
            debug_registered_taps();
            process_record(record);
            return true;
        }
    }
    return false;
}

// Checks both flow_tap_expired flag and elapsed time to determine
// if the key is within the flow tap term.
bool within_flow_tap_term(uint16_t keycode, keyrecord_t *record) {
    uint16_t term = get_flow_tap_term(keycode, record, flow_tap_prev_keycode);
    return !flow_tap_expired && TIMER_DIFF_16(record->event.time, flow_tap_prev_time) <= term;
}

// By default, enable Flow Tap for the keys in the main alphas area and Space.
// This should work reasonably even if the layout is remapped on the host to an
// alt layout or international layout (e.g. Dvorak or AZERTY), where these same
// key positions are mostly used for typing letters.
__attribute__((weak)) bool is_flow_tap_key(uint16_t keycode) {
    if ((get_mods() & (MOD_MASK_CG | MOD_BIT_LALT)) != 0) {
        return false; // Disable Flow Tap on hotkeys.
    }
    switch (get_tap_keycode(keycode)) {
        case KC_SPC:
        case KC_A ... KC_Z:
        case KC_DOT:
        case KC_COMM:
        case KC_SCLN:
        case KC_SLSH:
            return true;
    }
    return false;
}

__attribute__((weak)) uint16_t get_flow_tap_term(uint16_t keycode, keyrecord_t *record, uint16_t prev_keycode) {
    if (is_flow_tap_key(keycode) && is_flow_tap_key(prev_keycode)) {
        return FLOW_TAP_TERM;
    }
    return 0;
}
#    endif // FLOW_TAP_TERM

/** \brief Logs tapping key if ACTION_DEBUG is enabled. */
static void debug_tapping_key(void) {
    ac_dprintf("TAPPING_KEY=");
    debug_record(tapping_key);
    ac_dprintf("\n");
}

/** \brief Logs waiting buffer if ACTION_DEBUG is enabled. */
static void debug_waiting_buffer(void) {
    ac_dprintf("{");
    for (uint8_t i = waiting_buffer_tail; i != waiting_buffer_head; i = (i + 1) % WAITING_BUFFER_SIZE) {
        ac_dprintf(" [%u]=", i);
        debug_record(waiting_buffer[i]);
    }
    ac_dprintf("}\n");
}

#endif
