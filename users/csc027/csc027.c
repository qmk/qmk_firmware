#include "csc027.h"

// Declare the strings in PROGMEM using the convenience macro
GIT_MACROS(GIT_DEF, PARAMS, SEMI_DELIM);
CUSTOM_MACROS(CUSTOM_DEF, SEMI_DELIM);

static const char* const git_macros[] PROGMEM = {
    // Declare the pointer to the strings in PROGMEM
    GIT_MACROS(GIT_VAR, DROP, COMMA_DELIM),
    CUSTOM_MACROS(CUSTOM_VAR, COMMA_DELIM)
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
        case (MC_first + 1)...(MC_last - 1):
            if(record->event.pressed) {
#if defined(__AVR__)
                // The accessor here first reads from the pointer array that is located
                // in PROGMEM.  The pointer is taken and passed to the send_string_P
                // function, which is aware of the difference between RAM and PROGMEM
                // pointers.
                send_string_P((char*)pgm_read_word(&git_macros[keycode - MC_first - 1]));
#else
                // For some reason, compiling using ChibiOS for STM boards works without explicitly
                // grabbing the PROGMEM pointer.  This is a hack until
                send_string_P(git_macros[keycode - MC_first - 1]);
#endif
                return true;
            }
            return false;
        default:
            return true;
    }
}
