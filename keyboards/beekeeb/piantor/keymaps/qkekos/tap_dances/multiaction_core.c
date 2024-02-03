
#include "../__init__.h"

deferred_token defer_token = INVALID_DEFERRED_TOKEN;
multiaction_td_data *current_td = NULL;

void on_tap_fn(tap_dance_state_t *state, void *user_data) {
    if (defer_token != INVALID_DEFERRED_TOKEN || state->count > 1) return;
    current_td = (multiaction_td_data *)(user_data);

    defer_cb callback;
    assign_td_type_handler(current_td, callback);

    defer_token = defer_exec(get_tapping_term(TD(current_td->index), NULL), callback, user_data);
}

bool td_pr(uint16_t keycode, keyrecord_t *record, bool *return_value) {
    *return_value = true;

    if (current_td != NULL) {
        if (IS_QK_TAP_DANCE(keycode) && TD_INDEX(keycode) == current_td->index) {
            switch (current_td->type) {
                case TAP_HOLD:
                    if (!record->event.pressed && defer_token != INVALID_DEFERRED_TOKEN)
                        send_tap(current_td);

                    return true;

                case DOUBLE_TAP:
                    if (record->event.pressed && defer_token != INVALID_DEFERRED_TOKEN)
                        send_double_tap(current_td);

                    return true;
            }
        } else {
            send_tap(current_td);
            return true;
        }
    }

    return false;
}

void reset_token(void) {
    if (defer_token != INVALID_DEFERRED_TOKEN)
        cancel_deferred_exec(defer_token);

    defer_token = INVALID_DEFERRED_TOKEN;
    current_td = NULL;
}

void send_hold(multiaction_td_data *data) {
    (*(data->callback))(TD_HOLD);
    reset_token();
}

void send_tap(multiaction_td_data *data) {
    (*(data->callback))(TD_TAP);
    reset_token();
}

void send_double_tap(multiaction_td_data *data) {
    (*(data->callback))(TD_DOUBLE_TAP);
    reset_token();
}

uint32_t defer_hold(uint32_t trigger_time, void *cb_arg) {
    send_hold((multiaction_td_data *)(cb_arg));
    return 0;
}

uint32_t defer_tap(uint32_t trigger_time, void *cb_arg) {
    send_tap((multiaction_td_data *)(cb_arg));
    return 0;
}

uint32_t defer_double_tap(uint32_t trigger_time, void *cb_arg) {
    send_double_tap((multiaction_td_data *)(cb_arg));
    return 0;
}
