#include "static.h"

const uint16_t DEAD_KEY_CODES [] = { NO_TILD, NO_CIRC, NO_GRV };

// Replace key records with macros
bool handle_dead_keys(uint16_t keycode, keyrecord_t* record) {
    switch (keycode) {
    case NO_TILD_M ... NO_GRV_M:
        tap_dead_key(DEAD_KEY_CODES[keycode]);
    }
    return true;
};

bool process_static(uint16_t keycode, keyrecord_t* record) {
    if (!handle_dead_keys(keycode, record)) {
        return false;
    }
    return true;
}
