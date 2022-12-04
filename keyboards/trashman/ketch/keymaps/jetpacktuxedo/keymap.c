/* 
Copyright 2021 Evan Sailer, Jetpacktuxedo, & QMK Firmware

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to
deal in the Software without restriction, including without limitation the
rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
sell copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include QMK_KEYBOARD_H
#include <config.h>

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_jetvan( /* Qwerty */
        KC_GESC,       KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,   KC_I,    KC_O,    KC_P,    KC_BSPC,
        LT(2, KC_TAB), KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,   KC_K,    KC_L,    KC_SCLN, LT(2, KC_ENT),
        KC_LSFT,       KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,   KC_COMM, KC_DOT,  KC_UP,   MT(MOD_RSFT, KC_SLSH),
        KC_LCTL,       KC_LGUI, KC_LALT,                   LT(1, KC_SPC),                     KC_LEFT, KC_DOWN, KC_RIGHT
    ),
    [1] = LAYOUT_jetvan( /* LAYER 1 */
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL,
        KC_TRNS, KC_MINS, KC_EQL,  KC_SCLN, KC_QUOT, KC_TRNS, KC_TRNS, KC_TRNS, KC_MINS, KC_EQL,  KC_QUOT, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_LBRC, KC_RBRC, KC_PGUP, KC_BSLS,
        KC_TRNS, KC_TRNS, KC_TRNS,                            KC_TRNS,                   KC_HOME, KC_PGDN, KC_END
    ),
    [2] = LAYOUT_jetvan( /* LAYER 2 */
        KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_DEL,
        KC_TRNS, KC_UNDS, KC_PLUS, KC_COLN, KC_DQUO, KC_TRNS, KC_TRNS, KC_TRNS, KC_UNDS, KC_PLUS, KC_DQUO, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_LCBR, KC_RCBR, KC_PGUP, KC_PIPE,
        KC_TRNS, TG(4),   MO(3),                              KC_TRNS,                   KC_HOME, KC_PGDN, KC_END
    ),
    [3] = LAYOUT_jetvan( /* LAYER 3 */
        KC_TRNS, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_F11,  KC_F12,  KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS,   KC_TRNS,                          KC_TRNS,                   KC_TRNS, KC_TRNS, KC_TRNS
    ),
    [4] = LAYOUT_jetvan( /* Gaming Layer*/
        KC_ESC,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_WH_U, KC_BTN1, KC_MS_U, KC_BTN2, KC_TRNS, KC_TRNS,
        KC_TAB,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_WH_D, KC_MS_L, KC_MS_D, KC_MS_R, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, LT(5, KC_SLSH),
        KC_TRNS, KC_TRNS, KC_TRNS,                             KC_TRNS,                   KC_TRNS, KC_TRNS, KC_TRNS
    ),
    [5] = LAYOUT_jetvan( /* QK_BOOT Layer*/
        QK_BOOT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS,                             KC_TRNS,                   KC_TRNS, KC_TRNS, KC_TRNS
    )
};

const rgblight_segment_t PROGMEM layer1[] = RGBLIGHT_LAYER_SEGMENTS(
    {9, 1, HSV_RED}
);

const rgblight_segment_t PROGMEM layer2[] = RGBLIGHT_LAYER_SEGMENTS(
    {9, 1, HSV_GREEN}
);

const rgblight_segment_t PROGMEM layer3[] = RGBLIGHT_LAYER_SEGMENTS(
    {8, 1, HSV_CYAN}
);

const rgblight_segment_t PROGMEM layer4[] = RGBLIGHT_LAYER_SEGMENTS(
    {8, 1, HSV_MAGENTA}
);

const rgblight_segment_t PROGMEM layer5[] = RGBLIGHT_LAYER_SEGMENTS(
    {8, 1, HSV_YELLOW}
);

const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    layer1,
    layer2,
    layer3,
    layer4,
    layer5
);

layer_state_t layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(0, layer_state_cmp(state, 1));
    rgblight_set_layer_state(1, layer_state_cmp(state, 2));
    rgblight_set_layer_state(2, layer_state_cmp(state, 3));
    rgblight_set_layer_state(3, layer_state_cmp(state, 4));
    rgblight_set_layer_state(4, layer_state_cmp(state, 5));
    return state;
}

void keyboard_post_init_user(void) {
    #ifdef RGBLIGHT_ENABLE
        // Litearlly just doing this to lower the brightness. Since I am about to
        // turn on the rainbow effect which changes the hue I don't actually care
        // what that gets set to, but I am also lowering the saturation to get more
        // of a pastel feel
        rgblight_sethsv_noeeprom(0, 192, 128);
        // Set LED effects to rainbow
        rgblight_mode_noeeprom(RGBLIGHT_MODE_RAINBOW_SWIRL);
        rgblight_layers = my_rgb_layers;
    #endif //RGBLIGHT_ENABLE
}
