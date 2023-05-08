/*
Copyright 2022 oco9oco <oco9oco@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "oco9oco.h" //look for users/oco9oco/

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
//clang-format off

[_BASE] = LAYOUT_kimiko_wrapper(
// |--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|
    KC_ESC,  __________________NUMROW_L_________________,                            __________________NUMROW_R_________________, KC_MINS,
    S(KC_GRV),  __________________QWERTY_L1________________,                            __________________QWERTY_R1________________, KC_EQL,
    SFT_CAPS,__________________QWERTY_SACS_L2___________,                            __________________QWERTY_R2________________, RSFT_T(KC_QUOT),
    KC_LSFT, __________________QWERTY_GUIZ_L3___________, KC_DEL,  KC_B,    __________________QWERTY_HOME_R3___________, RSFT_T(KC_BSLS),
// |--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|
                      TG(_ONEHAND), TG(_BASE_NOMOD), THUMB_L3,THUMB_L1,THUMB_L2,         THUMB_R3,THUMB_R2,THUMB_R1, KC_LNG2, TG(_ONEHAND)
),

[_BASE_NOMOD] = LAYOUT_kimiko_wrapper(
// |--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|
    KC_ESC,  __________________NUMROW_L_________________,                            __________________NUMROW_R_________________, _______,
    KC_TAB,  __________________QWERTY_L1________________,                            __________________QWERTY_R1________________, _______,
    SFT_CAPS,__________________QWERTY_L2_SFTA___________,                            __________________QWERTY_R2________________, _______,
    KC_LSFT, __________________QWERTY_L3________________, _______,          KC_B,    __________________QWERTY_HOME_R3___________, _______,
// |--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|
                      _______, _______, THUMB_L3,THUMB_L1,THUMB_L2,         _______, _______, _______, _______, _______
),

[_IPC] = LAYOUT_kimiko_wrapper(
// |--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|
    _______, PDF_HL,  KC_P,    KC_X,    ALT_F4,  XXXXXXX,                            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
    _______, XXXXXXX, XXXXXXX, CLASS_E, CLASS_A, KC_SLSH,                            KC_GRV,  _________NUM_789_________, KC_RBRC, _______,
    _______, IPC(A),  IPC(S),  IPC_MIN, IPC(F), KC_DOT,                             XXXXXXX, _________NUM_456_________, KC_COLN,  KC_DQUO,
    _______, IPC(Z),  HWP_CITE,IPC(C),  KC_EQL,  KC_BSLS, XXXXXXX,          KC_LBRC, KC_RBRC, _________NUM_123_________, _______, KC_PIPE,
// |--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|
                      KC_WH_U, KC_WH_D, _______, _______, _______,          _______, LT(_NAV, KC_0), _______, KC_LPRN, KC_RPRN
),

// [_NUM] = LAYOUT_kimiko_wrapper(
// // |--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|
//     TO_BASE, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
//     _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                            XXXXXXX, C(KC_7), C(KC_8), C(KC_9), XXXXXXX, XXXXXXX,
//     _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                            XXXXXXX, C(KC_4), C(KC_5), C(KC_6), XXXXXXX, XXXXXXX,
//     _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, TO_BASE,          TO_BASE, XXXXXXX, C(KC_1), C(KC_2), C(KC_3), XXXXXXX, XXXXXXX,
// // |--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|
//                       KC_TRNS, KC_TRNS, _______, _______, _______,          ENT_HOME, C(KC_0), C(KC_0), KC_LPRN, KC_RPRN
// ),

[_NAV] = LAYOUT_kimiko_wrapper(
// |--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|
    _______, CTRL_F1, KC_F2,   KC_F3,   ALT_F4,   KC_F5,                             XXXXXXX, A(KC_7), A(KC_8), A(KC_9), A(KC_0), XXXXXXX,
    _______, LCA(KC_H),LCA(KC_J),LCA(KC_K),LCA(KC_L), KC_F6,                         XXXXXXX, A(KC_4), A(KC_5), A(KC_6), XXXXXXX, XXXXXXX,
    _______, XXXXXXX, KC_LALT, KC_LCTL, KC_LSFT,  KC_F7,                             KC_INS,  KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, XXXXXXX,
    _______, NAV(Z), C(KC_X), C(KC_C), C(KC_V), C(KC_B), TO(_ONEHAND),      XXXXXXX, KC_APP,  KC_HOME, KC_PGDN, KC_PGUP, KC_END,  XXXXXXX,
// |--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|
                      _______, _______, _______, KC_BSPC, KC_DEL,           _______, KC_TRNS, _______, _______, _______
),

[_MOUSE] = LAYOUT_kimiko_wrapper(
// |--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|
    _______, CTRL_F1, KC_F2,   KC_F3,   ALT_F4,  KC_F5,                              KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,   QK_BOOT,
    KC_U,    XXXXXXX, KC_WH_D, KC_MS_U, KC_WH_U, KC_F6,                            XXXXXXX,  KC_ACL2, XXXXXXX, XXXXXXX, XXXXXXX, QK_MAKE,
    KC_P,    KC_LSFT, KC_MS_L, KC_MS_D, KC_MS_R, KC_F7,                            XXXXXXX,  KC_ACL0, KC_BTN1, KC_BTN2, KC_BTN3, KC_ENT,
    KC_X,    KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, BOLDFACE,TO_BASE,          XXXXXXX, KC_APP,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, XXXXXXX,
// |--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|
                      _______, _______, KC_LCTL, KC_SPC,  KC_ENT,           KC_TRNS, _______, _______, _______, _______
),

[_FUNC] = LAYOUT_kimiko_wrapper(
// |--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|
    _______, RGB_TOG, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI, XXXXXXX,                            KC_F12, KC_F7,   KC_F8,  KC_F9,    XXXXXXX,  XXXXXXX,
    XXXXXXX, KC_LSFT, KC_LALT, KC_LCTL, KC_LSFT, XXXXXXX,                            KC_F11, KC_F4,   KC_F5,   KC_F6,   XXXXXXX,   XXXXXXX,
    XXXXXXX, KC_LGUI, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX, KC_F10, KC_F1,   KC_F2,   KC_F3,   XXXXXXX,   XXXXXXX,
// |--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|
                      _______, _______, _______, _______, _______,          _______, _______, KC_TRNS, KC_GT, KC_LT
),

[_ONEHAND] = LAYOUT_kimiko_wrapper(
// |--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|
    KC_ESC,  C(KC_F1),KC_WH_U, XXXXXXX, A(KC_F4),XXXXXXX,                            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    KC_TAB,  XXXXXXX, KC_WH_D, KC_UP,   KC_BTN1, KC_BTN2,                            XXXXXXX, XXXXXXX, KC_MS_U, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, KC_LSFT, KC_LEFT, KC_DOWN, KC_RGHT, KC_BSPC,                            XXXXXXX, KC_MS_L, KC_MS_D, KC_MS_R, XXXXXXX, XXXXXXX,
    _______, XXXXXXX, XXXXXXX, KC_WH_U, KC_WH_D, KC_DEL,  TO_BASE,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
// |--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|
                      KC_LGUI, KC_LALT, KC_LCTL, KC_SPC,  KC_ENT,           _______, _______, _______, _______, _______
),

[_SETTINGS] = LAYOUT(
//|-------------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|
   _______,     C(KC_WH_D), XXXXXXX, A(KC_0), A(KC_F4),XXXXXXX,                     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, QK_BOOT,
   KC_TAB,/*|*/ C(KC_WH_U), A(KC_4), A(KC_5), A(KC_6), KC_X,                        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
   KC_ENT,/*|*/ SCRNSHOT,A(KC_1), A(KC_2), A(KC_3), PDF_HL,                         RGB_TOG, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
   KC_SPC,/*|*/ XXXXXXX, A(KC_7), A(KC_8), A(KC_9), KC_P, TO_BASE,         TO_BASE, RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI, KC_LSFT, XXXXXXX,
