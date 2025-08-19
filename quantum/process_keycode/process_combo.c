/* Copyright 2016 Jack Humbert
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "process_combo.h"
#include <stddef.h>
#include "process_auto_shift.h"
#include "caps_word.h"
#include "timer.h"
#include "wait.h"
#include "keyboard.h"
#include "keymap_common.h"
#include "action_layer.h"
#include "action_tapping.h"
#include "action_util.h"
#include "keymap_introspection.h"

/* Enabled at matrix initialization, when linked lists are initialized */
static bool b_combo_enable = false;

/* Combo guarantees:
 * A combo will trigger if and only if
 *  - all of its keys are pressed within its combo term, and
 *  - none of the following occurs
 *      - One of the combo's keys was released before the final key was
 *        pressed
 *      - Two events (press and/or release) occur for any one keycode
 *        (whether or not it belongs to the combo) between the first and
 *        last triggering key presses
 *      - The combo has the "contiguous" requirement, and an unrelated key
 *        was pressed between the first and last triggering key presses
 *      - The combo has the "tap" requirement, but no triggering key is
 *        released within the hold term
 *      - The combo has the "hold" requirement, but a triggering key is
 *        released within the hold term
 *      - An overlapping combo with higher priority triggers instead
 *      - The key buffer overflows between the first and last key presses of
 *        the combo
 *
 * Combos, and key presses/releases not consumed by combos, will always be
 * released in their event order. The event time of a combo is that of its
 * FIRST trigger key press (so that the relevant keys are still in the
 * buffer for combos requiring detailed event processing)
 */

/* Combo statuses:
 * Inactive: no triggering key presses are available for legal assignment to
 * this combo
 *  - moves to partial status on the next triggering key press
 *
 * Partial: some, but not all, triggering key presses are available for
 * legal assignment to this combo
 *  - moves to inactive status if any triggering key is released, if any
 *    triggering key press expires, or if any non-triggering key is pressed
 *    and the combo is not contiguous
 *  - moves to complete status if all triggering keys are pressed
 *
 * Complete: all triggering keys have been pressed, but either the combo
 * term has not yet elapsed, or a tap is required has not yet occurred, or a
 * hold is required but the hold term has not yet elapsed
 *  - moves to ripe status if combo/hold term elapses or tap occurs,
 *    according to combo requirements
 *  - moves to inactive status if tap occurs for "must hold" combos, or
 *    combo term elapses with no tap for "must tap" combos
 *
 * Ripe: all triggering keys have been pressed, the combo term or hold term
 * has elapsed if required, and a tap has occurred if required
 *  - moves to ready status if this is the highest priority combo among all
 *    overlapping ripe combos, and if there is no higher-priority complete
 *    (but unripe) combo whose keys form a superset
 *  - moves to inactive status if a higher priority overlapping combo is
 *    ripened
 *
 * Ready: the combo is ready to be activated at the appropriate point in the
 * key sequence. Trigger keys are committed to this combo
 *  - moves to active status when the first triggering key press is the
 *    oldest key press in the buffer
 *
 * Active: the combo's event has already been processed, and some its keys
 * have not yet been released
 *  - moves to inactive status when the last of its keys is released
 *
 * Combo status is not recorded directly in the combo_t structure. Instead,
 * all combos of each status are organized into linked lists. There are
 * separate linked lists for inactive, active, and ripe combos. In addition,
 * each queued key record in the key buffer gives the index of any ready
 * combo that will consume that key. Alternatively, if the key record has
 * not (yet) been assigned to a ready combo, then the record has a linked
 * list of all the (partial and complete, but unripe) combos for which that
 * record is the oldest relevant press event.
 *
 * For combos that are partial or complete, the low bits of the combo state
 * give the number of remaining triggering key presses until the combo
 * activates.
 *
 * We use linked lists to organize combos by state, instead of recording
 * state directly in the combo_t structure, because we generally want to do
 * something with all combos of a particular state, rather than determine
 * what the state is of a particular combo. In particular, in order
 * handle expiration and ripening of combos, it is convenient to already
 * have each combo organized according to its oldest key press, rather than
 * having to iterate over all combo/key pairs. It is also convenient to be
 * able to sort ripe combos by priority.
 *
 * For the small number of active combos, more detailed state recording the
 * identity of each still-pressed key is required; this is stored in a
 * separate buffer.
 */

#define COMBO_NULL_INDEX (((combo_state_t)-1) >> COMBO_STATE_BITS)
#define COMBO_NULL_STATE ((COMBO_NULL_INDEX << COMBO_STATE_BITS))

/* Used by combo queue iterators */
#define GET_NEXT_COMBO_DIRECT(state_ptr) ((*state_ptr) >> COMBO_STATE_BITS)
#define SET_NEXT_COMBO_DIRECT(state_ptr, index) *state_ptr = ((index << COMBO_STATE_BITS) | ((*state_ptr) & ((1 << COMBO_STATE_BITS) - 1)))

/* Used when we have a combo_t or keyrecord_t */
#define GET_STATE(key_or_combo) (key_or_combo->state & ((1 << COMBO_STATE_BITS) - 1))
#define SET_STATE(key_or_combo, value) key_or_combo->state = ((key_or_combo->state & ~((1 << COMBO_STATE_BITS) - 1)) | value)
#define GET_NEXT_COMBO(key_or_combo) (key_or_combo->state >> COMBO_STATE_BITS)
#define SET_NEXT_COMBO(key_or_combo, index) key_or_combo->state = ((index << COMBO_STATE_BITS) | GET_STATE(key_or_combo))
/* DANGER: no guard against underflow on the state bits */
#define DECREMENT_STATE(key_or_combo) key_or_combo->state--;

