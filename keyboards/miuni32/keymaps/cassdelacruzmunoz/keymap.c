/* Copyright 2020 Cassandra de la Cruz-Munoz cassandra.delacruzmunoz@gmaill.com @cassdelacruzmunoz
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
* along with this program.  If not, see <http://www.gnu.org/licenses/>
*/

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Level 0: Default Layer
     * ,---------------------------------------------------------------------------------------.
     * |   Q   |   W   |   E   |   R   |   T   |   Y   |   U   |   I   |   O   |   P   |  BSP  |
     * |---------------------------------------------------------------------------------------|
     * |   A   |   S   |   D   |   F   |   G   |   H   |   J   |   K   |   L   |  ENT  |LT(1|,)|
     * |---------------------------------------------------------------------------------------|
     * |   Z   |   X   |   C   |   V   |      SPC      |   B   |   N   |   M   |  RSFT |   .   |
     * |---------------------------------------------------------------------------------------|
     */
  [0] = LAYOUT(
    KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y,   KC_U, KC_I, KC_O, KC_P,    KC_BSPC,
    KC_A, KC_S, KC_D, KC_F, KC_G, KC_H,   KC_J, KC_K, KC_L, KC_ENT,  LT(1, KC_COMMA),
    KC_Z, KC_X, KC_C, KC_V,       KC_SPC, KC_B, KC_N, KC_M, KC_RSFT, KC_DOT
    ),
    /* Level 1: Layers Layer
     * ,---------------------------------------------------------------------------------------.
     * | TO(2) | TO(3) | TO(4) | TO(5) | TO(6) | TO(7) | TO(8) | TO(9) | TO(10)| TO(11)| TO(12)|
     * |---------------------------------------------------------------------------------------|
     * | TO(13)| TO(14)| TO(15)| TO(16)| TO(17)| TO(18)| TO(19)| TO(20)| TO(21)| TO(22)|  TRNS |
     * |---------------------------------------------------------------------------------------|
     * | TO(23)| TO(24)| TO(25)| TO(26)|               | TO(27)| TO(28)| TO(29)| TO(30)| TO(31)|
     * |---------------------------------------------------------------------------------------|
     */
  [1] = LAYOUT(
    TO(2),  TO(3),  TO(4),  TO(5),  TO(6),//TO(7),  TO(8),  TO(9),  TO(10), TO(11), TO(12),
                                            KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,
  //TO(13), TO(14), TO(15), TO(16), TO(17), TO(18), TO(19), TO(20), TO(21), TO(22), _______,
    KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  _______,
  //TO(23), TO(24), TO(25), TO(26),         KC_NO,  TO(27), TO(28), TO(29), TO(30), TO(31)
    KC_NO,  KC_NO,  KC_NO,  KC_NO,          KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO
  ),
  /* Level 2: Numbers Layer
     * ,---------------------------------------------------------------------------------------.
     * |  ESC  |   7   |   8   |   9   |   /   |   *   |   .   |   ,   |   (   |   )   |  DEL  |
     * |---------------------------------------------------------------------------------------|
     * |  TAB  |   4   |   5   |   6   |   -   |   +   |  HOME |   UP  |  END  |  PGUP | TG(2) |
     * |---------------------------------------------------------------------------------------|
     * |  LALT |   1   |   2   |   3   |   0           |  LEFT |  DOWN |  RGHT |  PGDN | RSHFT |
     * |---------------------------------------------------------------------------------------|
     */
  [2] = LAYOUT(
    KC_ESC,  KC_7, KC_8, KC_9, KC_SLSH, KC_ASTR, KC_DOT,  KC_COMM, KC_LPRN, KC_RPRN, KC_DEL,
    KC_TAB,  KC_4, KC_5, KC_6, KC_MINS, KC_PLUS, KC_HOME, KC_UP,   KC_END,  KC_PGUP, TG(2),
    KC_LALT, KC_1, KC_2, KC_3, KC_0,             KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, KC_RSFT
  ),
  /* Level 3: Symbols Layer
     * ,---------------------------------------------------------------------------------------.
     * |   !   |   @   |   #   |   $   |   %   |   ^   |   &   |   *   |   -   |   +   |   =   |
     * |---------------------------------------------------------------------------------------|
     * |   {   |   }   |   [   |   ]   |   '   |       |   \   |   ;   |   :   |   `   | TG(3) |
     * |---------------------------------------------------------------------------------------|
     * |  LSFT |  LCTL |       |       |      TAB      |       |       |       |  RCTL |   ?   |
     * |---------------------------------------------------------------------------------------|
     */
  [3] = LAYOUT(
    KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_MINS, KC_PLUS, KC_EQL,
    KC_LCBR, KC_RCBR, KC_LBRC, KC_RBRC, KC_QUOT, KC_NO,   KC_BSLS, KC_SCLN, KC_COLN, KC_GRV,  TG(3),
    KC_LSFT, KC_LCTL, KC_NO,   KC_NO,            KC_TAB,  KC_NO,   KC_NO,   KC_NO,   KC_RCTL, KC_QUES
  ),
  /* Level 4: F-keys and Media Layer
     * ,---------------------------------------------------------------------------------------.
     * | QK_BOOT |  MUTE |  VOLU |  MPLY |  TRNS |   F1  |   F2  |   F3  |   F4  |   F5  |   F6  |
     * |---------------------------------------------------------------------------------------|
     * |  LGUI |  MPRV |  VOLD |  MNXT |  TRNS |  TRNS |  TRNS |  TRNS |  TRNS |  TRNS | TG(4) |
     * |---------------------------------------------------------------------------------------|
     * |  TRNS |  TRNS |  TRNS |  TRNS |       F7      |   F8  |   F9  |  F10  |  F11  |  F12  |
     * |---------------------------------------------------------------------------------------|
     */
  [4] = LAYOUT(
    QK_BOOT, KC_MUTE, KC_VOLU, KC_MPLY, KC_NO, KC_F1, KC_F2, KC_F3, KC_F4,  KC_F5,  KC_F6,
    KC_LGUI, KC_MPRV, KC_VOLD, KC_MNXT, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,  KC_NO,  TG(4),
    KC_NO,   KC_NO,   KC_NO,   KC_NO,          KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12
  ),
  /* Level 5: Commands Layer
     * ,---------------------------------------------------------------------------------------.
     * |  CUT  |  PSCR |  BRIU |  PWR  |       |       |       |       |       |       |       |
     * |---------------------------------------------------------------------------------------|
     * |  COPY |  FIND |  BRID |  SLEP |       |       |       |       |       |       | TG(5) |
     * |---------------------------------------------------------------------------------------|
     * |  PSTE |       |       |  WAKE |               |       |       |       |       |       |
     * |---------------------------------------------------------------------------------------|
     */
  [5] = LAYOUT(
    KC_CUT,  KC_PSCR, KC_BRIU, KC_PWR,  KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
    KC_COPY, KC_FIND, KC_BRID, KC_SLEP, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, TG(5),
    KC_PSTE, KC_NO,   KC_NO,   KC_WAKE,        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO
  ),
  /* Level 6: MIDI Layer
     * ,---------------------------------------------------------------------------------------.
     * |   C1  |   E1  |   G1  |   B1  |   D2  |   F2  |   A2  |   C3  |   E3  |   G3  |       |
     * |---------------------------------------------------------------------------------------|
     * |   D1  |   F1  |   A1  |   C2  |   E2  |   G2  |   B2  |   D3  |   F3  |   A3  | TG(6) |
     * |---------------------------------------------------------------------------------------|
     * |  OCTD |  OCTU | TRNSD | TRNSU |               |       |       |       |       |       |
     * |---------------------------------------------------------------------------------------|
     */
  [6] = LAYOUT(
    MI_C_1,  MI_E_1,  MI_G_1,   MI_B_1,   MI_D_2,  MI_F_2, MI_A_2, MI_C_3, MI_E_3, MI_G_3, KC_NO,
    MI_D_1,  MI_F_1,  MI_A_1,   MI_C_2,   MI_E_2,  MI_G_2, MI_B_2, MI_D_3, MI_F_3, MI_A_3, TG(6),
    MI_OCTD, MI_OCTU, MI_TRNSD, MI_TRNSU,          KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO
  )
};

