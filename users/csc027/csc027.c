#include "csc027.h"

// Declare the strings in PROGMEM using the convenience macro
CUSTOM_MACROS(CUSTOM_DEF, CUSTOM_MACRO_STRING, SEMI_DELIM);

static const char* const custom_macros[] PROGMEM = {
    // Declare the pointer to the strings in PROGMEM
    CUSTOM_MACROS(CUSTOM_VAR, DROP, COMMA_DELIM)
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
                send_string_P(
#if defined(__AVR__)
                    // The accessor here first reads from the pointer array that is located
                    // in PROGMEM.  The pointer is taken and passed to the send_string_P
                    // function, which is aware of the difference between RAM and PROGMEM
                    // pointers.
                    (char*)pgm_read_word(&custom_macros[keycode - MC_first - 1])
#else
                    // For non-AVR MCUs, the PROGMEM macro is defined as nothing.  So, the strings are
                    // declared in RAM instead of flash.  The send_string_P function, when compiled for
                    // non-AVR targets, uses a different definition of pgm_read_byte internally.  This
                    // definition uses RAM pointers instead.  This is why the raw pointer is passed for
                    // non-AVR MCUs.
                    custom_macros[keycode - MC_first - 1]
#endif
                );
                return true;
            }
            return false;
        default:
            return true;
    }
}
