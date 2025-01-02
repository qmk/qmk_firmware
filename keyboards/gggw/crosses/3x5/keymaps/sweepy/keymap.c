// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#include "lib/crosses.h"

enum CROSSES_LAYERS {
    _BASE,
    _MOUS,
    _NAV,
    _SYM,
    _BRC,
    _FUNC,
    _NUM,
    _MISC,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
//    ┌───────────┬───────────┬───────────┬──────────┬──────┐                       ┌────────────┬──────────┬───────────┬───────────┬───────────┐
//    │     q     │     w     │     e     │    r     │  t   │                       │     y      │    u     │     i     │     o     │     p     │
//    ├───────────┼───────────┼───────────┼──────────┼──────┤                       ├────────────┼──────────┼───────────┼───────────┼───────────┤
//    │ LSFT_T(a) │ LT(5, s)  │ LT(1, d)  │ LT(3, f) │  g   │                       │     h      │ LT(4, j) │ LT(2, k)  │ LT(6, l)  │ LSFT_T(;) │
//    ├───────────┼───────────┼───────────┼──────────┼──────┤                       ├────────────┼──────────┼───────────┼───────────┼───────────┤
//    │     z     │ LCTL_T(x) │ LALT_T(c) │    v     │  b   │                       │     n      │    m     │ LALT_T(,) │ LCTL_T(.) │     /     │
//    └───────────┴───────────┴───────────┼──────────┼──────┼────────────┐   ┌──────┼────────────┼──────────┼───────────┴───────────┴───────────┘
//                                        │   kp_0   │ bspc │ LT(7, spc) │   │ kp_1 │ LT(7, spc) │   kp_1   │
//                                        └──────────┴──────┴────────────┘   └──────┴────────────┴──────────┘
[_BASE] = LAYOUT_default(
  KC_Q         , KC_W         , KC_E         , KC_R        , KC_T    ,                             KC_Y          , KC_U        , KC_I            , KC_O           , KC_P           ,
  LSFT_T(KC_A) , LT(5, KC_S)  , LT(1, KC_D)  , LT(3, KC_F) , KC_G    ,                             KC_H          , LT(4, KC_J) , LT(2, KC_K)     , LT(6, KC_L)    , LSFT_T(KC_SCLN),
  KC_Z         , LCTL_T(KC_X) , LALT_T(KC_C) , KC_V        , KC_B    ,                             KC_N          , KC_M        , LALT_T(KC_COMM) , LCTL_T(KC_DOT) , KC_SLSH        ,
                                               KC_P0       , KC_BSPC , LT(7, KC_SPC) ,     KC_P1 , LT(7, KC_SPC) , KC_P1
),

//    ┌─────┬──────┬─────┬──────┬─────┐               ┌─────┬──────┬──────┬──────┬──────┐
//    │     │      │     │      │     │               │     │ btn1 │ wh_u │ btn2 │      │
//    ├─────┼──────┼─────┼──────┼─────┤               ├─────┼──────┼──────┼──────┼──────┤
//    │     │ btn2 │ no  │ btn1 │     │               │     │ ms_l │ ms_d │ ms_u │ ms_r │
//    ├─────┼──────┼─────┼──────┼─────┤               ├─────┼──────┼──────┼──────┼──────┤
//    │     │      │     │      │     │               │     │ wh_l │ wh_d │ wh_r │      │
//    └─────┴──────┴─────┼──────┼─────┼─────┐   ┌─────┼─────┼──────┼──────┴──────┴──────┘
//                       │      │     │     │   │     │ no  │  no  │
//                       └──────┴─────┴─────┘   └─────┴─────┴──────┘
[_MOUS] = LAYOUT_default(
  KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,                         KC_TRNS , KC_BTN1 , KC_WH_U , KC_BTN2 , KC_TRNS,
  KC_TRNS , KC_BTN2 , KC_NO   , KC_BTN1 , KC_TRNS ,                         KC_TRNS , KC_MS_L , KC_MS_D , KC_MS_U , KC_MS_R,
  KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,                         KC_TRNS , KC_WH_L , KC_WH_D , KC_WH_R , KC_TRNS,
                                KC_TRNS , KC_TRNS , KC_TRNS ,     KC_TRNS , KC_NO   , KC_NO
),

//    ┌──────┬──────┬──────┬──────┬─────┐               ┌─────┬──────┬─────┬────────────┬───────────┐
//    │      │      │ pgup │      │     │               │     │      │     │            │           │
//    ├──────┼──────┼──────┼──────┼─────┤               ├─────┼──────┼─────┼────────────┼───────────┤
//    │ left │  up  │ down │ rght │     │               │     │ lgui │ no  │ LCTL(lalt) │ LCA(lsft) │
//    ├──────┼──────┼──────┼──────┼─────┤               ├─────┼──────┼─────┼────────────┼───────────┤
//    │      │ home │ pgdn │ end  │     │               │     │      │     │            │           │
//    └──────┴──────┴──────┼──────┼─────┼─────┐   ┌─────┼─────┼──────┼─────┴────────────┴───────────┘
//                         │      │     │     │   │     │ no  │  no  │
//                         └──────┴─────┴─────┘   └─────┴─────┴──────┘
[_NAV] = LAYOUT_default(
  KC_TRNS , KC_TRNS , KC_PGUP , KC_TRNS , KC_TRNS ,                         KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS       , KC_TRNS     ,
  KC_LEFT , KC_UP   , KC_DOWN , KC_RGHT , KC_TRNS ,                         KC_TRNS , KC_LGUI , KC_NO   , LCTL(KC_LALT) , LCA(KC_LSFT),
  KC_TRNS , KC_HOME , KC_PGDN , KC_END  , KC_TRNS ,                         KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS       , KC_TRNS     ,
                                KC_TRNS , KC_TRNS , KC_TRNS ,     KC_TRNS , KC_NO   , KC_NO
),

//    ┌─────┬─────┬─────┬─────────┬─────┐                   ┌─────┬────┬───┬───┬─────┐
//    │     │     │     │         │     │                   │     │ _  │ | │ ' │     │
//    ├─────┼─────┼─────┼─────────┼─────┤                   ├─────┼────┼───┼───┼─────┤
//    │  ^  │  *  │  &  │   no    │     │                   │  #  │ ~  │ / │ " │  $  │
//    ├─────┼─────┼─────┼─────────┼─────┤                   ├─────┼────┼───┼───┼─────┤
//    │     │     │     │         │     │                   │     │ -  │ \ │ ` │     │
//    └─────┴─────┴─────┼─────────┼─────┼─────┐   ┌─────────┼─────┼────┼───┴───┴─────┘
//                      │ RM_PREV │     │     │   │ RM_NEXT │ no  │ no │
//                      └─────────┴─────┴─────┘   └─────────┴─────┴────┘
[_SYM] = LAYOUT_default(
  KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,                         KC_TRNS , KC_UNDS , KC_PIPE , KC_QUOT , KC_TRNS,
  KC_CIRC , KC_ASTR , KC_AMPR , KC_NO   , KC_TRNS ,                         KC_HASH , KC_TILD , KC_SLSH , KC_DQUO , KC_DLR ,
  KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS ,                         KC_TRNS , KC_MINS , KC_BSLS , KC_GRV  , KC_TRNS,
                                RM_PREV , KC_TRNS , KC_TRNS ,     RM_NEXT , KC_NO   , KC_NO
),

//    ┌─────┬───┬───┬──────┬─────┐                ┌─────┬─────┬─────┬─────┬─────┐
//    │     │ : │ < │  >   │  ;  │                │     │     │     │     │     │
//    ├─────┼───┼───┼──────┼─────┤                ├─────┼─────┼─────┼─────┼─────┤
//    │  {  │ } │ ( │  )   │  @  │                │     │ no  │  =  │  +  │  %  │
//    ├─────┼───┼───┼──────┼─────┤                ├─────┼─────┼─────┼─────┼─────┤
//    │     │ ! │ [ │  ]   │     │                │     │     │     │     │     │
//    └─────┴───┴───┼──────┼─────┼─────┐   ┌──────┼─────┼─────┼─────┴─────┴─────┘
//                  │ vold │     │     │   │ volu │ no  │ no  │
//                  └──────┴─────┴─────┘   └──────┴─────┴─────┘
[_BRC] = LAYOUT_default(
  KC_TRNS , KC_COLN , KC_LT   , KC_GT   , KC_SCLN ,                         KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS,
  KC_LCBR , KC_RCBR , KC_LPRN , KC_RPRN , KC_AT   ,                         KC_TRNS , KC_NO   , KC_EQL  , KC_PLUS , KC_PERC,
  KC_TRNS , KC_EXLM , KC_LBRC , KC_RBRC , KC_TRNS ,                         KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS,
                                KC_VOLD , KC_TRNS , KC_TRNS ,     KC_VOLU , KC_NO   , KC_NO
),

//    ┌─────┬─────┬────────────┬─────┬─────┐               ┌─────┬────┬────┬────┬─────┐
//    │     │     │            │     │     │               │     │ f7 │ f8 │ f9 │ f10 │
//    ├─────┼─────┼────────────┼─────┼─────┤               ├─────┼────┼────┼────┼─────┤
//    │     │ no  │ LCTL(lalt) │     │     │               │     │ f4 │ f5 │ f6 │ f11 │
//    ├─────┼─────┼────────────┼─────┼─────┤               ├─────┼────┼────┼────┼─────┤
//    │     │     │            │     │     │               │     │ f1 │ f2 │ f3 │ f12 │
//    └─────┴─────┴────────────┼─────┼─────┼─────┐   ┌─────┼─────┼────┼────┴────┴─────┘
//                             │     │     │     │   │     │ no  │ no │
//                             └─────┴─────┴─────┘   └─────┴─────┴────┘
[_FUNC] = LAYOUT_default(
  KC_TRNS , KC_TRNS , KC_TRNS       , KC_TRNS , KC_TRNS ,                         KC_TRNS , KC_F7 , KC_F8 , KC_F9 , KC_F10,
  KC_TRNS , KC_NO   , LCTL(KC_LALT) , KC_TRNS , KC_TRNS ,                         KC_TRNS , KC_F4 , KC_F5 , KC_F6 , KC_F11,
  KC_TRNS , KC_TRNS , KC_TRNS       , KC_TRNS , KC_TRNS ,                         KC_TRNS , KC_F1 , KC_F2 , KC_F3 , KC_F12,
                                      KC_TRNS , KC_TRNS , KC_TRNS ,     KC_TRNS , KC_NO   , KC_NO
),

//    ┌──────┬───┬───┬─────┬──────┐               ┌─────┬─────┬─────┬─────┬─────┐
//    │ kp_/ │ 7 │ 8 │  9  │ kp_+ │               │     │     │     │     │     │
//    ├──────┼───┼───┼─────┼──────┤               ├─────┼─────┼─────┼─────┼─────┤
//    │  0   │ 1 │ 2 │  3  │ kp_- │               │     │     │     │ no  │     │
//    ├──────┼───┼───┼─────┼──────┤               ├─────┼─────┼─────┼─────┼─────┤
//    │ kp_* │ 4 │ 5 │  6  │ kp_= │               │     │     │     │     │     │
//    └──────┴───┴───┼─────┼──────┼─────┐   ┌─────┼─────┼─────┼─────┴─────┴─────┘
//                   │     │      │     │   │     │ no  │ no  │
//                   └─────┴──────┴─────┘   └─────┴─────┴─────┘
[_NUM] = LAYOUT_default(
  KC_PSLS , KC_7 , KC_8 , KC_9    , KC_PPLS ,                         KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS,
  KC_0    , KC_1 , KC_2 , KC_3    , KC_PMNS ,                         KC_TRNS , KC_TRNS , KC_TRNS , KC_NO   , KC_TRNS,
  KC_PAST , KC_4 , KC_5 , KC_6    , KC_PEQL ,                         KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS , KC_TRNS,
                          KC_TRNS , KC_TRNS , KC_TRNS ,     KC_TRNS , KC_NO   , KC_NO
),

//    ┌─────┬─────┬─────┬─────┬─────┐              ┌───────┬──────┬───────────┬───────────┬─────────┐
//    │     │     │  :  │ esc │     │              │       │      │           │           │   del   │
//    ├─────┼─────┼─────┼─────┼─────┤              ├───────┼──────┼───────────┼───────────┼─────────┤
//    │     │  %  │  /  │ ent │     │              │ DF(1) │ lgui │           │           │         │
//    ├─────┼─────┼─────┼─────┼─────┤              ├───────┼──────┼───────────┼───────────┼─────────┤
//    │     │     │     │  !  │     │              │ DF(0) │      │ RALT_T(,) │ RCTL_T(.) │ QK_BOOT │
//    └─────┴─────┴─────┼─────┼─────┼────┐   ┌─────┼───────┼──────┼───────────┴───────────┴─────────┘
//                      │     │ tab │ no │   │     │  no   │  no  │
//                      └─────┴─────┴────┘   └─────┴───────┴──────┘
[_MISC] = LAYOUT_default(
  KC_TRNS , KC_TRNS , KC_COLN , KC_ESC  , KC_TRNS ,                       KC_TRNS , KC_TRNS , KC_TRNS         , KC_TRNS        , KC_DEL ,
  KC_TRNS , KC_PERC , KC_SLSH , KC_ENT  , KC_TRNS ,                       DF(1)   , KC_LGUI , KC_TRNS         , KC_TRNS        , KC_TRNS,
  KC_TRNS , KC_TRNS , KC_TRNS , KC_EXLM , KC_TRNS ,                       DF(0)   , KC_TRNS , RALT_T(KC_COMM) , RCTL_T(KC_DOT) , QK_BOOT,
                                KC_TRNS , KC_TAB  , KC_NO ,     KC_TRNS , KC_NO   , KC_NO
)
};

