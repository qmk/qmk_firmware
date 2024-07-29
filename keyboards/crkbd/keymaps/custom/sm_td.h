/* Copyright 2024 Stanislav Markin (https://github.com/stasmarkin)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *
 * Version: 0.4.0
 * Date: 2024-03-07
 */
#pragma once

#include QMK_KEYBOARD_H
#include "deferred_exec.h"

#ifdef SMTD_DEBUG_ENABLED
#include "print.h"
#endif

#ifdef SMTD_GLOBAL_SIMULTANEOUS_PRESSES_DELAY_MS
#include "timer.h"
#endif

/* ************************************* *
 *         GLOBAL CONFIGURATION          *
 * ************************************* */

#ifndef SMTD_GLOBAL_SIMULTANEOUS_PRESSES_DELAY_MS
#define SMTD_GLOBAL_SIMULTANEOUS_PRESSES_DELAY_MS 0
#endif

#if SMTD_GLOBAL_SIMULTANEOUS_PRESSES_DELAY_MS > 0
#define SMTD_SIMULTANEOUS_PRESSES_DELAY wait_ms(SMTD_GLOBAL_SIMULTANEOUS_PRESSES_DELAY_MS);
#else
#define SMTD_SIMULTANEOUS_PRESSES_DELAY
#endif

#ifndef SMTD_GLOBAL_TAP_TERM
#define SMTD_GLOBAL_TAP_TERM TAPPING_TERM
#endif

#ifndef SMTD_GLOBAL_SEQUENCE_TERM
#define SMTD_GLOBAL_SEQUENCE_TERM TAPPING_TERM / 2
#endif

#ifndef SMTD_GLOBAL_FOLLOWING_TAP_TERM
#define SMTD_GLOBAL_FOLLOWING_TAP_TERM TAPPING_TERM
#endif

#ifndef SMTD_GLOBAL_RELEASE_TERM
#define SMTD_GLOBAL_RELEASE_TERM TAPPING_TERM / 4
#endif

#ifndef SMTD_GLOBAL_MODS_RECALL
#define SMTD_GLOBAL_MODS_RECALL true
#endif

#ifndef SMTD_GLOBAL_AGGREGATE_TAPS
#define SMTD_GLOBAL_AGGREGATE_TAPS false
#endif

/* ************************************* *
 *          DEBUG CONFIGURATION          *
 * ************************************* */

#ifdef SMTD_DEBUG_ENABLED
__attribute__((weak)) char* keycode_to_string_user(uint16_t keycode);

char* keycode_to_string(uint16_t keycode) {
    if (keycode_to_string_user) {
        char* result = keycode_to_string_user(keycode);
        if (result) {
            return result;
        }
    }

    static char buffer[16];
    snprintf(buffer, sizeof(buffer), "KC_%d", keycode);
    return buffer;
}
#endif

/* ************************************* *
 *       USER TIMEOUT DEFINITIONS        *
 * ************************************* */

typedef enum {
    SMTD_TIMEOUT_TAP,
    SMTD_TIMEOUT_SEQUENCE,
    SMTD_TIMEOUT_FOLLOWING_TAP,
    SMTD_TIMEOUT_RELEASE,
} smtd_timeout;

__attribute__((weak)) uint32_t get_smtd_timeout(uint16_t keycode, smtd_timeout timeout);

uint32_t get_smtd_timeout_default(smtd_timeout timeout) {
    switch (timeout) {
        case SMTD_TIMEOUT_TAP:
            return SMTD_GLOBAL_TAP_TERM;
        case SMTD_TIMEOUT_SEQUENCE:
            return SMTD_GLOBAL_SEQUENCE_TERM;
        case SMTD_TIMEOUT_FOLLOWING_TAP:
            return SMTD_GLOBAL_FOLLOWING_TAP_TERM;
        case SMTD_TIMEOUT_RELEASE:
            return SMTD_GLOBAL_RELEASE_TERM;
    }
    return 0;
}

uint32_t get_smtd_timeout_or_default(uint16_t keycode, smtd_timeout timeout) {
    if (get_smtd_timeout) {
        return get_smtd_timeout(keycode, timeout);
    }
    return get_smtd_timeout_default(timeout);
}