static combo_state_t inactive_head;
static combo_state_t ripe_head;
static combo_state_t active_head;

/* Detailed state of active combos, i.e., which keys are still unpressed, is
 * recorded here as a bit array for each active combo.
 */
typedef struct {
    combo_state_t        combo_index;
    combo_active_state_t state;
} active_combo_t;

static active_combo_t active_buffer[COMBO_BUFFER_LENGTH];
static uint8_t        active_combo_count = 0;

/* Queued key record state is given by a combo_state_t. Like the
 * combo_state_t that holds combo_t state, its high bits give a combo index,
 * which can be used for a linked list of combos. Its low bits (the "state"
 * bits) encode the following possible statuses:
 *      COMBO_KEY_BASE - any key release. Also, presses that might help
 *          activate a combo, but require additional presses or ripening
 *          conditions. If this is the oldest key press in the buffer, and
 *          the high bits encode COMBO_NULL_INDEX, then the key press is not
 *          used by any combo and can be emitted as an ordinary press
 *      COMBO_KEY_RIPE - presses that will be used to activate a combo, but
 *          for which the specific combo has not yet been determined (e.g.,
 *          because we are waiting for an unripe high priority combo)
 *      COMBO_KEY_CONSUMED - presses that are being used to activate a
 *          combo, but will not trigger its event. The high bits indicate
 *          the combo being activated.
 *      COMBO_KEY_TRIGGER - the key press that actually triggers a combo
 *          event. The high bits indicate the combo being activated.
 *
 * Keys with status COMBO_KEY_CONSUMED or COMBO_KEY_TRIGGER can safely be
 * used in the appropriate manner when they reach the front of the key
 * buffer, as can keys with status COMBO_KEY_BASE whose high state bits
 * encode COMBO_NULL_INDEX.
 */
enum queued_record_state {
    COMBO_KEY_BASE,
    COMBO_KEY_RIPE,
    COMBO_KEY_CONSUMED,
    COMBO_KEY_TRIGGER,
};

typedef struct {
    keyrecord_t   record;
    combo_state_t state;
} queued_record_t;

static queued_record_t key_buffer[COMBO_KEY_BUFFER_LENGTH];
static uint8_t         key_buffer_head = 0;
static uint8_t         key_buffer_size = 0;
static uint16_t        next_expiration = 0;

#define GET_QUEUED_RECORD(i) &key_buffer[(key_buffer_head + i) % COMBO_KEY_BUFFER_LENGTH]

/* Returns true if this key is ready to be dumped from the buffer */
static inline bool is_key_resolved(queued_record_t *qrecord) { return ((qrecord->state == COMBO_NULL_STATE) || GET_STATE(qrecord) >= COMBO_KEY_CONSUMED); }

__attribute__((weak)) void process_combo_event(uint16_t combo_index, bool pressed) {}

#ifndef COMBO_ONLY_FROM_LAYER
__attribute__((weak)) uint8_t combo_ref_from_layer(uint8_t layer) {
    return layer;
}
#endif

#ifdef COMBO_MUST_HOLD_PER_COMBO
__attribute__((weak)) bool get_combo_must_hold(uint16_t index, combo_t *combo) { return false; }
#endif

#ifdef COMBO_MUST_TAP_PER_COMBO
__attribute__((weak)) bool get_combo_must_tap(uint16_t index, combo_t *combo) { return false; }
#endif

#ifdef COMBO_TERM_PER_COMBO
__attribute__((weak)) uint16_t get_combo_term(uint16_t index, combo_t *combo) { return COMBO_TERM; }
#endif

#ifdef COMBO_MUST_PRESS_IN_ORDER_PER_COMBO
__attribute__((weak)) bool get_combo_must_press_in_order(uint16_t combo_index, combo_t *combo) {
    return true;
}
#endif

#ifdef COMBO_SHOULD_TRIGGER
__attribute__((weak)) bool combo_should_trigger(uint16_t combo_index, combo_t *combo, uint16_t keycode, keyrecord_t *record) {
    return true;
}
#endif

#ifdef COMBO_DETAILED_EVENTS_PER_COMBO
__attribute__((weak)) bool get_combo_needs_details(uint16_t index, combo_t *combo) { return false; }
__attribute__((weak)) void process_combo_detailed_press(uint16_t index, combo_t *combo, keyrecord_t *triggers) {}
__attribute__((weak)) bool process_combo_detailed_release(uint16_t index, combo_t *combo, uint8_t key_index, uint16_t keycode, keyevent_t *event) { return false; }
static keyrecord_t         triggers[MAX_COMBO_LENGTH];
#endif

#ifdef COMBO_PROCESS_KEY_RELEASE
__attribute__((weak)) bool process_combo_key_release(uint16_t combo_index, combo_t *combo, uint8_t key_index, uint16_t keycode) { return false; }
#endif

#ifdef COMBO_PROCESS_KEY_REPRESS
__attribute__((weak)) bool process_combo_key_repress(uint16_t combo_index, combo_t *combo, uint8_t key_index, uint16_t keycode) {
    return false;
}
#endif

