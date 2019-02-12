#include "quantum.h"

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    static uint8_t f24_tracker;
    switch (keycode) {
    case KC_A ... KC_F23: //notice how it skips over F24
    case KC_EXECUTE ... KC_EXSEL: //exsel is the last one before the modifier keys
        if (record->event.pressed) {
            register_code(KC_F24); //this means to send F24 down
            f24_tracker++;
            register_code(keycode);
        } else {
            unregister_code(keycode);
            f24_tracker--;
            if (!f24_tracker) {
                unregister_code(KC_F24); //this means to send F24 up
            }
            //real key is released HERE. i wish it would happen BEFORE F24 up occurs.
        }
        return false;
        break;
    }
    return true;
}