/* ************************************* *
 *    USER FEATURE FLAGS DEFINITIONS     *
 * ************************************* */

typedef enum {
    SMTD_FEATURE_MODS_RECALL,
    SMTD_FEATURE_AGGREGATE_TAPS,
} smtd_feature;

__attribute__((weak)) bool smtd_feature_enabled(uint16_t keycode, smtd_feature feature);

bool smtd_feature_enabled_default(smtd_feature feature) {
    switch (feature) {
        case SMTD_FEATURE_MODS_RECALL:
            return SMTD_GLOBAL_MODS_RECALL;
        case SMTD_FEATURE_AGGREGATE_TAPS:
            return SMTD_GLOBAL_AGGREGATE_TAPS;
    }
    return false;
}

bool smtd_feature_enabled_or_default(uint16_t keycode, smtd_feature feature) {
    if (smtd_feature_enabled) {
        return smtd_feature_enabled(keycode, feature);
    }
    return smtd_feature_enabled_default(feature);
}

/* ************************************* *
 *       USER ACTION DEFINITIONS         *
 * ************************************* */

typedef enum {
    SMTD_ACTION_TOUCH,
    SMTD_ACTION_TAP,
    SMTD_ACTION_HOLD,
    SMTD_ACTION_RELEASE,
} smtd_action;

#ifdef SMTD_DEBUG_ENABLED
char *smtd_action_to_string(smtd_action action) {
    switch (action) {
        case SMTD_ACTION_TOUCH:
            return "ACT_TOUCH";
        case SMTD_ACTION_TAP:
            return "ACT_TAP";
        case SMTD_ACTION_HOLD:
            return "ACT_HOLD";
        case SMTD_ACTION_RELEASE:
            return "ACT_RELEASE";
    }
    return "ACT_UNKNOWN";
}
#endif

void on_smtd_action(uint16_t keycode, smtd_action action, uint8_t sequence_len);

#ifdef SMTD_DEBUG_ENABLED
#define SMTD_ACTION(action, state) printf("%s by %s in %s\n", \
    smtd_action_to_string(action), keycode_to_string(state->macro_keycode), smtd_stage_to_string(state->stage)); \
    on_smtd_action(state->macro_keycode, action, state->sequence_len);
#else
#define SMTD_ACTION(action, state) on_smtd_action(state->macro_keycode, action, state->sequence_len);
#endif

/* ************************************* *
 *       USER STATES DEFINITIONS         *
 * ************************************* */

typedef enum {
    SMTD_STAGE_NONE,
    SMTD_STAGE_TOUCH,
    SMTD_STAGE_SEQUENCE,
    SMTD_STAGE_FOLLOWING_TOUCH,
    SMTD_STAGE_HOLD,
    SMTD_STAGE_RELEASE,
} smtd_stage;

#ifdef SMTD_DEBUG_ENABLED
char *smtd_stage_to_string(smtd_stage stage) {
    switch (stage) {
        case SMTD_STAGE_NONE:
            return "STAGE_NONE";
        case SMTD_STAGE_TOUCH:
            return "STAGE_TOUCH";
        case SMTD_STAGE_SEQUENCE:
            return "STAGE_SEQUENCE";
        case SMTD_STAGE_FOLLOWING_TOUCH:
            return "STAGE_FOL_TOUCH";
        case SMTD_STAGE_HOLD:
            return "STAGE_HOLD";
        case SMTD_STAGE_RELEASE:
            return "STAGE_RELEASE";
    }
    return "STAGE_UNKNOWN";
}
#endif

typedef struct {
    /** The keycode of the macro key */
    uint16_t macro_keycode;

    /** The mods before the touch action performed. Required for mod_recall feature */
    uint8_t modes_before_touch;

    /** Since touch can modify global mods, we need to save them separately to correctly restore a state before touch */
    uint8_t modes_with_touch;

    /** The length of the sequence of same key taps */
    uint8_t sequence_len;

    /** The position of key that was pressed after macro was pressed */
    keypos_t following_key;

    /** The keycode of the key that was pressed after macro was pressed */
    uint16_t following_keycode;

    /** The timeout of current stage */
    deferred_token timeout;

    /** The current stage of the state */
    smtd_stage stage;

    /** The flag that indicates that the state is frozen, so it won't handle any events */
    bool freeze;
} smtd_state;