//|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|
                     _______, KC_LALT, _______, _______, KC_TRNS,          _______, _______, _______, KC_GT, KC_LT
)

};


//clang-format on
//keyboard-specific process
// COMBOS
enum combos {
    COMBO_ONEHAND,
    COMBO_ONEHAND_END,
    COMBO_LENGTH
};
uint16_t COMBO_LEN = COMBO_LENGTH;
const uint16_t PROGMEM onehand_combo[]      = {KC_W, KC_E, COMBO_END};
const uint16_t PROGMEM onehand_end_combo[]  = {KC_BTN2, KC_UP, COMBO_END};
// const uint16_t PROGMEM shift_T[] = {KC_A, KC_T, COMBO_END};

combo_t key_combos[] = {
    [COMBO_ONEHAND]     = COMBO(onehand_combo, TO(_ONEHAND)),
    [COMBO_ONEHAND_END] = COMBO(onehand_end_combo,TO(_BASE)),
    // [SHIFT_T]   = COMBO(shift_T,S(KC_T)),
};
// COMBO_TERM

// Key overrides
const key_override_t DLR_0_override     = ko_make_basic(MOD_MASK_SHIFT, KC_DLR, KC_0);
const key_override_t DEL_override       = ko_make_basic(MOD_MASK_SHIFT, KC_DEL, KC_BSPC);

