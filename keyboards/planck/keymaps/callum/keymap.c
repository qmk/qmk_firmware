#include "planck.h"
#include "action_layer.h"

extern keymap_config_t keymap_config;

#define ____ KC_TRNS
#define a LSFT_T(KC_A)
#define astr TD(_astr)
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
#define dlr TD(_dlr)
#define dot KC_DOT
#define down KC_DOWN
#define e RALT_T(KC_E)
#define end KC_END
#define ent KC_ENT
#define eql TD(_eql)
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
#define func MO(FUNC)
#define fwd G(KC_RBRC)
#define g KC_G
#define gbp A(KC_3)
#define h KC_H
#define hash TD(_hash)
#define home KC_HOME
#define i RCTL_T(KC_I)
#define j KC_J
#define k KC_K
#define l KC_L
#define lalt KC_LALT
#define lctl KC_LCTL
#define left KC_LEFT
#define lgui KC_LGUI
#define lprn TD(_lprn)
#define lsft KC_LSFT
#define m KC_M
#define mins KC_MINS
#define move MO(MOVE)
#define mute KC_MUTE
#define n RGUI_T(KC_N)
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
#define next KC_MNXT
#define o LSFT_T(KC_O)
#define p KC_P
#define pgdn KC_PGDN
#define pgup KC_PGUP
#define play KC_MPLY
#define powr KC_POWER
#define prev KC_MPRV
#define q KC_Q
#define quot KC_QUOT
#define r LCTL_T(KC_R)
#define ralt KC_RALT
#define rctl KC_RCTL
#define rght KC_RGHT
#define rgui KC_RGUI
#define rprn TD(_rprn)
#define rset RESET
#define rsft KC_RSFT
#define s LALT_T(KC_S)
#define scln KC_SCLN
#define sldn S(A(KC_DOWN))
#define slsh KC_SLSH
#define slup S(A(KC_UP))
#define spc KC_SPC
#define symb MO(SYMB)
#define t LGUI_T(KC_T)
#define tab KC_TAB
#define tabl S(C(KC_TAB))
#define tabr C(KC_TAB)
#define u KC_U
#define up KC_UP
#define v KC_V
#define vold KC_F11
#define volu KC_F12
#define w KC_W
#define x KC_X
#define xxxx KC_NO
#define y KC_Y
#define z KC_Z

enum planck_layers {
    BASE,
    SYMB,
    MOVE,
    FUNC,
};

enum planck_keycodes {
    ampr = SAFE_RANGE,
    at,
    bsls,
    circ,
    exlm,
    grv,
    lbrc,
    lcbr,
    perc,
    pipe,
    plus,
    rbrc,
    rcbr,
    tild,
};

enum td_keycodes {
    _hash,
    _astr,
    _eql,
    _rprn,
    _lprn,
    _dlr,
};

typedef enum {
  SINGLE_TAP,
  SINGLE_HOLD,
  DOUBLE_SINGLE_TAP,
} td_state_t;

static td_state_t td_state;

int cur_dance (qk_tap_dance_state_t *state);

void hash_finished(qk_tap_dance_state_t *state, void *user_data);
void hash_reset(qk_tap_dance_state_t *state, void *user_data);
void astr_finished(qk_tap_dance_state_t *state, void *user_data);
void astr_reset(qk_tap_dance_state_t *state, void *user_data);
void eql_finished(qk_tap_dance_state_t *state, void *user_data);
void eql_reset(qk_tap_dance_state_t *state, void *user_data);
void rprn_finished (qk_tap_dance_state_t *state, void *user_data);
void rprn_reset(qk_tap_dance_state_t *state, void *user_data);
void lprn_finished(qk_tap_dance_state_t *state, void *user_data);
void lprn_reset(qk_tap_dance_state_t *state, void *user_data);
void dlr_finished(qk_tap_dance_state_t *state, void *user_data);
void dlr_reset(qk_tap_dance_state_t *state, void *user_data);

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [BASE] = LAYOUT_planck_grid(
         tab,    q,    w,    f,    p,    g,    j,    l,    u,    y, scln, mins,
        bspc,    a,    r,    s,    t,    d,    h,    n,    e,    i,    o, quot,
        lsft,    z,    x,    c,    v,    b,    k,    m, comm,  dot, slsh, rsft,
        xxxx, xxxx, xxxx, func, move,  ent,  spc, symb, func, xxxx, xxxx, xxxx
    ),

    [SYMB] = LAYOUT_planck_grid(
         esc,   n7,   n5,   n3,   n1,   n9,   n8,   n0,   n2,   n4,   n6, dash,
         del, bsls, hash, astr,  eql, pipe,   at, rprn, lprn,  dlr, ampr,  gbp,
        caps,  grv, exlm, lbrc, rbrc, circ, tild, rcbr, lcbr, plus, perc, caps,
        ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____
    ),

    [MOVE] = LAYOUT_planck_grid(
         esc, xxxx, xxxx, tabl, tabr, xxxx, xxxx, home,   up,  end, xxxx, xxxx,
         del, lsft, lctl, lalt, lgui, xxxx, xxxx, left, down, rght, xxxx, xxxx,
        ____, xxxx, xxxx, back,  fwd, xxxx, xxxx, pgdn, pgup, xxxx, xxxx, ____,
        ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____
    ),

    [FUNC] = LAYOUT_planck_grid(
        rset,   f1,   f2,   f3,   f4,   f5,   f6,   f7,   f8,   f9,  f10, volu,
        powr,  f11,  f12,  f13,  f14,  f15,  f16,  f17,  f18,  f19,  f20, vold,
        ____, xxxx, xxxx, xxxx, xxxx, xxxx, xxxx, play, next, prev, mute, ____,
        ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____
    ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        // Override the defualt auto shifted symbols to use SEND_STRING
        // See https://github.com/qmk/qmk_firmware/issues/4072
        case exlm:
            if (record->event.pressed) { SEND_STRING("!"); }
            return false;
        case at:
            if (record->event.pressed) { SEND_STRING("@"); }
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
        case tild:
            if (record->event.pressed) { SEND_STRING("~"); }
            return false;
        case grv:
            if (record->event.pressed) { SEND_STRING("`"); }
            return false;
        case plus:
            if (record->event.pressed) { SEND_STRING("+"); }
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

int cur_dance(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) {
            return SINGLE_TAP;
        } else {
            return SINGLE_HOLD;
        }
    } else if (state->count == 2) {
        return DOUBLE_SINGLE_TAP;
    } else {
        return 3;
    }
}

