#include "pdl.h"

// unshifted
//
// regardless of current mods, send this character in an unshifted state

__attribute__ ((weak))
bool unshifted (uint16_t keycode, keyrecord_t *record) {
    uint8_t mods;

    if (record->event.pressed) {
        mods = keyboard_report->mods & EITHER_SHIFT;

        if (mods) {
            unregister_mods(mods);
            register_code(keycode);
            register_mods(mods);
        } else {
            register_code(keycode);
        }

        return false;
    } else {
        return true;
    }
}

/*
 * update_punctn_coding_layer_state
 *
 * Check NAVIGN and NUMBRS layers. If one is activated, also activate PUNCTN. If both are activated, also activate CODING.
 */

__attribute__ ((weak))
uint32_t update_punctn_coding_layer_state(uint32_t state) {
    uint32_t maskEither = (1UL << _NAVIGN) | (1UL << _NUMBRS);
    uint32_t maskPunctn = 1UL << _PUNCTN;
    uint32_t maskCoding = 1UL << _CODING;

    return (
        (state & maskEither)
        ? (state & maskEither) == maskEither
            ? (state & ~maskPunctn) | maskCoding // both    => coding
            : (state | maskPunctn) & ~maskCoding // either  => punctn
        : (state & ~maskCoding) & ~maskPunctn    // neither => neither
    );
}

__attribute__ ((weak))
uint32_t layer_state_set_user(uint32_t state) {
    return update_punctn_coding_layer_state(state);
}

__attribute__ ((weak))
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case QK_LAYER_TAP_TOGGLE ... QK_LAYER_TAP_TOGGLE_MAX:
            if (record->event.pressed) {
                // ensure that the toggled layer is switched off by a single tap
                layer_off(keycode & 0xFF);
            }
            break;
        case QWERTY:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_QWERTY);
            }
            return false;
            break;
        case PROXIM:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_PROXIM);
            }
            return false;
            break;
        // KC_LBRC, KC_NUHS, KC_GRV, KC_RBRC [&#`]
        // These four keys are unshifted in the UK layout and should be sent as such.
        case KC_LBRC:
            return unshifted(keycode, record);
        case KC_NUHS:
            return unshifted(keycode, record);
        case KC_GRV:
            return unshifted(keycode, record);
        case KC_RBRC:
            return unshifted(keycode, record);
    }
    return true;
}