const key_override_t **key_overrides = (const key_override_t *[]){                              // This globally defines all key overrides to be used
    &DLR_0_override,
    &DEL_override,
    NULL                                                                                        // Null terminate the array of overrides!
 };

// //RGBLIGHT LAYERS
// // Light LEDs 6 to 9 and 12 to 15 red when caps lock is active. Hard to ignore!
// const rgblight_segment_t PROGMEM my_capslock_layer[] = RGBLIGHT_LAYER_SEGMENTS(
//     {6, 4, HSV_RED},       // Light 4 LEDs, starting with LED 6
//     {12, 4, HSV_RED}       // Light 4 LEDs, starting with LED 12
// );
// // Light LEDs 9 & 10 in cyan when keyboard layer 1 is active
// const rgblight_segment_t PROGMEM my_layer1_layer[] = RGBLIGHT_LAYER_SEGMENTS(
//     {9, 2, HSV_OFF}
// );
// // Light LEDs 11 & 12 in purple when keyboard layer 2 is active
// const rgblight_segment_t PROGMEM my_layer2_layer[] = RGBLIGHT_LAYER_SEGMENTS(
//     {11, 2, HSV_PURPLE}
// );
// // Light LEDs 13 & 14 in green when keyboard layer 3 is active
// const rgblight_segment_t PROGMEM my_layer3_layer[] = RGBLIGHT_LAYER_SEGMENTS(
//     {13, 2, HSV_GREEN}
// );
// // Now define the array of layers. Later layers take precedence
// const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
//     my_capslock_layer,
//     my_layer1_layer,    // Overrides caps lock layer
//     my_layer2_layer,    // Overrides other layers
//     my_layer3_layer     // Overrides other layers
// );

// void keyboard_post_init_user(void) {
//     // Enable the LED layers
//     rgblight_layers = my_rgb_layers;
// }


// bool led_update_user(led_t led_state) {
//     rgblight_set_layer_state(0, led_state.caps_lock);
//     return true;
// }

// layer_state_t default_layer_state_set_user(layer_state_t state) {
//     rgblight_set_layer_state(1, layer_state_cmp(state, _BASE));
//     return state;
// }

// layer_state_t layer_state_set_user(layer_state_t state) {
//     rgblight_set_layer_state(2, layer_state_cmp(state, _BASE_NOMOD));
//     rgblight_set_layer_state(3, layer_state_cmp(state, _ONEHAND));
//     return state;

