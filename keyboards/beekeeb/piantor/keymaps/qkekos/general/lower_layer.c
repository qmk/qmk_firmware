
#include "../__init__.h"

layer_state_t old_layer_state;

enum pr_response lower_layer_mo(int target_layer, keyrecord_t *record) {
    if (record->event.pressed) {
        old_layer_state = layer_state;
        layer_state = (layer_state & ((1 << (target_layer + 1)) - 1)) | (1 << target_layer);
    } else {
        layer_state = old_layer_state;
    }

    return false;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    old_layer_state &= state;
    return state;
}
