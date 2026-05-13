/*
 * keymaps.c QMK keymap for BitDeck10
 * Copyright (C) 2026 morisoba
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H
#include "layers.h"

#ifdef ENCODER_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    // Volume UP/DOWN
    [_BASE]   = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [_LOWER]  = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [_RAISE]  = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [_ADJUST] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)}
};
#endif // ENCODER_ENABLE

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* For Text
     *                                     ┌────────┐
     *                                     │  MUTE  │
     * ┌────────┬────────┬────────┬────────┼────────┤
     * │  COPY  │ PASTE  │  UNDO  │  REDO  │_ADJUST │
     * ├────────┼────────┼────────┼────────┼────────┤
     * │SEL_ALL │SEL_WORD│ ←WORD  │ WORD→  │ _LOWER │
     * └────────┴────────┴────────┴────────┴────────┘
     */
    [_BASE] = LAYOUT(KC_MUTE,
        C(KC_C),        C(KC_V),        C(KC_Z),        C(KC_Y),        TO(_ADJUST),
        C(KC_A),        LCS(KC_RGHT),   C(KC_LEFT),     C(KC_RIGHT),    TO(_LOWER)),

    /* For Browser
     *                                     ┌────────┐
     *                                     │  MUTE  │
     * ┌────────┬────────┬────────┬────────┼────────┤
     * │REFRESH │  URL   │ BACK   │  FWD   │ _BASE  │
     * ├────────┼────────┼────────┼────────┼────────┤
     * │ NewTab │CloseTab│  ←TAB  │  TAB→  │ _RAISE │
     * └────────┴────────┴────────┴────────┴────────┘
     */
    [_LOWER] = LAYOUT(KC_MUTE,
        KC_WREF,        C(KC_R),        KC_WBAK,        KC_WFWD,        TO(_BASE),
        C(KC_T),        C(KC_W),        LCS(KC_TAB),    C(KC_TAB),      TO(_RAISE)
    ),

    /* For YouTube
     *                                     ┌────────┐
     *                                     │  MUTE  │
     * ┌────────┬────────┬────────┬────────┼────────┤
     * │  PLAY  │MiniPlay│ -5sec  │ +5sec  │ _LOWER │
     * ├────────┼────────┼────────┼────────┼────────┤
     * │SubTitle│FullScrn│SpdDown │ SpdUp  │_ADJUST │
     * └────────┴────────┴────────┴────────┴────────┘
     */
    [_RAISE] = LAYOUT(KC_MUTE,
        KC_MPLY,        KC_I,           KC_LEFT,        KC_RIGHT,       TO(_LOWER),
        KC_C,           KC_F,           S(KC_COMM),     S(KC_DOT),      TO(_ADJUST)
    ),

    /* For Excel
     *                                     ┌────────┐
     *                                     │  MUTE  │
     * ┌────────┬────────┬────────┬────────┼────────┤
     * │ COPY   │ PASTE  │  UNDO  │  REDO  │ _RAISE │
     * ├────────┼────────┼────────┼────────┼────────┤
     * │AUTOSUM │PASTE_V │ ←SHEET │ SHEET→ │ _BASE  │
     * └────────┴────────┴────────┴────────┴────────┘
     */
    [_ADJUST] = LAYOUT(KC_MUTE,
        C(KC_C),        C(KC_V),        C(KC_Z),        C(KC_Y),        TO(_RAISE),
        A(KC_MINUS),    LCS(KC_V),      C(KC_PGUP),     C(KC_PGDN),     TO(_BASE)
    )
};