// Light LEDs 0 through 16 in white when keyboard layer 0 is active
const rgblight_segment_t PROGMEM my_layer0_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 17, HSV_WHITE}
);
// Light LEDs 0 through 16 in blue when keyboard layer 1 is active
const rgblight_segment_t PROGMEM my_layer1_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 17, HSV_BLUE}
);
// Light LEDs 0 through 16 in green when keyboard layer 2 is active
const rgblight_segment_t PROGMEM my_layer2_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 17, HSV_GREEN}
);
// Light LEDs 0 through 16 in yellow when keyboard layer 3 is active
const rgblight_segment_t PROGMEM my_layer3_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 17, HSV_YELLOW}
);
// Light LEDs 0 through 16 in red when keyboard layer 4 is active
const rgblight_segment_t PROGMEM my_layer4_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 17, HSV_RED}
);
// Light LEDs 0 through 16 in cyan when keyboard layer 5 is active
const rgblight_segment_t PROGMEM my_layer5_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 17, HSV_CYAN}
);
// Light LEDs 0 through 16 in orange when keyboard layer 6 is active
const rgblight_segment_t PROGMEM my_layer6_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 17, HSV_ORANGE}
);

// Now define the array of layers. Later layers take precedence
const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    my_layer0_layer,
    my_layer1_layer,
    my_layer2_layer,
    my_layer3_layer,
    my_layer4_layer,
    my_layer5_layer,
    my_layer6_layer
);

void keyboard_post_init_user(void) {
    // Enable the LED layers
    rgblight_layers = my_rgb_layers;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    for (int i = 0; i < 7; i++) {
        rgblight_set_layer_state(i, layer_state_cmp(state, i));
    }
    return state;
}
