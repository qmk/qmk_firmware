#include QMK_KEYBOARD_H
#include "konstantin.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base layer
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
     * │Esc│ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │ 0 │ - │ = │ \ │ ` │PSc│
     * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┼───┤
     * │ Tab │ Q │ W │ E │ R │ T │ Y │ U │ I │ O │ P │ [ │ ] │Bspc │Del│
     * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┼───┤
     * │FnCaps│ A │ S │ D │ F │ G │ H │ J │ K │ L │ ; │ ' │ Enter  │PgU│
     * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┼───┤
     * │LSft│RAG│ Z │ X │ C │ V │ B │ N │ M │ , │ . │ / │RShift│ ↑ │PgD│
     * ├────┼───┴┬──┴─┬─┴───┴───┴┬──┴─┬─┴───┴──┬┴───┼───┴┬─┬───┼───┼───┤
     * │LCtl│LGui│LAlt│  Space   │FnLk│   Fn   │RAlG│RCtl│ │ ← │ ↓ │ → │
     * └────┴────┴────┴──────────┴────┴────────┴────┴────┘ └───┴───┴───┘
     */
    [L_BASE] = LAYOUT_multi(
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSLS, KC_GRV,  KC_PSCR,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSPC,          KC_DEL,
        FN_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,           KC_PGUP,
        KC_LSFT, RAL_RGU, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,          KC_UP,   KC_PGDN,
        KC_LCTL, KC_LGUI, KC_LALT,          KC_SPC,           FNLK,             FN,               RAL_RGU, KC_RCTL, XXXXXXX, KC_LEFT, KC_DOWN, KC_RGHT
    ),

    /* Function layer
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
     * │   │F1 │F2 │F3 │F4 │F5 │F6 │F7 │F8 │F9 │F10│F11│F12│Num│SLk│Pau│
     * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┼───┤
     * │ M4  │M2 │M↑ │M1 │M3 │M5 │   │UCM│   │Stp│Ply│Prv│Nxt│Clear│Ins│
     * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┼───┤
     * │      │M← │M↓ │M→ │MW↑│   │   │   │   │   │   │   │        │Top│
     * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┼───┤
     * │    │   │MA0│MA2│MW←│MW→│   │   │App│Vo-│Vo+│Mut│      │PgU│Btm│
     * ├────┼───┴┬──┴─┬─┴───┴───┴┬──┴─┬─┴───┴──┬┴───┼───┴┬─┬───┼───┼───┤
     * │    │DtPR│DtNA│   MW↓    │    │        │    │    │ │Hom│PgD│End│
     * └────┴────┴────┴──────────┴────┴────────┴────┴────┘ └───┴───┴───┘
     */
    [L_FN] = LAYOUT_multi(
        _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  NUMPAD,  KC_SLCK, KC_PAUS,
        KC_BTN4, KC_BTN2, KC_MS_U, KC_BTN1, KC_BTN3, KC_BTN5, _______, UC_MOD,  _______, KC_MSTP, KC_MPLY, KC_MPRV, KC_MNXT, CLEAR,            KC_INS,
        _______, KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_U, _______, _______, _______, _______, _______, _______, _______,          _______,          TOP,
        _______, _______, KC_ACL0, KC_ACL2, KC_WH_L, KC_WH_R, _______, _______, KC_APP,  KC_VOLD, KC_VOLU, KC_MUTE, _______,          KC_PGUP, BOTTOM,
        _______, DST_P_R, DST_N_A,          KC_WH_D,          _______,          _______,          _______, _______, XXXXXXX, KC_HOME, KC_PGDN, KC_END
    ),

    /* Numpad layer
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
     * │   │   │   │   │   │   │   │P7 │P8 │P9 │P- │ − │ = │Num│   │   │
     * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┼───┤
     * │     │   │   │   │   │   │   │P4 │P5 │P6 │P+ │ ( │ ) │     │   │
     * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┼───┤
     * │      │   │   │   │   │   │   │P1 │P2 │P3 │P* │ × │ PEnter │   │
     * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┼───┤
     * │    │   │   │   │   │   │   │P0 │P0 │ , │P. │P/ │  ÷   │   │   │
     * ├────┼───┴┬──┴─┬─┴───┴───┴┬──┴─┬─┴───┴──┬┴───┼───┴┬─┬───┼───┼───┤
     * │    │    │    │          │    │        │    │    │ │   │   │   │
     * └────┴────┴────┴──────────┴────┴────────┴────┴────┘ └───┴───┴───┘
     */
    [L_NUMPAD] = LAYOUT_multi(
        _______, _______, _______, _______, _______, _______, _______, KC_P7,   KC_P8,   KC_P9,   KC_PMNS, MINUS,   EQUALS,  NUMPAD,  _______, _______,
        _______, _______, _______, _______, _______, _______, _______, KC_P4,   KC_P5,   KC_P6,   KC_PPLS, L_PAREN, R_PAREN, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, KC_P1,   KC_P2,   KC_P3,   KC_PAST, TIMES,            KC_PENT,          _______,
        _______, _______, _______, _______, _______, _______, _______, KC_P0,   KC_P0,   COMMA,   KC_PDOT, KC_PSLS, DIVIDE,           _______, _______,
        _______, _______, _______,          _______,          _______,          _______,          _______, _______, XXXXXXX, _______, _______, _______
    ),
};
