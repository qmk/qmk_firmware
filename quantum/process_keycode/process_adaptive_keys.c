#include "process_adaptive_keys.h"
#include "print.h"

static bool                  b_adaptive_key_enable = true;

void enable_adaptive_keys(void) { b_adaptive_key_enable = true; }

void disable_adaptive_keys(void) { b_adaptive_key_enable = false; }

void toggle_adaptive_keys(void) {
    if (b_adaptive_key_enable) {
        disable_adaptive_keys();
    } else {
        enable_adaptive_keys();
    }
}


static inline bool _process_adaptive_key_predicate(qk_adaptive_key_state_t *state, uint16_t keycode, keyrecord_t *record, qk_adaptive_key_keyevent_predicate_fn_t pred) {
    if (pred) {
        return pred(state, keycode, record);
    }

    return false;
}

static inline void _process_adaptive_key_fn(qk_adaptive_key_state_t *state, keyrecord_t *record, qk_adaptive_key_keyevent_fn_t fn) {
    if (fn) {
        fn(state, record);
    }
}


bool process_single_adaptive_key(qk_adaptive_key_t *current, uint16_t keycode, keyrecord_t *record) {
    const bool key_down = record->event.pressed;
    qk_adaptive_key_state_t *state = &current->state;

    #define IS_LISTENING_FOR_PREFIX (!state->is_trigger_pressed && !state->is_listening_for_trigger && !state->is_behavior_active)

#ifdef ADAPTIVE_KEY_DEBUG_ENABLE
    uprintf("\nprocess_single_adaptive_key :: behavior active: %b, listening for trigger: %b, prefix pressed: %b, trigger pressed: %b\n", state->is_behavior_active, state->is_listening_for_trigger, state->is_prefix_pressed, state->is_trigger_pressed);
#endif

    if (_process_adaptive_key_predicate(state, keycode, record, current->fn.is_prefix_key)) {
        state->is_prefix_pressed = key_down;

#ifdef ADAPTIVE_KEY_DEBUG_ENABLE
        uprintf("* is_prefix_pressed changed to %b\n", state->is_prefix_pressed);
#endif

        if (key_down && IS_LISTENING_FOR_PREFIX) {
#ifdef ADAPTIVE_KEY_DEBUG_ENABLE
            print("* Start listening for trigger\n");
#endif

            state->is_listening_for_trigger = true;
            state->timer = timer_read();
        }
        return true;
    }

    if (_process_adaptive_key_predicate(state, keycode, record, current->fn.is_trigger_key)) {
        state->is_trigger_pressed = key_down;

#ifdef ADAPTIVE_KEY_DEBUG_ENABLE
        uprintf("* is_trigger_pressed changed to %b\n", state->is_trigger_pressed);
#endif

        if (key_down) {
            state->is_listening_for_trigger = false;

            if (timer_elapsed(state->timer) > ADAPTIVE_KEY_TERM) {

#ifdef ADAPTIVE_KEY_DEBUG_ENABLE
                uprintf("* Exceeded ADAPTIVE_KEY_TERM; not using adaptive behavior (tmr: %u, ADAPTIVE_KEY_TERM: %u)\n", tmr, ADAPTIVE_KEY_TERM);
#endif

                state->is_behavior_active = false;
                return true;
            }
            else {
#ifdef ADAPTIVE_KEY_DEBUG_ENABLE
                uprintf("* Starting adaptive behavior\n");
#endif
                state->is_behavior_active = true;
                _process_adaptive_key_fn(state, record, current->fn.on_adaptive_event);
                return false;
            }
        }
        else {
            if (!state->is_behavior_active) {
                return true;
            }
            else {
#ifdef ADAPTIVE_KEY_DEBUG_ENABLE
                print("* Releasing adaptive behavior\n");
#endif
                _process_adaptive_key_fn(state, record, current->fn.on_adaptive_event);
                state->is_behavior_active = false;
                return false;
            }
        }
    }

    return true;
}

bool process_adaptive_keys(uint16_t keycode, keyrecord_t *record) {
    // @TODO keycodes for enable / disable?

    if (!b_adaptive_key_enable) {
        return true;
    }

    for (uint16_t idx = 0; idx < ADAPTIVE_KEY_LEN; idx++) {
        // Handle adaptive keys in sequence. Any adaptive key can return false
        // (which is the QMK convention for "key event has been handled") and
        // the function will return early. If no adaptive key handles the
        // key event, yield processing back to the rest of QMK.
        qk_adaptive_key_t * current_key = &adaptive_keys[idx];
        if (!process_single_adaptive_key(current_key, keycode, record)) {
            return false;
        }
    }

    return true;
}


bool qk_adaptive_key_is_prefix_key(qk_adaptive_key_state_t *state, uint16_t keycode, keyrecord_t *record) {
    return keycode == state->prefix_keycode;
}

bool qk_adaptive_key_is_trigger_key(qk_adaptive_key_state_t *state, uint16_t keycode, keyrecord_t *record) {
    return keycode == state->trigger_keycode;
}

void qk_adaptive_key_on_adaptive_event(qk_adaptive_key_state_t *state, keyrecord_t *record) {
    if (record->event.pressed) {
        register_code16(state->replace_keycode);
    }
    else {
        unregister_code16(state->replace_keycode);
    }
}