#define EMPTY_STATE {                       \
        .macro_keycode = 0,                 \
        .modes_before_touch = 0,            \
        .modes_with_touch = 0,              \
        .sequence_len = 0,                  \
        .following_key = MAKE_KEYPOS(0, 0), \
        .following_keycode = 0,             \
        .timeout = INVALID_DEFERRED_TOKEN,  \
        .stage = SMTD_STAGE_NONE,           \
        .freeze = false                     \
}

/* ************************************* *
 *             LAYER UTILS               *
 * ************************************* */

#define RETURN_LAYER_NOT_SET 15

static uint8_t return_layer = RETURN_LAYER_NOT_SET;
static uint8_t return_layer_cnt = 0;

void avoid_unused_variable_on_compile(void* ptr) {
    // just touch them, so compiler won't throw "defined but not used" error
    // that variables are used in macros that user may not use
    if (return_layer == RETURN_LAYER_NOT_SET) return_layer = RETURN_LAYER_NOT_SET;
    if (return_layer_cnt == 0) return_layer_cnt = 0;
}

#define LAYER_PUSH(layer)                              \
    return_layer_cnt++;                                \
    if (return_layer == RETURN_LAYER_NOT_SET) {        \
        return_layer = get_highest_layer(layer_state); \
    }                                                  \
    layer_move(layer);

#define LAYER_RESTORE()                          \
    if (return_layer_cnt > 0) {                  \
        return_layer_cnt--;                      \
        if (return_layer_cnt == 0) {             \
            layer_move(return_layer);            \
            return_layer = RETURN_LAYER_NOT_SET; \
        }                                        \
    }

/* ************************************* *
 *      CORE LOGIC IMPLEMENTATION        *
 * ************************************* */

smtd_state smtd_active_states[10] = {EMPTY_STATE, EMPTY_STATE, EMPTY_STATE, EMPTY_STATE, EMPTY_STATE,
                                     EMPTY_STATE, EMPTY_STATE, EMPTY_STATE, EMPTY_STATE, EMPTY_STATE};
uint8_t smtd_active_states_size = 0;


#define DO_ACTION_TAP(state)                                                                 \
    uint8_t current_mods = get_mods();                                                       \
    if (                                                                                     \
            smtd_feature_enabled_or_default(state->macro_keycode, SMTD_FEATURE_MODS_RECALL)  \
            && state->modes_before_touch != current_mods                                     \
            ) {                                                                              \
        set_mods(state->modes_before_touch);                                                 \
        send_keyboard_report();                                                              \
                                                                                             \
        SMTD_SIMULTANEOUS_PRESSES_DELAY                                                      \
        SMTD_ACTION(SMTD_ACTION_TAP, state)                                                  \
        uint8_t mods_diff = get_mods() ^ state->modes_before_touch;                          \
                                                                                             \
        SMTD_SIMULTANEOUS_PRESSES_DELAY                                                      \
        set_mods(current_mods ^ mods_diff);                                                  \
        del_mods(state->modes_with_touch);                                                   \
        send_keyboard_report();                                                              \
                                                                                             \
        state->modes_before_touch = 0;                                                       \
        state->modes_with_touch = 0;                                                         \
    } else {                                                                                 \
        SMTD_ACTION(SMTD_ACTION_TAP, state)                                                  \
    }

