#include QMK_KEYBOARD_H

#define FN      MO(L_FN)
#define FN_CAPS LT(L_FN, KC_CAPS)
#define FN_ESC  LT(L_FN, KC_ESC)
#define FN_FNLK TT(L_FN)

#define MV_UP   LCTL(KC_UP)
#define MV_DOWN LCTL(KC_DOWN)
#define MV_LEFT LCTL(KC_LEFT)
#define MV_RGHT LCTL(KC_RGHT)
#define TOP     LCTL(KC_HOME)
#define BOTTOM  LCTL(KC_END)

enum keycodes {
    CLEAR = SAFE_RANGE,
};

enum layers {
    L_BASE,
    L_FN,
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case CLEAR:
        if (record->event.pressed) {
            SEND_STRING(SS_LCTL("a") SS_TAP(X_DELETE));
        }
        return false;

    default:
        return true;
    }
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base layer
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
     * │ ` │ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │ 0 │ - │ = │ \ │ ` │PSc│
     * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┼───┤
     * │ Tab │ Q │ W │ E │ R │ T │ Y │ U │ I │ O │ P │ [ │ ] │Bspc │Del│
     * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┼───┤
     * │FnEsc │ A │ S │ D │ F │ G │ H │ J │ K │ L │ ; │ ' │ Enter  │PgU│
     * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┼───┤
     * │ LShift │ Z │ X │ C │ V │ B │ N │ M │ , │ . │ / │RShift│ ↑ │PgD│
     * ├────┬───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬─┬───┼───┼───┤
     * │LCtl│LGui│LAlt│         Space          │RAlt│FnLk│ │ ← │ ↓ │ → │
     * └────┴────┴────┴────────────────────────┴────┴────┘ └───┴───┴───┘
     */
    [L_BASE] = LAYOUT(
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSLS, KC_GRV,  KC_PSCR,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSPC, KC_DEL,
        FN_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,  KC_PGUP,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT, KC_UP,   KC_PGDN,
        KC_LCTL, KC_LGUI, KC_LALT,                   KC_SPC,                             KC_RALT, FN_FNLK,          KC_LEFT, KC_DOWN, KC_RGHT
    ),

    /* Function layer
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
     * │   │F1 │F2 │F3 │F4 │F5 │F6 │F7 │F8 │F9 │F10│F11│F12│NLk│SLk│Pau│
     * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┼───┤
     * │     │M2 │M↑ │M1 │M3 │   │   │   │   │Stp│Ply│Prv│Nxt│Clear│Ins│
     * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┼───┤
     * │      │M← │M↓ │M→ │MW↑│   │   │Mv←│ ↓ │ ↑ │Mv→│   │        │Top│
     * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┼───┤
     * │        │MA0│MA2│MW←│MW→│   │   │App│Vo-│Vo+│Mut│      │PgU│Btm│
     * ├────┬───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬─┬───┼───┼───┤
     * │    │DtPR│DtNA│          MW↓           │    │    │ │Hom│PgD│End│
     * └────┴────┴────┴────────────────────────┴────┴────┘ └───┴───┴───┘
     */
    [L_FN] = LAYOUT(
        _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_NUM,  KC_SCRL, KC_PAUS,
        _______, KC_BTN2, KC_MS_U, KC_BTN1, KC_BTN3, _______, _______, _______, _______, KC_MSTP, KC_MPLY, KC_MPRV, KC_MNXT, CLEAR,   KC_INS,
        _______, KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_U, _______, MV_LEFT, KC_DOWN, KC_UP,   MV_RGHT, _______, _______,          _______, TOP,
        _______, KC_ACL0, KC_ACL2, KC_WH_L, KC_WH_R, _______, _______, KC_APP,  KC_VOLD, KC_VOLU, KC_MUTE,          _______, KC_PGUP, BOTTOM,
        _______, _______, _______,                   KC_WH_D,                            _______, _______,          KC_HOME, KC_PGDN, KC_END
    ),
};
