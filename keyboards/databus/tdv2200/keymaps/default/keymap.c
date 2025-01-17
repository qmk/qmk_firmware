// Created/amended by OleVoip 2024.
// SPDX-License-Identifier: GPL-2.0-or-later

#include "keymap_german.h"
#include "../../../databus.h"
#include "keymap.h"

#define k(key) DE_##key // change prefix according to host keymap
#define s(key) S(KC_##key)

#define X       KC_NO
#define MO_SFT  MO(KM_SHIFT)

// clang-format off

FCONST uint16_t keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
// ┌───────────────────────────────────────────────────────────────────────────────────────────────────────┐
// │    0   1   2   3   4   5   6   7   8   9  10  11  12  13  14       47  48  49  50  51  52  53  54     │
// │   ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬─────┐ ┌───┬───┬───┐   ┌───┬───┬───┬───┐   │
// │ G │ESC│F1 │F2 │F3 │F4 │F5 │F6 │F7 │F8 │F9 │F10│F11│F12│   │     │ │PRT│SCR│PAU│   │   │   │   │BT │ G │
// │   └───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴─────┘ ├───┼───┼───┤   ├───┼───┼───┼───┤   │
// │ F                                                                 │   │   │   │   │   │   │   │   │ F │
// │   ┌─────┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐ ├───┼───┼───┤   ├───┼───┼───┼───┤   │
// │ E │ CAPS│ 1!│ 2"│ 3#│ 4$│ 5%│ 6&│ 7'│ 8(│ 9)│ 0_│ -=│ ^~│BS │DEL│ │INS│   │   │   │NUM│SLS│AST│MNS│ E │
// │   ├───┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┤ ├───┼───┼───┤   ├───┼───┼───┼───┤   │
// │ D │ALT│TAB│ Q │ W │ E │ R │ T │ Y │ U │ I │ O │ P │ @ │ [{│ALTGR│ │PUP│UP │PDN│   │ 7 │ 8 │ 9 │PLS│ D │
// │   ├───┼───┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴───┴┬──┴┬──┴┬──┴┬──┴─┬───┤ ├───┼───┼───┤   ├───┼───┼───┼───┤   │
// │ C │CTL│LOCK│ A │ S │ D │ F │ G │ H │ J │ K │ L │ ;+│ :*│ ]} │   │ │LFT│DN │RGT│   │ 5 │ 6 │ 7 │   │ C │
// │   ├───┴──┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┤RET│ ├───┼───┼───┤   ├───┼───┼───┼───┤   │
// │ B │ SHIFT│ \|│ Z │ X │ C │ V │ B │ N │ M │ ,<│ .>│ /?│SHIFT │   │ │HOM│   │END│   │ 1 │ 2 │ 3 │   │ B │
// │   └──────┴───┴───┼───┴───┴───┴───┴───┴───┴───┴───┼───┴─┬───┬┴──┬┘ ├───┼───┼───┤   ├───┴───┼───┤ENT│   │
// │ A      \    \    │              SPC              │  \             │   │   │   │   │   0   │ . │   │ A │
// │                  └───────────────────────────────┘     └ ─ ┴ ─ ┘  └───┴───┴───┘   └───────┴───┴───┘   │
// │         99   0   1   2   3   4   5   6   7   8   9   10   11  12   47  48  49  50  51  52  53  54     │
// └───────────────────────────────────────────────────────────────────────────────────────────────────────┘
// 99   00      01    02    03     04    05    06    07     08      09     10      11      12      13      14    |47      48      49     |51     52      53      54
    [KM_DEFAULT] = LAYOUT_full(
        KC_ESC, KC_F1,KC_F2,KC_F3, KC_F4,KC_F5,KC_F6,KC_F7, KC_F8,  KC_F9, KC_F10, KC_F11, KC_F12, X, QK_MACRO_0, KC_PSCR,KC_SCRL,KC_PAUS,X,     X,      X,      X,       // G
                                                                                                                  X,      X,      X,      X,     X,      X,      X,       // F
        CW_TOGG,k(1), k(2), k(3),  k(4), k(5), k(6), k(7),  k(8),   k(9),  k(0),   k(MINS),k(CIRC),KC_BSPC,KC_DEL,KC_INS, KC_HOME,KC_PGUP,KC_NUM,KC_PSLS,KC_PAST,KC_PMNS, // E
KC_LALT,KC_TAB, k(Q), k(W), k(E),  k(R), k(T), k(Z), k(U),  k(I),   k(O),  k(P),   k(AT),  k(LBRC),KC_RALT,       KC_PGUP,KC_UP,  KC_PGDN,KC_P7, KC_P8,  KC_P9,  KC_PPLS, // D
KC_LCTL,KC_CAPS,k(A), k(S), k(D),  k(F), k(G), k(H), k(J),  k(K),   k(L),  k(SCLN),k(COLN),k(RBRC),KC_ENT,        KC_LEFT,KC_DOWN,KC_RGHT,KC_P4, KC_P5,  KC_P6,  X,       // C
MO_SFT ,k(BSLS),k(Y), k(X), k(C),  k(V), k(B), k(N), k(M), k(COMM), k(DOT),k(SLSH),MO_SFT,                        KC_HOME,X,      KC_END, KC_P1, KC_P2,  KC_P3,  KC_PENT, // B
                                         KC_SPC,                                   KC_NO,  KC_NO,                 X,      X,      X,      KC_P0,         KC_PDOT ),       // A
    [KM_SHIFT] = LAYOUT_full(
        s(ESC),s(F1), s(1), s(F3), s(F4),s(F5),s(F6),s(F7), s(F8),  s(F9), s(F10), s(F11), s(F12), X,      X,     s(PSCR),s(SCRL),s(PAUS),X,     X,      X,      QK_BOOT, // G
                                                                                                                  X,      X,      X,      X,     X,      X,      X,       // F
        _______,s(1), s(2),k(HASH),s(4), s(5), s(6),k(QUOT),s(8),   s(9),  k(UNDS),k(EQL), k(TILD),s(BSPC),s(DEL),s(INS), s(HOME),s(PGUP),s(NUM),s(PSLS),s(PAST),s(PMNS), // E
s(LALT),s(TAB), s(Q), s(W), s(E),  s(R), s(T), s(Z), s(U),  s(I),   s(O),  s(P),   k(GRV), k(LCBR),s(RALT),       s(PGUP),s(UP),  s(PGDN),s(P7), s(P8),  s(P9),  s(PPLS), // D
s(LCTL),s(CAPS),s(A), s(S), s(D),  s(F), s(G), s(H), s(J),  s(K),   s(L),  k(PLUS),k(ASTR),k(RCBR),s(ENT),        s(LEFT),s(DOWN),s(RGHT),s(P4), s(P5),  s(P6),  X,       // C
_______,k(PIPE),s(Y), s(X), s(C),  s(V), s(B), s(N), s(M), k(LABK),k(RABK),k(QUES),s(RSFT),                       s(HOME),X,      s(END), s(P1), s(P2),  s(P3),  s(PENT), // B
                                         s(SPC),                                   KC_NO,  KC_NO,                 X,      X,      X,      s(P0),         s(PDOT)          // A
    )