void smtd_press_following_key(smtd_state *state, bool release) {
    state->freeze = true;
    keyevent_t event_press = MAKE_KEYEVENT(state->following_key.row, state->following_key.col, true);
    keyrecord_t record_press = {.event = event_press};
    #ifdef SMTD_DEBUG_ENABLED
    if (release) {
        printf("FOLLOWING_TAP(%s) by %s in %s\n", keycode_to_string(state->following_keycode),
               keycode_to_string(state->macro_keycode), smtd_stage_to_string(state->stage));
    } else {
        printf("FOLLOWING_PRESS(%s) by %s in %s\n", keycode_to_string(state->following_keycode),
               keycode_to_string(state->macro_keycode), smtd_stage_to_string(state->stage));
    }
    #endif
    process_record(&record_press);
    if (release) {
        keyevent_t event_release = MAKE_KEYEVENT(state->following_key.row, state->following_key.col, false);
        keyrecord_t record_release = {.event = event_release};
        SMTD_SIMULTANEOUS_PRESSES_DELAY
        process_record(&record_release);
    }
    state->freeze = false;
}

void smtd_next_stage(smtd_state *state, smtd_stage next_stage);

uint32_t timeout_reset_seq(uint32_t trigger_time, void *cb_arg) {
    smtd_state *state = (smtd_state *) cb_arg;
    state->sequence_len = 0;

    return 0;
}

uint32_t timeout_touch(uint32_t trigger_time, void *cb_arg) {
    smtd_state *state = (smtd_state *) cb_arg;
    smtd_next_stage(state, SMTD_STAGE_HOLD);
    return 0;
}

uint32_t timeout_sequence(uint32_t trigger_time, void *cb_arg) {
    smtd_state *state = (smtd_state *) cb_arg;

    if (smtd_feature_enabled_or_default(state->macro_keycode, SMTD_FEATURE_AGGREGATE_TAPS)) {
        DO_ACTION_TAP(state);
    }

    smtd_next_stage(state, SMTD_STAGE_NONE);
    return 0;
}

uint32_t timeout_following_touch(uint32_t trigger_time, void *cb_arg) {
    smtd_state *state = (smtd_state *) cb_arg;
    smtd_next_stage(state, SMTD_STAGE_HOLD);

    SMTD_SIMULTANEOUS_PRESSES_DELAY
    smtd_press_following_key(state, false);
    return 0;
}

uint32_t timeout_release(uint32_t trigger_time, void *cb_arg) {
    smtd_state *state = (smtd_state *) cb_arg;

    DO_ACTION_TAP(state);

    SMTD_SIMULTANEOUS_PRESSES_DELAY
    smtd_press_following_key(state, false);

    smtd_next_stage(state, SMTD_STAGE_NONE);
    return 0;
}

void smtd_next_stage(smtd_state *state, smtd_stage next_stage) {
    #ifdef SMTD_DEBUG_ENABLED
    printf("STAGE by %s, %s -> %s\n", keycode_to_string(state->macro_keycode),
           smtd_stage_to_string(state->stage),smtd_stage_to_string(next_stage));
    #endif

    deferred_token prev_token = state->timeout;
    state->timeout = INVALID_DEFERRED_TOKEN;
    state->stage = next_stage;

    switch (state->stage) {
        case SMTD_STAGE_NONE:
            for (uint8_t i = 0; i < smtd_active_states_size; i++) {
                if (&smtd_active_states[i] != state) continue;

                for (uint8_t j = i; j < smtd_active_states_size - 1; j++) {
                    smtd_active_states[j].macro_keycode = smtd_active_states[j + 1].macro_keycode;
                    smtd_active_states[j].modes_before_touch = smtd_active_states[j + 1].modes_before_touch;
                    smtd_active_states[j].modes_with_touch = smtd_active_states[j + 1].modes_with_touch;
                    smtd_active_states[j].sequence_len = smtd_active_states[j + 1].sequence_len;
                    smtd_active_states[j].following_key = smtd_active_states[j + 1].following_key;
                    smtd_active_states[j].following_keycode = smtd_active_states[j + 1].following_keycode;
                    smtd_active_states[j].timeout = smtd_active_states[j + 1].timeout;
                    smtd_active_states[j].stage = smtd_active_states[j + 1].stage;
                    smtd_active_states[j].freeze = smtd_active_states[j + 1].freeze;
                }

                smtd_active_states_size--;
                smtd_state *last_state = &smtd_active_states[smtd_active_states_size];
                last_state->macro_keycode = 0;
                last_state->modes_before_touch = 0;
                last_state->modes_with_touch = 0;
                last_state->sequence_len = 0;
                last_state->following_key = MAKE_KEYPOS(0, 0);
                last_state->following_keycode = 0;
                last_state->timeout = INVALID_DEFERRED_TOKEN;
                last_state->stage = SMTD_STAGE_NONE;
                last_state->freeze = false;

                break;
            }
            break;

        case SMTD_STAGE_TOUCH:
            state->modes_before_touch = get_mods();
            SMTD_ACTION(SMTD_ACTION_TOUCH, state)
            state->modes_with_touch = get_mods() & ~state->modes_before_touch;
            state->timeout = defer_exec(get_smtd_timeout_or_default(state->macro_keycode, SMTD_TIMEOUT_TAP),
                                        timeout_touch, state);
            break;

        case SMTD_STAGE_SEQUENCE:
            state->timeout = defer_exec(get_smtd_timeout_or_default(state->macro_keycode, SMTD_TIMEOUT_SEQUENCE),
                                        timeout_sequence, state);
            break;

        case SMTD_STAGE_HOLD:
            SMTD_ACTION(SMTD_ACTION_HOLD, state)
            break;

        case SMTD_STAGE_FOLLOWING_TOUCH:
            state->timeout = defer_exec(get_smtd_timeout_or_default(state->macro_keycode, SMTD_TIMEOUT_FOLLOWING_TAP),
                                        timeout_following_touch, state);
            break;

        case SMTD_STAGE_RELEASE:
            state->timeout = defer_exec(get_smtd_timeout_or_default(state->macro_keycode, SMTD_TIMEOUT_RELEASE),
                                        timeout_release, state);
            break;
    }

    // need to cancel after creating new timeout. There is a bug in QMK scheduling
    cancel_deferred_exec(prev_token);
}