static inline bool _get_combo_must_hold(uint16_t combo_index, combo_t *combo) {
#ifdef COMBO_NO_TIMER
    return false;
#elif defined(COMBO_MUST_HOLD_PER_COMBO)
    return get_combo_must_hold(combo_index, combo);
#elif defined(COMBO_MUST_HOLD_MODS)
    return (KEYCODE_IS_MOD(combo->keycode) || (combo->keycode >= QK_MOMENTARY && combo->keycode <= QK_MOMENTARY_MAX));
#endif
    return false;
}

static inline uint16_t _get_combo_term(uint16_t combo_index, combo_t *combo) {
#if defined(COMBO_TERM_PER_COMBO)
    return get_combo_term(combo_index, combo);
#endif

    return COMBO_TERM;
}

static inline uint16_t _get_hold_term(uint16_t combo_index, combo_t *combo) {
    if (_get_combo_must_hold(combo_index, combo)
#ifdef COMBO_MUST_TAP_PER_COMBO
        || get_combo_must_tap(combo_index, combo)
#endif
    ) {
        return COMBO_HOLD_TERM;
    }
    return _get_combo_term(combo_index, combo);
}

bool _combo_has_key(combo_t *combo, uint16_t keycode) {
    const uint16_t *keys = combo->keys;
    for (uint8_t i = 0;; i++) {
        uint16_t key = pgm_read_word(&keys[i]);
        if (keycode == key) {
            return true;
        } else if (COMBO_END == key) {
            return false;
        }
    }
}

uint8_t _get_combo_keycode_index(combo_t *combo, uint16_t keycode) {
    const uint16_t *keys = combo->keys;
    for (uint8_t i = 0;; i++) {
        uint16_t key = pgm_read_word(&keys[i]);
        if (keycode == key) {
            return i;
        } else if (COMBO_END == key) {
            return (uint8_t)-1;
        }
    }
}

uint8_t _get_combo_length(combo_t *combo) {
    const uint16_t *keys = combo->keys;
    for (uint8_t i = 0;; i++) {
        uint16_t key = pgm_read_word(&keys[i]);
        if (COMBO_END == key) {
            return i;
        }
    }
}

bool does_combo_overlap(combo_t *combo1, combo_t *combo2) {
    const uint16_t *keys = combo1->keys;
    for (uint8_t i = 0;; i++) {
        uint16_t key = pgm_read_word(&keys[i]);
        if (COMBO_END == key) {
            break;
        }
        if (_combo_has_key(combo2, key)) {
            return true;
        }
    }
    return false;
}

/* Return true if combo1 is preferred to combo2 if they could both activate.
 * Default behavior: prefer longer combos, and break ties by preferring combos with higher indices */
__attribute__((weak)) bool is_combo_preferred(combo_state_t combo_index1, combo_state_t combo_index2, uint8_t combo_length1) {
    uint8_t combo_length2 = _get_combo_length(combo_get(combo_index2));
    if (combo_length1 > combo_length2) {
        return true;
    }
    return combo_index1 > combo_index2;
}

__attribute__((weak)) bool is_combo_contiguous(uint16_t index, combo_t *combo, uint16_t keycode, keyrecord_t *record, uint8_t n_unpressed_keys) {
    return true;
}

/* Default behavior (if none of COMBO_MUST_PRESS_IN_ORDER, COMBO_MUST_PRESS_IN_ORDER_PER_COMBO, or COMBO_SHOULD_TRIGGER are defined)
 * is to be interrupted by any key not contained in a combo, and otherwise to not be interrupted (require contiguous presses). */
