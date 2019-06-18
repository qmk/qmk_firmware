#include "planck.h"
#include "action_layer.h"

extern keymap_config_t keymap_config;

#define XXXX KC_NO
#define ____ KC_TRNS
#define a KC_A
#define b KC_B
#define back G(KC_LBRC)
#define bspc KC_BSPC
#define c KC_C
#define cTAB C(KC_TAB)
#define caps KC_CAPS
#define comm KC_COMM
#define d KC_D
#define dash A(KC_MINS)
#define del KC_DEL
#define dot KC_DOT
#define down KC_DOWN
#define e KC_E
#define e_ra RALT_T(KC_E)
#define end KC_END
#define ent KC_ENT
#define esc KC_ESC
#define f KC_F
#define f1 KC_F1
#define f10 KC_F10
#define f11 KC_F11
#define f12 KC_F12
#define f13 KC_F13
#define f14 KC_F14
#define f15 KC_F15
#define f16 KC_F16
#define f17 KC_F17
#define f18 KC_F18
#define f19 KC_F19
#define f2 KC_F2
#define f20 KC_F20
#define f21 KC_F21
#define f22 KC_F22
#define f23 KC_F23
#define f24 KC_F24
#define f3 KC_F3
#define f4 KC_F4
#define f5 KC_F5
#define f6 KC_F6
#define f7 KC_F7
#define f8 KC_F8
#define f9 KC_F9
#define fwd G(KC_RBRC)
#define g KC_G
#define gbp A(KC_3)
#define h KC_H
#define home KC_HOME
#define i KC_I
#define i_rc RCTL_T(KC_I)
#define j KC_J
#define k KC_K
#define l KC_L
#define lalt KC_LALT
#define lctl KC_LCTL
#define left KC_LEFT
#define lgui KC_LGUI
#define lsft KC_LSFT
#define m KC_M
#define mins KC_MINS
#define mute KC_MUTE
#define n KC_N
#define n0 KC_0
#define n1 KC_1
#define n2 KC_2
#define n3 KC_3
#define n4 KC_4
#define n5 KC_5
#define n6 KC_6
#define n7 KC_7
#define n8 KC_8
#define n9 KC_9
#define n_rg RGUI_T(KC_N)
#define next KC_MNXT
#define o KC_O
#define p KC_P
#define pgdn KC_PGDN
#define pgup KC_PGUP
#define play KC_MPLY
#define powr KC_POWER
#define prev KC_MPRV
#define q KC_Q
#define quot KC_QUOT
#define r KC_R
#define r_lc LCTL_T(KC_R)
#define ralt KC_RALT
#define rctl KC_RCTL
#define rght KC_RGHT
#define rgui KC_RGUI
#define rset RESET
#define rsft KC_RSFT
#define s KC_S
#define s_la LALT_T(KC_S)
#define scln KC_SCLN
#define sldn S(A(KC_DOWN))
#define slsh KC_SLSH
#define slup S(A(KC_UP))
#define spc KC_SPC
#define t KC_T
#define t_lg LGUI_T(KC_T)
#define tab KC_TAB
#define u KC_U
#define up KC_UP
#define v KC_V
#define vold KC_F11
#define volu KC_F12
#define w KC_W
#define x KC_X
#define y KC_Y
#define z KC_Z


enum planck_layers {
    _BASE,
    _SYMB,
    _MOVE,
    _FUNC,
};

enum planck_keycodes {
    SYMB = SAFE_RANGE,
    MOVE,
    FUNC,

    ampr,
    astr,
    at,
    bsls,
    circ,
    dlr,
    eql,
    exlm,
    grv,
    hash,
    lbrc,
    lcbr,
    lprn,
    perc,
    pipe,
    plus,
    rbrc,
    rcbr,
    rprn,
    tild,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT_planck_grid(
         tab,    q,    w,    f,    p,    g,    j,    l,    u,    y, scln, mins,
        bspc,    a, r_lc, s_la, t_lg,    d,    h, n_rg, e_ra, i_rc,    o, quot,
        lsft,    z,    x,    c,    v,    b,    k,    m, comm,  dot, slsh, rsft,
        XXXX, XXXX, XXXX, FUNC, MOVE,  ent,  spc, SYMB, FUNC, XXXX, XXXX, XXXX
    ),