bool process_smtd_state(uint16_t keycode, keyrecord_t *record, smtd_state *state) {
    if (state->freeze) {
        return true;
    }

    switch (state->stage) {
        case SMTD_STAGE_NONE:
            if (keycode == state->macro_keycode && record->event.pressed) {
                smtd_next_stage(state, SMTD_STAGE_TOUCH);
                return false;
            }
            return true;

        case SMTD_STAGE_TOUCH:
            if (keycode == state->macro_keycode && !record->event.pressed) {
                smtd_next_stage(state, SMTD_STAGE_SEQUENCE);

                if (!smtd_feature_enabled_or_default(state->macro_keycode, SMTD_FEATURE_AGGREGATE_TAPS)) {
                    DO_ACTION_TAP(state);
                }

                return false;
            }
            if (keycode != state->macro_keycode && record->event.pressed) {
                state->following_key = record->event.key;
                state->following_keycode = keycode;
                smtd_next_stage(state, SMTD_STAGE_FOLLOWING_TOUCH);
                return false;
            }
            return true;

        case SMTD_STAGE_SEQUENCE:
            if (keycode == state->macro_keycode && record->event.pressed) {
                state->sequence_len++;
                smtd_next_stage(state, SMTD_STAGE_TOUCH);
                return false;
            }
            if (record->event.pressed) {
                if (smtd_feature_enabled_or_default(state->macro_keycode, SMTD_FEATURE_AGGREGATE_TAPS)) {
                    DO_ACTION_TAP(state);
                }

                smtd_next_stage(state, SMTD_STAGE_NONE);

                return true;
            }
            return true;

        case SMTD_STAGE_FOLLOWING_TOUCH:
            // At this stage, we have already pressed the macro key and the following key
            // none of them is assumed to be held yet

            if (keycode == state->macro_keycode && !record->event.pressed) {
                // Macro key is released, moving to the next stage
                smtd_next_stage(state, SMTD_STAGE_RELEASE);
                return false;
            }

            if (
                    keycode != state->macro_keycode
                    && (state->following_key.row == record->event.key.row &&
                        state->following_key.col == record->event.key.col)
                    && !record->event.pressed
                    ) {
                // Following key is released. Now we definitely know that macro key is held
                // we need to execute hold the macro key and execute hold the following key
                // and then press move to next stage
                smtd_next_stage(state, SMTD_STAGE_HOLD);

                SMTD_SIMULTANEOUS_PRESSES_DELAY
                smtd_press_following_key(state, true);

                return false;
            }
            if (
                    keycode != state->macro_keycode
                    && !(state->following_key.row == record->event.key.row &&
                         state->following_key.col == record->event.key.col)
                    && record->event.pressed
                    ) {
                // so, now we have 3rd key pressed
                // we assume this to be hold macro key, hold following key and press the 3rd key

                // need to put first key state into HOLD stage
                smtd_next_stage(state, SMTD_STAGE_HOLD);

                // then press and hold (without releasing) the following key
                SMTD_SIMULTANEOUS_PRESSES_DELAY
                smtd_press_following_key(state, false);

                // then rerun the 3rd key press
                // since we have just started hold stage, we need to simulate the press of the 3rd key again
                // because by holding first two keys we might have changed a layer, so current keycode might be not actual
                // if we don't do this, we might continue processing the wrong key
                SMTD_SIMULTANEOUS_PRESSES_DELAY
                state->freeze = true;
                keyevent_t event_press = MAKE_KEYEVENT(record->event.key.row, record->event.key.col, true);
                keyrecord_t record_press = {.event = event_press};
                process_record(&record_press);
                state->freeze = false;

                // we have processed the 3rd key, so we intentionally return false to stop further processing
                return false;
            }
            return true;

        case SMTD_STAGE_HOLD:
            if (keycode == state->macro_keycode && !record->event.pressed) {
                SMTD_ACTION(SMTD_ACTION_RELEASE, state)

                smtd_next_stage(state, SMTD_STAGE_NONE);

                return false;
            }
            return true;

        case SMTD_STAGE_RELEASE:
            // At this stage we have just released the macro key and still holding the following key

            if (keycode == state->macro_keycode && record->event.pressed) {
                DO_ACTION_TAP(state);

                SMTD_SIMULTANEOUS_PRESSES_DELAY
                smtd_press_following_key(state, false);

                //todo need to go to NONE stage and from NONE jump to TOUCH stage
                SMTD_SIMULTANEOUS_PRESSES_DELAY
                smtd_next_stage(state, SMTD_STAGE_TOUCH);

                state->sequence_len = 0;

                return false;
            }
            if (
                    keycode != state->macro_keycode
                    && (state->following_key.row == record->event.key.row &&
                        state->following_key.col == record->event.key.col)
                    && !record->event.pressed
                    ) {
                // Following key is released. Now we definitely know that macro key is held
                // we need to execute hold the macro key and execute tap the following key
                // then close the state

                SMTD_ACTION(SMTD_ACTION_HOLD, state)

                SMTD_SIMULTANEOUS_PRESSES_DELAY
                smtd_press_following_key(state, true);

                SMTD_SIMULTANEOUS_PRESSES_DELAY
                SMTD_ACTION(SMTD_ACTION_RELEASE, state)

                smtd_next_stage(state, SMTD_STAGE_NONE);

                return false;
            }
            if (
                    keycode != state->macro_keycode
                    && (state->following_key.row != record->event.key.row ||
                        state->following_key.col != record->event.key.col)
                    && record->event.pressed
                    ) {
                // at this point we have already released the macro key and still holding the following key
                // and we get 3rd key pressed
                // we assume this to be tap macro key, press (w/o release) following key and press (w/o release) the 3rd key

                // so we need to tap the macro key first
                DO_ACTION_TAP(state)

                // then press and hold (without releasing) the following key
                SMTD_SIMULTANEOUS_PRESSES_DELAY
                smtd_press_following_key(state, false);

                // release current state, because the first key is already processed
                smtd_next_stage(state, SMTD_STAGE_NONE);

                // then rerun the 3rd key press
                // since we have just press following state, we need to simulate the press of the 3rd key again
                // because by pressing second key we might have changed a layer, so current keycode might be not actual
                // if we don't do this, we might continue processing the wrong key
                SMTD_SIMULTANEOUS_PRESSES_DELAY

                // we also don't need to freeze the state here, because we are already put in NONE stage
                keyevent_t event_press = MAKE_KEYEVENT(record->event.key.row, record->event.key.col, true);
                keyrecord_t record_press = {.event = event_press};
                process_record(&record_press);

                // we have processed the 3rd key, so we intentionally return false to stop further processing
                return false;
            }
            return true;
    }

    return true;
}

