
#pragma once
#include "../__init__.h"

enum td_actions {
    TD_TAP,
    TD_HOLD,
    TD_DOUBLE_TAP,
};

enum multiaction_type {
    TAP_HOLD,
    DOUBLE_TAP
};

#define tap_hold_case(tap, hold) \
    switch (action) { \
        case TD_TAP: \
            tap; \
            break; \
            \
        case TD_HOLD: \
            hold; \
            break; \
            \
        default: SEND_STRING("!!! Tap hold got something else."); \
    }

#define double_tap_case(tap, double_tap) \
    switch (action) { \
        case TD_TAP: \
            tap; \
            break; \
            \
        case TD_DOUBLE_TAP: \
            double_tap; \
            break; \
            \
        default: SEND_STRING("!!! Double tap got something else."); \
    }

#define assign_td_type_handler(data, callback) \
    switch (data->type) { \
        case TAP_HOLD: \
            callback = defer_hold; \
            break; \
            \
        case DOUBLE_TAP: \
            callback = defer_tap; \
            break; \
    }

#define MULTIACTION_COUNT 10
typedef void (*tap_hold_cb)(enum td_actions action);
typedef uint32_t (*defer_cb)(uint32_t trigger_time, void *cb_arg);

typedef struct {
    int index;
    tap_hold_cb callback;
    enum multiaction_type type;
} multiaction_td_data;

#define TAP_DANCE_TAP_HOLD(index, callback) \
    { .fn = {on_tap_fn, NULL, NULL}, .user_data = (void *)&((multiaction_td_data){index, callback, TAP_HOLD}), }

#define TAP_DANCE_DOUBLE(index, callback) \
    { .fn = {on_tap_fn, NULL, NULL}, .user_data = (void *)&((multiaction_td_data){index, callback, DOUBLE_TAP}), }

void on_tap_fn(tap_dance_state_t *state, void *user_data);
bool td_pr(uint16_t keycode, keyrecord_t *record, bool *return_value);bool td_process_record(uint16_t keycode, keyrecord_t *record, bool *return_value);

void reset_token(void);

void send_hold(multiaction_td_data *data);
void send_tap(multiaction_td_data *data);
void send_double_tap(multiaction_td_data *data);

uint32_t defer_hold(uint32_t trigger_time, void *cb_arg);
uint32_t defer_tap(uint32_t trigger_time, void *cb_arg);
uint32_t defer_double_tap(uint32_t trigger_time, void *cb_arg);
