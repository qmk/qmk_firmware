// Copyright (C) 2019 ,2020  Keyboard.io ,Inc
//
// Ruud Wijtvliet
// TODO:
// . toggle to layer on three-key combo
// . prevent rolling errors
//
// good tutorial:
// https://precondition.github.io/home-row-mods


#include QMK_KEYBOARD_H

// enums
enum layer_names {
    L_BASE,
    L_BASE2,
    L_SYM,
    L_NUM,
    L_NAV,
    L_NAV2,
    L_FUN,
    L_FUN2,
    L_MOUSE,
    L_GAME,
};
enum custom_keycodes {
    rPW = SAFE_RANGE,
};

// aliases
//#define KC_VOLD  KC_KB_VOLUME_DOWN
//#define KC_VOLU  KC_KB_VOLUME_UP
#define ___f___  _______ // transparent by design; must remain empty e.g. to capture underlying layer keys
#define ___o___  _______ // transparent but may optionally be filled; no reason to be empty
// layer switching
#define lKC_DOT  LT(L_SYM, KC_DOT)
#define lKC_P    LT(L_NUM, KC_P)
#define lKC_Y    LT(L_FUN, KC_Y)
#define lKC_G    LT(L_FUN, KC_G)
#define lKC_C    LT(L_SYM, KC_C)
#define lKC_I    LT(L_FUN2, KC_I)
#define lKC_K    LT(L_MOUSE, KC_K)
#define lKC_M    LT(L_MOUSE, KC_M)
#define lNAV     MO(L_NAV)
#define lNAV2    MO(L_NAV2)
#define lGAME    TO(L_GAME)
// mods
// . base
#define mKC_A    MT(MOD_LGUI, KC_A)
#define mKC_O    MT(MOD_LSFT, KC_O)
#define mKC_E    MT(MOD_LCTL, KC_E)
#define mKC_U    MT(MOD_LALT, KC_U)
#define mKC_H    MT(MOD_LALT, KC_H)
#define mKC_T    MT(MOD_LCTL, KC_T)
#define mKC_N    MT(MOD_LSFT, KC_N)
#define mKC_S    MT(MOD_LGUI, KC_S)
// . symbol
#define mKC_AT   MT(MOD_LGUI, KC_AT)
#define mKC_QUES MT(MOD_LSFT, KC_QUES)
#define mKC_PERC MT(MOD_LCTL, KC_PERC)
#define mKC_EXLM MT(MOD_LALT, KC_EXLM)
#define mKC_LPRN MT(MOD_LALT, KC_LPRN)
#define mKC_RPRN MT(MOD_LCTL, KC_RPRN)
#define mKC_EQL  MT(MOD_LSFT, KC_EQL)
#define mKC_UNDS MT(MOD_LGUI, KC_UNDS)

#define mKC_SPC  MT(MOD_LALT | MOD_LCTL | MOD_LGUI, KC_SPC)
// special functions
#define fCUT    LCTL(KC_X)
#define fCOPY   LCTL(KC_C)
#define fPASTE  LCTL(KC_V)



