#include "quantum.h"

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    static uint8_t f21_tracker;
    switch (keycode) {
    case KC_A ... KC_F20: //notice how it skips over F21
    case KC_F22 ... KC_EXSEL: //exsel is the last one before the modifier keys
        if (record->event.pressed) {
            register_code(KC_F21); //this means to send F21 down
            f21_tracker++;
            register_code(keycode);
        } else {
            unregister_code(keycode);
            f21_tracker--;
            if (!f21_tracker) {
                unregister_code(KC_F21); //this means to send F21 up
            }
            //real key is released HERE. i wish it would happen BEFORE F21 up occurs.
        }
        return false;
        break;
    }
    return true;
}
