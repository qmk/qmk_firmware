#include "csc027.h"

GIT_MACROS(DROP, GIT_DEF, PARAMS, SEMI_DELIM);
const char mc_mrd7[] PROGMEM = SS_LCTRL(SS_LALT(SS_TAP(X_HOME)))"\t ";
const char mc_mrd8[] PROGMEM = SS_LCTRL(SS_LALT(SS_TAP(X_HOME)))"\t\t\t ";
const char mc_atrd[] PROGMEM = SS_LCTRL(SS_LALT(SS_TAP(X_HOME)))SS_LALT("\t");

static const char* const git_macros[] PROGMEM = {
    // Make sure that the macro strings match the order they are declared
    // in the custom_keycodes enum.
    GIT_MACROS(DROP, GIT_VAR, DROP, COMMA_DELIM),
    mc_mrd7,
    mc_mrd8,
    mc_atrd
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch(keycode) {
        case LOWER:
            if(record->event.pressed) {
                layer_on(_LW);
                update_tri_layer(_LW, _RS, _MS);
            } else {
                layer_off(_LW);
                update_tri_layer(_LW, _RS, _MS);
            }
            return false;
        case RAISE:
            if(record->event.pressed) {
                layer_on(_RS);
                update_tri_layer(_LW, _RS, _MS);
            } else {
                layer_off(_RS);
                update_tri_layer(_LW, _RS, _MS);
            }
            return false;
        case GIT_ADD...MC_ATRD:
            if(record->event.pressed) {
                // The calculation here is to make sure that the custom keycode
                // aligns with the git_macros array.
                send_string_P((char*)pgm_read_word(&git_macros[keycode - GIT_ADD]));
                return true;
            }
            return false;
        default:
            return true;
    }
}
