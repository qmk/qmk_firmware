#include "process_records.h"

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case RGB_DEFAULT:
        if (record->event.pressed) {
            set_default_keyboard_rgb();
        }
        break;
    };
    return true;
}

void post_process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case KC_ASTG: // Using post process because we want autoshift state after it has been changed
        if (record->event.pressed) {
            set_autoshift_disabled_rgb();
        }
        break;
    }
}
