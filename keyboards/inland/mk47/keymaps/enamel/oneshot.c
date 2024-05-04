#include "quantum.h"
#include "oneshot.h"

void update_oneshot(
    oneshot_state *osstate,
    uint16_t mod,
    uint16_t trigger,
    uint16_t keycode,
    keyrecord_t *record
) {
    if (keycode == trigger) {
        if (record->event.pressed) {
            // Trigger keydown
            if (*osstate == os_up_unqueued) {
                register_code(mod);
            }
            *osstate = os_down_unused;
        } else {
            // Trigger keyup
            switch (*osstate) {
            case os_down_unused:
                // If we didn't use the mod while trigger was held, queue it.
                *osstate = os_up_queued;
                break;
            case os_down_used:
                // If we did use the mod while trigger was held, unregister it.
                *osstate = os_up_unqueued;
                unregister_code(mod);
                break;
            default:
                break;
            }
        }
    } else {
        if (record->event.pressed) {
            if (is_oneshot_cancel_key(keycode) && *osstate != os_up_unqueued) {
                // Cancel oneshot on designated cancel keydown.
                *osstate = os_up_unqueued;
                unregister_code(mod);
            }
        } else {
            if (!is_oneshot_ignored_key(keycode)) {
                // On non-ignored keyup, consider the oneshot used.
                switch (*osstate) {
                case os_down_unused:
                    *osstate = os_down_used;
                    break;
                case os_up_queued:
                    *osstate = os_up_unqueued;
                    unregister_code(mod);
                    break;
                default:
                    break;
                }
            }
        }
    }
}