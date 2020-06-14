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
     * | TO(23)| TO(24)| TO(25)| TO(26)|     TRNS      | TO(27)| TO(28)| TO(29)| TO(30)| TO(31)|
     * |---------------------------------------------------------------------------------------|
     */
  [1] = LAYOUT(
    TO(2),  TO(3),  TO(4),  TO(5),//TO(6),  TO(7),   TO(8),  TO(9),  TO(10), TO(11), TO(12),
                                    KC_NO,  KC_NO,   KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,
  //TO(13), TO(14), TO(15), TO(16), TO(17), TO(18),  TO(19), TO(20), TO(21), TO(22), _______,
    KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,   KC_NO,  KC_NO,  KC_NO,  KC_NO,  _______,
  //TO(23), TO(24), TO(25), TO(26),         _______, TO(27), TO(28), TO(29), TO(30), TO(31)
    KC_NO,  KC_NO,  KC_NO,  KC_NO,          _______, KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO
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
    KC_ESC,        KC_7, KC_8, KC_9, KC_SLSH, KC_ASTR, KC_DOT,  KC_COMM, KC_LPRN, KC_RPRN, KC_DEL,
    KC_TAB,        KC_4, KC_5, KC_6, KC_MINS, KC_PLUS, KC_HOME, KC_UP,   KC_END,  KC_PGUP, TG(2),
    OSM(MOD_LALT), KC_1, KC_2, KC_3, KC_0,             KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, KC_RSFT
  ),
  /* Level 3: Symbols Layer
     * ,---------------------------------------------------------------------------------------.
     * |   !   |   @   |   #   |   $   |   %   |   ^   |   &   |   *   |   -   |   +   |   =   |
     * |---------------------------------------------------------------------------------------|
     * |   {   |   }   |   [   |   ]   |   '   |  TRNS |   \   |   ;   |   :   |   `   | TG(3) |
     * |---------------------------------------------------------------------------------------|
     * |  LSFT |  LCTL |   L   |   T   |      TAB      |   N   |  TRNS |  TRNS |  RCTL |   ?   |
     * |---------------------------------------------------------------------------------------|
     */
  [3] = LAYOUT(
    KC_EXLM, KC_AT,         KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_MINS, KC_PLUS,       KC_EQL,
    KC_LCBR, KC_RCBR,       KC_LBRC, KC_RBRC, KC_QUOT, _______, KC_BSLS, KC_SCLN, KC_COLN, KC_GRV,        TG(3),
    KC_LSFT, OSM(MOD_LCTL), KC_L,    KC_T,             KC_TAB,  KC_N,    _______, _______, OSM(MOD_RCTL), KC_QUES
  ),
  /* Level 4: F-keys and Media Layer
     * ,---------------------------------------------------------------------------------------.
     * | RESET |  MUTE |  VOLU |  MPLY |  TRNS |   F1  |   F2  |   F3  |   F4  |   F5  |   F6  |
     * |---------------------------------------------------------------------------------------|
     * |  LGUI |  MPRV |  VOLD |  MNXT |  TRNS |  TRNS |  TRNS |  TRNS |  TRNS |  TRNS | TG(4) |
     * |---------------------------------------------------------------------------------------|
     * |  TRNS |  TRNS |  TRNS |  TRNS |       F7      |   F8  |   F9  |  F10  |  F11  |  F12  |
     * |---------------------------------------------------------------------------------------|
     */
  [4] = LAYOUT(
    RESET,         KC_MUTE, KC_VOLU, KC_MPLY, _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,
    OSM(MOD_LGUI), KC_MPRV, KC_VOLD, KC_MNXT, _______, _______, _______, _______, _______, _______, TG(4),
    _______,       _______, _______, _______,          KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12
  ),
  /* Level 5: Commands Layer
     * ,---------------------------------------------------------------------------------------.
     * |  CUT  |  PSCR |  BRIU |  PWR  |  TRNS |  TRNS |  TRNS |  TRNS |  TRNS |  TRNS |  TRNS |
     * |---------------------------------------------------------------------------------------|
     * |  COPY |  FIND |  BRID |  SLEP |  TRNS |  TRNS |  TRNS |  TRNS |  TRNS |  TRNS | TG(5) |
     * |---------------------------------------------------------------------------------------|
     * |  PSTE |  TRNS |  TRNS |  WAKE |      TRNS     |  TRNS |  TRNS |  TRNS |  TRNS |  TRNS |
     * |---------------------------------------------------------------------------------------|
     */
  [5] = LAYOUT(
    KC_CUT,  KC_PSCR, KC_BRIU, KC_PWR, _______, _______, _______, _______, _______, _______, _______,
    KC_COPY, KC_FIND, KC_BRID, KC_SLEP, _______, _______, _______, _______, _______, _______, TG(5),
    KC_PSTE, _______, _______, KC_WAKE,          _______, _______, _______, _______, _______, _______
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

// Now define the array of layers. Later layers take precedence
const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    my_layer0_layer,
    my_layer1_layer,
    my_layer2_layer,
    my_layer3_layer,
    my_layer4_layer,
    my_layer5_layer
);

void keyboard_post_init_user(void) {
    // Enable the LED layers
    rgblight_layers = my_rgb_layers;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(0, layer_state_cmp(state, 0));
    rgblight_set_layer_state(1, layer_state_cmp(state, 1));
    rgblight_set_layer_state(2, layer_state_cmp(state, 2));
    rgblight_set_layer_state(3, layer_state_cmp(state, 3));
    rgblight_set_layer_state(4, layer_state_cmp(state, 4));
    rgblight_set_layer_state(5, layer_state_cmp(state, 5));
    return state;
}
