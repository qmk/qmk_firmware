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

#include "unicode.h"
#include "mreel.h"

// *** UCIS ***
const qk_ucis_symbol_t ucis_symbol_table[] = UCIS_TABLE(
    UCIS_SYM("love", 0x2665),                       // ♥
    UCIS_SYM("degree", 0x1BC85),                    // 𛲅  Not actual degree symbol (0x00B0), hexcodes ending in 0 don't work on macos….
    UCIS_SYM("deg", 0x1BC85),                       // 𛲅
    UCIS_SYM("delta", 0x0394),                      // Δ
    UCIS_SYM("euro", 0x20AC),                       // €
    UCIS_SYM("eur", 0x20AC),                        // €
    UCIS_SYM("pound", 0x00A3),                      // £
    UCIS_SYM("plusminus", 0x00B1),                  // ±
    UCIS_SYM("inv", 0x2062)                         // invisible times
);

void qk_ucis_cancel(void) {
    if (!layer_state_is(_WIN)) {tap_code16(C(LOPT(KC_BSLS)));} //switch back to normal input on macos
}

void qk_ucis_symbol_fallback(void) {
    if (!layer_state_is(_WIN)) {tap_code16(C(LOPT(KC_BSLS)));} //switch back to normal input on macos
}

void qk_ucis_success(uint8_t symbol_index) {
    if (!layer_state_is(_WIN)) {tap_code16(C(LOPT(KC_BSLS)));} //switch back to normal input on macos
}

// *** Unicode map ***
bool process_record_unicodemap(uint16_t keycode, keyrecord_t *record) {
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
