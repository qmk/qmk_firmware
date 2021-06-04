#include "mouse_jiggle.h"

bool is_mouse_jiggle_active = false;

void matrix_scan_mouse_jiggle(void) {
    if (is_mouse_jiggle_active) {
        tap_code(KC_MS_UP);
        tap_code(KC_MS_DOWN);
    }
}

bool process_record_mouse_jiggle(uint16_t keycode, const keyrecord_t *record) {
    if (!record->event.pressed) {
        return true;
    }

    if (is_mouse_jiggle_active) {
        // If active, quit whenever another key is pressed
        is_mouse_jiggle_active = false;
        return true;
    }

    if (keycode != MS_JIGL) {
        return true;
    }

    is_mouse_jiggle_active = true;
    SEND_STRING("Mouse jiggler enabled");
    return false;
}