/* ************************************* *
 *      ENTRY POINT IMPLEMENTATION       *
 * ************************************* */

bool process_smtd(uint16_t keycode, keyrecord_t *record) {
    #ifdef SMTD_DEBUG_ENABLED
    printf("\n>> GOT KEY %s %s\n", keycode_to_string(keycode), record->event.pressed ? "PRESSED" : "RELEASED");
    #endif

    // check if any active state may process an event
    for (uint8_t i = 0; i < smtd_active_states_size; i++) {
        smtd_state *state = &smtd_active_states[i];
        if (!process_smtd_state(keycode, record, state)) {
            #ifdef SMTD_DEBUG_ENABLED
            printf("<< HANDLE KEY %s %s by %s\n", keycode_to_string(keycode),
                   record->event.pressed ? "PRESSED" : "RELEASED", keycode_to_string(state->macro_keycode));
            #endif
            return false;
        }
    }

    // may be start a new state? A key must be just pressed
    if (!record->event.pressed) {
        #ifdef SMTD_DEBUG_ENABLED
        printf("<< BYPASS KEY %s %s\n", keycode_to_string(keycode), record->event.pressed ? "PRESSED" : "RELEASED");
        #endif
        return true;
    }

    // check if the key is a macro key
    if (keycode <= SMTD_KEYCODES_BEGIN || SMTD_KEYCODES_END <= keycode) {
        #ifdef SMTD_DEBUG_ENABLED
        printf("<< BYPASS KEY %s %s\n", keycode_to_string(keycode), record->event.pressed ? "PRESSED" : "RELEASED");
        #endif
        return true;
    }

    // check if the key is already handled
    for (uint8_t i = 0; i < smtd_active_states_size; i++) {
        if (smtd_active_states[i].macro_keycode == keycode) {
            #ifdef SMTD_DEBUG_ENABLED
            printf("<< ALREADY HANDELED KEY %s %s\n", keycode_to_string(keycode), record->event.pressed ? "PRESSED" : "RELEASED");
            #endif
            return true;
        }
    }

    // create a new state and process the event
    smtd_state *state = &smtd_active_states[smtd_active_states_size];
    state->macro_keycode = keycode;
    smtd_active_states_size++;

    #ifdef SMTD_DEBUG_ENABLED
    printf("<< CREATE STATE %s %s\n", keycode_to_string(keycode), record->event.pressed ? "PRESSED" : "RELEASED");
    #endif
    return process_smtd_state(keycode, record, state);
}

