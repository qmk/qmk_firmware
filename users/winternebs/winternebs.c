#include "winternebs.h"
#include "g/keymap_combo.h"
#ifdef CONSOLE_ENABLE
#    include "print.h"
#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
#ifdef CONSOLE_ENABLE
        uprintf("0x%04X,%u,%u,%u\n", keycode, record->event.key.row, record->event.key.col, get_highest_layer(layer_state));
#endif
    }
    return true;
}
layer_state_t layer_state_set_user(layer_state_t state) { return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST); }
bool          get_ignore_mod_tap_interrupt(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LOWER:
            return false;
        default:
            return true;
    }
}
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case HOME_A:
        case HOME_S:
        case HOME_O:
        case HOME_I:
            return TAPPING_TERM + 50;
        case LOWER:
            return TAPPING_TERM - 50;
        default:
            return TAPPING_TERM;
    }
}
/**
 * TODO:
 * Mouse keys?
 * Game layer
 * move <> onto symbol layers?
 * replace < > with '"
 * replace q ?
 */
