// Copyright 2022 Zoull Danusty (@zoullx)
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H

// #define RAISE MO(_RAISE)
// #define LOWER MO(_LOWER)

enum custom_layer {
    _PDVORAK,
    _SPDVORAK,
    _DVORAK,
    _QWERTY,
    _RGBMATRIX
    // _LOWER,
    // _RAISE,
};

enum custom_keycodes {
    DVORAK = DF(_DVORAK),
    PDVORAK = DF(_PDVORAK),
    SDVORAK = MO(_SPDVORAK),
    QWERTY = DF(_QWERTY),
    RGBMAT = DF(_RGBMATRIX),
    KCSA = S(KC_A),
    KCSB = S(KC_B),
    KCSC = S(KC_C),
    KCSD = S(KC_D),
    KCSE = S(KC_E),
    KCSF = S(KC_F),
    KCSG = S(KC_G),
    KCSH = S(KC_H),
    KCSI = S(KC_I),
    KCSJ = S(KC_J),
    KCSK = S(KC_K),
    KCSL = S(KC_L),
    KCSM = S(KC_M),
    KCSN = S(KC_N),
    KCSO = S(KC_O),
    KCSP = S(KC_P),
    KCSQ = S(KC_Q),
    KCSR = S(KC_R),
    KCSS = S(KC_S),
    KCST = S(KC_T),
    KCSU = S(KC_U),
    KCSV = S(KC_V),
    KCSW = S(KC_W),
    KCSX = S(KC_X),
    KCSY = S(KC_Y),
    KCSZ = S(KC_Z),
    KCSTAB = S(KC_TAB),
    KCSENT = S(KC_ENT),
    KCSLEFT = S(KC_LEFT),
    KCSRGHT = S(KC_RGHT),
    KCSUP = S(KC_UP),
    KCSDOWN = S(KC_DOWN)
};

