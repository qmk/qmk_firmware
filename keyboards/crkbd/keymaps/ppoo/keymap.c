/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>
Copyright 2022 Alejandro Jarovisky <@ajarov>

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

#include QMK_KEYBOARD_H
#include "keymap_spanish.h"
#include "keymap_esp_latino.h"

enum layers {
    L_NORMAL,
    L_ABAJO,
    L_ARRIBA,
    L_AJUSTAR,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
      ,-----------------------------------------------------.                    ,-----------------------------------------------------.
      |    TAB ,    Q   ,    W   ,    E   ,    R   ,    T   ,                    |    Y   ,    U   ,    I   ,    O   ,    P   ,   BSPC ,
      |--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      | L SHIFT,    A   ,    S   ,    D   ,    F   ,    G   ,                    |    H   ,    J   ,    K   ,    L   ,    Ñ   ,    \   ,
      |--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      |    CTRL,    Z   ,    X   ,    C   ,    V   ,    B   ,                    |    N   ,    M   ,   , ;  ,   . :  ,   - _  , R SHIFT,
      |--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                            WIN/CMD,   MO(1),  KC_SPC,     KC_SPC,   MO(2),    RALT(SUPR)
                                        //`--------------------------'  `--------------------------'
    */

    [L_NORMAL] = LAYOUT_split_3x6_3(
    //,-----------------------------------------------------.                    ,-----------------------------------------------------.
         KC_TAB,    ES_Q,    ES_W,    ES_E,    ES_R,    ES_T,                         ES_Y,    ES_U,    ES_I,    ES_O,   ES_P,  KC_BSPC,
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        KC_LSFT,    ES_A,    ES_S,    ES_D,    ES_F,    ES_G,                         ES_H,    ES_J,    ES_K,    ES_L, ES_NTIL, ALGR(ES_QUOT),
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        KC_LCTL,    ES_Z,    ES_X,    ES_C,    ES_V,    ES_B,                         ES_N,    ES_M, ES_COMM,  ES_DOT, ES_MINS, KC_RSFT,
    //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+---I-----+--------|
                                            KC_LGUI,   MO(1),  KC_SPC,     KC_ENT,   MO(2), KC_LALT
                                        //`--------------------------'  `--------------------------'    
    ),

    /*
      ,-----------------------------------------------------.                    ,-----------------------------------------------------.
      |   TAB  ,   F1   ,   F2   ,   F3   ,   F4   ,   CALC ,                    |   INS  ,   HOME ,        ,  PG UP ,    _   ,   BSPC ,
      |--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      |  L SHIFT,  F5   ,   F6   ,   F7   ,   F8   , PRT SCR,                    |   DEL  ,    END ,   ↑    , PG DOWN,        ,        ,
      |--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      |   CTRL ,   F9   ,   F10  ,   F11  ,   F12  ,        ,                    |        ,    ←   ,   ↓    ,    →   ,        , R SHIFT,
      |--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                            WIN/CMD,        ,  KC_SPC,     KC_SPC,   MO(2), KC_DEL
                                        //`--------------------------'  `--------------------------'
    */

    [L_ABAJO] = LAYOUT_split_3x6_3(
    //,-----------------------------------------------------.                    ,-----------------------------------------------------.
         KC_ESC,   KC_F1,   KC_F2,   KC_F3,   KC_F4, KC_CALC,                       KC_INS, KC_HOME, XXXXXXX, KC_PGUP, ES_UNDS, KC_BSPC,
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        KC_LSFT,   KC_F5,   KC_F6,   KC_F7,   KC_F8, KC_PSCR,                       KC_DEL, KC_END ,   KC_UP, KC_PGDN, XXXXXXX, XXXXXXX,
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        KC_LCTL,   KC_F9,  KC_F10,  KC_F11,  KC_F12, XXXXXXX,                       XXXXXXX, KC_LEFT, KC_DOWN,KC_RGHT, XXXXXXX, KC_RSFT,
    //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                            KC_LGUI, _______,  KC_SPC,     KC_ENT, _______, KC_LALT
                                        //`--------------------------'  `--------------------------'
    ),

    /*
      ,-----------------------------------------------------.                    ,-----------------------------------------------------.
      |    TAB  ,   '    ,   "   ,   ·    ,   @    ,    $   ,                    |   *    ,    7   ,    8   ,    9   ,   -   ,    BSPC ,
      |--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      | L SHIFT ,   {    ,   }   ,   (    ,   )    ,    ?   ,                    |   /    ,    4   ,    5   ,    6   ,   +   ,     =   ,
      |--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      |   CTRL  ,   [    ,   ]   ,    <   ,   >   ,     ¿   ,                    |   0    ,    1   ,    2   ,    3   ,   .   , R SHIFT ,
      |--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                            WIN/CMD,        ,  KC_SPC,     KC_SPC,   MO(2), KC_RALT
                                        //`--------------------------'  `--------------------------'
    */

