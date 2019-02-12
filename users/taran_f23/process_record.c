#include "quantum.h"

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    static uint8_t f23_tracker;
    switch (keycode) {
    case KC_A ... KC_F22: //notice how it skips over F23
    case KC_F24 ... KC_EXSEL: //exsel is the last one before the modifier keys
        if (record->event.pressed) {
            register_code(KC_F23); //this means to send F23 down
            f23_tracker++;
            register_code(keycode);
        } else {
            unregister_code(keycode);
            f23_tracker--;
            if (!f23_tracker) {
                unregister_code(KC_F23); //this means to send F23 up
            }
            //real key is released HERE. i wish it would happen BEFORE F23 up occurs.
        }
        return false;
        break;
    }
    return true;
}
