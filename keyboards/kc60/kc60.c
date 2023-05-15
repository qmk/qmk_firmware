#include "kc60.h"

void led_update_ports(led_t led_state) {
    if (led_state.caps_lock) {
        setPinOutput(B2);
    } else {
        setPinInput(B2);
    }
}
