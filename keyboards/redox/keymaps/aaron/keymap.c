#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[0] = LAYOUT(QK_GESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_BSPC, KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_HOME, RGB_M_K, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSLS, CW_TOGG, KC_A, KC_S, KC_D, KC_F, KC_G, LT(3,KC_DEL), LT(3,KC_APP), KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_ENT, OSM(MOD_LSFT), KC_Z, KC_X, KC_C, KC_V, KC_B, KC_LBRC, KC_RBRC, KC_MINS, KC_EQL, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, RSFT(KC_QUOT), OSM(MOD_LCTL), OSM(MOD_LGUI), LCTL(KC_C), LSFT(KC_V), LALT_T(KC_F23), LT(2,KC_ENT), LT(1,KC_BSPC), LT(1,KC_DEL), LT(2,KC_SPC), ALL_T(KC_F24), KC_LEFT, KC_DOWN, KC_UP, KC_RGHT),
	[1] = LAYOUT(KC_GRV, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_TRNS, KC_TAB, KC_PGUP, LALT(KC_UP), KC_UP, LALT(KC_DOWN), KC_PGDN, KC_F11, KC_F12, KC_LBRC, KC_RBRC, LCTL(KC_UP), KC_LPRN, KC_RPRN, KC_TRNS, KC_CAPS, KC_HOME, KC_LEFT, KC_DOWN, KC_RGHT, KC_END, LCTL(KC_SPC), KC_PSCR, RCS(KC_LEFT), LCTL(KC_LEFT), LCTL(KC_DOWN), LCTL(KC_RGHT), RCS(KC_RGHT), KC_TRNS, KC_LSFT, LSFT(KC_HOME), LSFT(KC_LEFT), LSFT(KC_DOWN), LSFT(KC_RGHT), LSFT(KC_END), LCTL(KC_LBRC), LCTL(KC_RBRC), KC_TRNS, KC_TRNS, KC_LCBR, KC_RCBR, KC_LT, KC_GT, KC_SLSH, KC_TRNS, KC_LCTL, KC_LGUI, LCTL(KC_X), RCS(KC_V), KC_LALT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, LCTL(KC_SLSH), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),
	[2] = LAYOUT(KC_TILD, KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC, LALT(KC_TAB), LCTL(KC_J), LCTL(KC_W), RCS(KC_T), RCS(KC_K), LCTL(KC_T), LCTL(KC_N), SGUI(KC_T), KC_NUM, KC_PSLS, KC_P7, KC_P8, KC_P9, KC_DEL, RCS(KC_S), LCTL(KC_H), LCTL(KC_9), RCS(KC_TAB), LCTL(KC_TAB), LCTL(KC_Z), RCS(KC_O), KC_CALC, RALT(KC_P1), KC_PAST, KC_P4, KC_P5, KC_P6, KC_ENT, LCTL(KC_0), LALT(KC_F), RCS(KC_DOT), RCS(KC_E), RCS(KC_A), LCTL(KC_F), LGUI(KC_1), LGUI(KC_2), LGUI(KC_3), LGUI(KC_4), RALT(KC_P5), KC_PMNS, KC_P1, KC_P2, KC_P3, KC_PPLS, LCTL(KC_MINS), LCTL(KC_EQL), LALT(KC_D), RCS(KC_L), LGUI(KC_DOT), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_P0, KC_PCMM, KC_PDOT, KC_PEQL),
	[3] = LAYOUT(KC_MPLY, KC_MSTP, KC_MUTE, KC_NO, KC_NO, LGUI(KC_L), RGB_MOD, RGB_SPI, RGB_HUI, RGB_SAI, RGB_VAI, RGB_TOG, KC_VOLU, KC_MNXT, KC_MFFD, KC_NO, KC_NO, LCA(KC_DEL), LAG(KC_K), LAG(KC_K), RGB_RMOD, RGB_SPD, RGB_HUD, RGB_SAD, RGB_VAD, RGB_M_K, KC_VOLD, KC_MPRV, KC_MRWD, KC_NO, KC_NO, RCS(KC_ESC), KC_TRNS, KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, RGB_M_SN, KC_NO, KC_NO, KC_NO, KC_NO, KC_SCRL, KC_PAUS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, RGB_M_B, CG_SWAP, CG_NORM, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, DB_TOGG, KC_NO, QK_BOOT, EE_CLR)
};

const uint8_t RGBLED_KNIGHT_INTERVALS[] PROGMEM = {150, 75, 8};

const rgblight_segment_t PROGMEM layer0[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 14, HSV_YELLOW}
);
const rgblight_segment_t PROGMEM layer1[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 14, HSV_WHITE}
);
const rgblight_segment_t PROGMEM layer2[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 14, HSV_CYAN}
);
const rgblight_segment_t PROGMEM layer3[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 14, HSV_PURPLE}
);
const rgblight_segment_t PROGMEM capslock[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 14, HSV_RED}
);
const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    layer0,
    layer1,
    layer2,
    layer3,
    capslock
);
void keyboard_post_init_user(void) {
    rgblight_layers = my_rgb_layers;
}
bool led_update_user(led_t led_state) {
    rgblight_set_layer_state(4, led_state.caps_lock);
    return true;
}
void caps_word_set_user(bool active) {
    rgblight_set_layer_state(4,active);
}
// layer_state_t default_layer_state_set_user(layer_state_t state) {
//     rgblight_set_layer_state(0, layer_state_cmp(state, 0));
//     return state;
// }
layer_state_t layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(0, layer_state_cmp(state, 0));
    rgblight_set_layer_state(1, layer_state_cmp(state, 1));
    rgblight_set_layer_state(2, layer_state_cmp(state, 2));
    rgblight_set_layer_state(3, layer_state_cmp(state, 3));
    return state;
}