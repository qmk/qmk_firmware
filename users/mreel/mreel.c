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

qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_SHAP] = ACTION_TAP_DANCE_DOUBLE(KC_RSFT, KC_CAPS)
};

const qk_ucis_symbol_t ucis_symbol_table[] = UCIS_TABLE(
    UCIS_SYM("love", 0x2665),                       // ♥
    UCIS_SYM("degree", 0x1BC85),                    // 𛲅
    UCIS_SYM("deg", 0x1BC85),                       // 𛲅
    UCIS_SYM("delta", 0x0394),                      // Δ
    UCIS_SYM("euro", 0x20AC),                       // €
    UCIS_SYM("eur", 0x20AC),                        // €
    UCIS_SYM("pound", 0x00A3),                      // £
    UCIS_SYM("plusminus", 0x00B1),                  // ±
    UCIS_SYM("inv", 0x2062),                        // invisible times
    UCIS_SYM("kiss", 0x1F618)                       // 😘
);