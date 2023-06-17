/* Copyright 2021 Sean Johnson
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
#include "muse.h"

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

#define lopt KC_LALT
#define lctl KC_LCTL
#define lsft KC_LSFT
#define ropt KC_RALT
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

#define bspc KC_BSPC
#define caps KC_CAPS
#define comm KC_COMM
#define dash A(KC_MINS)
#define scln KC_SCLN
#define slsh KC_SLSH
#define spc KC_SPC
#define tab KC_TAB
#define del KC_DEL
#define dot KC_DOT
#define ent KC_ENT
#define mins KC_MINS
#define quot KC_QUOT
#define esc KC_ESC
#define escg QK_GESC

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
#define dtl C(KC_LEFT)
#define dtr C(KC_RGHT)
#define slup S(A(KC_UP))
#define sldn S(A(KC_DOWN))

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

#define rset QK_BOOT
#define powr KC_PWR

#define ____ KC_TRNS
#define xxxx KC_NO

#define emji LCMD(LCTL(KC_SPC))
#define hypr OSM(MOD_HYPR)
#define brup KC_BRMU
#define brdn KC_BRMD
#define escf LT(FUNC,KC_ESC)

enum planck_layers {
    BASE,
    SYMB,
    MOVE,
    FUNC,
};

enum planck_keycodes {
    ampr = SAFE_RANGE,
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
    cmd,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [BASE] = LAYOUT_planck_grid(
         tab,    q,    w,    f,    p,    g,    j,    l,    u,    y, scln, mins,
        bspc,    a,    r,    s,    t,    d,    h,    n,    e,    i,    o, quot,
        lsft,    z,    x,    c,    v,    b,    k,    m, comm,  dot, slsh, rsft,
        hypr, lctl, lopt,  cmd, move,  ent,  spc, symb,  cmd, ropt, rctl, func
    ),

    [SYMB] = LAYOUT_planck_grid(
         esc,   n7,   n5,   n3,   n1,   n9,   n8,   n0,   n2,   n4,   n6, dash,
        bspc, lbrc, lcbr, lprn, hash, pipe, astr,  dlr, rprn, rcbr, rbrc,   at,
        ____,  grv, exlm, circ, tild, perc, ampr, plus, mins,  eql, bsls, ____,
        ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____
    ),

    [MOVE] = LAYOUT_planck_grid(
         esc, xxxx, slup,  dtl,  dtr, xxxx, xxxx, home,   up,  end, xxxx, ____,
         del, xxxx, sldn, tabl, tabr, xxxx, xxxx, left, down, rght, xxxx, ____,
        ____, xxxx, xxxx, back,  fwd, xxxx, xxxx, pgdn, pgup, xxxx, xxxx, ____,
        ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____
    ),

    [FUNC] = LAYOUT_planck_grid(
        rset,   f7,   f5,   f3,   f1,   f9,   f8,  f10,   f2,   f4,   f6, volu,
        powr,  f17,  f15,  f13,  f11,  f19,  f18,  f20,  f12,  f14,  f16, vold,
        brup, ____, xxxx, xxxx, xxxx, xxxx, xxxx, xxxx, xxxx, xxxx, xxxx, mute,
        brdn, caps, ____, ____, ____, ____, ____, ____, prev, next, play, ____
    ),
};


bool send_string_if_keydown(keyrecord_t *record, const char *s) {
    if (record->event.pressed) {
        send_string(s);
    }
    return true;
}

int cmd_keys_down = 0;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        // Override the default auto shifted symbols to use SEND_STRING See
        // https://github.com/qmk/qmk_firmware/issues/4072
        case ampr:
            return send_string_if_keydown(record, "&");
        case astr:
            return send_string_if_keydown(record, "*");
        case at:
            return send_string_if_keydown(record, "@");
        case bsls:
            return send_string_if_keydown(record, "\\");
        case circ:
            return send_string_if_keydown(record, "^");
        case dlr:
            return send_string_if_keydown(record, "$");
        case eql:
            return send_string_if_keydown(record, "=");
        case exlm:
            return send_string_if_keydown(record, "!");
        case grv:
            return send_string_if_keydown(record, "`");
        case hash:
            return send_string_if_keydown(record, "#");
        case lbrc:
            return send_string_if_keydown(record, "[");
        case lcbr:
            return send_string_if_keydown(record, "{");
        case lprn:
            return send_string_if_keydown(record, "(");
        case perc:
            return send_string_if_keydown(record, "%");
        case pipe:
            return send_string_if_keydown(record, "|");
        case plus:
            return send_string_if_keydown(record, "+");
        case rbrc:
            return send_string_if_keydown(record, "]");
        case rcbr:
            return send_string_if_keydown(record, "}");
        case rprn:
            return send_string_if_keydown(record, ")");
        case tild:
            return send_string_if_keydown(record, "~");

        // cmd + cmd -> cmd + ctl
        case cmd:
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
    return true;
}

