#include "ak81_ve.h"

#if !defined(VIA_ENABLE) && defined(ENCODER_ENABLE)
bool encoder_update_kb(uint8_t index, bool clockwise) {
    if (!encoder_update_user(index, clockwise)) {
        return false;
    }
    if (clockwise) {
        tap_code(KC_VOLD);
    } else {
        tap_code(KC_VOLU);
    }
    return true;
}
#endif