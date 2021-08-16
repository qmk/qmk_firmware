#pragma once

#include "quantum.h"

#ifndef ADAPTIVE_KEY_TERM
#    define ADAPTIVE_KEY_TERM 200
#endif


typedef struct {
    // Keycode that starts this adaptive sequence
    uint16_t prefix_keycode;

    // Keycode on the keymap that will trigger adaptive behavior. This is also the keycode that is sent if adaptive behavior doesn't activate.
    uint16_t trigger_keycode;

    // Keycode to be fired when adaptive behavior is activated
    uint16_t replace_keycode;

    // Local timing for this adaptive key
    uint16_t timer;

    // Is the prefix key physically pressed down?
    bool is_prefix_pressed;

    // Is the trigger key physically pressed down? (This could mean either the trigger or the replacement keycode is active.)
    bool is_trigger_pressed;

    // Is the adaptive key currently listening for the trigger? This is true immediately after the prefix has been pressed.
    bool is_listening_for_trigger;

    // Is this adaptive key currently active? If so, releasing the trigger key should be handled by adaptive code
    bool is_behavior_active;
} qk_adaptive_key_state_t;


typedef bool (*qk_adaptive_key_keyevent_predicate_fn_t)(qk_adaptive_key_state_t *state, uint16_t keycode, keyrecord_t *record);
typedef void (*qk_adaptive_key_keyevent_fn_t)(qk_adaptive_key_state_t *state, keyrecord_t *record);


typedef struct {
    struct {
        qk_adaptive_key_keyevent_predicate_fn_t is_prefix_key;
        qk_adaptive_key_keyevent_predicate_fn_t is_trigger_key;
        qk_adaptive_key_keyevent_fn_t on_adaptive_event;
    } fn;
    qk_adaptive_key_state_t state;
} qk_adaptive_key_t;



bool qk_adaptive_key_is_prefix_key(qk_adaptive_key_state_t *state, uint16_t keycode, keyrecord_t *record);
bool qk_adaptive_key_is_trigger_key(qk_adaptive_key_state_t *state, uint16_t keycode, keyrecord_t *record);
void qk_adaptive_key_on_adaptive_event(qk_adaptive_key_state_t *state, keyrecord_t *record);

bool process_adaptive_keys(uint16_t keycode, keyrecord_t *record);

void enable_adaptive_keys(void);
void disable_adaptive_keys(void);
void toggle_adaptive_keys(void);

extern qk_adaptive_key_t adaptive_keys[];
extern uint16_t ADAPTIVE_KEY_LEN;

#define ADAPTIVE_KEY(pfx, trg, rep) { \
    .fn = {qk_adaptive_key_is_prefix_key, qk_adaptive_key_is_trigger_key, qk_adaptive_key_on_adaptive_event}, \
    .state = { .prefix_keycode = pfx, .trigger_keycode = trg, .replace_keycode = rep } \
}

#define ADAPTIVE_KEY_PREFIX_FN(pfx_fn, trg, rep) { \
    .fn = {pfx_fn, qk_adaptive_key_is_trigger_key, qk_adaptive_key_on_adaptive_event}, \
    .state = { .trigger_keycode = trg, .replace_keycode = rep } \
}

#define ADAPTIVE_KEY_TRIGGER_FN(pfx, trg_fn, rep) { \
    .fn = {qk_adaptive_key_is_prefix_key, qk_adaptive_key_is_trigger_key, qk_adaptive_key_on_adaptive_event}, \
    .state = { .prefix_keycode = pfx, .replace_keycode = rep } \
}

#define ADAPTIVE_KEY_FN(pfx_fun, trg_fun, rep_down_fun, rep_up_fun) { .fn = {pfx_fun, trg_fun, rep_fun} }
