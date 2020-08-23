#include "planck.h"
#include "action_layer.h"

#define a KC_A
#define b KC_B
#define c KC_C
#define d KC_D
#define e KC_E
#define f KC_F
#define g KC_G
#define h KC_H
#define i KC_I
#define j KC_J
#define k KC_K
#define l KC_L
#define m KC_M
#define n KC_N
#define o KC_O
#define p KC_P
#define q KC_Q
#define r KC_R
#define s KC_S
#define t KC_T
#define u KC_U
#define v KC_V
#define w KC_W
#define x KC_X
#define y KC_Y
#define z KC_Z

#define lalt KC_LALT
#define lctl KC_LCTL
#define lsft KC_LSFT
#define ralt KC_RALT
#define rctl KC_RCTL
#define rsft KC_RSFT

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

#define ampr KC_AMPR
#define astr KC_ASTR
#define at KC_AT
#define bsls KC_BSLS
#define bspc KC_BSPC
#define caps KC_CAPS
#define circ KC_CIRC
#define comm KC_COMM
#define dash A(KC_MINS) // en-dash (–); or with shift: em-dash (—)
#define del KC_DEL
#define dlr KC_DLR
#define dot KC_DOT
#define ent KC_ENT
#define eql KC_EQL
#define esc KC_ESC
#define exlm KC_EXLM
#define grv KC_GRV
#define hash KC_HASH
#define lbrc KC_LBRC
#define lcbr KC_LCBR
#define lprn KC_LPRN
#define mins KC_MINS
#define perc KC_PERC
#define pipe KC_PIPE
#define plus KC_PLUS
#define quot KC_QUOT
#define rbrc KC_RBRC
#define rcbr KC_RCBR
#define rprn KC_RPRN
#define scln KC_SCLN
#define slsh KC_SLSH
#define spc KC_SPC
#define tab KC_TAB
#define tild KC_TILD

#define down KC_DOWN
#define home G(KC_LEFT)
#define end G(KC_RGHT)
#define up KC_UP
#define pgdn KC_PGDN
#define pgup KC_PGUP
#define left KC_LEFT
#define rght KC_RGHT

#define tabl G(S(KC_LBRC))
#define tabr G(S(KC_RBRC))
#define fwd G(KC_RBRC)
#define back G(KC_LBRC)
#define slup S(A(KC_UP))   // Previous unread in Slack
#define sldn S(A(KC_DOWN)) // Next unread in Slack

#define ctl1 C(KC_1) // Desktop 1 (6 with shift)
#define ctl2 C(KC_2) // Desktop 2 (7 with shift)
#define ctl3 C(KC_3) // Desktop 3 (8 with shift)
#define ctl4 C(KC_4) // Desktop 4 (9 with shift)
#define ctl5 C(KC_5) // Desktop 5 (10 with shift)
#define ctl6 C(KC_6) // Screenshot
#define ctl7 C(KC_7) // Brightness up
#define ctl8 C(KC_8) // Brightness down

#define f1 KC_F1
#define f2 KC_F2
#define f3 KC_F3
#define f4 KC_F4
#define f5 KC_F5
#define f6 KC_F6
#define f7 KC_F7
#define f8 KC_F8
#define f9 KC_F9
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
#define f20 KC_F20

#define mute KC_MUTE
#define next KC_MNXT
#define play KC_MPLY
#define prev KC_MPRV
#define vold KC_VOLD
#define volu KC_VOLU

#define symb MO(SYMB)
#define move MO(MOVE)
#define func MO(FUNC)

#define rset RESET
#define powr KC_POWER

#define ____ KC_TRNS
#define xxxx KC_NO

extern keymap_config_t keymap_config;

enum planck_layers {
    BASE,
    SYMB,
    MOVE,
    FUNC,
};

enum planck_keycodes {
    // Curly quotes
    lcqt = SAFE_RANGE,
    rcqt,

    // "Smart" mods
    cmd,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [BASE] = LAYOUT_planck_grid(
         tab,    q,    w,    f,    p,    g,    j,    l,    u,    y, scln, mins,
        bspc,    a,    r,    s,    t,    d,    h,    n,    e,    i,    o, quot,
        lsft,    z,    x,    c,    v,    b,    k,    m, comm,  dot, slsh, rsft,
        func, lctl, lalt,  cmd, move,  ent,  spc, symb,  cmd, ralt, rctl, func
    ),

    [SYMB] = LAYOUT_planck_grid(
         esc,   n7,   n5,   n3,   n1,   n9,   n8,   n0,   n2,   n4,   n6, dash,
        lcqt,   at,  dlr,  eql, lprn, lbrc, rbrc, rprn, astr, hash, plus, rcqt,
        ____,  grv, pipe, bsls, lcbr, tild, circ, rcbr, ampr, exlm, perc, ____,
        ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____
    ),

    [MOVE] = LAYOUT_planck_grid(
         esc, ctl1, ctl2, ctl3, ctl4, ctl5, ctl6, home,   up,  end, xxxx, xxxx,
         del, play, volu, tabl, tabr, slup, ctl7, left, down, rght, caps, xxxx,
        ____, mute, vold, back,  fwd, sldn, ctl8, pgdn, pgup, xxxx, xxxx, ____,
        ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____
    ),

    [FUNC] = LAYOUT_planck_grid(
        rset,   f7,   f5,   f3,   f1,   f9,   f8,  f10,   f2,   f4,   f6, xxxx,
        xxxx,  f17,  f15,  f13,  f11,  f19,  f18,  f20,  f12,  f14,  f16, xxxx,
        ____, xxxx, xxxx, xxxx, xxxx, xxxx, xxxx, xxxx, xxxx, xxxx, xxxx, ____,
        ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____
    ),
};

bool send_string_if_keydown(
        keyrecord_t *record,
        const char *unshifted,
        const char *shifted) {
    if (record->event.pressed) {
        if (shifted) {
            uint8_t shifts = get_mods() & MOD_MASK_SHIFT;
            if (shifts) {
                del_mods(shifts);
                send_string(shifted);
                add_mods(shifts);
            } else {
                send_string(unshifted);
            }
        } else {
            send_string(unshifted);
        }
    }
    return true;
}

// Holding both cmd keys will instead register as cmd + ctl
bool smart_cmd(keyrecord_t *record) {
    static int cmd_keys_down = 0;

    if (record->event.pressed) {
        if (cmd_keys_down == 0) {
            register_code(KC_LCMD);
        } else {
            register_code(KC_LCTL);
        }
        cmd_keys_down++;
    } else {
        if (cmd_keys_down == 1) {
            unregister_code(KC_LCMD);
        } else {
            unregister_code(KC_LCTL);
        }
        cmd_keys_down--;
    }
    return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        // The macOS shortcuts for curly quotes are horrible, so this rebinds
        // them so that shift toggles single–double instead of left–right, and
        // then both varieties of left quote can share one key, and both
        // varieties of right quote share another.
        case lcqt:
            return send_string_if_keydown(
                    record,
                    SS_LALT("]"),           // left single quote (‘)
                    SS_LALT("["));          // left double quote (“)
        case rcqt:
            return send_string_if_keydown(
                    record,
                    SS_LALT(SS_LSFT("]")),  // right single quote (’)
                    SS_LALT(SS_LSFT("["))); // right double quote (”)

        // cmd + cmd -> cmd + ctl
        case cmd:
            return smart_cmd(record);
    }
    return true;
}
