#include "mouse.h"

#if defined(AUTOMOUSE_ENABLED)
void pointing_device_init_user(void) {
    set_auto_mouse_layer(_MOUSE);        // only required if AUTO_MOUSE_DEFAULT_LAYER is not set to index of <mouse_layer>
    set_auto_mouse_enable(true);         // always required before the auto mouse feature will work
}

bool is_mouse_record_user(uint16_t keycode, keyrecord_t* record) {
    switch(keycode) {
        case KC_LGUI:
        case KC_LALT:
        case KC_LCTL:
        case KC_LSFT:
            return true;
        case QK_KB ... QK_KB_MAX:
            return true;
        default:
            return false;
    }
    return false;
}
#endif //POINTING_DEVICE_AUTO_MOUSE_ENABLE