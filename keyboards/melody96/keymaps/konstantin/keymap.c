#include QMK_KEYBOARD_H
#include "konstantin.h"

static const HSV *colors[] = { &godspeed_blue, &godspeed_yellow };
static const size_t cnum = sizeof colors / sizeof *colors;
static size_t cidx = 0;

enum keycodes_keymap {
    RGB_SET = RANGE_KEYMAP,
};

void eeconfig_init_keymap(void) {
    rgblight_sethsv(colors[cidx]->h, colors[cidx]->s, colors[cidx]->v);
}

bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case RGB_SET:
        if (record->event.pressed) {
            cidx = (cidx + 1) % cnum;
            rgblight_sethsv(colors[cidx]->h, colors[cidx]->s, colors[cidx]->v);
        }
        break;
    }

    return true;
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base layer
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
     * │Esc│F1 │F2 │F3 │F4 │F5 │F6 │F7 │F8 │F9 │F10│F11│F12│PSc│Ins│Hom│End│PgU│PgD│
     * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
     * │ ` │ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │ 0 │ - │ = │ \ │Del│NLk│P/ │P* │P- │
     * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┼───┼───┼───┼───┤
     * │ Tab │ Q │ W │ E │ R │ T │ Y │ U │ I │ O │ P │ [ │ ] │Bspc │P7 │P8 │P9 │   │
     * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┼───┼───┼───┤P+ │
     * │FnCaps│ A │ S │ D │ F │ G │ H │ J │ K │ L │ ; │ ' │ Enter  │P4 │P5 │P6 │   │
     * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┼───┼───┼───┼───┤
     * │LSft│RAG│ Z │ X │ C │ V │ B │ N │ M │ , │ . │ / │RSfRCt│ ↑ │P1 │P2 │P3 │   │
     * ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┴┬──┴──┬───┼───┼───┼───┼───┤PEn│
     * │LCtl│LGui│LAlt│         Space          │RAlGu│FnFLk│ ← │ ↓ │ → │P0 │P. │   │
     * └────┴────┴────┴────────────────────────┴─────┴─────┴───┴───┴───┴───┴───┴───┘
     */
    [L_BASE] = LAYOUT(
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_PSCR, KC_INS,  KC_HOME, KC_END,  KC_PGUP, KC_PGDN,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSLS, KC_DEL,  KC_NLCK, KC_PSLS, KC_PAST, KC_PMNS,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSPC,          KC_P7,   KC_P8,   KC_P9,   XXXXXXX,
        FN_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,                    KC_P4,   KC_P5,   KC_P6,   KC_PPLS,
        KC_LSFT, RAL_RGU, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, RSF_RCT,          KC_UP,   KC_P1,   KC_P2,   KC_P3,   XXXXXXX,
        KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                             RAL_RGU, XXXXXXX, FN_FNLK, KC_LEFT, KC_DOWN, KC_RGHT, KC_P0,   KC_PDOT, KC_PENT
    ),

    /* Fn layer
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
     * │   │   │   │   │   │   │   │   │   │   │   │   │   │Sys│SLk│Pau│Brk│Top│Btm│
     * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
     * │   │F1 │F2 │F3 │F4 │F5 │F6 │F7 │F8 │F9 │F10│F11│F12│   │   │RTg│ ÷ │ × │ − │
     * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┼───┼───┼───┼───┤
     * │ M4  │M2 │M↑ │M1 │M3 │M5 │   │UCM│   │Stp│Ply│Prv│Nxt│Clear│RH+│RS+│RV+│   │
     * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┼───┼───┼───┤RSt│
     * │      │M← │M↓ │M→ │MW↑│   │   │   │   │   │   │   │        │RH-│RS-│RV-│   │
     * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┼───┼───┼───┼───┤
     * │    │   │MA0│MA2│MW←│MW→│   │   │App│Vo-│Vo+│Mut│      │PgU│RMR│RMS│RMB│   │
     * ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴──┬┴──┬┴──┬───┼───┼───┼───┼───┤RMP│
     * │    │DtPR│DtNA│          MW↓           │   │   │   │Hom│PgD│End│RM-│RM+│   │
     * └────┴────┴────┴────────────────────────┴───┴───┴───┴───┴───┴───┴───┴───┴───┘
     */
    [L_FN] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, SYSRQ,   KC_SLCK, KC_PAUS, BREAK,   TOP,     BOTTOM,
        _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, _______, RGB_TOG, DIVIDE,  TIMES,   MINUS,
        KC_BTN4, KC_BTN2, KC_MS_U, KC_BTN1, KC_BTN3, KC_BTN5, _______, UC_MOD,  _______, KC_MSTP, KC_MPLY, KC_MPRV, KC_MNXT, CLEAR,            RGB_HUI, RGB_SAI, RGB_VAI, XXXXXXX,
        _______, KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_U, _______, _______, _______, _______, _______, _______, _______, _______,                   RGB_HUD, RGB_SAD, RGB_VAD, RGB_SET,
        _______, _______, KC_ACL0, KC_ACL2, KC_WH_L, KC_WH_R, _______, _______, KC_APP,  KC_VOLD, KC_VOLU, KC_MUTE, _______,          KC_PGUP, RGB_M_R, RGB_M_SN,RGB_M_B, XXXXXXX,
        _______, DST_P_R, DST_N_A,                            KC_WH_D,                            _______, XXXXXXX, _______, KC_HOME, KC_PGDN, KC_END,  RGB_RMOD,RGB_MOD, RGB_M_P
    ),
};