__attribute__((weak)) bool is_combo_interrupted(uint16_t index, combo_t *combo, uint16_t keycode, keyrecord_t *record, uint8_t n_unpressed_keys, bool combo_has_key) {
    if (combo_has_key) {
#ifdef COMBO_MUST_PRESS_IN_ORDER_PER_COMBO
        if (get_combo_must_press_in_order(index, combo)) {
#elif defined(COMBO_MUST_PRESS_IN_ORDER)
        if (true) {
#else
        if (false) {
#endif
            /* If the combo must be pressed in order, it is interrupted if this key is not the next key in sequence */
            uint8_t combo_length = _get_combo_length(combo);
            uint16_t expected_key = pgm_read_word(&(combo->keys)[combo_length - n_unpressed_keys]);
            if (expected_key != keycode) {
                return true;
            }
        }

#ifdef COMBO_SHOULD_TRIGGER
        return !combo_should_trigger(index, combo, keycode, record);
#else
        return false;
#endif
    }
    return is_combo_contiguous(index, combo, keycode, record, n_unpressed_keys);
}

/*************************
 * COMBO QUEUE ITERATION *
 *************************/

typedef struct {
    combo_t       *combo;
    combo_state_t  combo_index;
    combo_state_t *prev_combo;
    bool           removed;
} combo_iterator_t;

/* Have we reached the end of the iteration; usually used only through convenience macro below */
static inline bool combo_iter_is_complete(combo_iterator_t *iter) { return (iter->combo_index == COMBO_NULL_INDEX); }

/* Move to next iterator; usually used only through convenience macro below */
void combo_iter_next(combo_iterator_t *iter) {
    if (combo_iter_is_complete(iter)) {
        return;
    }
    if (!iter->removed) {
        iter->prev_combo = &iter->combo->state;
    } else {
        iter->removed = false;
    }
    iter->combo_index = GET_NEXT_COMBO_DIRECT(iter->prev_combo);
    if (iter->combo_index == COMBO_NULL_INDEX) {
        iter->combo = NULL;
    } else {
        iter->combo = combo_get(iter->combo_index);
    }
}

/* Intialize new iterator; usually used only through convenience macro below */
void combo_iter_init(combo_iterator_t *iter, combo_state_t *head) {
    iter->prev_combo  = head;
    iter->combo_index = 0;
    iter->removed     = true;
    combo_iter_next(iter);
}

#define ALL_COMBOS_IN_QUEUE(queue, iter) \
    combo_iter_init(iter, queue);        \
    !combo_iter_is_complete(iter);       \
    combo_iter_next(iter)
#define ALL_COMBOS_IN_KEY(qrecord, iter) ALL_COMBOS_IN_QUEUE(&qrecord->state, iter)

/* Remove from its queue the combo currently accessed by the iterator */
static inline void combo_iter_remove(combo_iterator_t *iter) {
    if (!iter->removed && !combo_iter_is_complete(iter)) {
        SET_NEXT_COMBO_DIRECT(iter->prev_combo, GET_NEXT_COMBO(iter->combo));
        iter->removed = true;
    }
}

/* Insert combo immediately before current entry in iterator */
static inline void combo_iter_insert(combo_iterator_t *iter, combo_state_t combo_index, combo_t *combo) {
    SET_NEXT_COMBO(combo, iter->combo_index);
    SET_NEXT_COMBO_DIRECT(iter->prev_combo, combo_index);
}

/* Insert combo at head of queue */
static inline void combo_queue_insert(combo_state_t *head, combo_state_t combo_index, combo_t *combo) {
    SET_NEXT_COMBO(combo, GET_NEXT_COMBO_DIRECT(head));
    SET_NEXT_COMBO_DIRECT(head, combo_index);
}

/****************************
 * ACTIVE BUFFER MANAGEMENT *
 ****************************/

bool release_from_active(keyrecord_t *record);

/* Search for active combo state with given combo index and return pointer */
combo_active_state_t *get_combo_active_state(combo_state_t combo_index) {
    for (uint8_t i = 0; i < COMBO_BUFFER_LENGTH; i++) {
        active_combo_t *buffer_entry = &active_buffer[i];
        if (buffer_entry->combo_index == combo_index) {
            return &buffer_entry->state;
        }
    }
    return NULL;
}

/* Free active state buffer space currently allocated to a particular combo */
void free_combo_active_state(combo_state_t combo_index) {
    for (uint8_t i = 0; i < COMBO_BUFFER_LENGTH; i++) {
        active_combo_t *buffer_entry = &active_buffer[i];
        if (buffer_entry->combo_index == combo_index) {
            buffer_entry->combo_index = COMBO_NULL_INDEX;
            active_combo_count--;
            return;
        }
    }
}

void process_active_buffer_overflow(void) {
    /* Get oldest active combo (tail of active queue) */
    combo_iterator_t iter;
    for (ALL_COMBOS_IN_QUEUE(&active_head, &iter)) {
        if (COMBO_NULL_INDEX == GET_NEXT_COMBO(iter.combo)) {
            break;
        }
    }
    uint16_t       combo_index = iter.combo_index;
    combo_t       *combo       = iter.combo;
    combo_active_state_t *combo_state = NULL;
    if (combo != NULL) {
        combo_state = get_combo_active_state(iter.combo_index);
    }
    if (combo_state == NULL) {
        /* Called overflow even though there aren't any active combos, or
           oldest active combo doesn't have active state...
           This should never happen. */
        combo_index = active_buffer[0].combo_index;
        if (combo_index == COMBO_NULL_INDEX) {
            return;
        }
        combo       = combo_get(combo_index);
        combo_state = &active_buffer[0].state;
    }

    /* Release the active combo, key by key */
    uint16_t keycode;
    for (uint8_t combo_key = 0; (keycode = pgm_read_word(&combo->keys[combo_key])) != COMBO_END; combo_key++) {
        if (*combo_state & (1 << combo_key)) {
            /* Key is still present in the combo; simulate its release */
            keyrecord_t fake_release = {
                .event =
                    {
                        .key     = MAKE_KEYPOS(0,0),
                        .time    = timer_read() | 1,
                        .type    = KEY_EVENT,
                        .pressed = false,
                    },
                .keycode = keycode,
            };
            release_from_active(&fake_release); /*free_combo_active_state called on final release */
        }
    }
}

/* Search for unused active combo state buffer space, allocate to specified
 * combo, and return pointer */
combo_active_state_t *init_combo_active_state(combo_state_t combo_index) {
    if (active_combo_count == COMBO_BUFFER_LENGTH) {
        process_active_buffer_overflow();
    }
    for (uint8_t i = 0; i < COMBO_BUFFER_LENGTH; i++) {
        active_combo_t *buffer_entry = &active_buffer[i];
        if (buffer_entry->combo_index == COMBO_NULL_INDEX) {
            buffer_entry->combo_index = combo_index;
            buffer_entry->state       = 0;
            active_combo_count++;
            return &buffer_entry->state;
        }
    }
    return NULL;
}

/********************************
 * RIPENING AND READYING COMBOS *
 ********************************/

/* Insert into ripe queue, maintaining sort in order of decreasing priority */
void ripen_combo(combo_state_t combo_index, combo_t *combo) {
    combo_iterator_t iter;
    uint8_t combo_length = _get_combo_length(combo);
    for (ALL_COMBOS_IN_QUEUE(&ripe_head, &iter)) {
        if (is_combo_preferred(combo_index, iter.combo_index, combo_length)) {
            break;
        }
    }
    combo_iter_insert(&iter, combo_index, combo);
}

/* Prepare to activate a ripened combo by transferring it to the ready queue
 * and committing its triggering key records
 *
 * Should only be called by resolve_conflicts() */
void ready_combo(combo_state_t combo_index, combo_t *combo) {
    bool triggered = false;
    SET_NEXT_COMBO(combo, COMBO_NULL_INDEX);
    for (uint8_t i = 0; i < key_buffer_size; i++) {
        queued_record_t *qrecord = GET_QUEUED_RECORD(i);
        if ((COMBO_KEY_RIPE == GET_STATE(qrecord)) && _combo_has_key(combo, qrecord->record.keycode)) {
            /* This function is only called by resolve_conflicts(), so the key queue should already
             * be empty */
            if (!triggered) {
                SET_STATE(qrecord, COMBO_KEY_TRIGGER);
                SET_NEXT_COMBO(qrecord, combo_index);
                triggered = true;
            } else {
                qrecord->state = COMBO_KEY_CONSUMED;
                SET_NEXT_COMBO(qrecord, combo_index);
            }
        }
    }
}

/* Ensure that there are no overlapping combos in the ripe queue by
 * inactivating lower-priority combos.
 *
 * For surviving ripe combos, mark every key including the combo as
 * COMBO_KEY_RIPE
 *
 * Also ensure that any remaining ripe combos have no overlap with combos in
 * the key queues, except in the case of higher-priority combos with a
 * superset of triggers */
void resolve_conflicts(void) {
    combo_iterator_t ripe_iter;
    for (ALL_COMBOS_IN_QUEUE(&ripe_head, &ripe_iter)) {
        bool             is_key_later = false;
        bool             blocked      = false;
        uint8_t          combo_length = _get_combo_length(ripe_iter.combo);
        combo_iterator_t conflict_iter;
        /* Overlapping ripe combos (after this one) are lower priority; inactivate them */
        for (ALL_COMBOS_IN_QUEUE(&ripe_iter.combo->state, &conflict_iter)) {
            if (does_combo_overlap(ripe_iter.combo, conflict_iter.combo)) {
                combo_iter_remove(&conflict_iter);
                combo_queue_insert(&inactive_head, conflict_iter.combo_index, conflict_iter.combo);
            }
        }
        /* Overlapping partial and unripe complete combos that have lower
         * priority or don't fully contain this combo are inactivated */
        for (uint8_t i = 0; i < key_buffer_size; i++) {
            queued_record_t *qrecord = GET_QUEUED_RECORD(i);
            bool combo_has_key = _combo_has_key(ripe_iter.combo, qrecord->record.keycode);
            if (combo_has_key) {
                SET_STATE(qrecord, COMBO_KEY_RIPE);
            } else if (is_key_resolved(qrecord)) {
                /* Skip resolved keys.
                 * This key might have temporarily appeared resolved until
                 * this call to resolve_conflicts(), if this combo was the
                 * only remaining combo for the key, so it's important to
                 * first check for presence of the key in the combo */
                continue;
            }
            for (ALL_COMBOS_IN_KEY(qrecord, &conflict_iter)) {
                bool has_overlap = does_combo_overlap(ripe_iter.combo, conflict_iter.combo);
                if (has_overlap) {
                    /* Overlapping combos:
                     *    - are inactivated by this combo if they have a later trigger or lower priority
                     *    - block this combo otherwise */
                    if (is_key_later || is_combo_preferred(ripe_iter.combo_index, conflict_iter.combo_index, combo_length)) {
                        combo_iter_remove(&conflict_iter);
                        combo_queue_insert(&inactive_head, conflict_iter.combo_index, conflict_iter.combo);
                    } else {
                        blocked = true;
                    }
                }
            }
            is_key_later |= combo_has_key;
        }
        if (!blocked) {
            combo_iter_remove(&ripe_iter);
            ready_combo(ripe_iter.combo_index, ripe_iter.combo);
        }
    }
}

/**********************************
 * COMBO AND HOLD TERM EXPIRATION *
 **********************************/

/* Process expiration of a queued key record until a particular limit time.
 * May cause completed combos to ripen, ready, or inactivate, or cause
 * partial combos to inactivate. All incomplete or unripe combos for which
 * this key record was the first press are held in the combo queue of this
 * queued key record, so the relevant expiration time is easy to compute.
 *
 * If until!=0, any combo whose hold or combo term expired before `until` is
 * processed. If tap!=0, then additionally, any combo containing the key
 * `tap` is processed. If until==0, all combos are processed.
 *
 * If tap==0, then hold requirements are satisfied and tap requirements are
 * unsatisfied. If tap!=0, the opposite holds only for combos including the
 * key `tap`. */
void expire_key(queued_record_t *qrecord, uint16_t until, uint16_t tap) {
    if (is_key_resolved(qrecord)) {
        return;
    }

    combo_iterator_t iter;
    for (ALL_COMBOS_IN_KEY(qrecord, &iter)) {
        bool combo_complete = (0 == GET_STATE(iter.combo));
        bool combo_expired  = true;
        bool combo_tapped   = false;
        if (tap && _combo_has_key(iter.combo, tap)) {
            combo_tapped = true;
        }
        if (!combo_tapped && until) {
            uint16_t term = combo_complete ? _get_hold_term(iter.combo_index, iter.combo) : _get_combo_term(iter.combo_index, iter.combo);
            if (!timer_expired(until, (qrecord->record.event.time + term))) {
                combo_expired = false;
            }
        }
        if (combo_expired) {
            combo_iter_remove(&iter);
            if (!combo_complete
#ifdef COMBO_MUST_TAP_PER_COMBO
                || (!combo_tapped && get_combo_must_tap(iter.combo_index, iter.combo))
#endif
#if defined(COMBO_MUST_HOLD_PER_COMBO) || defined(COMBO_MUST_HOLD_MODS)
                || (combo_tapped && _get_combo_must_hold(iter.combo_index, iter.combo))
#endif
            ) {
                combo_queue_insert(&inactive_head, iter.combo_index, iter.combo);
            } else {
                ripen_combo(iter.combo_index, iter.combo);
            }
        }
    }
    /* Resolving conflicts per key ensures that earlier triggered combos are preferred */
    resolve_conflicts();
}

/* Forces expiration (with specified keycode tap if tap!=0) of all combos
 * associated with oldest `force` records in the key buffer. Additionally,
 * if until != 0, handles expiration of all combos expiring before the limit
 * `until` (using the specified keycode tap if tap!=0). */
void process_expiration(uint16_t until, uint16_t tap, uint8_t force) {
    for (uint8_t i = 0; i < key_buffer_size; i++) {
        queued_record_t *qrecord = GET_QUEUED_RECORD(i);
        if (i < force) {
            expire_key(qrecord, 0, tap);
        } else if (until) {
            expire_key(qrecord, until, tap);
        } else {
            break;
        }
    }
}

/* Compute when the next expiration should be performed. Should only be
 * called after calling dump_safely() (since that calls resolve_conflicts(),
 * which affects the result of this computation)
 *
 * If there are unripe complete combos, the next expiration is the soonest
 * time when one will ripen. (The order of ripening is important for
 * consistent triggering, since combos can inactivate higher priority
 * completed combos when they ripen, as long as the higher priority combos
 * do not have a superset of the combo triggers.)
 *
 * If there are no unripe complete combos, the next expiration is determined
 * by the longest combo term among partial combos containing the oldest
 * (unresolved) key in the buffer, since this determines the soonest time
 * when we can safely dump a key. */
void set_next_expiration(void) {
    next_expiration             = 0;
    uint16_t partial_expiration = 0;
    bool     oldest             = true;
    for (uint8_t i = 0; i < key_buffer_size; i++) {
        queued_record_t *qrecord = GET_QUEUED_RECORD(i);
        if (is_key_resolved(qrecord)) {
            continue;
        }
        combo_iterator_t iter;
        for (ALL_COMBOS_IN_KEY(qrecord, &iter)) {
            if (0 == GET_STATE(iter.combo)) {
                uint16_t ripening = qrecord->record.event.time + _get_hold_term(iter.combo_index, iter.combo);
                if (!next_expiration || ripening < next_expiration) {
                    next_expiration = ripening;
                }
            } else if (oldest && !next_expiration) {
                uint16_t inactivation = qrecord->record.event.time + _get_combo_term(iter.combo_index, iter.combo);
                if (inactivation > partial_expiration) {
                    partial_expiration = inactivation;
                }
            }
        }
        oldest = false;
    }
    if (!next_expiration) {
        next_expiration = partial_expiration;
    }
}

/****************************
 * DUMPING KEYS FROM BUFFER *
 ****************************/

/* Release a key record for processing by later steps of QMK pipeline */
void dump_keyrecord(keyrecord_t *record) {
#ifndef NO_ACTION_TAPPING
    action_tapping_process(*record);
#else
    process_record(record);
#endif
}

/* Insert combo into active queue, process the combo's outcome, and
 * initialize detailed active state */
void activate_combo(queued_record_t *qrecord) {
    combo_state_t  combo_index = GET_NEXT_COMBO(qrecord);
    combo_t       *combo       = combo_get(combo_index);
    combo_active_state_t *combo_state = init_combo_active_state(combo_index);
    if (combo_state == NULL) {
        /* This should never happen! */
        return;
    }
    uint8_t combo_length = _get_combo_length(combo);
    *combo_state         = (1 << combo_length) - 1;
    combo_queue_insert(&active_head, combo_index, combo);

    if (!combo->keycode) {
#ifdef COMBO_DETAILED_EVENTS_PER_COMBO
        if (get_combo_needs_details(combo_index, combo)) {
            triggers[0]                  = qrecord->record;
            uint8_t       trigger_index  = 1;
            combo_state_t consumed_state = ((combo_index << COMBO_STATE_BITS) & COMBO_KEY_CONSUMED);
            for (uint8_t i = 0; i < key_buffer_size; i++) {
                queued_record_t *buffer_entry = GET_QUEUED_RECORD(i);
                if (qrecord->state == consumed_state) {
                    triggers[trigger_index] = buffer_entry->record;
                    trigger_index++;
                }
            }
            process_combo_detailed_press(combo_index, combo, triggers);
        } else
#endif
        {
            process_combo_event(combo_index, true);
        }
    } else {
        keyrecord_t record = {
            .event = {
                .key     = MAKE_KEYPOS(0, 0),
                .time    = qrecord->record.event.time,
                .type    = COMBO_EVENT,
                .pressed = true,
            },
            .keycode = combo->keycode,
        };
        dump_keyrecord(&record);
    }
}

/* Try releasing a key from any active combos in which it is present.
 * Returns true if it was in fact released from an active combo, false
 * otherwise. */
bool release_from_active(keyrecord_t *record) {
    bool             released = false;
    combo_iterator_t iter;
    for (ALL_COMBOS_IN_QUEUE(&active_head, &iter)) {
        uint8_t key_index = _get_combo_keycode_index(iter.combo, record->keycode);
        if (key_index != (uint8_t)-1) {
            combo_active_state_t *combo_state = get_combo_active_state(iter.combo_index);
            if (combo_state == NULL) {
                /* Shouldn't happen... */
                continue;
            }
            if (*combo_state & (1 << key_index)) {
                /* Key is still pressed for this combo */
                released = true;
                *combo_state &= ~(1 << key_index);

#ifdef COMBO_DETAILED_EVENTS_PER_COMBO
                if (get_combo_needs_details(iter.combo_index, iter.combo)) {
                    if (process_combo_detailed_release(iter.combo_index, iter.combo, key_index, record->keycode, &record->event)) {
                        *combo_state = 0;
                    }
                }
#endif
#ifdef COMBO_PROCESS_KEY_RELEASE
                if (process_combo_key_release(iter.combo_index, iter.combo, key_index, record->keycode)) {
                    *combo_state = 0;
                }
#endif
                if (*combo_state == 0) {
                    if (!iter.combo->keycode) {
                        process_combo_event(iter.combo_index, false);
                    } else {
                        keyrecord_t release_record = {
                            .event = MAKE_COMBOEVENT(false),
                            .keycode = iter.combo->keycode,
                        };
                        dump_keyrecord(&release_record);
                    }
                    free_combo_active_state(iter.combo_index);
                    combo_iter_remove(&iter);
                    combo_queue_insert(&inactive_head, iter.combo_index, iter.combo);
                }
            }
        }
    }
    return released;
}

/* Releases key records from the buffer and combos from their queues for as
 * long as we have enough information to fully resolve the next item in the
 * sequence */
void dump_safely(void) {
    resolve_conflicts();
    while (key_buffer_size > 0) {
        queued_record_t *qrecord = GET_QUEUED_RECORD(0);
        if (!is_key_resolved(qrecord)) {
            break;
        }
        /* We advance the buffer here, in case dump_safely() gets called
         * recursively as a side-effect of user code */
        key_buffer_head = (key_buffer_head + 1) % COMBO_KEY_BUFFER_LENGTH;
        key_buffer_size--;
        switch (GET_STATE(qrecord)) {
            case COMBO_KEY_CONSUMED:
                qrecord->record.event.type = TICK_EVENT;
                dump_keyrecord(&qrecord->record);
                break;
            case COMBO_KEY_TRIGGER:
                activate_combo(qrecord);
                break;
            default:
                if (!qrecord->record.event.pressed) {
                    if (release_from_active(&qrecord->record)) {
                        qrecord->record.event.type = TICK_EVENT;
                        dump_keyrecord(&qrecord->record);
                        break;
                    }
                }
                /* Remove our cached keycode so the proper code is used */
                qrecord->record.keycode = 0;
                dump_keyrecord(&qrecord->record);
        }
    }
}

/* Force oldest key in the buffer to be released, as though all combos
 * involving it had already been resolved */
void process_key_buffer_overflow(void) {
    process_expiration(0, 0, 1);
    dump_safely();
}

#ifdef COMBO_PROCESS_KEY_REPRESS
/* Check if a key press belongs to a currently active combo.
 * If so, we call `process_combo_key_repress` to handle the key press.
 * If the key press is consumed by a combo repress, we return true.
 * Otherwise, we return false.
 */
bool try_repress(queued_record_t *qrecord, uint16_t keycode) {
    combo_iterator_t iter;
    for (ALL_COMBOS_IN_QUEUE(&active_head, &iter)) {
        uint8_t key_index = _get_combo_keycode_index(iter.combo, keycode);
        if (key_index != (uint8_t)-1) {
            combo_active_state_t *combo_state = get_combo_active_state(iter.combo_index);
            if (combo_state == NULL) {
                /* Shouldn't happen... */
                continue;
            }
            if (!(*combo_state & (1 << key_index))) {
                if (process_combo_key_repress(iter.combo_index, iter.combo, key_index, keycode)) {
                    *combo_state |= (1 << key_index);
                    qrecord->state = COMBO_KEY_CONSUMED | (iter.combo_index << COMBO_STATE_BITS);
                    return true;
                }
            }
        }
    }
    return false;
}
#endif

/***************************
 * MAIN COMBO ENTRY POINTS *
 ***************************/

bool process_combo(uint16_t keycode, keyrecord_t *record) {
    if (keycode == QK_COMBO_ON && record->event.pressed) {
        combo_enable();
        return true;
    }

    if (keycode == QK_COMBO_OFF && record->event.pressed) {
        combo_disable();
        return true;
    }

    if (keycode == QK_COMBO_TOGGLE && record->event.pressed) {
        combo_toggle();
        return true;
    }

    if (!is_combo_enabled()) {
        return true;
    }

    if (IS_NOEVENT(record->event)) {
        return true;
    }

#ifdef COMBO_ONLY_FROM_LAYER
    /* Only check keycodes from one layer. */
    keycode = keymap_key_to_keycode(COMBO_ONLY_FROM_LAYER, record->event.key);
#else
    uint8_t  highest_layer = get_highest_layer(layer_state | default_layer_state);
    uint8_t  ref_layer     = combo_ref_from_layer(highest_layer);
    if (ref_layer != highest_layer) {
        keycode = keymap_key_to_keycode(ref_layer, record->event.key);
    }
#endif

    /* We first check the key buffer for duplicate keycodes. When we
     * encounter a new event for a keycode already in the buffer, everything
     * preceding the older event immediately resolves, allowing the older
     * keyrecord to be dumped.
     *
     * Regardless of whether we encounter a duplicate keycode, we first
     * expire everything until the event time of the new keyrecord, so that
     * we don't end up, e.g., completing partial combos that should have
     * already expired. If the new keyrecord is a key release, it is
     * processed during this expiration to appropriately ripen or inactivate
     * completed combos (depending on tap/hold requirements) and to
     * inactivate overlapping partial combos.
     *
     * After expiration, we dump anything that has resolved from the
     * keybuffer. */

    uint8_t  force = 0;
    uint16_t tap   = record->event.pressed ? 0 : keycode;
    for (uint8_t i = 0; i < key_buffer_size; i++) {
        queued_record_t *old_record = GET_QUEUED_RECORD(i);
        if (keycode == old_record->record.keycode) {
            force = i + 1;
            break;
        }
    }
    process_expiration(record->event.time, tap, force);
    dump_safely();

    if (key_buffer_size == COMBO_KEY_BUFFER_LENGTH) {
        process_key_buffer_overflow();
    }

    queued_record_t *qrecord = GET_QUEUED_RECORD(key_buffer_size);
    qrecord->record          = *record;
    qrecord->state           = COMBO_NULL_STATE;
    key_buffer_size++;

    if (record->event.pressed
        /* Key presses can:
         * - be consumed by an active combo repress if COMBO_PROCESS_KEY_REPRESS is defined, OR
         * - contribute to partial combos, possibly completing them;
         * - contribute to inactive combos, moving them to partial state (or
         *   completing them, if user has defined a combo of length 1);
         * - inactivate partial combos that are contiguous but lack this key
         */
#ifdef COMBO_PROCESS_KEY_REPRESS
        && !try_repress(qrecord, keycode)
#endif
    ) {
        /* Add key to inactive combos */
        combo_iterator_t iter;
        for (ALL_COMBOS_IN_QUEUE(&inactive_head, &iter)) {
            if (_combo_has_key(iter.combo, keycode)) {
                uint8_t combo_length = _get_combo_length(iter.combo);
                /* Check for required order, etc. */
                if (!is_combo_interrupted(iter.combo_index, iter.combo, keycode, record, combo_length, true)) {
                    /* Remove from inactive queue and add to this key's queue */
                    SET_STATE(iter.combo, (combo_length - 1));
                    combo_iter_remove(&iter);
                    combo_queue_insert(&qrecord->state, iter.combo_index, iter.combo);
                }
            }
        }

        /* Add key to partial combos of other keys */
        for (uint8_t i = 0; i < key_buffer_size - 1; i++) {
            queued_record_t *old_record = GET_QUEUED_RECORD(i);
            if (is_key_resolved(old_record)) {
                continue;
            }
            for (ALL_COMBOS_IN_KEY(old_record, &iter)) {
                bool combo_has_key = _combo_has_key(iter.combo, keycode);
                uint8_t keys_remaining = GET_STATE(iter.combo);
                /* If already complete, can't be interrupted */
                if (0 != keys_remaining) {
                    /* Check for required order, contiguity constraints, etc. */
                    if (is_combo_interrupted(iter.combo_index, iter.combo, keycode, record, keys_remaining, combo_has_key)) {
                        combo_iter_remove(&iter);
                        combo_queue_insert(&inactive_head, iter.combo_index, iter.combo);
                    } else if (combo_has_key) {
                        /* Add the key to the combo*/
                        DECREMENT_STATE(iter.combo);
                    }
                }
            }
        }
    } /* Key releases are handled by the process_expiration call above */

    /* Store the keycode so we can notice overlaps later */
    qrecord->record.keycode  = keycode;
    dump_safely();
    set_next_expiration();
    return false; /* Key events can only be released from buffer when safe */
}

void combo_task(void) {
    if (!is_combo_enabled() || !next_expiration) {
        return;
    }
    uint16_t time = timer_read();
    if (timer_expired(time, next_expiration)) {
        process_expiration(time, 0, key_buffer_size);
        dump_safely();
        set_next_expiration();
    }
}

/************************
 * COMBO FEATURE SET-UP *
 ************************/

/* Initializes combo state when keyboard matrix is initialized, and when
 * combo feature is re-enabled after having been disabled */
void reset_combos(void) {
    key_buffer_head = key_buffer_size = 0;
    ripe_head = active_head = COMBO_NULL_STATE;

    inactive_head  = 0;
    combo_t *combo = combo_get(0);
    for (combo_state_t i = 0; i < combo_count(); i++) {
        combo = combo_get(i);
        SET_NEXT_COMBO(combo, (i + 1));
    }
    SET_NEXT_COMBO(combo, COMBO_NULL_INDEX);

    active_combo_count = 0;
    for (uint8_t i = 0; i < COMBO_BUFFER_LENGTH - 1; i++) {
        active_buffer[i].combo_index = COMBO_NULL_INDEX;
        active_buffer[i].state       = 0;
    }
}

void combo_enable(void) {
    if ((!b_combo_enable) && combo_count() > 0) {
        reset_combos();
        b_combo_enable = true;
    }
}

void combo_disable(void) {
    b_combo_enable = false;
    process_expiration(0, 0, key_buffer_size);
    dump_safely();
}

void combo_toggle(void) {
    if (b_combo_enable) {
        combo_disable();
    } else {
        combo_enable();
    }
}

bool is_combo_enabled(void) { return b_combo_enable; }
