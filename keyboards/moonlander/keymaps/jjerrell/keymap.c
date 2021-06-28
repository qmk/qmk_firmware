/* Copyright 2021 Jacob Jerrell <jjerrell+github@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H
#include "version.h"

enum layers {
    WRK,  // default layer
    SYM,
    NAV,
    MOD,
    FN,
    ADJ
};

#define MO_SEL (MOD_LSFT | MOD_LALT)

enum custom_keycodes {
    // a_umlaut = ML_SAFE_RANGE,
    // o_umlaut,
    // u_umlaut,
    // eszett,
};

// clang-format off
#define LAYOUT_moonlander_wrapper(...)  LAYOUT_moonlander(__VA_ARGS__)

#define LAYOUT_moonlander_overlay( \
        k00, k01, k02, k03, k04, k05, k06,   k60, k61, k62, k63, k64, k65, k66, \
        k10, k11, k12, k13, k14, k15, k16,   k70, k71, k72, k73, k74, k75, k76, \
        k20, k21, k22, k23, k24, k25, k26,   k80, k81, k82, k83, k84, k85, k86, \
        k30, k31, k32, k33, k34, k35,             k91, k92, k93, k94, k95, k96, \
        k40, k41, k42, k43, k44,      k53,   kb3,      ka2, ka3, ka4, ka5, ka6, \
                            k50, k51, k52,   kb4, kb5, kb6 \
    ) \
    LAYOUT_moonlander_wrapper( \
        k00,       k01,       k02,       k03,       k04,       k05,       k06, /* LHS / RHS */ k60,       k61,        k62,       k63,       k64,        k65,       k66, \
        k10,       k11,       k12,       k13,       k14,       k15,       k16, /* LHS / RHS */ k70,       k71,        k72,       k73,       k74,        k75,       k76, \
        k20,       k21,SFT_T(k22),GUI_T(k23),ALT_T(k24),       k25,       k26, /* LHS / RHS */ k80,       k81,RALT_T(k82),GUI_T(k83),SFT_T(k84),        k85,       k86, \
        k30,CTL_T(k31),       k32,       k33,       k34,       k35,            /* LHS / RHS */            k91,        k92,       k93,       k94,RCTL_T(k95),       k96, \
        k40,       k41,       k42,       k43,       k44,                  k53, /* LHS / RHS */ kb3,                   ka2,       ka3,       ka4,        ka5,       ka6, \
                                             HYP_T(k50),       k51,       k52, /* LHS / RHS */ kb4,       kb5, MET_T(kb6)                                               \
    )

