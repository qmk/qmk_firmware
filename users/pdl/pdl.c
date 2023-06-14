/*
Copyright 2018-2021 Daniel Perrett

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

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

#ifdef COMBO_PDL
    return (
        (state & maskEither)
        ? (state | maskPunctn) & ~maskCoding  // either  => punctn
        : (state & ~maskCoding) & ~maskPunctn // neither => neither
    );
#endif

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
        // KC_LBRC, KC_NUHS, KC_GRV, KC_RBRC [#`]
        // These four keys are unshifted in the UK layout and should be sent as such.
        case KU_LBRC:
            return unshifted(KC_LBRC, record);
        case KU_NUHS:
            return unshifted(KC_NUHS, record);
        case KU_GRV:
            return unshifted(KC_GRV, record);
        case KU_RBRC:
            return unshifted(KC_RBRC, record);
        case KC_ESC:
            if (!record->event.pressed) {
                layer_off(_NUMBRS);
                layer_off(_NAVIGN);
                layer_off(_PUNCTN);
                layer_off(_CODING);
            }
            return true;
    }
    return true;
}

#ifdef COMBO_PDL
enum combos {
    VCOMBO_PU,
    VCOMBO_NU,
    VCOMBO_EU,
    VCOMBO_IU,
    VCOMBO_LU,
    VCOMBO_PD,
    VCOMBO_ND,
    VCOMBO_ED,
    VCOMBO_ID,
    VCOMBO_LD,
    HCOMBO_JR,
    HCOMBO_UR,
    HCOMBO_PR,
    HCOMBO_MR,
    HCOMBO_HR,
    XCOMBO_LEFT,
    XCOMBO_RIGHT,
    XCOMBO_UP,
    XCOMBO_DOWN,
    XCOMBO_ENTER,
    XCOMBO_DEL,
    XCOMBO_BKSP,
    XCOMBO_MINS,
    XCOMBO_TAB,
    XCOMBO_UNDO,
    XCOMBO_REDO,
    XCOMBO_PGUP,
    XCOMBO_PGDN
};

const uint16_t PROGMEM vcombo_pu[] = {KC_J,    KC_P, COMBO_END};
const uint16_t PROGMEM vcombo_nu[] = {KC_Y,    KC_N, COMBO_END};
const uint16_t PROGMEM vcombo_eu[] = {KC_O,    KC_E, COMBO_END};
const uint16_t PROGMEM vcombo_iu[] = {KC_U,    KC_I, COMBO_END};
const uint16_t PROGMEM vcombo_lu[] = {KC_QUOT, KC_L, COMBO_END};
const uint16_t PROGMEM vcombo_pd[] = {KC_M,    KC_P, COMBO_END};
const uint16_t PROGMEM vcombo_nd[] = {KC_H,    KC_N, COMBO_END};
const uint16_t PROGMEM vcombo_ed[] = {KC_COMM, KC_E, COMBO_END};
const uint16_t PROGMEM vcombo_id[] = {KC_DOT,  KC_I, COMBO_END};
const uint16_t PROGMEM vcombo_ld[] = {KC_SLSH, KC_L, COMBO_END};
const uint16_t PROGMEM hcombo_jr[] = {KC_J,    KC_Y, COMBO_END};
const uint16_t PROGMEM hcombo_ur[] = {KC_QUOT, KC_U, COMBO_END};
const uint16_t PROGMEM hcombo_pr[] = {KC_P,    KC_N, COMBO_END};
const uint16_t PROGMEM hcombo_mr[] = {KC_M,    KC_H, COMBO_END};
const uint16_t PROGMEM hcombo_hr[] = {KC_COMM, KC_H, COMBO_END};

const uint16_t PROGMEM xcombo_left[]   = {KC_K, KC_P, COMBO_END};
const uint16_t PROGMEM xcombo_right[]  = {KC_M, KC_G, COMBO_END};
const uint16_t PROGMEM xcombo_up[]     = {KC_B, KC_J, COMBO_END};
const uint16_t PROGMEM xcombo_down[]   = {KC_K, KC_M, COMBO_END};
const uint16_t PROGMEM xcombo_enter[]  = {KC_G, KC_P, COMBO_END};
const uint16_t PROGMEM xcombo_del[]    = {KC_M, KC_B, COMBO_END};
const uint16_t PROGMEM xcombo_bksp[]   = {KC_K, KC_J, COMBO_END};
const uint16_t PROGMEM xcombo_mins[]   = {KC_V, KC_H, COMBO_END};
const uint16_t PROGMEM xcombo_tab[]    = {KC_V, KC_K, COMBO_END};
const uint16_t PROGMEM xcombo_undo[]   = {KC_V, KC_J, COMBO_END};
const uint16_t PROGMEM xcombo_redo[]   = {KC_B, KC_H, COMBO_END};
const uint16_t PROGMEM xcombo_pgup[]   = {KC_G, KC_B, COMBO_END};
const uint16_t PROGMEM xcombo_pgdn[]   = {KC_G, KC_K, COMBO_END};

combo_t key_combos[] = {
    [VCOMBO_PU] = COMBO(vcombo_pu, KC_CIRC),
    [VCOMBO_NU] = COMBO(vcombo_nu, KC_LBRC),
    [VCOMBO_EU] = COMBO(vcombo_eu, LSFT(KC_9)),
    [VCOMBO_IU] = COMBO(vcombo_iu, LSFT(KC_0)),
    [VCOMBO_LU] = COMBO(vcombo_lu, KC_RBRC),
    [VCOMBO_PD] = COMBO(vcombo_pd, LSFT(KC_7)),
    [VCOMBO_ND] = COMBO(vcombo_nd, KC_EQL),
    [VCOMBO_ED] = COMBO(vcombo_ed, KC_MINS),
    [VCOMBO_ID] = COMBO(vcombo_id, LSFT(KC_1)),
    [VCOMBO_LD] = COMBO(vcombo_ld, LSFT(KC_5)),
    [HCOMBO_JR] = COMBO(hcombo_jr, KC_GRV),
    [HCOMBO_UR] = COMBO(hcombo_ur, LSFT(KC_2)),
    [HCOMBO_PR] = COMBO(hcombo_pr, LSFT(KC_8)),
    [HCOMBO_MR] = COMBO(hcombo_mr, KC_NUHS),
    [HCOMBO_HR] = COMBO(hcombo_hr, KC_NUBS),

    [XCOMBO_LEFT]   = COMBO(xcombo_left,  KC_LEFT),
    [XCOMBO_RIGHT]  = COMBO(xcombo_right, KC_RGHT),
    [XCOMBO_UP]     = COMBO(xcombo_up,    KC_UP),
    [XCOMBO_DOWN]   = COMBO(xcombo_down,  KC_DOWN),
    [XCOMBO_ENTER]  = COMBO(xcombo_enter, KC_ENT),
    [XCOMBO_DEL]    = COMBO(xcombo_del,   KC_DEL),
    [XCOMBO_BKSP]   = COMBO(xcombo_bksp,  KC_BSPC),
    [XCOMBO_MINS]   = COMBO(xcombo_mins,  KC_MINS),
    [XCOMBO_TAB]    = COMBO(xcombo_tab,   KC_TAB),
    [XCOMBO_UNDO]   = COMBO(xcombo_undo,  LCTL(KC_Y)),
    [XCOMBO_REDO]   = COMBO(xcombo_redo,  LCTL(KC_Z)),
    [XCOMBO_PGUP]   = COMBO(xcombo_pgup,  KC_PGUP),
    [XCOMBO_PGDN]   = COMBO(xcombo_pgdn,  KC_PGDN)
};

#endif
