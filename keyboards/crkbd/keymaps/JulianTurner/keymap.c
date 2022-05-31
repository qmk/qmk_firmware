
#include QMK_KEYBOARD_H
#include "keycodes.h"
#include "keytabs.h"

#ifdef OLED_ENABLE
#    include "oled.c"
#endif

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTZ] = LAYOUT_split_3x6_3(
        //,-----------------------------------------------------.                    ,-----------------------------------------------------.
             KC_TAB,    DE_Q,    DE_W,    DE_E,    DE_R,    DE_T,                         DE_Z,    DE_U,    DE_I,    DE_O,    DE_P, DE_UDIA,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
            XXXXXXX,  HOME_A,  HOME_S,  HOME_D,  HOME_F,    DE_G,                         DE_H,  HOME_J,  HOME_K,  HOME_L, HOME_OE, DE_ADIA,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       KC_LEFT_CTRL,    DE_Y,    DE_X,    DE_C,    DE_V,    DE_B,                         DE_N,    DE_M, KC_COMM,  DE_DOT, XXXXXXX, XXXXXXX,
        //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                         MO(_NUMBER), MO(_SYMBOL), KC_SPC,   KC_BSPACE, KC_ENTER, XXXXXXX
                                            //`--------------------------'  `--------------------------'

        ),
    [_SYMBOL] = LAYOUT_split_3x6_3(
        //,-----------------------------------------------------.                    ,-----------------------------------------------------.
            XXXXXXX, XXXXXXX, DE_UNDS, DE_LBRC, DE_RBRC, DE_CIRC,                      DE_EXLM, DE_LABK, DE_RABK,  DE_EQL, DE_AMPR,   DE_SS,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
            XXXXXXX, DE_BSLS, DE_SLSH, DE_LCBR, DE_RCBR, DE_ASTR,                      DE_QUES, DE_LPRN, DE_RPRN, DE_MINS,   DE_AT, XXXXXXX,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       KC_LEFT_CTRL, DE_HASH,  DE_DLR, DE_PIPE, DE_TILD,  DE_GRV,                      DE_PLUS, DE_PERC, DE_DQUO, DE_QUOT, XXXXXXX, XXXXXXX,
        //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                      MO(_NUMBER), MO(_SYMBOL),    KC_SPC,   KC_BSPACE, KC_ENTER, XXXXXXX
                                            //`--------------------------'  `--------------------------'

        ),
    [_NUMBER] = LAYOUT_split_3x6_3(
        //,-----------------------------------------------------.                    ,-----------------------------------------------------.
            XXXXXXX, XXXXXXX, KC_PAGE_UP, KC_UP, KC_PAGE_DOWN, XXXXXXX,                XXXXXXX,    DE_7,    DE_8,    DE_9, DE_ASTR, DE_SLSH,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
            XXXXXXX, XXXXXXX, KC_LEFT, KC_DOWN, KC_RIGHT, XXXXXXX,                     XXXXXXX,    DE_4,    DE_5,    DE_6, DE_PLUS, DE_MINS,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       KC_LEFT_CTRL, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX,    DE_1,    DE_2,    DE_3, XXXXXXX, XXXXXXX,
        //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                        MO(_NUMBER), MO(_SYMBOL),  KC_SPC,   KC_BSPACE, KC_ENTER, DE_0
                                            //`--------------------------'  `--------------------------'

        ),
};
// clang-format off