#define LAYOUT_moonlander_base_wrapper(...) LAYOUT_moonlander_overlay(__VA_ARGS__)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [WRK] = LAYOUT_moonlander_base_wrapper(
        XXXXXXX, KC_1    , KC_2    , KC_3    , KC_4   , KC_5   , XXXXXXX,    XXXXXXX, KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , XXXXXXX,
        XXXXXXX, KC_Q    , KC_D    , KC_R    , KC_W   , KC_B   , XXXXXXX,    XXXXXXX, KC_J   , KC_F   , KC_U   , KC_P   , KC_SCLN, XXXXXXX,
        XXXXXXX, KC_A    , KC_S    , KC_H    , KC_T   , KC_G   , XXXXXXX,    XXXXXXX, KC_Y   , KC_N   , KC_E   , KC_O   , KC_I   , KC_QUOT,
        KC_LSFT, KC_Z    , KC_X    , KC_M    , KC_C   , KC_V   ,                      KC_K   , KC_L   , KC_COMM, KC_DOT , KC_SLSH, XXXXXXX,
        XXXXXXX, XXXXXXX , XXXXXXX , XXXXXXX , MO(NAV),          MO(FN) ,    MO(FN) ,          MO(NAV), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                               KC_SPC , KC_BSPC, MO(SYM),    MO(SYM), KC_TAB , KC_ENT
    ),

    [SYM] = LAYOUT_moonlander_wrapper(
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, KC_UNDS, KC_LBRC, KC_RBRC, KC_CIRC, XXXXXXX,    XXXXXXX, KC_EXLM, KC_LABK, KC_RABK, KC_EQL , KC_AMPR, XXXXXXX,
        XXXXXXX, KC_BSLS, KC_SLSH, KC_LCBR, KC_RCBR, KC_ASTR, XXXXXXX,    XXXXXXX, KC_QUES, KC_LPRN, KC_RPRN, KC_MINS, KC_COLN, KC_AT  ,
        XXXXXXX, KC_HASH, KC_DLR , KC_PIPE, KC_TILD, KC_GRV ,                      KC_PLUS, KC_PERC, KC_DQUO, KC_QUOT, KC_SCLN, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,          _______,    _______,          _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                            XXXXXXX, XXXXXXX, _______,    _______, XXXXXXX, XXXXXXX
    ),

    [NAV] = LAYOUT_moonlander_wrapper(
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, KC_PGUP, KC_BSPC, KC_UP  , KC_DEL , KC_PGDN, XXXXXXX,    XXXXXXX, XXXXXXX, KC_7   , KC_8   , KC_9   , XXXXXXX, XXXXXXX,
        XXXXXXX, KC_HOME, KC_LEFT, KC_DOWN, KC_RGHT, KC_END , XXXXXXX,    XXXXXXX, XXXXXXX, KC_4   , KC_5   , KC_6   , XXXXXXX, XXXXXXX,
        XXXXXXX, KC_ESC , KC_TAB , XXXXXXX, KC_ENT , XXXXXXX,                      XXXXXXX, KC_1   , KC_2   , KC_3   , XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,          _______,    _______,          _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                            XXXXXXX, XXXXXXX, _______,    _______, XXXXXXX, KC_0
    ),

    [MOD] = LAYOUT_moonlander_wrapper(
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, KC_PGUP, KC_BSPC, KC_UP  , KC_DEL , KC_PGDN, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, KC_HOME, KC_LEFT, KC_DOWN, KC_RGHT, KC_END , XXXXXXX,    XXXXXXX, XXXXXXX, KC_LALT, KC_LGUI, KC_LSFT, XXXXXXX, XXXXXXX,
        XXXXXXX, KC_ESC , KC_TAB , XXXXXXX, KC_ENT , XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_LCTL, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX,    XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                            XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX
    ),

    [FN] = LAYOUT_moonlander_wrapper(
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, KC_F10 , KC_F11 , KC_F12 , XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, KC_F7  , KC_F8  , KC_F9  , XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, KC_LSFT, KC_LGUI, KC_LALT, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, KC_F4  , KC_F5  , KC_F6  , XXXXXXX, XXXXXXX,
        XXXXXXX, KC_LCTL, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, KC_F1  , KC_F2  , KC_F3  , XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX,    XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                            XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX
    ),

    [ADJ] = LAYOUT_moonlander_wrapper(
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, KC_F22 , KC_F23 , KC_F24 , XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, KC_F19 , KC_F20 , KC_F21 , XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, KC_LSFT, KC_LGUI, KC_LALT, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, KC_F16 , KC_F17 , KC_F18 , XXXXXXX, XXXXXXX,
        XXXXXXX, KC_LCTL, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, KC_F13 , KC_F14 , KC_F15 , XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX,    XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                            XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX
    )


};

layer_state_t layer_state_set_user(layer_state_t state) {
    ML_LED_1(0);
    ML_LED_2(0);
    ML_LED_3(0);
    ML_LED_4(0);
    ML_LED_5(0);
    ML_LED_6(0);

    state = update_tri_layer_state(state, SYM, NAV, MOD);
    state = update_tri_layer_state(state, SYM, FN, ADJ);
    state = update_tri_layer_state(state, NAV, FN, ADJ);

    switch (get_highest_layer(state)) {
        case 1:
            ML_LED_1(1);
            ML_LED_4(1);
            break;
        case 2:
            ML_LED_2(1);
            ML_LED_5(1);
            break;
        case 3:
            ML_LED_3(1);
            break;
        case 4:
            ML_LED_4(1);
            break;
        case 5:
            ML_LED_5(1);
            break;
        case 6:
            ML_LED_6(1);
            break;
        default:
            break;
    }

    return state;
}
