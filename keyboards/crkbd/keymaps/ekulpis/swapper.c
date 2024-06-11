// Copyright Callum Oakley
// https://github.com/callum-oakley/qmk_firmware/tree/master/users/callum

#include "swapper.h"

void update_swapper(
    bool *active,
    uint16_t cmdish,
    uint16_t tabish,
    uint16_t trigger,
    uint16_t keycode,
    keyrecord_t *record
) {
    if (keycode == trigger) {
        if (record->event.pressed) {
            if (!*active) {
                *active = true;
                register_code16(cmdish);
            }
            register_code16(tabish);
        } else {
            unregister_code16(tabish);
            // Don't unregister cmdish until some other key is hit or released.
        }
    } else if (*active) {
        unregister_code16(cmdish);
        *active = false;
    }
}