const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[L_BASE] = LAYOUT( /* Dvorak */
    KC_QUOT   ,KC_COMM   ,lKC_DOT   ,lKC_P     ,lKC_Y     ,                      KC_F      ,lKC_G     ,lKC_C     ,KC_R      ,KC_L      ,
    mKC_A     ,mKC_O     ,mKC_E     ,mKC_U     ,lKC_I     ,                      KC_D      ,mKC_H     ,mKC_T     ,mKC_N     ,mKC_S     ,
    KC_SCLN   ,KC_Q      ,KC_J      ,lKC_K     ,KC_X      ,KC_VOLD   ,KC_VOLU   ,KC_B      ,lKC_M     ,KC_W      ,KC_V      ,KC_Z      ,
    KC_ESC    ,___o___   ,lNAV2     ,lNAV      ,mKC_SPC   ,KC_LCTL   ,KC_LSFT   ,KC_BSPC   ,KC_TAB    ,___o___   ,___o___   ,KC_ENT
),
[L_BASE2] = LAYOUT( /* Dvorak without modifiers. Never switched to, just as base for the combos*/
    KC_QUOT   ,KC_COMM   ,KC_DOT    ,KC_P      ,KC_Y     ,                      KC_F      ,KC_G      ,KC_C      ,KC_R      ,KC_L      ,
    KC_A      ,KC_O      ,KC_E      ,KC_U      ,KC_I     ,                      KC_D      ,KC_H      ,KC_T      ,KC_N      ,KC_S      ,
    KC_SCLN   ,KC_Q      ,KC_J      ,KC_K      ,KC_X     ,XXXXXXX   ,XXXXXXX   ,KC_B      ,KC_M      ,KC_W      ,KC_V      ,KC_Z      ,
    XXXXXXX   ,XXXXXXX   ,XXXXXXX   ,XXXXXXX   ,XXXXXXX  ,XXXXXXX   ,XXXXXXX   ,XXXXXXX   ,XXXXXXX   ,XXXXXXX   ,XXXXXXX   ,XXXXXXX
),
[L_SYM] = LAYOUT(
/*  `          ~          #          $          ^                                &          [          ]          \          /         */
    KC_GRV    ,KC_TILD   ,KC_HASH   ,KC_DLR    ,KC_CIRC   ,                      KC_AMPR   ,KC_LBRC   ,KC_RBRC   ,KC_BSLS   ,KC_SLSH   ,
/*  @          ?          %          !          /                                -          (          )          =          _         */
/*  mKC_AT    ,mKC_QUES  ,mKC_PERC  ,mKC_EXLM  ,KC_SLSH   ,                      KC_MINS   ,mKC_LPRN  ,mKC_RPRN  ,mKC_EQL   ,mKC_UNDS  , */
    KC_AT     ,KC_QUES   ,KC_PERC   ,KC_EXLM   ,XXXXXXX   ,                      KC_MINS   ,KC_LPRN   ,KC_RPRN   ,KC_EQL    ,KC_UNDS  ,
/*                                              *                                +          {          }          |          *         */
    XXXXXXX   ,XXXXXXX   ,XXXXXXX   ,XXXXXXX   ,XXXXXXX   ,___f___   ,___f___   ,KC_PLUS   ,KC_LCBR   ,KC_RCBR   ,KC_PIPE   ,KC_ASTR   ,
    ___f___   ,_______   ,_______   ,TO(L_BASE),___f___   ,_______   ,_______   ,___f___   ,___f___   ,_______   ,_______   ,___f___
),
[L_NUM] = LAYOUT(
    XXXXXXX   ,rPW       ,KC_DOT    ,___f___   ,XXXXXXX   ,                      KC_0      ,KC_1      ,KC_2      ,KC_3      ,KC_SLSH   ,
    XXXXXXX   ,XXXXXXX   ,KC_PERC   ,XXXXXXX   ,XXXXXXX   ,                      KC_MINUS  ,KC_4      ,KC_5      ,KC_6      ,KC_UNDS   ,
    KC_COLN   ,XXXXXXX   ,XXXXXXX   ,XXXXXXX   ,XXXXXXX   ,_______   ,_______   ,KC_PLUS   ,KC_7      ,KC_8      ,KC_9      ,KC_ASTR   ,
    ___f___   ,_______   ,_______   ,TO(L_BASE),___f___   ,_______   ,_______   ,_______   ,_______   ,_______   ,_______   ,___f___
),
[L_NAV] = LAYOUT(
    KC_HOME   ,KC_PGUP   ,KC_PGDN   ,KC_END    ,fCOPY     ,                      fCOPY     ,KC_HOME   ,KC_PGUP   ,KC_PGDN   ,KC_END    ,
    KC_LGUI   ,KC_LSFT   ,KC_LCTL   ,KC_LALT   ,fPASTE    ,                      fPASTE    ,KC_LEFT   ,KC_UP     ,KC_DOWN   ,KC_RGHT   ,
    KC_BTN1   ,KC_BTN2   ,XXXXXXX   ,KC_DEL    ,fCUT      ,KC_MPRV   ,KC_MNXT   ,fCUT      ,KC_DEL    ,KC_INS    ,KC_CAPS   ,KC_SCRL   ,
    ___f___   ,_______   ,_______   ,TO(L_BASE),___f___   ,_______   ,_______   ,___f___   ,_______   ,_______   ,_______   ,___f___
),
[L_NAV2] = LAYOUT(
    C(KC_HOME),C(KC_PGUP),C(KC_PGDN),C(KC_END) ,fCOPY     ,                      fCOPY     ,C(KC_HOME),C(KC_PGUP),C(KC_PGDN),C(KC_END) ,
    KC_LGUI   ,KC_LSFT   ,KC_LCTL   ,KC_LALT   ,fPASTE    ,                      fPASTE    ,C(KC_LEFT),C(KC_UP)  ,C(KC_DOWN),C(KC_RGHT),
    KC_BTN1   ,KC_BTN2   ,XXXXXXX   ,C(KC_DEL) ,fCUT      ,KC_MUTE   ,KC_MPLY   ,fCUT      ,C(KC_DEL) ,KC_INS    ,KC_CAPS   ,KC_SCRL   ,
    ___f___   ,_______   ,_______   ,TO(L_BASE),C(KC_SPC) ,_______   ,_______   ,C(KC_BSPC),_______   ,_______   ,_______   ,C(KC_ENT)
),
[L_FUN] = LAYOUT(
    KC_F1     ,KC_F2     ,KC_F3     ,KC_F4     ,___f___   ,                      XXXXXXX   ,___f___   ,KC_LALT   ,XXXXXXX   ,XXXXXXX   ,
    KC_F5     ,KC_F6     ,KC_F7     ,KC_F8     ,KC_LALT   ,                      XXXXXXX   ,XXXXXXX   ,KC_LCTL   ,KC_LSFT   ,XXXXXXX   ,
    KC_F9     ,KC_F10    ,KC_F11    ,KC_F12    ,XXXXXXX   ,_______   ,_______   ,XXXXXXX   ,XXXXXXX   ,XXXXXXX   ,XXXXXXX   ,XXXXXXX   ,
    ___f___   ,_______   ,_______   ,TO(L_BASE),___f___   ,_______   ,_______   ,___f___   ,___f___   ,_______   ,_______   ,_______
),
[L_FUN2] = LAYOUT(
    A(KC_F1)  ,A(KC_F2)  ,A(KC_F3)  ,A(KC_F4)  ,___f___   ,                      _______   ,___f___   ,_______   ,_______   ,_______   ,
    A(KC_F5)  ,A(KC_F6)  ,A(KC_F7)  ,A(KC_F8)  ,___f___   ,                      _______   ,_______   ,KC_LCTL   ,KC_LSFT   ,_______   ,
    A(KC_F9)  ,A(KC_F10) ,A(KC_F11) ,A(KC_F12) ,_______   ,_______   ,_______   ,_______   ,_______   ,_______   ,_______   ,_______   ,
    ___f___   ,_______   ,_______   ,TO(L_BASE),___f___   ,_______   ,_______   ,_______   ,_______   ,_______   ,_______   ,_______
),
[L_MOUSE] = LAYOUT(
    RESET     ,KC_BTN1   ,KC_MS_U   ,KC_BTN2   ,XXXXXXX   ,                      XXXXXXX   ,KC_BTN1   ,KC_MS_U   ,KC_BTN2   ,lGAME     ,
    XXXXXXX   ,KC_MS_L   ,KC_MS_D   ,KC_MS_R   ,XXXXXXX   ,                      XXXXXXX   ,KC_MS_L   ,KC_MS_D   ,KC_MS_R   ,XXXXXXX   ,
    XXXXXXX   ,KC_ACL0   ,KC_ACL1   ,KC_ACL2   ,XXXXXXX   ,_______   ,_______   ,XXXXXXX   ,KC_ACL2   ,KC_ACL1   ,KC_ACL0   ,XXXXXXX   ,
    ___f___   ,_______   ,_______   ,TO(L_BASE),___f___   ,_______   ,_______   ,_______   ,_______   ,_______   ,_______   ,_______
),
[L_GAME] = LAYOUT(
    KC_Q      ,KC_W      ,KC_E      ,KC_R      ,KC_T      ,                      KC_Y      ,KC_U      ,KC_I      ,KC_O      ,KC_P      ,
    KC_A      ,KC_S      ,KC_D      ,KC_F      ,KC_G      ,                      KC_H      ,KC_J      ,KC_K      ,KC_L      ,KC_SCLN   ,
    KC_Z      ,KC_X      ,KC_C      ,KC_V      ,KC_B      ,_______   ,_______   ,KC_N      ,KC_M      ,KC_UP     ,KC_DOT    ,KC_SLSH   ,
    ___o___   ,KC_LSFT   ,_______   ,TO(L_BASE),___o___   ,_______   ,_______   ,___o___   ,KC_LEFT   ,KC_DOWN   ,KC_RGHT   ,___o___
)/*,
[L_TEMPLATE] = LAYOUT(
    _______   ,_______   ,_______   ,_______   ,_______   ,                      _______   ,_______   ,_______   ,_______   ,_______   ,
    _______   ,_______   ,_______   ,_______   ,_______   ,                      _______   ,_______   ,_______   ,_______   ,_______   ,
    _______   ,_______   ,_______   ,_______   ,_______   ,_______   ,_______   ,_______   ,_______   ,_______   ,_______   ,_______   ,
    _______   ,_______   ,_______   ,_______   ,_______   ,_______   ,_______   ,_______   ,_______   ,_______   ,_______   ,_______
)*/
};


bool process_record_user(uint16_t keycode  , keyrecord_t *record) {
  switch (keycode) {
    case rPW:
    if (record->event.pressed) {
      SEND_STRING("Ammm1mmm2mmm3mmm");
    }
    break;
  }
  return true;
}


// combos. rest in combos.def
#include "g/keymap_combo.h"