#ifdef OLED_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (!is_keyboard_master()) {
        return OLED_ROTATION_180;
    }

    return rotation;
}

static void render_logo(void) {
    static const char PROGMEM qmk_logo[] = {0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0x94, 0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4, 0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0x00};

    oled_write_P(qmk_logo, false);
}

bool oled_task_user(void) {
    render_logo();
    const char *layer_names[] = {
        [ _BASE ] = ">>> BASE ",
        [ _MOUS ] = ">>> MOUSE ",
        [ _NAV ] = ">>> NAVI ",
        [ _SYM ] = ">>> SYM",
        [ _BRC ] = ">>> BRC",
        [ _FUNC ] = ">>> FUNC ",
        [ _NUM ] = ">>> NUM",
        [ _MISC ] = ">>> MISC"
    };

    oled_write_P(PSTR(layer_names[get_highest_layer(layer_state)]), false);
    return false;
}
#endif /* ifdef OLED_ENABLE */

void keyboard_post_init_user(void) {
    global_user_config.raw = eeconfig_read_user();
    update_pointer_cpi(&global_user_config);
    write_config_to_eeprom(&global_user_config);
}

void pointing_device_init_user(void) {
    set_auto_mouse_layer(_MOUS);
    set_auto_mouse_enable(true);
}