/* ************************************* *
 *         CUSTOMIZATION MACROS          *
 * ************************************* */

#ifdef CAPS_WORD_ENABLE
#define SMTD_TAP_16(use_cl, key) tap_code16(use_cl && is_caps_word_on() ? LSFT(key) : key)
#define SMTD_REGISTER_16(use_cl, key) register_code16(use_cl && is_caps_word_on() ? LSFT(key) : key)
#define SMTD_UNREGISTER_16(use_cl, key) unregister_code16(use_cl && is_caps_word_on() ? LSFT(key) : key)
#else
#define SMTD_TAP_16(use_cl, key) tap_code16(key)
#define SMTD_REGISTER_16(use_cl, key) register_code16(key)
#define SMTD_UNREGISTER_16(use_cl, key) unregister_code16(key)
#endif

#define SMTD_GET_MACRO(_1, _2, _3, _4, _5, NAME, ...) NAME
#define SMTD_MT(...) SMTD_GET_MACRO(__VA_ARGS__, SMTD_MT5, SMTD_MT4, SMTD_MT3)(__VA_ARGS__)
#define SMTD_MTE(...) SMTD_GET_MACRO(__VA_ARGS__, SMTD_MTE5, SMTD_MTE4, SMTD_MTE3)(__VA_ARGS__)
#define SMTD_LT(...) SMTD_GET_MACRO(__VA_ARGS__, SMTD_LT5, SMTD_LT4, SMTD_LT3)(__VA_ARGS__)

