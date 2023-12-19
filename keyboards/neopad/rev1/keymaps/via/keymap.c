/* Copyright 2021 rookiebwoy
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

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* LAYER 0
     * ,-----------------------------.
     * |  TO(1)  |   up    |   mute  |	L ENC: brightness up/down
     * |---------+---------+---------|
     * |   left  |  down   |  right  |	R ENC: volume up/down
     * `-----------------------------'
     */
    [0] = LAYOUT(
                TO(1),     KC_UP,    KC_MUTE,
    		    KC_LEFT,   KC_DOWN,  KC_RIGHT
    ),

    /* LAYER 1
     * ,---------------------------------------.
     * |    TO(2)    | maximize | show desktop | L ENC: page up/down
     * |-------------+----------+--------------|
     * | move window | minimize | move window  | R ENC: mouse wheel up/down
     * `---------------------------------------'
     */
    [1] = LAYOUT(
				TO(2),     		LGUI(KC_UP),    LGUI(KC_D),
				LGUI(KC_LEFT),	LGUI(KC_DOWN),  LGUI(KC_RIGHT)
    ),

    /* LAYER 2
     * ,------------------------------.
     * |  TO(3)  |   esc   | sel all  | L ENC: redo/undo
     * |---------+---------+----------|
     * |   cut   |   copy  |   paste  | R ENC: forward/backward one word
     * `------------------------------'
     */
    [2] = LAYOUT(
                TO(3),     		KC_ESC,    		LCTL(KC_A),
    		    LCTL(KC_X),		LCTL(KC_C),     LCTL(KC_V)
    ),

    /* LAYER 3
     * ,-----------------------------.
     * |  TO(0)  |    W    |    E    |	L ENC: pan right/left
     * |---------+---------+---------|
     * |    A    |    S    |    D    |	R ENC: mouse wheel up/down
     * `-----------------------------'
     */
    [3] = LAYOUT(
                TO(0),   KC_W,    KC_E,
    		    KC_A,	 KC_S,    KC_D
    ),

};

#if defined(ENCODER_MAP_ENABLE)
// { LEFT ENCODER, RIGHT ENCODER }
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] = { ENCODER_CCW_CW(KC_BRIGHTNESS_DOWN, KC_BRIGHTNESS_UP),   ENCODER_CCW_CW(KC_AUDIO_VOL_DOWN, KC_AUDIO_VOL_UP)  },
    [1] = { ENCODER_CCW_CW(KC_PAGE_DOWN, KC_PAGE_UP),               ENCODER_CCW_CW(KC_WH_D, KC_WH_U)                    },
    [2] = { ENCODER_CCW_CW(LCTL(KC_Z), LCTL(KC_Y)),                 ENCODER_CCW_CW(LCTL(KC_LEFT), LCTL(KC_RIGHT))       },
    [3] = { ENCODER_CCW_CW(KC_WH_L, KC_WH_R),                       ENCODER_CCW_CW(KC_WH_D, KC_WH_U)                    },
};
#endif