    [L_ARRIBA] = LAYOUT_split_3x6_3(
    //,-----------------------------------------------------.                    ,-----------------------------------------------------.
         KC_TAB, ES_QUOT, ES_DQUO, ES_SHRP, ES_ARRB,  ES_DLR,                       KC_PAST,    ES_7,    ES_8,    ES_9, ES_QUOT, KC_BSPC,
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        KC_LSFT, KC_QUOT, KC_BSLS, ES_LPRN, ES_RPRN, ES_QUES,                      KC_PSLS,    ES_4,    ES_5,    ES_6, KC_PPLS,  ES_EQL,
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        KC_LCTL, ES_LBR2, ES_RBR2, ES_LABK, ES_RABK, ES_INTG,                         ES_0,    ES_1,    ES_2,    ES_3,  ES_DOT, KC_RSFT,
    //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                            KC_LGUI, _______,  KC_SPC,     KC_ENT, _______, KC_LALT
                                        //`--------------------------'  `--------------------------'
    ),

    /*
      ,-----------------------------------------------------.                    ,-----------------------------------------------------.
      |   CAPS  ,   ~   ,    %   ,    &   ,        ,   MOD  ,                    |  R up  ,  MUTE  ,  VOL-  ,   VOL+ ,  PLAY ,    BSPC ,
      |--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      | L SHIFT ,   á   ,    ä   ,    à   ,    ¿    , R MOD,                     | R down ,        ,        ,        ,   S    ,   BOOT ,
      |--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      |   CTRL  , R ALT ,    ¡   ,    !   ,  <--brw,  -->brw,                    | RGB TOG, R CLICK,        ,        ,        , R SHIFT,
      |--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                            WIN/CMD,        ,  KC_SPC,     KC_SPC,   MO(2), KC_RALT
                                        //`--------------------------'  `--------------------------'
    */

    [L_AJUSTAR] = LAYOUT_split_3x6_3(
    //,-----------------------------------------------------.                    ,-----------------------------------------------------.
        KC_CAPS, ES_RBRC, ES_PERC, ES_AMPR, XXXXXXX, RGB_MOD,                      KC_WH_U, KC_MUTE, KC_VOLD, KC_VOLU, KC_MPLY, KC_BSPC,
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        KC_LCTL, ES_GRV,  ES_LBRC, ES_RCBR, ES_IQUE,RGB_RMOD,                      KC_WH_D, XXXXXXX, RGB_HUI, RGB_SAI, RGB_VAI, QK_BOOT,
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        KC_LSFT, KC_ALGR, ES_LEXL, ES_EXLM, KC_WBAK, KC_WFWD,                      RGB_TOG, KC_BTN2, RGB_HUD, RGB_SAD, RGB_VAD, KC_RSFT,
    //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                            KC_LGUI, _______,  KC_SPC,     KC_ENT, _______, KC_LALT
                                        //`--------------------------'  `--------------------------'
    )
};

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, L_ABAJO, L_ARRIBA, L_AJUSTAR);
}

#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (!is_keyboard_master()) {
        return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
    }
    return rotation;
}

void oled_render_layer_state(void) {
    // Host Keyboard Layer Status
    oled_write_P(PSTR("Capa: "), false);
    switch (get_highest_layer(layer_state)) {
        case L_NORMAL:
            oled_write_ln_P(PSTR("Normal"), false);
            break;
        case L_ABAJO:
            oled_write_ln_P(PSTR("Abajo"), false);
            break;
        case L_ARRIBA:
            oled_write_ln_P(PSTR("Arriba"), false);
            break;
        case L_AJUSTAR:
            oled_write_ln_P(PSTR("Ajustar"), false);
            break;
        default:
            oled_write_ln_P(PSTR("Undefined"), false);
    }

    // Host Keyboard LED Status
    led_t led_state = host_keyboard_led_state();
    oled_write_ln_P(PSTR(""), false);
    oled_write_ln_P(led_state.caps_lock ? PSTR("CAPS LOCK") : PSTR("         "), false);
}

void render_bootmagic_status(bool status) {
    /* Show Ctrl-Gui Swap options */
    static const char PROGMEM logo[][2][3] = {
        {{0x97, 0x98, 0}, {0xb7, 0xb8, 0}},
        {{0x95, 0x96, 0}, {0xb5, 0xb6, 0}},
    };
    if (status) {
        oled_write_ln_P(logo[0][0], false);
        oled_write_ln_P(logo[0][1], false);
    } else {
        oled_write_ln_P(logo[1][0], false);
        oled_write_ln_P(logo[1][1], false); 
    }
}

void oled_render_logo(void) {
    static const char PROGMEM crkbd_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4,
        0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4,
        0};
    oled_write_P(crkbd_logo, false);
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        oled_render_layer_state();
    } else {
        oled_render_logo();
    }
    return false;
}

#endif // OLED_ENABLE
