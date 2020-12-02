#include "crbn.h"
/* Encoder setting. only one encoder despite 4 possible spots */
void encoder_update_kb(uint8_t index, bool clockwise) {
    if (clockwise) {
        tap_code(KC_VOLU);
    } else {
        tap_code(KC_VOLD);
    }
}