#define SMTD_MT3(macro_key, tap_key, mod) SMTD_MT4(macro_key, tap_key, mod, 1000)
#define SMTD_MTE3(macro_key, tap_key, mod) SMTD_MTE4(macro_key, tap_key, mod, 1000)
#define SMTD_LT3(macro_key, tap_key, layer) SMTD_LT4(macro_key, tap_key, layer, 1000)

#define SMTD_MT4(macro_key, tap_key, mod, threshold) SMTD_MT5(macro_key, tap_key, mod, threshold, true)
#define SMTD_MTE4(macro_key, tap_key, mod, threshold) SMTD_MTE5(macro_key, tap_key, mod, threshold, true)
#define SMTD_LT4(macro_key, tap_key, layer, threshold) SMTD_LT5(macro_key, tap_key, layer, threshold, true)

#define SMTD_MT5(macro_key, tap_key, mod, threshold, use_cl)  \
    case macro_key: {                                         \
        switch (action) {                                     \
            case SMTD_ACTION_TOUCH:                           \
                break;                                        \
            case SMTD_ACTION_TAP:                             \
                SMTD_TAP_16(use_cl, tap_key);                 \
                break;                                        \
            case SMTD_ACTION_HOLD:                            \
                if (tap_count < threshold) {                  \
                    register_mods(MOD_BIT(mod));              \
                } else {                                      \
                    SMTD_REGISTER_16(use_cl, tap_key);        \
                }                                             \
                break;                                        \
            case SMTD_ACTION_RELEASE:                         \
                if (tap_count < threshold) {                  \
                    unregister_mods(MOD_BIT(mod));            \
                } else {                                      \
                    SMTD_UNREGISTER_16(use_cl, tap_key);      \
                    send_keyboard_report();                   \
                }                                             \
                break;                                        \
        }                                                     \
        break;                                                \
    }

#define SMTD_MTE5(macro_key, tap_key, mod, threshold, use_cl) \
    case macro_key: {                                         \
        switch (action) {                                     \
            case SMTD_ACTION_TOUCH:                           \
                register_mods(MOD_BIT(mod));                  \
                break;                                        \
            case SMTD_ACTION_TAP:                             \
                unregister_mods(MOD_BIT(mod));                \
                SMTD_TAP_16(use_cl, tap_key);                 \
                break;                                        \
            case SMTD_ACTION_HOLD:                            \
                if (!(tap_count < threshold)) {               \
                    unregister_mods(MOD_BIT(mod));            \
                    SMTD_REGISTER_16(use_cl, tap_key);        \
                }                                             \
                break;                                        \
            case SMTD_ACTION_RELEASE:                         \
                if (tap_count < threshold) {                  \
                    unregister_mods(MOD_BIT(mod));            \
                    send_keyboard_report();                   \
                } else {                                      \
                    SMTD_UNREGISTER_16(use_cl, tap_key);      \
                }                                             \
                break;                                        \
        }                                                     \
        break;                                                \
    }

#define SMTD_LT5(macro_key, tap_key, layer, threshold, use_cl)\
    case macro_key: {                                         \
        switch (action) {                                     \
            case SMTD_ACTION_TOUCH:                           \
                break;                                        \
            case SMTD_ACTION_TAP:                             \
                SMTD_TAP_16(use_cl, tap_key);                 \
                break;                                        \
            case SMTD_ACTION_HOLD:                            \
                if (tap_count < threshold) {                  \
                    LAYER_PUSH(layer);                        \
                } else {                                      \
                    SMTD_REGISTER_16(use_cl, tap_key);        \
                }                                             \
                break;                                        \
            case SMTD_ACTION_RELEASE:                         \
                if (tap_count < threshold) {                  \
                    LAYER_RESTORE();                          \
                }                                             \
                SMTD_UNREGISTER_16(use_cl, tap_key);          \
                break;                                        \
        }                                                     \
        break;                                                \
    }

