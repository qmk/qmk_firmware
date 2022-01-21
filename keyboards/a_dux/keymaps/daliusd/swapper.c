#include "swapper.h"

bool active;

void update_swapper(
    uint16_t trigger,
    uint16_t keycode,
    bool pressed
) {
    if (keycode == trigger) {
        if (pressed) {
            if (!active) {
                active = true;
                register_code(KC_LGUI);
            }
            register_code(KC_TAB);
        } else {
            unregister_code(KC_TAB);
        }
    } else if (active && keycode != KC_LSFT) {
        unregister_code(KC_LGUI);
        active = false;
    }
}
