/*
Copyright 2022 Tibo Loete, aka Mister Eel <mistermister1111@hotmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program. If not, see <https://www.gnu.org/licenses/>.
*/

#include "mreel.h"

const qk_ucis_symbol_t ucis_symbol_table[] = UCIS_TABLE(
    UCIS_SYM("love", 0x2665),                       // ♥
    UCIS_SYM("degree", 0x1BC85),                    // 𛲅  Not actual degree symbol (0x00B0), hexcodes ending in 0 don't work on macos...
    UCIS_SYM("deg", 0x1BC85),                       // 𛲅
    UCIS_SYM("delta", 0x0394),                      // Δ
    UCIS_SYM("euro", 0x20AC),                       // €
    UCIS_SYM("eur", 0x20AC),                        // €
    UCIS_SYM("pound", 0x00A3),                      // £
    UCIS_SYM("plusminus", 0x00B1),                  // ±
    UCIS_SYM("inv", 0x2062)                         // invisible times
);

 bool process_custom_unicodemap(uint16_t keycode, keyrecord_t *record) {
    bool is_shifted = (get_mods() | get_oneshot_mods()) & MOD_MASK_SHIFT;
    bool caps  = host_keyboard_led_state().caps_lock;   // capslock needs to be checked from ledstate because it can be influenced from other keyboards
    is_shifted = is_shifted ^ caps;                     // either caps lock, or shift in on, not both
    switch (keycode) {
        case UC_TRMI:
            send_unicode_string(!is_shifted ? "ï" : "Ï");
            return true;
        case UC_TRMU:
            send_unicode_string(!is_shifted ? "ü" : "Ü");
            return true;
        case UC_TRMO:
            send_unicode_string(!is_shifted ? "ö" : "Ö");
            return true;
        case UC_TRME:
            send_unicode_string(!is_shifted ? "ë" : "Ë");
            return true;
        case UC_AGRE:
            send_unicode_string(!is_shifted ? "è" : "È");
            return true;
        case UC_AAGE:
            send_unicode_string(!is_shifted ? "é" : "É");
            return true;
        case UC_ACRE:
            send_unicode_string(!is_shifted ? "ê" : "Ê");
            return true;
        case UC_SP23:
            send_unicode_string(!is_shifted ? "²" : "³");
            return true;
        case UC_SMLE:
            send_unicode_string("😊");
            return true;
        case UC_COL:
            send_unicode_string("꞉");
            return true;
    }
    return true;
 }

 bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_TAB:
            if (record->event.pressed && layer_state_is(_WIN) && ((get_mods() & MOD_BIT(KC_LCTL)) == MOD_BIT(KC_LCTL))) { //if windows and lctl is active replace with alt
                set_mods(MOD_BIT(KC_LALT));
            }
            return true;
        case KC_LCTL:
            if (!record->event.pressed && layer_state_is(_WIN)) {
                if ((!(get_mods() & MOD_MASK_CTRL)) && ((get_mods() & MOD_BIT(KC_LALT)) == MOD_BIT(KC_LALT))) {  //no ctrl and yes left alt
                    unregister_code(KC_LALT);
                    return false;
                }
            }
            return true;

        case CK_BWRD:
            if (record->event.pressed) {
                tap_code16(layer_state_is(_WIN) ? C(KC_BSPC) : LOPT(KC_BSPC));
            }
            return true;

        case CK_HOME:
            if (record->event.pressed) {
                tap_code16(layer_state_is(_WIN) ? KC_HOME : LCMD(KC_LEFT));
            }
            return true;

        case CK_END:
            if (record->event.pressed) {
                tap_code16(layer_state_is(_WIN) ? KC_END : LCMD(KC_RGHT));
            }
            return true;

        case CK_VOLU:
            if (record->event.pressed) {
                tap_code16(layer_state_is(_WIN) ? KC_VOLU : LOPT(S(KC_KB_VOLUME_UP)));
            }
            return true;

        case CK_VOLD:
            if (record->event.pressed) {
                tap_code16(layer_state_is(_WIN) ? KC_VOLD : LOPT(S(KC_KB_VOLUME_DOWN)));
            }
            return true;

        case CK_DLFT:
            if (record->event.pressed) {
                tap_code16(layer_state_is(_WIN) ? C(LWIN(KC_LEFT)) : C(KC_LEFT));
            }
            return true;

        case CK_DRHT:
            if (record->event.pressed) {
                tap_code16(layer_state_is(_WIN) ? C(LWIN(KC_RGHT)) : C(KC_RGHT));
            }
            return true;

        case CK_LWRD:
            if (record->event.pressed) {
                tap_code16(layer_state_is(_WIN) ? C(KC_LEFT) : LOPT(KC_LEFT));
            }
            return true;

        case CK_RWRD:
            if (record->event.pressed) {
                tap_code16(layer_state_is(_WIN) ? C(KC_RGHT) : LOPT(KC_RGHT));
            }
            return true;


        case UC_UCIS:
            if (record->event.pressed) {
                if (!layer_state_is(_WIN)) {tap_code16(C(LOPT(KC_BSLS)));} //switch to unicode hex input on macos
                qk_ucis_start();
                }
            return false;
        case UC_TRMI ... UC_COL:
            if (record->event.pressed) {
                if (!layer_state_is(_WIN)) {tap_code16(C(LOPT(KC_BSLS)));} //switch to unicode hex input on macos
                process_custom_unicodemap(keycode, record);
            }
    }
    return true;
}

void post_process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case UC_TRMI ... UC_COL:
    if (record->event.pressed) {
        if (!layer_state_is(_WIN)) {tap_code16(C(LOPT(KC_BSLS)));} //switch back to normal input on macos
    }
  }
}

void qk_ucis_symbol_fallback(void) {
    if (!layer_state_is(_WIN)) {tap_code16(C(LOPT(KC_BSLS)));} //switch back to normal input on macos
}

void qk_ucis_success(uint8_t symbol_index) {
    if (!layer_state_is(_WIN)) {tap_code16(C(LOPT(KC_BSLS)));} //switch back to normal input on macos
}

void qk_ucis_cancel(void) {
    if (!layer_state_is(_WIN)) {tap_code16(C(LOPT(KC_BSLS)));} //switch back to normal input on macos
}
