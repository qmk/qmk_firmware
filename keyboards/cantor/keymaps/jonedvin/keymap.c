// Copyright 2022 Diego Palacios (@diepala)
// SPDX-License-Identifier: GPL-2.0

#include QMK_KEYBOARD_H
#include "keymap_norwegian.h"


// Mac aliases
#define MAC_QUOT  NO_LABK       // '
#define MAC_PIPE  NO_LCBR       // |
#define MAC_ACUT  NO_BSLS       // ´
#define MAC_DLR   S(NO_4)       // $
#define MAC_LCBR  S(ALGR(NO_8)) // {
#define MAC_RCBR  S(ALGR(NO_9)) // {
#define MAC_PIPE  NO_LCBR       // |
#define MAC_LABK  NO_PIPE       // <
#define MAC_RABK  NO_SECT       // >
#define MAC_AT    NO_QUOT       // @
#define MAC_BSLS  S(ALGR(NO_7)) // (bachslash)
#define MAC_EUR   ALGR(NO_4)    // €
#define MAC_SECT  S(NO_LABK)    // §




enum layer_names {
    _NORSK_WIN = 0,
    _BASE_WIN,
    _SYM_WIN,
    _NAV_WIN,

    _NORSK_MAC,
    _BASE_MAC,
    _SYM_MAC,
    _NAV_MAC,

    _LAYER_SWITCH
};


enum custom_keycodes {
    QQ_WIN = SAFE_RANGE,
    QQ_MAC,
    BACK_DEL
};


bool send_shift_sensitive_code(keyrecord_t *record, bool shiftPressed, int normalCode, int shiftCode) {
    if (record->event.pressed) {
        if (shiftPressed) {
            // Get mods, delete mods, send character, set mods again
            del_mods(MOD_BIT(KC_LSFT));
            tap_code16(shiftCode);
            set_mods(MOD_BIT(KC_LSFT));
        } else {
            // If shift is not pressed, just send the normalCode
            tap_code16(normalCode);
        }
    }
    return false; // Skip all further processing of this key
}


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    bool shiftPressed = keyboard_report->mods & (MOD_BIT(KC_LSFT));
    bool altPressed   = keyboard_report->mods & (MOD_BIT(KC_LALT));
    bool optPressed   = keyboard_report->mods & (MOD_BIT(KC_LOPT));
    switch(keycode) {
        case QQ_WIN:
            return send_shift_sensitive_code(record, shiftPressed, NO_QUOT, NO_QUES);
        case QQ_MAC:
            return send_shift_sensitive_code(record, shiftPressed, MAC_QUOT, NO_QUES);
        case BACK_DEL:
            return send_shift_sensitive_code(record, shiftPressed || altPressed || optPressed, KC_BSPC, KC_DEL);
        default:
            return true; // Process all other keycodes normally
    }
}