// Indicators
bool rgb_matrix_indicators_user(void) {
    switch(get_highest_layer(layer_state|default_layer_state)) {
        case _PDVORAK:
            rgb_matrix_set_color(6, RGB_RED);
            break;
        case _SPDVORAK:
            rgb_matrix_set_color(6, RGB_ORANGE);
            break;
        case _DVORAK:
            rgb_matrix_set_color(6, RGB_YELLOW);
            break;
        case _QWERTY:
            rgb_matrix_set_color(6, RGB_GREEN);
            break;
        case _RGBMATRIX:
            rgb_matrix_set_color(6, RGB_BLUE);
            break;
        // case _LOWER:
        //     rgb_matrix_set_color(6, RGB_BLUE);
        //     break;
        // case _RAISE:
        //     rgb_matrix_set_color(6, RGB_PURPLE);
        //     break;
        default:
            break;
    }
    return false;
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_PDVORAK] = LAYOUT_6x7_fullrows(
        _______ , KC_F1   , KC_F2   , KC_F3   , KC_F4   , KC_F5   , KC_F6   ,                  KC_F7   , KC_F8   , KC_F9   , KC_F10  , KC_F11  , KC_F12  , _______ ,
        _______ , KC_DLR  , KC_PLUS , KC_LBRC , KC_LCBR , KC_LPRN , KC_AMPR ,                  KC_EQL  , KC_RPRN , KC_RCBR , KC_RBRC , KC_ASTR , KC_EXLM , _______ ,
        _______ , KC_PIPE , KC_QUOT , KC_COMM , KC_DOT  , KC_P    , KC_Y    ,                  KC_F    , KC_G    , KC_C    , KC_R    , KC_L    , KC_AT   , _______ ,
        _______ , KC_BSLS , KC_A    , KC_O    , KC_E    , KC_U    , KC_I    ,                  KC_D    , KC_H    , KC_T    , KC_N    , KC_S    , KC_SLSH , _______ ,
        _______ , KC_DEL  , KC_SCLN , KC_Q    , KC_J    , KC_K    , KC_X    ,                  KC_B    , KC_M    , KC_W    , KC_V    , KC_Z    , KC_MINS , _______ ,
        DVORAK  , KC_LALT , KC_LSFT , KC_LEFT , KC_RGHT ,                                                          KC_UP   , KC_DOWN , KC_RSFT , KC_RALT , RGBMAT  ,
                                                          KC_SPC  , KC_TAB  ,                  KC_BSPC , KC_ENT  ,
                                                          KC_LCTL , SDVORAK ,                  SDVORAK , KC_RCTL ,
                                                          KC_HOME , KC_END  ,                  KC_ESC  , KC_LGUI
    ),
    
    [_SPDVORAK] = LAYOUT_6x7_fullrows(
        _______ , _______ , _______ , _______ , _______ , _______ , _______ ,                  _______ , _______ , _______ , _______ , _______ , _______ , _______ ,
        _______ , KC_TILD , KC_1    , KC_2    , KC_3    , KC_4    , KC_5    ,                  KC_6    , KC_7    , KC_8    , KC_9    , KC_0    , KC_PERC , _______ ,
        _______ , KC_GRV  , KC_DQUO , KC_LABK , KC_RABK , KCSP    , KCSY    ,                  KCSF    , KCSG    , KCSC    , KCSR    , KCSL    , KC_CIRC , _______ ,
        _______ , KC_HASH , KCSA    , KCSO    , KCSE    , KCSU    , KCSI    ,                  KCSD    , KCSH    , KCST    , KCSN    , KCSS    , KC_UNDS , _______ ,
        _______ , _______ , KC_COLN , KCSQ    , KCSJ    , KCSK    , KCSX    ,                  KCSB    , KCSM    , KCSW    , KCSV    , KCSZ    , KC_QUES , _______ ,
        _______ , _______ , _______ , KCSLEFT , KCSRGHT ,                                                          KCSUP   , KCSDOWN , _______ , _______ , _______ ,
                                                          _______ , KCSTAB  ,                  _______ , KCSENT  ,
                                                          _______ , _______ ,                  _______ , _______ ,
                                                          _______ , _______ ,                  _______ , _______
    ),

    [_DVORAK] = LAYOUT_6x7_fullrows(
        _______ , KC_F1   , KC_F2   , KC_F3   , KC_F4   , KC_F5   , KC_F6   ,                  KC_F7   , KC_F8   , KC_F9   , KC_F10  , KC_F11  , KC_F12  , _______ ,
        _______ , _______ , KC_1    , KC_2    , KC_3    , KC_4    , KC_5    ,                  KC_6    , KC_7    , KC_8    , KC_9    , KC_0    , KC_BSLS , _______ ,
        _______ , _______ , KC_QUOT , KC_COMM , KC_DOT  , KC_P    , KC_Y    ,                  KC_F    , KC_G    , KC_C    , KC_R    , KC_L    , KC_MINS , _______ ,
        _______ , KC_DEL  , KC_A    , KC_O    , KC_E    , KC_U    , KC_I    ,                  KC_D    , KC_H    , KC_T    , KC_N    , KC_S    , KC_EQL  , _______ ,
        _______ , KC_LALT , KC_SCLN , KC_Q    , KC_J    , KC_K    , KC_X    ,                  KC_B    , KC_M    , KC_W    , KC_V    , KC_Z    , KC_RALT , _______ ,
        QWERTY  , KC_GRV  , KC_SLSH , KC_LEFT , KC_RGHT ,                                                          KC_UP   , KC_DOWN , KC_LBRC , KC_RBRC , PDVORAK ,
                                                          KC_SPC  , KC_TAB  ,                  KC_BSPC , KC_ENT  ,
                                                          KC_LCTL , KC_LSFT ,                  KC_RSFT , KC_RCTL ,
                                                          KC_HOME , KC_END  ,                  KC_ESC  , KC_LGUI
    ),

    [_QWERTY] = LAYOUT_6x7_fullrows(
        _______ , KC_F1   , KC_F2   , KC_F3   , KC_F4   , KC_F5   , KC_F6   ,                  KC_F7   , KC_F8   , KC_F9   , KC_F10  , KC_F11  , KC_F12  , _______ ,
        _______ , KC_GRV  , KC_1    , KC_2    , KC_3    , KC_4    , KC_5    ,                  KC_6    , KC_7    , KC_8    , KC_9    , KC_0    , KC_BSLS , _______ ,
        _______ , _______ , KC_Q    , KC_W    , KC_E    , KC_R    , KC_T    ,                  KC_Y    , KC_U    , KC_I    , KC_O    , KC_P    , KC_MINS , _______ ,
        _______ , _______ , KC_A    , KC_S    , KC_D    , KC_F    , KC_G    ,                  KC_H    , KC_J    , KC_K    , KC_L    , KC_SCLN , KC_EQL  , _______ ,
        _______ , KC_LALT , KC_Z    , KC_X    , KC_C    , KC_V    , KC_B    ,                  KC_N    , KC_M    , KC_COMM , KC_DOT  , KC_SLSH , KC_RALT , _______ ,
        RGBMAT  , KC_DEL  , KC_QUOT , KC_LEFT , KC_RGHT ,                                                          KC_UP   , KC_DOWN , KC_LBRC , KC_RBRC , DVORAK  ,
                                                          KC_SPC  , KC_TAB  ,                  KC_BSPC , KC_ENT  ,
                                                          KC_LCTL , KC_LSFT ,                  KC_RSFT , KC_RCTL ,
                                                          KC_HOME , KC_END  ,                  KC_ESC  , KC_LGUI
    ),

    [_RGBMATRIX] = LAYOUT_6x7_fullrows(
        _______ , _______ , _______ , _______ , _______ , _______ , _______ ,                  _______ , _______ , _______ , _______ , _______ , _______ , _______ ,
        _______ , _______ , _______ , _______ , _______ , _______ , _______ ,                  _______ , _______ , _______ , _______ , _______ , _______ , _______ ,
        _______ , _______ , _______ , _______ , _______ , _______ , _______ ,                  _______ , _______ , _______ , _______ , _______ , _______ , _______ ,
        _______ , RGB_TOG , RGB_VAI , RGB_SAI , RGB_HUI , RGB_MOD , RGB_SPI ,                  RGB_SPI , RGB_MOD , RGB_HUI , RGB_SAI , RGB_VAI , RGB_TOG , _______ ,
        _______ , _______ , RGB_VAD , RGB_SAD , RGB_HUD , RGB_RMOD, RGB_SPD ,                  RGB_SPD , RGB_RMOD, RGB_HUD , RGB_SAD , RGB_VAD , _______ , _______ ,
        PDVORAK , _______ , _______ , _______ , _______ ,                                                          _______ , _______ , _______ , _______ , QWERTY  ,
                                                          _______ , _______ ,                  _______ , _______ ,
                                                          _______ , _______ ,                  _______ , _______ ,
                                                          _______ , _______ ,                  _______ , _______
    ),

    // [_LOWER] = LAYOUT_6x7_fullrows(
    //     KC_ESC , KC_F1  , KC_F2 , KC_F3 , KC_F4 , KC_F5 , KC_F6  ,                       KC_F7 , KC_F8  , KC_F9 ,KC_F10 ,KC_F11 ,KC_F12 , _______,
    //     _______, KC_TILD,KC_EXLM, KC_AT ,KC_HASH,KC_DLR ,KC_PERC,                        KC_CIRC,KC_AMPR,KC_ASTR,KC_LPRN,KC_RPRN,KC_DEL , _______,
    //     _______, _______,_______,_______,_______,_______,KC_LBRC,                        KC_RBRC, KC_P7 , KC_P8 , KC_P9 ,_______,KC_PLUS, _______,
    //     _______, _______,KC_HOME,KC_PGUP,KC_PGDN,KC_END ,KC_LPRN,                        KC_RPRN, KC_P4 , KC_P5 , KC_P6 ,KC_MINS,KC_PIPE, _______,
    //     _______, _______,_______,_______,_______,_______,_______,                        _______, KC_P1 , KC_P2 , KC_P3 ,KC_EQL ,KC_UNDS, _______,
    //     _______, _______,_______,_______,KC_PSCR,                                                        _______, KC_P0,_______, _______, _______,
    //                                             _______,_______,                         _______,_______,
    //                                             _______,_______,                         _______,_______,
    //                                             _______,_______,                         _______,_______
    // ),

    // [_RAISE] = LAYOUT_6x7_fullrows(
    //     _______,KC_F12 , KC_F1 , KC_F2 , KC_F3 , KC_F4 , KC_F5 ,                        KC_F6  , KC_F7 , KC_F8 , KC_F9 ,KC_F10 ,KC_F11 , _______,
    //     _______,_______,_______,_______,_______,_______,KC_LBRC,                        KC_RBRC,_______,KC_NLCK,KC_INS ,KC_SLCK,KC_MUTE, _______,
    //     _______,_______,KC_LEFT,KC_UP  ,KC_DOWN,KC_RGHT,KC_LPRN,                        KC_RPRN,KC_MPRV,KC_MPLY,KC_MNXT,_______,KC_VOLU, _______,
    //     _______,_______,_______,_______,_______,_______,_______,                        _______,_______,_______,_______,_______,KC_VOLD, _______,
    //     _______,_______,_______,_______,_______,_______,_______,                        _______,_______,_______,_______,_______,_______, _______,
    //     _______,_______,_______,_______,_______,                                                        KC_EQL ,_______,_______,_______, _______,
    //                                             _______,_______,                        _______,_______,
    //                                             _______,_______,                        _______,_______,
    //                                             _______,_______,                        _______,_______
    // )
};
