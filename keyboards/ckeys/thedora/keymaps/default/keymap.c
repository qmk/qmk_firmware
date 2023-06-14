/* Copyright 2019 Branden Byers (@brandenbyers)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H

enum layers {
    _BASE,   // base layer
    _MUSIC,  // music mode
    _MIDI,   // midi mode
    _MOUSE,  // mouse keys
    _ADMIN   // admin duties
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    //           ┌─────────┬─────────┬─────────┬─────────┬─────────┐
    //           │         │         │         │         │         │
    //           │    7    │    8    │    9    │    /    │  ADMIN  │
    //  ROTARY   │         │         │         │         │         │
    //  RIGHT:   ├─────────┼─────────┼─────────┼─────────┼─────────┤
    //  PAGE DOWN│         │         │         │         │         │
    //           │    4    │    5    │    6    │    *    │  MOUSE  │
    //  ROTARY   │         │         │         │         │         │
    //  LEFT:    ├─────────┼─────────┼─────────┼─────────┼─────────┤
    //  PAGE UP  │         │         │         │         │         │
    //           │    1    │    2    │    3    │    -    │  MIDI   │
    //           │         │         │         │         │         │
    // ┌─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
    // │  TOGGLE │         │         │         │         │         │
    // │  MUSIC  │    0    │    .    │    =    │    +    │  MUSIC  │
    // │         │         │         │         │         │         │
    // └─────────┴─────────┴─────────┴─────────┴─────────┴─────────┘

    [_BASE] = LAYOUT(
                KC_P7,    KC_P8  , KC_P9  , KC_PSLS, MO(_ADMIN),
                KC_P4,    KC_P5  , KC_P6  , KC_PAST, TG(_MOUSE),
                KC_P1,    KC_P2  , KC_P3  , KC_PMNS, TG(_MIDI),
        MU_TOGG,KC_P0,    KC_PDOT, KC_PEQL, KC_PPLS, MO(_MUSIC)
    ),

    // MUSIC LAYER
    //           ┌─────────┬─────────┬─────────┬─────────┬─────────┐
    //           │         │         │         │         │         │
    //           │         │         │         │         │         │
    //  ROTARY   │         │         │         │         │         │
    //  RIGHT:   ├─────────┼─────────┼─────────┼─────────┼─────────┤
    //  PAGE DOWN│         │         │         │         │         │
    //           │         │         │         │         │         │
    //  ROTARY   │         │         │         │         │         │
    //  LEFT:    ├─────────┼─────────┼─────────┼─────────┼─────────┤
    //  PAGE UP  │         │         │         │         │         │
    //           │         │         │         │  MODE   │         │
    //           │         │         │         │         │         │
    // ┌─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
    // │         │         │         │         │         │         │
    // │         │ RECORD  │  STOP   │         │  PLAY   │         │
    // │         │         │         │         │         │         │
    // └─────────┴─────────┴─────────┴─────────┴─────────┴─────────┘

    [_MUSIC] = LAYOUT(
                 _______, _______, _______, _______, _______,
                 _______, _______, _______, _______, _______,
                 _______, _______, _______, _______, MU_NEXT,
        _______, KC_LCTL, KC_LALT, _______, KC_LGUI, _______
    ),

    // MIDI LAYER
    //           ┌─────────┬─────────┬─────────┬─────────┬─────────┐
    //           │         │         │         │         │         │
    //           │   D♯    │    E    │    F    │   F♯    │    G    │
    //  ROTARY   │         │         │         │         │         │
    //  RIGHT:   ├─────────┼─────────┼─────────┼─────────┼─────────┤
    //  PAGE DOWN│         │         │         │         │         │
    //           │   A♯    │    B    │    C    │   C♯    │    D    │
    //  ROTARY   │         │         │         │         │         │
    //  LEFT:    ├─────────┼─────────┼─────────┼─────────┼─────────┤
    //  PAGE UP  │         │         │         │         │         │
    //           │    F    │   F♯    │    G    │   G♯    │    A    │
    //           │         │         │         │         │         │
    // ┌─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
    // │         │         │         │         │         │         │
    // │         │    C    │   C♯    │    D    │   D♯    │    E    │
    // │         │         │         │         │         │         │
    // └─────────┴─────────┴─────────┴─────────┴─────────┴─────────┘

    [_MIDI] = LAYOUT(
                 MI_Ds3, MI_E3,  MI_F3,  MI_Fs3, MI_G3,
                 MI_As2, MI_B2,  MI_C3,  MI_Cs3, MI_D3,
                 MI_F2,  MI_Fs2, MI_G2,  MI_Gs2, TG(_MIDI),
        _______, MI_C2,  MI_Cs2, MI_D2,  MI_Ds2, MI_E2
    ),

    // MOUSE LAYER
    //           ┌─────────┬─────────┬─────────┬─────────┬─────────┐
    //           │         │         │         │         │         │
    //           │  BTN 5  │         │  WHEEL  │         │         │
    //  ROTARY   │         │         │   UP    │         │         │
    //  RIGHT:   ├─────────┼─────────┼─────────┼─────────┼─────────┤
    //  PAGE DOWN│         │         │         │         │         │
    //           │         │  LEFT   │  MOUSE  │  RIGHT  │         │
    //  ROTARY   │         │  CLICK  │   UP    │  CLICK  │         │
    //  LEFT:    ├─────────┼─────────┼─────────┼─────────┼─────────┤
    //  PAGE UP  │         │         │         │         │         │
    //           │  BTN 4  │  MOUSE  │  MOUSE  │  MOUSE  │         │
    //           │         │  LEFT   │  DOWN   │  RIGHT  │         │
    // ┌─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
    // │         │         │         │         │         │         │
    // │         │  BTN 3  │  WHEEL  │  WHEEL  │  WHEEL  │         │
    // │         │         │  LEFT   │  DOWN   │  RIGHT  │         │
    // └─────────┴─────────┴─────────┴─────────┴─────────┴─────────┘

    [_MOUSE] = LAYOUT(
                 KC_BTN5, _______, KC_WH_U, _______, _______,
                 _______, KC_BTN1, KC_MS_U, KC_BTN2, TG(_MOUSE),
                 KC_BTN4, KC_MS_L, KC_MS_D, KC_MS_R, _______,
        _______, KC_BTN3, KC_WH_L, KC_WH_D, KC_WH_R, _______
    ),

    // ADMIN LAYER
    //           ┌─────────┬─────────┬─────────┬─────────┬─────────┐
    //           │         │         │         │         │         │
    //           │  QK_BOOT  │         │         │         │         │
    //  ROTARY   │         │         │         │         │         │
    //  RIGHT:   ├─────────┼─────────┼─────────┼─────────┼─────────┤
    //  PAGE DOWN│         │         │         │         │         │
    //           │    4    │    5    │    6    │    *    │         │
    //  ROTARY   │         │         │         │         │         │
    //  LEFT:    ├─────────┼─────────┼─────────┼─────────┼─────────┤
    //  PAGE UP  │         │         │         │         │         │
    //           │    1    │    2    │    3    │         │         │
    //           │         │         │         │         │         │
    // ┌─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
    // │         │         │         │         │         │         │
    // │         │    0    │    .    │    =    │         │         │
    // │         │         │         │         │         │         │
    // └─────────┴─────────┴─────────┴─────────┴─────────┴─────────┘

    [_ADMIN] = LAYOUT(
                 QK_BOOT,   _______, _______, _______, TG(_ADMIN),
                 _______, _______, _______, _______, _______,
                 _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______
    ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    return true;
};

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) { /* First encoder */
        if (clockwise) {
            tap_code(KC_PGDN);
        } else {
            tap_code(KC_PGUP);
        }
    }
    return true;
}
