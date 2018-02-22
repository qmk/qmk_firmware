#include "xd75.h"
#include "bbaserdem.h"

#define DVO 0
#define ALT 1
#define FNC 2

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Dvorak
 * ,-----------------------------------------------------------------.
 * | ` | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 0 | - |  =  |  \  |Termn|
 * |---+---+---+---+---+---+---+---+---+---+---+---+-----+-----+-----|
 * |                                               |  (  |  )  |CpLck|
 * |---+---+---+---+---+---+---+---+---+---+---+---+-----+-----+-----|
 * |                                               |  {  |  }  | Lock|
 * |---+---+---+---+---+---+---+---+---+---+---+---+-----+-----+-----|
 * |                                               |  [  |  ]  | Pass|
 * |---+---+---+---+---+---+---+---+---+---+---+---+-----+-----+-----|
 * |                                               | Alt | Ctrl|Shift|
 * `-----------------------------------------------------------------'
 */
[DVO] = KM(
    KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,
    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,
                               KC_EQL,  KC_BSLS, LGUI(KC_ENT),
    DVORAK_L1,
    DVORAK_R1,
                               KC_LPRN, KC_RPRN, KC_CAPS,
    DVORAK_L2,
    DVORAK_R2,
                               KC_LCBR, KC_RCBR, LGUI(KC_ESC),
    DVORAK_L3,
    DVORAK_R3,
                               KC_LBRC, KC_RBRC, LGUI(KC_P),
    KC_LCTL, KC_LALT, KC_LGUI, MO(ALT), XXX,     KC_SPC,
    KC_ENT,  XXX,     MO(FNC), KC_LEFT, KC_DOWN, KC_RGHT,
                               KC_RALT, KC_RCTL, KC_RSFT ),

[ALT] = KM(
    _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______,
                               _______, _______, _______,
    ALTCHAR_L1,
    ALTCHAR_R1,
                               _______, _______, _______,
    ALTCHAR_L2,
    ALTCHAR_R2,
                               _______, _______, _______,
    ALTCHAR_L3,
    ALTCHAR_R3,
                               _______, _______, _______,
    ALTCHAR_L4,
    ALTCHAR_R4,
                               _______, _______, _______ ),

/* Function
 * ,-----------------------------------------------------------------.
 * |   | F1| F2| F3| F4| F5| F6| F7| F8| F9|F10|F11| F12 |BlLvl|BlBrt|
 * |---+---+---+---+---+---+---+---+---+---+---+---+-----+-----+-----|
 * |Brt|\\\||^||///|   |lin|win|wke|   |^^^|   |   |acc 0|acc 1|acc 2|
 * |---+---+---+---+---+---+---+---+---+---+---+---+-----+-----+-----|
 * |   |<--|mid|-->|cl4|mut|psc|cl5|<<<|mid|>>>|   |     |     |     |
 * |---+---+---+---+---+---+---+---+---+---+---+---+-----+-----+-----|
 * |   |///||v||\\\|   |vl-|vl+|   |   |vvv|   |stp|     |     |     |
 * |---+---+---+---+---+---+---+---+---+---+---+---+-----+-----+-----|
 * |pwr|   |   |   | l clc | r clc |   |rwn|ply|ffw|     |     |     |
 * `-----------------------------------------------------------------'
 */
[FNC] = KM(
    _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,
    KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
                               KC_F12,  BL_STEP, BL_BRTG,
    TG(_MO), MO_NW,   MO_N,    MO_NE,   XXX,     UNI_LI,
    UNI_WN,  KC_WAKE, MO_S_NW, MO_S_N,  MO_S_NE, _______
                               MO_AC_0, MO_AC_1, MO_AC_2,
    _______, MO_W,    MO_CL_M, MO_E,    MO_CL_4, KC_MUTE,
    KC_PSCR, MO_CL_5, MO_S_W,  MO_CL_M, MO_S_E,  _______,
                               _______, _______, _______,
    XXX,     XXX,     MO_S_SW, MO_S_S,  MO_S_SE, KC_VOLD,
    KC_VOLU, XXX,     MO_S_SW, MO_S_S,  MO_S_SE, KC_MSTP,
                               _______, _______, _______,
    KC_PWR,  _______, _______, _______, XXX,     MO_CL_L,
    MO_CL_R, XXX,     _______, KC_MPRV, KC_MPLY, KC_MNXT,
                               _______, _______, _______ )
};