const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    // Windows-specific
    [_NORSK_WIN] = LAYOUT_split_3x6_3(
        KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                               KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    NO_ARNG,
        KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                               KC_H,    KC_J,    KC_K,    KC_L,    NO_OSTR, NO_AE,
        MO(_LAYER_SWITCH),KC_Z,KC_X,KC_C,   KC_V,    KC_B,                               KC_N,    KC_M,    KC_COMM, KC_DOT,  BACK_DEL, KC_ENT,
                                            KC_LCTL, KC_SPC,  KC_LALT,           MO(_SYM_WIN), KC_LSFT, MO(_NAV_WIN)
    ),
    [_BASE_WIN] = LAYOUT_split_3x6_3(
        KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                               KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    BACK_DEL,
        KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                               KC_H,    KC_J,    KC_K,    KC_L,    QQ_WIN,  KC_ENT,
        MO(_LAYER_SWITCH),KC_Z,KC_X,KC_C,   KC_V,    KC_B,                               KC_N,    KC_M,    KC_COMM, KC_DOT,  NO_MINS, XXXXXXX,
                                            KC_LCTL, KC_SPC, KC_LALT,           MO(_SYM_WIN), KC_LSFT, MO(_NAV_WIN)
    ),
    [_SYM_WIN] = LAYOUT_split_3x6_3(
        NO_GRV,  NO_ACUT, NO_DQUO, KC_7,    KC_8,    KC_9,                               NO_LCBR, NO_RCBR, NO_BSLS, NO_EQL,  NO_PLUS, BACK_DEL,
        NO_LABK, NO_RABK, NO_EXLM, KC_4,    KC_5,    KC_6,                               NO_LPRN, NO_RPRN, NO_SLSH, NO_HASH, NO_ASTR, KC_ENT,
        NO_DIAE, NO_CIRC, KC_0,    KC_1,    KC_2,    KC_3,                               NO_LBRC, NO_RBRC, NO_PIPE, NO_PERC, NO_AT,   XXXXXXX,
                                            KC_LCTL, KC_SPC, KC_LALT,          XXXXXXX, KC_LSFT, XXXXXXX
    ),
    [_NAV_WIN] = LAYOUT_split_3x6_3(
        XXXXXXX, NO_OSTR, KC_F10,  KC_F7,   KC_F8,   KC_F9,                             NO_PND,   KC_HOME, KC_UP,   KC_END,  XXXXXXX, BACK_DEL,
        XXXXXXX, NO_ARNG, KC_F11,  KC_F4,   KC_F5,   KC_F6,                             NO_DLR,   KC_LEFT, KC_DOWN, KC_RIGHT,XXXXXXX, KC_ENT,
        XXXXXXX, NO_AE, KC_F12,  KC_F1,   KC_F2,   KC_F3,                             NO_EURO,  NO_TILD, NO_AMPR, NO_SECT, XXXXXXX, XXXXXXX,
                                            KC_LCTL, KC_SPC, XXXXXXX,          XXXXXXX, KC_LSFT, KC_LCTL
    ),



    // Mac-specific
    [_NORSK_MAC] = LAYOUT_split_3x6_3(
        KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                               KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    NO_ARNG,
        KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                               KC_H,    KC_J,    KC_K,    KC_L,    NO_OSTR, NO_AE,
        MO(_LAYER_SWITCH),KC_Z,KC_X,KC_C,   KC_V,    KC_B,                               KC_N,    KC_M,    KC_COMM, KC_DOT,  BACK_DEL, KC_ENT,
                                        KC_LEFT_GUI, KC_SPC,  KC_LOPT,       MO(_SYM_MAC), KC_LSFT, MO(_NAV_MAC)
    ),
    [_BASE_MAC] = LAYOUT_split_3x6_3(
        KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                               KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    BACK_DEL,
        KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                               KC_H,    KC_J,    KC_K,    KC_L,    QQ_MAC,  KC_ENT,
        MO(_LAYER_SWITCH),KC_Z,KC_X,KC_C,   KC_V,    KC_B,                               KC_N,    KC_M,    KC_COMM, KC_DOT,  NO_MINS, XXXXXXX,
                                        KC_LEFT_GUI, KC_SPC, KC_LOPT,        MO(_SYM_MAC), KC_LSFT, MO(_NAV_MAC)
    ),
    [_SYM_MAC] = LAYOUT_split_3x6_3(
        NO_GRV,  MAC_ACUT, NO_DQUO, KC_7,    KC_8,    KC_9,                              MAC_LCBR,MAC_RCBR,MAC_BSLS,NO_EQL,  NO_PLUS, BACK_DEL,
        MAC_LABK,MAC_RABK, NO_EXLM, KC_4,    KC_5,    KC_6,                              NO_LPRN, NO_RPRN, NO_SLSH, NO_HASH, NO_ASTR, KC_ENT,
        NO_DIAE, NO_CIRC,  KC_0,    KC_1,    KC_2,    KC_3,                              NO_LBRC, NO_RBRC, MAC_PIPE,NO_PERC, MAC_AT,  XXXXXXX,
                                        KC_LEFT_GUI, KC_SPC, KC_LOPT,          XXXXXXX, KC_LSFT, XXXXXXX
    ),
    [_NAV_MAC] = LAYOUT_split_3x6_3(
        XXXXXXX, NO_OSTR, KC_F10,  KC_F7,   KC_F8,   KC_F9,                             NO_PND,   KC_HOME, KC_UP,   KC_END,  XXXXXXX, BACK_DEL,
        XXXXXXX, NO_ARNG, KC_F11,  KC_F4,   KC_F5,   KC_F6,                             MAC_DLR,  KC_LEFT, KC_DOWN, KC_RIGHT,XXXXXXX, KC_ENT,
        XXXXXXX, NO_AE, KC_F12,  KC_F1,   KC_F2,   KC_F3,                             NO_EURO,  NO_TILD, NO_AMPR, NO_SECT, XXXXXXX, XXXXXXX,
                                            KC_LOPT, KC_SPC, XXXXXXX,          XXXXXXX, KC_LSFT, KC_LOPT
    ),



    // Base layer switch and windows key access
    [_LAYER_SWITCH] = LAYOUT_split_3x6_3(
        KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                               KC_Y,   KC_U,   KC_I,   KC_O,          KC_P,         XXXXXXX,
        KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                               KC_H,   KC_J,   KC_K,   KC_L,          _______,      DF(_NORSK_MAC),
        XXXXXXX, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                               KC_N,   KC_M,   _______,DF(_NORSK_WIN),DF(_BASE_WIN),DF(_BASE_MAC),
                                            KC_LCTL, KC_LGUI, KC_LALT,           MO(_SYM_WIN), KC_LSFT, MO(_NAV_WIN)
    )
};
