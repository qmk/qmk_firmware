/* Copyright 2022 filmstarr <https://github.com/filmstarr>
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

enum layer_names {
    _LAY0,
    _LAY1
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
       L0:
       ┌───┬───┬───┬───┐   ┌───┐
       │MO1│Prv│Ply│Nxt│   │Mut│
       └───┴───┴───┴───┘   └───┘
       L1:
       ┌───┬───┬───┬───┐   ┌───┐
       │   │Hud│Tog│Mod│   │   │
       └───┴───┴───┴───┘   └───┘
*/
    [_LAY0] = LAYOUT(
        MO(_LAY1),   KC_MPRV,    KC_MPLY,    KC_MNXT,     KC_MUTE
    ),
    [_LAY1] = LAYOUT(
        KC_TRNS,     RM_HUED,    RM_TOGG,    RM_NEXT,     KC_TRNS
    )
};

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_LAY0] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [_LAY1] = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS) }
};
#endif
