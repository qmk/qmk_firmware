#include "cybr-x.h"

bool encoder_update_user(uint8_t index, bool clockwise) {
    switch(index) {
        case 0:
            if (clockwise) {
                tap_code(KC_VOLU);
            } else {
                tap_code(KC_VOLD);
            }
            break;
        case 1:
            if (clockwise) {
                tap_code(KC_MEDIA_NEXT_TRACK);
            } else {
                tap_code(KC_MEDIA_PREV_TRACK);
            }
            break;
    }
    return true;
}

bool oled_task_user(void) {
    oled_write_P(PSTR("CYBR-X: Enhanced Edition\n"), false);
    return false;
}
