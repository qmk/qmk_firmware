#include "idb_60.h"

void keyboard_pre_init_kb(void) {
    setPinOutput(C4);
    setPinOutput(C5);
}

inline void _idb_60_caps_led_on(void) {
    writePinLow(C5);
}

inline void _idb_60_fn_led_on(void) {
    writePinLow(C4);
}

inline void _idb_60_caps_led_off(void) {
    writePinHigh(C5);
}

inline void _idb_60_fn_led_off(void) {
    writePinHigh(C4);
}

// Capslock LED indicator

bool led_update_kb(led_t led_state) {
    bool res = led_update_user(led_state);
    if (res) {
        if (led_state.caps_lock) {
            _idb_60_caps_led_on();
        } else {
            _idb_60_caps_led_off();
        }
    }
    return res;
}

// Layer LED indicator - drive LED when not on base layer

__attribute__((weak)) layer_state_t layer_state_set_user(layer_state_t state) {
    if (get_highest_layer(state) == 0) {
        _idb_60_fn_led_off();
    } else {
        _idb_60_fn_led_on();
    }
    return state;
}
