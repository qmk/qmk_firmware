#include "crbn.h"
/* Encoder setting. only one encoder despite 4 possible spots */
__attribute__((weak)) void encoder_update_user(uint8_t index, bool clockwise) {
    if (clockwise) {
        tap_code(KC_VOLU);
    } else {
        tap_code(KC_VOLD);
    }
}
