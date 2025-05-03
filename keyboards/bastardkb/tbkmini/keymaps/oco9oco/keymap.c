#include "oco9oco.h" //look for users/oco9oco/
//clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_BASE] = LAYOUT_crkbd_wrapper(
// |--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|
    KC_ESC,  __________________QWERTY_L1________________,                            __________________QWERTY_R1________________, KC_LNG1,
    SFT_CAPS,__________________QWERTY_SACS_L2___________,                            __________________QWERTY_R2________________, KC_QUOT,
    KC_LGUI, __________________QWERTY_L3________________,                            __________________QWERTY_HOME_R3___________, KC_BSLS,
                                      THUMB_L1, THUMB_L2, THUMB_L3,        THUMB_R1, THUMB_R3, THUMB_R2
    ),
  [_BASE_SWAP] = LAYOUT_crkbd_wrapper(
// |--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|
    _______, __________________QWERTY_L1________________,                            __________________QWERTY_R1________________, _______,
    _______, __________________QWERTY_SACS_L2___________,                            __________________QWERTY_R2________________, _______,
    _______, __________________QWERTY_L3________________,                            __________________QWERTY_HOME_R3___________, _______,
                                        _______, _______, _______,         THUMB_R3, THUMB_R2, THUMB_R1
    ),

  [_BASE_NOMOD] = LAYOUT_crkbd_wrapper(
// |--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|
    KC_ESC,  __________________QWERTY_L1________________,                            __________________QWERTY_R1________________, _______,
    SFT_CAPS,__________________QWERTY_L2________________,                           __________________QWERTY_R2________________, KC_QUOT,
    _______, __________________QWERTY_L3________________,                            __________________QWERTY_HOME_R3___________, KC_BSLS,
                                        THUMB_L1, THUMB_L2, THUMB_L3,       TH_BK_R1, THUMB_R3, THUMB_R2
),
  [_DOOM] = LAYOUT_crkbd_wrapper(
// |--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|
    KC_ESC,  KC_ENT,   KC_Q,KC_W, KC_E, KC_R,                            TO(_BASE),XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX, TO(_BASE),
    KC_TAB,  KC_LSFT,KC_A, KC_S, KC_D, KC_G,                               XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX, XXXXXXX,
    XXXXXXX, KC_Z,   KC_X, KC_4, KC_V, KC_B,                               XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX, XXXXXXX,
                                        KC_F, KC_SPC, KC_C,       KC_ENT, THUMB_R3, THUMB_R2
),
  [_IPC] = LAYOUT_crkbd_wrapper(
// |--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|
    A(KC_F4),        C(KC_F1), SCRNSHOT, G(KC_E), CLASS_A, HWP_MACRO,                  KC_GRV,  _________NUM_789_________, _______, KC_PLUS,
    TO(_DOOM),         IPC(A),   IPC(S),   IPC_MIN, IPC(F), KC_DOT,                  AT_IPC,  _________NUM_456_________, KC_COLN, KC_DQUO,
    TO(_BASE_NOMOD), IPC(Z),   HWP_CITE, IPC(C),  KC_EQL,  KC_BSLS,                  XXXXXXX, _________NUM_123_________, _______, KC_PIPE,
                                        TO(_BASE_NOMOD), _______, TO(_BASE),   KC_LPRN, KC_RPRN, LT(_NAV,KC_0)
),
  [_NUM] = LAYOUT_crkbd_wrapper(
// |--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|
    _______, KC_P,    KC_O,    KC_I,    KC_U,    KC_Y,                               XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_EQL,
    _______, XXXXXXX, KC_L,    KC_K,    KC_J,    KC_H,                               XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_COLN, KC_DQUO,
    _______, XXXXXXX, XXXXXXX, XXXXXXX, KC_M,    KC_N,                               KC_B,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_PIPE,
                                        _______, _______, _______,          _______, _______, _______
    ),
  [_NAV] = LAYOUT_split_3x6_3(          //Navigations
// |--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|
    KC_ESC,  NAV_NS,  LCA(KC_J),LCA(KC_K),LCA(KC_L),KC_F5,                          A(KC_4), A(KC_7), A(KC_8), A(KC_4), A(S(KC_8)), S(KC_F8),
    ALT_TAB, KC_LGUI,  KC_LALT,  KC_LCTL,  KC_LSFT, KC_F6,                          KC_INS,  KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, XXXXXXX,
    _______, NAV(Z),  C(KC_X),  C(KC_C),  C(KC_V),  C(KC_B),                          KC_APP,  KC_HOME, KC_PGDN, KC_PGUP, KC_END,  XXXXXXX,
                                        KC_LNG1, KC_BSPC, KC_DEL,        _______, _______, _______
    ),
  [_FUNC] = LAYOUT_crkbd_wrapper(       //Functions
// |--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|
    XXXXXXX, C(KC_F1),KC_F2,   KC_F3,   A(KC_F4),KC_F5,                              _____________FUNC_2789____________, XXXXXXX, XXXXXXX,
    XXXXXXX, KC_LSFT, KC_LALT, KC_LCTL, KC_LSFT, KC_F6,                              _____________FUNC_1456____________, XXXXXXX, XXXXXXX,
    QK_COMBO_TOGGLE, KC_LGUI, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                            _____________FUNC_0123____________, XXXXXXX, XXXXXXX,
                                        _______, _______, _______,          _______, _______, _______
    ),
  [_MOUSE] = LAYOUT_split_3x6_3(       //Mouse keys
// |--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|
    A(KC_F4), C(KC_F1), KC_WH_D, KC_MS_U, KC_WH_U,   KC_F5,                         XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, QK_BOOT,
     KC_LNG1,  KC_LSFT, KC_MS_L, KC_MS_D, KC_MS_R,   KC_F6,                         XXXXXXX, KC_ACL0, KC_BTN1, KC_BTN2, KC_BTN3, QK_MAKE,
     KC_LNG2,  KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT,   KC_F7,                         XXXXXXX, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, XXXXXXX,
                                          KC_LCTL, KC_LNG1, KC_LSFT,       _______, _______, _______
    ),
  [_ONEHAND] = LAYOUT_split_3x6_3( //Trackball Manipulation
// |--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|
     KC_ESC, C(KC_F1),   KC_F2,   KC_F3,  ALT_F4, XXXXXXX,                            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, TO_BASE,
     KC_TAB,  KC_WH_U, KC_BTN2,   KC_UP, KC_BTN1, XXXXXXX,                            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    G(KC_R),  KC_WH_D, KC_LEFT, KC_DOWN, KC_RGHT,  KC_SPC,                            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                         KC_LCTL, KC_BSPC, KC_ENT,           TO_BASE, XXXXXXX, XXXXXXX
  )
};
//clang-format on

// COMBOS
// enum combos {
//     COMBO_B,
//     COMBO_P,
//     COMBO_LNG1,
//     COMBO_LNG2
// //     COMBO_OS,
// //     COMBO_ONEHAND_HOME,
// //     //ZB_STENO,
// };

// const uint16_t PROGMEM JK_combo[] = {KC_J,    KC_K,    COMBO_END};
// const uint16_t PROGMEM KL_combo[] = {KC_K,    KC_L,    COMBO_END};
// const uint16_t PROGMEM JL_combo[] = {KC_J,   KC_L,    COMBO_END};
// const uint16_t PROGMEM NM_combo[] = {KC_N,    KC_M,    COMBO_END};

// combo_t key_combos[] = {
//     [COMBO_B]     = COMBO(JK_combo, KC_B),
//     [COMBO_P]     = COMBO(KL_combo, KC_P),
//     [COMBO_LNG1]  = COMBO(JL_combo, KC_LNG1),
//     [COMBO_LNG2]  = COMBO(NM_combo, G(KC_SPC)),
// };