/*
    [KM_DFT] = LAYOUT_full(
//   0   1   2   3   4   5   6   7   8   9  10  11  12  13  14      47  48  49     51  52  53  54
// ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬─────┐ ┌───┬───┬───┐  ┌───┬───┬───┬───┐
// │ESC│F1 │F2 │F3 │F4 │F5 │F6 │F7 │F8 │F9 │F10│F11│F12│   │     │ │PRT│SCR│PAU│  │   │   │   │BT │ G
// └───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴─────┘ ├───┼───┼───┤  ├───┼───┼───┼───┤
//                                                                 │   │   │   │  │   │   │   │   │ F
// ┌─────┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐ ├───┼───┼───┤  ├───┼───┼───┼───┤
// │  GRV│ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │ 0 │ - │ = │BS │WIN│ │INS│HOM│PUP│  │NUM│SLS│AST│MNS│ E
// ├───┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┤ ├───┼───┼───┤  ├───┼───┼───┼───┤
// │ALT│TAB│ Q │ W │ E │ R │ T │ Y │ U │ I │ O │ P │ [ │ ] │ALTGR│ │DEL│END│PDN│  │ 7 │ 8 │ 9 │PLS│ D
// ├───┼───┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴───┴┬──┴┬──┴┬──┴┬──┴─┬───┤ ├───┼───┼───┤  ├───┼───┼───┼───┤
// │CTL│CAPS│ A │ S │ D │ F │ G │ H │ J │ K │ L │ ; │ " │ #  │   │ │   │   │   │  │ 5 │ 6 │ 7 │   │ C
// ├───┴──┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┤RET│ ├───┼───┼───┤  ├───┼───┼───┼───┤
// │ SHIFT│ \ │ Z │ X │ C │ V │ B │ N │ M │ , │ . │ / │SHIFT │   │ │   │UP │   │  │ 1 │ 2 │ 3 │   │ B
// └──────┴───┴───┼───┴───┴───┴───┴───┴───┴───┴───┼───┴─┬───┬┴──┬┘ ├───┼───┼───┤  ├───┴───┼───┤ENT│
//                │              SPC              │                │LFT│DN │RGT│  │   0   │ . │   │ A
//                └───────────────────────────────┘     └ ─ ┴ ─ ┘  └───┴───┴───┘  └───────┴───┴───┘
//
// 99   00      01   02    03    04    05    06    07    08      09     10      11      12      13      14     |47      48      49     |51     52      53      54
        KC_ESC,KC_F1,KC_F2,KC_F3,KC_F4,KC_F5,KC_F6,KC_F7,KC_F8,  KC_F9, KC_F10, KC9_F11,KC_F12, X,      X,      KC_PSCR,KC_SCRL,KC_PAUS,X,     X,      X,      QK_BOOT, // G
                                                                                                                X,      X,      X,      X,     X,      X,      X,       // F
        KC_GRV, KC_1,KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8,   KC_9,  KC_0,   KC_MINS,KC_EQL, KC_BSPC,KC_LWIN,KC_INS, KC_HOME,KC_PGUP,KC_NUM,KC_PSLS,KC_PAST,KC_PMNS, // E
KC_LALT,KC_TAB, KC_Q,KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I,   KC_O,  KC_P,   KC_LBRC,KC_RBRC,KC_RALT,        KC_DEL, KC_END, KC_PGDN,KC_P7, KC_P8,  KC_P9,  KC_PPLS, // D
KC_LCTL,KC_CAPS,KC_A,KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K,   KC_L,  KC_SCLN,KC_QUOT,KC_NUHS,KC_ENT,         X,      X,      X,      KC_P4, KC_P5,  KC_P6,  X,       // C
KC_LSFT,KC_BSLS,KC_Z,KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM,KC_DOT,KC_SLSH,KC_RSFT,                        X,      KC_UP,  X,      KC_P1, KC_P2,  KC_P3,  KC_PENT, // B
                                       KC_SPC,                                  X,      X,                      KC_LEFT,KC_DOWN,KC_RGHT,KC_P0,         KC_PDOT          // A
    )
*/
};

void keyboard_gre_init_user(void) {
    debug_config.enable = true;
    debug_config.matrix = true;
    debug_config.keyboard = true;
}

bool caps_word_press_user(uint16_t keycode) {
    switch (keycode) {
        case KC_A ... KC_Z:
            add_weak_mods(MOD_BIT(KC_LSFT)); // apply shift
            break;

        case KC_1 ... KC_0:
        case KC_BSPC:
        case KC_DEL:
        case k(UNDS):
            break; // unshifted

        default:
            return false; // deactivate Caps Word.
    }
    return true;
}

// .
