
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
                                         MO(_NUMBER), MO(_SYMBOL), KC_SPC,  KC_BSPACE, XXXXXXX, XXXXXXX
                                            //`--------------------------'  `--------------------------'

        ),
    [_SYMBOL] = LAYOUT_split_3x6_3(
        //,-----------------------------------------------------.                    ,-----------------------------------------------------.
            XXXXXXX, XXXXXXX, XXXXXXX, DE_LBRC, DE_RBRC, XXXXXXX,                      DE_EXLM, DE_LABK, DE_RABK, XXXXXXX, XXXXXXX,   DE_SS,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
            XXXXXXX, XXXXXXX, XXXXXXX, DE_LCBR, DE_RCBR, XXXXXXX,                      DE_QUES, DE_LPRN, DE_RPRN, XXXXXXX, XXXXXXX, XXXXXXX,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       KC_LEFT_CTRL, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                      MO(_NUMBER), MO(_SYMBOL), XXXXXXX,     KC_ENTER, XXXXXXX, XXXXXXX
                                            //`--------------------------'  `--------------------------'

        ),
    [_NUMBER] = LAYOUT_split_3x6_3(
        //,-----------------------------------------------------.                    ,-----------------------------------------------------.
            XXXXXXX, XXXXXXX, KC_PAGE_UP, KC_UP, KC_PAGE_DOWN, XXXXXXX,                XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
            XXXXXXX, XXXXXXX, KC_LEFT, KC_DOWN, KC_RIGHT, XXXXXXX,                     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       KC_LEFT_CTRL, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                        MO(_NUMBER), MO(_SYMBOL), XXXXXXX,   XXXXXXX, XXXXXXX, XXXXXXX
                                            //`--------------------------'  `--------------------------'

        ),
};
// clang-format off

