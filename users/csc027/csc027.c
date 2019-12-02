#include "csc027.h"

// Declare the strings in PROGMEM using the convenience macro
GIT_MACROS(DROP, GIT_DEF, PARAMS, SEMI_DELIM);
CUSTOM_MACROS(DROP, CUSTOM_DEF, SEMI_DELIM);

static const char* const git_macros[] PROGMEM = {
    // Declare the pointer to the strings in PROGMEM
    GIT_MACROS(DROP, GIT_VAR, DROP, COMMA_DELIM),
    CUSTOM_MACROS(DROP, CUSTOM_VAR, COMMA_DELIM)
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch(keycode) {
        case LOWER:
            if(record->event.pressed) {
                layer_on(_LW);
            } else {
                layer_off(_LW);
            }
            update_tri_layer(_LW, _RS, _MS);
            return false;
        case RAISE:
            if(record->event.pressed) {
                layer_on(_RS);
            } else {
                layer_off(_RS);
            }
            update_tri_layer(_LW, _RS, _MS);
            return false;
        case GIT_ADD...MC_ATRD:
            if(record->event.pressed) {
                // The accessor here first reads from the pointer array that is located
                // in PROGMEM.  The pointer is taken and passed to the send_string_P
                // function, which is aware of the difference between RAM and PROGMEM
                // pointers.
                send_string_P((char*)pgm_read_word(&git_macros[keycode - GIT_ADD]));
                return true;
            }
            return false;
        default:
            return true;
    }
}
