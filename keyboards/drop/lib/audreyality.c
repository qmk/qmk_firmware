#include "audreyality.h"

bool to_default_layer(void) {
    if(layer_state_is(_DFL_MACOS)) {
        layer_move(_DFL_MACOS);
    } else if(layer_state_is(_DFL_WINDOWS)) {
        layer_move(_DFL_WINDOWS);
    } else {
        layer_move(AUD_DEFAULT_LAYER);
    }

    return false;
}

inline bool flap(keyrecord_t *record, uint16_t code) {
    if (record->event.pressed) {
        register_code16(code);
    } else {
        unregister_code16(code);
    }

    return false; // Skip all further processing of this key
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_SPOT:
            return flap(record, 0x221);
        case KC_DICT:
            return flap(record, 0xCF);
        case KC_DND:
            return flap(record, 0x9B);
        case E_X_I_T:
            return to_default_layer();

    }
    return true;
}
