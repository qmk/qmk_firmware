#include "quantum.h"

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    static uint8_t f22_tracker;
    switch (keycode) {
    case KC_A ... KC_F21: //notice how it skips over F22
    case KC_F23 ... KC_EXSEL: //exsel is the last one before the modifier keys
        if (record->event.pressed) {
            register_code(KC_F22); //this means to send F22 down
            f22_tracker++;
            register_code(keycode);
        } else {
            unregister_code(keycode);
            f22_tracker--;
            if (!f22_tracker) {
                unregister_code(KC_F22); //this means to send F22 up
            }
            //real key is released HERE. i wish it would happen BEFORE F22 up occurs.
        }
        return false;
        break;
    }
    return true;
}
