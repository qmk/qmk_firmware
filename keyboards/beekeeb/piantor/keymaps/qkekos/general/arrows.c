
#include QMK_KEYBOARD_H
#include "arrows.h"

const int arrow_repeat_delay = 500;
const int base_arrow_repeat_rate = 25;
void *current_context;

int arrow_repeat_rate = base_arrow_repeat_rate;
deferred_token string_repeat_token = INVALID_DEFERRED_TOKEN;

uint32_t restore_base_repeat_rate(uint32_t trigger_time, void *cb_arg) {
    arrow_repeat_rate = base_arrow_repeat_rate;
    return 0;
}

uint32_t arrow_repeat_cb(uint32_t trigger_time, void *cb_arg) {
    send_string((const char *)cb_arg);
    if (arrow_repeat_rate == arrow_repeat_delay) defer_exec(arrow_repeat_delay - base_arrow_repeat_rate, restore_base_repeat_rate, NULL);

    return arrow_repeat_rate;
}

bool send_repeated_arrow(bool key_down, void *context) {
    if (context == current_context || key_down) cancel_deferred_exec(string_repeat_token);
    arrow_repeat_rate = arrow_repeat_delay;

    if (key_down) {
        current_context = context;
        send_string((const char *)context);

        arrow_repeat_rate = base_arrow_repeat_rate;
        string_repeat_token = defer_exec(arrow_repeat_delay, arrow_repeat_cb, (void *)context);
    }

    return false;
}