    [_SYMB] = LAYOUT_planck_grid(
         esc,   n7,   n5,   n3,   n1,   n9,   n8,   n0,   n2,   n4,   n6, dash,
         del, bsls, hash, astr,  eql, pipe,   at, rprn, lprn,  dlr, ampr,  gbp,
        caps,  grv, exlm, lbrc, rbrc, circ, tild, rcbr, lcbr, plus, perc, caps,
        ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____
    ),

    [_MOVE] = LAYOUT_planck_grid(
         esc, XXXX, XXXX, XXXX, XXXX, XXXX, XXXX, home,   up,  end, XXXX, XXXX,
         del, XXXX, lctl, lalt, lgui, XXXX, XXXX, left, down, rght, XXXX, XXXX,
        ____, XXXX, XXXX, back,  fwd, XXXX, XXXX, pgdn, pgup, XXXX, XXXX, ____,
        ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____
    ),

    [_FUNC] = LAYOUT_planck_grid(
        rset,   f1,   f2,   f3,   f4,   f5,   f6,   f7,   f8,   f9,  f10, volu,
        powr,  f11,  f12,  f13,  f14,  f15,  f16,  f17,  f18,  f19,  f20, vold,
        ____, XXXX, XXXX, XXXX, XXXX, XXXX, XXXX, XXXX, XXXX, XXXX, XXXX, ____,
        ____, ____, ____, ____, prev, mute, play, next, ____, ____, ____, ____
    ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case SYMB:
            if (record->event.pressed) {
                layer_on(_SYMB);
            } else {
                layer_off(_SYMB);
            }
            return false;
        case MOVE:
            if (record->event.pressed) {
                layer_on(_MOVE);
            } else {
                layer_off(_MOVE);
            }
            return false;
        case FUNC:
            if (record->event.pressed) {
                layer_on(_FUNC);
            } else {
                layer_off(_FUNC);
            }
            return false;

        // Override the defualt auto shifted symbols to use SEND_STRING
        // See https://github.com/qmk/qmk_firmware/issues/4072
        case exlm:
            if (record->event.pressed) { SEND_STRING("!"); }
            return false;
        case at:
            if (record->event.pressed) { SEND_STRING("@"); }
            return false;
        case hash:
            if (record->event.pressed) { SEND_STRING("#"); }
            return false;
        case dlr:
            if (record->event.pressed) { SEND_STRING("$"); }
            return false;
        case perc:
            if (record->event.pressed) { SEND_STRING("%"); }
            return false;
        case circ:
            if (record->event.pressed) { SEND_STRING("^"); }
            return false;
        case ampr:
            if (record->event.pressed) { SEND_STRING("&"); }
            return false;
        case astr:
            if (record->event.pressed) { SEND_STRING("*"); }
            return false;
        case lprn:
            if (record->event.pressed) { SEND_STRING("("); }
            return false;
        case rprn:
            if (record->event.pressed) { SEND_STRING(")"); }
            return false;
        case tild:
            if (record->event.pressed) { SEND_STRING("~"); }
            return false;
        case grv:
            if (record->event.pressed) { SEND_STRING("`"); }
            return false;
        case plus:
            if (record->event.pressed) { SEND_STRING("+"); }
            return false;
        case eql:
            if (record->event.pressed) { SEND_STRING("="); }
            return false;
        case pipe:
            if (record->event.pressed) { SEND_STRING("|"); }
            return false;
        case bsls:
            if (record->event.pressed) { SEND_STRING("\\"); }
            return false;
        case lbrc:
            if (record->event.pressed) { SEND_STRING("["); }
            return false;
        case rbrc:
            if (record->event.pressed) { SEND_STRING("]"); }
            return false;
        case lcbr:
            if (record->event.pressed) { SEND_STRING("{"); }
            return false;
        case rcbr:
            if (record->event.pressed) { SEND_STRING("}"); }
            return false;
    }
    return true;
}