void hash_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case SINGLE_TAP:
            SEND_STRING("#");
            break;
        case SINGLE_HOLD:
            register_mods(MOD_BIT(KC_LCTL));
            break;
        case DOUBLE_SINGLE_TAP:
            SEND_STRING("##");
            break;
    }
}

void hash_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case SINGLE_TAP:
            break;
        case SINGLE_HOLD:
            unregister_mods(MOD_BIT(KC_LCTL));
            break;
        case DOUBLE_SINGLE_TAP:
            break;
    }
}

void astr_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case SINGLE_TAP:
            SEND_STRING("*");
            break;
        case SINGLE_HOLD:
            register_mods(MOD_BIT(KC_LALT));
            break;
        case DOUBLE_SINGLE_TAP:
            SEND_STRING("**");
            break;
    }
}

void astr_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case SINGLE_TAP:
            break;
        case SINGLE_HOLD:
            unregister_mods(MOD_BIT(KC_LALT));
            break;
        case DOUBLE_SINGLE_TAP:
            break;
    }
}

void eql_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case SINGLE_TAP:
            SEND_STRING("=");
            break;
        case SINGLE_HOLD:
            register_mods(MOD_BIT(KC_LGUI));
            break;
        case DOUBLE_SINGLE_TAP:
            SEND_STRING("==");
            break;
    }
}

void eql_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case SINGLE_TAP:
            break;
        case SINGLE_HOLD:
            unregister_mods(MOD_BIT(KC_LGUI));
            break;
        case DOUBLE_SINGLE_TAP:
            break;
    }
}

void rprn_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case SINGLE_TAP:
            SEND_STRING(")");
            break;
        case SINGLE_HOLD:
            register_mods(MOD_BIT(KC_RGUI));
            break;
        case DOUBLE_SINGLE_TAP:
            SEND_STRING("))");
            break;
    }
}

void rprn_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case SINGLE_TAP:
            break;
        case SINGLE_HOLD:
            unregister_mods(MOD_BIT(KC_RGUI));
            break;
        case DOUBLE_SINGLE_TAP:
            break;
    }
}

void lprn_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case SINGLE_TAP:
            SEND_STRING("(");
            break;
        case SINGLE_HOLD:
            register_mods(MOD_BIT(KC_RALT));
            break;
        case DOUBLE_SINGLE_TAP:
            SEND_STRING("((");
            break;
    }
}

void lprn_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case SINGLE_TAP:
            break;
        case SINGLE_HOLD:
            unregister_mods(MOD_BIT(KC_RALT));
            break;
        case DOUBLE_SINGLE_TAP:
            break;
    }
}

void dlr_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case SINGLE_TAP:
            SEND_STRING("$");
            break;
        case SINGLE_HOLD:
            register_mods(MOD_BIT(KC_RCTL));
            break;
        case DOUBLE_SINGLE_TAP:
            SEND_STRING("$$");
            break;
    }
}

void dlr_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case SINGLE_TAP:
            break;
        case SINGLE_HOLD:
            unregister_mods(MOD_BIT(KC_RCTL));
            break;
        case DOUBLE_SINGLE_TAP:
            break;
    }
}

qk_tap_dance_action_t tap_dance_actions[] = {
    [_hash] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, hash_finished, hash_reset),
    [_astr] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, astr_finished, astr_reset),
    [_eql] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, eql_finished, eql_reset),
    [_rprn] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, rprn_finished, rprn_reset),
    [_lprn] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, lprn_finished, lprn_reset),
    [_dlr] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dlr_finished, dlr_reset),
};
