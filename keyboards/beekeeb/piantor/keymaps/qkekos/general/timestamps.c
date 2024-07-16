
#include "../__init__.h"

int prev_key_timestamp;
int current_key_timestamp;

int prev_key_layerstamp;
int current_key_layerstamp;

int timestamps_pr(uint16_t keycode, keyrecord_t *record) {
    if (!record->event.pressed) return PR_IGNORE;

    prev_key_timestamp = current_key_timestamp;
    prev_key_layerstamp = current_key_layerstamp;

    current_key_timestamp = timer_read();
    current_key_layerstamp = highest_layer;

    return PR_IGNORE;
}
